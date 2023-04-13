# Introduction

- [Introduction](#introduction)
  - [1. Architectural Principles](#1-architectural-principles)
    - [1.1. Packets, Connections, and Datagrams](#11-packets-connections-and-datagrams)
    - [1.2. The End-to-End Argument and Fate Sharing](#12-the-end-to-end-argument-and-fate-sharing)
    - [1.3. Error Control and Flow Control](#13-error-control-and-flow-control)
  - [2. Design and Implementation](#2-design-and-implementation)
    - [2.1. Layering](#21-layering)
    - [2.2. Multiplexing, Demultiplexing, and Encapsulation in Layered Implementations](#22-multiplexing-demultiplexing-and-encapsulation-in-layered-implementations)

The first definition of a protocol, according to the *New Oxford American
Dictionary*, is

> The official procedure or system of rules governing affairs of state or
> diplomatic occasions.

A collection of related protocols is called a ***protocol suite***.

The design that specifies how various protocols of a protocol suite relate to
each other and devide up tasks to be accomplished is called the
***architecture*** or ***reference model*** for the protocol suite.

TCP/IP is a protocol suite that implements the Internet architecture and draws
its origins from the ***ARPANET Reference Model*** (ARM).

## 1. Architectural Principles

- WAN: wide area network

**The Internet vs. the World Wide Web:**

- We refer to the Internet in terms of its ability to provide basic
  communication of messages between computers.
- We refer to WWW as an application that uses the Internet for communication.

**The goals of the Internet Architecture:**

The primary goal: **develop an effective technique for multiplexed utilization
of existing interconnected networks**.

The second-level goals are:

- Internet communication must continue despite loss of networks or gateways.
- The Internet must support multiple types of communication services.
- The Internet architecture must accommodate a variety of networks.
- The Internet architecture must permit distributed management of its resources.
- The Internet architecture must be cost-effective.
- The Internet architecture must permit host attachment with a low level of
  effort.
- The resource used in the Internet architecture must be accountable.

### 1.1. Packets, Connections, and Datagrams

- **packets**
  - *statitical multiplexing*
    - FCFS/FIFO: first-come-first-served/first-in-first-out
  - *time-division multiplexing* (TDM)
  - *static multiplexing*
- **connection-oriented** networks
  - *virtual circuits* (VCs)
    - *X.25*
      - *logical channel identifier* (LCI)
      - *logical channel number* (LCN)
  - *digital subscriber line* (DSL)
- **datagrams**: a datagram is a special type of packet in which all the
  identifying information of the source and final destination resides inside the
  packet itself.
  - *message boundaries/ record markers*
    - Most datagram protocols preserve message boundaries.
    - Applications need to implement their own methods to indicate a sender's
      message boundaries if this capability is required.

### 1.2. The End-to-End Argument and Fate Sharing

One of the most important principles that influenced the design of the TCP/IP
suite is called the *end-to-end argument*:

> The function in question can completely and correctly be implemented only
> with the knowledge and help of the application standing at the end points of
> the communication system. Therefore, providing that questioned function as a
> feature of the communication itself is not possible. (Sometimes an incomplete
> version of the function provided by the communication system may be useful as
> a performance enhancement.)

It argues that correctness and completeness can be achieved ***only*** by
involving the application or ultimate user of the communication system. This
principle argues that important functions (e.g., error control, encryption,
delivery acknowledgment) should usually not be implemented at low levels (or
layers) of large systems.

The TCP/IP took the design to which the end-to-end argument tends to support
with a "dumb" network and "smart" systems connected to the network. Its many
functions (e.g., methods to ensure that data is not lost, controlling the rate
at which a sender sends) are implemented in the end hosts where the applications
reside.

*Fate sharing* suggests placing all the necessary state to maintain an active
communication association (e.g., virtual connection) at the same location with
the communicating endpoints. With this reasoning, the only type of failure that
destroys communication is one that also destroys one or more of the endpoints,
which obviously destroys the overall communication anyhow. Fate sharing is one
of the design philosophies that allows virtual connections (e.g., those
implemented by TCP) to remain active even if connectivity within the network
has failed for a (modest) period of time. Fate sharing also supports a "dumb
network with smart end hosts" model, and one of the ongoing tensions in today's
Internet is what functions reside in the network and what functions do not.

### 1.3. Error Control and Flow Control

- *error control*: it can be implemented in the systems constituting the network
  infrastructure, or in the systems that attach to the network, or some
  combination.
- *best-effort delivery*: the network does not expend much effort to ensure that
  data is delivered without errors or gaps.
- *flow control*: operate outside the network and at higher levels of the
  communication system.
  - This is consistent with the end-to-end argument: TCP, which resides at the
    end hosts, handles rate control.
  - It is also consistent with fate sharing: the approach allows some elements
    of the network infrastructure to fail without necessarily affecting the
    ability of the devices outside the network to communicate as long as some
    communication path continues to operate.

## 2. Design and Implementation

### 2.1. Layering

Layers are beneficial because a layered design allows developers to evolve
different portions of the system separately, often by different people with
somewhat different areas of expertise.

- *Open Systems Interconnection* (OSI) model
  - Hosts
    - 7.Application
    - 6.Presentation
    - 5.Session
    - 4.Transport
  - All Networked Devices
    - 3.Network (or Internetwork)
    - 2.Link (or Data-Link)
    - 1.Physical
- The TCP/IP architecture is normally considered to consist of five.
  - Hosts
    - 5.Application
    - 4.Transport
  - All Networked Devices
    - 3.Network (or Internetwork)
    - 2.Link (or Data-Link)
    - 1.Physical

### 2.2. Multiplexing, Demultiplexing, and Encapsulation in Layered Implementations

>>>>> progress
