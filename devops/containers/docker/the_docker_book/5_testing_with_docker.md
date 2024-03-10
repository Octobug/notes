# Chapter 5 Testing with Docker

- [Chapter 5 Testing with Docker](#chapter-5-testing-with-docker)
  - [Using Docker to test a static website](#using-docker-to-test-a-static-website)
    - [An initial Dockerfile for the Sample website](#an-initial-dockerfile-for-the-sample-website)
    - [Building our Sample webside and Nginx image](#building-our-sample-webside-and-nginx-image)
    - [Building containers from our Sample website and Nginx image](#building-containers-from-our-sample-website-and-nginx-image)
    - [Editing our website](#editing-our-website)
  - [Using Docker to build and test a web application](#using-docker-to-build-and-test-a-web-application)
    - [Building our Sinatra application](#building-our-sinatra-application)
    - [Creating our Sinatra container](#creating-our-sinatra-container)
    - [Extending our Sinatra application to use Redis](#extending-our-sinatra-application-to-use-redis)
      - [Updating our Sinatra application](#updating-our-sinatra-application)
      - [Building a Redis database image](#building-a-redis-database-image)
    - [Connecting our Sinatra application to the Redis container](#connecting-our-sinatra-application-to-the-redis-container)
    - [Docker internal networking](#docker-internal-networking)

## Using Docker to test a static website

### An initial Dockerfile for the Sample website

```dockerfile
FROM ubuntu:18.04
LABEL maintainer="whalevocal@gmail.com"
ENV REFRESHED_AT 2016-06-01
RUN apt-get -y update; apt-get -y install nginx
RUN mkdir -p /var/www/html/website
ADD global.conf /etc/nginx/conf.d/
ADD nginx.conf /etc/nginx/nginx.conf
EXPOSE 80
```

The `daemon off;` in `nginx.conf` prevents Nginx from going into the background
and forces it to run in the foreground. This is because Docker containers rely
on the running process inside them to remain active. By default, Nginx
daemonizes itself when started, which would cause the container to run briefly
and then stop when the daemon was forked and launched and the original process
that forked it stopped.

### Building our Sample webside and Nginx image

```sh
docker build -t octobug/nginx .
docker history octobug/nginx
```

The history starts with the final layer.

### Building containers from our Sample website and Nginx image

```sh
docker run -d -p 80 --name website \
    -v $PWD/website:/var/www/html/website \
    octobug/nginx nginx
```

`-v`: create a volume in the container from a directory on the host.

- Volumes are specially designated directories within one or more containers
  that bypass the layered Union File System to provide persistent or shared
  data for Docker.
- Changes to a volume are made directly and bypass the image.
- They will not be included when we commit or build an image.

💡 Volumes can be shared between containers and can persist even when containers
are stopped.

- `-v` works by specifying a directory or mount on the local host separated from
  the directory on the container with a `:`. Docker will automatically create
  the container directory.
- We can also specify the read/write status of the container directory by adding
  either `rw` or `ro` after that directory.

```sh
docker run -d -p 80 --name website \
    -v $PWD/website:/var/www/html/website:ro \
    octobug/nginx nginx
```

### Editing our website

## Using Docker to build and test a web application

### Building our Sinatra application

```dockerfile
FROM ubuntu:18.04
LABEL maintainer="whalevocal@gmail.com"
ENV REFRESHED_AT 2016-06-01

RUN apt-get update -y; apt-get -y install ruby ruby-dev build-essential \
    redis-tools
RUN gem install --no-rdoc --no-ri sinatra json redis

RUN mkdir -p /opt/webapp

EXPOSE 4567

CMD ["/opt/webapp/bin/webapp"]
```

```sh
docker build -t octobug/sinatra .
```

### Creating our Sinatra container

```sh
chmod +x webapp/bin/webapp

docker run -d -p 4567 --name webapp \
    -v $PWD/webapp:/opt/webapp octobug/sinatra

docker logs -f webapp
docker top webapp
docker port webapp 4567

curl -i -H 'Accept: application/json' \
    -d 'name=Foo&status=Bar' http://localhost:32769/json
```

### Extending our Sinatra application to use Redis

#### Updating our Sinatra application

```sh
chmod +x webapp_redis/bin/webapp
```

#### Building a Redis database image

```sh
docker build -t octobug/redis .
docker run -d -p 6379 --name redis octobug/redis
docker port redis 6379

redis-cli -h localhost -p 32770
```

### Connecting our Sinatra application to the Redis container

There are two ways to connect containers by the network:

- Docker's own internal network.
  - It is not an overly flexible or powerful solution.
  - Not recommended as a solution for connecting containers.
- From Docker 1.9 and later, using Docker Networking and the `docker network`.
  - It can connect containers to each other across different hosts.
  - Containers connected via Docker Networking can be stopped, started or
    restarted without needing to update connections.
  - With Docker Networking you don't need to create a container before you can
    connect to it. You also don't need to worry about the order in which you run
    containers and you get internal container name resolution and discovery
    inside the network.

### Docker internal networking
