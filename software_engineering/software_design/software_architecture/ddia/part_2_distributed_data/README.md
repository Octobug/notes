# Part II Distributed Data

- [Part II Distributed Data](#part-ii-distributed-data)
  - [Scaling to Higher Load](#scaling-to-higher-load)
    - [Shared-Nothing Architectures](#shared-nothing-architectures)
    - [Replication Versus Partitioning](#replication-versus-partitioning)

There are various reasons why you might want to distribute a database across
multiple machines:

- Scalability (可伸缩)
- Fault tolerance/high availability (高可用)
- Latency (低延迟)

## Scaling to Higher Load

- ***vertical scaling*** or ***scaling up***: improvements under one operating
  system
  - *shared-memory architecture*
  - *shared-disk architecture* (by NAS (Network Attached Storage) or SAN
    (Storage Area Network)) : mainly used for data warehousing workloads

### Shared-Nothing Architectures

> also called ***horizontal scaling*** or ***scaling out***

Shared-nothing architecture requires the most caution from the application
developers. It incurs additional complexity for applications and limits the
expressiveness of the data models.

### Replication Versus Partitioning

There are two common ways data is distributed across multiple nodes:

- ***Replication***
  - Keeping a copy of the same data on several different nodes, potentially in
    different locations.
  - Replication provides redundancy: if some nodes are unavailable, the data can
    still be served from the remaining nodes.
- ***Partitioning***
  - Splitting a big database into smaller subsets so that they could can be
    assigned to different nodes.
