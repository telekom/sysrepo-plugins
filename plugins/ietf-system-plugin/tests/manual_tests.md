<!--
SPDX-FileCopyrightText: 2024 Deutsche Telekom AG

SPDX-License-Identifier: CC0-1.0    
-->

# Manual testing

## Intro
This document contains a list of sysrepocfg commands that can be used to testand expected outputs
currently implemented plugin functionality.

It can also serve as a reference containing a list of currently implemented leafs in the model.

It is assumed that the datastore has already been initialized, and the data in examples imported.
To import the example data run the following command:
```
sysrepocfg --edit=examples/system.xml -m "ietf-system"
```

### ietf-system

First we can confirm that the datastore contains any data at all.

```
$ sysrepocfg -X -m ietf-system
sysrepocfg -X -m 'ietf-system'
<system xmlns="urn:ietf:params:xml:ns:yang:ietf-system">
  <contact>Mr. Admin</contact>
  <hostname>test.it</hostname>
  <clock>
    <timezone-name>Europe/Stockholm</timezone-name>
  </clock>
  <ntp>
    <enabled>true</enabled>
    <server>
      <name>hr.pool.ntp.org</name>
      <udp>
        <address>162.159.200.123</address>
      </udp>
    </server>
  </ntp>
</system>
```

#### Contact
``` 
$ sysrepocfg -X -x '/ietf-system:system/contact
<system xmlns="urn:ietf:params:xml:ns:yang:ietf-system">
  <contact>Mr. Admin</contact>
</system>
```

The contact information is retrieved from the `/etc/passwd` file, which we can confirm.
```
$ cat /etc/passwd
root:x:0:0:Mr. Admin:/root:/bin/bash
daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
bin:x:2:2:bin:/bin:/usr/sbin/nologin
sys:x:3:3:sys:/dev:/usr/sbin/nologin
sync:x:4:65534:sync:/bin:/bin/sync
```

We can change the contact field, which will store new contact information in the `/etc/passwd` file.

```
$ sysrepocfg -X -x '/ietf-system:system/contact'
<system xmlns="urn:ietf:params:xml:ns:yang:ietf-system">
  <contact>test contact</contact>
</system>

$ cat /etc/passwd
root:x:0:0:test contact:/root:/bin/bash
daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin
bin:x:2:2:bin:/bin:/usr/sbin/nologin
sys:x:3:3:sys:/dev:/usr/sbin/nologin
sync:x:4:65534:sync:/bin:/bin/sync
```

#### Hostname
We can retrieve the hostname:

```
$ sysrepocfg -X -x '/ietf-system:system/hostname'
<system xmlns="urn:ietf:params:xml:ns:yang:ietf-system">
  <hostname>test.it</hostname>
</system>
```

The hostname is set and retrieved using the `sethostname()` and `gethostname()` system calls.

We can verify that the hostname matches the system hostname:
```
hostnamectl
   Static hostname: c70d08e518bd
Transient hostname: test.it
         Icon name: computer-laptop
           Chassis: laptop
        Machine ID: d95430cef4c5dce339469c8c6011e470
           Boot ID: ac5d9f56dbde476aaec818a8016df0d7
  Operating System: Ubuntu 18.04.5 LTS
            Kernel: Linux 5.10.8
      Architecture: x86-64
```

The plugin also supports hostname editing. After setting it to `test2` with `sysrepocfg -Evim -fjson -m ietf-system`,
we can verify that the changes have been applied.

```
$ sysrepocfg -X -x '/ietf-system:system/hostname'
<system xmlns="urn:ietf:params:xml:ns:yang:ietf-system">
  <hostname>test2</hostname>
</system>
$ hostnamectl
   Static hostname: c70d08e518bd
Transient hostname: test2
         Icon name: computer-laptop
           Chassis: laptop
        Machine ID: d95430cef4c5dce339469c8c6011e470
           Boot ID: ac5d9f56dbde476aaec818a8016df0d7
  Operating System: Ubuntu 18.04.5 LTS
            Kernel: Linux 5.10.8
      Architecture: x86-64
```

#### Location
We can retrieve the location:

```
$ sysrepocfg -X -x '/ietf-system:system/location'
<system xmlns="urn:ietf:params:xml:ns:yang:ietf-system">
  <location>basement</location>
</system>
```

The location is set and retrieved from a file (`location_info`) located in a directory whos path is set via the `GEN_PLUGIN_DATA_DIR` environment variable.

After setting it to `3rd floor` with `sysrepocfg -Evim -fjson -m ietf-system`, we can verify the changes.
```
$ sysrepocfg -X -x '/ietf-system:system/location'
<system xmlns="urn:ietf:params:xml:ns:yang:ietf-system">
  <location>3rd floor</location>
</system
```

#### Timezone-name
If the timezone-name feature is enabled, we can retrieve and change the timezone-name.
The timezone data is retrieved and set by using the `/etc/localtime` symlink.

```
$ sysrepocfg -X -x '/ietf-system:system/clock/timezone-name'
<system xmlns="urn:ietf:params:xml:ns:yang:ietf-system">
  <clock>
    <timezone-name>Europe/Stockholm</timezone-name>
  </clock>
</system>

$ ls -al /etc/localtime
lrwxrwxrwx 1 root root 33 Mar 22 16:28 /etc/localtime -> /usr/share/zoneinfo/Europe/Stockholm
```

After setting it to `Europe/Zagreb` with `sysrepocfg -Evim -fjson -m ietf-system`, we can verify the changes.

```
$ sysrepocfg -X -x '/ietf-system:system/clock/timezone-name'
<system xmlns="urn:ietf:params:xml:ns:yang:ietf-system">
  <clock>
    <timezone-name>Europe/Zagreb</timezone-name>
  </clock>
</system>
$ ls -al /etc/localtime
lrwxrwxrwx 1 root root 33 Mar 22 16:28 /etc/localtime -> /usr/share/zoneinfo/Europe/Zagreb
```

#### NTP
If the ntp feature is enabled, we can retrieve and change the ntp node.
The NTP data is retrieved and set in /etc/ntp.conf and use of the ntpd NTP daemon is assumed.

```
sysrepocfg -X -x '/ietf-system:system/ntp'
<system xmlns="urn:ietf:params:xml:ns:yang:ietf-system">
  <ntp>
    <enabled>true</enabled>
    <server>
      <name>hr.pool.ntp.org</name>
      <udp>
        <address>162.159.200.123</address>
      </udp>
    </server>
  </ntp>
</system>
```

The enabled node can be set to true or false. Enabling or disabling it calls systemctl in the backgruond
and disables or enables ntpd.

The NTP config would then look something like this

```
# /etc/ntp.conf, configuration for ntpd; see ntp.conf(5) for help

driftfile /var/lib/ntp/ntp.drift

# Leap seconds definition provided by tzdata
leapfile /usr/share/zoneinfo/leap-seconds.list

# Enable this if you want statistics to be logged.
#statsdir /var/log/ntpstats/

statistics loopstats peerstats clockstats
filegen loopstats file loopstats type day enable
filegen peerstats file peerstats type day enable
filegen clockstats file clockstats type day enable

# Specify one or more NTP servers.

# Use servers from the NTP Pool Project. Approved by Ubuntu Technical Board
# on 2011-02-08 (LP: #104525). See http://www.pool.ntp.org/join.html for
# more information.

# Use Ubuntu's ntp server as a fallback.

# Access control configuration; see /usr/share/doc/ntp-doc/html/accopt.html for
# details.  The web page <http://support.ntp.org/bin/view/Support/AccessRestrictions>
# might also be helpful.
#
# Note that "restrict" applies to both servers and clients, so a configuration
# that might be intended to block requests from certain clients could also end
# up blocking replies from your own upstream servers.

# By default, exchange time with everybody, but don't allow configuration.
restrict -4 default kod notrap nomodify nopeer noquery limited
restrict -6 default kod notrap nomodify nopeer noquery limited

# Local users may interrogate the ntp server more closely.
restrict 127.0.0.1
restrict ::1

# Needed for adding pool entries
restrict source notrap nomodify noquery

# Clients from this (example!) subnet have unlimited access, but only if
# cryptographically authenticated.
#restrict 192.168.123.0 mask 255.255.255.0 notrust


# If you want to provide time to your local subnet, change the next line.
# (Again, the address is an example only.)
#broadcast 192.168.123.255

# If you want to listen to time broadcasts on your local subnet, de-comment the
# next lines.  Please do this only if you trust everybody on the network!
#disable auth
#broadcastclient
server 162.159.200.123 
```

We can rename the server:
```
sysrepocfg -E vim -f json -m ietf-system
```

After which the name should change:

```
sysrepocfg -X -x '/ietf-system:system/ntp'
<system xmlns="urn:ietf:params:xml:ns:yang:ietf-system">
  <ntp>
    <enabled>true</enabled>
    <server>
      <name>hr.pool2.ntp.org</name>
      <udp>
        <address>162.159.200.123</address>
      </udp>
    </server>
  </ntp>
</system>
```

As the server is renamed, the plugin adds a new server entry to `/etc/ntp.conf`.
The names are not seen in the config file but are tracked internally by the plugin.

We can also change the IP:

```
sysrepocfg -X -x '/ietf-system:system/ntp'
<system xmlns="urn:ietf:params:xml:ns:yang:ietf-system">
  <ntp>
    <enabled>true</enabled>
    <server>
      <name>hr.pool2.ntp.org</name>
      <udp>
        <address>162.159.200.124</address>
      </udp>
    </server>
  </ntp>
</system>
```

After those two changes, the end of `/etc/ntp.conf` looks something like this:

```
# If you want to listen to time broadcasts on your local subnet, de-comment the
# next lines.  Please do this only if you trust everybody on the network!
#disable auth
#broadcastclient
    
server 162.159.200.123   
    
server 162.159.200.124   
```

Furthermore, various settings for the server nodes can be adjusted.

We can set the association type:
```
sysrepocfg -Evim -f json -m ietf-system

sysrepocfg -X -x '/ietf-system:system/ntp'
<system xmlns="urn:ietf:params:xml:ns:yang:ietf-system">
  <ntp>
    <enabled>true</enabled>
    <server>
      <name>hr.pool2.ntp.org</name>
      <udp>
        <address>162.159.200.124</address>
      </udp>
      <association-type>pool</association-type>
    </server>
  </ntp>
</system>
```

After that the association type will be changed in `ntp.conf` with the end looking something like this:
```
server 162.159.200.123   
    
pool 162.159.200.124
```

The association type can also be changed to peer, with the default being server.

iburst and prefer options can also be set:
```
sysrepocfg -Evim -f json -m ietf-system

sysrepocfg -X -x '/ietf-system:system/ntp'
<system xmlns="urn:ietf:params:xml:ns:yang:ietf-system">
  <ntp>
    <enabled>true</enabled>
    <server>
      <name>hr.pool2.ntp.org</name>
      <udp>
        <address>162.159.200.124</address>
      </udp>
      <association-type>pool</association-type>
      <iburst>true</iburst>
      <prefer>true</prefer>
    </server>
  </ntp>
</system>
```

The default values for both nodes are false.

The changes are again reflected in `/etc/ntp.conf`

```
server 162.159.200.123   
    
pool 162.159.200.124  iburst prefer
```

#### Local User Authentication

If the `authentication` and `local-users` features are enabled, we can retrieve and change the authentication node for local users.
The username is retrieved from `/etc/passwd` file, the encrypted password is retrieved from `/etc/shadow` and the ssh public key file data is retrieved from the `.ssh` directory inside the users home directory.

The plugin will populate the datastores at startup. We can check the current configuration with sysrepocfg as follows:
```
sysrepocfg -X -x '/ietf-system:system/authentication'

<system xmlns="urn:ietf:params:xml:ns:yang:ietf-system">
  <authentication>
    <user>
      <name>root</name>
      <password>$6$neE50F20wOMVP$7glM2pJ.d9sIe9fvuSd89N9djsh.95j9fKjfdsN34j89dfO84jf/Sf/</password>
    </user>
    <user>
      <name>user123</name>
      <password>$6$0/AkfjsdI$F9jfd3Ask9dVv9sOm2Neih/dvjCyCvVGbgOQbOMrd/</password>
      <authorized-key>
        <name>id_ed25519.pub</name>
        <algorithm>ssh-ed25519</algorithm>
        <key-data>AAAAC3NzaC1lZDI1NTE5AAAAIOvyVRtYrJWW7gThF7czOtaTOE85cHrkW9kMcGQnafmA</key-data>
      </authorized-key>
      <authorized-key>
        <name>id_rsa.pub</name>
        <algorithm>ssh-rsa</algorithm>
        <key-data>AAAAB3NzaC1yc2EAAAADAQABAAABA8SH6Wu0p6v3D/yeLEtlSOfqVYWIr2oT96AMGHbhiThVqFJxi+M7uS/vfJMwNz2z9s1MiYvVQ9RSEYP/hI7JBK488GeXY7HIvC6c6RO3q3DGY+HSToTqMdPUwTDjb5EkWCApvI4Rvx+joC3KwN6HdU09GCa9aekK/bY3yV5pFvWtr6EoB4Mj/dQYmwwhI9/K3KyN2gZSg77CsyZ/XstovL</key-data>
      </authorized-key>
    </user>
  </authentication>
</system>
```

In the example configuration above two users exist on the system: `root` and `user123`.
The `root` user doesn't have any ssh public keys set up, and `user123` has two: `id_ed25519.pub` and `id_rsa.pub`.

We can add a new user named `test_user`, set his password and public ssh key info:

```
sysrepocfg -Evim -fjson -m ietf-system

<system xmlns="urn:ietf:params:xml:ns:yang:ietf-system">
    <authentication>
        <user>
            <name>test_user</name>
            <password>$6$S05zV2Np5LQzaOpM$qqUxvFsEVg7iwaqnEHhF4ZJv8dwXdtgFpLTHyr78Rr8cz/ml2riPyBlPol.3V8qVXFohR0XSTJXMHO4XLjrXd1</password>
            <authorized-key>
                <name>test_rsa.pub</name>
                <algorithm>ssh-rsa</algorithm>
                <key-data>AAAAB3NzaC1yc2EAAAADAQABAAABAQCiIf32L0B77f//ldk1QpUyfaJQUgI4mXSPtkmaokxUUlj8j9pxlwpFDSmsrZn2H0DJhZZ3ktAGsbFJabZJhV73l7HhQggC/6uzrNPSe+R3lOMGYIAhHaWbGSnT/uvpPMBVA/nWulDkBphiXv606WQHDxqGkngF1kzvvpd5FPpc/jy2vv+66HaP6XA9MgzHLYTOTb3ct3dVoz7HDAQ8tC5l3/3YYLyMhc3LxOBQLZ9PklWvQeSyO6neKi3Au0T13SpUGjtuqKpiCvE/X0ZuFtZSZzPo5UDASD65Er8jOqqYDcfHR1hsfJJjJA/nP+VKoGeBzUBxhxNetqswnEcPDEBv</key-data>
            </authorized-key>
        </user>
    </authentication>
</system>
```
We can check if the user has been successfully added to the system by trying to login in as the new user or by inspecting the passwd and shadow files, the home directory and the contents of .ssh directory:


```
cat /etc/passwd

[...]
test_user:x:1001:1001::/home/test_user:/bin/bash
```

```
cat /etc/shadow

[...]
test_user:$6$S05zV2Np5LQzaOpM$qqUxvFsEVg7iwaqnEHhF4ZJv8dwXdtgFpLTHyr78Rr8cz/ml2riPyBlPol.3V8qVXFohR0XSTJXMHO4XLjrXd1::0:99999:7:::0
```

```
ls -la /home/

[...]
drwx------  3 test_user      1001 4096 Jun 14 17:51 test_use
```

```
cat /home/test_user/.ssh/test_rsa.pub

ssh-rsa
AAAAB3NzaC1yc2EAAAADAQABAAABAQCiIf32L0B77f//ldk1QpUyfaJQUgI4mXSPtkmaokxUUlj8j9pxlwpFDSmsrZn2H0DJhZZ3ktAGsbFJabZJhV73l7HhQggC/6uzrNPSe+R3lOMGYIAhHaWbGSnT/uvpPMBVA/nWulDkBphiXv606WQHDxqGkngF1kzvvpd5FPpc/jy2vv+66HaP6XA9MgzHLYTOTb3ct3dVoz7HDAQ8tC5l3/3YYLyMhc3LxOBQLZ9PklWvQeSyO6neKi3Au0T13SpUGjtuqKpiCvE/X0ZuFtZSZzPo5UDASD65Er8jOqqYDcfHR1hsfJJjJA/nP+VKoGeBzUBxhxNetqswnEcPDEBv
```

Deletion of any node is also supported.
