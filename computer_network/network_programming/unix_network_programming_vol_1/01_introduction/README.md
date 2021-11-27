# Chapter 1. Introduction

## 1.1 Introduction

### Network application: client and server.

```diagram
[client] <-- application protocol --> [server]
```

### Server handling multiple clients at the same time.

```diagram
[client]    ↖
...             ↘
[client]    ←---→   [server]
...             ↗
[client]    ↙
```

### Client and server on the same Ethernet communicating using TCP.

![Client and server on the same Ethernet communicating using TCP](images/1_3.png)

The actual flow of information between the client and server goes down the
protocol stack on one side, across the network, and up the protocol stack on the
other side. And the client and server are typically user processes, while the
TCP and IP protocols are normally part of the protocol stack within the kernel.

### Client and server on different LANs connected through a WAN.

![Client and server on different LANs connected through a WAN](images/1_4.png)

*The largest WAN today is the Internet.*

## 1.2 A Simple Daytime Client

`intro/daytimetcpcli`: should make & run `intro/daytimetcpsrv` first.

```c
#include "unp.h"

int main(int argc, char **argv)
{
    int sockfd, n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in servaddr;

    if (argc != 2)
        err_quit("usage: a.out <IPaddress>");

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_sys("socket error");

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(13); /* daytime server */
    if (inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
        err_quit("inet_pton error for %s", argv[1]);

    if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) < 0)
        err_sys("connect error");

    while ((n = read(sockfd, recvline, MAXLINE)) > 0)
    {
        recvline[n] = 0; /* null terminate */
        if (fputs(recvline, stdout) == EOF)
            err_sys("fputs error");
    }
    if (n < 0)
        err_sys("read error");

    exit(0);
}
```

1. Include our own header
2. Command-line arguments
3. Create TCP socket
4. Specify server's IP address and port

    - `bzero`: initialize memory to zero
    - `htons`: host to network short
    - `inet_pton`: presentation to numeric of internet
    - `inet_addr`: to convert an ASCII dotted-decimal string into the correct
        format

5. Establish connect with server

    The `connect` function, when applied to a TCP socket, establishes a TCP
    connection with the server specified by the socket address structure
    pointed to by the second argument.

6. Read and display server's reply

    TCP is a *byte-stream* protocol with no record boundaries. With that, data
    can be returned in numerous ways. With larger data sizes, we cannot assume
    that the server's reply will be returned by s single `read`. Therefore,
    when reading from a TCP socket, we *always* need to code the `read` in a
    loop and terminate the loop when either `read` returns 0 (i.e., the other
    end closed the connection) or a value less than 0 (an error).

    The important concept here is that TCP itself provides no record markers:
    If an application wants to delineate the ends of records, it must do so
    itself and there are a few common ways to accomplish this.

7. Terminate program

    Unix always closes all open descriptors when a process terminates.

## 1.3 Protocol Independence

## 1.4 Error Handling: Wrapper Functions

In any real-world program, it is essential to check *every* function call for
error return.

Capilize the name of the error handling wrapper function:

```c
sockfd = Socket(AF_INET, SOCK_STREAM, 0);

int Socket(int family, int type, int protocol)
{
    int n;

    if ((n = socket(family, type, protocol)) < 0)
        err_sys("socket error");

    return (n);
}
```

To avoid cluttering the code with braces:

```c
int n;

if ((n = pthread_mutex_lock(&ndone_mutex)) != 0)
    errno = n, err_sys("pthread_mutex_lock error");

// better way
Pthread_mutex_lock(&ndone_mutex);

void Pthread_mutex_lock(pthread_mutex_t *mptr)
{
    int n;

    if ((n = pthread_mutet_lock(mptr)) == 0)
        return;
    errno = n;
    err_sys("pthread_mutex_lock error");
}
```

Using `C` macros instead of functions providing a little runtime efficiency, but
these wrapper functions are rarely the performance bottleneck of a program.

### Unix `errno` Value

When an error occurs in a Unix function (such as one of the socket functions),
the global variable `errno` is set to a positive value indicating the type of
error and the function normally returns -1.

All of the positive error values are constants with all-uppercase names
beginning with "E", and are normally defined in the `<sys/errno.h>` header. No
error has a value of 0.

Storing `errno` in a global variable does not work with multiple threads that
share all global variables.

## 1.5 A Simple Daytime Server

```c
#include "unp.h"
#include <time.h>

int main(int argc, char **argv)
{
    int listenfd, connfd;
    struct sockaddr_in servaddr;
    char buff[MAXLINE];
    time_t ticks;

    listenfd = Socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(13); /* daytime server */

    Bind(listenfd, (SA *)&servaddr, sizeof(servaddr));

    Listen(listenfd, LISTENQ);

    for (;;)
    {
        connfd = Accept(listenfd, (SA *)NULL, NULL);

        ticks = time(NULL);
        snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
        Write(connfd, buff, strlen(buff));

        Close(connfd);
    }
}
```

The style used throughout the book for an infinite loop is

```c
for (;;)
{
    //...
}
```

`snprintf` is better than `sprintf` because it checks for overflow by requiring
the 2nd argument be the size of the destination buffer.

### Functions that should be carefully dealt with, and better functions

- `sprintf`: `snprintf`
- `gets`: `fgets`
- `strcat`: `strncat`: `strlcat`
- `strcpy`: `strncpy`: `strlcpy`

1. Create a TCP socket
2. Bind server's well-known port to socket

    The server's well-known port (13 for the daytime service) is bound to the
    socket by filling in an Internet socket address struture and calling `bind`.
    `INADDR_ANY` allows the server to accept a client connection on any
    interface.

3. Convert socket to listening socket

    By calling `listen`, the socket is converted into a listening socket, on
    which incoming connections from clients will be accepted by the kernel.
    These three steps, `socket`, `bind`, and `listen`, are the normal steps for
    any TCP server to prepare what we call the *listening descriptor*
    (`listenfd` in this example).

    The constant `LISTENQ` is from our `unp.h` header. It specifies the maximum
    number of client connections that the kernel will queue for this listening
    descriptor.

4. Accept client connection, send reply

    Normally, the server process is put to **sleep** in the call to `accept`,
    waiting for a client connection to arrive and be accepted. A TCP connection
    uses what is called a *three-way handshake* to establish a connection. When
    this handshake completes, `accept` returns, and the return value from the
    function is a new descriptor (`connfd`) that is called the *connected
    descriptor*. This new descriptor is used for communication with the new
    client. A new descriptor is returned by `accept` for each client that
    connects to our server.

5. Terminate connection

    The server closes its connection with the client by calling `close`. This
    initiates the normal TCP connection termination sequence: a FIN is sent in
    each direction and each FIN is acknowledged by the other end.

This server is called an *iterative server* because it iterates through each
client, one at a time. There are numerous techniques for writing a *concurrent
server*, one that handles multiple clients at the same time. The simplest
technique for a concurrent server is to call the Unix `fork` function, creating
one child process for each client. Other techniques are to use threads instead
of `fork`, or to pre-fork a fixed number of children when the server starts.

## 1.6 Roadmap to Client/Server Examples in the Text

- A daytime client/server
- An echo client/server

## 1.7 OSI Model

OSI: Open Systems Interconnection.

### Layers in OSI model and Internet protocol suite

```diagram
7   application
----------------                                            application details
6   presentation    application
----------------                               user process
5   session
--------------------------------<-sockets XTI  ---------------------------------
4   transport       TCP|  ↕  |UDP
----------------    -------------
3   network         IPv4, IPv6                 kernel
----------------    -------------
2   datalink        device driver                        communications details
----------------    and
1   physical        hardware
----------------    -------------
OSI model           Internet protocol
                    suite
```

It is possible for an application to bypass the transport layer and use IPv4 and
IPv6 directly. This is called *raw socket*.

Why do sockets provide the interface from the upper three layers of the OSI
model into the transport layer? There are two reasons for this design:

1. The upper three layers handle all the details of the application (FTP,
    Telnet, HTTP, etc.) and know little about the communication details.

    The lower four layers know little about the application, but handle all the
    communication details: sending data, waiting for ackowledgment, sequencing
    data that arrives out of order, calculating and verifying checksums, and so
    on.

2. The upper three layers often form what is called a *user process* while the
    lower four layers are normally provided as part of the operating system
    kernel. Unix provides this separation between the user process and the
    kernel, as do many other contemporary operating systems. Therefore, the
    interface between layers 4 and 5 is the natural place to build the API.

## 1.8 BSD Networking History

```diagram
4.2BSD (1983)
first widely available
release of TCP/IP
and sockets API
↓
4.3BSD (1986)
TCP performance improvements
↓
4.3BSD Tahoe (1988)
slow start,
congestion avoidance,                   →   BSD Networking Software
fast restransmit                            Release 1.0 (1989): Net/1
↓
4.3BSD Reno (1990)
fast recovery,
TCP header prediction,
routing table changes;
length field added to `socketaddr{}`;   →   BSD Networking Software
control infomation added to `msghdr{}`      Release 2.0 (1991): Net/2
↓
4.4BSD (1993)
multicasting,
long fat pipe modifications             →   4.4BSD-Lite (1994)
                                            referred to in text as Net/3
                                            ↓
                                            4.4BSD-Lite2 (1995)
                                            (
                                                BSD/OS
                                                FreeBSD
                                                NetBSD
                                                OpenBSD
                                            )
```

## 1.9 Test Networks and Hosts

### Discovering Network Topology

1. `netstat`
    1. `-n`: print numeric addresses instead of trying to find names for the
    networks.
    2. `netstat -i`: provides information on the interfaces.
    3. `netstat -r`: shows the routing table.
2. `ifconfig`
   1. `ifconfig eth0`: show details for specific interface
3. `ping`
   1. `ping -b <broadcast address>`

## 1.10 Unix Standards

*The POSIX Specification*, which is identical to `ISO/IEC 9945:2002`,
`IEEE Std 1003.1-2001`, and the `Single Unix Specification Version 3`, has
roughly 4,000 pages of specifications covering over 1,700 programming
interfaces.

### Background on POSIX

POSIX (Portable Operating System Interface) is not a single standard, but a
family of standards being developed by the IEEE (Institute for Electical and
Electronics Engineers).

### Background on The Open Group

### Unification of Standards

### Internet Engineering Task Force (IETF)

## 1.11 64-Bit Architectures

The common programming model for existing 32-bit Unix syetems is called the
*ILP32* model, denoting that integers (I), long integers (L), and pointers (P)
occupy 32 bits.

The model that is becoming most prevalent for 64-bit Unix systems is called the
*LP64* model, meaning only long integers (L) and pointers (P) require 64 bits.

### Comparison of number of bits to hold various datatypes for the ILP32 and LP64 models

| Datatype | ILP32 model | LP64 model |
| - | - | - |
| char | 8 | 8 |
| short | 16 | 16 |
| int | 32 | 32 |
| long | 32 | 64 |
| pointer | 32 | 64 |

The LP64 model means we cannot assume that a pointer can be stored in an
integer. We must also consider the effect

ANSI C invented the `size_t` datatype. On a 32-bit system, `size_t` is a 32-bit
value, but on a 64-bit system, it must be a 64-bit value, to take advantage of
the larger addressing model.

## 1.12 Summary
