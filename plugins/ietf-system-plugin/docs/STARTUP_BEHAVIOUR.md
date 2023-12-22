# IETF System Plugin Startup Behavior

This document describes the plugin behaviour on startup i.e. the behaviour of
the plugin when it starts after the system boots up. The plugin initialization
callback is divided into 3 steps: applying startup data, copying the startup
data to the running datastore and setting up plugin callbacks.

## Startup datastore

Any data which needs to be set (or applied) on plugin startup should be
contained in the startup datastore. This data will be directly read when the
plugin starts and the plugin will check it agains the data contained on the
system. If possible, the plugin will overwrite the system data and apply the
startup datastore configuration. Each plugin module contains several appliers
which are responsible for this activity. For example in the IETF System Plugin,
the DNS module contains a DNS Server List applier and a DNS Search List applier.
Each of them is responsible for applying the startup datastore configuration if
it is present during the plugin startup.

## Running datastore

Running datastore will contain the startup configuration which was applied
during the startup datastore applier calls. If a startup entry was unable to be
set on the system, that data will not be contained in the running datastore
since it doesn't match the current running configuration on the system. You can
try to apply the data again by using the change callbacks which the plugin
provides.

## Plugin callbacks

After the datastore configuration has been set up, callbacks will be subscribed
(change, oper get, RPR/action). You can then use these callbacks to edit,
retrieve data or both.
