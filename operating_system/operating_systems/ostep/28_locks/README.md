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
