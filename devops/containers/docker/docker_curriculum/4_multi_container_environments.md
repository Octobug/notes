# Multi Container Environments

> <https://docker-curriculum.com/#multi-container-environments>

- [Multi Container Environments](#multi-container-environments)
  - [SF Food Trucks](#sf-food-trucks)

## SF Food Trucks

The application consists of a **Flask backend server** and an **Elasticsearch
service**. A natural way to split this app would be to have two containers -
one running the Flask process and another running the Elasticsearch (ES)
process. That way if our app becomes popular, we can scale it by adding more
containers depending on where the bottleneck lies.

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
