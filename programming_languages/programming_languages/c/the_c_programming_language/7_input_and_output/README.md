# Chapter 7: Input and Output

- [Chapter 7: Input and Output](#chapter-7-input-and-output)
  - [7.1 Standard Input and Output](#71-standard-input-and-output)
  - [7.2 Formatted Output - printf](#72-formatted-output---printf)

Input and output are not part of the C language itself.

## 7.1 Standard Input and Output

`int getchar(void)` returns the next input character each time it is called, or
`EOF` when it encounters end of file. The symbolic constant `EOF` is defined in
`<stdio.h>`. The value is typically `-1`.

In many environments, a file my be substituted for the keyboard by using `<`
convention for input redirection: if a program `prog` uses `getchar`, then the
command line

```sh
prog <infile
```

causes `prog` to read characters from `infile` instead. The string `<infile` is
not included in the command-line arguments in `argv`.

Input switching is also invisible if the input comes from another program via a
pipe mechanism: on some systems, the command line

```sh
otherprog | prog
```

runs two programs `otherprog` and `prog`, and pipes the standard output of
`otherprog` into the standard input for `prog`.

The function `int putchar(int)` is used for output: `putchar(c)` puts the
character `c` on the `standard output`, which is by default the screen.
`putchar` returns the character written, or `EOF` if an error occurs.

Output can usually be directed to a file with `>filename`: if `prog` uses
`putchar`,

```sh
prog >outfile
```

will write the standard output to `outfile` instead. If pipes are supported,

```sh
prog | anotherprog
```

puts the standard output of `prog` into the standard input of `anotherprog`.

Output produced by `printf` also finds its way to the standard output. Calls to
`putchar` and `printf` may be interleaved - output happens in the order in which
the calls are made.

Each source file that refers to an input/output library function must contain
the line

```c
#include <stdio.h>
```

before the first reference. When the name is bracketed by `<` and `>` a search
is made for hte header in a standard set of places (eg. on UNIX, typically in
`/usr/include`).

## 7.2 Formatted Output - printf

>>>>> progress
