# Chapter 8 Using the Docker API

- [Chapter 8 Using the Docker API](#chapter-8-using-the-docker-api)
  - [The Docker APIs](#the-docker-apis)
  - [First steps with the Engine API](#first-steps-with-the-engine-api)
  - [Testing the Docker Engine API](#testing-the-docker-engine-api)
    - [Managing images with the API](#managing-images-with-the-api)
    - [Managing containers with the API](#managing-containers-with-the-api)

## The Docker APIs

Three specific APIs in the Docker ecosystem:

- The [Registry API](https://docs.docker.com/registry/): privides integration
  with the Docker registry.
- The Docker Hub API: provides integration with the Docker Hub
- The [Docker Engine API](https://docs.docker.com/engine/api/): provides
  integration with the Docker daemon.

All APIs are RESTful.

## First steps with the Engine API

By default, the Docker daemon binds to a socket, `unix:///var/run/docker.sock`.
The daemon runs with `root` privileges so as to have the access needed to manage
the appropriate resources. If a group named `docker` exists on your system,
Docker will apply ownership of the socket to that group. Hence, any user that
belongs to the `docker` group can run Docker without needing `root` privileges.

⚠️ Although the `docker` group makes life easier, it is still a security
exposure. The `docker` group is `root`-equivalent and should be limited to those
users and applications that absolutely need it.

This works fine if we're querying the API from the same host running Docker, but
if we want remote access to the API, we need to bind the Docker daemon to a
network interface. This is done by passing or adjusting the `-H` flag to the
Docker daemon.

Use the Docker API locally:

```sh
curl --unix-socket /var/run/docker.sock http://docker/info 
```

Bind the Docker daemon to a network interface by editing the daemon's startup
configuration files:

- For Ubuntu or Debian
  - Older releases: `/etc/default/docker`
  - Releases with upstart: `/etc/init/docker.conf`
  - Systemd releases: `/lib/systemd/system/docker.service`
- For Red Hat, Fedora and related: `/etc/sysconfig/docker`
  - Systemd releases: `/usr/lib/systemd/system/docker.service`

Bind the Docker daemon to a network interface on a Red Hat derivative running
systemd: `/usr/lib/systemd/system/docker.service`

Change

```service
ExecStart=/usr/bin/dockerd --selinux-enabled
```

to

```service
# not safe for now, better to enable auth
ExecStart=/usr/bin/dockerd --selinux-enabled -H tcp://0.0.0.0:2375
```

```sh
# Connect to the Docker daemon from a remote host
docker -H docker.example.com:2375 info

# Docker also uses the DOCKER_HOST env var
export DOCKER_HOST="tcp://docker.example.com:2375"
```

## Testing the Docker Engine API

```sh
curl http://docker/example.com:2375/info | python -mjson.tool
```

### Managing images with the API

```sh
curl http://docker/example.com:2375/images/json | python -mjson.tool

# local
curl --unix-socket /var/run/docker.sock http://docker/images/json | python -mjson.tool

curl --unix-socket /var/run/docker.sock http://docker/images/431bd73d5c59098602a2fecd84c4bcddc90b4b15676a4a68e3cb42a0924f3e5f/json | python -mjson.tool

# search for images on the Docker Hub
curl --unix-socket /var/run/docker.sock "http://docker/images/search?term=octobug/" | python -mjson.tool
```

### Managing containers with the API
