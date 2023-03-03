# Chapter 7: Input and Output

- [Chapter 7: Input and Output](#chapter-7-input-and-output)
  - [7.1 Standard Input and Output](#71-standard-input-and-output)
  - [7.2 Formatted Output - printf](#72-formatted-output---printf)
  - [7.3 Variable-length Argument Lists](#73-variable-length-argument-lists)
  - [7.4 Formatted Input - Scanf](#74-formatted-input---scanf)
  - [7.5 File Access](#75-file-access)

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

`scanf` reads characters from the standard input, interprets them according to
the specification in `format`, and stores the results through the remaining
arguments, **each of which must be a pointer**, indicate where the corresponding
converted input should be stored.

There is also a function `sscanf` that reads from a string instead of the
standard input:

```c
int sscanf(char *string, char *format, arg1, arg2, ...)
```

The format string may contain:

- Blanks or tabs.
- Ordinary characters (not `%`).
- Conversion specifications
  - `%`
  - `*`, optional
  - `h`, `l` or `L`, optional
- A conversion specification directs the conversion of the next input field.
  An input field is defined as a string of non-white space characters; it
  extends either to the next white space character or until the field width,
  is specified, is exhausted.
  This implies that `scanf` will read across boundaries to find its input, since
  newliens are white space.
- Input Data; Argument type:
  - `d`: decimal interger; `int *`
  - `i`: integer; `int *`
  - `o`: octal integer; `int *`
  - `u`: unsigned decimal integer; `unsigned in *`
  - `x`: hexadecimal integer; `int *`
  - `c`: characters; `char *`, use `%1s` to read the next non-white space char
  - `s`: character string; `char *`
  - `e`, `f`, `g`: floating-point number with optional sign, optional decimal
    point and optional exponent; `float *`
  - `%`: literal %
  - The conversion characters `d`, `i`, `o`, `u`, and `x` may be preceded by `h`
    to indicate that a pointer to `short` rather than `int` appears in the
    argument in the argument list, or by `l` to indicate that a pointer to
    `long` appears in the argument list.

eg. a calculator:

```c
#include <stdio.h>

int main() /* rudimentary calculator */
{
    double sum, v;

    sum = 0;
    while (scanf("%lf", &v) == 1)
    {
        printf("\t%.2f\n", sum += v);
    }
    return 0;
}
```

Input lines and their `scanf` statement:

```c
// 25 Dec 1988
int day, year;
char monthname[20];
scanf("%d %s %d", &day, monthname, &year);

// mm/dd/yy
int day, month, year;
scanf("%d/%d/%d", &month, &day, &year);
```

To read input whose format is not fixed, it is often best to read a line at a
time, then pick it apart with `scanf`.

eg. read lines that might contain a date in multiple forms:

```c
while (getline(line, sizeof(line)) > 0) {
  if (sscanf(line, "%d %s %d", &day, monthname, &year) == 3)) {
    printf("valid: %s\n", line); /* 25 Dec 1988 form */
  } else if (sscanf(line, "%d/%d/%d", &month, & day, &year) == 3) {
    printf("valid: &s\n", line); /* mm/dd/yy form */
  } else {
    printf("invalid: %s\n", line); /* invalid form */
  }
}
```

⚠️ Calls to `scanf` can be mixed with calls to other input functions. The next
call to any input function will begin by reading the first character not read by
`scanf`.

## 7.5 File Access

>>>>> progress
