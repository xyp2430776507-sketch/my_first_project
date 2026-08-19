#!/usr/bin/env python3
"""Generate report figures from tf2_echo localization logs."""

import argparse
import math
import re
from pathlib import Path

import matplotlib.pyplot as plt
import numpy as np


TIME_RE = re.compile(r"^At time ([0-9.]+)")
XYZ_RE = re.compile(
    r"^- Translation: \[([-+0-9.eE]+), ([-+0-9.eE]+), ([-+0-9.eE]+)\]"
)
RPY_RE = re.compile(
    r"^- Rotation: in RPY \(degree\) \[([-+0-9.eE]+), ([-+0-9.eE]+), ([-+0-9.eE]+)\]"
)


def read_tf_log(path: Path):
    records = []
    stamp = None
    xyz = None
    for line in path.read_text(encoding="utf-8", errors="replace").splitlines():
        match = TIME_RE.match(line)
        if match:
            stamp = float(match.group(1))
            xyz = None
            continue
        match = XYZ_RE.match(line)
        if match and stamp is not None:
            xyz = tuple(float(v) for v in match.groups())
            continue
        match = RPY_RE.match(line)
        if match and stamp is not None and xyz is not None:
            rpy = tuple(float(v) for v in match.groups())
            if not records or stamp > records[-1][0]:
                records.append((stamp, *xyz, *rpy))
    if not records:
        raise RuntimeError(f"No complete TF records found in {path}")
    return np.asarray(records, dtype=float)


def setup_style():
    plt.rcParams.update(
        {
            "font.family": "sans-serif",
            "font.sans-serif": ["Noto Sans CJK JP", "Droid Sans Fallback", "DejaVu Sans"],
            "axes.unicode_minus": False,
            "axes.grid": True,
            "grid.alpha": 0.28,
            "figure.dpi": 130,
            "savefig.dpi": 220,
        }
    )


def static_figure(records, output: Path):
    stable = records[records[:, 0] >= records[0, 0] + 10.0]
    time_s = stable[:, 0] - stable[0, 0]
    x_cm = (stable[:, 1] - stable[0, 1]) * 100.0
    y_cm = (stable[:, 2] - stable[0, 2]) * 100.0
    yaw_deg = np.rad2deg(np.unwrap(np.deg2rad(stable[:, 6])))
    yaw_deg -= yaw_deg[0]

    fig, axes = plt.subplots(2, 1, figsize=(9.2, 6.6), sharex=True)
    axes[0].plot(time_s, x_cm, linewidth=1.7, label="X方向变化")
    axes[0].plot(time_s, y_cm, linewidth=1.7, label="Y方向变化")
    axes[0].axhline(0.0, color="black", linewidth=0.7)
    axes[0].set_ylabel("相对位移（cm）")
    axes[0].legend(loc="best")
    axes[0].set_title("静止状态下X、Y位置及航向变化")

    axes[1].plot(time_s, yaw_deg, color="#d55e00", linewidth=1.7, label="航向角变化")
    axes[1].axhline(0.0, color="black", linewidth=0.7)
    axes[1].set_xlabel("时间（s，已去除前10 s初始化阶段）")
    axes[1].set_ylabel("相对航向角（°）")
    axes[1].legend(loc="best")

    xy_span = math.hypot(np.ptp(stable[:, 1]), np.ptp(stable[:, 2])) * 100.0
    yaw_span = np.ptp(yaw_deg)
    fig.text(
        0.5,
        0.012,
        f"有效时长：{time_s[-1]:.1f} s    XY包络范围：{xy_span:.2f} cm    航向波动：{yaw_span:.3f}°",
        ha="center",
        fontsize=9.5,
    )
    fig.tight_layout(rect=(0, 0.045, 1, 1))
    fig.savefig(output, bbox_inches="tight")
    plt.close(fig)


def dynamic_figure(records, output: Path):
    x = records[:, 1]
    y = records[:, 2]
    closure_cm = math.hypot(x[-1] - x[0], y[-1] - y[0]) * 100.0

    fig, ax = plt.subplots(figsize=(8.2, 8.2))
    elapsed = records[:, 0] - records[0, 0]
    scatter = ax.scatter(x, y, c=elapsed, cmap="viridis", s=13, zorder=2)
    ax.plot(x, y, color="#3b6fb6", linewidth=1.1, alpha=0.65, zorder=1)
    ax.scatter(x[0], y[0], s=110, marker="o", color="#009e73", edgecolor="white", label="起点", zorder=4)
    ax.scatter(x[-1], y[-1], s=125, marker="X", color="#d55e00", edgecolor="white", label="终点", zorder=4)
    ax.plot([x[0], x[-1]], [y[0], y[-1]], linestyle="--", color="#d55e00", linewidth=1.2)
    ax.annotate(
        f"闭合误差 {closure_cm:.2f} cm",
        xy=(x[-1], y[-1]),
        xytext=(18, 20),
        textcoords="offset points",
        arrowprops={"arrowstyle": "->", "color": "#d55e00"},
        fontsize=10,
    )
    ax.set_title("动态回环定位轨迹及起终点位置")
    ax.set_xlabel("X（m）")
    ax.set_ylabel("Y（m）")
    ax.set_aspect("equal", adjustable="datalim")
    ax.legend(loc="best")
    colorbar = fig.colorbar(scatter, ax=ax, pad=0.02)
    colorbar.set_label("测试时间（s）")
    fig.tight_layout()
    fig.savefig(output, bbox_inches="tight")
    plt.close(fig)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--static-log", type=Path, required=True)
    parser.add_argument("--dynamic-log", type=Path, required=True)
    parser.add_argument("--output-dir", type=Path, required=True)
    args = parser.parse_args()

    args.output_dir.mkdir(parents=True, exist_ok=True)
    setup_style()
    static_figure(read_tf_log(args.static_log), args.output_dir / "figure-2-1-static-stability.png")
    dynamic_figure(read_tf_log(args.dynamic_log), args.output_dir / "figure-2-2-dynamic-loop.png")


if __name__ == "__main__":
    main()
