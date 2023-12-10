# 6. Parititioning

- [6. Parititioning](#6-parititioning)
  - [Partitioning and Replication](#partitioning-and-replication)
  - [Partitioning of Key-Value Data](#partitioning-of-key-value-data)
    - [Partitioning by Key Range](#partitioning-by-key-range)
    - [Partitioning by Hash of Key](#partitioning-by-hash-of-key)
      - [Consistent Hashing](#consistent-hashing)
    - [Skewed Workloads and Relieving Hot Spots](#skewed-workloads-and-relieving-hot-spots)
  - [Partitioning and Secondary Indexes](#partitioning-and-secondary-indexes)
    - [Partitioning Secondary Indexes by Document](#partitioning-secondary-indexes-by-document)
    - [Partitioning Secondary Indexes by Term](#partitioning-secondary-indexes-by-term)
  - [Rebalancing Partitions](#rebalancing-partitions)
    - [Strategies for Rebalancing](#strategies-for-rebalancing)
      - [How not to do it: hash mod N](#how-not-to-do-it-hash-mod-n)
      - [Fixed number of partitions](#fixed-number-of-partitions)
      - [Dynamic partitioning](#dynamic-partitioning)
      - [Partitioning proportionally to nodes](#partitioning-proportionally-to-nodes)
    - [Operations: Automatic or Manual Rebalancing](#operations-automatic-or-manual-rebalancing)
  - [Request Routing](#request-routing)
    - [Parallel Query Execution](#parallel-query-execution)

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

Because of this risk of skew and hot spots, many distributed datastores use a
hash function to determine the partition for a given key.

Cassandra and MongoDB use MD5, and Voldemort uses the Fowler-Noll-Vo function.
Some built-in hash functions are not suitable for partitioning because they
may generate different hash values for the same key. e.g. Java's
`Object.hashCode`.

Once you have a suitable hash function for keys, you can assign each partition
a range of hashes (rather than a range of keys).

⚠️ By using the hash of the key for partitioning, the ability to do efficient
range queries is lost.

e.g. In MongoDB, if you have enabled hash-based sharding mode, any range query
has to be sent to all partitions.

A table in Cassandra can be declared with a ***compound primary key***
consisting of several columns. Only the first part of that key is hashed to
determine the partition, but the other columns are used as a concatenated index
for sorting the data in its SSTables.

- A query cannot search for a range of values within the first column of a
  compound key.
- But if it specifies a fixed value for the first column, it can perform an
  effecient range scan over the other columns of the key.
- Use case: `(user_id, update_timestamp)`, you can efficiently retrieve all
  updates made by a particular user within a time range.

#### Consistent Hashing

***Consistent hashing*** is a way of evenly distributing load across an
internet-wide system of caches such as a CDN (content delivery network).
It uses randomly chosen partition boundaries to avoid the need for central
control or distributed consensus. The *consistent* here has nothing to do with
replica consistency or ACID consistency, but rather describes a particular
approach to rebalancing.

⚠️ This approach doesn't work very well for databases, so it is rarely used in
practice.

### Skewed Workloads and Relieving Hot Spots

There is an extreme case where all reads and writes are for the same key.
e.g. a celebrity user with millions of followers may cause a storm of activity.
In this case, hashing the key doesn't help.

Currently, most data systems are not able to automatically compensate for such a
highly skewed workload, so the application has to do the work to reduce the
skew.

- e.g. if one key is known to be very hot, a simple technique is to add a random
  number to the beginnng or end of the key. Each number generates a different
  key.
  - Reads have to read the data from all keys and combine it.
  - You need some way of keeping track of which keys are being split.

## Partitioning and Secondary Indexes

A secondary index usually doesn't identify a record uniquely but rather is a way
of searching for occurrences of a particular value. e.g.

- find all actions by user 123
- find all articles containing a specific word
- ...

Many key-value stores (e.g. HBase) have avoided secondary indexes because of
their added implementation complexity, but some (e.g. Riak) have started adding
them because they are so useful for data modeling.

The problem with secondary indexes is that they don't map neatly to partitions.
There are two main approaches to partitioning a database with secondary indexes:

- document-based partitioning
- term-based partitioning

### Partitioning Secondary Indexes by Document

Each partition maintains its own secondary indexes, covering only the documents
in that partition. Whenever you need to write to the database (add, remove, or
update a document) you only need to deal with the partition that contains the
document ID that you are writing. For that reason, a document-partitioned index
is also known as a **local index**.

Reading from a document-partitioned index requires care: you need to send the
query to all partitions, and combine all the results.

This approach to querying a partitioned database is known as
***scatter/gather***, and it can make read queries on secondary indexes quite
expensive. Nevertheless, it is widely used: MongoDB, Riak, Cassandra,
Elasticsearch, SolrCloud, and VoltDB all use document-partitioned secondary
indexes.

### Partitioning Secondary Indexes by Term

A ***global index*** covers data in all partitions. It must also be partitioned,
but it can be partitioned differently from the primary key index.

- e.g. red cars from all partitions appear under `color:red` in the index, but
  the index is partitioned so that colors starting with the letters `a` to `r`
  appear in partition `0` and colors starting with `s` to `z` appear in
  partition `1`.

This kind of index is called ***term-partitioned***, because the term we're
looking for determines the partition of the index.

As before, the index can be partitioned by the term itself, or using a hash of
term.

- by the term: useful for range scans
- by the hash of term: gives a more even distribution of load

The advantage of a global index over a local index is that it can make read more
efficient: a client only needs to make a request to the partition containing the
term that it wants.

The downside of a global index is that writes are slower and more complicated,
because a write to a single document may now affect multiple partitions of the
index (every term in the document might be on a different partition).

In an ideal world, the index would alway be up to date, and every document
written to the database would immediately be reflected in the index. However,
in a term-partitioned index, that would require a distributed transaction across
all partitions affected by a write, which is not supported in all databases.

In practice, updates to global secondary indexes are often asynchronous

## Rebalancing Partitions

The process of moving load from one node in the cluster to another is called
***rebalancing***. It is usually expected to meet some minimum requirements:

- After rebalancing, the load should be shared fairly between the nodes in the
  cluster.
- While rebalancing is happening, the database should continue accepting reads
  and writes.
- No more data than necessary should be moved between nodes, to make rebalancing
  fast and to minimize the network and disk I/O load.

### Strategies for Rebalancing

#### How not to do it: hash mod N

The problem with the `mode N` approach is that if the number of nodes `N`
changes, most of the keys will need to be moved from one node to another.
Such frequent moves make rebalancing excessively expensive. 👎

#### Fixed number of partitions

Fortunately, there is a fairly simple solution:

- Create many more partitions than there are nodes, and assign several
  partitions to each node.
- If a node is added to the cluster, the new node can *steal* a few partitions
  from every existing node until partitions are fairly distributed once again.
- If a node is removed from the cluster, the same happens in reverse.
- Only entire partitions are moved between nodes.
- The number of partitions does not change, nor does the assignment of keys to
  partitions.

The only thing that changes is the assignment of partitions to nodes. This
change of assignment is not immediate -- it takes some time to transfer a large
amount of data -- so the old assignment of partitions is used for any reads and
writes that happen while the transfer is in progress.

You can even assign more partitions to nodes that are more powerful to take a
greater share of the load.

This approach to rebalancing is used in Riak, Elasticsearch, Counchbase and
Voldemort.

In principle it's possible to split and merge partitions, a fixed number of
partitions is operationally simpler, and so many fixed-partition databases
choose not to implement partition splitting.

You need to choose the number high enough to accommodate future growth.
Choosing the right number of partitions is difficult if the total size or the
dataset is highly variable.

#### Dynamic partitioning

For databases that use key range partitioning, a fixed number of paritions with
fixed boundaries would be very inconvenient: if you got the boundaries wrong,
you could end up with all of the data in one partition and all of the other
parititions empty.

Key range-partitioned databases such as HBase and RethinkDB create partitions
dynamically.

- When a partition grows to exceed a configured size, it is split into two
  partitions so that approximately half of the data ends up on each side of the
  split.
- Conversely, if lots of data is deleted and a partition shrinks below some
  threshold, it can be merged with an adjacent partition.

An advantage of dynamic partitioning is that the number of partitions adapts to
the total data volume.

HBase and MongoDB allow an initial set of partitions to be configured on an
empty database (called ***pre-splitting***), so that it doesn't have to wait
until the database hits the threshold to have loads spread on each nodes.

- This requires that you already know what the key distribution is going to look
  like.

Dynamic partitioning is also suitable for hash-partitioned data.
MongoDB supports both key-range and hash partitioning.

#### Partitioning proportionally to nodes

In both fixed number partitioning and dynamic partitioning, the number of
partitions is independent of the number of nodes.

A third option, used by Cassandra and Ketama, is to make the number of
partitions proportional to the number of nodes -- in other words, to have a
fixed number of partitions **per node**.

- When a new node joins the cluster, it randomly chooses a fixed number of
  existing partitions to split, and then takes ownership of one half of each of
  those split partitions while leaving the other half of each partition in
  place.

In Cassandra, the default number is 256 partitions per node.

### Operations: Automatic or Manual Rebalancing

There is a gradient between fully automatic rebalancing and fully manual.
Couchbase, Riak, and Voldemort generate a suggested partition assignment
automatically, but require an administrator to commit it before it takes effect.

Fully automated rebalancing can be unpredictable. It requires rerouting requests
and moving a large amount of data from one node to another.

Such automation can be dangerours in combination with automatic failure
detection. For example, one node is overloaded and is temporarily slow to
respond to requests. The other nodes conclude that the overloaded node is dead,
and automatically rebalance the cluster. This puts additional load on the
overloaded node, other nodes, and the network, making the situation worse.

For that reason, it can be a **good** thing to have ahuman in the loop for
rebalancing.

## Request Routing

As partitions are rebalanced, the assignment of partitions to nodes changes.
How does a client know which node to connect to? This is an instance of a more
general problem called ***service discovery***.

There are a few different approaches to this problem:

1. Allow clients to contact any node. If that node coincidentally owns the
   partition to which the request applies, it can handle the request directly;
   otherwise, it forwards the request to the appropriate node, receives the
   reply, and passes the reply along to the client. (doesn't seem like a good
   solution)
2. Send all requests from clients to a routing tier first, which determines the
   node that should handle each request and forwards it accordingly. This
   routing tier does not itself handle any requests; it only acts as a
   partition-aware load balancer.
3. Require that clients be aware of the partitioning and the assignment of
   partitions to nodes. In this case, a client can connect directly to the
   appropriate node, without any intermediary.

In all cases, the key problem is: how does the component making the routing
decision learn about changes in the assignment of partitions to nodes?

Many distributed data systems rely on a separate coordination service such as
ZooKeeper to keep track of this cluster metadata.

- Each node registers itself in ZooKeeper, and ZooKeeper maintains the
  authoritative mapping of partitions to nodes.
- The routing tier or the paritioning-aware client, can subscribe to this
  information in ZooKeeper.
- Whenever a partition changes ownership, or a node is added or removed,
  ZooKeeper notifies those partitioning-aware components.

Espreso uses Helix (relies on ZooKeeper) for cluster management, implementing a
routing tier. HBase, SolrCloud, and Kafka also use ZooKeeper to track partition
assignment. MongoDB has a similar architecture, but it relies on its own
*config server* implementation and *mongos* daemons as the routing tier.

Cassandra and Riak take a different approach: they use a ***gossip protocol***
among the nodes to disseminate any changes in cluster state. (approach 1)

Couchbase does not rebalance automatically. Normally it is configured with a
routing tier called *moxi*, which learns about routing changes from the cluster
nodes.

### Parallel Query Execution

***MPP (massively parallel processing)*** relational database products, often
used for analytics, are much more sophisticated in the types of queries they
support.

- A typical data warehouse query contains several join, filtering, grouping, and
  aggregation operation.
- The MPP query optimizer breaks this complex query into a number of execution
  stages and partitions, many of wich can be executed in parallel on different
  nodes of the database cluster.
