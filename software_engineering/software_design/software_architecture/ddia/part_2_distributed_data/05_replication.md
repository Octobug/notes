# 5. Replication

- [5. Replication](#5-replication)
  - [Leaders and Followers](#leaders-and-followers)
    - [Synchronous Versus Asynchronous Replication](#synchronous-versus-asynchronous-replication)
    - [Setting Up New Followers](#setting-up-new-followers)
    - [Handling Node Outages](#handling-node-outages)
      - [Follower failure: Catch-up recovery](#follower-failure-catch-up-recovery)
      - [Leader failure: Failover](#leader-failure-failover)
    - [Implementation of Replication Logs](#implementation-of-replication-logs)
      - [Statement-based replication](#statement-based-replication)
      - [Write-ahead log (WAL) shipping](#write-ahead-log-wal-shipping)
      - [Logical (row-based) log replicatoin](#logical-row-based-log-replicatoin)
      - [Trigger-based replication](#trigger-based-replication)
  - [Problems with Replication Lag](#problems-with-replication-lag)
    - [Reading Your Own Writes](#reading-your-own-writes)
    - [Monotonic Reads](#monotonic-reads)
    - [Consistent Prefix Reads](#consistent-prefix-reads)
    - [Solutions for Replication Lag](#solutions-for-replication-lag)
  - [Multi-Leader Replication](#multi-leader-replication)
    - [Use Cases for Multi-Leader Replication](#use-cases-for-multi-leader-replication)
      - [Multi-datacenter operation](#multi-datacenter-operation)
      - [Clients with offline operation](#clients-with-offline-operation)
      - [Collaborative editing](#collaborative-editing)
    - [Handling Write Conflicts](#handling-write-conflicts)

> The major difference between a thing that might go wrong and a thing that
> cannot possibly go wrong is that when a thing that cannot possibly go wrong
> gose wrong it usually turns out to be impossible to get at or repair.

***Replication*** means keeping a copy of the same data on multiple machines
that are connected via a network. Why people want to replicate data:

- To keep data geographically close to users (reduce latency)
- To allow the system to continue working even if some of its parts have failed
  (increase availability)
- To scale out the number of machines that can serve read queries (increase read
  throughput)

If the data that you're replicating does not change over time, then you just
need to copy the data to every node once. All of the difficulty in replication
lies in handling *changes* to replicated data.

Three popular algorithms for replicating changes between nodes:

- single-leader
- multi-leader
- leaderless

## Leaders and Followers

Each node that stores a copy of the database is called a ***replica***.

Every write to the database needs to be processed by every replica; otherwise,
the replicas would no longer contain the same data. The most common solution for
this is called ***leader-based replication*** (also known as *active/passive* or
*master-slave replication*).

1. One of the replicas is designated the *leader* (master or primary).
   - When clients want to write to the database, they must send their requests
     to the leader, which first writes the new data to its local storage.
2. The other replicas are known as *followers* (read replicas, slaves,
   secondaries, or hot standbys).
   - Whenever the leader writes new data to its local storage, it also sends the
     data change to all of its followers as part of a *replication log* or
     *change stream*.
   - Each follower takes the log from the leader and updates its local copy of
     the database accordingly, by applying all writes in the same order as they
     were processed on the leader.
3. When a client wants to read from the database, it can query either the leader
   or any of the followers.
   - However, writes are only accepted on the leader.

This mode of replication is a built-in feature of many relational databases,
such as PostgreSQL, MySQL. And some nonrelational databases, including MongoDB.
And distributed brokers such as Kafka.

### Synchronous Versus Asynchronous Replication

One scenario:

```graph
User .....|-------------------------|......................
    [update profile]               [ok1]

Leader .....|----------------------|..........|............
        [data change]             [ok1]      [ok2]
            [waitting for follower's ok]

Follower 1 ........|-------------|.........................
              [data change]   [ok1]

Follower 2 ..............|-----------------|...............
```                 [data change]       [ok2]
```

The replication to follower 1 is *synchronous*: the leader waits until follower
1 has confirmed. The replication to follower 2 is *asynchronous*: the leader
sends the message, but doesn't wait for a response from the follower.

Synchronous replication:

- Advantage: the follower is guaranteed to have an up-to-date copy of the data.
  - If the leader suddenly fails, the data is still available on the follower.
- Disadvantage: if the synchronous follower doesn't respond, the write cannot be
  processed.
  - That is why it is impractical for all followers to be synchronous.

***semi-synchronous***: 1 synchronous + some asynchronous

💡 Often, leader-based replication is configured to be completely asynchronous.
In this case, if the leader fails and is not recoverable, any writes that have
not yet been replicated to followers are lost.

- 👎 This means that a write is not guaranteed to be durable, even if it has
  been confirmed to be client.
- 👍 The leader can continue processing writes even if all of its followers have
  fallen behind.

### Setting Up New Followers

How do you ensure that the new follower has an accurate copy of the leader's
data?

Simply copying data files from one node to another is typically not sufficient:
clients are constantly writing to the database, and the data is always in flux.

Fortunately, setting up a follower can usually be down without downtime. In some
systems the process is even fully automated:

1. Take a consistent snapshot of the leader's database at some point in time
   without taking a lock on the entire database.
   - Most databases have this feature, as it is also required for backups.
2. Copy the snapshot to the new follower node.
3. The follower connects to the leader and requests all the data changes that
   have happened since the snapshot was taken.
   - this requires that the snapshot is associated with an exact position in the
     leader's replication log.
     - PostgreSQL: *log sequence number*
     - MySQL: *binlog coordinates*
4. When the follower has processed the backlog of data changes, it can now
   continue to process data changes from the leader.

### Handling Node Outages

#### Follower failure: Catch-up recovery

Each follower keeps a log of the data changes it has received from the leader on
its local disk. The follower can recover quite easily from its log after
failures:

- it knows the last transaction that was processed before the fault ocurred.
- it can connect to the leader and request all the data changes that occurred
  during the time when the follower was disconnected.

#### Leader failure: Failover

***Failover***: one of the followers needs to be promoted to be the new leader,
clients need to be reconfigured to send their writes to the new leader, and the
other followers need to start consuming data changes from the new leader.

An automatic failover process usually consists of the following steps:

1. **Determining that the leader has failed**. There is no foolproof way of
   detecting what has gone wrong, so most systems simply use a timeout.
2. **Choosing a new leader**. This could be done through an election process or
   a new leader could be appointed by a previously elected *controller node*.
   - The best candidate for leadership is usually the replica with the most
     up-to-date data changes from the old leader.
3. **Reconfiguring the system to use the new leader**. Clients now need to send
   their write requests to the new leader.
   - If the old leader comes back, it might still believe that it is the leader.
     The system needs to ensure that the old leader becomes a follower and
     recognizes the new leader.

Failover is fraught with things that can go wrong:

- If asynchronous replication is used, the new leader may not have received all
  the writes from the old leader before it failed.
  - What if the former leader rejoins the cluster after a new leader has been
    chosen?
  - The new leader may have received confliting writes in the meantime.
  - **The most common solution** is for the old leader's unreplicated writes to
    simply be discarded, which may violate client's durability expectations.
- Discarding writes is especially dangerous if other storage systems (e.g.
  Redis) outside of the database need to be coordinated with the database
  contents.
- In certain fault scenarios, it could happen that two nodes both believe that
  they are the leader. This situation is called ***split brain***. If both
  leaders accept writes, and there is no process for resolving conflicts, data
  is likely to be lost or corrupted.
  - As a safety catch, some systems have a mechanism to shut down one node if
    two leaders are detected.
- A longer timeout means a longer time to recovery in the case where the leader
  fails. However, if the timeout is too short, there could be unnecessary
  failovers.

For the difficulties above, some operation teams prefer to perform failovers
**manually**, even if the software supports automatic failover.

### Implementation of Replication Logs

#### Statement-based replication

In the simplest case, the leader logs every write request and sends that
statement log to its followers. For a relational database, this means that
every `INSERT`, `UPDATE`, or `DELETE` statement is forwarded to followers, and
each follower executes that SQL statement.

There are various ways in which this approach to replication can break down:

- Any statement that calls a nondeterministic function, such as `NOW()` to get
  the current date and time or `RAND()` to get a random number, is likely to
  generate a different value on each replica.
- If statements use an autoincrementing column, or if they depend on the
  existing data, they must be executed in exactly the same order on each
  replica. This can be limiting when there are multiple concurrently executing
  transactions.
- Nondeterministic side effects made by statements may be different on each
  replica.

By default MySQL (since version 5.1) uses row-based replication if there is any
nondeterminism in a statement.

#### Write-ahead log (WAL) shipping

Every write is appended to a log:

- For a log-structured storage engine, this log is the main place for storage.
  Log segments are compacted and garbage-collected in the background.
- In the case of a B-tree, every modification is first written to a write-ahead
  log so that the index can be restored to a consistent state after a crash.

In either case, the log is an append-only sequence of bytes containing all
writes to the database. Besides writing this log to disk, the leader also sends
it across the network to its followers.

The main disadvantage is that the log describes the data on a very low level: a
WAL contains details of which bytes were changed in which disk blocks. This
makes replication closely coupled to the storage engine: it is difficult to
perform a zero-downtime upgrade of the database software if the replication
protocol does not allow a version mismatch between the leader and the followers.

#### Logical (row-based) log replicatoin

> Seems this one is preferred.

An alternative is to use different log formats for replication and for the
storage engine. This kind of replication log is called a ***logical log***, to
distinguish it from the storage engine's (*physical*) data representation.

A logical log for a relational database is usually a sequence of records
describing writes to database tables at the granularity of a row:

- For a inserted row, the log contains the new values of all columns.
- For a deleted row, the log contains enough information (typically the primary
  key) to uniquely identify the row that was deleted. If there is no primary key
  on the table, the old values of all columns need to be logged.
- For an updated row, the log contains enough information to uniquely indentify
  the updated row, and the new values of all columns.
- A transaction that modifies several rows needs an extra record indicating that
  the transaction was committed.

MySQL's binlog uses this approach when configured to use row-based replication.

#### Trigger-based replication

In some cases, you may need to move replication up to the application layer:

- You want to replicate a subset of the data
- You want to replicate from one kind of database to another
- You need conflit resolution logic

There are tools (e.g. Oracle GoldenGate) that can make data changes available
to an application by reading the database log.

An alternative is to use features that are available in many relational
databases: *triggers* and *stored procedures*.

- A trigger lets you register custom application code that is automatically
  executed when a data change occurs in a database.
  - So that you could log this change into a separate table, from which it can
    be read by the application.
- Trigger-based replicaction typically has greater overheads, and is more prone
  to bugs and limitations than other replication methods.

## Problems with Replication Lag

***Read-scaling*** architecture: leader-based replication with many followers.
This approach only works with asynchronous (or semi-synchronous) replication.

***Inconsistency***: if an application reads from an *asynchronous* follower,
it may see outdated information. But if you stop writing and wait a while, the
followers will eventually catch up and become consistent with the leader. This
effect is called ***eventual consistency***.

### Reading Your Own Writes

With asynchronous replication: the new data may not yet have reached the
replica from which the user reads the data created shortly before. To the user,
it looks as though the data they submitted was lost.

In this situation, ***read-after-write consistency*** (also known as
***read-your-writes*** consistency) is needed. It makes no promises about other
users.

How to:

- When reading something that the user may have modified, read it from the
  leader.
  - This requires that you know whether something might have been modified
    without actually querying it.
  - e.g. always read the user's own profile from the leader.
- If most things in the application are potentially editable by the user, most
  things would have to be read from the leader.
  - Use other criteria to decide whether to read from the leader.
  - e.g. track the last update time and, for `1` minute after the last update,
    make all reads from the leader.
- The client can remember the timestamp of its most recent write, then the
  system can ensure that the replica serving any reads for that user reflects
  updates at least until that timestamp. The timestamp could be *logical*
  (e.g. the log sequence number).

Another complication arises when the same user is accessing your service from
multiple devices. In this case you may want to provide *cross-device*
read-after-write consistency:

- The timestamp approach needs to make the timestamp info centralized.
- Requests from all of a user's devices need to be routed to the same
  datacenter.

### Monotonic Reads

It's possible for a user to see things *moving backward in time* when reading
from asynchronous followers.

***Monotonic reads*** is a guarantee that this kind of anomaly does not happen.
It's a lesser guarantee than strong consistency, but a stronger guarantee than
eventual consistency.

- When you read data, you may see an old value;
- monotonic reads only means that if one user makes several reads in sequence,
  they will not see time go backward.

How to: make sure that each user always makes their reads from the same replica.

### Consistent Prefix Reads

If some partitions are replicated slower than others, an observer may see the
answer before they see the question.

***Consistent prefix reads*** is used to prevent this kind of anomaly. This
guarantee says that if a sequence of writes happens in a certain order, then
anyone reading those writes will see them appear in the same order.

How to: make sure that any writes that are causally related to each other are
written to the same partition - but in some applications that cannot be done
efficiently.

### Solutions for Replication Lag

Performing certain kinds of reads on the leader (e.g. read-after-write) can
provide a stronger gurantee. However, dealing with these issues in application
level is complex and easy to get wrong.

***transactions*** are a way for a database to provide stronger guarantees so
that the application can be simpler.

## Multi-Leader Replication

Leader-based replication has one major downdside: all writes must go through the
single leader.

***Multi-leader replication***: allow more than one node to accept writes, each
node that processes a write must forward that data change to all the other
nodes (also known as *master-master* or *active/active* replication).

### Use Cases for Multi-Leader Replication

It rarely makes sense to use a multi-leader setup within a single datacenter.
However, there are some situations in which this configuration is reasonable.

#### Multi-datacenter operation

Within each datacenter, regular leader-follower replication is used; between
datacenters, each datacenter's leader replicates its changes to the leaders in
other datacenters.

**single-leader vs. multi-leader**:

- Performance
  - Single: every write must go over the internet to the leader.
  - Multi: every write can be processed in the local datacenter and is
    replicated asynchronously to the other datacenters. Thus, the
    inter-datacenter network delay is hidden from users.
- Tolerance of datacenter outages
  - Single: if the datacenter with the leader fails, failover can promote a
    follower in another datacenter to be leader.
  - Multi: each datacenter can continue operating independently of the others,
    and replication catches up when the failed datacenter comes back online.
- Tolerance of network problems
  - Single: is very sensitive to problems in the inter-datacenter link.
  - Multi: with asynchronous replication, it can usually tolerate network
    problems better.

How-to:

- MySQL: Tungsten Replicator
- PostgreSQL: BDR
- Oracle: GoldenGate

Big downside: the same data may be concurrently modified in two different
datacenters, and those write conflicts must be resolved.

Autoincrementing keys, triggers, and integrity constraints are often problematic
with multi-leader replication. For this reason, it is often considered dangerous
and should be avoided if possible.

#### Clients with offline operation

Multi-leader is appropriate if you have an application that needs to continue to
work while it is offline.

In the calendar apps on mobile phones, every device has a local database that
acts as a leader (it accepts write requests), and there is an asynchronous
multi-leader replication process (sync calendar data) between the replicas of
your calendar on all of your devices. Each device is a "datacenter".

CouchDB is designed for multi-leader replication.

#### Collaborative editing

Collaborative editing has a lot in common with the offline editing use case.

No editing conflicts model: the application obtains a lock on the document
before a user can edit it. Only after the user editing the document has
committed their changes and released the lock, other users can edit it.

- This model is equivalent to single-leader replication with transaction on the
leader.

### Handling Write Conflicts

>>>>> progress
