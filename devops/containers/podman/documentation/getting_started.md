# Getting Started with Podman

> <https://podman.io/getting-started/>

- [Getting Started with Podman](#getting-started-with-podman)
  - [Podman Installation Instructions](#podman-installation-instructions)
  - [Sync datetime of VM](#sync-datetime-of-vm)

## Podman Installation Instructions

```sh
# macOS
brew install podman

# podman machine
podman machine init
podman machine start
```

## Sync datetime of VM

```sh
podman machine ssh sudo date --set $(date +'%Y-%m-%dT%H:%M:%S')
```
