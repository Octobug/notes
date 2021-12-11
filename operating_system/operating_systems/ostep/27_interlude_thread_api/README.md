# 27. Interlude: Thread API

CRUX: **HOW TO CREATE AND CONTROL THREADS**

## 27.1 Thread Creation

The first thing you have to be able to do to write a multi-threaded program is
to create new threads, and thus some kind of thread creation interface must
exist. In POSIX, it is easy:

```c
#include <pthread.h>

int pthread_create(pthread_t *thread,
                   const pthread_attr_t *attr,
                   void *(*start_routine)(void *),
                   void *arg);
```

There are four arguments: `thread`, `attr`, `start routine`, and `arg`. The
first, `thread`, is a pointer to a structure of type `pthread_t`; we’ll use
this structure to interact with this thread, and thus we need to pass it to
`pthread_create()` in order to initialize it.

The second argument, `attr`, is used to specify any attributes this thread
might have. An attribute is initialized with a separate call to
`pthread_attr_init()`.

The third argument is a **function pointer**: a function name (`start_routine`),
which is passed a single argument of type `void *`, and which returns a value
of type `void *` (i.e.,a **void pointer**).

If this routine instead required an integer argument, instead of a void
pointer, the declaration would look like this:

```c
#include <pthread.h>

int pthread_create(pthread_t *thread,
                   const pthread_attr_t *attr,
                   void *(*start_routine)(int),
                   int arg);
```

If instead the routine took a void pointer as an argument, but returned an
integer, it would look like this:

```c
#include <pthread.h>

int pthread_create(pthread_t *thread,
                   const pthread_attr_t *attr,
                   int (*start_routine)(void *),
                   void *arg);
```

Finally, the fourth argument, `arg`, is exactly the argument to be passed to
the function where the thread begins execution. Why do we need these void
pointers? The answer is quite simple: having a void pointer as an argument to
the function `start_routine` allows us to pass in *any* type of argument;
having it as a return value allows the thread to return any type of result.

```c
#include <assert.h>
#include <stdio.h>
#include <pthread.h>

typedef struct
{
    int a;
    int b;
} myarg_t;

void *mythread(void *arg)
{
    myarg_t *args = (myarg_t *)arg;
    printf("%d %d\n", args->a, args->b);
    return NULL;
}

int main(int argc, char *argv[])
{
    pthread_t p;
    myarg_t args = {10, 20};

    int rc = pthread_create(&p, NULL, mythread, &args);
    assert(rc == 0);
    (void)pthread_join(p, NULL);
    printf("done\n");
    return 0;
}
```

Here we just create a thread that is passed two arguments, packaged into a
single type we define ourselves (`myarg_t`). The thread, once created, can
simply cast its argument to the type it expects and thus unpack the arguments
as desired.

Once you create a thread, you really have another live executing entity,
complete with its own call stack, running within the same address space as all
the currently existing threads in the program.

## 27.2 Thread Completion

What happens if you want to wait for a thread to complete? You need to do
something special in order to wait for completion; in particular, you must call
the routine `pthread_join()`.

`int pthread_join(pthread_t thread, void **value_ptr);`

This routine takes two arguments. The first is of type `pthread_t`, and is used
to specify which thread to wait for. This variable is initialized by the thread
creation routine; if you keep it around, you can use it to wait for that thread
to terminate.

The second argument is a pointer to the return value you expect to get back.
Because the routine can return anything, it is defined to return a pointer to
void; because the `pthread_join()` routine *changes* the value of the passed in
argument, you need to pass in a pointer to that value, not just the value
itself.

```c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "common_threads.h"

typedef struct
{
    int a;
    int b;
} myarg_t;

typedef struct
{
    int x;
    int y;
} myret_t;

void *mythread(void *arg)
{
    myarg_t *args = (myarg_t *)arg;
    printf("args %d %d\n", args->a, args->b);
    myret_t *rvals = malloc(sizeof(myret_t));
    assert(rvals != NULL);
    rvals->x = 1;
    rvals->y = 2;
    return (void *)rvals;
}

int main(int argc, char *argv[])
{
    pthread_t p;
    myret_t *rvals;
    myarg_t args = {10, 20};
    Pthread_create(&p, NULL, mythread, &args);
    Pthread_join(p, (void **)&rvals);
    printf("returned %d %d\n", rvals->x, rvals->y);
    free(rvals);
    return 0;
}
```

In the code, a single thread is again created, and passed a couple of arguments
via the `myarg_t` structure. To return values, the `myret_t` type is used. Once
the thread is finished running, the main thread, which has been waiting inside
of the `pthread_join()` routine, then returns, and we can access the values
returned from the thread, namely whatever is in `myret_t`.

First, often times we don’t have to do all of this painful packing and
unpacking of arguments. If we just create a thread with no arguments, we can
pass `NULL` in as an argument when the thread is created. Similarly, we can
pass `NULL` into `pthread_join()` if we don’t care about the return value.

```c
#include <stdio.h>
#include <pthread.h>
#include "common_threads.h"

void *mythread(void *arg)
{
    long long int value = (long long int)arg;
    printf("%lld\n", value);
    return (void *)(value + 1);
}

int main(int argc, char *argv[])
{
    pthread_t p;
    long long int rvalue;
    Pthread_create(&p, NULL, mythread, (void *)100);
    Pthread_join(p, (void **)&rvalue);
    printf("returned %lld\n", rvalue);
    return 0;
}
```

Second, if we are just passing in a single value, we don’t have to package it
up as an argument. In this case, life is a bit simpler, as we don’t have to
package arguments and return values inside of structures.

Third, we should note that one has to be extremely careful with how values are
returned from a thread. In particular, never return a pointer which refers to
something allocated on the thread’s call stack. Here is an example of a
dangerous piece of code, modified from the example above.

```c
void *mythread(void *arg)
{
    myarg_t *m = (myarg_t *)arg;
    printf("%d %d\n", m->a, m->b);
    myret_t r; // ALLOCATED ON STACK: BAD!
    r.x = 1;
    r.y = 2;
    return (void *)&r;
}
```

In this case, the variable `r` is allocated on the stack of mythread. However,
when it returns, the value is automatically deallocated, and thus, passing back
a pointer to a now deallocated variable will lead to all sorts of bad results.
Certainly, when you print out the values you think you returned, you’ll
probably be surprised.

Finally, you might notice that the use of `pthread_create()` to create a
thread, followed by an immediate call to `pthread_join()`, is a pretty strange
way to create a thread. In fact, there is an easier way to accomplish this
exact task; it’s called a **procedure call**. Clearly, we’ll usually be creating
more than just one thread and waiting for it to complete, otherwise there is
not much purpose to using threads at all.

We should note that not all code that is multi-threaded uses the join routine.
For example, a multi-threaded web server might create a number of worker
threads, and then use the main thread to accept requests and pass them to the
workers, indefinitely. Such long-lived programs thus may not need to join.
However, a parallel program that creates threads to execute a particular task
(in parallel) will likely use join to make sure all such work completes before
exiting or moving onto the next stage of computation.

## 27.3 Locks

Beyond thread creation and join, probably the next most useful set of functions
provided by the POSIX threads library are those for providing mutual exclusion
to a critical section via **locks**. The most basic pair of routines to use for
this purpose is provided by the following:

- `int pthread_mutex_lock(pthread_mutex_t *mutex);`
- `int pthread_mutex_unlock(pthread_mutex_t *mutex);`

When you have a region of code that is a **critical section**, and thus needs
to be protected to ensure correct operation, locks are quite useful. You can
probably imagine what the code looks like:

```c
pthread_mutex_t lock;
pthread_mutex_lock(&lock);
x = x + 1; // or whatever your critical section is
pthread_mutex_unlock(&lock);
```

The intent of the code is as follows: if no other thread holds the lock when
`pthread_mutex_lock()` is called, the thread will acquire the lock and enter
the critical section. If another thread does indeed hold the lock, the thread
trying to grab the lock will not return from the call until it has acquired the
lock. Of course, many threads may be stuck waiting inside the lock acquisition
function at a given time; only the thread with the lock acquired, however,
should call unlock.

Unfortunately, this code is broken, in two important ways. The first problem is
a **lack of proper initialization**. All locks must be properly initialized in
order to guarantee that they have the correct values to begin with and thus
work as desired when lock and unlock are called.

With POSIX threads, there are two ways to initialize locks. One way to do this
is to use `PTHREAD_MUTEX_INITIALIZER`, as follows:

`pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;`

Doing so sets the lock to the default values and thus makes the lock usable.
The dynamic way to do it is to make a call to `pthread_mutex_init()`, as
follows:

```c
int rc = pthread_mutex_init(&lock, NULL);
assert(rc == 0); // always check success!
```

The first argument to this routine is the address of the lock itself, whereas
the second is an optional set of attributes. Passing `NULL` in simply uses the
defaults. Either way works, but we usually use the dynamic (latter) method.
Note that a corresponding call to `pthread_mutex_destroy()` should also be
made, when you are done with the lock.

The second problem with the code above is that it fails to check error codes
when calling lock and unlock. Just like virtually any library routine you call
in a UNIX system, these routines can also fail! If your code doesn’t properly
check error codes, the failure will happen silently, which in this case could
allow multiple threads into a critical section. Minimally, use wrappers, which
assert that the routine succeeded; more sophisticated (non-toy) programs, which
can’t simply exit when something goes wrong, should check for failure and do
something appropriate when the lock or unlock does not succeed.

*An Example Wrapper*.

```c
// Use this to keep your code clean but check for failures
// Only use if exiting program is OK upon failure
void Pthread_mutex_lock(pthread_mutex_t *mutex)
{
    int rc = pthread_mutex_lock(mutex);
    assert(rc == 0);
}
```

The lock and unlock routines are not the only routines within the pthreads
library to interact with locks. In particular, here are two more routines which
may be of interest:

```c
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_timedlock(pthread_mutex_t *mutex,
                            struct timespec *abs_timeout);
```

These two calls are used in lock acquisition. The `trylock` version returns
failure if the lock is already held; the `timedlock` version of acquiring a
lock returns after a timeout or after acquiring the lock, whichever happens
first. Thus, the timedlock with a timeout of zero degenerates to the trylock
case. Both of these versions should generally be avoided; however, there are a
few cases where avoiding getting stuck (perhaps indefinitely) in a lock
acquisition routine can be useful.

## 27.4 Condition Variables

The other major component of any threads library, and certainly the case with
POSIX threads, is the presence of a **condition variable**. Condition variables
are useful when some kind of signaling must take place between threads, if one
thread is waiting for another to do something before it can continue. Two
primary routines are used by programs wishing to interact in this way:

```c
int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
int pthread_cond_signal(pthread_cond_t *cond);
```

To use a condition variable, one has to in addition have a lock that is
associated with this condition. When calling either of the above routines, this
lock should be held.

The first routine, `pthread_cond_wait()`, puts the calling thread to sleep, and
thus waits for some other thread to signal it, usually when something in the
program has changed that the now-sleeping thread might care about. A typical
usage looks like this:

```c
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

Pthread_mutex_lock(&lock);
while (ready == 0)
    Pthread_cond_wait(&cond, &lock);
Pthread_mutex_unlock(&lock);
```

Note that one could use `pthread_cond_init()` (and corresponding the
`pthread_cond_destroy()` call) instead of the static initializer
`PTHREAD_COND_INITIALIZER`.

In this code, after initialization of the relevant lock and condition, a thread
checks to see if the variable `ready` has yet been set to something other than
zero. If not, the thread simply calls the wait routine in order to sleep until
some other thread wakes it.

The code to wake a thread, which would run in some other thread, looks like
this:

```c
Pthread_mutex_lock(&lock);
ready = 1;
Pthread_cond_signal(&cond);
Pthread_mutex_unlock(&lock);
```

A few things to note about this code sequence. First, when signaling (as well
as when modifying the global variable `ready`), we always make sure to have the
lock held. This ensures that we don’t accidentally introduce a race condition
into our code.

Second, you might notice that the wait call takes a lock as its second
parameter, whereas the signal call only takes a condition. The reason for this
difference is that the wait call, in addition to putting the calling thread to
sleep, *releases* the lock when putting said caller to sleep. Imagine if it did
not: how could the other thread acquire the lock and signal it to wake up?
However, *before* returning after being woken, the `pthread_cond_wait()`
re-acquires the lock, thus ensuring that any time the waiting thread is running
between the lock acquire at the beginning of the wait sequence, and the lock
release at the end, it holds the lock.

One last oddity: the waiting thread re-checks the condition in a while loop,
instead of a simple if statement. In general, using a while loop is the simple
and safe thing to do. Although it rechecks the condition, there are some
pthread implementations that could spuriously wake up a waiting thread; in such
a case, without rechecking, the waiting thread will continue thinking that the
condition has changed even though it has not. It is safer thus to view waking
up as a hint that something might have changed, rather than an absolute fact.

Note that sometimes it is tempting to use a simple flag to signal between two
threads, instead of a condition variable and associated lock. For example, we
could rewrite the waiting code above to look more like this in the waiting code:

```c
while (ready == 0)
    ; // spin
```

The associated signaling code would look like this:

```c
ready = 1;
```

**Don’t** ever do this, for the following reasons.

- First, it performs poorly in many cases (spinning for a long time just wastes
  CPU cycles).
- Second, it is error prone. As recent research shows, it is surprisingly easy
  to make mistakes when using flags (as above) to synchronize between threads;
  in that study, roughly half the uses of these `ad hoc` synchronizations were
  buggy! Don’t be lazy; use condition variables even when you think you can get
  away without doing so.

## 27.5 Compiling and Running

To compile them, you must include the header pthread.h in your code. On the
link line, you must also explicitly link with the pthreads library, by adding
the `-pthread` flag.

To compile a simple multi-threaded program, all you have to do is the following:

```sh
gcc -o main main.c -Wall -pthread
```

As long as `main.c` includes the pthreads header, you have now successfully
compiled a concurrent program.

## 27.6 Summary

The basics of the pthread library including **thread creation**,
**building mutual exclusion** via **locks**, and **signaling** and **waiting**
via **condition variables**. You don’t need much else to write robust and
efficient multi-threaded code, except patience and a great deal of care!

There are other aspects of the API that are interesting; if you want more
information, type `man -k pthread` on a Linux system to see over one hundred
APIs that make up the entire interface. However, the basics discussed herein
should enable you to build sophisticated multi-threaded programs. The hard part
with threads is not the APIs, but rather the tricky logic of how you build
concurrent programs.

### THREAD API GUIDELINES

- **Keep it simple.** Above all else, any code to lock or signal between
  threads should be as simple as possible. Tricky thread interactions lead to
  bugs.
- **Minimize thread interactions.** Try to keep the number of ways in which
  threads interact to a minimum. Each interaction should be carefully thought
  out and constructed with tried and true approaches.
- **Initialize locks and condition variables.** Failure to do so will lead to
  code that sometimes works and sometimes fails in very strange ways.
- **Check your return codes.** Of course, in any C and UNIX programming you do,
  you should be checking each and every return code, and it’s true here as
  well. Failure to do so will lead to bizarre and hard to understand behavior.
- **Be careful with how you pass arguments to, and return values from,
  threads.** In particular, any time you are passing a reference to a variable
  allocated on the stack, you are probably doing something wrong.
- **Each thread has its own stack.** As related to the point above, please
  remember that each thread has its own stack. Thus, if you have a
  locally-allocated variable inside of some function a thread is executing, it
  is essentially *private* to that thread; no other thread can (easily) access
  it. To share data between threads, the values must be in the **heap** or
  otherwise some locale that is globally accessible.
- **Always use condition variables to signal between threads.** While it is
  often tempting to use a simple flag, don’t do it.
- **Use the manual pages.** On Linux, in particular, the pthread man pages are
  highly informative and discuss much of the nuances presented here, often in
  even more detail.

## Homework (Code)

tool: `helgrind`

1. `valgrind --tool=helgrind main-race`
