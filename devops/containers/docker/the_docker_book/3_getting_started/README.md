# Chapter 3 Getting Started with Docker

- [Chapter 3 Getting Started with Docker](#chapter-3-getting-started-with-docker)
  - [Running our first container](#running-our-first-container)
  - [Working with our first container](#working-with-our-first-container)
  - [Container naming](#container-naming)
  - [Starting a stopped container](#starting-a-stopped-container)
  - [Attaching to a container](#attaching-to-a-container)
  - [Creating daemonized containers](#creating-daemonized-containers)
  - [Seeing what's happening inside our container](#seeing-whats-happening-inside-our-container)
  - [Docker log drivers](#docker-log-drivers)
  - [Inspecting the container's processes](#inspecting-the-containers-processes)
  - [Docker statistics](#docker-statistics)
  - [Running a process inside an already running container](#running-a-process-inside-an-already-running-container)
  - [Stopping a daemonized container](#stopping-a-daemonized-container)
  - [Automatic container restarts](#automatic-container-restarts)
  - [Finding out more about our container](#finding-out-more-about-our-container)
  - [Deleting a container](#deleting-a-container)

## Running our first container

```sh
sudo docker run -i -t ubuntu /bin/bash
```

- `-i`: keeps `STDIN` open from the container
- `-t`: assign a pseudo-tty to the container

The `docker run` process:

1. Docker checked locally for the `ubuntu` image.
2. If it can't find the image on the local Docker host, it will reach out to the
   registry. Once it had found the image, it downloaded the image and stored it
   on the local host.
3. Docker then used the image to create a new container inside a filesystem.

   The container has a network, IP address, and a bridge interface to talk to
   the local host.

4. Docker run the specified command in the new container.

## Working with our first container

```sh
$ root@becbc1dbb3a7:/# hostname
becbc1dbb3a7

$ root@becbc1dbb3a7:/# cat /etc/hosts
127.0.0.1       localhost localhost.localdomain localhost4 localhost4.localdomain4
::1     localhost localhost.localdomain localhost6 localhost6.localdomain6
10.88.0.4       becbc1dbb3a7 distracted_gould

$ root@becbc1dbb3a7:/# hostname -I
10.88.0.4

$ root@becbc1dbb3a7:/# ps -aux
USER         PID %CPU %MEM    VSZ   RSS TTY      STAT START   TIME COMMAND
root           1  0.0  0.1   4624  3740 pts/0    Ss   13:15   0:00 /bin/bash
root           7  0.0  0.0   7060  1548 pts/0    R+   13:18   0:00 ps -aux

$ apt-get update; apt-get install vim
```

List containers:

```sh
# list containers
docker ps
```

📝 There are three ways containers can be identified:

- a short UUID (like `b8f66f20da1a`)
- a longer UUID (like
  `b8f66f20da1a78d581db0cb7b9633bba660bda79b7b498e72c65a0ca10c46860`,
  `--no-trunc`)
- a name (like `gray_cat`)

## Container naming

Names are unique.

```sh
docker run --name bob_the_container -i -t ubuntu /bin/bash
```

## Starting a stopped container

```sh
docker start bob_the_container
```

📝 In a similar vein there is also the `docker create` command which creates a
container but does not run it. This allows you more granular control over your
container workflow.

The container will restart with the same options we'd specified when we launched
it with the `docker run` command.

## Attaching to a container

```sh
docker attach bob_the_container
```

## Creating daemonized containers

```sh
docker run --name daemon_dave -d ubuntu /bin/sh -c \
  "while true; do echo hello world; sleep 1; done"
```

## Seeing what's happening inside our container

```sh
# Fetching the logs of our daemonized container
docker logs daemon_dave

# Tailing the logs of our daemonized container
docker logs -f daemon_dave

# Tailing part of the logs
docker logs --tail 10 daemon_dave

# Following the logs of a container without having to read the whole log file
docker logs --tail 0 -f daemon_dave

# Tailing the logs with timestamp
docker logs -ft daemon_dave
```

## Docker log drivers

```sh
# Enabling Syslog at the container level
# - json-file (default)
# - syslog
# - none
docker run --log-driver="syslog" --name daemon_dwayne -d \
  ubuntu /bin/sh -c "while true; do echo hello world; sleep 1; done"
```

## Inspecting the container's processes

```sh
docker top daemon_dave
```

## Docker statistics

```sh
docker stats daemon_dave daemon_dwayen
```

## Running a process inside an already running container

We can run additional processes inside our containers using the `docker exec`
command.

```sh
docker exec -d daemon_dave touch /etc/new_config_file

# Running an interactive command inside a container
docker exec -it daemon_dave /bin/bash
```

## Stopping a daemonized container

```sh
docker stop daemon_dave
```

📝 The `docker stop` command sends a `SIGTERM` signal to the Docker container's
running process. If you want to stop a container a bit more enthusiastically,
you can use the `docker kill` command, which will send a `SIGKILL` signal to the
container's process.

## Automatic container restarts

```sh
docker run --restart=always --name daemon_alice -d ubuntu \
  /bin/sh -c "while true; do echo hello world; sleep 1; done"
```

Values of `--restart`:

- `always`: no matter what exit code it returned
- `on-failure`: if it exits with a non-zero exit code, it also accepts an
  optional restart count
  - `on-failure:5`

## Finding out more about our container

```sh
docker inspect daemon_alice

# Selectively inspecting a container
docker inspect --format='{{ .State.Running }}' daemon_alice

# Inspecting the container's IP address
docker inspect --format='{{ .NetworkSettings.IPAddress }}' daemon_alice

# Inspecting multiple containers
docker inspect --format '{{ .Name }} {{ .State.Running }}' \
  daemon_dave daemon_alice
```

💡 The `--format` or `-f` flag is a bit more than it seems on the surface. It's
actually a full Go template being exposed.

📝 In addition to inspecting containers, you can see a bit more about how Docker
works by explorinng the `/var/lib/docker` directory. This directory holds your
images, containers, and container configuration. You'll find all your containers
in the `/var/lib/docker/containers` directory.

## Deleting a container

```sh
docker rm daemon_alice

# Deleting a running conntainer
docker rm -f daemon_alice

# Deleting all containers
docker rm -f $(docker ps -aq)
```
