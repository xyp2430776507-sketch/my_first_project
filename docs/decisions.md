# Decisions

- Keep generated build/runtime artifacts out of version control.
- Use small, targeted edits for repo documentation and workspace hygiene.

## Decision: Keep Lightning native map and add horizontal map externally

Date: 2026-08-20

### Context

The real MID360 is mechanically mounted about 5 degrees away from the horizontal chassis frame.

Lightning-LM generated a 3D map that is internally consistent but globally tilted. Ground plane fitting measured:

```text
total tilt ~= 4.95 deg
pitch ~= 4.85 deg
roll ~= 1.00 deg
```

### Decision

Do not modify:

```text
LiDAR-IMU extrinsic_R
Lightning LIO internals
Lightning IMU initialization
stored 3D map
```

Keep Lightning native frame as:

```text
lightning_map
```

Create a separate horizontal frame:

```text
map
```

and connect it with an external fixed transform:

```text
map -> lightning_map
```

### Reason

This separates SLAM/localization internal coordinates, robot mechanical mounting, and navigation world coordinates while minimizing changes to upstream Lightning-LM.

### Validation

Horizontal correction reduced flat-ground robot trajectory z variation from about `1.215 m` to about `0.145 m`.

## Decision: Use wrapper instead of changing Lightning localization output

Date: 2026-08-20

### Problem

Lightning publishes:

```text
map -> base_link
```

while chassis odometry publishes:

```text
odom -> base_link
```

This gives `base_link` two TF parents.

### Decision

Remap Lightning `/tf` to:

```text
/lightning_tf
```

and keep its native transform only as intermediate input. Use an external wrapper to compute and publish:

```text
lightning_map -> odom
```

### Final TF

```text
map -> lightning_map -> odom -> base_link
```

### Reason

The wrapper avoids modifying localization algorithms, avoids TF conflicts, preserves upstream Lightning-LM behavior, and matches the standard ROS 2 / Nav2 TF model.
