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
      - [Our Redis container's network](#our-redis-containers-network)
    - [Docker networking](#docker-networking)
      - [Connecting existing containers to the network](#connecting-existing-containers-to-the-network)
    - [Connecting containers summary](#connecting-containers-summary)
  - [Using Docker for continuous integration](#using-docker-for-continuous-integration)
    - [Build a Jenkins and Docker server](#build-a-jenkins-and-docker-server)
    - [Create a new Jenkins job](#create-a-new-jenkins-job)
    - [Next steps with our Jenkins job](#next-steps-with-our-jenkins-job)
    - [Summary of our Jenkins setup](#summary-of-our-jenkins-setup)
  - [Multi-configuration Jenkins](#multi-configuration-jenkins)
    - [Create a multi-configuration job](#create-a-multi-configuration-job)
    - [Testing our multi-configuration job](#testing-our-multi-configuration-job)
    - [Summary of our multi-configuration Jenkins](#summary-of-our-multi-configuration-jenkins)
  - [Other alternatives](#other-alternatives)
    - [Drone](#drone)
    - [Shippable](#shippable)
  - [Summary](#summary)

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

Every Docker container is assigned an IP address, provided through an interface
created when we installed Docker. That interface is called `docker0`.

💡 IPv6 addresses are also supported. To enable this run the Docker daemon with
the `--ipv6` flag.

```sh
# debian
ip a show docker0

# macOS 没有 docker0: https://docker-docs.uclv.cu/docker-for-mac/networking/#there-is-no-docker0-bridge-on-macos
```

The `docker0` interface has an RFC1918 private IP adress in the `172.16-172.30`
range. It is a virtual Ethernet bridge that connects the containers and the
local host network.

💡 Docker will default to `172.12.x.x` as a subnet unless that subnet is already
in use, in which case it will try to acquire another in the `172.16-172.30`
ranges.

Interfaces starting with `veth` are craeted every time Docker creates a
container. At that time, it creates a pair of peer interfaces that are like
opposite ends of a pipe (a packet sent on one will be received on the other). It
gives one of the peers to the container to become its `eth0` interface and keeps
the other peer, with a unique name like `vethac0d`, out on the host machine.

A `veth` interface's one end is plugged into the `docker0` bridge, and the other
end is plugged into the container. By binding every `veth*` interface to the
`docker0` bridge, Docker creates a virtual subnet shared between the host
machine and every Docker container.

```sh
docker run -it ubuntu /bin/bash

root@0d690a46529c:/# hostname -I
172.17.0.3
# its next hop to the outside world is the `docker0` interface gateway IP
```

There's one other piece of Docker networking that enables this connectivity:
firewall rules and NAT configuration allow Docker to route between containers
and the host network.

```sh
# Linux
$ sodu iptables -t nat -L -n
...
DOCKER  all....
...

Chain DOCKER (2 references)
target  prot  opt source    destination
DNAT    tcp   --  0.0.0.0/0 0.0.0.0/0   tcp dpt:49161 to :172.17.0.18:6379
# this routes traffic from the container to port 49161 on the Docker host
```

- More about networking: <https://docs.docker.com/network/>

#### Our Redis container's network

```sh
docker inspect redis
docker inspect -f '{{.NetworkSettings.IPAddress}}' redis
```

`Linux only`: because we're on the local Docker host, we don't have to use the
container's mapped port. We can instead use the `172.17.0.2` address to
communicate with the Redis server on port `6379` directly.

This initially looks like it might be a good solution for connecting our
containers together, sadly, this approach has two big rough edges:

- We'd need to hard-code the IP address of our Redis container into our apps.
- If we restart the container, Docker might change its IP address.

```sh
docker restart redis
docker inspect -f '{{.NetworkSettings.IPAddress}}' redis
```

### Docker networking

Container connections are created using Docker Networking. It allows you to
setup your own networks through which containers can communicate. Essentially
this supplements the existing `docker0` network with new, user managed networks.
Importantly, containers can now communicate with each across hosts and your
networking configuration can be highly customizable.

📝 The networking support is also pluggable, meaning you can add network drivers
to support specific topologies and networking frameworks from vendors like Cisco
and VMware.

- <https://docs.docker.com/engine/extend/plugins_network/>

To use Docker networks we first need to create a network and then launch a
container inside that network.

```sh
docker network create app
docker network inspect app
```

The `app` network is a local, bridged network much like the `docker0` network.

💡 In addition to `bridge` networks, which exist on a single host, we can also
create `overlay` networks, which allow us to span multiple hosts.

- <https://docs.docker.com/network/network-tutorial-overlay/>

```sh
docker network ls
docker network rm
docker run -d --net app --name db octobug/redis

docker network inspect app
```

```sh
cd sinatra
docker run -it -p 4567 \
  --net app --name network_test \
  octobug/sinatra /bin/bash
```

Docker will take note of all other containers running inside the same network
and populate their addresses in local DNS.

```sh
# inside the container
apt-get install -y dnsutils iputils-ping
nslookup db
```

A Docker network will also add the `app` network as a domain suffix for the
network, any host in the `app` network can be resolved by `hostname.app`.

```sh
ping db.app
```

```rb
redis = Redis.new(:host => 'db', :port => '6379')
```

```sh
docker run -d -p 4567 \
  --net app --name webapp_redis \
  -v $PWD/webapp_redis:/opt/webapp octobug/sinatra

docker port webapp_redis 4567

curl -i -H 'Accept: application/json' \
    -d 'name=Foo&status=Bar' http://localhost:32771/json
```

#### Connecting existing containers to the network

```sh
docker run -d --name db2 octobug/redis
docker network connect app db2
docker network inspect app
docker network disconnect app db2
```

Containers can belong to multiple networks.

### Connecting containers summary

## Using Docker for continuous integration

💡 There are a number of continuous integration tool alternatives to Jenkins,
including Stider and Drone, which actually make use of Docker.

### Build a Jenkins and Docker server

```dockerfile
FROM jenkins
LABEL maintainer="whalevocal@gmail.com"
ENV REFRESHED_AT 2016-06-01

USER root
RUN apt-get -y update; apt-get install -y sudo
RUN echo "jenkins ALL=NOPASSWD:ALL" >> /etc/sudoers
RUN wget https://get.docker.com/builds/Linux/x86_64/docker-latest.tgz
RUN tar -xzf docker-latest.tgz
RUN mv docker/* /usr/bin/

USER jenkins
RUN /usr/local/bin/install-plugins.sh junit git git-client ssh-slaves \
    greenballs chucknorris ws-cleanup
```

The `jenkins` user is the default for the `jenkins` image and is required for
containers launched from the image to run Jenkins correctly.

```sh
# host
sudo mkdir -p /private/var/jenkins_home
# doesn't work on macOS
# sudo chown -R 1000 /private/var/jenkins_home
sudo chmod 0777 /private/var/jenkins_home
cd /private/var/jenkins_home
```

The ownership of the `jenkins_home` is UID `1000`, which is the UID of the
`jenkins` user inside the image we're about to build. This will allow Jenkins
to write into this directory and store the Jenkins configuration.

```sh
docker build -t octobug/jenkins .

docker run -d -p 8080:8080 -p 50000:50000 \
  -v /private/var/jenkins_home:/var/jenkins_home \
  -v /var/run/docker.sock:/var/run/docker.sock \
  --name jenkins octobug/jenkins
```

The second volume mounts `/var/run/docker.sock`, the socket for Docker's daemon
into the Docker container. This will allow us to run Docker containers from
inside our Jenkins container.

- ⚠️ This is a security risk. By binding the Docker socket inside the Jenkins
  container you give the container access to the underlying Docker host.

```sh
docker logs jenkins -f
```

### Create a new Jenkins job

- `create a new job`
- name: `Docker_test_job`
- `Freestyle project`
- `Use Custome workspace`
  - `/var/jenkins_home/jobs/${JOB_NAME}/workspace`
- `Source Code Management`
  - `https://github.com/OctobugDemo/docker-jenkins-sample.git`
- `Add Build Step`
  - `Execute shell`

```sh
# Build the image to be used for this job.
# IMAGE=$(sudo docker build . | tail -l | awk '{ print $NF}')
sudo docker build -t rake_test .

# Build the directory to be mounted into Docker.
MNT="$WORKSPACE/.."

# Execute the build inside Docker.
# CONTAINER=$(sudo docker run -d -v $MNT:/opt/project/ $IMAGE /bin/bash -c 'cd /opt/project/workspace; rake spec')
CONTAINER=$(sudo docker run -d -v $MNT:/opt/project/ rake_test /bin/bash -c 'cd /opt/project/workspace; rake spec')

# Attach to the container so that we can see the output.
sudo docker attach $CONTAINER

# Get its exit code as soon as the container stops.
RC=$(sudo docker wait $CONTAINER)

# Delete the container we've just used.
sudo docker rm $CONTAINER

# Exit with the same value as that with which the process exited.
exit $RC
```

- `$WORKSPACE` is created by Jenkins, holding the workspace directory defined
  in the job. It is going to be mounted into the Docker container.
- `Add post-build action`
  - `Publish JUnit test result report`
  - `Test report XMLs`
    - `spec/reports/*.xml`: this is the location of the `ci_reporter` gem's XML
      output.

```dockerfile
FROM ubuntu:18.04
LABEL maintainer="whalevocal@gmail.com"
ENV REFRESHED_AT 2016-06-01
RUN apt-get update
RUN apt-get -y install ruby rake
RUN gem sources --add https://mirrors.tuna.tsinghua.edu.cn/rubygems/ --remove https://rubygems.org/
RUN gem install --no-rdoc --no-ri rspec ci_reporter_rspec
```

💡 Docker also comes with a command line option called `--cidfile` that captures
the container's ID and stores it in a file specified in the `--cidfile` options,
like so: `--cidfile=/tmp/containerid.txt`

### Next steps with our Jenkins job

- `SCM polling`: automatically builds when new commits are made to the repo.

### Summary of our Jenkins setup

💡 You could also use `parameterized builds` to make the job more generic.

## Multi-configuration Jenkins

When the Jenkins multi-configuration job is run, it will spawn multiple sub-jobs
that will test varying configurations.

### Create a multi-configuration job

- `Docker_matrix_job`
  - `Multi-configuration project`
- `Git`: `https://github.com/OctobugDemo/docker-jenkins-sample.git`
- `Add Axis`
  - `User-defined Axis`
    - `OS`: `centos`, `debian`, `ubuntu`
- `Build Environment`: `Delete workspace before build starts`

```sh
# Build the image to be used for this job.
cd $OS; IMAGE=$(sudo docker build . | tail -l | awk '{ print $NF}')

# Build the directory to be mounted into Docker.
MNT="$WORKSPACE/.."

# Execute the build inside Docker.
CONTAINER=$(sudo docker run -d -v $MNT:/opt/project/ $IMAGE /bin/bash -c 'cd /opt/project/$OS; rake spec')

# Attach to the container so that we can see the output.
sudo docker attach $CONTAINER

# Get its exit code as soon as the container stops.
RC=$(sudo docker wait $CONTAINER)

# Delete the container we've just used.
sudo docker rm $CONTAINER

# Exit with the same value as that with which the process exited.
exit $RC
```

### Testing our multi-configuration job

### Summary of our multi-configuration Jenkins

## Other alternatives

### Drone

### Shippable

## Summary
