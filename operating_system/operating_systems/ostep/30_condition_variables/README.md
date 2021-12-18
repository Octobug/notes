# 30. Condition Variables

In particular, there are many cases where a thread wishes to check whether a
**condition** is true before continuing its execution. For example, a parent
thread might wish to check whether a child thread has completed before
continuing (this is often called a `join()`); how should such a wait be
implemented? Let’s look at Figure 30.1.

Figure 30.1: **A Parent Waiting For Its Child**

```c
void *child(void *arg)
{
    printf("child\n");
    // XXX how to indicate we are done?
    return NULL;
}

int main(int argc, char *argv[])
{
    printf("parent: begin\n");
    pthread_t c;
    Pthread_create(&c, NULL, child, NULL); // create child
    // XXX how to wait for child?
    printf("parent: end\n");
    return 0;
}
```

What we would like to see here is the following output:

```diagram
parent: begin
child
parent: end
```

Figure 30.2: **Parent Waiting For Child: Spin-based Approach**

```c
volatile int done = 0;

void *child(void *arg)
{
    printf("child\n");
    done = 1;
    return NULL;
}

int main(int argc, char *argv[])
{
    printf("parent: begin\n");
    pthread_t c;
    Pthread_create(&c, NULL, child, NULL); // create child
    while (done == 0)
        ; // spin
    printf("parent: end\n");
    return 0;
}
```

We could try using a shared variable, as you see in Figure 30.2. This solution
will generally work, but it is hugely inefficient as the parent spins and
wastes CPU time. What we would like here instead is some way to put the parent
to sleep until the condition we are waiting for comes true.

THE CRUX: **HOW TO WAIT FOR A CONDITION**

In multi-threaded programs, it is often useful for a thread to wait for some
condition to become true before proceeding. The simple approach, of just
spinning until the condition becomes true, is grossly inefficient and wastes
CPU cycles, and in some cases, can be incorrect. Thus, how should a thread wait
for a condition?

## 30.1 Definition and Routines

To wait for a condition to become true, a thread can make use of what is known
as a **condition variable**. A **condition variable** is an explicit queue that
threads can put themselves on when some state of execution is not as desired
(by **waiting** on the condition); some other thread, when it changes said
state, can then wake one (or more) of those waiting threads and thus allow them
to continue (by **signaling** on the condition). The idea goes back to
Dijkstra’s use of “private semaphores”; a similar idea was later named a
“condition variable” by Hoare in his work on monitors.

To declare such a condition variable, one simply writes something like this:
`pthread_cond_t c;`, which declares `c` as a condition variable (note: proper
initialization is also required). A condition variable has two operations
associated with it: `wait()` and `signal()`. The `wait()` call is executed when
a thread wishes to put itself to sleep; the `signal()` call is executed when a
thread has changed something in the program and thus wants to wake a sleeping
thread waiting on this condition. Specifically, the POSIX calls look like this:

```c
pthread_cond_wait(pthread_cond_t *c, pthread_mutex_t *m);
pthread_cond_signal(pthread_cond_t *c);
```

Figure 30.3: **Parent Waiting For Child: Use A Condition Variable**

```c
int done = 0;
pthread_mutex_t m = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t c = PTHREAD_COND_INITIALIZER;

void thr_exit()
{
    Pthread_mutex_lock(&m);
    done = 1;
    Pthread_cond_signal(&c);
    Pthread_mutex_unlock(&m);
}

void *child(void *arg)
{
    printf("child\n");
    thr_exit();
    return NULL;
}

void thr_join()
{
    Pthread_mutex_lock(&m);
    while (done == 0)
        Pthread_cond_wait(&c, &m);
    Pthread_mutex_unlock(&m);
}

int main(int argc, char *argv[])
{
    printf("parent: begin\n");
    pthread_t p;
    Pthread_create(&p, NULL, child, NULL);
    thr_join();
    printf("parent: end\n");
    return 0;
}
```

We will often refer to these as `wait()` and `signal()` for simplicity. One
thing you might notice about the `wait()` call is that it also takes a mutex as
a parameter; it assumes that this mutex is locked when `wait()` is called. The
responsibility of `wait()` is to release the lock and put the calling thread to
sleep (atomically); when the thread wakes up (after some other thread has
signaled it), it must re-acquire the lock before returning to the caller. This
complexity stems from the desire to prevent certain race conditions from
occurring when a thread is trying to put itself to sleep.

There are two cases to consider. In the first, the parent creates the child
thread but continues running itself (assume we have only a single processor)
and thus immediately calls into `thr_join()` to wait for the child thread to
complete. In this case, it will acquire the lock, check if the child is done
(it is not), and put itself to sleep by calling `wait()` (hence releasing the
lock). The child will eventually run, print the message “child”, and call
`thr_exit()` to wake the parent thread; this code just grabs the lock, sets the
state variable `done`, and signals the parent thus waking it. Finally, the
parent will run (returning from `wait()` with the lock held), unlock the lock,
and print the final message “parent: end”.

In the second case, the child runs immediately upon creation, sets `done` to 1,
calls signal to wake a sleeping thread (but there is none, so it just returns),
and is done. The parent then runs, calls `thr_join()`, sees that `done` is 1,
and thus does not wait and returns.

One last note: you might observe the parent uses a `while` loop instead of just
an `if` statement when deciding whether to wait on the condition. While this
does not seem strictly necessary per the logic of the program, it is always a
good idea, as we will see below.

To make sure you understand the importance of each piece of the `thr_exit()`
and `thr_join()` code, let’s try a few alternate implementations. First, you
might be wondering if we need the state variable `done`. What if the code
looked like the example below? Would this work?

```c
void thr_exit()
{
    Pthread_mutex_lock(&m);
    Pthread_cond_signal(&c);
    Pthread_mutex_unlock(&m);
}

void thr_join()
{
    Pthread_mutex_lock(&m);
    Pthread_cond_wait(&c, &m);
    Pthread_mutex_unlock(&m);
}
```

Unfortunately this approach is broken. Imagine the case where the child runs
immediately and calls `thr_exit()` immediately; in this case, the child will
signal, but there is no thread asleep on the condition. When the parent runs,
it will simply call wait and be stuck; no thread will ever wake it. From this
example, you should appreciate the importance of the state variable `done`; it
records the value the threads are interested in knowing. The sleeping, waking,
and locking all are built around it.

Here is another poor implementation. In this example, we imagine that one does
not need to hold a lock in order to signal and wait. What problem could occur
here? Think about it!

```c
void thr_exit()
{
    done = 1;
    Pthread_cond_signal(&c);
}

void thr_join()
{
    if (done == 0)
        Pthread_cond_wait(&c);
}
```

The issue here is a subtle race condition. Specifically, if the parent calls
`thr_join()` and then checks the value of `done`, it will see that it is 0 and
thus try to go to sleep. But just before it calls wait to go to sleep, the
parent is interrupted, and the child runs. The child changes the state variable
done to 1 and signals, but no thread is waiting and thus no thread is woken.
When the parent runs again, it sleeps forever, which is sad.

TIP: **ALWAYS HOLD THE LOCK WHILE SIGNALING**

Although it is strictly not necessary in all cases, it is likely simplest and
best to hold the lock while signaling when using condition variables. The
example above shows a case where you *must* hold the lock for correctness;
however, there are some other cases where it is likely OK not to, but probably
is something you should avoid. Thus, for simplicity,
**hold the lock when calling signal**.

The converse of this tip, i.e., hold the lock when calling wait, is not just a
tip, but rather mandated by the semantics of wait, because wait always (a)
assumes the lock is held when you call it, (b) releases said lock when putting
the caller to sleep, and (c) re-acquires the lock just before returning. Thus,
the generalization of this tip is correct: **hold the lock when calling signal
or wait**, and you will always be in good shape.

Hopefully, from this simple join example, you can see some of the basic
requirements of using condition variables properly. To make sure you
understand, we now go through a more complicated example: the
**producer/consumer** or **bounded-buffer** problem.

## 30.2 The Producer/Consumer (Bounded Buffer) Problem

The next synchronization problem we will confront in this chapter is known as
the **producer/consumer** problem, or sometimes as the
**bounded buffer (有界缓冲区)** problem, which was first posed by Dijkstra.
Indeed, it was this very producer/consumer problem that led Dijkstra and his
co-workers to invent the generalized semaphore (which can be used as either a
lock or a condition variable).

Imagine one or more producer threads and one or more consumer threads.
Producers generate data items and place them in a buffer; consumers grab said
items from the buffer and consume them in some way.

This arrangement occurs in many real systems. For example, in a multi-threaded
web server, a producer puts HTTP requests into a work queue; consumer threads
take requests out of this queue and process them.

A bounded buffer is also used when you pipe the output of one program into
another, e.g., `grep foo file.txt | wc -l`. This example runs two processes
concurrently; `grep` writes lines from `file.txt` with the string `foo` in them
to what it thinks is standard output; the UNIX shell redirects the output to
what is called a UNIX pipe (created by the `pipe` system call). The other end
of this pipe is connected to the standard input of the process `wc`, which
simply counts the number of lines in the input stream and prints out the
result. Thus, the `grep` process is the producer; the `wc` process is the
consumer; between them is an in-kernel bounded buffer.

Because the bounded buffer is a shared resource, we must of course require
synchronized access to it, lest a race condition arise.

The first thing we need is a shared buffer, into which a producer puts data,
and out of which a consumer takes data. Let’s just use a single integer for
simplicity (you can certainly imagine placing a pointer to a data structure
into this slot instead), and the two inner routines to put a value into the
shared buffer, and to get a value out of the buffer. See Figure 30.4 for
details.

Figure 30.4: **The Put And Get Routines (Version 1)**

```c
int buffer;
int count = 0; // initially, empty

void put(int value)
{
    assert(count == 0);
    count = 1;
    buffer = value;
}

int get()
{
    assert(count == 1);
    count = 0;
    return buffer;
}
```

The `put()` routine assumes the buffer is empty (and checks this with an
assertion), and then simply puts a value into the shared buffer and marks it
full by setting `count` to 1. The `get()` routine does the opposite, setting
the buffer to empty (i.e., setting `count` to 0) and returning the value.

Now we need to write some routines that know when it is OK to access the buffer
to either put data into it or get data out of it. The conditions for this
should be obvious: only put data into the buffer when `count` is zero (i.e.,
when the buffer is empty), and only get data from the buffer when `count` is
one (i.e., when the buffer is full). If we write the synchronization code such
that a producer puts data into a full buffer, or a consumer gets data from an
empty one, we have done something wrong (and in this code, an assertion will
fire).

This work is going to be done by two types of threads, one set of which we’ll
call the **producer** threads, and the other set which we’ll call **consumer**
threads. Figure 30.5 shows the code for a producer that puts an integer into
the shared buffer `loops` number of times, and a consumer that gets the data
out of that shared buffer (forever), each time printing out the data item it
pulled from the shared buffer.

Figure 30.5: **Producer/Consumer Threads (Version 1)**

```c
void *producer(void *arg)
{
    int i;
    int loops = (int)arg;
    for (i = 0; i < loops; i++)
    {
        put(i);
    }
}

void *consumer(void *arg)
{
    int i;
    while (1)
    {
        int tmp = get();
        printf("%d\n", tmp);
    }
}
```

### A Broken Solution

Now imagine that we have just a single producer and a single consumer.
Obviously the `put()` and `get()` routines have critical sections within them,
as put() updates the buffer, and get() reads from it. However, putting a lock
around the code doesn’t work; we need something more. Not surprisingly, that
something more is some condition variables. In this (broken) first try (Figure
30.6), we have a single condition variable `cond` and associated lock `mutex.

Figure 30.6: **Producer/Consumer: Single CV And If Statement**

```c
int loops; // must initialize somewhere...
cond_t cond;
mutex_t mutex;

void *producer(void *arg)
{
    int i;
    for (i = 0; i < loops; i++)
    {
        Pthread_mutex_lock(&mutex);           // p1
        if (count == 1)                       // p2
            Pthread_cond_wait(&cond, &mutex); // p3
        put(i);                               // p4
        Pthread_cond_signal(&cond);           // p5
        Pthread_mutex_unlock(&mutex);         // p6
    }
}

void *consumer(void *arg)
{
    int i;
    for (i = 0; i < loops; i++)
    {
        Pthread_mutex_lock(&mutex);           // c1
        if (count == 0)                       // c2
            Pthread_cond_wait(&cond, &mutex); // c3
        int tmp = get();                      // c4
        Pthread_cond_signal(&cond);           // c5
        Pthread_mutex_unlock(&mutex);         // c6
        printf("%d\n", tmp);
    }
}
```

Let’s examine the signaling logic between producers and consumers. When a
producer wants to fill the buffer, it waits for it to be empty (p1–p3). The
consumer has the exact same logic, but waits for a different condition:
fullness (c1–c3).

With just a single producer and a single consumer, the code in Figure 30.6
works. However, if we have more than one of these threads (e.g., two consumers),
the solution has two critical problems. What are they?

Let’s understand the first problem, which has to do with the `if` statement
before the wait. Assume there are two consumers (Tc1 and Tc2) and one producer
(Tp). First, a consumer (Tc1) runs; it acquires the lock (c1), checks if any
buffers are ready for consumption (c2), and finding that none are, waits (c3)
(**which releases the lock**).

Then the producer (Tp) runs. It acquires the lock (p1), checks if all buffers
are full (p2), and finding that not to be the case, goes ahead and fills the
buffer (p4). The producer then signals that a buffer has been filled (p5).
Critically, this moves the first consumer (Tc1) from sleeping on a condition
variable to the ready queue; Tc1 is now able to run (but not yet running). The
producer then continues until realizing the buffer is full, at which point it
sleeps (p6, p1–p3).

Here is where the problem occurs: another consumer (Tc2) sneaks in and consumes
the one existing value in the buffer (c1, c2, c4, c5, c6). Now assume Tc1 runs;
just before returning from the wait, it re-acquires the lock and then returns.
It then calls `get()` (c4), but there are no buffers to consume! An assertion
triggers, and the code has not functioned as desired. Clearly, we should have
somehow prevented Tc1 from trying to consume because Tc2 snuck in and consumed
the one value in the buffer that had been produced. Figure 30.7 shows the
action each thread takes, as well as its scheduler state (Ready, Running, or
Sleeping) over time.

Figure 30.7: **Thread Trace: Broken Solution (Version 1)**

![Thread Trace: Broken Solution (Version 1)](images/30_7_thread_trace_broken_solution_v1.png)

The problem arises for a simple reason: after the producer woke Tc1, but
*before* Tc1 ever ran, the state of the bounded buffer changed (thanks to Tc2).
Signaling a thread only wakes them up; it is thus a *hint* that the state of the
world has changed (in this case, that a value has been placed in the buffer),
but there is no guarantee that when the woken thread runs, the state will
*still* be as desired. This interpretation of what a signal means is often
referred to as **Mesa semantics**, after the first research that built a
condition variable in such a manner; the contrast, referred to as
**Hoare semantics**, is harder to build but provides a stronger guarantee that
the woken thread will run immediately upon being woken. Virtually every system
ever built employs Mesa semantics.

### Better, But Still Broken: While, Not If

Fortunately, this fix is easy (Figure 30.8): change the if to a while. Think
about why this works; now consumer Tc1 wakes up and (with the lock held)
immediately re-checks the state of the shared variable (c2). If the buffer is
empty at that point, the consumer simply goes back to sleep (c3). The corollary
`if` is also changed to a `while` in the producer (p2).

Figure 30.8: **Producer/Consumer: Single CV And While**

```c
int loops; // must initialize somewhere...
cond_t cond;
mutex_t mutex;

void *producer(void *arg)
{
    int i;
    for (i = 0; i < loops; i++)
    {
        Pthread_mutex_lock(&mutex);           // p1
        while (count == 1)                    // p2
            Pthread_cond_wait(&cond, &mutex); // p3
        put(i);                               // p4
        Pthread_cond_signal(&cond);           // p5
        Pthread_mutex_unlock(&mutex);         // p6
    }
}

void *consumer(void *arg)
{
    int i;
    for (i = 0; i < loops; i++)
    {
        Pthread_mutex_lock(&mutex);           // c1
        while (count == 0)                    // c2
            Pthread_cond_wait(&cond, &mutex); // c3
        int tmp = get();                      // c4
        Pthread_cond_signal(&cond);           // c5
        Pthread_mutex_unlock(&mutex);         // c6
        printf("%d\n", tmp);
    }
}
```

Thanks to Mesa semantics, a simple rule to remember with condition variables is
to **always use while loops**. Sometimes you don’t have to re-check the
condition, but it is always safe to do so; just do it and be happy.

However, this code still has a bug, the second of two problems mentioned above.
It has something to do with the fact that there is only one condition variable.

The problem occurs when two consumers run first (Tc1 and Tc2) and both go to
sleep (c3). Then, the producer runs, puts a value in the buffer, and wakes one
of the consumers (say Tc1). The producer then loops back (releasing and
reacquiring the lock along the way) and tries to put more data in the buffer;
because the buffer is full, the producer instead waits on the condition (thus
sleeping). Now, one consumer is ready to run (Tc1), and two threads are
sleeping on a condition (Tc2 and Tp).

The consumer Tc1 then wakes by returning from `wait()` (c3), re-checks the
condition (c2), and finding the buffer full, consumes the value (c4). This
consumer then, critically, signals on the condition (c5), waking only one
thread that is sleeping. However, which thread should it wake?

Because the consumer has emptied the buffer, it clearly should wake the
producer. However, if it wakes the consumer Tc2 (which is definitely possible,
depending on how the wait queue is managed), we have a problem. Specifically,
the consumer Tc2 will wake up and find the buffer empty (c2), and go back to
sleep (c3). The producer Tp, which has a value to put into the buffer, is left
sleeping. The other consumer thread, Tc1, also goes back to sleep. All three
threads are left sleeping, a clear bug; see Figure 30.9 for the brutal
step-by-step of this terrible calamity.

Figure 30.9: **Thread Trace: Broken Solution (Version 2)**

![Thread Trace: Broken Solution (Version 2)](images/30_9_thread_trace_broken_solution_v2.png)

Signaling is clearly needed, but must be more directed. A consumer should not
wake other consumers, only producers, and vice-versa.

### The Single Buffer Producer/Consumer Solution

The solution here is once again a small one: use *two* condition variables,
instead of one, in order to properly signal which type of thread should wake up
when the state of the system changes. Figure 30.10 shows the resulting code.

Figure 30.10: **Producer/Consumer: Two CVs And While**

```c
cond_t empty, fill;
mutex_t mutex;

void *producer(void *arg)
{
    int i;
    for (i = 0; i < loops; i++)
    {
        Pthread_mutex_lock(&mutex);
        while (count == 1)
            Pthread_cond_wait(&empty, &mutex);
        put(i);
        Pthread_cond_signal(&fill);
        Pthread_mutex_unlock(&mutex);
    }
}

void *consumer(void *arg)
{
    int i;
    for (i = 0; i < loops; i++)
    {
        Pthread_mutex_lock(&mutex);
        while (count == 0)
            Pthread_cond_wait(&fill, &mutex);
        int tmp = get();
        Pthread_cond_signal(&empty);
        Pthread_mutex_unlock(&mutex);
        printf("%d\n", tmp);
    }
}
```

In the code above, producer threads wait on the condition **empty**, and
signals **fill**. Conversely, consumer threads wait on **fill** and signal
**empty**. By doing so, the second problem above is avoided by design: a
consumer can never accidentally wake a consumer, and a producer can never
accidentally wake a producer.

### The Correct Producer/Consumer Solution

We now have a working producer/consumer solution, albeit not a fully general
one. The last change we make is to enable more concurrency and efficiency;
specifically, we add more buffer slots, so that multiple values can be produced
before sleeping, and similarly multiple values can be consumed before sleeping.
With just a single producer and consumer, this approach is more efficient as it
reduces context switches; with multiple producers or consumers (or both), it
even allows concurrent producing or consuming to take place, thus increasing
concurrency. Fortunately, it is a small change from our current solution.

The first change for this correct solution is within the buffer structure
itself and the corresponding `put()` and `get()` (Figure 30.11). We also
slightly change the conditions that producers and consumers check in order to
determine whether to sleep or not. Figure 30.12 shows the correct waiting and
signaling logic. A producer only sleeps if all buffers are currently filled
(p2); similarly, a consumer only sleeps if all buffers are currently empty (c2).
And thus we solve the producer/consumer problem.

Figure 30.11: **The Correct Put And Get Routines**

```c
int buffer[MAX];

int fill_ptr = 0;
int use_ptr = 0;
int count = 0;

void put(int value)
{
    buffer[fill_ptr] = value;
    fill_ptr = (fill_ptr + 1) % MAX;
    count++;
}

int get()
{
    int tmp = buffer[use_ptr];
    use_ptr = (use_ptr + 1) % MAX;
    count--;
    return tmp;
}
```

Figure 30.12: **The Correct Producer/Consumer Synchronization**

```c
cond_t empty, fill;
mutex_t mutex;

void *producer(void *arg)
{
    int i;
    for (i = 0; i < loops; i++)
    {
        Pthread_mutex_lock(&mutex);            // p1
        while (count == MAX)                   // p2
            Pthread_cond_wait(&empty, &mutex); // p3
        put(i);                                // p4
        Pthread_cond_signal(&fill);            // p5
        Pthread_mutex_unlock(&mutex);          // p6
    }
}
void *consumer(void *arg)
{
    int i;
    for (i = 0; i < loops; i++)
    {
        Pthread_mutex_lock(&mutex);
        while (count == 0)                    // c1
            Pthread_cond_wait(&fill, &mutex); // c2
        int tmp = get();                      // c3
        Pthread_cond_signal(&empty);          // c4
        Pthread_mutex_unlock(&mutex);         // c5
        printf("%d\n", tmp);                  // c6
    }
}
```

TIP: **USE WHILE (NOT IF) FOR CONDITIONS**

When checking for a condition in a multi-threaded program, using a `while` loop
is always correct; using an `if` statement only might be, depending on the
semantics of signaling. Thus, always use `while` and your code will behave as
expected.

Using while loops around conditional checks also handles the case where
**spurious wakeups** occur. In some thread packages, due to details of the
implementation, it is possible that two threads get woken up though just a
single signal has taken place]. Spurious wakeups are further reason to re-check
the condition a thread is waiting on.

## 30.3 Covering Conditions

We’ll now look at one more example of how condition variables can be used. This
code study is drawn from Lampson and Redell’s paper on Pilot, the same group
who first implemented the **Mesa semantics** described above (the language they
used was Mesa, hence the name).

The problem they ran into is best shown via simple example, in this case in a
simple multi-threaded memory allocation library. Figure 30.13 shows a code
snippet which demonstrates the issue.

Figure 30.13: **Covering Conditions: An Example**

```c
// how many bytes of the heap are free?
int bytesLeft = MAX_HEAP_SIZE;

// need lock and condition too
cond_t c;
mutex_t m;

void *allocate(int size)
{
    Pthread_mutex_lock(&m);
    while (bytesLeft < size)
        Pthread_cond_wait(&c, &m);
    void *ptr = ...; // get mem from heap
    bytesLeft -= size;
    Pthread_mutex_unlock(&m);
    return ptr;
}

void free(void *ptr, int size)
{
    Pthread_mutex_lock(&m);
    bytesLeft += size;
    Pthread_cond_signal(&c); // whom to signal??
    Pthread_mutex_unlock(&m);
}
```

As you might see in the code, when a thread calls into the memory allocation
code, it might have to wait in order for more memory to become free.
Conversely, when a thread frees memory, it signals that more memory is free.
However, our code above has a problem: which waiting thread (there can be more
than one) should be woken up?

Consider the following scenario. Assume there are zero bytes free; thread *Ta*
calls `allocate(100)`, followed by thread *Tb* which asks for less memory by
calling `allocate(10)`. Both *Ta* and *Tb* thus wait on the condition and go to
sleep; there aren’t enough free bytes to satisfy either of these requests.

At that point, assume a third thread, *Tc*, calls `free(50)`. Unfortunately,
when it calls signal to wake a waiting thread, it might not wake the correct
waiting thread, *Tb*, which is waiting for only 10 bytes to be freed; *Ta*
should remain waiting, as not enough memory is yet free. Thus, the code in the
figure does not work, as the thread waking other threads does not know which
thread (or threads) to wake up.

The solution suggested by Lampson and Redell is straightforward: replace the
`pthread_cond_signal()` call in the code above with a call to
`pthread_cond_broadcast()`, which wakes up *all* waiting threads. By doing so,
we guarantee that any threads that should be woken are. The downside, of
course, can be a negative performance impact, as we might needlessly wake up
many other waiting threads that shouldn’t (yet) be awake. Those threads will
simply wake up, re-check the condition, and then go immediately back to sleep.

Lampson and Redell call such a condition a **covering condition**, as it covers
all the cases where a thread needs to wake up (conservatively); the cost, as
we’ve discussed, is that too many threads might be woken. The astute reader
might also have noticed we could have used this approach earlier (see the
producer/consumer problem with only a single condition variable). However, in
that case, a better solution was available to us, and thus we used it. In
general, if you find that your program only works when you change your signals
to broadcasts (but you don’t think it should need to), you probably have a bug;
fix it! But in cases like the memory allocator above, broadcast may be the most
straightforward solution available.

## 30.4 Summary

We have seen the introduction of another important synchronization primitive
beyond locks: condition variables. By allowing threads to sleep when some
program state is not as desired, CVs enable us to neatly solve a number of
important synchronization problems, including the famous (and still important)
producer/consumer problem, as well as covering conditions.

## Homework (Code)

> untouched
