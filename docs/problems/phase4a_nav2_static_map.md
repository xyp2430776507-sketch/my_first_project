# Phase 4A Nav2 Static Map Problems

本文记录 Phase 4A 中生成 Nav2 静态地图时确认过的关键问题。最终 Phase 4A 输出：

```text
/home/kepler/lightning_lm_ws/runs/real_mid360/phase4a-final-20260820-132916/map.yaml
```

## 1. Lightning g2p5 输出坐标不是水平 map

### 现象

Lightning-LM 内部有 g2p5 相关功能，但直接启用 `system.with_g2p5: true` 不能保证输出地图属于 Phase 3D 建立的水平 `map` frame。

### 原因

g2p5 使用 Lightning 内部 SLAM keyframe / point cloud 坐标，也就是原始倾斜的 `lightning_map`。Phase 3D 的

```text
map -> lightning_map
```

是外部 TF correction，不会回写 Lightning 内部 keyframe pose。

### 解决方案

不修改 Lightning-LM 核心，不直接启用 g2p5 生成最终 Nav2 map。改为独立路线：

```text
global.pcd
  -> apply verified map -> lightning_map rotation
  -> global_horizontal.pcd in map frame
  -> independent rasterization
  -> map.pgm / map.yaml
```

### 验证结果

水平化前：

```text
ground normal = [-0.084220, 0.017458, 0.996294]
ground tilt   = 4.9342 deg
ground RMSE   = 0.02016 m
```

水平化后：

```text
ground normal = [0.000185, 0.000113, 1.000000]
ground tilt   = 0.0124 deg
ground RMSE   = 0.02055 m
```

反向旋转会得到约 `9.8991 deg` tilt，因此方向确认不能取反。

## 2. global.pcd 缺少 free-space evidence

### 现象

第一版静态栅格可以被 `map_server` 加载，RViz 中方向、尺寸和 origin 没有明显异常，但 free 区域过少：

```text
occupied = 11370 = 3.433%
free     = 1458  = 0.440%
unknown  = 318332 = 96.126%
```

### 原因

最终 `global.pcd` 只记录哪里有点，不能完整说明 LiDAR 射线经过哪些空间。因此不能把“没有点”的 cell 直接当成 free。

### 解决方案

使用原始 MID360 bag 和 Phase 3E TF bag 做 2D ray tracing：

```text
T_map_lidar(t)
=
T_map_lightning_map
*
T_lightning_map_odom(t)
*
T_odom_base_link(t)
*
T_base_link_livox
```

关键参数：

```text
base_link -> livox_frame:
x=0.285, y=0.0, z=0.267
roll=0, pitch=0.087266, yaw=0

frame_stride = 2
point_stride = 100
max_ray_range = 12.0 m
min_free_rays = 2
add_observed_occupied_threshold = 0
```

注意：`mid360_real.yaml` 中的 `extrinsic_T` / `extrinsic_R` 是 Lightning 的 LiDAR-IMU 外参，不是机器人 `base_link -> lidar` 安装外参。

### 验证结果

时间范围重叠正常：

```text
lidar:
[1786701746131356159, 1786701971930530239]

lightning_map -> odom:
[1786701746597359418, 1786701972220920801]

odom -> base_link:
[1786701746203926598, 1786701972196730008]
```

Ray tracing 后：

```text
occupied = 11370 = 3.433%
free     = 22125 = 6.681%
unknown  = 297665 = 89.886%
ray_added_free_cells = 20667
```

普通 ray tracing 不清除已有 static occupied。

## 3. 机器人自身轨迹形成 occupied artifacts

### 现象

RViz 中出现沿机器人真实运动轨迹的黑色锯齿状 / 虚线状 occupied cells。人工确认这些不是环境固定障碍。

### 原因

这些 occupied 在 ray tracing 前后数量不变：

```text
before ray tracing occupied = 11370
after ray tracing occupied  = 11370
```

因此 artifact 来自 `global_horizontal.pcd -> static occupancy rasterization`，不是 ray tracing 新增。可能是机器人自身结构或运动过程中的点进入了静态点云。

### 解决方案

利用 Phase 3E TF bag 得到水平 `map` 中的 `base_link` 轨迹。机器人真实通过过的 footprint 区域可视作强 observed-free evidence。

不用完整底盘尺寸 `0.78 x 0.60 m`，而使用内缩 footprint：

```text
footprint_length = 0.68 m
footprint_width  = 0.50 m
pose_stride      = 10
```

只允许 trajectory footprint 清除 occupied，不允许普通 LiDAR ray 穿过 static occupied 后清墙。

### 验证结果

```text
trajectory_poses:       4508
swept_footprint_cells:  3547
removed_occupied_cells: 1347

removed distance mean: 0.1542 m
removed distance p50:  0.1716 m
removed distance p95:  0.2677 m
removed distance max:  0.3438 m
wall_risk_detected:    False
```

RViz 人工确认：

- 原轨迹锯齿基本消失；
- 外墙、房间边界和主要固定障碍仍保留；
- 未见 trajectory footprint 大面积切穿真实墙体。

## 4. PGM unknown pixel 被 map_server 误判为 free

### 现象

最终 connectivity check 发现，内部统计显示约 `89.879%` unknown，但按 `map.yaml` 阈值解释 PGM 后，unknown 实际变成 `0`。

### 原因

当时配置：

```text
negate = 0
free_thresh = 0.25
occupied_thresh = 0.65
```

旧 PGM 像素：

```text
occupied = 0
free     = 254
unknown  = 205
```

对于 `negate=0`：

```text
occupancy(205) = (255 - 205) / 255 = 0.196
```

`0.196 < free_thresh 0.25`，所以 `pixel 205` 会被 `map_server` 解释成 free，而不是 unknown。

### 解决方案

统一 PGM 像素：

```text
OCCUPIED_PIXEL = 0
FREE_PIXEL     = 254
UNKNOWN_PIXEL  = 128
```

并在写出 PGM 前根据 `negate`、`free_thresh`、`occupied_thresh` 自动验证三种像素的最终语义。如果不满足 expected semantic，直接报错，不允许写出地图。

### 验证结果

最终像素统计：

```text
pixel 0   count = 10023  -> occupied
pixel 254 count = 23494  -> free
pixel 128 count = 297643 -> unknown
```

按 `map.yaml` 阈值解释后：

```text
occupied = 10023
free     = 23494
unknown  = 297643
```

最终 free 连通性：

```text
free component count:       166
largest free component:     23256 cells
largest / total free:       98.987%
largest component area:     232.56 m^2

trajectory samples:         754
trajectory free:            752
trajectory occupied:        0
trajectory unknown:         0
trajectory out_of_grid:     0
trajectory in largest comp: 752 / 752 = 100%
```

## Phase 4A 最终结论

Phase 4A 通过。最终地图：

```text
/home/kepler/lightning_lm_ws/runs/real_mid360/phase4a-final-20260820-132916/map.yaml
```

Phase 4B 才开始验证 Nav2 对该地图和现有 TF 链的使用；Phase 4A 不启动 planner/controller，也不发布 `/cmd_vel`。
