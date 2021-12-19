# 34. Summary Dialogue on Concurrency

First, keep it simple! Avoid complex interactions between threads, and use
well-known and tried-and-true ways to manage thread interactions.

Second, only use concurrency when absolutely needed; avoid it if at all
possible. There is nothing worse than premature optimization of a program.

Third, if you really need parallelism, seek it in other simplified forms. For
example, the Map-Reduce method for writing parallel data analysis code is an
excellent example of achieving parallelism without having to handle any of the
horrific complexities of locks, condition variables, and the other nasty things
we’ve talked about.
