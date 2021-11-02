# Webapps with Docker

> <https://docker-curriculum.com/#webapps-with-docker>

## Static Sites

```sh
docker run --rm prakhar1989/static-site
```

```sh
docker run -d -P --name static-site prakhar1989/static-site
```

In the above command, `-d` will detach our terminal, `-P` will publish all
exposed ports to random ports and finally `--name` corresponds to a name we
want to give. Now we can see the ports by running the `docker port [CONTAINER]`
command.

```sh
docker port static-site
```

You can also specify a custom port to which the client will forward connections
to the container.

```sh
docker run -d -p 8888:80 --name static-site prakhar1989/static-site
# podman works fine ;)
podman run -d -p 8888:80 --name static-site prakhar1989/static-site
```

```sh
docker stop static-site
```

## Docker Images

> progress: <https://docker-curriculum.com/#docker-images>
