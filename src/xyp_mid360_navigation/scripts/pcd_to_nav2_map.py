#!/usr/bin/env python3
"""Prepare a horizontal Nav2 map from a Lightning-LM PCD map."""

import argparse
import math
import struct
from pathlib import Path

import numpy as np
import yaml
from PIL import Image


DEFAULT_Q_MAP_LIGHTNING = (0.008708, 0.042288, 0.0, 0.999068)
OCCUPIED_PIXEL = 0
FREE_PIXEL = 254
UNKNOWN_PIXEL = 128


def _lzf_decompress(data, expected_size):
    out = bytearray()
    i = 0
    while i < len(data):
        ctrl = data[i]
        i += 1
        if ctrl < 32:
            length = ctrl + 1
            out.extend(data[i : i + length])
            i += length
        else:
            length = ctrl >> 5
            ref_offset = (ctrl & 0x1F) << 8
            if length == 7:
                length += data[i]
                i += 1
            ref_offset += data[i]
            i += 1
            ref = len(out) - ref_offset - 1
            length += 2
            for _ in range(length):
                out.append(out[ref])
                ref += 1
    if len(out) != expected_size:
        raise ValueError(f"LZF decompressed {len(out)} bytes, expected {expected_size}")
    return bytes(out)


def _read_pcd(path):
    header = []
    with Path(path).open("rb") as f:
        while True:
            line = f.readline()
            if not line:
                raise ValueError("PCD header ended before DATA")
            text = line.decode("ascii").strip()
            header.append(text)
            if text.startswith("DATA "):
                data_type = text.split()[1]
                break
        payload = f.read()

    meta = {}
    for line in header:
        if not line or line.startswith("#"):
            continue
        parts = line.split()
        meta[parts[0]] = parts[1:]

    fields = meta["FIELDS"]
    sizes = [int(x) for x in meta["SIZE"]]
    types = meta["TYPE"]
    counts = [int(x) for x in meta["COUNT"]]
    points = int(meta["POINTS"][0])
    field_widths = [s * c for s, c in zip(sizes, counts)]
    point_step = sum(field_widths)

    if data_type == "binary_compressed":
        compressed_size, uncompressed_size = struct.unpack("<II", payload[:8])
        raw = _lzf_decompress(payload[8 : 8 + compressed_size], uncompressed_size)
        if uncompressed_size != point_step * points:
            raise ValueError("Unexpected binary_compressed payload size")
        arrays = {}
        offset = 0
        for field, size, typ, count, width in zip(fields, sizes, types, counts, field_widths):
            block = raw[offset : offset + points * width]
            offset += points * width
            if count != 1:
                continue
            if typ == "F" and size == 4:
                arrays[field] = np.frombuffer(block, dtype="<f4")
            elif typ == "F" and size == 8:
                arrays[field] = np.frombuffer(block, dtype="<f8")
            elif typ == "U" and size == 4:
                arrays[field] = np.frombuffer(block, dtype="<u4")
            elif typ == "I" and size == 4:
                arrays[field] = np.frombuffer(block, dtype="<i4")
    elif data_type == "binary":
        dtype_fields = []
        for field, size, typ, count in zip(fields, sizes, types, counts):
            if count != 1:
                raise ValueError("Only COUNT 1 PCD fields are supported")
            if typ == "F" and size == 4:
                dtype = "<f4"
            elif typ == "F" and size == 8:
                dtype = "<f8"
            elif typ == "U" and size == 4:
                dtype = "<u4"
            elif typ == "I" and size == 4:
                dtype = "<i4"
            else:
                raise ValueError(f"Unsupported PCD field {field} {typ}{size}")
            dtype_fields.append((field, dtype))
        structured = np.frombuffer(payload, dtype=np.dtype(dtype_fields), count=points)
        arrays = {name: structured[name] for name, _ in dtype_fields}
    elif data_type == "ascii":
        text = payload.decode("ascii")
        numeric = np.loadtxt(text.splitlines(), dtype=np.float64, ndmin=2)
        arrays = {field: numeric[:, idx] for idx, field in enumerate(fields)}
    else:
        raise ValueError(f"Unsupported PCD DATA type: {data_type}")

    xyz = np.column_stack((arrays["x"], arrays["y"], arrays["z"])).astype(np.float64)
    return xyz, arrays


def _write_ascii_xyz_pcd(path, xyz):
    path = Path(path)
    with path.open("w", encoding="ascii") as f:
        f.write("# .PCD v0.7 - Point Cloud Data file format\n")
        f.write("VERSION 0.7\n")
        f.write("FIELDS x y z\n")
        f.write("SIZE 4 4 4\n")
        f.write("TYPE F F F\n")
        f.write("COUNT 1 1 1\n")
        f.write(f"WIDTH {len(xyz)}\n")
        f.write("HEIGHT 1\n")
        f.write("VIEWPOINT 0 0 0 1 0 0 0\n")
        f.write(f"POINTS {len(xyz)}\n")
        f.write("DATA ascii\n")
        for x, y, z in xyz:
            f.write(f"{x:.6f} {y:.6f} {z:.6f}\n")


def _quat_to_matrix(q):
    x, y, z, w = q
    n = math.sqrt(x * x + y * y + z * z + w * w)
    x, y, z, w = x / n, y / n, z / n, w / n
    return np.array(
        [
            [1 - 2 * (y * y + z * z), 2 * (x * y - z * w), 2 * (x * z + y * w)],
            [2 * (x * y + z * w), 1 - 2 * (x * x + z * z), 2 * (y * z - x * w)],
            [2 * (x * z - y * w), 2 * (y * z + x * w), 1 - 2 * (x * x + y * y)],
        ],
        dtype=np.float64,
    )


def _fit_plane(points):
    centroid = points.mean(axis=0)
    centered = points - centroid
    _, _, vh = np.linalg.svd(centered, full_matrices=False)
    normal = vh[-1]
    if normal[2] < 0:
        normal = -normal
    distances = centered @ normal
    rmse = math.sqrt(float(np.mean(distances * distances)))
    p95 = float(np.percentile(np.abs(distances), 95))
    tilt = math.degrees(math.acos(float(np.clip(normal[2], -1.0, 1.0))))
    return normal, centroid, rmse, p95, tilt


def _low_surface_candidates(xyz, cell_size=0.25, z_quantile=0.15, max_points=30000):
    xy = xyz[:, :2]
    mins = xy.min(axis=0)
    ij = np.floor((xy - mins) / cell_size).astype(np.int64)
    order = np.lexsort((ij[:, 1], ij[:, 0]))
    ij_sorted = ij[order]
    z_sorted = xyz[order, 2]
    groups = np.r_[0, np.flatnonzero(np.any(np.diff(ij_sorted, axis=0), axis=1)) + 1, len(order)]
    selected = []
    for start, end in zip(groups[:-1], groups[1:]):
        count = end - start
        if count < 5:
            continue
        local = order[start:end]
        cutoff = float(np.quantile(z_sorted[start:end], z_quantile))
        take = local[z_sorted[start:end] <= cutoff]
        if len(take) > 3:
            take = take[:3]
        selected.extend(take.tolist())
    cand = xyz[np.array(selected, dtype=np.int64)]
    if len(cand) > max_points:
        rng = np.random.default_rng(42)
        cand = cand[rng.choice(len(cand), size=max_points, replace=False)]
    return cand


def _ground_candidates(xyz, ransac_threshold=0.05, ransac_iterations=3000):
    cand = _low_surface_candidates(xyz)
    rng = np.random.default_rng(7)
    best = None
    for _ in range(ransac_iterations):
        sample = cand[rng.choice(len(cand), size=3, replace=False)]
        normal = np.cross(sample[1] - sample[0], sample[2] - sample[0])
        norm = float(np.linalg.norm(normal))
        if norm < 1e-8:
            continue
        normal = normal / norm
        if normal[2] < 0:
            normal = -normal
        tilt = math.degrees(math.acos(float(np.clip(normal[2], -1.0, 1.0))))
        if tilt > 15.0:
            continue
        distances = np.abs((cand - sample[0]) @ normal)
        inlier_count = int(np.count_nonzero(distances < ransac_threshold))
        if best is None or inlier_count > best[0]:
            best = (inlier_count, normal, sample[0])

    if best is None:
        raise RuntimeError("Failed to find a near-horizontal ground plane")

    distances = np.abs((xyz - best[2]) @ best[1])
    inliers = xyz[distances < ransac_threshold]
    normal, centroid, rmse, p95, tilt = _fit_plane(inliers)
    return inliers, normal, centroid, rmse, p95, tilt


def _format_fit(label, fit):
    inliers, normal, centroid, rmse, p95, tilt = fit
    return "\n".join(
        [
            f"{label}:",
            f"  ground_points: {len(inliers)}",
            f"  normal: [{normal[0]:.6f}, {normal[1]:.6f}, {normal[2]:.6f}]",
            f"  tilt_deg: {tilt:.4f}",
            f"  rmse_m: {rmse:.5f}",
            f"  p95_m: {p95:.5f}",
            f"  centroid: [{centroid[0]:.3f}, {centroid[1]:.3f}, {centroid[2]:.3f}]",
        ]
    )


def _z_stats(xyz):
    qs = [0, 1, 5, 10, 25, 50, 75, 90, 95, 99, 100]
    values = np.percentile(xyz[:, 2], qs)
    return "\n".join(f"  p{q:>3}: {v:.4f}" for q, v in zip(qs, values))


def _relative_height_stats(heights):
    qs = [0, 1, 5, 10, 25, 50, 75, 90, 95, 99, 100]
    values = np.percentile(heights, qs)
    return "\n".join(f"  p{q:>3}: {v:.4f}" for q, v in zip(qs, values))


def horizontalize(args):
    xyz, _ = _read_pcd(args.input)
    q = tuple(args.q)
    r_map_lightning = _quat_to_matrix(q)
    candidates = {
        "original_lightning_map": xyz,
        "apply_static_q": xyz @ r_map_lightning.T,
        "apply_inverse_q": xyz @ r_map_lightning,
    }
    fits = {name: _ground_candidates(points) for name, points in candidates.items()}
    best_name = min((name for name in fits if name != "original_lightning_map"), key=lambda n: fits[n][5])
    horizontal = candidates[best_name]

    out_dir = Path(args.output_dir)
    out_dir.mkdir(parents=True, exist_ok=False)
    out_pcd = out_dir / "global_horizontal.pcd"
    stats_path = out_dir / "horizontalization_stats.txt"
    _write_ascii_xyz_pcd(out_pcd, horizontal)

    lines = [
        f"input: {Path(args.input).resolve()}",
        f"output_pcd: {out_pcd.resolve()}",
        "static_tf: parent=map child=lightning_map",
        f"static_tf_quaternion_xyzw: [{q[0]}, {q[1]}, {q[2]}, {q[3]}]",
        "direction_rule: PCD points are expressed in lightning_map; applying T_map_lightning_map maps them into map.",
        f"selected_direction: {best_name}",
        "",
    ]
    for name in ("original_lightning_map", "apply_static_q", "apply_inverse_q"):
        lines.append(_format_fit(name, fits[name]))
        lines.append("")
    lines.extend(["horizontal_z_quantiles_m:", _z_stats(horizontal), ""])
    stats_path.write_text("\n".join(lines), encoding="utf-8")

    print("\n".join(lines))


def _write_map_yaml(path, resolution, origin, occupied_thresh, free_thresh):
    data = {
        "image": "map.pgm",
        "resolution": float(resolution),
        "origin": [float(origin[0]), float(origin[1]), 0.0],
        "negate": 0,
        "occupied_thresh": float(occupied_thresh),
        "free_thresh": float(free_thresh),
    }
    with Path(path).open("w", encoding="utf-8") as f:
        yaml.safe_dump(data, f, default_flow_style=False, sort_keys=False)


def _pixel_to_occupancy(pixel, negate):
    if negate:
        return float(pixel) / 255.0
    return float(255 - pixel) / 255.0


def _semantic_class_for_pixel(pixel, negate, occupied_thresh, free_thresh):
    occupancy = _pixel_to_occupancy(pixel, negate)
    if occupancy >= occupied_thresh:
        return "occupied"
    if occupancy <= free_thresh:
        return "free"
    return "unknown"


def _validate_pixel_semantics(negate, occupied_thresh, free_thresh):
    expected = {
        OCCUPIED_PIXEL: "occupied",
        FREE_PIXEL: "free",
        UNKNOWN_PIXEL: "unknown",
    }
    for pixel, expected_class in expected.items():
        actual = _semantic_class_for_pixel(pixel, negate, occupied_thresh, free_thresh)
        if actual != expected_class:
            occupancy = _pixel_to_occupancy(pixel, negate)
            raise ValueError(
                f"Pixel {pixel} is interpreted as {actual}, expected {expected_class}; "
                f"occupancy={occupancy:.6f}, negate={negate}, "
                f"occupied_thresh={occupied_thresh}, free_thresh={free_thresh}"
            )


def _image_from_state(state, occupied_thresh, free_thresh, negate=0):
    _validate_pixel_semantics(negate, occupied_thresh, free_thresh)
    image = np.full(state.shape, UNKNOWN_PIXEL, dtype=np.uint8)
    image[state == 0] = FREE_PIXEL
    image[state == 100] = OCCUPIED_PIXEL
    return np.flipud(image)


def _stamp_ns(stamp):
    return int(stamp.sec) * 1_000_000_000 + int(stamp.nanosec)


def _normalize_quat(q):
    q = np.asarray(q, dtype=np.float64)
    return q / np.linalg.norm(q)


def _slerp_quat(q0, q1, ratio):
    q0 = _normalize_quat(q0)
    q1 = _normalize_quat(q1)
    dot = float(np.dot(q0, q1))
    if dot < 0.0:
        q1 = -q1
        dot = -dot
    if dot > 0.9995:
        return _normalize_quat(q0 + ratio * (q1 - q0))
    theta0 = math.acos(float(np.clip(dot, -1.0, 1.0)))
    sin_theta0 = math.sin(theta0)
    theta = theta0 * ratio
    return (
        math.sin(theta0 - theta) / sin_theta0 * q0
        + math.sin(theta) / sin_theta0 * q1
    )


def _rpy_to_quat(roll, pitch, yaw):
    cr, sr = math.cos(roll * 0.5), math.sin(roll * 0.5)
    cp, sp = math.cos(pitch * 0.5), math.sin(pitch * 0.5)
    cy, sy = math.cos(yaw * 0.5), math.sin(yaw * 0.5)
    return np.array(
        [
            sr * cp * cy - cr * sp * sy,
            cr * sp * cy + sr * cp * sy,
            cr * cp * sy - sr * sp * cy,
            cr * cp * cy + sr * sp * sy,
        ],
        dtype=np.float64,
    )


def _transform_points(points, translation, quat):
    return points @ _quat_to_matrix(tuple(quat)).T + translation


def _transform_point(point, translation, quat):
    return _quat_to_matrix(tuple(quat)) @ point + translation


def _transform_to_tuple(transform):
    trans = transform.transform.translation
    rot = transform.transform.rotation
    return (
        np.array([trans.x, trans.y, trans.z], dtype=np.float64),
        np.array([rot.x, rot.y, rot.z, rot.w], dtype=np.float64),
    )


def _interpolate_transform(series, stamp_ns):
    times = series["times"]
    idx = int(np.searchsorted(times, stamp_ns))
    if idx <= 0 or idx >= len(times):
        return None
    t0, t1 = int(times[idx - 1]), int(times[idx])
    ratio = 0.0 if t1 == t0 else (stamp_ns - t0) / (t1 - t0)
    trans = series["trans"][idx - 1] + ratio * (series["trans"][idx] - series["trans"][idx - 1])
    quat = _slerp_quat(series["quat"][idx - 1], series["quat"][idx], ratio)
    nearest_error_ns = min(abs(stamp_ns - t0), abs(t1 - stamp_ns))
    bracket_ns = t1 - t0
    return trans, quat, nearest_error_ns, bracket_ns


def _compose_points(points, transforms):
    out = points
    for trans, quat in transforms:
        out = _transform_points(out, trans, quat)
    return out


def _compose_origin(transforms):
    point = np.zeros(3, dtype=np.float64)
    for trans, quat in transforms:
        point = _transform_point(point, trans, quat)
    return point


def _quat_to_yaw(quat):
    x, y, z, w = _normalize_quat(quat)
    siny_cosp = 2.0 * (w * z + x * y)
    cosy_cosp = 1.0 - 2.0 * (y * y + z * z)
    return math.atan2(siny_cosp, cosy_cosp)


def _point_in_poly(px, py, poly):
    inside = False
    n = len(poly)
    j = n - 1
    for i in range(n):
        xi, yi = poly[i]
        xj, yj = poly[j]
        intersect = ((yi > py) != (yj > py)) and (
            px < (xj - xi) * (py - yi) / ((yj - yi) if abs(yj - yi) > 1e-12 else 1e-12) + xi
        )
        if intersect:
            inside = not inside
        j = i
    return inside


def _rectangle_polygon(center_xy, yaw, length, width):
    hl = length * 0.5
    hw = width * 0.5
    c = math.cos(yaw)
    s = math.sin(yaw)
    local = np.array(
        [
            [hl, hw],
            [hl, -hw],
            [-hl, -hw],
            [-hl, hw],
        ],
        dtype=np.float64,
    )
    rot = np.array([[c, -s], [s, c]], dtype=np.float64)
    return local @ rot.T + np.asarray(center_xy, dtype=np.float64)


def _footprint_cells_for_pose(center_xy, yaw, length, width, origin, resolution, map_width, map_height):
    poly = _rectangle_polygon(center_xy, yaw, length, width)
    min_xy = np.min(poly, axis=0)
    max_xy = np.max(poly, axis=0)
    min_i = max(0, int(math.floor((min_xy[0] - origin[0]) / resolution)))
    max_i = min(map_width - 1, int(math.floor((max_xy[0] - origin[0]) / resolution)))
    min_j = max(0, int(math.floor((min_xy[1] - origin[1]) / resolution)))
    max_j = min(map_height - 1, int(math.floor((max_xy[1] - origin[1]) / resolution)))
    cells = []
    for j in range(min_j, max_j + 1):
        cy = origin[1] + (j + 0.5) * resolution
        for i in range(min_i, max_i + 1):
            cx = origin[0] + (i + 0.5) * resolution
            if _point_in_poly(cx, cy, poly):
                cells.append((i, j))
    return cells, poly


def _bresenham(x0, y0, x1, y1):
    dx = abs(x1 - x0)
    dy = abs(y1 - y0)
    sx = 1 if x0 < x1 else -1
    sy = 1 if y0 < y1 else -1
    err = dx - dy
    x, y = x0, y0
    while True:
        yield x, y
        if x == x1 and y == y1:
            break
        e2 = 2 * err
        if e2 > -dy:
            err -= dy
            x += sx
        if e2 < dx:
            err += dx
            y += sy


def _load_tf_for_raytrace(tf_bag):
    import rosbag2_py
    from rclpy.serialization import deserialize_message
    from rosidl_runtime_py.utilities import get_message

    reader = rosbag2_py.SequentialReader()
    reader.open(
        rosbag2_py.StorageOptions(uri=str(Path(tf_bag).resolve()), storage_id="sqlite3"),
        rosbag2_py.ConverterOptions("", ""),
    )
    tf_msg_type = get_message("tf2_msgs/msg/TFMessage")
    raw = {
        ("lightning_map", "odom"): [],
        ("odom", "base_link"): [],
    }
    static_map_lightning = None
    while reader.has_next():
        topic, data, _ = reader.read_next()
        if topic not in ("/tf", "/tf_static"):
            continue
        msg = deserialize_message(data, tf_msg_type)
        for transform in msg.transforms:
            edge = (transform.header.frame_id, transform.child_frame_id)
            if edge in raw:
                trans, quat = _transform_to_tuple(transform)
                raw[edge].append((_stamp_ns(transform.header.stamp), trans, quat))
            elif topic == "/tf_static" and edge == ("map", "lightning_map"):
                static_map_lightning = _transform_to_tuple(transform)

    if static_map_lightning is None:
        static_map_lightning = (
            np.zeros(3, dtype=np.float64),
            np.asarray(DEFAULT_Q_MAP_LIGHTNING, dtype=np.float64),
        )

    series = {}
    for edge, rows in raw.items():
        if not rows:
            raise RuntimeError(f"TF bag has no {edge[0]}->{edge[1]} transforms")
        rows.sort(key=lambda row: row[0])
        times = np.asarray([row[0] for row in rows], dtype=np.int64)
        trans = np.vstack([row[1] for row in rows])
        quat = np.vstack([row[2] for row in rows])
        series[edge] = {"times": times, "trans": trans, "quat": quat}
    return static_map_lightning, series


def _read_lidar_messages(lidar_bag, lidar_topic, frame_stride, point_stride):
    import rosbag2_py
    from rclpy.serialization import deserialize_message
    from rosidl_runtime_py.utilities import get_message

    reader = rosbag2_py.SequentialReader()
    reader.open(
        rosbag2_py.StorageOptions(uri=str(Path(lidar_bag).resolve()), storage_id="sqlite3"),
        rosbag2_py.ConverterOptions("", ""),
    )
    topics = {topic.name: topic.type for topic in reader.get_all_topics_and_types()}
    if lidar_topic not in topics:
        raise RuntimeError(f"Bag has no lidar topic {lidar_topic}")
    msg_type = get_message(topics[lidar_topic])
    messages = []
    index = -1
    frame_id = None
    total = 0
    while reader.has_next():
        topic, data, _ = reader.read_next()
        if topic != lidar_topic:
            continue
        index += 1
        total += 1
        if index % frame_stride != 0:
            continue
        msg = deserialize_message(data, msg_type)
        frame_id = frame_id or msg.header.frame_id
        sampled_points = msg.points[::point_stride] if point_stride > 1 else msg.points
        points = np.asarray([[p.x, p.y, p.z] for p in sampled_points], dtype=np.float64)
        messages.append((_stamp_ns(msg.header.stamp), msg.header.frame_id, points))
    if not messages:
        raise RuntimeError(f"No lidar messages selected from {lidar_topic}")
    return messages, total, frame_id


def _grid_from_horizontal_pcd(xyz, args):
    ground_inliers, normal, centroid, rmse, p95, tilt = _ground_candidates(xyz)
    heights = (xyz - centroid) @ normal
    xy = xyz[:, :2]
    min_xy = xy.min(axis=0)
    max_xy = xy.max(axis=0)
    origin = np.floor(min_xy / args.resolution) * args.resolution
    max_corner = np.ceil(max_xy / args.resolution) * args.resolution
    width = int(math.ceil((max_corner[0] - origin[0]) / args.resolution)) + 1
    height = int(math.ceil((max_corner[1] - origin[1]) / args.resolution)) + 1
    ij = np.floor((xy - origin) / args.resolution).astype(np.int64)
    valid = (ij[:, 0] >= 0) & (ij[:, 0] < width) & (ij[:, 1] >= 0) & (ij[:, 1] < height)
    ij = ij[valid]
    heights_valid = heights[valid]
    ground_mask = (heights_valid >= args.ground_min) & (heights_valid <= args.ground_max)
    obstacle_mask = (heights_valid >= args.obstacle_min) & (heights_valid <= args.obstacle_max)
    ground_counts = np.zeros((height, width), dtype=np.uint16)
    obstacle_counts = np.zeros((height, width), dtype=np.uint16)
    np.add.at(ground_counts, (ij[ground_mask, 1], ij[ground_mask, 0]), 1)
    np.add.at(obstacle_counts, (ij[obstacle_mask, 1], ij[obstacle_mask, 0]), 1)
    static_state = np.full((height, width), -1, dtype=np.int8)
    static_state[ground_counts >= args.min_ground_points] = 0
    static_state[obstacle_counts >= args.min_obstacle_points] = 100
    return {
        "origin": origin,
        "width": width,
        "height": height,
        "ground_fit": (ground_inliers, normal, centroid, rmse, p95, tilt),
        "normal": normal,
        "centroid": centroid,
        "static_state": static_state,
        "static_ground_counts": ground_counts,
        "static_obstacle_counts": obstacle_counts,
        "relative_heights": heights,
    }


def _state_from_map_yaml(map_yaml_path):
    map_yaml_path = Path(map_yaml_path)
    data = yaml.safe_load(map_yaml_path.read_text(encoding="utf-8"))
    image_path = map_yaml_path.parent / data["image"]
    image = np.asarray(Image.open(image_path).convert("L"), dtype=np.uint8)
    ros_image = np.flipud(image)
    state = np.full(ros_image.shape, -1, dtype=np.int8)
    state[ros_image >= 250] = 0
    state[ros_image <= 10] = 100
    origin = np.asarray(data["origin"][:2], dtype=np.float64)
    return state, float(data["resolution"]), origin, image_path


def rasterize(args):
    xyz, _ = _read_pcd(args.input)
    ground_inliers, normal, centroid, rmse, p95, tilt = _ground_candidates(xyz)
    heights = (xyz - centroid) @ normal

    xy = xyz[:, :2]
    min_xy = xy.min(axis=0)
    max_xy = xy.max(axis=0)
    origin = np.floor(min_xy / args.resolution) * args.resolution
    max_corner = np.ceil(max_xy / args.resolution) * args.resolution
    width = int(math.ceil((max_corner[0] - origin[0]) / args.resolution)) + 1
    height = int(math.ceil((max_corner[1] - origin[1]) / args.resolution)) + 1

    ij = np.floor((xy - origin) / args.resolution).astype(np.int64)
    valid = (ij[:, 0] >= 0) & (ij[:, 0] < width) & (ij[:, 1] >= 0) & (ij[:, 1] < height)
    ij = ij[valid]
    heights_valid = heights[valid]

    ground_mask = (heights_valid >= args.ground_min) & (heights_valid <= args.ground_max)
    obstacle_mask = (heights_valid >= args.obstacle_min) & (heights_valid <= args.obstacle_max)

    ground_counts = np.zeros((height, width), dtype=np.uint16)
    obstacle_counts = np.zeros((height, width), dtype=np.uint16)
    np.add.at(ground_counts, (ij[ground_mask, 1], ij[ground_mask, 0]), 1)
    np.add.at(obstacle_counts, (ij[obstacle_mask, 1], ij[obstacle_mask, 0]), 1)

    state = np.full((height, width), -1, dtype=np.int8)
    free = ground_counts >= args.min_ground_points
    occupied = obstacle_counts >= args.min_obstacle_points
    state[free] = 0
    state[occupied] = 100

    image_for_pgm = _image_from_state(state, args.occupied_thresh, args.free_thresh)

    out_dir = Path(args.output_dir)
    out_dir.mkdir(parents=True, exist_ok=True)
    map_pgm = out_dir / "map.pgm"
    map_yaml = out_dir / "map.yaml"
    preview_png = out_dir / "map_preview.png"
    stats_path = out_dir / "rasterization_stats.txt"
    Image.fromarray(image_for_pgm, mode="L").save(map_pgm)
    Image.fromarray(image_for_pgm, mode="L").save(preview_png)
    _write_map_yaml(map_yaml, args.resolution, origin, args.occupied_thresh, args.free_thresh)

    total = int(width * height)
    occupied_cells = int(np.count_nonzero(state == 100))
    free_cells = int(np.count_nonzero(state == 0))
    unknown_cells = int(np.count_nonzero(state < 0))
    physical_width = width * args.resolution
    physical_height = height * args.resolution

    lines = [
        f"input: {Path(args.input).resolve()}",
        f"map_pgm: {map_pgm.resolve()}",
        f"map_yaml: {map_yaml.resolve()}",
        f"preview_png: {preview_png.resolve()}",
        "frame_semantics: map",
        f"resolution_m: {args.resolution}",
        f"width_cells: {width}",
        f"height_cells: {height}",
        f"physical_width_m: {physical_width:.3f}",
        f"physical_height_m: {physical_height:.3f}",
        f"origin: [{origin[0]:.6f}, {origin[1]:.6f}, 0.0]",
        "image_row_rule: PGM rows are vertically flipped so map.yaml origin is the lower-left map cell.",
        "",
        _format_fit("ground_fit_used_for_relative_height", (ground_inliers, normal, centroid, rmse, p95, tilt)),
        "",
        "relative_height_thresholds_m:",
        f"  ground: [{args.ground_min}, {args.ground_max}]",
        f"  obstacle: [{args.obstacle_min}, {args.obstacle_max}]",
        "  uncertain band remains unknown unless obstacle/free evidence reaches thresholds.",
        f"min_ground_points: {args.min_ground_points}",
        f"min_obstacle_points: {args.min_obstacle_points}",
        "",
        "relative_height_quantiles_m:",
        _relative_height_stats(heights),
        "",
        "classification_counts:",
        f"  occupied_cells: {occupied_cells}",
        f"  free_cells: {free_cells}",
        f"  unknown_cells: {unknown_cells}",
        f"  occupied_percent: {occupied_cells / total * 100.0:.3f}",
        f"  free_percent: {free_cells / total * 100.0:.3f}",
        f"  unknown_percent: {unknown_cells / total * 100.0:.3f}",
        "",
        "point_evidence_counts:",
        f"  ground_points_in_threshold: {int(np.count_nonzero(ground_mask))}",
        f"  obstacle_points_in_threshold: {int(np.count_nonzero(obstacle_mask))}",
        f"  max_ground_points_per_cell: {int(ground_counts.max())}",
        f"  max_obstacle_points_per_cell: {int(obstacle_counts.max())}",
        "",
    ]
    stats_path.write_text("\n".join(lines), encoding="utf-8")
    print("\n".join(lines))


def raytrace(args):
    xyz, _ = _read_pcd(args.pcd_input)
    grid = _grid_from_horizontal_pcd(xyz, args)
    origin = grid["origin"]
    width = grid["width"]
    height = grid["height"]
    static_state = grid["static_state"]
    normal = grid["normal"]
    centroid = grid["centroid"]

    t_map_lightning, tf_series = _load_tf_for_raytrace(args.tf_bag)
    lidar_messages, total_lidar_frames, lidar_frame = _read_lidar_messages(
        args.lidar_bag, args.lidar_topic, args.frame_stride, args.point_stride
    )

    lidar_stamp_range = (lidar_messages[0][0], lidar_messages[-1][0])
    lmo_range = (
        int(tf_series[("lightning_map", "odom")]["times"][0]),
        int(tf_series[("lightning_map", "odom")]["times"][-1]),
    )
    ob_range = (
        int(tf_series[("odom", "base_link")]["times"][0]),
        int(tf_series[("odom", "base_link")]["times"][-1]),
    )
    overlap_start = max(lidar_stamp_range[0], lmo_range[0], ob_range[0])
    overlap_end = min(lidar_stamp_range[1], lmo_range[1], ob_range[1])
    if overlap_start >= overlap_end:
        raise RuntimeError(
            "Lidar and TF header stamp ranges do not overlap; refusing to raytrace"
        )

    t_base_livox = (
        np.array([args.base_to_livox_x, args.base_to_livox_y, args.base_to_livox_z], dtype=np.float64),
        _rpy_to_quat(args.base_to_livox_roll, args.base_to_livox_pitch, args.base_to_livox_yaw),
    )

    free_counts = np.zeros((height, width), dtype=np.uint16)
    endpoint_obstacle_counts = np.zeros((height, width), dtype=np.uint16)
    ray_lengths = []
    tf_nearest_errors = []
    tf_brackets = []
    processed_frames = 0
    skipped_frames = 0
    skipped_points = 0
    processed_rays = 0
    obstacle_endpoint_rays = 0
    ground_endpoint_rays = 0
    uncertain_endpoint_rays = 0
    high_endpoint_rays = 0
    out_of_grid_rays = 0
    stopped_by_static_occupied = 0

    for stamp_ns, frame_id, points_livox in lidar_messages:
        interp_lmo = _interpolate_transform(tf_series[("lightning_map", "odom")], stamp_ns)
        interp_ob = _interpolate_transform(tf_series[("odom", "base_link")], stamp_ns)
        if interp_lmo is None or interp_ob is None:
            skipped_frames += 1
            continue
        t_lmo = (interp_lmo[0], interp_lmo[1])
        t_odom_base = (interp_ob[0], interp_ob[1])
        tf_nearest_errors.extend([interp_lmo[2], interp_ob[2]])
        tf_brackets.extend([interp_lmo[3], interp_ob[3]])

        transforms = [t_base_livox, t_odom_base, t_lmo, t_map_lightning]
        lidar_origin = _compose_origin(transforms)
        origin_cell = np.floor((lidar_origin[:2] - origin) / args.resolution).astype(np.int64)
        if not (0 <= origin_cell[0] < width and 0 <= origin_cell[1] < height):
            skipped_frames += 1
            continue

        finite = np.isfinite(points_livox).all(axis=1)
        ranges = np.linalg.norm(points_livox, axis=1)
        keep = finite & (ranges >= args.min_ray_range) & (ranges <= args.max_ray_range)
        points_livox = points_livox[keep]
        ranges = ranges[keep]
        if len(points_livox) == 0:
            processed_frames += 1
            continue

        points_map = _compose_points(points_livox, transforms)
        endpoint_cells = np.floor((points_map[:, :2] - origin) / args.resolution).astype(np.int64)
        heights = (points_map - centroid) @ normal
        processed_frames += 1

        for endpoint_cell, rel_h, ray_range in zip(endpoint_cells, heights, ranges):
            ex, ey = int(endpoint_cell[0]), int(endpoint_cell[1])
            if not (0 <= ex < width and 0 <= ey < height):
                out_of_grid_rays += 1
                continue
            is_ground = args.ground_min <= rel_h <= args.ground_max
            is_obstacle = args.obstacle_min <= rel_h <= args.obstacle_max
            is_high = rel_h > args.obstacle_max
            if is_high:
                high_endpoint_rays += 1

            ray_cells = list(_bresenham(int(origin_cell[0]), int(origin_cell[1]), ex, ey))
            if len(ray_cells) <= 1:
                skipped_points += 1
                continue

            blocked = False
            for cx, cy in ray_cells[1:-1]:
                if static_state[cy, cx] == 100:
                    stopped_by_static_occupied += 1
                    blocked = True
                    break
                free_counts[cy, cx] = min(int(free_counts[cy, cx]) + 1, np.iinfo(np.uint16).max)
            if blocked:
                continue

            processed_rays += 1
            ray_lengths.append(float(ray_range))
            if is_obstacle:
                endpoint_obstacle_counts[ey, ex] = min(
                    int(endpoint_obstacle_counts[ey, ex]) + 1, np.iinfo(np.uint16).max
                )
                obstacle_endpoint_rays += 1
            elif is_ground:
                if static_state[ey, ex] != 100:
                    free_counts[ey, ex] = min(
                        int(free_counts[ey, ex]) + 1, np.iinfo(np.uint16).max
                    )
                ground_endpoint_rays += 1
            elif not is_high:
                uncertain_endpoint_rays += 1

    state = np.array(static_state, copy=True)
    ray_free = (free_counts >= args.min_free_rays) & (state != 100)
    state[ray_free] = 0
    added_occupied = np.zeros_like(ray_free, dtype=bool)
    if args.add_observed_occupied_threshold > 0:
        added_occupied = endpoint_obstacle_counts >= args.add_observed_occupied_threshold
        state[added_occupied] = 100

    image_for_pgm = _image_from_state(state, args.occupied_thresh, args.free_thresh)

    out_dir = Path(args.output_dir)
    out_dir.mkdir(parents=True, exist_ok=False)
    map_pgm = out_dir / "map.pgm"
    map_yaml = out_dir / "map.yaml"
    preview_png = out_dir / "map_preview.png"
    stats_path = out_dir / "rasterization_stats.txt"
    Image.fromarray(image_for_pgm, mode="L").save(map_pgm)
    Image.fromarray(image_for_pgm, mode="L").save(preview_png)
    _write_map_yaml(map_yaml, args.resolution, origin, args.occupied_thresh, args.free_thresh)

    total_cells = int(width * height)
    static_occ = int(np.count_nonzero(static_state == 100))
    static_free = int(np.count_nonzero(static_state == 0))
    static_unknown = int(np.count_nonzero(static_state < 0))
    occ = int(np.count_nonzero(state == 100))
    free = int(np.count_nonzero(state == 0))
    unknown = int(np.count_nonzero(state < 0))
    ray_lengths_arr = np.asarray(ray_lengths, dtype=np.float64)
    tf_err_ms = np.asarray(tf_nearest_errors, dtype=np.float64) / 1e6
    tf_bracket_ms = np.asarray(tf_brackets, dtype=np.float64) / 1e6

    def pct(count):
        return count / total_cells * 100.0

    def stat_line(name, values, unit):
        if len(values) == 0:
            return [f"{name}_count: 0"]
        return [
            f"{name}_count: {len(values)}",
            f"{name}_mean_{unit}: {float(np.mean(values)):.4f}",
            f"{name}_max_{unit}: {float(np.max(values)):.4f}",
            f"{name}_p95_{unit}: {float(np.percentile(values, 95)):.4f}",
        ]

    lines = [
        f"pcd_input: {Path(args.pcd_input).resolve()}",
        f"lidar_bag: {Path(args.lidar_bag).resolve()}",
        f"tf_bag: {Path(args.tf_bag).resolve()}",
        f"map_pgm: {map_pgm.resolve()}",
        f"map_yaml: {map_yaml.resolve()}",
        f"preview_png: {preview_png.resolve()}",
        "frame_semantics: map",
        f"lidar_topic: {args.lidar_topic}",
        f"lidar_frame_seen: {lidar_frame}",
        "base_link_to_livox_frame:",
        f"  xyz_m: [{args.base_to_livox_x}, {args.base_to_livox_y}, {args.base_to_livox_z}]",
        f"  rpy_rad: [{args.base_to_livox_roll}, {args.base_to_livox_pitch}, {args.base_to_livox_yaw}]",
        f"resolution_m: {args.resolution}",
        f"width_cells: {width}",
        f"height_cells: {height}",
        f"origin: [{origin[0]:.6f}, {origin[1]:.6f}, 0.0]",
        "image_row_rule: PGM rows are vertically flipped so map.yaml origin is the lower-left map cell.",
        "",
        "header_stamp_ranges_ns:",
        f"  lidar: [{lidar_stamp_range[0]}, {lidar_stamp_range[1]}]",
        f"  lightning_map_to_odom: [{lmo_range[0]}, {lmo_range[1]}]",
        f"  odom_to_base_link: [{ob_range[0]}, {ob_range[1]}]",
        f"  overlap: [{overlap_start}, {overlap_end}]",
        "",
        "tf_interpolation_error:",
        *stat_line("nearest_tf_error", tf_err_ms, "ms"),
        *stat_line("tf_bracket", tf_bracket_ms, "ms"),
        "",
        _format_fit("ground_fit_used_for_relative_height", grid["ground_fit"]),
        "",
        "relative_height_thresholds_m:",
        f"  ground: [{args.ground_min}, {args.ground_max}]",
        f"  obstacle: [{args.obstacle_min}, {args.obstacle_max}]",
        f"  high_structures_ignored_above: {args.obstacle_max}",
        f"min_free_rays: {args.min_free_rays}",
        f"min_ground_points_for_static_base: {args.min_ground_points}",
        f"min_obstacle_points_for_static_base: {args.min_obstacle_points}",
        f"add_observed_occupied_threshold: {args.add_observed_occupied_threshold}",
        "",
        "processing:",
        f"  total_lidar_frames: {total_lidar_frames}",
        f"  selected_lidar_frames: {len(lidar_messages)}",
        f"  processed_frames: {processed_frames}",
        f"  skipped_frames: {skipped_frames}",
        f"  frame_stride: {args.frame_stride}",
        f"  point_stride: {args.point_stride}",
        f"  min_ray_range_m: {args.min_ray_range}",
        f"  max_ray_range_m: {args.max_ray_range}",
        f"  processed_rays: {processed_rays}",
        f"  skipped_points: {skipped_points}",
        f"  out_of_grid_rays: {out_of_grid_rays}",
        f"  stopped_by_static_occupied: {stopped_by_static_occupied}",
        f"  ground_endpoint_rays: {ground_endpoint_rays}",
        f"  obstacle_endpoint_rays: {obstacle_endpoint_rays}",
        f"  uncertain_endpoint_rays: {uncertain_endpoint_rays}",
        f"  high_endpoint_rays: {high_endpoint_rays}",
        *stat_line("ray_length", ray_lengths_arr, "m"),
        "",
        "classification_counts_static_base:",
        f"  occupied_cells: {static_occ}",
        f"  free_cells: {static_free}",
        f"  unknown_cells: {static_unknown}",
        f"  occupied_percent: {pct(static_occ):.3f}",
        f"  free_percent: {pct(static_free):.3f}",
        f"  unknown_percent: {pct(static_unknown):.3f}",
        "",
        "classification_counts_raytraced:",
        f"  occupied_cells: {occ}",
        f"  free_cells: {free}",
        f"  unknown_cells: {unknown}",
        f"  occupied_percent: {pct(occ):.3f}",
        f"  free_percent: {pct(free):.3f}",
        f"  unknown_percent: {pct(unknown):.3f}",
        f"  ray_added_free_cells: {int(np.count_nonzero(ray_free & (static_state < 0)))}",
        f"  observed_occupied_added_cells: {int(np.count_nonzero(added_occupied & (static_state != 100)))}",
        "",
    ]
    stats_path.write_text("\n".join(lines), encoding="utf-8")
    print("\n".join(lines))


def clean_trajectory(args):
    xyz, _ = _read_pcd(args.pcd_input)
    grid = _grid_from_horizontal_pcd(xyz, args)
    origin = grid["origin"]
    width = grid["width"]
    height = grid["height"]
    static_state = grid["static_state"]
    base_map_image = None
    base_map_source = "pcd_static_raster"
    if args.map_yaml:
        static_state, map_resolution, origin, base_map_image = _state_from_map_yaml(args.map_yaml)
        if abs(map_resolution - args.resolution) > 1e-9:
            raise RuntimeError(
                f"Input map resolution {map_resolution} does not match --resolution {args.resolution}"
            )
        height, width = static_state.shape
        base_map_source = str(Path(args.map_yaml).resolve())

    t_map_lightning, tf_series = _load_tf_for_raytrace(args.tf_bag)
    lmo = tf_series[("lightning_map", "odom")]
    ob = tf_series[("odom", "base_link")]
    times = lmo["times"][:: args.pose_stride]
    swept = np.zeros((height, width), dtype=bool)
    centers = []
    yaws = []
    skipped_poses = 0

    for stamp_ns in times:
        interp_lmo = _interpolate_transform(lmo, int(stamp_ns))
        interp_ob = _interpolate_transform(ob, int(stamp_ns))
        if interp_lmo is None or interp_ob is None:
            skipped_poses += 1
            continue
        t_lmo = (interp_lmo[0], interp_lmo[1])
        t_odom_base = (interp_ob[0], interp_ob[1])
        center = _compose_origin([t_odom_base, t_lmo, t_map_lightning])
        base_x = _transform_point(np.array([1.0, 0.0, 0.0], dtype=np.float64), *t_odom_base)
        base_x = _transform_point(base_x, *t_lmo)
        base_x = _transform_point(base_x, *t_map_lightning)
        yaw = math.atan2(base_x[1] - center[1], base_x[0] - center[0])
        cells, _ = _footprint_cells_for_pose(
            center[:2],
            yaw,
            args.footprint_length,
            args.footprint_width,
            origin,
            args.resolution,
            width,
            height,
        )
        for i, j in cells:
            swept[j, i] = True
        centers.append(center[:2])
        yaws.append(yaw)

    centers = np.asarray(centers, dtype=np.float64)
    removed_occupied = swept & (static_state == 100)
    state = np.array(static_state, copy=True)
    state[swept] = 0

    removed_indices = np.argwhere(removed_occupied)
    removed_distances = []
    if len(removed_indices) > 0 and len(centers) > 0:
        removed_xy = np.column_stack(
            (
                origin[0] + (removed_indices[:, 1] + 0.5) * args.resolution,
                origin[1] + (removed_indices[:, 0] + 0.5) * args.resolution,
            )
        )
        chunk = 1000
        for start in range(0, len(removed_xy), chunk):
            local = removed_xy[start : start + chunk]
            d2 = np.sum((local[:, None, :] - centers[None, :, :]) ** 2, axis=2)
            removed_distances.extend(np.sqrt(np.min(d2, axis=1)).tolist())
    removed_distances = np.asarray(removed_distances, dtype=np.float64)
    wall_risk = bool(len(removed_distances) > 0 and np.percentile(removed_distances, 95) > args.wall_risk_distance)

    out_dir = Path(args.output_dir)
    if wall_risk and not args.write_on_wall_risk:
        raise RuntimeError(
            "Trajectory clearing risk is high: removed occupied cells extend far from base_link trajectory"
        )
    out_dir.mkdir(parents=True, exist_ok=False)
    map_pgm = out_dir / "map.pgm"
    map_yaml = out_dir / "map.yaml"
    preview_png = out_dir / "map_preview.png"
    stats_path = out_dir / "rasterization_stats.txt"

    image_for_pgm = _image_from_state(state, args.occupied_thresh, args.free_thresh)
    Image.fromarray(image_for_pgm, mode="L").save(map_pgm)
    Image.fromarray(image_for_pgm, mode="L").save(preview_png)
    _write_map_yaml(map_yaml, args.resolution, origin, args.occupied_thresh, args.free_thresh)

    total_cells = int(width * height)
    before_occ = int(np.count_nonzero(static_state == 100))
    before_free = int(np.count_nonzero(static_state == 0))
    before_unknown = int(np.count_nonzero(static_state < 0))
    after_occ = int(np.count_nonzero(state == 100))
    after_free = int(np.count_nonzero(state == 0))
    after_unknown = int(np.count_nonzero(state < 0))

    def pct(count):
        return count / total_cells * 100.0

    def dist_lines():
        if len(removed_distances) == 0:
            return ["removed_occupied_distance_count: 0"]
        return [
            f"removed_occupied_distance_count: {len(removed_distances)}",
            f"removed_occupied_distance_mean_m: {float(np.mean(removed_distances)):.4f}",
            f"removed_occupied_distance_max_m: {float(np.max(removed_distances)):.4f}",
            f"removed_occupied_distance_p50_m: {float(np.percentile(removed_distances, 50)):.4f}",
            f"removed_occupied_distance_p95_m: {float(np.percentile(removed_distances, 95)):.4f}",
        ]

    lines = [
        f"pcd_input: {Path(args.pcd_input).resolve()}",
        f"base_map_source: {base_map_source}",
        f"base_map_image: {base_map_image.resolve() if base_map_image else ''}",
        f"tf_bag: {Path(args.tf_bag).resolve()}",
        f"map_pgm: {map_pgm.resolve()}",
        f"map_yaml: {map_yaml.resolve()}",
        f"preview_png: {preview_png.resolve()}",
        "frame_semantics: map",
        f"resolution_m: {args.resolution}",
        f"width_cells: {width}",
        f"height_cells: {height}",
        f"origin: [{origin[0]:.6f}, {origin[1]:.6f}, 0.0]",
        "",
        "trajectory_footprint:",
        f"  source_tf_chain: map->lightning_map->odom->base_link",
        f"  pose_stride: {args.pose_stride}",
        f"  trajectory_poses: {len(centers)}",
        f"  skipped_poses: {skipped_poses}",
        f"  footprint_length_m: {args.footprint_length}",
        f"  footprint_width_m: {args.footprint_width}",
        f"  swept_footprint_cells: {int(np.count_nonzero(swept))}",
        f"  wall_risk_distance_m: {args.wall_risk_distance}",
        f"  wall_risk_detected: {wall_risk}",
        "",
        _format_fit("ground_fit_used_for_static_base", grid["ground_fit"]),
        "",
        "removed_occupied:",
        f"  removed_occupied_cells: {int(np.count_nonzero(removed_occupied))}",
        *dist_lines(),
        "",
        "classification_counts_before_clean:",
        f"  occupied_cells: {before_occ}",
        f"  free_cells: {before_free}",
        f"  unknown_cells: {before_unknown}",
        f"  occupied_percent: {pct(before_occ):.3f}",
        f"  free_percent: {pct(before_free):.3f}",
        f"  unknown_percent: {pct(before_unknown):.3f}",
        "",
        "classification_counts_after_clean:",
        f"  occupied_cells: {after_occ}",
        f"  free_cells: {after_free}",
        f"  unknown_cells: {after_unknown}",
        f"  occupied_percent: {pct(after_occ):.3f}",
        f"  free_percent: {pct(after_free):.3f}",
        f"  unknown_percent: {pct(after_unknown):.3f}",
        "",
    ]
    stats_path.write_text("\n".join(lines), encoding="utf-8")
    print("\n".join(lines))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    sub = parser.add_subparsers(dest="cmd", required=True)
    h = sub.add_parser("horizontalize")
    h.add_argument("--input", required=True)
    h.add_argument("--output-dir", required=True)
    h.add_argument("--q", nargs=4, type=float, default=DEFAULT_Q_MAP_LIGHTNING)
    h.set_defaults(func=horizontalize)
    r = sub.add_parser("rasterize")
    r.add_argument("--input", required=True)
    r.add_argument("--output-dir", required=True)
    r.add_argument("--resolution", type=float, required=True)
    r.add_argument("--ground-min", type=float, default=-0.08)
    r.add_argument("--ground-max", type=float, default=0.08)
    r.add_argument("--obstacle-min", type=float, default=0.20)
    r.add_argument("--obstacle-max", type=float, default=1.80)
    r.add_argument("--min-ground-points", type=int, default=2)
    r.add_argument("--min-obstacle-points", type=int, default=1)
    r.add_argument("--occupied-thresh", type=float, default=0.65)
    r.add_argument("--free-thresh", type=float, default=0.25)
    r.set_defaults(func=rasterize)
    rt = sub.add_parser("raytrace")
    rt.add_argument("--pcd-input", required=True)
    rt.add_argument("--lidar-bag", required=True)
    rt.add_argument("--tf-bag", required=True)
    rt.add_argument("--output-dir", required=True)
    rt.add_argument("--lidar-topic", default="/livox/lidar")
    rt.add_argument("--resolution", type=float, required=True)
    rt.add_argument("--ground-min", type=float, default=-0.08)
    rt.add_argument("--ground-max", type=float, default=0.08)
    rt.add_argument("--obstacle-min", type=float, default=0.20)
    rt.add_argument("--obstacle-max", type=float, default=1.80)
    rt.add_argument("--min-ground-points", type=int, default=2)
    rt.add_argument("--min-obstacle-points", type=int, default=1)
    rt.add_argument("--min-free-rays", type=int, default=2)
    rt.add_argument("--add-observed-occupied-threshold", type=int, default=0)
    rt.add_argument("--frame-stride", type=int, default=2)
    rt.add_argument("--point-stride", type=int, default=10)
    rt.add_argument("--min-ray-range", type=float, default=0.5)
    rt.add_argument("--max-ray-range", type=float, default=15.0)
    rt.add_argument("--base-to-livox-x", type=float, default=0.285)
    rt.add_argument("--base-to-livox-y", type=float, default=0.0)
    rt.add_argument("--base-to-livox-z", type=float, default=0.267)
    rt.add_argument("--base-to-livox-roll", type=float, default=0.0)
    rt.add_argument("--base-to-livox-pitch", type=float, default=0.087266)
    rt.add_argument("--base-to-livox-yaw", type=float, default=0.0)
    rt.add_argument("--occupied-thresh", type=float, default=0.65)
    rt.add_argument("--free-thresh", type=float, default=0.25)
    rt.set_defaults(func=raytrace)
    ct = sub.add_parser("clean-trajectory")
    ct.add_argument("--pcd-input", required=True)
    ct.add_argument("--map-yaml", default="")
    ct.add_argument("--tf-bag", required=True)
    ct.add_argument("--output-dir", required=True)
    ct.add_argument("--resolution", type=float, required=True)
    ct.add_argument("--ground-min", type=float, default=-0.08)
    ct.add_argument("--ground-max", type=float, default=0.08)
    ct.add_argument("--obstacle-min", type=float, default=0.20)
    ct.add_argument("--obstacle-max", type=float, default=1.80)
    ct.add_argument("--min-ground-points", type=int, default=2)
    ct.add_argument("--min-obstacle-points", type=int, default=1)
    ct.add_argument("--pose-stride", type=int, default=10)
    ct.add_argument("--footprint-length", type=float, default=0.68)
    ct.add_argument("--footprint-width", type=float, default=0.50)
    ct.add_argument("--wall-risk-distance", type=float, default=0.45)
    ct.add_argument("--write-on-wall-risk", action="store_true")
    ct.add_argument("--occupied-thresh", type=float, default=0.65)
    ct.add_argument("--free-thresh", type=float, default=0.25)
    ct.set_defaults(func=clean_trajectory)
    args = parser.parse_args()
    args.func(args)


if __name__ == "__main__":
    main()
