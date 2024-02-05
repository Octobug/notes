# 9. Consistency and Consensus

> Is it better to be alive and wrong or right and dead?
>
> —Jay Kreps, A Few Notes on Kafka and Jepsen (2013)

- [9. Consistency and Consensus](#9-consistency-and-consensus)
  - [Consistency Guarantees](#consistency-guarantees)
  - [Linearizability](#linearizability)
    - [What Makes a System Linearizable?](#what-makes-a-system-linearizable)
      - [Linearizability Versus Serializability](#linearizability-versus-serializability)
    - [Relying on Linearizability](#relying-on-linearizability)

The simplest way of handling faults is to simply let the entire service fail,
and show the user an error message. If that solution is unacceptable, we need
to find ways of tolerating faults—that is, of keeping the service functioning
correctly, even if some internal component is faulty.

The best way of building fault-tolerant systems is to find some general-purpose
abstractions with useful guarantees, implement them once, and then let
applications rely on those guarantees. This is the same approach as we used
with transactions: by using a transaction, the application can pretend that
there are no crashes (`atomicity`), that nobody else is concurrently accessing
the database (`isolation`), and that storage devices are perfectly reliable
(`durability`). Even though crashes, race conditions, and disk failures do
occur, the transaction abstraction hides those problems so that the application
doesn’t need to worry about them.

One of the most important abstractions for distributed systems is consensus:
that is, getting all of the nodes to agree on something.

Once you have an implementation of consensus, applications can use it for
various purposes. For example, say you have a database with single-leader
replication. If the leader dies and you need to fail over to another node, the
remaining database nodes can use consensus to elect a new leader. If two nodes
both believe that they are the leader, that situation is called split brain,
and it often leads to data loss. Correct implementations of consensus help
avoid such problems.

## Consistency Guarantees

Most replicated databases provide at least ***eventual consistency***, which
means that if you stop writing to the database and wait for some unspecified
length of time, then eventually all read requests will return the same value.
In other words, the inconsistency is temporary, and it eventually resolves
itself. A better name for eventual consistency may be ***convergence***, as we
expect all replicas to eventually converge to the same value.

Systems with stronger guarantees may have worse performance or be less
fault-tolerant than systems with weaker guarantees. Nevertheless, stronger
guarantees can be appealing because they are easier to use correctly.

There is some similarity between distributed consistency models and the
hierarchy of transaction isolation levels. But while there is some overlap,
they are mostly independent concerns:

- Transaction isolation is primarily about avoiding race conditions due to
  concurrently executing transactions
- Distributed consistency is mostly about coordinating the state of replicas in
  the face of delays and faults.

## Linearizability

Wouldn’t it be a lot simpler if the database could give the illusion that there
is only one replica? Then every client would have the same view of the data.

This is the idea behind ***linearizability*** (also known as
***atomic consistency***, ***strong consistency***, ***immediate consistency***,
or ***external consistency***). The basic idea is to make a system appear as if
there were only one copy of the data, and all operations on it are atomic.

In a linearizable system, as soon as one client successfully completes a write,
all clients reading from the database must be able to see the value just
written. Maintaining the illusion of a single copy of the data means
guaranteeing that the value read is the most recent, up-to-date value, and
doesn’t come from a stale cache or replica. In other words, linearizability is
a ***recency guarantee***.

![09_01_not_linearizable_system](../images/09_01_not_linearizable_system.png)

If Alice and Bob had hit reload at the same time, it would have been less
surprising if they had gotten two different query results, because they
wouldn’t know at exactly what time their respective requests were processed by
the server. However, Bob knows that he hit the reload button after he heard
Alice exclaim the final score, and therefore he expects his query result to be
at least as recent as Alice’s. The fact that his query returned a stale result
is a violation of linearizability.

### What Makes a System Linearizable?

The basic idea behind linearizability is simple: to make a system appear as if
there is only a single copy of the data.

In the distributed systems literature, `x` is called a ***register*** — in
practice, it could be one key in a key-value store, one row in a relational
database, or one document in a document database, for example.

![09_02_read_with_write](../images/09_02_read_with_write.png)

The start of a bar is the time when the request was sent, and the end of a bar
is when the response was received by the client. Due to variable network
delays, a client doesn’t know exactly when the database processed its
request — it only knows that it must have happened sometime between the client
sending the request and receiving the response.

In this example, the `register` has two types of operations:

- `read(x) ⇒ v` means the client requested to read the value of register `x`,
  and the database returned the value `v`.
- `write(x, v) ⇒ r` means the client requested to set the register `x` to value
  `v`, and the database returned response `r` (which could be `ok` or `error`).

What are the possible responses that `A` and `B` might get for their read
requests?

1. The first read operation by `client A` completes before the write begins, so
  it must definitely return the old value `0`.
2. The last read by `client A` begins after the write has completed, so it must
  definitely return the new value `1` if the database is ***linearizable***: we
  know that the write must have been processed sometime between the start and
  end of the write operation, and the read must have been processed sometime
  between the start and end of the read operation. If the read started after
  the write ended, then the read must have been processed after the write, and
  therefore it must see the new value that was written.
3. Any read operations that overlap in time with the write operation might
  return either `0` or `1`, because we don’t know whether or not the write has
  taken effect at the time when the read operation is processed.

第三种情况不满足 linearizability: if reads that are concurrent with a write can
return either the old or the new value, then readers could see a value flip
back and forth between the old and the new value several times while a write is
going on. That is not what we expect of a system that emulates a “single copy
of the data.”

- A register in which reads may return either the old or the new value if they
  are concurrent with a write is known as a ***regular register***.

To make the system linearizable, we need to add another constraint:

![09_03_all_reads_return_the_new](../images/09_03_all_reads_return_the_new.png)

In a linearizable system we imagine that there must be some point in time
(between the start and end of the write operation) at which the value of `x`
atomically flips from `0` to `1`. Thus, if one client’s read returns the new
value `1`, all subsequent reads must also return the new value, even if the
write operation has not yet completed.

`Client A` is the first to read the new value, `1`. Just after `A`’s read
returns, `B` begins a new read. Since `B`’s read occurs strictly after `A`’s
read, it must also return `1`, even though the write by `C` is still ongoing.

A more complex example of non-linearizability:

![09_04_reads_and_writes_appear_to_have_taken_effect](../images/09_04_reads_and_writes_appear_to_have_taken_effect.png)

- `cas(x, v_old, v_new) ⇒ r` means the client requested an atomic
  compare-and-set operation. If the current value of the register `x` equals
  `v_old`, it should be atomically set to `v_new`. If `x ≠ v_old` then the
  operation should leave the register unchanged and return an error. `r` is the
  database’s response (`ok` or `error`).
  - 可以理解为原子性的自增操作，如果旧值已发生变化，则自增失败。

Each operation in Figure 9-4 is marked with a vertical line at the time when we
think the operation was executed. Those markers are joined up in a sequential
order, and the result must be a valid sequence of reads and writes for a
`register` (every read must return the value set by the most recent write).

***The requirement of linearizability*** is that the lines joining up the
operation markers always move forward in time, never backward. This requirement
ensures the recency guarantee: once a new value has been written or read, all
subsequent reads see the value that was written, until it is overwritten again.

- First `client B` sent a request to read `x`, then `client D` sent a request
  to set `x` to `0`, and then `client A` sent a request to set `x` to `1`.
  Nevertheless, the value returned to `B`’s read is `1` (the value written by
  `A`). This is okay: it means that the database first processed `D`’s write,
  then `A`’s write, and finally `B`’s read. Although this is not the order in
  which the requests were sent, it’s an acceptable order, because the three
  requests are concurrent. Perhaps `B`’s read request was slightly delayed in
  the network, so it only reached the database after the two writes.
- `Client B`’s read returned `1` before `client A` received its response from
  the database, saying that the write of the value `1` was successful. This is
  also okay: it doesn’t mean the value was read before it was written, it just
  means the `ok` response from the database to `client A` was slightly delayed
  in the network.
- This model doesn’t assume any transaction isolation: another client may
  change a value at any time. For example, `C` first reads `1` and then reads
  `2`, because the value was changed by `B` between the two reads. An atomic
  `compare-and-set (cas)` operation can be used to check the value hasn’t been
  concurrently changed by another client: `B` and `C`’s `cas` requests succeed,
  but `D`’s cas request fails (by the time the database processes it, the value
  of `x` is no longer `0`).
- The final read by client `B` is not linearizable. The operation is concurrent
  with `C`’s cas write, which updates `x` from `2` to `4`. In the absence of
  other requests, it would be okay for `B`’s read to return `2`. However,
  `client A` has already read the new value `4` before `B`’s read started, so
  `B` is not allowed to read an older value than `A`.

It is possible (though computationally expensive) to test whether a system’s
behavior is linearizable by recording the timings of all requests and
responses, and checking whether they can be arranged into a valid sequential
order.

#### Linearizability Versus Serializability

`Linearizability` is easily confused with `serializability`, as both words seem
to mean something like “can be arranged in a sequential order.” However, they
are two quite different guarantees, and it is important to distinguish between
them:

- `Serializability`: `Serializability` is an isolation property of
  transactions, where every transaction may read and write multiple objects
  (rows, documents, records) - “Single-Object and Multi-Object Operations”. It
  guarantees that transactions behave the same as if they had executed in some
  serial order (each transaction running to completion before the next
  transaction starts). It is okay for that serial order to be different from
  the order in which transactions were actually run.
- `Linearizability`: `Linearizability` is a recency guarantee on reads and
  writes of a `register` (an individual object). It doesn’t group operations
  together into transactions, so it does not prevent problems such as write
  skew, unless you take additional measures such as materializing conflicts.

A database may provide both `serializability` and `linearizability`, and this
combination is known as `strict serializability` or
`strong one-copy serializability (strong-1SR)`. Implementations of
serializability based on two-phase locking or actual serial execution are
typically `linearizable`.

However, serializable snapshot isolation (SSI) is not linearizable: by design,
it makes reads from a consistent snapshot, to avoid lock contention between
readers and writers. The whole point of a consistent snapshot is that it does
not include writes that are more recent than the snapshot, and thus reads from
the snapshot are not linearizable.

### Relying on Linearizability

>>>>> progress
