# 33. Event-based Concurrency (Advanced)

Thus far, we’ve written about concurrency as if the only way to build
concurrent applications is to use threads. Like many things in life, this is
not completely true. Specifically, a different style of concurrent programming
is often used in both GUI-based applications as well as some types of internet
servers. This style, known as **event-based concurrency**, has become popular
in some modern systems, including server-side frameworks such as **node.js**,
but its roots are found in C/UNIX systems that we’ll discuss below.

The problem that event-based concurrency addresses is two-fold.

- The first is that managing concurrency correctly in multi-threaded
  applications can be challenging; as we’ve discussed, missing locks, deadlock,
  and other nasty problems can arise.
- The second is that in a multi-threaded application, the developer has little
  or no control over what is scheduled at a given moment in time; rather, the
  programmer simply creates threads and then hopes that the underlying OS
  schedules them in a reasonable manner across available CPUs. Given the
  difficulty of building a general-purpose scheduler that works well in all
  cases for all workloads, sometimes the OS will schedule work in a manner that
  is less than optimal.

THE CRUX: **HOW TO BUILD CONCURRENT SERVERS WITHOUT THREADS**

How can we build a concurrent server without using threads, and thus retain
control over concurrency as well as avoid some of the problems that seem to
plague multi-threaded applications?

## 33.1 The Basic Idea: An Event Loop

The basic approach we’ll use, as stated above, is called
**event-based concurrency**. The approach is quite simple: you simply wait for
something (i.e., an “event”) to occur; when it does, you check what type of
event it is and do the small amount of work it requires (which may include
issuing I/O requests, or scheduling other events for future handling, etc.).

Before getting into the details, let’s first examine what a canonical
event-based server looks like. Such applications are based around a simple
construct known as the *event loop**. Pseudocode for an event loop looks like
this:

```c
while (1)
{
    events = getEvents();
    for (e in events)
        processEvent(e);
}
```

It’s really that simple. The main loop simply waits for something to do (by
calling `getEvents()` in the code above) and then, for each event returned,
processes them, one at a time; the code that processes each event is known as
an **event handler**. Importantly, when a handler processes an event, it is the
only activity taking place in the system; thus, deciding which event to handle
next is equivalent to scheduling. This explicit control over scheduling is one
of the fundamental advantages of the event-based approach.

But this discussion leaves us with a bigger question: how exactly does an
event-based server determine which events are taking place, in particular with
regards to network and disk I/O? Specifically, how can an event server tell if
a message has arrived for it?

## 33.2 An Important API: `select()` (or `poll()`)

With that basic event loop in mind, we next must address the question of how to
receive events. In most systems, a basic API is available, via either the
`select()` or `poll()` system calls.

What these interfaces enable a program to do is simple: check whether there is
any incoming I/O that should be attended to. For example, imagine that a
network application (such as a web server) wishes to check whether any network
packets have arrived, in order to service them. These system calls let you do
exactly that.

Take `select()` for example. The manual page describes the API in this manner:

```c
int select(int nfds,
           fd_set *restrict readfds,
           fd_set *restrict writefds,
           fd_set *restrict errorfds,
           struct timeval *restrict timeout);
```

The actual description from the man page:

> `select()` examines the I/O descriptor sets whose addresses are passed in
> `readfds`, `writefds`, and `errorfds` to see if some of their descriptors are
> ready for reading, are ready for writing, or have an exceptional condition
> pending, respectively. The first `nfds` descriptors are checked in each set,
> i.e., the descriptors from 0 through nfds-1 in the descriptor sets are
> examined. On return, `select()` replaces the given descriptor sets with
> subsets consisting of those descriptors that are ready for the requested
> operation. `select()` returns the total number of ready descriptors in all
> the sets.

A couple of points about `select()`. First, note that it lets you check whether
descriptors can be *read* from as well as *written* to; the former lets a
server determine that a new packet has arrived and is in need of processing,
whereas the latter lets the service know when it is OK to reply (i.e., the
outbound queue is not full).

Second, note the timeout argument. One common usage here is to set the timeout
to `NULL`, which causes `select()` to block indefinitely, until some descriptor
is ready. However, more robust servers will usually specify some kind of
timeout; one common technique is to set the timeout to zero, and thus use the
call to `select()` to return immediately.

The `poll()` system call is quite similar. See its manual page, or Stevens and
Rago, for details.

Either way, these basic primitives give us a way to build a non-blocking event
loop, which simply checks for incoming packets, reads from sockets with
messages upon them, and replies as needed.

## 33.3 Using `select()`

To make this more concrete, let’s examine how to use `select()` to see which
network descriptors have incoming messages upon them. Figure 33.1 shows a
simple example.

Figure 33.1: **Simple Code Using select()**

```c
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>

int main(void)
{
    // open and set up a bunch of sockets (not shown)
    // main loop
    while (1)
    {
        // initialize the fd_set to all zero
        fd_set readFDs;
        FD_ZERO(&readFDs);

        // now set the bits for descriptors
        // this server is interested in
        // (for simplicity, all of them from min to max)
        int fd;
        for (fd = minFD; fd < maxFD; fd++)
        {
            FD_SET(fd, &readFDs);
        }

        // do the select
        int rc = select(maxFD + 1, &readFDs, NULL, NULL, NULL);

        // check which actually have data using FD_ISSET()
        int fd;
        for (fd = minFD; fd < maxFD; fd++)
        {
            if (FD_ISSET(fd, &readFDs))
            {
                processFD(fd);
            }
        }
    }
}
```

This code is actually fairly simple to understand. After some initialization,
the server enters an infinite loop. Inside the loop, it uses the `FD_ZERO()`
macro to first clear the set of file descriptors, and then uses `FD_SET()` to
include all of the file descriptors from `minFD` to `maxFD` in the set. This
set of descriptors might represent, for example, all of the network sockets to
which the server is paying attention. Finally, the server calls `select()` to
see which of the connections have data available upon them. By then using
`FD_ISSET()` in a loop, the event server can see which of the descriptors have
data ready and process the incoming data.

Of course, a real server would be more complicated than this, and require logic
to use when sending messages, issuing disk I/O, and many other details.

## 33.4 Why Simpler? No Locks Needed

With a single CPU and an event-based application, the problems found in
concurrent programs are no longer present. Specifically, because only one event
is being handled at a time, there is no need to acquire or release locks; the
event-based server cannot be interrupted by another thread because it is
decidedly single threaded. Thus, concurrency bugs common in threaded programs
do not manifest in the basic event-based approach.

TIP: **DON’T BLOCK IN EVENT-BASED SERVERS**

Event-based servers enable fine-grained control over scheduling of tasks.
However, to maintain such control, no call that blocks the execution of the
caller can ever be made; failing to obey this design tip will result in a
blocked event-based server, frustrated clients, and serious questions as to
whether you ever read this part of the book.

## 33.5 A Problem: Blocking System Calls

Thus far, event-based programming sounds great, right? You program a simple
loop, and handle events as they arise. You don’t even need to think about
locking! But there is an issue: what if an event requires that you issue a
system call that might block?

For example, imagine a request comes from a client into a server to read a file
from disk and return its contents to the requesting client (much like a simple
HTTP request). To service such a request, some event handler will eventually
have to issue an `open()` system call to open the file, followed by a series of
`read()` calls to read the file. When the file is read into memory, the server
will likely start sending the results to the client.

Both the `open()` and `read()` calls may issue I/O requests to the storage
system (when the needed metadata or data is not in memory already), and thus
may take a long time to service. With a thread-based server, this is no issue:
while the thread issuing the I/O request suspends (waiting for the I/O to
complete), other threads can run, thus enabling the server to make progress.
Indeed, this natural **overlap** of I/O and other computation is what makes
thread-based programming quite natural and straightforward.

With an event-based approach, however, there are no other threads to run: just
the main event loop. And this implies that if an event handler issues a call
that blocks, the *entire* server will do just that: block until the call
completes. When the event loop blocks, the system sits idle, and thus is a huge
potential waste of resources. We thus have a rule that must be obeyed in
event-based systems: no blocking calls are allowed.

## 33.6 A Solution: Asynchronous I/O

To overcome this limit, many modern operating systems have introduced new ways
to issue I/O requests to the disk system, referred to generically as
**asynchronous I/O**. These interfaces enable an application to issue an I/O
request and return control immediately to the caller, before the I/O has
completed; additional interfaces enable an application to determine whether
various I/Os have completed.

For example, let us examine the interface provided on a Mac (other systems have
similar APIs). The APIs revolve around a basic structure, the `struct aiocb` or
**AIO control block** in common terminology. A simplified version of the
structure looks like this:

```c
struct aiocb
{
    int aio_fildes;         /* File descriptor */
    off_t aio_offset;       /* File offset */
    volatile void *aio_buf; /* Location of buffer */
    size_t aio_nbytes;      /* Length of transfer */
};
```

To issue an asynchronous read to a file, an application should first fill in
this structure with the relevant information: the file descriptor of the file
to be read (`aio_fildes`), the offset within the file (`aio_offset`) as well as
the length of the request (`aio_nbytes`), and finally the target memory
location into which the results of the read should be copied (`aio_buf`).

After this structure is filled in, the application must issue the asynchronous
call to read the file; on a Mac, this API is simply the **asynchronous read**
API:

```c
int aio_read(struct aiocb *aiocbp);
```

This call tries to issue the I/O; if successful, it simply returns right away
and the application (i.e., the event-based server) can continue with its work.

There is one last piece of the puzzle we must solve, however. How can we tell
when an I/O is complete, and thus that the buffer (pointed to by `aio_buf`) now
has the requested data within it?

One last API is needed. On a Mac, it is referred to (somewhat confusingly) as
`aio_error()`. The API looks like this:

```c
int aio_error(const struct aiocb *aiocbp);
```

This system call checks whether the request referred to by `aiocbp` has
completed. If it has, the routine returns success (indicated by a zero); if
not, `EINPROGRESS` is returned. Thus, for every outstanding asynchronous I/O,
an application can periodically **poll** the system via a call to `aio_error()`
to determine whether said I/O has yet completed.

One thing you might have noticed is that it is painful to check whether an I/O
has completed; if a program has tens or hundreds of I/Os issued at a given
point in time, should it simply keep checking each of them repeatedly, or wait
a little while first, or ... ?

To remedy this issue, some systems provide an approach based on the
**interrupt**. This method uses UNIX **signals** to inform applications when an
asynchronous I/O completes, thus removing the need to repeatedly ask the
system. This polling vs. interrupts issue is seen in devices too.

ASIDE: **UNIX SIGNALS**

A huge and fascinating infrastructure known as **signals** is present in all
modern UNIX variants. At its simplest, signals provide a way to communicate
with a process. Specifically, a signal can be delivered to an application;
doing so stops the application from whatever it is doing to run a
**signal handler**, i.e., some code in the application to handle that signal.
When finished, the process just resumes its previous behavior.

Each signal has a name, such as **HUP** (hang up), **INT** (interrupt),
**SEGV** (segmentation violation), etc; see the manual page for details.
Interestingly, sometimes it is the kernel itself that does the signaling. For
example, when your program encounters a segmentation violation, the OS sends it
a **SIGSEGV** (prepending **SIG** to signal names is common); if your program
is configured to catch that signal, you can actually run some code in response
to this erroneous program behavior (which can be useful for debugging). When a
signal is sent to a process not configured to handle that signal, some default
behavior is enacted; for **SEGV**, the process is killed.

Here is a simple program that goes into an infinite loop, but has first set up
a signal handler to catch **SIGHUP**:

```c
#include <stdio.h>
#include <signal.h>

void handle(int arg)
{
    printf("stop wakin’ me up...\n");
}

int main(int argc, char *argv[])
{
    signal(SIGHUP, handle);
    while (1)
        ; // doin’ nothin’ except catchin’ some sigs
    return 0;
}
```

You can send signals to it with the **kill** command line tool (yes, this is an
odd and aggressive name). Doing so will interrupt the main while loop in the
program and run the handler code `handle()`:

```sh
./bin/signal &
[1] 27515

kill -HUP 27515
stop wakin’ me up..

kill -HUP 27515
stop wakin’ me up...
```

In systems without asynchronous I/O, the pure event-based approach cannot be
implemented. However, clever researchers have derived methods that work fairly
well in their place. For example, Pai et al. describe a hybrid approach in
which events are used to process network packets, and a thread pool is used to
manage outstanding I/Os.

## 33.7 Another Problem: State Management
