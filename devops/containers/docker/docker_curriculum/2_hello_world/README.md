# Hello World

> <https://docker-curriculum.com/#hello-world>

## Playing with Busybox

```sh
docker pull busybox
```

## Docker Run

### run

```sh
# run then exit
docker run busybox
# run then exec echo
docker run busybox echo "hello from busybox"
# run then exit then rm container
docker run --rm busybox
# run container and with an interactive tty
docker run -it busybox sh
```

### ps

```sh
# list all containers that are running
docker ps
# list all containers that ever ran
docker ps -a
```

### rm

```sh
# rm container
docker rm <container_id>
# rm all containers that have a status of exited
docker rm $(docker ps -a -q -f status=exited)
```

### container

```sh
# rm all stopped containers
docker container prune
```

## Terminology

- *Images* - The blueprints of our application which form the basis of
  containers. In the demo above, we used the `docker pull` command to download
  the busybox image.
- *Containers* - Created from Docker images and run the actual application. We
  create a container using `docker run` which we did using the busybox image
  that we downloaded. A list of running containers can be seen using the
  `docker ps` command.
- *Docker Daemon* - The background service running on the host that manages
  building, running and distributing Docker containers. The daemon is the
  process that runs in the operating system which clients talk to.
- *Docker Client* - The command line tool that allows the user to interact with
  the daemon. More generally, there can be other forms of clients too - such as
  Kitematic which provide a GUI to the users.
- *Docker Hub* - A `registry` of Docker images. You can think of the registry
  as a directory of all available Docker images. If required, one can host
  their own Docker registries and can use them for pulling images.
