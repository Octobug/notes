# Chapter 6 Building services with Docker

- [Chapter 6 Building services with Docker](#chapter-6-building-services-with-docker)
  - [Building our first application](#building-our-first-application)
    - [The Jekyll base image](#the-jekyll-base-image)
    - [Building the Jekyll base image](#building-the-jekyll-base-image)
    - [The Apache image](#the-apache-image)
    - [Building the Jekyll Apache image](#building-the-jekyll-apache-image)
    - [Launching our Jekyll site](#launching-our-jekyll-site)
    - [Updating our Jekyll site](#updating-our-jekyll-site)
    - [Backing up our Jekyll volume](#backing-up-our-jekyll-volume)
    - [Extending our Jekyll website example](#extending-our-jekyll-website-example)
  - [Building a Java application server with Docker](#building-a-java-application-server-with-docker)
    - [A WAR file fetcher](#a-war-file-fetcher)
    - [Fetching a WAR file](#fetching-a-war-file)
    - [Our Tomcat 7 application server](#our-tomcat-7-application-server)
    - [Running our WAR file](#running-our-war-file)
    - [Building on top of our Tomcat application server](#building-on-top-of-our-tomcat-application-server)
  - [A multi-container application stack](#a-multi-container-application-stack)
    - [The Node.js image](#the-nodejs-image)
    - [The Redis base image](#the-redis-base-image)
    - [The Redis primary image](#the-redis-primary-image)
    - [The Redis replica image](#the-redis-replica-image)
    - [Creating our Redis back-end cluster](#creating-our-redis-back-end-cluster)
    - [Creating our Node container](#creating-our-node-container)
    - [Capturing our application logs](#capturing-our-application-logs)
    - [Summary of our Node stack](#summary-of-our-node-stack)
  - [Managing Docker containers without SSH](#managing-docker-containers-without-ssh)
  - [Summary](#summary)

## Building our first application

Workflow:

- Create the Jekyll base image and the Apache image (once-off)
- Create a container from the Jekyll image that holds the website source mounted
  via a volume.
- Create a Docker container from the Apache image that uses the volume
  containing the compiled site and serve that out.
- Rinse and repeat as the site needs to be updated.

### The Jekyll base image

```dockerfile
FROM ubuntu:18.04
LABEL maintainer="whalevocal@gmail.com"
ENV REFRESHED_AT=2016-06-01

RUN apt-get update
RUN apt-get -y install ruby ruby-dev build-essential nodejs
RUN gem install public_suffix:4.0.7 jekyll:2.5.3

VOLUME [ "/data" ]
VOLUME [ "/var/www/html" ]
WORKDIR /data

ENTRYPOINT [ "jekyll", "build", "--destination=/var/www/html" ]
```

- `/data`: holds the website source code
- `/var/www/html`: holds the compiled Jekyll site

### Building the Jekyll base image

```sh
docker build -t octobug/jekyll .
```

### The Apache image

```dockerfile
FROM ubuntu:20.04
LABEL maintainer="whalevocal@gmail.com"
ENV REFRESHED_AT=2016-06-01

RUN apt-get update
RUN apt-get install -y apache2

VOLUME [ "/var/www/html" ]
WORKDIR /var/www/html

ENV APACHE_RUN_USER www-data
ENV APACHE_RUN_GROUP www-data
ENV APACHE_LOG_DIR /var/log/apache2
ENV APACHE_PID_FILE /var/run/apache2.pid
ENV APACHE_RUN_DIR /var/run/apache2
ENV APACHE_LOCK_DIR /var/lock/apache2

RUN mkdir -p $APACHE_RUN_DIR $APACHE_LOCK_DIR $APACHE_LOG_DIR

EXPOSE 80

ENTRYPOINT [ "/usr/sbin/apachectl" ]
CMD ["-D", "FOREGROUND"]
```

### Building the Jekyll Apache image

```sh
docker build -t octobug/apache .
```

### Launching our Jekyll site

```sh
docker run -v ~/dev/james_blog:/data/ \
    --name james_blog octobug/jekyll
```

A volume is a specially designated directory within one or more containers that
bypasses the Union File System to provide several useful features for persistent
or shared data:

- Volumes can be shared and reused between containers.
- A container doesn't have to be running to share its volumes.
- Changes to a volume are made directly.
- Changes to a volume will not be included when you update an image.
- Volumes persist even when no containers use them.

Volumes live on the Docker host in `/var/lib/docker/volumes`.

```sh
docker inspect -f "{{ range .Mounts }}{{.}}{{end}}" james_blog
```

```sh
docker run -d -P --volumes-from james_blog octobug/apache
```

The `--volumes-from` flag adds any volumes in the named container to the newly
created container.

📝 Even if you delete the last container that uses a volume, the volume will
still persist.

### Updating our Jekyll site

```sh
# Make some changes

docker start james_blog
docker logs james_blog
```

### Backing up our Jekyll volume

```sh
docker run --rm --volumes-from james_blog \
    -v $(pwd):/backup ubuntu \
    tar cvf /backup/james_blog_backup.tar /var/www/html

ls james_blog_backup.tar
```

💡 The `--rm` flag is useful for single-use or throwaway containers.

💡 This example could also work for a database stored in a volume or similar
data.

### Extending our Jekyll website example

## Building a Java application server with Docker

e.g. Two-stage Docker pipeline:

- An image that pulls down specified WAR files from a URL and stores them in a
  volume.
- An image with a Tomcat server installed that runs those downloaded WAR files.

### A WAR file fetcher

```dockerfile
FROM ubuntu:20.04
LABEL maintainer="whalevocal@gmail.com"
ENV REFRESHED_AT=2016-06-01

RUN apt-get update
RUN apt-get -y install wget

VOLUME [ "/var/lib/tomcat8/webapps/" ]
WORKDIR /var/lib/tomcat8/webapps/

ENTRYPOINT [ "wget" ]
CMD [ "-?" ]
```

```sh
docker build -t octobug/fetcher .
```

### Fetching a WAR file

```sh
docker run -it --name sample octobug/fetcher\
  https://tomcat.apache.org/tomcat-7.0-doc/appdev/sample/sample.war

docker inspect -f "{{ range .Mounts }}{{.}}{{end}}" sample
```

### Our Tomcat 7 application server

```dockerfile
FROM ubuntu:18.04
LABEL maintainer="whalevocal@gmail.com"
ENV REFRESHED_AT=2016-06-01

RUN apt-get update
RUN apt-get -y install tomcat8 default-jdk

ENV CATALINA_HOME=/usr/share/tomcat8
ENV CATALINA_BASE=/var/lib/tomcat8
ENV CATALINA_PID=/var/run/tomcat8.pid
ENV CATALINA_SH=/usr/share/tomcat8/bin/catalina.sh
ENV CATALINA_TMPDIR=/tmp/tomcat8-tomcat8-tmp

RUN mkdir -p ${CATALINA_TMPDIR}

VOLUME [ "/var/lib/tomcat8/webapps/" ]

EXPOSE 8080

ENTRYPOINT [ "/usr/share/tomcat8/bin/catalina.sh", "run" ]
```

```sh
docker build -t octobug/tomcat8 .
```

### Running our WAR file

```sh
docker run -d -P --name sample_app --volumes-from sample \
  octobug/tomcat8

docker port sample_app
# http://localhost:32769/sample/
```

### Building on top of our Tomcat application server

You can build a Docker management service by using shell interactiving with
`docker` commands.

## A multi-container application stack

Deploy a multi-container application:

- A Node container to serve a Node application.
- A Redis primary container to hold and cluster state.
- Two Redis replica containers to cluster state.
- A logging container to capture application logs.

### The Node.js image

```dockerfile
FROM ubuntu:20.04
LABEL maintainer="whalevocal@gmail.com"
ENV REFRESHED_AT=2016-06-01

RUN apt-get update
RUN apt-get -y install build-essential
RUN DEBIAN_FRONTEND=noninteractive TZ=Asia/UTC apt-get -y install tzdata
RUN apt-get -y install nodejs --fix-missing

RUN ln -s /usr/bin/nodejs /usr/bin/node
RUN mkdir -p /var/log/nodepp

ADD nodeapp /opt/nodeapp/

WORKDIR /opt/nodeapp/
RUN npm install

VOLUME [ "/var/log/nodeapp" ]

EXPOSE 3000

ENTRYPOINT [ "nodejs", "server.js" ]
```

```sh
docker build -t octobug/nodejs .
```

### The Redis base image

```dockerfile
FROM ubuntu:18.04
LABEL maintainer="whalevocal@gmail.com"
ENV REFRESHED_AT=2017-06-01

RUN apt-get update
RUN apt-get install -y software-properties-common python-software-properties
RUN add-apt-repository ppa:chris-lea/redis-server
RUN apt-get update
RUN apt-get install -y redis-server redis-tools

VOLUME [ "/var/lib/redis", "/var/log/redis" ]

EXPOSE 6379
CMD []
```

```sh
docker build -t octobug/redis .
```

### The Redis primary image

```dockerfile
FROM octobug/redis
LABEL maintainer="whalevocal@gmail.com"
ENV REFRESHED_AT=2016-06-01

ENTRYPOINT [ "redis-server", "--protected-mode no", "--logfile /var/log/redis/redis-server.log" ]
```

```sh
docker build -t octobug/redis_primary .
```

### The Redis replica image

```dockerfile
FROM octobug/redis
LABEL maintainer="whalevocal@gmail.com"
ENV REFRESHED_AT=2016-06-01

ENTRYPOINT [ "redis-server", "--protected-mode no", "--logfile /var/log/redis/redis-replica.log", "--slaveof redis_primary 6379" ]
```

```sh
docker build -t octobug/redis_replica .
```

### Creating our Redis back-end cluster

```sh
docker network create express

docker run -d -h redis_primary --net express --name redis_primary \
  octobug/redis_primary
```

`-h` sets the hostname of the container. This overrides the default behavior
(setting the hostname of the container to the short container ID).

```sh
docker logs redis_primary
```

This shows nothing because redis is logging to a file rather than to `stdout`.

```sh
docker run -it --rm --volumes-from redis_primary ubuntu \
  cat /var/log/redis/redis-server.log
```

Replica 1:

```sh
docker run -d -h redis_replica1 --name redis_replica1 --net express \
  octobug/redis_replica
```

```sh
docker run -it --rm --volumes-from redis_replica1 ubuntu \
  cat /var/log/redis/redis-replica.log
```

Replica 2:

```sh
docker run -d -h redis_replica2 --name redis_replica2 --net express \
  octobug/redis_replica
```

```sh
docker run -it --rm --volumes-from redis_replica2 ubuntu \
  cat /var/log/redis/redis-replica.log
```

### Creating our Node container

```sh
docker run -d --name nodeapp -p 3000:3000 --net express octobug/nodejs

docker logs nodeapp
```

### Capturing our application logs

```dockerfile
FROM ubuntu:18.04
LABEL maintainer="whalevocal@gmail.com"
ENV REFRESHED_AT=2016-06-01
RUN apt-get update
RUN apt-get -y install wget gnupg2 openjdk-8-jdk
RUN wget -q0 - https://artifacts.elastic.co/GPG-KEY-elasticsearch | apt-key add -
RUN echo "deb https://artifacts.elastic.co/packages/5.x/apt stable main" | tee -a /etc/apt/sources.list.d/elastic-5.x.list

RUN apt-get update
RUN apt-get install -y logstash

WORKDIR /usr/share/logstash
ADD logstash.conf /usr/share/logstash/
ENTRYPOINT [ "bin/logstash" ]
CMD [ "-f", "logstash.conf", "--config.reload.automatic" ]
```

```sh
docker build -t octobug/logstash .

docker run -d --name logstash --volumes-from redis_primary \
  --volumes-from nodeapp octobug/logstash

docker logs logstash -f
```

### Summary of our Node stack

## Managing Docker containers without SSH

In the Docker world, where most containers run a single process, SSH isn't
available.

We can use **volumes** and **networking** to perform a lot of the same actions.

- If a service is managed via a network interface, we expose that on a
  container.
- If a service is managed through a Unix socket, we expose that with a volume.
- If we need to send a signal to a Docker container, we use the `docker kill`
  command.
- If we have to sign into a container, we use `docker exec`

```sh
docker exec -it CONTAINER /bin/bash
docker kill -s SIGNAL CONTAINER
```

## Summary
