# 25. A Dialogue on Concurrency

There are certain types of programs that we call **multi-threaded**
applications; each **thread** is kind of like an independent agent running
around in this program, doing things on the program’s behalf. But these threads
access memory, if we don’t coordinate access to memory between threads, the
program won’t work as expected.

First, the OS must support multi-threaded applications with primitives such as
**locks** and **condition variables**. Second, the OS itself was the first
concurrent program —— it must access its own memory very carefully or many
strange and terrible things will happen.
