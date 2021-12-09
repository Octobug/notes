# 2. Introduction to Operating Systems

Crux of Virtualization: how to virtualize resources

## 2.1 Virtualizing The CPU

```c
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: cpu <string>\n");
        exit(1);
    }
    char *str = argv[1];

    while (1)
    {
        printf("%s\n", str);
        Spin(1);s
    }
    return 0;
}
```

Run many different instances of this same program at the same time:

```sh
./cpu A & ; ./cpu B & ; ./cpu C & ; ./cpu D &
```

Using `&` runs a job in the background in shell.

Turning a single CPU (or small set of them) into a seemingly infinite number of
CPUs and thus allowing many programs to seemingly run at once is what we call
virtualizing the CPU。

## 2.2 Virtualizing Memory

```c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: mem <value>\n");
        exit(1);
    }
    int *p;
    p = malloc(sizeof(int));
    assert(p != NULL);
    printf("(%d) addr pointed to by p: %p\n", (int)getpid(), p);
    *p = atoi(argv[1]); // assign value to addr stored in p
    while (1)
    {
        Spin(1);
        *p = *p + 1;
        printf("(%d) value of p: %d\n", getpid(), *p);
    }
    return 0;
}
```

Memory is just an array of bytes; to `read` memory, one must specify an
`address` to be able to access the data stored there; to `write` memory, one
must also specify the data to be written to the given address.

A program keeps all of its data structures in memory, and accesses them through
various instructions, like `loads` and `stores` or other explicit instructions
that access memory in doing their work. Don’t forget that each instruction of
the program is in memory too; thus memory is accessed on each instruction fetch.

Each process accesses its own private `virtual address space` (sometimes just
called its `address space`), which the OS somehow maps onto the physical memory
of the machine. As far as the running program is concerned, it has physical
memory all to itself. The reality, however, is that physical memory is a shared
resource, managed by the operating system.

## 2.3 Concurrency

Crux: HOW TO BUILD CORRECT CONCURRENT PROGRAMS

- concurrency: 并发, in a period of time
- parallelism: 并行, at the same time

You can think of a thread as a function running within the same memory space as
other functions, with more than one of them active at a time. In this example,
each thread starts running in a routine called `worker()`, in which it simply
increments a counter in a loop for loops number of times.

```c
#include <stdio.h>
#include <stdlib.h>
#include "common.h"
#include "common_threads.h"

volatile int counter = 0;
int loops;

void *worker(void *arg)
{
    int i;
    for (i = 0; i < loops; i++)
    {
        counter++;
    }
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: threads <loops>\n");
        exit(1);
    }
    loops = atoi(argv[1]);
    pthread_t p1, p2;
    printf("Initial value : %d\n", counter);
    Pthread_create(&p1, NULL, worker, NULL);
    Pthread_create(&p2, NULL, worker, NULL);
    Pthread_join(p1, NULL);
    Pthread_join(p2, NULL);
    printf("Final value   : %d\n", counter);
    return 0;
}
```

When the input value of `loops` is set to *N*, we would expect the final output
of the program to be *2N*.

In this run, when we gave an input value of 100,000, instead of getting a final
value of 200,000, we instead first get 143,012. Then, when we run the program a
second time, we not only again get the wrong value, but also a different value
than the last time.

As it turns out, the reason for these odd and unusual outcomes relate to how
instructions are executed, which is one at a time. Unfortunately, a key part of
the program above, where the shared counter is incremented, takes three
instructions:

1. one to load the value of the counter from memory into a register
2. one to increment it
3. and one to store it back into memory.

Because these three instructions do not execute **atomically** (all at once),
strange things can happen.

## 2.4 Persistence

Crux: HOW TO STORE DATA PERSISTENTLY

In system memory, data can be easily lost, as devices such as DRAM store values
in a **volatile** manner; when power goes away or the system crashes, any data
in memory is lost.

The software in the operating system that usually manages the disk is called
the **file system**; it is thus responsible for storing any files the user
creates in a reliable and efficient manner on the disks of the system.

Unlike the abstractions provided by the OS for the CPU and memory, the OS does
not create a private, virtualized disk for each application. Rather, it is
assumed that often times, users will want to **share** information that is in
files.

```c
#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int fd = open("/tmp/file", O_WRONLY | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
    assert(fd >= 0);
    char buffer[20];
    sprintf(buffer, "hello world\n");
    int rc = write(fd, buffer, strlen(buffer));
    assert(rc == (strlen(buffer)));
    fsync(fd);
    close(fd);
    return 0;
}
```

To accomplish this task, the program makes three calls into the operating
system.

1. a call to `open()`, opens the file and creates it
2. `write()` writes some data to the file
3. `close()`, simply closes the file thus indicating the program won’t be
  writing any more data to it

These **system calls** are routed to the part of the operating system called
the **file system**, which then handles the requests and returns some kind of
error code to the user.

The file system has to do a fair bit of work:

First figuring out where on disk this new data will reside, and then keeping
track of it in various structures the file system maintains. Doing so requires
issuing I/O requests to the underlying storage device, to either read existing
structures or update (write) them.

For performance reasons, most file systems first delay such writes for a while,
hoping to batch them into larger groups. To handle the problems of system
crashes during writes, most file systems incorporate some kind of intricate
write protocol, such as **journaling** or **copy-on-write**, carefully ordering
writes to disk to ensure that if a failure occurs during the write sequence, the
system can recover to reasonable state afterwards.

To make different common operations efficient, file systems employ many
different data structures and access methods, from simple lists to complex
b-trees.

## 2.5 Design Goals

What an OS actually does: it takes physical **resources**, such as a CPU,
memory, or disk, and **virtualizes** them. It handles tough and tricky issues
related to **concurrency**. And it stores files **persistently**, thus making
them safe over the long-term.

One of the most basic goals is to build up some **abstractions** in order to
make the system convenient and easy to use. Abstractions are fundamental to
everything we do in computer science. Abstraction makes it possible to write a
large program by dividing it into small and understandable pieces, to write
such a program in a high-level language like C without thinking about assembly,
to write code in assembly without thinking about logic gates, and to build a
processor out of gates without thinking too much about transistors. Abstraction
is so fundamental that sometimes we forget its importance, but we won’t here;
thus, in each section, we’ll discuss some of the major abstractions that have
developed over time, giving you a way to think about pieces of the OS.

One goal in designing and implementing an operating system is to provide high
**performance**; another way to say this is our goal is to **minimize the
overheads** of the OS. Virtualization and making the system easy to use are
well worth it, but not at any cost; thus, we must strive to provide
virtualization and other OS features without excessive overheads. These
overheads arise in a number of forms: extra time (more instructions) and extra
space (in memory or on disk).

Another goal will be to provide **protection** between applications, as well as
between the OS and applications. Because we wish to allow many programs to run
at the same time, we want to make sure that the malicious or accidental bad
behavior of one does not harm others; we certainly don’t want an application to
be able to harm the OS itself (as that would affect all programs running on the
system). Protection is at the heart of one of the main principles underlying an
operating system, which is that of isolation; isolating processes from one
another is the key to protection and thus underlies much of what an OS must do.

The operating system must also run non-stop; when it fails, all applications
running on the system fail as well. Because of this dependence, operating
systems often strive to provide a high degree of **reliability**.

Other goals make sense: **energy-efficiency** is important in our increasingly
green world; **security** (an extension of protection, really) against
malicious applications is critical, especially in these highly-networked times;
**mobility** is increasingly important as OSes are run on smaller and smaller
devices. Depending on how the system is used, the OS will have different goals
and thus likely be implemented in at least slightly different ways. However,
many of the principles we will present on how to build an OS are useful on a
range of different devices.

## 2.6 Some History

### Early Operating Systems: Just Libraries

Basically, it was just a set of libraries of commonly-used function. Usually,
on these old mainframe systems, one program ran at a time, as controlled by a
human operator. Much of what you think a modern OS would do (e.g., deciding
what order to run jobs in) was performed by this operator.

This mode of computing was known as **batch** processing, as a number of jobs
were set up and then run in a “batch” by the operator. Computers, as of that
point, were not used in an interactive manner, because of cost: it was simply
too expensive to let a user sit in front of the computer and use it, as most of
the time it would just sit idle then, costing the facility hundreds of
thousands of dollars per hour.

### Beyond Libraries: Protection

In moving beyond being a simple library of commonly-used services, operating
systems took on a more central role in managing machines. One important aspect
of this was the realization that code run on behalf of the OS was special; it
had control of devices and thus should be treated differently than normal
application code.

Thus, the idea of a **system call** was invented, pioneered by the Atlas
computing system. Instead of providing OS routines as a library (where you just
make a procedure call to access them), the idea here was to add a special pair
of hardware instructions and hardware state to make the transition into the OS
a more formal, controlled process.

The key difference between a **system call** and a **procedure call** is that a
system call transfers control (i.e., jumps) into the OS while simultaneously
raising the **hardware privilege level**. User applications run in what is
referred to as **user mode** which means the hardware restricts what
applications can do; for example, an application running in user mode can’t
typically initiate an I/O request to the disk, access any physical memory page,
or send a packet on the network. When a system call is initiated (usually
through a special hardware instruction called a **trap**), the hardware
transfers control to a pre-specified **trap handler** (that the OS set up
previously) and simultaneously raises the privilege level to **kernel mode**. In
kernel mode, the OS has full access to the hardware of the system and thus can
do things like initiate an I/O request or make more memory available to a
program. When the OS is done servicing the request, it passes control back to
the user via a special **return-from-trap** instruction, which reverts to user
mode while simultaneously passing control back to where the application left
off.

### The Era of Multiprogramming

Where operating systems really took off was in the era of computing beyond the
mainframe, that of the **minicomputer**.

In particular, **multiprogramming** became commonplace due to the desire to
make better use of machine resources. Instead of just running one job at a
time, the OS would load a number of jobs into memory and switch rapidly between
them, thus improving CPU utilization. This switching was particularly important
because I/O devices were slow; having a program wait on the CPU while its I/O
was being serviced was a waste of CPU time.

The desire to support multiprogramming and overlap in the presence of I/O and
interrupts forced innovation in the conceptual development of operating systems
along a number of directions. Issues such as **memory protection** became
important. Understanding how to deal with the concurrency issues introduced by
multiprogramming was also critical; making sure the OS was behaving correctly
despite the presence of interrupts is a great challenge.

One of the major practical advances of the time was the introduction of the
UNIX operating system, primarily thanks to Ken Thompson (and Dennis Ritchie) at
Bell Labs. UNIX took many good ideas from different operating systems, but made
them simpler and easier to use. Soon this team was shipping tapes containing
UNIX source code to people around the world, many of whom then got involved and
added to the system themselves.

### The Modern Era

Beyond the minicomputer came a new type of machine, cheaper, faster, and for
the masses: the **personal computer**, or **PC** as we call it today.

Unfortunately, for operating systems, the PC at first represented a great leap
backwards, as early systems forgot (or never knew of) the lessons learned in
the era of minicomputers. For example, early operating systems such as DOS (the
Disk Operating System, from Microsoft) didn’t think memory protection was
important.

Fortunately, after some years of suffering, the old features of minicomputer
operating systems started to find their way onto the desktop. Even today’s cell
phones run operating systems (such as Linux) that are much more like what a
minicomputer ran in the 1970s than what a PC ran in the 1980s (thank goodness).

- THE IMPORTANCE OF UNIX
- AND THEN CAME LINUX

## 2.7 Summary

- virtualization of the CPU and memory
- concurrency
- persistence via devices and file systems

## Homework

- simulation
- real-world code: <https://github.com/remzi-arpacidusseau/ostep-projects>
