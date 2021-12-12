# 5. Interlude: Process API

UNIX presents one of the most intriguing ways to create a new process with a
pair of system calls: `fork()` and `exec()`. A third routine, `wait()`, can be
used by a process wishing to wait for a process it has created to complete.

CRUX: **HOW TO CREATE AND CONTROL PROCESSES**

What interfaces should the OS present for process creation and control? How
should these interfaces be designed to enable powerful functionality, ease of
use, and high performance?

## 5.1 The `fork()` System Call

The `fork()` system call is used to create a new process. However, be
forewarned: it is certainly the strangest routine you will ever call.

Figure 5.1: **Calling fork() (p1.c)**

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int)getpid());
    int rc = fork();
    if (rc < 0)
    {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int)getpid());
    }
    else
    {
        // parent goes down this path (original process)
        printf("hello, I am parent of %d (pid:%d)\n",
               rc, (int)getpid());
    }
    return 0;
}
```

```sh
./p1   
hello world (pid:10122)
hello, I am parent of 10123 (pid:10122)
hello, I am child (pid:10123)

./p1
hello world (pid:29146)
hello, I am child (pid:29147)
hello, I am parent of 29147 (pid:29146)
```

In UNIX systems, the **PID** is used to name the process if one wants to do
something with the process, such as stop it from running.

The process calls the `fork()` system call, which the OS provides as a way to
create a new process. The odd part: the process that is created is an (almost)
*exact copy of the calling process*. That means that to the OS, it now looks
like there are two copies of the program `p1` running, and both are about to
return from the `fork()` system call. The newly-created process (called the
**child**, in contrast to the creating parent) doesn’t start running at
`main()`, like you might expect (note, the “hello, world” message only got
printed out once); rather, it just comes into life as if it had called `fork()`
itself.

You might have noticed: the child isn’t an *exact copy*. Specifically, although
it now has its own copy of the address space (i.e., its own private memory),
its own registers, its own PC, and so forth, the value it returns to the caller
of `fork()` is different. Specifically, while the parent receives the PID of
the newly-created child, the child receives a return code of zero. This
differentiation is useful, because it is simple then to write the code that
handles the two different cases (as above).

You might also have noticed: the output (of `p1.c`) is not deterministic. When
the child process is created, there are now two active processes in the system
that we care about: the parent and the child. Assuming we are running on a
system with a single CPU, then either the child or the parent might run at that
point. In our example, the parent did and thus printed out its message first.
In other cases, the opposite might happen, as we show in this output trace:

The CPU **scheduler** determines which process runs at a given moment in time;
because the scheduler is complex, we cannot usually make strong assumptions
about what it will choose to do, and hence which process will run first. This
**nondeterminism**, as it turns out, leads to some interesting problems,
particularly in **multi-threaded programs**.

## 5.2 The `wait()` System Call

Figure 5.2: **Calling fork() And wait() (p2.c)**

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int)getpid());
    int rc = fork();
    if (rc < 0)
    {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int)getpid());
        sleep(1);
    }
    else
    {
        // parent goes down this path (original process)
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n",
               rc, wc, (int)getpid());
    }
    return 0;
}
```

```sh
./p2
hello world (pid:14394)
hello, I am child (pid:14397)
hello, I am parent of 14397 (wc:14397) (pid:14394)
```

It is quite useful for a parent to wait for a child process to finish what it
has been doing. This task is accomplished with the `wait()` system call (or its
more complete sibling `waitpid()`).

In this example (p2.c), the parent process calls `wait()` to delay its
execution until the child finishes executing. When the child is done, `wait()`
returns to the parent.

Adding a `wait()` call to the code above makes the output deterministic.

If the parent does happen to run first, it will immediately call `wait()`; this
system call won’t return until the child has run and exited (There are a few
cases where `wait()` returns before the child exits; read the man page for more
details). Thus, even when the parent runs first, it politely waits for the
child to finish running, then `wait()` returns, and then the parent prints its
message.

## 5.3 Finally, The `exec()` System Call

A final and important piece of the process creation API is the `exec()` system
call. On Linux, there are six variants of `exec()`: `execl()`, `execlp()`,
`execle()`, `execv()`, `execvp()`, and `execvpe()`.

This system call is useful when you want to run a program that is different
from the calling program. For example, calling `fork()` in `p2.c` is only
useful if you want to keep running copies of the same program. However, often
you want to run a *different* program; `exec()` does just that.

Figure 5.3: **Calling fork(), wait(), And exec() (p3.c)**

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    printf("hello world (pid:%d)\n", (int)getpid());
    int rc = fork();
    if (rc < 0)
    {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        // child (new process)
        printf("hello, I am child (pid:%d)\n", (int)getpid());
        char *myargs[3];
        myargs[0] = strdup("wc");   // program: "wc" (word count)
        myargs[1] = strdup("p3.c"); // argument: file to count
        myargs[2] = NULL;           // marks end of array
        execvp(myargs[0], myargs);  // runs word count
        printf("this shouldn't print out");
    }
    else
    {
        // parent goes down this path (original process)
        int wc = wait(NULL);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n",
               rc, wc, (int)getpid());
    }
    return 0;
}
```

```sh
./p3 
hello world (pid:31022)
hello, I am child (pid:31023)
      36     120     990 p3.c
hello, I am parent of 31023 (wc:31023) (pid:31022)
```

In this example, the child process calls `execvp()` in order to run the program
`wc`, which is the word counting program.

The `fork()` system call is strange; its partner in crime, `exec()`, is not so
normal either. What it does: given the name of an executable (e.g., wc), and
some arguments, it **loads** code (and static data) from that executable and
overwrites its current code segment (and current static data) with it; the heap
and stack and other parts of the memory space of the program are
re-initialized. Then the OS simply runs that program, passing in any arguments
as the `argv` of that process. Thus, it does not create a new process; rather,
it transforms the currently running program (formerly `p3`) into a different
running program (`wc`). After the `exec()` in the child, it is almost as if
`p3.c` never ran; a successful call to `exec()` never returns.

## 5.4 Why? Motivating The API

TIP: **GETTING IT RIGHT (LAMPSON’S LAW)**

As Lampson states in his well-regarded “Hints for Computer Systems Design”,
“**Get it right**. Neither abstraction nor simplicity is a substitute for
getting it right.” Sometimes, you just have to do the right thing, and when you
do, it is way better than the alternatives. There are lots of ways to design
APIs for process creation; however, the combination of `fork()` and `exec()`
are simple and immensely powerful. Here, the UNIX designers simply got it
right. And because Lampson so often “got it right”, we name the law in his
honor.

Why would we build such an odd interface to what should be the simple act of
creating a new process? T

The separation of `fork()` and `exec()` is essential in building a UNIX shell,
because it lets the shell run code *after* the call to `fork()` but before the
call to `exec()`; this code can alter the environment of the about-to-be-run
program, and thus enables a variety of interesting features to be readily built.

The shell is just a user program. It shows you a **prompt** and then waits for
you to type something into it. You then type a command into it; the shell then
figures out where in the file system the executable resides, calls `fork()` to
create a new child process to run the command, calls some variant of `exec()`
to run the command, and then waits for the command to complete by calling
`wait()`. When the child completes, the shell returns from `wait()` and prints
out a prompt again, ready for your next command.

The separation of `fork()` and `exec()` allows the shell to do a whole bunch of
useful things rather easily. For example:

```sh
wc p3.c > newfile.txt
```

In the example above, the output of the program `wc` is **redirected** into the
output file `newfile.txt`. The way the shell accomplishes this task is quite
simple: when the child is created, before calling `exec()`, the shell closes
**standard output** and opens the file `newfile.txt`. By doing so, any output
from the soon-to-be-running program `wc` are sent to the file instead of the
screen.

Figure 5.4: **All Of The Above With Redirection (p4.c)**

```c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <assert.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
    int rc = fork();
    if (rc < 0)
    {
        // fork failed; exit
        fprintf(stderr, "fork failed\n");
        exit(1);
    }
    else if (rc == 0)
    {
        // child: redirect standard output to a file
        close(STDOUT_FILENO);
        open("./p4.output", O_CREAT | O_WRONLY | O_TRUNC, S_IRWXU);

        // now exec "wc"...
        char *myargs[3];
        myargs[0] = strdup("wc");   // program: "wc" (word count)
        myargs[1] = strdup("p4.c"); // argument: file to count
        myargs[2] = NULL;           // marks end of array
        execvp(myargs[0], myargs);  // runs word count
    }
    else
    {
        // parent goes down this path (original process)
        int wc = wait(NULL);
        assert(wc >= 0);
        printf("hello, I am parent of %d (wc:%d) (pid:%d)\n",
               rc, wc, (int)getpid());
    }
    return 0;
}
```

The reason this redirection works is due to an assumption about how the
operating system manages file descriptors. Specifically, UNIX systems start
looking for free file descriptors at zero. In this case, `STDOUT_FILENO` will
be the first available one and thus get assigned when `open()` is called.
Subsequent writes by the child process to the standard output file descriptor,
for example by routines such as `printf()`, will then be routed transparently
to the newly-opened file instead of the screen.

```sh
./p4
hello, I am parent of 47649 (wc:47649) (pid:47648)
```

The program `p4` called `fork()` to create a new child, and then run the `wc`
program via a call to `execvp()`. It redirected the ouput to the file
`p4.output`.

UNIX pipes are implemented in a similar way, but with the `pipe()` system call.
In this case, the output of one process is connected to an in-kernel **pipe**
(i.e., queue), and the input of another process is connected to that same pipe;
thus, the output of one process seamlessly is used as input to the next, and
long and useful chains of commands can be strung together.

ASIDE: **RTFM — READ THE MAN PAGES**

**Man pages** are the original form of documentation that exist on UNIX
systems.

Spending some time reading man pages is a key step in the growth of a systems
programmer; there are tons of useful tidbits hidden in those pages. Some
particularly useful pages to read are the man pages for whichever shell you are
using, and certainly for any system calls your program makes.

Finally, reading the man pages can save you some embarrassment. When you ask
colleagues about some intricacy of `fork()`, they may simply reply: “RTFM.”

## 5.5 Process Control And Users

Beyond `fork()`, `exec()`, and `wait()`, there are a lot of other interfaces
for interacting with processes in UNIX systems. For example, the `kill()`
system call is used to send **signals** to a process, including directives to
pause, die, and other useful imperatives. For convenience, in most UNIX shells,
certain keystroke combinations are configured to deliver a specific signal to
the currently running process; for example, control-c sends a `SIGINT`
(interrupt) to the process (normally terminating it) and control-z sends a
`SIGTSTP` (stop) signal thus pausing the process in mid-execution (you can
resume it later with a command, e.g., the `fg` built-in command found in many
shells).

The entire signals subsystem provides a rich infrastructure to deliver external
events to processes, including ways to receive and process those signals within
individual processes, and ways to send signals to individual processes as well
as entire **process groups**. To use this form of communication, a process
should use the `signal()` system call to “catch” various signals; doing so
ensures that when a particular signal is delivered to a process, it will
suspend its normal execution and run a particular piece of code in response to
the signal.

This naturally raises the question: who can send a signal to a process, and who
cannot? Generally, the systems we use can have multiple people using them at
the same time; if one of these people can arbitrarily send signals such as
`SIGINT` (to interrupt a process, likely terminating it), the usability and
security of the system will be compromised. As a result, modern systems include
a strong conception of the notion of a **user**. The user, after entering a
password to establish credentials, logs in to gain access to system resources.
The user may then launch one or many processes, and exercise full control over
them. Users generally can only control their own processes; it is the job of
the operating system to parcel out resources to each user to meet overall
system goals.

ASIDE: **THE SUPERUSER (ROOT)**

A system generally needs a user who can **administer** the system, and is not
limited in the way most users are. Such a user should be able to kill an
arbitrary process, even though that process was not started by this user. Such
a user should also be able to run powerful commands such as `shutdown`. In
UNIX-based systems, these special abilities are given to the **superuser**
(sometimes called **root**). While most users can’t kill other users processes,
the superuser can. Being root is much like being Spider-Man: with great power
comes great responsibility. Thus, to increase security (and avoid costly
mistakes), it’s usually better to be a regular user; if you do need to be root,
tread carefully, as all of the destructive powers of the computing world are
now at your fingertips.

## 5.6 Useful Tools

- `kill`
- `killall`
- `ps`
- `top`

## 5.7 Summary

We have introduced some of the APIs dealing with UNIX process creation:
`fork()`, `exec()`, and `wait()`.

ASIDE: **KEY PROCESS API TERMS**

- Each process has a name; in most systems, that name is a number known as a
  **process ID (PID)**.
- The `fork()` system call is used in UNIX systems to create a new process. The
  creator is called the **parent**; the newly created process is called the
  **child**. As sometimes occurs in real life, the child process is a nearly
  identical copy of the parent.
- The `wait()` system call allows a parent to wait for its child to complete
  execution.
- The `exec()` family of system calls allows a child to break free from its
  similarity to its parent and execute an entirely new program.
- A UNIX **shell** commonly uses `fork()`, `wait()`, and `exec()` to launch
  user commands; the separation of `fork` and `exec` enables features like
  input/output redirection, pipes, and other cool features, all without
  changing anything about the programs being run.
- Process control is available in the form of **signals**, which can cause jobs
  to stop, continue, or even terminate.
- Which processes can be controlled by a particular person is encapsulated in
  the notion of a **user**; the operating system allows multiple users onto the
  system, and ensures users can only control their own processes.
- A **superuser** can control all processes (and indeed do many other things);
  this role should be assumed infrequently and with caution for security
  reasons.

## Homework (Code)
