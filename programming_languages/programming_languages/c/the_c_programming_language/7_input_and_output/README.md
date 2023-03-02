# Chapter 7: Input and Output

- [Chapter 7: Input and Output](#chapter-7-input-and-output)
  - [7.1 Standard Input and Output](#71-standard-input-and-output)
  - [7.2 Formatted Output - printf](#72-formatted-output---printf)
  - [7.3 Variable-length Argument Lists](#73-variable-length-argument-lists)
  - [7.4 Formatted Input - Scanf](#74-formatted-input---scanf)

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

The format string of `int printf(char *format, arg1, arg2, ...);` contains two
types of objects: ordinary characters, which are copied to the output stream,
and conversion specifications, each of which causes conversion and printing
of the next successive argument to `printf`. Each conversion specification
begins with a `%` and ends with a conversion character. Between the `%` and the
conversion character there may be, in order:

- A minus sign: specifies left adjustment of the converted argument.
- A number: specifies the minimum field width.
- A period: separates the field width from the precision.
- A number, the precision: specifies the maximum number of characters to be
  printed from a string, or the number of digits after the decimal point of a
  floating-point value, or the minimum number of digits for an integer.
- An `h` if the integer is to be printed as a `short`, or `l` if as a `long`.
- Conversion characters:
  - `d`, `i`: `int`; decimal number
  - `o`: `int`; unsigned octal number
  - `x`, `X`: `int`; unsigned hexadecimal number
  - `u`: `int`; unsigned decimal number
  - `c`: `int`; single character
  - `s`: `char *`; print characters from the string until a `\0` or the number
    of characters given by the precision
  - `f`: `double`; `[-]`m.dddddd
  - `e`, `E`: `double`;`[-]`m.dddddd`e+/-`
  - `g`, `G`: `double`; use `%e` or `%E` if the exponent is less than `-4` or
    greater than ot equal to the precision; otherwise use `%f`
  - `p`: `void *`; pointer
  - `%`: print a %

A width or precision may be specified as `*`, in which case the value is
computed by converting the next argument. eg. to print at most `max` characters
from a string `s`:

```c
printf("%.*s", max, s);
```

The function `sprintf` does the same conversions as `printf` does, but stores
the output in a string (the first argument):

```c
int sprintf(char *string, char *format, arg1, arg2, ...);
```

## 7.3 Variable-length Argument Lists

The proper declaration for `printf` is

```c
int printf(char *fmt, ...)
```

where the declaration `...` means that the number and types of these arguments
may vary. The declaration `...` can only appear at the end of an argument list.
eg. `minprintf` was declaraed as

```c
void minprintf(char *fmt, ...)
```

The standard header `<stdarg.h>` contains a set of macro definitions that define
how to step through an argument list. The implementation of this header will
vary from machine to machine, but the interface it presents is uniform.

The type `va_list` is used to declare a variable that will refer to each
argument in turn; in `minprintf`, this variable is called `ap`, for argument
pointer. The macro `va_start` initializes `ap` to point to the first unnamed
argument. It must be called once before `ap` is used.

There must be at least one named argument; the final named argument is used by
`va_start` to get started.

Each call of `va_arg` returns one argument and steps `ap` to the next; `va_arg`
uses a type name to determine what type to return and how big a step to take.
Finally, `va_end` does whatever cleanup is necessary. It must be called before
the program returns.

```c
#include <stdarg.h>

/* minprintf: minimal printf with variable argument list */
void minprintf(char *fmt, ...)
{
    va_list ap; /* points to each unnamed arg in turn */
    char *p, *sval;
    int ival;
    double dval;

    va_start(ap, fmt); /* make ap point to 1st unnamed arg */
    for (p = fmt; *p; p++)
    {
        if (*p != '%')
        {
            putchar(*p);
            continue;
        }
        switch (*++p)
        {
        case 'd':
            ival = va_arg(ap, int);
            printf("%d", dval);
            break;
        case 'f':
            dval = va_arg(ap, double);
            printf("%f", dval);
            break;
        case 's':
            for (sval = va_arg(ap, char *); *sval; sval++)
                putchar(*sval);
            break;
        default:
            putchar(*p);
            break;
        }
    }
    va_end(ap); /* clean up when done */
}
```

## 7.4 Formatted Input - Scanf

>>>>> progress
