# Chapter 7 Docker Orchestration and Service Discovery

- [Chapter 7 Docker Orchestration and Service Discovery](#chapter-7-docker-orchestration-and-service-discovery)
  - [Docker Compose](#docker-compose)
    - [Installing Docker Compose](#installing-docker-compose)
    - [Getting our sample application](#getting-our-sample-application)
    - [The `docker-compose.yml` file](#the-docker-composeyml-file)
    - [Running Compose](#running-compose)
    - [Using Compose](#using-compose)
    - [Compose in summary](#compose-in-summary)
  - [Consul, Service Discovery and Docker](#consul-service-discovery-and-docker)
    - [Building a Consul image](#building-a-consul-image)
    - [Testing a Consul container locally](#testing-a-consul-container-locally)
    - [Running a Consul cluster in Docker](#running-a-consul-cluster-in-docker)
    - [Starting the Consul bootstrap node](#starting-the-consul-bootstrap-node)
    - [Starting the remaining nodes](#starting-the-remaining-nodes)
    - [Running a distributed servide with Consul in Docker](#running-a-distributed-servide-with-consul-in-docker)
      - [Building our distributed application](#building-our-distributed-application)
      - [Building our distributed client](#building-our-distributed-client)
      - [Starting our distributed application](#starting-our-distributed-application)
      - [Starting our distributed application client](#starting-our-distributed-application-client)
  - [Docker Swarm](#docker-swarm)
    - [Understanding the Swarm](#understanding-the-swarm)
    - [Installing Swarm](#installing-swarm)
    - [Setting up a Swarm](#setting-up-a-swarm)
    - [Running a service on your Swarm](#running-a-service-on-your-swarm)
  - [Orchestration alternatives and components](#orchestration-alternatives-and-components)
    - [Fleet and etcd](#fleet-and-etcd)
    - [Kubernetes](#kubernetes)
    - [Apache Mesos](#apache-mesos)
    - [Helios](#helios)
    - [Centurion](#centurion)
  - [Summary](#summary)

## Docker Compose

> <https://docs.docker.com/compose/compose-file/>

Docker Compose calls each of the containers "services" which it defines as:

> A container that interacts with other containers in some way and that has
> specific runtime properties.

### Installing Docker Compose

### Getting our sample application

Two containers:

- An application container running the sample Python application.
- A container running the Redis database.

```sh
docker build -t octobug/composeapp .
```

### The `docker-compose.yml` file

Compose can also build Docker images. You can use the `build` instruction and
provide the path to a `Dockerfile` to have Compose build an image and then
create services from it.

```yml
version: '3'
services:
  web:
    image: octobug/composeapp
    # build: /home/octobug/compoaseapp
    command: python app.py
    ports:
      - "5000:5000"
    volumes:
      - .:/composeapp
  redis:
    image: redis
```

Same configuration on the command line:

```sh
docker run -d -p 5000:5000 -v .:/composeapp
    --name octobug/composeapp python app.py
```

### Running Compose

```sh
docker-compose up
docker-compose up -d
```

💡 By default, Compose tries to connect to a local Docker daemon but it'll also
honor the `DOCKER_HOST` environment variable to connect to a remote Docker host.

### Using Compose

```sh
# docker-compose always uses a docker-compose.yml
docker-compose ps
docker-compose logs
docker-compose kill
docker-compose rm
```

### Compose in summary

## Consul, Service Discovery and Docker

> <https://developer.hashicorp.com/consul/docs/intro>

Service discovery is the mechanism by which distributed applications manage
their relationships.

It allows these components to find each other when they want to interact. Due
to the distributed nature of these applications, service discovery mechanisms
also need to be distributed.

Each Docker container can register its running service or services with the
tool. This provides the information needed, for example an IP address or port or
both, to allow interaction between services.

Consul is a specialized datastore that uses consensus algorithms. It uses the
Raft consensus algorithm to require a quorum for writes. It also exposes a key
value store and service catalog that is highly available, fault-tolerant, and
maintains strong consistency guarantees.

Services can register themselves with Consul and share that registration
information in a highly available and distributed manner.

Consul provides:

- A service catalog with an API instead of the traditional `key=value` store of
  most service discovery tools.
- Both a DNS-based query interface through an inbuilt DNS server and a
  HTTP-based REST API to query the information. The choice of interfaces,
  especially the DNS-based interface, allows you to easily drop Consul into your
  existing environment.
- Service monitoring AKA health checks. Consul has powerful service monitoring
  built into the tool.

Practice:

- Create a Docker image for the Consul service.
- Build three hosts running Docker and then run Consul on each. The three hosts
  will provide us with a distributed environment to see how resiliency and
  failover works with Consul.
- Build services that we'll register with Consul and then query that data from
  another service.

### Building a Consul image

> <https://developer.hashicorp.com/consul/docs/agent/config/config-files>

Consul ports:

- `53/udp`: DNS server
- `8300`: Server RPC
- `8301 + udp`: Serf LAN port
- `8302 + udp`: Serf WAN port
- `8400`: RPC endpoint
- `8500`: HTTP API

```sh
docker build -t="octobug/consul" .
```

### Testing a Consul container locally

```sh
docker run -p 8500:8500 -p 53:53/udp \
    -h node1 octobug/consul -server -bootstrap
```

- `server`: tells the Consul agent to operate in server mode
- `bootstrap`: tells Consul that this node is allowed to self-elect as a leader

⚠️ No more than one server per datacenter can be running in `bootstrap` mode.
Otherwise consistency cannot be guaranteed if multiple nodes are able to
self-elect.

### Running a Consul cluster in Docker

There are three new hosts each with a Docker daemon to run Consul. On each host
we're going to run a Docker container with the `octobug/consul` image.

- `larry`
- `curly`
- `moe`

In most cases, the network to run Consul over is private. Here we use public
network to demonstrate. On `larry`, `curly` and `moe`:

```sh
PUBLIC_IP="$(ifconfig eth0 | awk -F ' *|:' '/inet addr/{print $4}')"
echo $PUBLIC_IP
```

We then choose `larry` to bootstrap to start the cluster. `larry`'s IP needs to
be set on `curly` and `moe` to tell them which Consul node's cluster to join. On
`curly` and `moe`:

```sh
$JOIN_IP=IP.IP.IP.IP
```

### Starting the Consul bootstrap node

On `larry`:

```sh
docker run -d -h $HOSTNAME \
    -p 53:53/udp \
    -p 8300:8300 \
    -p 8301:8301 -p 8301:8301/udp \
    -p 8302:8302 -p 8302:8302/udp \
    -p 8400:8400 \
    -p 8500:8500 \
    --name larry_agent octobug/consul \
    -server -advertise $PUBLIC_IP -bootstrap-expect 3
```

- `advertise`: to advertise itself on the IP address specified in the
  `$PUBLIC_IP` environment variable.
- `bootstrap-expect`: how many agents to expect in this cluster

### Starting the remaining nodes

On `curly`:

```sh
docker run -d -h $HOSTNAME \
    -p 53:53/udp \
    -p 8300:8300 \
    -p 8301:8301 -p 8301:8301/udp \
    -p 8302:8302 -p 8302:8302/udp \
    -p 8400:8400 \
    -p 8500:8500 \
    --name curly_agent octobug/consul \
    -server -advertise $PUBLIC_IP -join $JOIN_IP
```

On `moe`:

```sh
docker run -d -h $HOSTNAME \
    -p 53:53/udp \
    -p 8300:8300 \
    -p 8301:8301 -p 8301:8301/udp \
    -p 8302:8302 -p 8302:8302/udp \
    -p 8400:8400 \
    -p 8500:8500 \
    --name moe_agent octobug/consul \
    -server -advertise $PUBLIC_IP -join $JOIN_IP
```

When the expected number of cluster members is reached, it triggers a leader
election.

Test the DNS:

```sh
ip addr show docker0
# IP.IP.IP.IP

dig @IP.IP.IP.IP consul.service.consul
# Query the IP of the local Docker interface as a DNS server and asked it to
#   return any infomation on `consul.service.consul`
```

`consul.service.consul` represents the DNS entry for the Consul service itself.
It is Consul's DNS shorthand for services:

- `consul` is the host
- `service.consul` is the domain

```sh
dig @IP.IP.IP.IP curly.node.consul +noall +answer
```

### Running a distributed servide with Consul in Docker

Two parts:

- A web application, `distributed_app`. It runs web workers and registers them
  as services with Consul when it starts.
  - Runs on `larry` and `curly`.
- A client for the application, `distributed_client`. The client reads data
  about distributed_app from Consul and reports the current application state
  and configuration.
  - Runs on `moe`.

#### Building our distributed application

```dockerfile
FROM ubuntu:18.04
LABEL maintainer="whalevocal@gmail.com"
ENV REFRESHED_AT=2016-06-01

RUN apt-get update
RUN apt-get -y install ruby-dev git libcurl4-openssl-dev curl build-essential python
RUN gem install --no-ri --no-rdoc uwsgi sinatra

RUN mkdir -p /opt/distributed_app
WORKDIR /opt/distributed_app

RUN uwsgi --build-plugin https://github.com/unbit/uwsgi-consul

ADD uwsgi-consul.ini /opt/distributed_app/
ADD config.ru /opt/distributed_app/

ENTRYPOINT [ "uwsgi", "--ini", "uwsgi-consul.ini", "--ini", "uwsgi-consul.ini:server1", "--ini", "uwsgi-consul.ini:server2" ]
CMD []
```

```ini
[uwsgi]
plugins = consul
socket = 127.0.0.1:9999
master = true
enable-threads = true

[server1]
consul-register = url=http://%h.node.consul:8500,name=distributed_app,id=server1,port=2001
mule = config.ru

[server2]
consul-register = url=http://%h.node.consul:8500,name=distributed_app,id=server2,port=2002
mule = config.ru
```

The `uwsgi-consul.ini` file uses uWSGI's Mule construct to run two identical
applications. When the framework runs the file, it will create two application
workers and register a service for each on Consul.

#### Building our distributed client

```dockerfile
FROM ubuntu:18.04
LABEL maintainer="whalevocal@gmail.com"
ENV REFRESHED_AT=2016-06-01

RUN apt-get update
RUN apt-get -y install ruby ruby-dev build-essential
RUN gem install --no-ri --no-rdoc json

RUN mkdir -p /opt/distributed_client
ADD client.rb /opt/distributed_client/

WORKDIR /opt/distributed_client

ENTRYPOINT [ "ruby", "/opt/distributed_client/client.rb" ]
CMD []
```

The client checks the Consul HTTP API and the Consul DNS for the presence of a
service called `distributed_app`. It queries the host `consul.service.consul`
which is the DNS CNAME entry that contains all the A records of the Consul
cluster nodes. This demonstrates a simple DNS round robin for queries.

If no service is present is puts a message to that effect on the consle. If it
detects a `distributed_app` service then it:

- Parses out the JSON output from the API call and returns some useful
  information to the console.
- Performs a DNS lookup for any A records for that service and returns them to
  the console.

This shows the results of launching the `distributed_app` containers on the
Consul cluster.

```sh
docker build -t="octobug/distributed_client" .
```

#### Starting our distributed application

On `larry`:

```sh
docker run --dns=IP.IP.IP.IP -h $HOSTNAME -d --name larry_distributed \
    octobug/distributed_app
```

`IP.IP.IP.IP` is the IP of docker0 interface, this will allow the application to
lookup nodes and services in Consul.

The `-h` flag is set as `$HOSTNAME`. This is used to tell uWSGI what Consul node
to register the service on.

```sh
docker logs larry_distributed
```

On `curly`:

```sh
docker run --dns=IP.IP.IP.IP -h $HOSTNAME -d --name curly_distributed \
    octobug/distributed_app
```

#### Starting our distributed application client

On `moe`:

```sh
docker run -it --dns=IP.IP.IP.IP --name moe_distributed_client \
    octobug/distributed_client
```

The client can take advantage of the information returned from Consul to
configure, connect, route between elements of the distributed application.

## Docker Swarm

> <https://docs.docker.com/engine/swarm/>

Docker Swarm is native clustering for Docker. It turns a pool of Docker hosts
into a single virtual Docker host. It clusters together multiple Docker hosts
and serves the standard Docker API on top of that cluster. This moves up the
abstraction of Docker containers to the cluster level without you having to
learn a new API. This makes integration with tools that already support the
Docker API easy, including the standard Docker client. To a Docker client a
Swarm cluster is just another Docker host.

### Understanding the Swarm

A swarm is a cluster of Docker hosts onto which you can deploy services. It is
made up of manager and worker nodes.

- Each unit of work is called a task.
- Managers do the dispatching and organizing of work on the swarm.
  - Managers also handle all the cluster management functions that keep the
    swarm healthy and active.
  - If there is more than one manager then the manager node will conduct an
    election for a leader.
- Worker nodes run the tasks dispatched from manager nodes.
- Every node, managers and workders, will run tasks by default.
  - You can configure a swarm manager node to only perform management
    activities.

As a task is a pretty atomic unit swarms use a bigger abstraction, called a
service as a building block. Services defined which tasks are executed on the
nodes. Each service consists of a container image and a series of commands to
execute inside one or more containers on the nodes. You can run services in a
number of modes:

- **Replicated services**: a swarm manager distributes replica tasks amongst
  workers according to a scale you specify.
- **Global services**: a swarm manager dispatches one task for the service on
  every available worker.

The swarm also manages load balancing and DNS much like a local Docker host.
Each swarm can expose ports, much like Docker containers publish ports.

### Installing Swarm

### Setting up a Swarm

e.g. Each node in the cluster runs a Swarm node agent. Each agent registers its
related Docker daemon with the cluster.

- `larry`: Manager
- `curly`: Worker
- `moe`: Worker

Ports:

- `2377`: Cluster Management
- `7946` + udp: Node communication
- `4789` + udp: Overlay network

On `larry`

```sh
PUBLIC_IP="$(ifconfig eth0 | awk -F ' *|:' '/inet addr/{print $4}')"
echo $PUBLIC_IP

# ubuntu 22.04
PUBLIC_IP="$(ifconfig enp1s0 | awk '/inet / {print $2}')"
echo $PUBLIC_IP
```

```sh
docker swarm init --advertise-addr $PUBLIC_IP

# Show join-token on the Swarm manager
docker swarm join-token worker

docker info
docker node ls
```

On `curly` and `moe`:

```sh
docker swarm join --token SWMTKN-1-2 xxxxxxxx \
    IP.IP.IP.IP:2377
```

### Running a service on your Swarm

Replica services run the number of tasks you speficy.

```sh
docker service create --replicas 2 --name heyworld ubuntu \
    /bin/sh -c "while true; do echo hey world; sleep 1; done"

docker service ls
docker service inspect --pretty heyworld
docker service ps heyworld
```

To add another task to the service, scaling it up:

```sh
docker service scale heyworld=3
docker service ps heyworld
```

We can also run global services. Rather than running as many replicas as you
speficy, global services run on every worker in the swarm.

```sh
docker service create --name heyworld_global --mode global ubuntu \
    /bin/sh -c "while true; do echo hey world; sleep 1; done"

docker service ps heyworld_global

docker service rm heyworld
```

💡 Swarm mode also allows for scaling, draining and staged upgrades.

- <https://docs.docker.com/engine/swarm/swarm-tutorial/>

## Orchestration alternatives and components

Two categories of them:

- Scheduling and cluster management.
- Service discovery.

### Fleet and etcd

- **Fleet**: a cluster management tool.
  - The official of recommends k8s now.
- **etcd**: a highly available key value store for shared configuration and
  service discovery.

### Kubernetes

Kubernetes is a container cluster management tool. It allows you to deploy and
scale applications using Docker across multiple hosts.

### Apache Mesos

A highly available cluster management tool.

### Helios

A Docker orchestration platform for deploying and managing containers across an
entire fleet.

### Centurion

A Docker-based deployment tool. It takes containers from a Docker registry and
runs them on a fleet of hosts with the correct environment variables, host
volume mappings, and port mappings.

## Summary
