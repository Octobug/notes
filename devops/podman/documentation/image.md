# Podman Image

> <https://github.com/containers/image/tree/main/docs>

## `containers-registries.conf`

> <https://github.com/containers/image/blob/main/docs/containers-registries.conf.5.md>

### Location

- `$HOME/.config/containers/registries.conf`
- `/etc/containers/registries.conf`

### Sample

```conf
# Note that changing the order here may break tests.
unqualified-search-registries = ['docker.io', 'quay.io', 'registry.fedoraproject.org']

[[registry]]
# In Nov. 2020, Docker rate-limits image pulling.  To avoid hitting these
# limits while testing, always use the google mirror for qualified and
# unqualified `docker.io` images.
# Ref: https://cloud.google.com/container-registry/docs/pulling-cached-images
prefix="docker.io"
location="hub-mirror.c.163.com"

# 2020-10-27 a number of images are not present in gcr.io, and podman
# barfs spectacularly when trying to fetch them. We've hand-copied
# those to quay, using skopeo copy --all ...
[[registry]]
prefix="docker.io/library"
location="quay.io/libpod"
```
