# Network Socket

> <https://en.wikipedia.org/wiki/Network_socket>

## Relevants

- [Handle](handle.md)

## Digest

### In the context of Internet Protocol Suite

*network socket* is referred to as **Internet socket**. In this context, a
socket is externally identified to other hosts by its **socket address**, which
is the triad of:

- **transport protocol**
- **IP address**
- **port number**

> The term *socket* is also used for the software endpoint of node-internal
**inter-process communication (IPC)**, which often uses the same API as a
network socket.

### Use

> The application programming interface (API) for the network protocol stack
> creates a handle for each socket created by an application, commonly referred
> to as a socket descriptor. In Unix-like operating systems, this descriptor is
> a type of file descriptor.

### Socket addresses

- protocol type
- IP address
- port number

### Implementation

A protocal stack, usually provided by the operating system (rather than as a
separate library), is a set of services that allow processes to communicate
over a network using the protocols that the stack implements.

The application programming interface that programs use to communicate with
the protocol stack, using network sockets, is called a **socket API**.

Internet socket APIs are usually based on the [Berkeley sockets](https://en.wikipedia.org/wiki/Berkeley_sockets)
standard.

Sockets need not have a source address, for example, for only sending data,
but if a program *binds* a socket to a source address, the socket can be used
to receive data sent to that address. Based on this address, Internet sockets
deliver incoming data packets to the appropriate application process.

An internet socket is minimally characterized by the following:

- local socket address, consisting of the local IP address and (for TCP and UDP,
  but not IP) a port number
- protocol: A transport protocol, e.g., TCP, UDP, raw IP. This means that (local
  or remote) endpoints with TCP port 53 nad UDP port 53 are distinct sockets,
  while IP does not have ports.
- A socket that has been connected to another socket, e.g., during the
  establishment of a TCP connection, also has a remote socket address.

### Definition

In the original definition of *socket* in RFC 147, as it was related to the
[ARPA network](https://en.wikipedia.org/wiki/ARPANET) in 1971, *"the socket is
specified as a 32-bit number with even sockets identifying receiving sockets
and odd sockets identifying sending sockets."*

Today, however, socket communications are bidirectional.

Within the operating system and the application that created a socket, a socket
is referred to by a unique integer value called a *socket descriptor*.

### Example

According to the Berkeley socket interface.

```py
# sends the string "Hello, world!" via TCP to port 80 of the host with address
# 1.2.3.4

# creation of a socket
Socket mysocket = getSocket(type = "TCP")
# connecting it to the remote host
connect(mysocket, address = "1.2.3.4", port = "80")
# sending the string
send(mysocket, "Hello, world!")
# closing the socket
close(mysocket)
```

### Types

Several types of Internet sockets are available:

- **Datagram sockets**: Connectionless sockets, which use
  [User Datagram Protocol (UDP)](https://en.wikipedia.org/wiki/User_Datagram_Protocol)
- **Stream sockets**: [Connection-oriented](https://en.wikipedia.org/wiki/Connection-oriented)
  sockets, which use [Transmission Control Protocol (TCP)](https://en.wikipedia.org/wiki/Transmission_Control_Protocol),
  Stream Control Transmission Protocol (STCP) or Datagram Congestion Control
  Protocol (DCCP).
- **Raw sockets**: Allow direct sending and receiving of IP packets without any
  protocol-specific transport layer formatting. With other types of sockets,
  the payload is automatically encapsulated according to the chosen transport
  layer protocol (e.g. TCP, UDP), and the socket user is unaware of the
  existence of protocol headers that are broadcast with the payload.

  Raw sockets are used in security-related applications like Nmap. One use case
  for raw sockets is the implementation of new transport-layer protocols in
  user space

### Socket states in the client-server model

A TCP server may serve several clients concurrently by creating a unique
dedicated socket for each client connection in a new child process or processing
thread for each client(that's how the c10k problem comes). These are in the
*established state* when a socket-to-socket virtual connection or virtual
circuit (VC), also known as a TCP sesstion, is established with the remote
socket, providing a duplex byte stream.

A server may create several concurrently established TCP sockets with the same
local port number and local IP address, each mapped to its own server-child
process, serving its own client process. They are treated as different sockets
by the operating system since the remote socket address (the client IP address
or port number) is different. Since they have different socket pair tuples.

UDP sockets do not have a *established state*, because the protocol is
connectionless. A UDP server process handles incoming datagrams from all remote
clients sequentially through the same socket. **UDP sockets are not identified
by the remote address, but only by the local address**, although each message
has an associated remote address that can be retrieved from each datagram with
the networking application programming interface (API).

### Sockat pairs

Communicating local and remote sockets are called **socket pairs**. Each socket
pair is described by a unique 4-tuple consisting of source and destination IP
addresses and port numbers, i.e. of local and remote socket addresses. As
discussed above, in the TCP case, a socket pair is associated on each end of the
connection with an unique 4-tuple.

### Sockets in network equipment

The socket is primarily a concept used in the transport layer of the Internet
protocol suite or session layer of the OSI model.

Stateful network firewalls, network address translators, and proxy servers keep
track of active socket pairs.

Raw sockets are typically available in network equipment and are used for
routing protocols such as IGRP and OSPF, and for Internet Control Message
Protocol (ICMP).
