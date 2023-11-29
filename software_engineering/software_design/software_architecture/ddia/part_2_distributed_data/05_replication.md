# 5. Replication

- [5. Replication](#5-replication)
  - [Leaders and Followers](#leaders-and-followers)
    - [Synchronous Versus Asynchronous Replication](#synchronous-versus-asynchronous-replication)
    - [Setting Up New Followers](#setting-up-new-followers)
    - [Handling Node Outages](#handling-node-outages)
      - [Follower failure: Catch-up recovery](#follower-failure-catch-up-recovery)
      - [Leader failure: Failover](#leader-failure-failover)
    - [Implementation of Replication Logs](#implementation-of-replication-logs)

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

>>>>> progress
