# 28. Locks

## 28.1 Locks: The Basic Idea

As an example, assume our critical section looks like this, the canonical
update of a shared variable:

```c
balance = balance + 1;
```

To use a lock, we add some code around the critical section like this:

```c
lock_t mutex; // some globally-allocated lock ’mutex’
// ...
lock(&mutex);
balance = balance + 1;
unlock(&mutex);
```

A lock is just a variable, and thus to use one, you must declare a
**lock variable** of some kind (such as `mutex` above). This lock variable
holds the state of the lock at any instant in time. It is either **available**
(or **unlocked** or **free**) and thus no thread holds the lock, or
**acquired** (or **locked** or **held**), and thus exactly one thread holds the
lock and presumably is in a critical section. We could store other information
in the data type (`lock_t`) as well, such as which thread holds the lock, or a
queue for ordering lock acquisition, but information like that is hidden from
the user of the lock.

The semantics of the `lock()` and `unlock()` routines are simple. Calling the
routine `lock()` tries to acquire the lock; if no other thread holds the lock,
the thread will acquire the lock and enter the critical section; this thread is
sometimes said to be the **owner** of the lock. If another thread then calls
`lock()` on that same lock variable (`mutex` in this example), it will not
return while the lock is held by another thread; in this way, other threads are
prevented from entering the critical section while the first thread that holds
the lock is in there.

Once the owner of the lock calls `unlock()`, the lock is now available again.
If no other threads are waiting for the lock, the state of the lock is simply
changed to free. If there are waiting threads (stuck in `lock()`), one of them
will notice (or be informed of) this change of the lock’s state, acquire the
lock, and enter the critical section.

Locks provide some minimal amount of control over scheduling to programmers. In
general, we view threads as entities created by the programmer but scheduled by
the OS, in any fashion that the OS chooses. Locks yield some of that control
back to the programmer; by putting a lock around a section of code, the
programmer can guarantee that no more than a single thread can ever be active
within that code. Thus locks help transform the chaos that is traditional OS
scheduling into a more controlled activity.

## 28.2 Pthread Locks

The name that the POSIX library uses for a lock is a **mutex**, as it is used
to provide **mutual exclusion** between threads, i.e., if one thread is in the
critical section, it excludes the others from entering until it has completed
the section. Thus, when you see the following POSIX threads code, you should
understand that it is doing the same thing as above:

```c
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

Pthread_mutex_lock(&lock); // wrapper; exits on failure
balance = balance + 1;
Pthread_mutex_unlock(&lock);
```

You might also notice here that the POSIX version passes a variable to lock and
unlock, as we may be using *different* locks to protect different variables.
Doing so can increase concurrency: instead of one big lock that is used any
time any critical section is accessed (a **coarse-grained** locking strategy),
one will often protect different data and data structures with different locks,
thus allowing more threads to be in locked code at once (a more
**fine-grained** approach).

## 28.3 Building A Lock

How should we build a lock? What hardware support is needed? What OS support?

THE CRUX: **HOW TO BUILD A LOCK**

How can we build an efficient lock? Efficient locks provide mutual exclusion at
low cost, and also might attain a few other properties we discuss below. What
hardware support is needed? What OS support?

To build a working lock, we will need some help from our old friend, the
**hardware**, as well as our good pal, the **OS**. Over the years, a number of
different hardware primitives have been added to the instruction sets of
various computer architectures.

## 28.4 Evaluating Locks

To evaluate whether a lock works (and works well), we should first establish
some basic criteria.

- The first is whether the lock does its basic task, which is to provide
  **mutual exclusion**. Basically, does the lock work, preventing multiple
  threads from entering a critical section?
- The second is **fairness**. Does each thread contending for the lock get a
  fair shot at acquiring it once it is free? Another way to look at this is by
  examining the more extreme case: does any thread contending for the lock
  **starve** while doing so, thus never obtaining it?
- The final criterion is **performance**, specifically the time overheads added
  by using the lock. There are a few different cases that are worth considering
  here.
  - One is the case of no contention; when a single thread is running and grabs
    and releases the lock, what is the overhead of doing so?
  - Another is the case where multiple threads are contending for the lock on a
    single CPU; in this case, are there performance concerns?
  - Finally, how does the lock perform when there are multiple CPUs involved,
    and threads on each contending for the lock?

  By comparing these different scenarios, we can better understand the
  performance impact of using various locking techniques, as described below.

## 28.5 Controlling Interrupts

One of the earliest solutions used to provide mutual exclusion was to disable
interrupts for critical sections; this solution was invented for
single-processor systems. The code would look like this:

```c
void lock() {
    DisableInterrupts();
}
void unlock() {
    EnableInterrupts();
}
```

Assume we are running on such a single-processor system. By turning off
interrupts (using some kind of special hardware instruction) before entering a
critical section, we ensure that the code inside the critical section will
**not** be interrupted, and thus will execute as if it were atomic. When we are
finished, we re-enable interrupts (again, via a hardware instruction) and thus
the program proceeds as usual.

The main positive of this approach is its simplicity. You certainly don’t have
to scratch your head too hard to figure out why this works. Without
interruption, a thread can be sure that the code it executes will execute and
that no other thread will interfere with it.

The negatives, unfortunately, are many.

- First, this approach requires us to allow any calling thread to perform a
  **privileged** operation (turning interrupts on and off), and thus **trust**
  that this facility is not abused. As you already know, any time we are
  required to trust an arbitrary program, we are probably in trouble. Here, the
  trouble manifests in numerous ways: a greedy program could call `lock()` at
  the beginning of its execution and thus monopolize the processor; worse, an
  errant or malicious program could call `lock()` and go into an endless loop.
  In this latter case, the OS never regains control of the system, and there is
  only one recourse: restart the system. Using interrupt disabling as a
  general-purpose synchronization solution requires too much trust in
  applications.
- Second, the approach does not work on multiprocessors. If multiple threads
  are running on different CPUs, and each try to enter the same critical
  section, it does not matter whether interrupts are disabled; threads will be
  able to run on other processors, and thus could enter the critical section.
  As multiprocessors are now commonplace, our general solution will have to do
  better than this.
- Third, turning off interrupts for extended periods of time can lead to
  interrupts becoming lost, which can lead to serious systems problems.
  Imagine, for example, if the CPU missed the fact that a disk device has
  finished a read request. How will the OS know to wake the process waiting for
  said read?
- Finally, and probably least important, this approach can be inefficient.
  Compared to normal instruction execution, code that masks or unmasks
  interrupts tends to be executed slowly by modern CPUs.

For these reasons, turning off interrupts is only used in limited contexts as a
mutual-exclusion primitive. For example, in some cases an operating system
itself will use interrupt masking to guarantee atomicity when accessing its own
data structures, or at least to prevent certain messy interrupt handling
situations from arising. This usage makes sense, as the trust issue disappears
inside the OS, which always trusts itself to perform privileged operations
anyhow.

## 28.6 A Failed Attempt: Just Using Loads/Stores

To move beyond interrupt-based techniques, we will have to rely on CPU hardware
and the instructions it provides us to build a proper lock. Let’s first try to
build a simple lock by using a single flag variable. In this failed attempt,
we’ll see some of the basic ideas needed to build a lock, and (hopefully) see
why just using a single variable and accessing it via normal loads and stores
is insufficient.

Figure 28.1: **First Attempt: A Simple Flag**

```c
typedef struct __lock_t
{
    int flag;
} lock_t;

void init(lock_t *mutex)
{
    // 0 -> lock is available, 1 -> held
    mutex->flag = 0;
}

void lock(lock_t *mutex)
{
    while (mutex->flag == 1) // TEST the flag
        ;                    // spin-wait (do nothing)
    mutex->flag = 1;         // now SET it
}

void unlock(lock_t *mutex)
{
    mutex->flag = 0;
}
```

In this first attempt (Figure 28.1), the idea is quite simple: use a simple
variable (`flag`) to indicate whether some thread has possession of a lock. The
first thread that enters the critical section will call `lock()`, which
**tests** whether the flag is equal to 1 (in this case, it is not), and then
**sets** the flag to 1 to indicate that the thread now **holds** the lock. When
finished with the critical section, the thread calls `unlock()` and clears the
flag, thus indicating that the lock is no longer held.

If another thread happens to call `lock()` while that first thread is in the
critical section, it will simply **spin-wait** in the while loop for that
thread to call `unlock()` and clear the flag. Once that first thread does so,
the waiting thread will fall out of the while loop, set the flag to 1 for
itself, and proceed into the critical section.

Figure 28.2: **Trace: No Mutual Exclusion**

```diagram
Thread 1                            Thread 2
--------                            --------
call lock()
while (flag == 1)
interrupt: switch to Thread 2
                                    call lock()
                                    while (flag == 1)
                                    flag = 1;
                                    interrupt: switch to Thread 1
flag = 1;   // set flag to 1 (too!)
```

Unfortunately, the code has two problems: one of correctness, and another of
performance. The correctness problem is simple to see once you get used to
thinking about concurrent programming. Imagine the code interleaving in Figure
28.2; assume `flag=0` to begin.

As you can see from this interleaving, with timely (untimely?) interrupts, we
can easily produce a case where *both* threads set the flag to 1 and both
threads are thus able to enter the critical section. This behavior is what
professionals call “bad” – we have obviously failed to provide the most basic
requirement: providing mutual exclusion.

The performance problem, which we will address more later on, is the fact that
the way a thread waits to acquire a lock that is already held: it endlessly
checks the value of flag, a technique known as **spin-waiting**. Spin-waiting
wastes time waiting for another thread to release a lock. The waste is
exceptionally high on a uniprocessor, where the thread that the waiter is
waiting for cannot even run (at least, until a context switch occurs)! Thus, as
we move forward and develop more sophisticated solutions, we should also
consider ways to avoid this kind of waste.

## 28.7 Building Working Spin Locks with Test-And-Set

Because disabling interrupts does not work on multiple processors, and because
simple approaches using loads and stores (as shown above) don’t work, system
designers started to invent hardware support for locking, today all systems
provide this type of support, even for single CPU systems.

The simplest bit of hardware support to understand is known as a
**test-and-set** (or **atomic exchange**) instruction. We define what the
test-and-set instruction does via the following C code snippet:

Figure 28.3: **A Simple Spin Lock Using Test-and-set**

```c
int TestAndSet(int *old_ptr, int new)
{
    int old = *old_ptr; // fetch old value at old_ptr
    *old_ptr = new;     // store ’new’ into old_ptr
    return old;         // return the old value
}

typedef struct __lock_t
{
    int flag;
} lock_t;

void init(lock_t *lock)
{
    // 0 -> lock is available, 1 -> held
    lock->flag = 0;
}

void lock(lock_t *lock)
{
    while (TestAndSet(&lock->flag, 1) == 1) // TEST the flag
        ;                                   // spin-wait (do nothing)
    lock->flag = 1;                         // now SET it
}

void unlock(lock_t *lock)
{
    lock->flag = 0;
}
```

What the test-and-set instruction does is as follows. It returns the old value
pointed to by the `ptr`, and simultaneously updates said value to `new`. The
key, of course, is that this sequence of operations is performed
**atomically**. The reason it is called “test and set” is that it enables you
to “test” the old value (which is what is returned) while simultaneously
“setting” the memory location to a new value; as it turns out, this slightly
more powerful instruction is enough to build a simple **spin lock**, as we now
examine in Figure 28.3. Or better yet: figure it out first yourself!

Let’s make sure we understand why this lock works. Imagine first the case where
a thread calls `lock()` and no other thread currently holds the lock; thus,
`flag` should be 0. When the thread calls `TestAndSet(flag, 1)`, the routine
will return the old value of `flag`, which is 0; thus, the calling thread,
which is *testing* the value of flag, will not get caught spinning in the while
loop and will acquire the lock. The thread will also atomically *set* the value
to 1, thus indicating that the lock is now held. When the thread is finished
with its critical section, it calls `unlock()` to set the flag back to zero.

The second case we can imagine arises when one thread already has the lock held
(i.e., `flag` is 1). In this case, this thread will call `lock()` and then call
`TestAndSet(flag, 1)` as well. This time, `TestAndSet()` will return the old
value at flag, which is 1, while simultaneously setting it to 1 again. As long
as the lock is held by another thread, `TestAndSet()` will repeatedly return 1,
and thus this thread will spin and spin until the lock is finally released.
When the flag is finally set to 0 by some other thread, this thread will call
`TestAndSet()` again, which will now return 0 while atomically setting the
value to 1 and thus acquire the lock and enter the critical section.

By making both the **test** (of the old lock value) and set (of the new value)
a single atomic operation, we ensure that only one thread acquires the lock.
And that’s how to build a working mutual exclusion primitive!

You may also now understand why this type of lock is usually referred to as a
**spin lock**. It is the simplest type of lock to build, and simply spins,
using CPU cycles, until the lock becomes available. To work correctly on a
single processor, it requires a **preemptive scheduler** (i.e., one that will
interrupt a thread via a timer, in order to run a different thread, from time
to time). Without preemption, spin locks don’t make much sense on a single CPU,
as a thread spinning on a CPU will never relinquish it.

ASIDE: **DEKKER’S AND PETERSON’S ALGORITHMS**

In the 1960’s, Dijkstra posed the concurrency problem to his friends, and one
of them, a mathematician named Theodorus Jozef Dekker, came up with a solution.
Unlike the solutions we discuss here, which use special hardware instructions
and even OS support, **Dekker’s algorithm** uses just loads and stores
(assuming they are atomic with respect to each other, which was true on early hardware).

Dekker’s approach was later refined by Peterson. Once again, just loads and
stores are used, and the idea is to ensure that two threads never enter a
critical section at the same time. Here is **Peterson’s algorithm** (for two
threads); see if you can understand the code. What are the `flag` and `turn`
variables used for?

```c
int flag[2];
int turn;
void init()
{
    // indicate you intend to hold the lock w/ ’flag’
    flag[0] = flag[1] = 0;
    // whose turn is it? (thread 0 or 1)
    turn = 0;
}
void lock()
{
    // ’self’ is the thread ID of caller
    flag[self] = 1;
    // make it other thread’s turn
    turn = 1 - self;
    while ((flag[1 - self] == 1) && (turn == 1 - self))
        ; // spin-wait while it’s not your turn
}
void unlock()
{
    // simply undo your intent
    flag[self] = 0;
}
```

For some reason, developing locks that work without special hardware support
became all the rage for a while, giving theory-types a lot of problems to work
on. Of course, this line of work became quite useless when people realized it
is much easier to assume a little hardware support (and indeed that support had
been around from the earliest days of multiprocessing). Further, algorithms
like the ones above don’t work on modern hardware (due to relaxed memory
consistency models), thus making them even less useful than they were before.

TIP: **THINK ABOUT CONCURRENCY AS A MALICIOUS SCHEDULER**

From this example, you might get a sense of the approach you need to take to
understand concurrent execution. What you should try to do is to pretend you
are a **malicious scheduler**, one that interrupts threads at the most
inopportune of times in order to foil their feeble attempts at building
synchronization primitives. Although the exact sequence of interrupts may be
improbable, it is possible, and that is all we need to demonstrate that a
particular approach does not work.

## 28.8 Evaluating Spin Locks

The most important aspect of a lock is **correctness**: does it provide mutual
exclusion? The answer here is yes: the spin lock only allows a single thread to
enter the critical section at a time. Thus, we have a correct lock.

The next axis is **fairness**. How fair is a spin lock to a waiting thread? Can
you guarantee that a waiting thread will ever enter the critical section? The
answer here, unfortunately, is bad news: spin locks don’t provide any fairness
guarantees. Indeed, a thread spinning may spin forever, under contention.
Simple spin locks are not fair and may lead to starvation.

The final axis is **performance**. What are the costs of using a spin lock? To
analyze this more carefully, we suggest thinking about a few different cases.
In the first, imagine threads competing for the lock on a single processor; in
the second, consider threads spread out across many CPUs.

- For spin locks, in the single CPU case, performance overheads can be quite
  painful; imagine the case where the thread holding the lock is preempted
  within a critical section. The scheduler might then run every other thread
  (imagine there are *N − 1* others), each of which tries to acquire the lock.
  In this case, each of those threads will spin for the duration of a time
  slice before giving up the CPU, a waste of CPU cycles.
- However, on multiple CPUs, spin locks work reasonably well (if the number of
  threads roughly equals the number of CPUs). The thinking goes as follows:
  imagine Thread A on CPU 1 and Thread B on CPU 2, both contending for a lock.
  If Thread A (CPU 1) grabs the lock, and then Thread B tries to, B will spin
  (on CPU 2). However, presumably the critical section is short, and thus soon
  the lock becomes available, and is acquired by Thread B. Spinning to wait for
  a lock held on another processor doesn’t waste many cycles in this case, and
  thus can be effective.

## 28.9 Compare-And-Swap

Figure 28.4: **Compare-and-swap**

```c
int CompareAndSwap(int *ptr, int expected, int new)
{
    int actual = *ptr;
    if (actual == expected)
        *ptr = new;
    return actual;
}
```
