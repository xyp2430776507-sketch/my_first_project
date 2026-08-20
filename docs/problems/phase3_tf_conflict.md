# Lightning / Chassis TF Parent Conflict

## Symptom

Lightning native online localization publishes:

```text
map -> base_link
```

The chassis or recorded bag also publishes:

```text
odom -> base_link
```

When both are in `/tf`, TF can report disconnected trees or invalid frame relationships because `base_link` has two parents.

## Cause

ROS TF expects one parent per child frame in a valid tree. `base_link` cannot be directly parented by both `map` and `odom`.

## Investigation

Confirmed inputs:

```text
/lightning_tf: map -> base_link
/tf:           odom -> base_link
```

Confirmed that Lightning localization itself was running and publishing native map-based pose. The issue was the TF tree shape, not failed localization.

Also found that `run_loc_online` originally rejected ROS 2 remap arguments such as:

```text
--ros-args -r /tf:=/lightning_tf
```

because of gflags argument parsing.

## Solution

Do not publish Lightning native localization TF directly into the main `/tf` tree.

Remap Lightning `/tf` to:

```text
/lightning_tf
```

Use the wrapper `lightning_map_to_odom_tf.py` to compute:

```text
T_lightning_map_odom = T_lightning_map_base * inverse(T_odom_base)
```

and publish:

```text
lightning_map -> odom
```

Final chain:

```text
lightning_map -> odom -> base_link
```

After Phase 3D horizontalization:

```text
map -> lightning_map -> odom -> base_link
```

## Validation Result

Full-bag TF recording confirmed:

```text
/lightning_tf map->base_link count: 44707
/tf lightning_map->odom count:     44707
/tf odom->base_link count:          7457
```

`tf2_echo lightning_map odom` and `tf2_echo map base_link` both produced continuous transforms during replay.

Integrated launch validation also passed using:

```bash
ros2 launch xyp_mid360_navigation lightning_localization_tf.launch.py
```

Recorded result:

```text
/lightning_tf map->base_link count: 45088
/tf lightning_map->odom count:     45088
/tf odom->base_link count:          7534
/tf_static map->lightning_map:      1
final chain z_range span:           ~0.134 m
```

## Remaining Work

No remaining work for this TF conflict. Phase 4 Nav2 map and navigation integration is separate.
