# Webapps with Docker

> <https://docker-curriculum.com/#webapps-with-docker>

## Static Sites

```sh
# --rm flag removes the container when it exits
# -it specifies an interactive terminal
docker run --rm -it prakhar1989/static-site
```

```sh
# -d detechs terminal
# -P publishes all exposed ports to random ports
# --name gives the container a name
docker run -d -P --name static-site prakhar1989/static-site
```

```sh
# see container's ports
docker port static-site
```

You can also specify a custom port to which the client will forward connections
to the container.

```sh
docker run -d -p 8888:80 --name static-site prakhar1989/static-site
```

```sh
docker stop static-site
```

## Docker Images

> progress: <https://docker-curriculum.com/#docker-images>
