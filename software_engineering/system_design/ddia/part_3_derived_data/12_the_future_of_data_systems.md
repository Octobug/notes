# 12. The Future of Data Systems

> If a thing be ordained to another as to its end, its last end cannot consist
> in the preservation of its being. Hence a captain does not intend as a last
> end, the preservation of the ship entrusted to him, since a ship is ordained
> to something else as its end, viz. to navigation. (Often quoted as: If the
> highest aim of a captain was the preserve his ship, he would keep it in port
> forever.)
>
> —St. Thomas Aquinas, Summa Theologica (1265–1274)

- [12. The Future of Data Systems](#12-the-future-of-data-systems)
  - [Data Integration](#data-integration)
    - [Combining Specialized Tools by Deriving Data](#combining-specialized-tools-by-deriving-data)
      - [Reasoning about dataflows](#reasoning-about-dataflows)
      - [Derived data versus distributed transactions](#derived-data-versus-distributed-transactions)
      - [The limits of total ordering](#the-limits-of-total-ordering)
      - [Ordering events to capture causality](#ordering-events-to-capture-causality)
    - [Batch and Stream Processing](#batch-and-stream-processing)
      - [Maintaining derived state](#maintaining-derived-state)
      - [Reprocessing data for application evolution](#reprocessing-data-for-application-evolution)
      - [The lambda architecture](#the-lambda-architecture)
      - [Unifying batch and stream processing](#unifying-batch-and-stream-processing)
  - [Unbundling Databases](#unbundling-databases)

## Data Integration

It’s hard enough to get one code path robust and performing well — trying to do
everything in one piece of software almost guarantees that the implementation
will be poor.

Every piece of software, even a so-called “general-purpose” database, is
designed for a particular usage pattern.

There is another challenge: in complex applications, data is often used in
several different ways. There is unlikely to be one piece of software that is
suitable for all the different circumstances in which the data is used, so you
inevitably end up having to cobble together several different pieces of
software in order to provide your application’s functionality.

### Combining Specialized Tools by Deriving Data

#### Reasoning about dataflows

- If **change data capture (CDC)** is the only way of updating the index, you
  can be confident that the index is entirely derived from the system of
  record, and therefore consistent with it (barring bugs in the software).
- Allowing the application to directly write to both the search index and the
  database introduces the problem in which two clients concurrently send
  conflicting writes, and the two storage systems process them in a different
  order.
  - In this case, neither the database nor the search index is “in charge” of
    determining the order of writes, and so they may make contradictory
    decisions and become permanently inconsistent with each other.
- If it is possible for you to funnel all user input through a single system
  that decides on an ordering for all writes, it becomes much easier to derive
  other representations of the data by processing the writes in the same order.
- Updating a derived data system based on an event log can often be made
  deterministic and idempotent, making it quite easy to recover from faults.

#### Derived data versus distributed transactions

The classic approach for keeping different data systems consistent with each
other involves ***distributed transactions***

- Atomic Commit
- Two-Phase Commit (2PC)

How does the approach of using derived data systems fare in comparison to
distributed transactions?

- **Distributed transactions** decide on an ordering of writes by using locks
  for mutual exclusion, while **CDC** and **event sourcing** use a log for
  ordering. Distributed transactions use **atomic commit** to ensure that
  changes take effect exactly once, while log-based systems are often based on
  deterministic retry and idempotence.
- The biggest difference is that transaction systems usually provide
  linearizability, which implies useful guarantees such as reading your own
  writes. On the other hand, derived data systems are often updated
  asynchronously, and so they do not by default offer the same timing
  guarantees.

However, I think that XA has poor fault tolerance and performance
characteristics, which severely limit its usefulness.

In the absence of widespread support for a good distributed transaction
protocol, I believe that log-based derived data is the most promising approach
for integrating different data systems.

#### The limits of total ordering

- In most cases, constructing a totally ordered log requires all events to pass
  through a ***single leader node*** that decides on the ordering. If the
  throughput of events is greater than a single machine can handle, you need to
  partition it across multiple machines. The order of events in two different
  partitions is then ambiguous.
- If the servers are spread across multiple ***geographically distributed***
  datacenters, in order to tolerate an entire datacenter going offline, you
  typically have a separate leader in each datacenter, because network delays
  make synchronous cross-datacenter coordination inefficient. This implies an
  undefined ordering of events that originate in two different datacenters.
- When applications are deployed as ***microservices***, a common design choice
  is to deploy each service and its durable state as an independent unit, with
  no durable state shared between services. When two events originate in
  different services, there is no defined order for those events.
- Some applications maintain client-side state that is updated immediately on
  user input (without waiting for confirmation from a server), and even
  continue to work offline. With such applications, clients and servers are
  very likely to see events in different orders.

In formal terms, deciding on a total order of events is known as
***total order broadcast***, which is equivalent to consensus. Most consensus
algorithms are designed for situations in which the throughput of a single node
is sufficient to process the entire stream of events, and these algorithms do
not provide a mechanism for multiple nodes to share the work of ordering the
events. It is still an open research problem to design consensus algorithms
that can scale beyond the throughput of a single node and that work well in a
geographically distributed setting.

#### Ordering events to capture causality

In cases where there is no causal link between events, the lack of a total
order is not a big problem, since concurrent events can be ordered arbitrarily.
Some other cases are easy to handle: for example, when there are multiple
updates of the same object, they can be totally ordered by routing all updates
for a particular object ID to the same log partition. However, causal
dependencies sometimes arise in more subtle ways.

For example, consider a social networking service, and two users who were in a
relationship but have just broken up. One of the users removes the other as a
friend, and then sends a message to their remaining friends complaining about
their ex-partner. The user’s intention is that their ex-partner should not see
the rude message, since the message was sent after the friend status was
revoked.

However, in a system that stores friendship status in one place and messages in
another place, that ordering dependency between the `unfriend` event and
the `message-send` event may be lost. If the causal dependency is not captured,
a service that sends notifications about new messages may process the
`message-send` event before the `unfriend` event, and thus incorrectly send a
notification to the ex-partner.

In this example, the notifications are effectively a join between the messages
and the friend list, making it related to the timing issues of joins.
Unfortunately, there does not seem to be a simple answer to this problem.
Starting points include:

- Logical timestamps can provide total ordering without coordination, so they
  may help in cases where total order broadcast is not feasible. However, they
  still require recipients to handle events that are delivered out of order,
  and they require additional metadata to be passed around.
- If you can log an event to record the state of the system that the user saw
  before making a decision, and give that event a unique identifier, then any
  later events can reference that event identifier in order to record the
  causal dependency.
- Conflict resolution algorithms help with processing events that are delivered
  in an unexpected order. They are useful for maintaining state, but they do
  not help if actions have external side effects.

### Batch and Stream Processing

Spark performs stream processing on top of a batch processing engine by
breaking the stream into microbatches, whereas Apache Flink performs batch
processing on top of a stream processing engine. In principle, one type of
processing can be emulated on top of the other, although the performance
characteristics vary: for example, microbatching may perform poorly on hopping
or sliding windows.

#### Maintaining derived state

Batch processing has a quite strong functional flavor: it encourages
deterministic, pure functions whose output depends only on the input and which
have no side effects other than the explicit outputs, treating inputs as
immutable and outputs as append-only. Stream processing is similar, but it
extends operators to allow managed, fault-tolerant state.

The principle of deterministic functions with well-defined inputs and outputs
is not only good for fault tolerance, but also simplifies reasoning about the
dataflows in an organization.

In principle, derived data systems could be maintained synchronously, just like
a relational database updates secondary indexes synchronously within the same
transaction as writes to the table being indexed. However, asynchrony is what
makes systems based on event logs robust: it allows a fault in one part of the
system to be contained locally, whereas distributed transactions abort if any
one participant fails, so they tend to amplify failures by spreading them to
the rest of the system.

A partitioned system with secondary indexes either needs to send writes to
multiple partitions (if the index is term-partitioned) or send reads to all
partitions (if the index is document-partitioned). Such cross-partition
communication is also most reliable and scalable if the index is maintained
asynchronously.

#### Reprocessing data for application evolution

Stream processing allows changes in the input to be reflected in derived views
with low delay, whereas batch processing allows large amounts of accumulated
historical data to be reprocessed in order to derive new views onto an existing
dataset.

With reprocessing it is possible to restructure a dataset into a completely
different model in order to better serve new requirements.

If you want to restructure a dataset, you do not need to perform the migration
as a sudden switch. Instead, you can maintain the old schema and the new schema
side by side as two independently derived views onto the same underlying data.
You can then start shifting a small number of users to the new view in order to
test its performance and find any bugs, while most users continue to be routed
to the old view. Gradually, you can increase the proportion of users accessing
the new view, and eventually you can drop the old view.

The beauty of such a gradual migration is that every stage of the process is
easily reversible if something goes wrong: you always have a working system to
go back to.

#### The lambda architecture

If batch processing is used to reprocess historical data, and stream processing
is used to process recent updates, then how do you combine the two? The lambda
architecture is a proposal in this area that has gained a lot of attention.

The core idea of the lambda architecture is that incoming data should be
recorded by appending immutable events to an always-growing dataset, similarly
to event sourcing. From these events, read-optimized views are derived. The
lambda architecture proposes running two different systems in parallel: a batch
processing system such as Hadoop MapReduce, and a separate stream-processing
system such as Storm.

In the lambda approach, the stream processor consumes the events and quickly
produces an approximate update to the view; the batch processor later consumes
the **same** set of events and produces a corrected version of the derived view.
The reasoning behind this design is that batch processing is simpler and thus
less prone to bugs, while stream processors are thought to be less reliable and
harder to make fault-tolerant. Moreover, the stream process can use fast
approximate algorithms while the batch process uses slower exact algorithms.

The lambda architecture was an influential idea that shaped the design of data
systems for the better, particularly by popularizing the principle of deriving
views onto streams of immutable events and reprocessing events when needed.
However, I also think that it has a number of practical problems:

- Having to maintain the same logic to run both in a batch and in a stream
  processing framework is significant additional effort. Although libraries
  such as Summingbird provide an abstraction for computations that can be run
  in either a batch or a streaming context, the operational complexity of
  debugging, tuning, and maintaining two different systems remains.
- Since the stream pipeline and the batch pipeline produce separate outputs,
  they need to be merged in order to respond to user requests. This merge is
  fairly easy if the computation is a simple aggregation over a tumbling
  window, but it becomes significantly harder if the view is derived using more
  complex operations such as joins and sessionization, or if the output is not
  a time series.
- Although it is great to have the ability to reprocess the entire historical
  dataset, doing so frequently is expensive on large datasets. Thus, the batch
  pipeline often needs to be set up to process incremental batches (e.g., an
  hour’s worth of data at the end of every hour) rather than reprocessing
  everything. This raises the problems such as handling stragglers and handling
  windows that cross boundaries between batches. Incrementalizing a batch
  computation adds complexity, making it more akin to the streaming layer,
  which runs counter to the goal of keeping the batch layer as simple as
  possible.

#### Unifying batch and stream processing

More recent work has enabled the benefits of the lambda architecture to be
enjoyed without its downsides, by allowing both batch computations
(reprocessing historical data) and stream computations (processing events as
they arrive) to be implemented in the same system.

Unifying batch and stream processing in one system requires the following
features, which are becoming increasingly widely available:

- The ability to replay historical events through the same processing engine
  that handles the stream of recent events. For example, log-based message
  brokers have the ability to replay messages, and some stream processors can
  read input from a distributed filesystem like HDFS.
- Exactly-once semantics for stream processors — that is, ensuring that the
  output is the same as if no faults had occurred, even if faults did in fact
  occur. Like with batch processing, this requires discarding the partial
  output of any failed tasks.
- Tools for windowing by event time, not by processing time, since processing
  time is meaningless when reprocessing historical events. For example, Apache
  Beam provides an API for expressing such computations, which can then be run
  using Apache Flink or Google Cloud Dataflow.

## Unbundling Databases
