<!--
telekom / sysrepo-plugins

This program is made available under the terms of the
BSD 3-Clause license which is available at
https://opensource.org/licenses/BSD-3-Clause

SPDX-FileCopyrightText: 2026 Deutsche Telekom AG
SPDX-FileContributor: Sartura d.d.

SPDX-License-Identifier: BSD-3-Clause
-->

# Tools

## notif-listener

A minimal sysrepo notification subscriber that prints YANG notifications to stdout in real-time.

### Building

```bash
gcc -o notif-listener notif-listener.c -lsysrepo
```

### Usage

```bash
# Listen to os-metrics notifications (default)
sudo ./notif-listener

# Listen to a specific module
sudo ./notif-listener <module-name>
```

The tool subscribes to all notifications from the specified module and prints each notification with a timestamp, type, xpath, and all values. Press Ctrl+C to stop.

### Example output

```
Subscribing to notifications from module "os-metrics"...
Listening... (Ctrl+C to stop)
[1712500000.000000000] Notification (realtime): /os-metrics:memory-threshold-crossed
  /os-metrics:memory-threshold-crossed/name = high-memory
  /os-metrics:memory-threshold-crossed/usage = 42.50
  /os-metrics:memory-threshold-crossed/rising = (empty)
```
