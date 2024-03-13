# 11. Stream Processing

> A complex system that works is invariably found to have evolved from a simple
> system that works. The inverse proposition also appears to be true: A complex
> system designed from scratch never works and cannot be made to work.
>
> —John Gall, Systemantics (1975)

- [11. Stream Processing](#11-stream-processing)
  - [Transmitting Event Streams](#transmitting-event-streams)
    - [Messaging Systems](#messaging-systems)
      - [Direct messaging from producers to consumers](#direct-messaging-from-producers-to-consumers)
      - [Message brokers](#message-brokers)
      - [Message brokers compared to databases](#message-brokers-compared-to-databases)
      - [Multiple consumers](#multiple-consumers)
      - [Acknowledgments and redelivery](#acknowledgments-and-redelivery)
    - [Partitioned Logs](#partitioned-logs)
      - [Using logs for message storage](#using-logs-for-message-storage)
      - [Logs compared to traditional messaging](#logs-compared-to-traditional-messaging)

Batch processing—techniques read a set of files as input and produce a new set
of output files. The output is a form of ***derived data***; that is, a dataset
that can be recreated by running the batch process again if necessary.

One big assumption remained throughout batch processing: namely, that the input
is bounded — i.e., of a known and finite size — so the batch process knows when
it has finished reading its input.

In reality, a lot of data is unbounded because it arrives gradually over time.
Thus, batch processors must artificially divide the data into chunks of fixed
duration: for example, processing a day’s worth of data at the end of every
day, or processing an hour’s worth of data at the end of every hour.

The problem with daily batch processes is that changes in the input are only
reflected in the output a day later, which is too slow for many impatient
users. To reduce the delay, we can run the processing more frequently — say,
processing a second’s worth of data at the end of every second — or even
continuously, abandoning the fixed time slices entirely and simply processing
every event as it happens. That is the idea behind ***stream processing***.

In general, a “stream” refers to data that is incrementally made available over
time. The concept appears in many places: in the `stdin` and `stdout` of Unix,
programming languages (lazy lists), filesystem APIs (such as Java’s
`FileInputStream`), TCP connections, delivering audio and video over the
internet, and so on.

***Event streams*** as a data management mechanism: the unbounded,
incrementally processed counterpart to the batch data.

## Transmitting Event Streams

In the batch processing world, the inputs and outputs of a job are files
(perhaps on a distributed filesystem). What does the streaming equivalent look
like?

When the input is a file (a sequence of bytes), the first processing step is
usually to parse it into a sequence of records. In a stream processing context,
a record is more commonly known as an ***event***, but it is essentially the
same thing: a small, self-contained, immutable object containing the details of
something that happened at some point in time. An event usually contains a
timestamp indicating when it happened according to a time-of-day clock.

For example, the thing that happened might be an action that a user took, such
as viewing a page or making a purchase. It might also originate from a machine,
such as a periodic measurement from a temperature sensor, or a CPU utilization
metric.

An event may be encoded as a text string, or JSON, or perhaps in some binary
form.

In batch processing, a file is written once and then potentially read by
multiple jobs. Analogously, in streaming terminology, an event is generated
once by a ***producer*** (***publisher*** or ***sender***), and then
potentially processed by multiple ***consumers*** (***subscribers*** or
***recipients***). In a filesystem, a filename identifies a set of related
records; in a streaming system, related events are usually grouped together
into a ***topic*** or ***stream***.

In principle, a file or database is sufficient to connect producers and
consumers: a producer writes every event that it generates to the datastore,
and each consumer periodically polls the datastore to check for events that
have appeared since it last ran. This is essentially what a batch process does
when it processes a day’s worth of data at the end of every day.

However, when moving toward continual processing with low delays, polling
becomes expensive if the datastore is not designed for this kind of usage. The
more often you poll, the lower the percentage of requests that return new
events, and thus the higher the overheads become. Instead, it is better for
consumers to be notified when new events appear.

Databases have traditionally not supported this kind of notification mechanism
very well: relational databases commonly have triggers, which can react to a
change, but they are very limited in what they can do and have been somewhat of
an afterthought in database design. Instead, specialized tools have been
developed for the purpose of delivering event notifications.

### Messaging Systems

A common approach for notifying consumers about new events is to use a
messaging system: a producer sends a message containing the event, which is
then pushed to consumers.

A direct communication channel like a Unix pipe or TCP connection between
producer and consumer would be a simple way of implementing a messaging system.
However, most messaging systems expand on this basic model. A messaging system
allows multiple producer nodes to send messages to the same topic and allows
multiple consumer nodes to receive messages in a topic.

Within this ***publish/subscribe*** model, different systems take a wide range
of approaches, and there is no one right answer for all purposes. To
differentiate the systems, it is particularly helpful to ask the following two
questions:

1. ***What happens if the producers send messages faster than the consumers can
   process them?***
    - Broadly speaking, there are three options:
      - the system can drop messages
      - buffer messages in a queue
      - apply backpressure (also known as flow control; i.e., blocking the
        producer from sending more messages). For example, Unix pipes and TCP
        use backpressure: they have a small fixed-size buffer, and if it fills
        up, the sender is blocked until the recipient takes data out of the
        buffer.
    - If messages are buffered in a queue, it is important to understand what
      happens as that queue grows. Does the system crash if the queue no longer
      fits in memory, or does it write messages to disk? If so, how does the
      disk access affect the performance of the messaging system?
2. ***What happens if nodes crash or temporarily go offline—are any messages
   lost?***
    - As with databases, durability may require some combination of writing to
      disk and/or replication, which has a cost. If you can afford to sometimes
      lose messages, you can probably get higher throughput and lower latency
      on the same hardware.

Whether message loss is acceptable depends very much on the application. For
example, with sensor readings and metrics that are transmitted periodically, an
occasional missing data point is perhaps not important, since an updated value
will be sent a short time later anyway. However, beware that if a large number
of messages are dropped, it may not be immediately apparent that the metrics
are incorrect. If you are counting events, it is more important that they are
delivered reliably, since every lost message means incorrect counters.

A nice property of the batch processing systems is that they provide a strong
reliability guarantee: failed tasks are automatically retried, and partial
output from failed tasks is automatically discarded. This means the output is
the same as if no failures had occurred, which helps simplify the programming
model.

#### Direct messaging from producers to consumers

A number of messaging systems use direct network communication between
producers and consumers without going via intermediary nodes:

- UDP multicast is widely used in the financial industry for streams such as
  stock market feeds, where low latency is important. Although UDP itself is
  unreliable, application-level protocols can recover lost packets (the
  producer must remember packets it has sent so that it can retransmit them on
  demand).
- Brokerless messaging libraries such as ZeroMQ and nanomsg take a similar
  approach, implementing publish/subscribe messaging over TCP or IP multicast.
- StatsD and Brubeck use unreliable UDP messaging for collecting metrics from
  all machines on the network and monitoring them. (In the StatsD protocol,
  counter metrics are only correct if all messages are received; using UDP
  makes the metrics at best approximate.)

If the consumer exposes a service on the network, producers can make a direct
HTTP or RPC request to push messages to the consumer. This is the idea behind
webhooks, a pattern in which a callback URL of one service is registered with
another service, and it makes a request to that URL whenever an event occurs.

Although these direct messaging systems work well in the situations for which
they are designed, they generally require the application code to be aware of
the possibility of message loss. The faults they can tolerate are quite
limited: even if the protocols detect and retransmit packets that are lost in
the network, they generally assume that producers and consumers are constantly
online.

If a consumer is offline, it may miss messages that were sent while it is
unreachable. Some protocols allow the producer to retry failed message
deliveries, but this approach may break down if the producer crashes, losing
the buffer of messages that it was supposed to retry.

#### Message brokers

A widely used alternative is to send messages via a ***message broker***
(***message queue***), which is essentially a kind of database that is
optimized for handling message streams.

By centralizing the data in the broker, these systems can more easily tolerate
clients that come and go, and the question of durability is moved to the broker
instead. Some message brokers only keep messages in memory, while others write
them to disk so that they are not lost in case of a broker crash. Faced with
slow consumers, they generally allow unbounded queueing (as opposed to dropping
messages or backpressure), although this choice may also depend on the
configuration.

A consequence of queueing is also that consumers are generally asynchronous:
when a producer sends a message, it normally only waits for the broker to
confirm that it has buffered the message and does not wait for the message to
be processed by consumers. The delivery to consumers will happen at some
undetermined future point in time — often within a fraction of a second, but
sometimes significantly later if there is a queue backlog.

#### Message brokers compared to databases

Some message brokers can even participate in two-phase commit protocols using
XA or JTA. This feature makes them quite similar in nature to databases,
although there are still important practical differences between message
brokers and databases:

- Databases usually keep data until it is explicitly deleted, whereas most
  message brokers automatically delete a message when it has been successfully
  delivered to its consumers. Such message brokers are not suitable for
  long-term data storage.
- Since they quickly delete messages, most message brokers assume that their
  working set is fairly small — i.e., the queues are short. If the broker needs
  to buffer a lot of messages because the consumers are slow (perhaps spilling
  messages to disk if they no longer fit in memory), each individual message
  takes longer to process, and the overall throughput may degrade.
- Databases often support secondary indexes and various ways of searching for
  data, while message brokers often support some way of subscribing to a subset
  of topics matching some pattern.
- When querying a database, the result is typically based on a point-in-time
  snapshot of the data; if another client subsequently writes something to the
  database that changes the query result, the first client does not find out
  that its prior result is now outdated. By contrast, message brokers do not
  support arbitrary queries, but they do notify clients when data changes.

This is the traditional view of message brokers, which is encapsulated in
standards like JMS and AMQP and implemented in software like RabbitMQ,
ActiveMQ, HornetQ, Qpid, TIBCO Enterprise Message Service, IBM MQ, Azure
Service Bus, and Google Cloud Pub/Sub.

#### Multiple consumers

When multiple consumers read messages in the same topic, two main patterns of
messaging are used:

- ***Load balancing***: Each message is delivered to one of the consumers, so
  the consumers can share the work of processing the messages in the topic. The
  broker may assign messages to consumers arbitrarily. This pattern is useful
  when the messages are expensive to process, and so you want to be able to add
  consumers to parallelize the processing. (In AMQP, you can implement load
  balancing by having multiple clients consuming from the same queue, and in
  JMS it is called a ***shared subscription***.)
- ***Fan-out***: Each message is delivered to all of the consumers. Fan-out
  allows several independent consumers to each “tune in” to the same broadcast
  of messages, without affecting each other — the streaming equivalent of
  having several different batch jobs that read the same input file. (This
  feature is provided by topic subscriptions in JMS, and exchange bindings in
  AMQP.)

The two patterns can be combined: for example, two separate groups of consumers
may each subscribe to a topic, such that each group collectively receives all
messages, but within each group only one of the nodes receives each message.

#### Acknowledgments and redelivery

Consumers may crash at any time, so it could happen that a broker delivers a
message to a consumer but the consumer never processes it, or only partially
processes it before crashing. In order to ensure that the message is not lost,
message brokers use acknowledgments: a client must explicitly tell the broker
when it has finished processing a message so that the broker can remove it from
the queue.

If the connection to a client is closed or times out without the broker
receiving an acknowledgment, it assumes that the message was not processed, and
therefore it delivers the message again to another consumer. (Note that it
could happen that the message actually was fully processed, but the
acknowledgment was lost in the network. Handling this case requires an atomic
commit protocol.)

When combined with load balancing, this redelivery behavior has an interesting
effect on the ordering of messages. The consumers generally process messages in
the order they were sent by producers. However, `consumer 2` crashes while
processing message `m3`, at the same time as `consumer 1` is processing message
`m4`. The unacknowledged message `m3` is subsequently redelivered to
`consumer 1`, with the result that `consumer 1` processes messages in the order
`m4, m3, m5`. Thus, `m3` and `m4` are not delivered in the same order as they
were sent by producer 1.

Even if the message broker otherwise tries to preserve the order of messages
(as required by both the JMS and AMQP standards), the combination of load
balancing with redelivery inevitably leads to messages being reordered. To
avoid this issue, you can use a separate queue per consumer (i.e., not use the
load balancing feature). Message reordering is not a problem if messages are
completely independent of each other, but it can be important if there are
causal dependencies between messages.

### Partitioned Logs

Sending a packet over a network or making a request to a network service is
normally a transient operation that leaves no permanent trace. Although it is
possible to record it permanently (using packet capture and logging), we
normally don’t think of it that way. Even message brokers that durably write
messages to disk quickly delete them again after they have been delivered to
consumers, because they are built around a transient messaging mindset.

This difference in mindset has a big impact on how derived data is created. A
key feature of batch processes is that you can run them repeatedly,
experimenting with the processing steps, without risk of damaging the input.
This is not the case with AMQP/JMS-style messaging: receiving a message is
destructive if the acknowledgment causes it to be deleted from the broker, so
you cannot run the same consumer again and expect to get the same result.

If you add a new consumer to a messaging system, it typically only starts
receiving messages sent after the time it was registered.

Why can we not have a hybrid, combining the durable storage approach of
databases with the low-latency notification facilities of messaging? This is
the idea behind ***log-based message brokers***.

#### Using logs for message storage

A log is simply an append-only sequence of records on disk.

The same structure can be used to implement a message broker: a producer sends
a message by appending it to the end of the log, and a consumer receives
messages by reading the log sequentially. If a consumer reaches the end of the
log, it waits for a notification that a new message has been appended. The Unix
tool `tail -f`, which watches a file for data being appended, essentially works
like this.

In order to scale to higher throughput than a single disk can offer, the log
can be partitioned. Different partitions can then be hosted on different
machines, making each partition a separate log that can be read and written
independently from other partitions. A topic can then be defined as a group of
partitions that all carry messages of the same type.

Within each partition, the broker assigns a monotonically increasing sequence
number, or ***offset***, to every message. Such a sequence number makes sense
because a partition is append-only, so the messages within a partition are
totally ordered. There is no ordering guarantee across different partitions.

Apache Kafka, Amazon Kinesis Streams, and Twitter’s DistributedLog are
log-based message brokers that work like this. Google Cloud Pub/Sub is
architecturally similar but exposes a JMS-style API rather than a log
abstraction. Even though these message brokers write all messages to disk, they
are able to achieve throughput of millions of messages per second by
partitioning across multiple machines, and fault tolerance by replicating
messages.

#### Logs compared to traditional messaging

>>>>> progress
