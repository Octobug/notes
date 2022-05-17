# Multi Container Environments

> <https://docker-curriculum.com/#multi-container-environments>

- [Multi Container Environments](#multi-container-environments)
  - [SF Food Trucks](#sf-food-trucks)
  - [Docker Network](#docker-network)
  - [Docker Compose](#docker-compose)
  - [Development Workflow](#development-workflow)
  - [AWS Elastic Container Service](#aws-elastic-container-service)

## SF Food Trucks

The application consists of

- a **Flask backend server**
- an **Elasticsearch service**

A natural way to split this app would be to have two containers - one running
the Flask process and another running the Elasticsearch (ES) process. That way
if our app becomes popular, we can scale it by adding more containers depending
on where the bottleneck lies.

The Elasticsearch service:

```sh
docker search elasticsearch
docker pull docker.elastic.co/elasticsearch/elasticsearch:6.3.2
docker run -d --name es -p 9200:9200 -p 9300:9300 \
    -e "discovery.type=single-node" \
    docker.elastic.co/elasticsearch/elasticsearch:6.3.2
docker container logs es
# check if the ES is running.
curl 0.0.0.0:9200
```

The Flask backend server (in the `FoodTrucks` project):

```docker
# start from base
FROM ubuntu:18.04

MAINTAINER Prakhar Srivastav <prakhar@prakhar.me>

# install system-wide deps for python and node
RUN apt-get -yqq update
RUN apt-get -yqq install python3-pip python3-dev curl gnupg
RUN curl -sL https://deb.nodesource.com/setup_10.x | bash
RUN apt-get install -yq nodejs

# copy our application code
ADD flask-app /opt/flask-app
WORKDIR /opt/flask-app

# fetch app specific deps
RUN npm install
RUN npm run build
RUN pip3 install -r requirements.txt

# expose port
EXPOSE 5000

# start app
CMD [ "python3", "./app.py" ]
```

```sh
$ docker build -t yourusername/foodtrucks-web .

$ docker run -P --rm yourusername/foodtrucks-web
Unable to connect to ES. Retying in 5 secs...
Unable to connect to ES. Retying in 5 secs...
Unable to connect to ES. Retying in 5 secs...
Out of retries. Bailing out...
```

## Docker Network

```sh
$ docker network ls
NETWORK ID          NAME                DRIVER              SCOPE
c2c695315b3a        bridge              bridge              local
a875bec5d6fd        host                host                local
ead0e804a67b        none                null                local
```

```sh
$ docker network inspect bridge
[
    {
        "Name": "bridge",
        "Id": "c2c695315b3aaf8fc30530bb3c6b8f6692cedd5cc7579663f0550dfdd21c9a26",
        "Created": "2018-07-28T20:32:39.405687265Z",
        "Scope": "local",
        "Driver": "bridge",
        "EnableIPv6": false,
        "IPAM": {
            "Driver": "default",
            "Options": null,
            "Config": [
                {
                    "Subnet": "172.17.0.0/16",
                    "Gateway": "172.17.0.1"
                }
            ]
        },
        "Internal": false,
        "Attachable": false,
        "Ingress": false,
        "ConfigFrom": {
            "Network": ""
        },
        "ConfigOnly": false,
        "Containers": {
            "277451c15ec183dd939e80298ea4bcf55050328a39b04124b387d668e3ed3943": {
                "Name": "es",
                "EndpointID": "5c417a2fc6b13d8ec97b76bbd54aaf3ee2d48f328c3f7279ee335174fbb4d6bb",
                "MacAddress": "02:42:ac:11:00:02",
                "IPv4Address": "172.17.0.2/16",
                "IPv6Address": ""
            }
        },
        "Options": {
            "com.docker.network.bridge.default_bridge": "true",
            "com.docker.network.bridge.enable_icc": "true",
            "com.docker.network.bridge.enable_ip_masquerade": "true",
            "com.docker.network.bridge.host_binding_ipv4": "0.0.0.0",
            "com.docker.network.bridge.name": "docker0",
            "com.docker.network.driver.mtu": "1500"
        },
        "Labels": {}
    }
]
```

```sh
# run command on existing container
docker exec -it es bash
```

```sh
$ docker run -it --rm yourusername/foodtrucks-web bash
root@35180ccc206a:/opt/flask-app# curl 172.17.0.2:9200
{
  "name" : "Jane Foster",
  "cluster_name" : "elasticsearch",
  "version" : {
    "number" : "2.1.1",
    "build_hash" : "40e2c53a6b6c2972b3d13846e450e66f4375bd71",
    "build_timestamp" : "2015-12-15T13:05:55Z",
    "build_snapshot" : false,
    "lucene_version" : "5.3.1"
  },
  "tagline" : "You Know, for Search"
}
root@35180ccc206a:/opt/flask-app# exit
```

There are still two problems with this approach:

- How do we tell the Flask container that `es` hostname stands for 172.17.0.2
  or some other IP since the IP can change?
- Since the bridge network is shared by every container by default, this method
  is not secure. How do we isolate our network?

```sh
$ docker network create foodtrucks-net
0815b2a3bb7a6608e850d05553cc0bda98187c4528d94621438f31d97a6fea3c

$ docker network ls
NETWORK ID          NAME                DRIVER              SCOPE
c2c695315b3a        bridge              bridge              local
0815b2a3bb7a        foodtrucks-net      bridge              local
a875bec5d6fd        host                host                local
ead0e804a67b        none                null                local
```

The `network create` command creates a new `bridge` network. In terms of
Docker, a bridge network uses a software bridge which allows containers
connected to the same bridge network to communicate, while providing isolation
from containers which are not connected to that bridge network. The Docker
bridge driver automatically installs rules in the host machine so that
containers on different bridge networks cannot communicate directly with each
other.

```sh
$ docker container stop es
es

$ docker container rm es
es

$ docker run -d --name es --net foodtrucks-net \
    -p 9200:9200 -p 9300:9300 -e "discovery.type=single-node" \
    docker.elastic.co/elasticsearch/elasticsearch:6.3.2
13d6415f73c8d88bddb1f236f584b63dbaf2c3051f09863a3f1ba219edba3673

$ docker network inspect foodtrucks-net
[
    {
        "Name": "foodtrucks-net",
        "Id": "0815b2a3bb7a6608e850d05553cc0bda98187c4528d94621438f31d97a6fea3c",
        "Created": "2018-07-30T00:01:29.1500984Z",
        "Scope": "local",
        "Driver": "bridge",
        "EnableIPv6": false,
        "IPAM": {
            "Driver": "default",
            "Options": {},
            "Config": [
                {
                    "Subnet": "172.18.0.0/16",
                    "Gateway": "172.18.0.1"
                }
            ]
        },
        "Internal": false,
        "Attachable": false,
        "Ingress": false,
        "ConfigFrom": {
            "Network": ""
        },
        "ConfigOnly": false,
        "Containers": {
            "13d6415f73c8d88bddb1f236f584b63dbaf2c3051f09863a3f1ba219edba3673": {
                "Name": "es",
                "EndpointID": "29ba2d33f9713e57eb6b38db41d656e4ee2c53e4a2f7cf636bdca0ec59cd3aa7",
                "MacAddress": "02:42:ac:12:00:02",
                "IPv4Address": "172.18.0.2/16",
                "IPv6Address": ""
            }
        },
        "Options": {},
        "Labels": {}
    }
]
```

```sh
$ docker run -it --rm --net foodtrucks-net yourusername/foodtrucks-web bash
root@9d2722cf282c:/opt/flask-app# curl es:9200
{
  "name" : "wWALl9M",
  "cluster_name" : "docker-cluster",
  "cluster_uuid" : "BA36XuOiRPaghPNBLBHleQ",
  "version" : {
    "number" : "6.3.2",
    "build_flavor" : "default",
    "build_type" : "tar",
    "build_hash" : "053779d",
    "build_date" : "2018-07-20T05:20:23.451332Z",
    "build_snapshot" : false,
    "lucene_version" : "7.3.1",
    "minimum_wire_compatibility_version" : "5.6.0",
    "minimum_index_compatibility_version" : "5.0.0"
  },
  "tagline" : "You Know, for Search"
}
root@53af252b771a:/opt/flask-app# ls
app.py  node_modules  package.json  requirements.txt  static  templates  webpack.config.js
root@53af252b771a:/opt/flask-app# python3 app.py
Index not found...
Loading data in elasticsearch ...
Total trucks loaded:  733
 * Running on http://0.0.0.0:5000/ (Press CTRL+C to quit)
root@53af252b771a:/opt/flask-app# exit
```

On user-defined networks like foodtrucks-net, containers can not only
communicate by IP address, but can also resolve a container name to an IP
address. This capability is called `automatic service discovery`.

```sh
$ docker run -d --net foodtrucks-net -p 5000:5000 --name foodtrucks-web \
    yourusername/foodtrucks-web
852fc74de2954bb72471b858dce64d764181dca0cf7693fed201d76da33df794

$ docker container ls
CONTAINER ID  IMAGE
  COMMAND                 CREATED             STATUS
  PORTS                                           NAMES
852fc74de295  yourusername/foodtrucks-web
  "python3 ./app.py"      About a minute ago  Up About a minute
  0.0.0.0:5000->5000/tcp                          foodtrucks-web
13d6415f73c8  docker.elastic.co/elasticsearch/elasticsearch:6.3.2
  "/usr/local/bin/dock…"  17 minutes ago      Up 17 minutes
  0.0.0.0:9200->9200/tcp, 0.0.0.0:9300->9300/tcp  es

$ curl -I 0.0.0.0:5000
HTTP/1.0 200 OK
Content-Type: text/html; charset=utf-8
Content-Length: 3697
Server: Werkzeug/0.11.2 Python/2.7.6
Date: Sun, 10 Jan 2016 23:58:53 GMT
```

```sh
#!/bin/bash

# build the flask container
docker build -t prakhar1989/foodtrucks-web .

# create the network
docker network create foodtrucks-net

# start the ES container
docker run -d --name es --net foodtrucks-net -p 9200:9200 -p 9300:9300 -e \
  "discovery.type=single-node" \
  docker.elastic.co/elasticsearch/elasticsearch:6.3.2

# start the flask app container
docker run -d --net foodtrucks-net -p 5000:5000 --name foodtrucks-web \
  prakhar1989/foodtrucks-web
```

## Docker Compose

```yml
version: "3"
services:
  es:
    image: docker.elastic.co/elasticsearch/elasticsearch:6.3.2
    container_name: es
    environment:
      - discovery.type=single-node
    ports:
      - 9200:9200
    volumes:
      - esdata1:/usr/share/elasticsearch/data
  web:
    image: yourusername/foodtrucks-web
    command: python3 app.py
    depends_on:
      - es
    ports:
      - 5000:5000
    volumes:
      - ./flask-app:/opt/flask-app
volumes:
  esdata1:
    driver: local
```

At the parent level, we define the names of our services - `es` and `web`. The
`image` parameter is always required, and for each service that we want Docker
to run, we can add additional parameters. For `es`, we just refer to the
`elasticsearch` image available on Elastic registry. For our Flask app, we
refer to the image that we built at the beginning of this section.

Other parameters such as `command` and `ports` provide more information about
the container. The `volumes` parameter specifies a mount point in our `web`
container where the code will reside. This is purely optional and is useful if
you need access to logs, etc. We'll later see how this can be useful during
development. We also add volumes for the `es` container so that the data we
load persists between restarts. We also specify `depends_on`, which tells
docker to start the `es` container before `web`.

```sh
docker-compose up
docker-compose up -d
docker-compose down -v
```

You can see that compose went ahead and created a new network called
`foodtrucks_default` and attached both the new services in that network so that
each of these are discoverable to the other. Each container for a service joins
the default network and is both reachable by other containers on that network,
and discoverable by them at a hostname identical to the container name.

## Development Workflow

```sh
$ docker-compose run web bash
Starting es ... done
root@581e351c82b0:/opt/flask-app# ls
app.py        package-lock.json  requirements.txt  templates
node_modules  package.json       static            webpack.config.js
root@581e351c82b0:/opt/flask-app# grep hello app.py
root@581e351c82b0:/opt/flask-app# exit
```

First off, we need to tell docker compose to not use the image and instead use
the files locally. We'll also set debug mode to `true` so that Flask knows to
reload the server when `app.py` changes. Replace the `web` portion of the
`docker-compose.yml` file like so:

```yml
version: "3"
services:
  es:
    image: docker.elastic.co/elasticsearch/elasticsearch:6.3.2
    container_name: es
    environment:
      - discovery.type=single-node
    ports:
      - 9200:9200
    volumes:
      - esdata1:/usr/share/elasticsearch/data
  web:
    build: . # replaced image with build
    command: python3 app.py
    environment:
      - DEBUG=True # set an env var for flask
    depends_on:
      - es
    ports:
      - "5000:5000"
    volumes:
      - ./flask-app:/opt/flask-app
volumes:
  esdata1:
    driver: local
```

## AWS Elastic Container Service

> <https://docker-curriculum.com/#aws-elastic-container-service>
