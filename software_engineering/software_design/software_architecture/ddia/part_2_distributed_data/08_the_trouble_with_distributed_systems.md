# 8. The Trouble with Distributed Systems

- [8. The Trouble with Distributed Systems](#8-the-trouble-with-distributed-systems)
  - [Faults and Partial Failures](#faults-and-partial-failures)
    - [Cloud Computing and Supercomputing](#cloud-computing-and-supercomputing)
    - [Building a Reliable System from Unreliable Components](#building-a-reliable-system-from-unreliable-components)
  - [Unreliable Networks](#unreliable-networks)
    - [Network Faults in Practice](#network-faults-in-practice)
      - [Network partitions](#network-partitions)
    - [Detecting Faults](#detecting-faults)
    - [Timeouts and Unbounded Delays](#timeouts-and-unbounded-delays)
      - [Network congestion and queueing](#network-congestion-and-queueing)
      - [TCP Versus UDP](#tcp-versus-udp)
    - [Synchronous Versus Asynchronous Networks](#synchronous-versus-asynchronous-networks)
      - [Can we not simply make network delays predictable?](#can-we-not-simply-make-network-delays-predictable)
      - [Latency and Resource Utilization](#latency-and-resource-utilization)
  - [Unreliable Clocks](#unreliable-clocks)
    - [Monotonic Versus Time-of-day Clocks](#monotonic-versus-time-of-day-clocks)
      - [Time-of-day clocks](#time-of-day-clocks)
      - [Monotonic clocks](#monotonic-clocks)
    - [Clock Synchronization and Accuracy](#clock-synchronization-and-accuracy)

## Faults and Partial Failures

On a single computer, if an internal fault occurs, we prefer a computer to
crash completely rather than returning a wrong result, because wrong results
are difficult and confusing to deal with. Computers present an idealized system
model that operates with mathematical perfection.

In distributed systems, we are no longer operating in an idealized system model.

**Partial failures** are ***nondeterministic***. The nondeterminism and
possibility of partial failures is what makes distributed systems hard to work
with.

### Cloud Computing and Supercomputing

A supercomputer is more like a single-node computer than a distributed system:
it deals with partial failure by letting it escalate into total failure.

Even in a small system, sooner or later, some part of the system will become
faulty, and the software will have to somehow handle it. The fault handling must
be part of the software design.

### Building a Reliable System from Unreliable Components

For example:

- Error-correcting codes allow digital data to be transmitted accurately across
  communication channel that occasionally gets some bits wrong.
- The IP Protocol is unreliable: it may drop, delay, duplicate, or reorder
  packets. TCP provides a more reliable transport layer on top of IP: it ensures
  that missing packets are retransmitted, duplicates are eliminated, and packets
  are reassembled into the order in which they were sent.

## Unreliable Networks

Shared-nothing has become the dominant approach for building internet services:

- it's comparatively cheap because it requires no special hardware
- it can make use of commoditized cloud computing services
- it can achieve high reliability through redundancy across multiple
  geographically distributed datacenters

Network issues: if you send a request to another node and don't receive a
response, it is *impossible* to tell why.

- The usual way of handling this issue is a *timeout*.

### Network Faults in Practice

#### Network partitions

### Detecting Faults

Many systems need to detect faulty nodes:

- A load balancer needs to stop sending requests to a node that is dead.
- In a distributed database with single-leader replication, if the leader fails,
  one of the followers needs to be promoted to the new leader.

The uncertainty about the network makes it difficult to tell whether a node is
working or not. In some circumstances you might get feedback to tell you that
something is wrong:

- If you can reach the machine on which the node should be running, but no
  process is listening on the destination port, the OS will close or refuse TCP
  connections by sending a `RST` or `FIN` packet in reply.
- If a node process crashed but the node's OS is still running, a script can
  notify other nodes so that another node can take over quickly without having
  to wait for a timeout. e.g. HBase works like this.
- If you have access to the management interface of the network switches in your
  datacenter, you can query them to detect link failures at a hardware level.
- If a router is sure that the IP you're trying to connect to is unreachable, it
  may reply to you with an ICMP Destination Unreachable packet.

If you want to be sure that a request was successful, you need a positive
response from the application itself.

### Timeouts and Unbounded Delays

Prematurely declaring a node dead is problematic:

- If the node is actually alive and in the middle of performing some actoin,
  and another node takes over, the action may end up being perform twice.
- If the system is already struggling with high load, it can make the problem
  worse.

Asynchronous networks have *unbounded delays*, and most server implementations
cannot guarantee that they can handle requests within some maximum time.

#### Network congestion and queueing

- network switch
- operating system
- virtual machine monitor
- TCP *flow control*

In public clouds and multi-tenant datacenters, resources are shared among many
customers. In such environments, you can only choose timeouts experimentally:

- measure the distribution of network round-trip times over an extended period
  to determine the expected variability of delays.
- then taking into account your applications' characteristics, determine an
  appropriate trade-off between failure detection delay and risk of premature
  timeouts.
- dynamically measure and adjust response times and their variability according
  to the observed response time distribution.

#### TCP Versus UDP

Some latency-sensitive applications use UDP rather than TCP. It avoids some of
the reasons for variable network delays.

- UDP does not perform flow control
- UDP does not retransmit lost packets. e.g.
  - In a VoIP phone call, there's not point in retransmitting the packet.

### Synchronous Versus Asynchronous Networks

**Synchronous** networks: even as data passes through several routers, it does
not suffer from queueing, because the bits of space for the call have already
been reserved in the next hop of the network. And because there is no queueing,
the maximum end-to-end latency of the network is fixed. It is called a *bounded
delay*.

#### Can we not simply make network delays predictable?

- A circuit in a telephone network is a fixed amount of reserved bandwidth which
  nobody else can use while the circuit is established
- The packets of a TCP connection opportunistically use whatever network
  bandwidth is available.

If the internet were circuit-switched networks, it would be possible to
establish a guaranteed maximum round-trip time.

However, they are not. They are optimized for *bursty traffic*. TCP dynamically
adapts the rate of data transfer to the available network capacity.

Currently deployed technology does not allow us to make any guarantees about
delays or reliability ot the network.

#### Latency and Resource Utilization

- The resource in a circuit is divided up in a *static way*. The circuit is
  allocated the same fixed amount of bandwidth no matter the wire is full
  utilized or not.
- The internet shares network bandwidth *dynamically*.
  - This approach has the downside of queueing.
  - The advantage is that it maximizes utilization of the wire.
    - Better hardware utilization is also a significant motivation for using
      virtual machines.

Latency guarantees are achievable in certain environments, if resources are
statically paritioned. However, it comes at the cost of reduced utilization.

## Unreliable Clocks

It is possible to synchronize clocks to some degree: the most commonly used
mechanism is the Network Time Protocol (NTP).

### Monotonic Versus Time-of-day Clocks

Modern computers have at least two kinds of clocks:

- a *time-of-day clock*
- a *monotonic clock*

#### Time-of-day clocks

- `clock_gettime(CLOCK_REALTIME)`

It returns the current date and time according to some calendar. It is usually
synchronized with NTP. However, it also has various oddities. e.g.

- If the local clock is too far ahead of the NTP server, it may be forcibly
  reset and appear to jump back to a previous point in time.

These jumps and the fact that they often ignore leap seconds, make time-of-day
clocks unsuitable for measuring elapsed time.

#### Monotonic clocks

- `clock_gettime(CLOCK_MONOTONIC)`

A monotonic clock is suitable for measuring a duration. The name comes from the
fact that they are guaranteed to always move forward, whereas a time-of-day
clock may jump back in time.

- The *absolute* value of the monotonic clock is meaningless.
- It makes no sense to compare monotonic clock values from two different
  computers.

On a server with multiple CPU sockets, there may be a separate timer per CPU.
Operating systems try to present a monotonic view of the clocks to application
threads.

In a distributed system, using a monotonic clock for measuting elapsed time is
usually fine, because it doesn't assume any synchronization between different
nodes' clocks and is not sensitive to slight inaccuracies of measurement.

### Clock Synchronization and Accuracy
