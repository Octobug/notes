# Chapter 3 Getting Started with Docker

- [Chapter 3 Getting Started with Docker](#chapter-3-getting-started-with-docker)
  - [Running our first container](#running-our-first-container)
  - [Working with our first container](#working-with-our-first-container)
  - [Container naming](#container-naming)
  - [Starting a stopped container](#starting-a-stopped-container)
  - [Attaching to a container](#attaching-to-a-container)

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

## Attaching to a container

>>>>> progress
