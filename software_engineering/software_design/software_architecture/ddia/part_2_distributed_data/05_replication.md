# 5. Replication

- [5. Replication](#5-replication)
  - [Leaders and Followers](#leaders-and-followers)
    - [Synchronous Versus Asynchronous Replication](#synchronous-versus-asynchronous-replication)
    - [Setting Up New Followers](#setting-up-new-followers)

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

>>>>> progress
