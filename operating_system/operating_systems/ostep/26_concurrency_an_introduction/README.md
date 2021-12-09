# 26. Concurrency: An Introduction

**Thread** is very much like a separate process, except for one difference:
they share the same address space and thus can access the same data.

The state of a single thread is thus very similar to that of a process. It has
a program counter (PC) that tracks where the program is fetching instructions
from. Each thread has its own private set of registers it uses for computation;
thus, if there are two threads that are running on a single processor, when
switching from running one (T1) to running the other (T2), a **context switch**
must take place. The context switch between threads is quite similar to the
context switch between processes, as the register state of T1 must be saved and
the register state of T2 restored before running T2. With processes, we saved
state to a **process control block (PCB)**; now, we’ll need one or more
**thread control blocks (TCBs)** to store the state of each thread of a
process. There is one major difference, though, in the context switch we
perform between threads as compared to processes: the address space remains the
same (i.e., there is no need to switch which page table we are using).

*26.1 Single-Threaded And Multi-Threaded Address Spaces*.

![Single-Threaded And Multi-Threaded Address Spaces](images/26_1_threads_address_spaces.png)

One other major difference between threads and processes concerns the stack. In
our simple model of the address space of a classic process (which we can now
call a **single-threaded** process), there is a single stack, usually residing
at the bottom of the address space (Figure 26.1, left).

However, in a multi-threaded process, each thread runs independently and of
course may call into various routines to do whatever work it is doing. Instead
of a single stack in the address space, there will be one per thread. Let’s say
we have a multi-threaded process that has two threads in it; the resulting
address space looks different (Figure 26.1, right).

In this figure, you can see two stacks spread throughout the address space of
the process. Thus, any stack-allocated variables, parameters, return values,
and other things that we put on the stack will be placed in what is sometimes
called thread-local storage.

## 26.1 Why Use Threads?

There are at least two major reasons you should use threads.

- The first is simple: **parallelism**. The task of transforming your standard
  **single-threaded** program into a program that does this sort of work on
  multiple CPUs is called **parallelization**, and using a thread per CPU to do
  this work is a natural and typical way to make programs run faster on modern
  hardware.
- The second reason is a bit more subtle: to avoid blocking program progress
  due to slow I/O. Many modern server-based applications (web servers, database
  management systems, and the like) make use of threads in their
  implementations.

Threads share an address space and thus make it easy to share data, and hence
are a natural choice when constructing these types of programs.

Processes are a more sound choice for logically separate tasks where little
sharing of data structures in memory is needed.

## 26.2 An Example: Thread Creation

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#include "common.h"
#include "common_threads.h"

void *mythread(void *arg)
{
    printf("%s\n", (char *)arg);
    return NULL;
}

int main(int argc, char *argv[])
{
    if (argc != 1)
    {
        fprintf(stderr, "usage: main\n");
        exit(1);
    }

    pthread_t p1, p2;
    printf("main: begin\n");
    Pthread_create(&p1, NULL, mythread, "A");
    Pthread_create(&p2, NULL, mythread, "B");
    // join waits for the threads to finish
    Pthread_join(p1, NULL);
    Pthread_join(p2, NULL);
    printf("main: end\n");
    return 0;
}
```

Once a thread is created, it may start running right away (depending on the
whims of the scheduler); alternately, it may be put in a “ready” but not
“running” state and thus not run yet. Of course, on a multiprocessor, the
threads could even be running at the same time.

After creating the two threads (let’s call them T1 and T2), the main thread
calls `pthread_join()`, which waits for a particular thread to complete. It
does so twice, thus ensuring T1 and T2 will run and complete before finally
allowing the main thread to run again; when it does, it will print “main: end”
and exit. Overall, three threads were employed during this run:
`the main thread`, `T1`, and `T2`.

In fact, given a sequence of instructions, there are quite a few, depending on
which thread the scheduler decides to run at a given point. Once a thread is
created, it may run immediately.

*Thread Trace (1)*.

```trace
main                                Thread 1        Thread 2
----                                --------        --------
starts running
prints "main: begin"
creates Thread 1
creates Thread 2
waits for T1
                                    runs
                                    prints "A"
                                    returns
waits for T2
                                                    runs
                                                    prints "B"
                                                    returns
prints "main: end"
```

*Thread Trace (2)*.

```trace
main                                Thread 1        Thread 2
----                                --------        --------
starts running
prints "main: begin"
creates Thread 1
                                    runs
                                    prints "A"
                                    returns
creates Thread 2
                                                    runs
                                                    prints "B"
                                                    returns
waits for T1
  returns imdmdiately; T1 is done
waits for T2
  returns imdmdiately; T2 is done
prints "main: end"
```

*Thread Trace (3)*.

```trace
main                                Thread 1        Thread 2
----                                --------        --------
starts running
prints "main: begin"
creates Thread 1
creates Thread 2
                                                    runs
                                                    prints "B"
                                                    returns
waits for T1
                                    runs
                                    prints "A"
                                    returns
waits for T2
  returns imdmdiately; T2 is done
prints "main: end"
```

We also could even see “B” printed before “A” if the scheduler decided to run
Thread 2 first even though Thread 1 was created earlier; there is no reason to
assume that a thread that is created first will run first.

As you might be able to see, one way to think about thread creation is that it
is a bit like making a function call; however, instead of first executing the
function and then returning to the caller, the system instead creates a new
thread of execution for the routine that is being called, and it runs
independently of the caller, perhaps before returning from the create, but
perhaps much later. What runs next is determined by the OS **scheduler**, and
although the scheduler likely implements some sensible algorithm, it is hard to
know what will run at any given moment in time.

Threads make life complicated: it is already hard to tell what will run when!
Computers are hard enough to understand without concurrency. Unfortunately,
with concurrency, it simply gets worse.

## 26.3 Why It Gets Worse: Shared Data
