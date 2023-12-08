# 6. Parititioning

- [6. Parititioning](#6-parititioning)
  - [Partitioning and Replication](#partitioning-and-replication)
  - [Partitioning of Key-Value Data](#partitioning-of-key-value-data)
    - [Partitioning by Key Range](#partitioning-by-key-range)
    - [Partitioning by Hash of Key](#partitioning-by-hash-of-key)

A ***partition***, also known as a ***shard*** (in MongoDB, Elasticsearch, and
SolrCloud), a ***region*** (in HBase), a ***tablet*** (in Bigtable), a
***vnode*** (in Cassandra and Riak), and a ***vBucket*** (in Couchbase).

Normally, partitions are defined in such a way that each piece of data (each
record, row, or document) belongs to exactly one partition. In effect, each
partition is a small database of its own, although the database may support
operations that touch multiple partitions at the same time.

The main reason for wanting to partition data is ***scalability***. Different
partitions can be placed on different nodes in a shared-nothing cluster.

Some systems are designed for transactional workloads, and others for analytics:
this difference affects how the system is tuned, but the fundamentals of
partitioning apply to both kinds of workloads.

## Partitioning and Replication

- Partitioning is usually combined with replication so that copies of each
  partition are stored on multiple nodes (for fault tolerance).
- A node may store more than one partition.
- In a leader-follower replication model configuration, each node may be the
  leader for some partitions and a follower for other partitions.
- The choice of partitioning scheme is mostly independent of the choice of
  replication scheme.

## Partitioning of Key-Value Data

- Goal: to spread the data and the query load evenly across nodes.
- ***skewed***: if the partitioning is unfair.
- ***hot spot***: a partition with disproportionately high load.

The simplest approach for avoiding hot spots would be to assign records to nodes
*randomly*. But when you try to read a particular item, you have to query all
nodes in parallel.

### Partitioning by Key Range

- One way of partitioning is to assign a continuous range (from some minimum to
  some maximum) of keys to each partition.
- As long as you know the boundaries between the ranges, you can easily
  determine which partition contains a given key.
- In order to distribute the data evenly, the partition boundaries need to adapt
  to the data.
- Partition boundaries might be chosen manually, or the database can choose them
  automatically.
- Within each partition, keeps keys in sorted order so that range scans are
  easy.
  - The downside of this is that certain access patterns can lead to hot spots.
  - e.g. If the key is a timestamp, partitioning per day in one, writes end up
    going to the same partition (today).
  - e.g. Prefixing each timestamp with the sensor name so that the partitioning
    is first by sensor name and then by time.

### Partitioning by Hash of Key
