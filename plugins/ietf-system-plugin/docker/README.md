# build
As the plugin is currently not open source, we need to clone from a private git server.

To do that, docker buildkit is required, and a private SSH key
with access to the plugin repo needs to be passed at build time.

```
$ export DOCKER_BUILDKIT=1
$ docker build --progress=plain --secret id=sshkey,src=/home/user/.ssh/id_ed25519 -t sysrepo/system-plugin -f Dockerfile .
```

# run
Since the plugin depends on systemd, we need to run the container with `CAP_SYS_ADMIN` privileges and mount the
cgroups FS within the container.

```
docker run -ti -v /sys/fs/cgroup:/sys/fs/cgroup:ro --cap-add SYS_ADMIN --cap-add SYS_TIME --name system-plugin sysrepo/system-plugin /sbin/init
```


