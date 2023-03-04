# Chapter 7: Input and Output

- [Chapter 7: Input and Output](#chapter-7-input-and-output)
  - [7.1 Standard Input and Output](#71-standard-input-and-output)
  - [7.2 Formatted Output - printf](#72-formatted-output---printf)
  - [7.3 Variable-length Argument Lists](#73-variable-length-argument-lists)
  - [7.4 Formatted Input - Scanf](#74-formatted-input---scanf)
  - [7.5 File Access](#75-file-access)
  - [7.6 Error Handling - Stderr and Exit](#76-error-handling---stderr-and-exit)
  - [7.7 Line Input and Output](#77-line-input-and-output)
  - [7.8 Miscellaneous Functions](#78-miscellaneous-functions)
    - [7.8.1 String Operations](#781-string-operations)
    - [7.8.2 Character Class Testing and Conversion](#782-character-class-testing-and-conversion)
    - [7.8.3 Ungetc](#783-ungetc)
    - [7.8.4 Command Execution](#784-command-execution)
    - [7.8.5 Storage Management](#785-storage-management)
    - [7.8.6 Mathematical Functions](#786-mathematical-functions)
    - [7.8.7 Random Number Generation](#787-random-number-generation)

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

In C, a ***file pointer*** points to a structure that contains information about
the file, such as the location of a buffer, the current character position in
the buffer, whether the file is being read or written, and whether errors or end
of file have occured.

The definitions obtained from `<stdio.h>` include a structure declaration called
`FILE`. The only declaration needed for a file pointer is exemplified by

```c
FILE *fp;
FILE *fopen(char *name, char *mode);
```

This says that `fp` is a pointer to a FILE, and `fopen` returns a pointer to a
`FILE`. `FILE` is a type name, like `int`, not a structure tag; it is defined
with a `typedef`.

The call to `fopen` in a program is

```c
fp = fopen(name, mode);
```

Allowable modes include read(`r`), write(`w`), and append(`a`). Some systems
distinguish between text and binary files; for the latter, a `b` must be
appended to this mode string.

If a file that does not exist is opened for writing or appending, it is created
if possible. If there is any error, `fopen` will return `NULL`.

`getc` returns the next character from a file; it needs the file pointer to tell
it which file: `int getc(FILE *fp)`. `getc` returns the next character from the
stream referred to by `fp`; it returns `EOF` for end of file or error.

`putc` is an output function: `int putc(int c, FILE *fp)`. `putc` writes the
character `c` to the file `fp` and returns the character written, or `EOF` if an
error occurs.

💡 When a C program is started, the operating system environment is responsible
for opening three files and providing pointers for them. These files are **the
standard input**, **the standard output**, and **the standard error**; the
corresponding file pointers are called `stdin`, `stdout`, and `stderr`, and are
declared in `<stdio.h>`.

`getchar` and `putchar` can be defined in terms of `getc`, `putc`, `stdin`, and
`stdout` as follows:

```c
#define getchar()   getc(stdin)
#define putchar(c)  putc((c), stdout)
```

For formatted input or output of files, the functions `fscanf` and `fprintf` may
be used:

```c
int fscanf(FILE *fp, char *format, ...)
int fprintf(FILE *fp, char *format, ...)
```

eg. cat

```c
#include <stdio.h>

/* cat: concatenate files, version 1 */
int main(int argc, char *argv[])
{
    FILE *fp;
    void filecopy(FILE *, FILE *);

    if (argc == 1) /* no args: copy standard input */
    {
        filecopy(stdin, stdout);
    }
    else
    {
        while (--argc > 0)
        {
            if ((fp = fopen(*++argv, "r")) == NULL)
            {
                printf("cat: can't open %s\n", *argv);
                return 1;
            }
            else
            {
                filecopy(fp, stdout);
                fclose(fp);
            }
        }
        return 0;
    }
}

/* filecopy: copy file ifp to file ofp */
void filecopy(FILE *ifp, FILE *ofp)
{
    int c;

    while ((c = getc(ifp)) != EOF)
    {
        putc(c, ofp);
    }
}
```

The file pointers `stdin` and `stdout` are objects of type `FILE *`.

The function `int fclose(FILE *fp)` is the inverse of `fopen`, it breaks the
connection between the file pointer and the external name that was established
by `fopen`, freeing the file pointer for another file.

`fclose` also flushes the buffer in which `putc` is collecting output. `fclose`
is called automatically for each open file when a program terminates normally.

## 7.6 Error Handling - Stderr and Exit

To handle error better, a second ouput stream, called `stderr`, is assigned to a
program in the same way that `stdin` and `stdout` are. Output written on
`stderr` normally appears on the screen even if the standard output is
redirected.

eg. improved cat

```c
#include <stdio.h>

/* cat: concatenate files, version 2 */
int main(int argc, char *argv[])
{
    FILE *fp;
    void filecopy(FILE *, FILE *);
    char *prog = argv[0]; /* program name for errors */

    if (argc == 1) /* no args: copy standard input */
    {
        filecopy(stdin, stdout);
    }
    else
    {
        while (--argc > 0)
        {
            if ((fp = fopen(*++argv, "r")) == NULL)
            {
                fprintf(stderr, "%s: can't open %s\n", prog, *argv);
                exit(1);
            }
            else
            {
                filecopy(fp, stdout);
                fclose(fp);
            }
        }
    }
    if (ferror(stdout))
    {
        fprintf(stderr, "%s: error writing stdout\n", prog);
        exit(2);
    }
    exit(0);
}

/* filecopy: copy file ifp to file ofp */
void filecopy(FILE *ifp, FILE *ofp)
{
    int c;

    while ((c = getc(ifp)) != EOF)
    {
        putc(c, ofp);
    }
}
```

The program uses the standard library function `exit`, which terminates program
execution when it is called. The argument of `exit` is available to whatever
process called this one, so the success or failure of the program can be tested
by another program that uses this one as a sub-process.

Conventionally, a return value of `0` signals that all is well; non-zero values
usually signal abnormal situations. `exit` calls `fclose` for each open output
files, to flush out any buffered output.

💡 Within `main`, `return` *expr* is equivalent to `exit`, `exit` has the
advantage that it can be called from other functions.

The function `int ferror(FILE *fp)` returns non-zero if an error occurred on
the stream `fp`.

The function `int feof(FILE *fp)` is analogous to `ferror`; it returns non-zero
if end of file has occurred on the specified file.

## 7.7 Line Input and Output

The rountine `fgets`is similar to the `getline` function.

```c
char *fgets(char *line, int maxline, FILE *fp)
```

For output, the function `fputs` writes a string to a file:

```c
int fputs(char *line, FILE *fp)
```

The library functions `gets` and `puts` are similar to `fgets` and `fputs`, but
operate on `stdin` and `stdout`.

eg. fgets and fputs

```c
/* fgets: get at most n chars from iop */
char *fgets(char *s, int n, FILE *iop)
{
    register int c;
    register char *cs;

    cs = s;
    while (--n > 0 && (c = getc(iop)) != EOF)
    {
        if ((*cs++ = c) == '\n')
        {
            break;
        }
    }
    *cs = '\0';
    return (c == EOF && cs == s) ? NULL : s;
}

/* fputs: put string s on file iop */
int fputs(char *s, FILE *iop)
{
    int c;

    while (c = *s++)
    {
        putc(c, iop);
    }
    return ferror(iop) ? EOF : 0;
}
```

eg. getline

```c
/* getline: read a line, return length */
int getline(char *line, int max)
{
    if (fgets(line, max, stdin) == NULL)
    {
        return 0;
    }
    else
    {
        return strlen(line);
    }
}
```

## 7.8 Miscellaneous Functions

### 7.8.1 String Operations

`<string.h>`

- `void strcat(char *s, char *t)`: concatenate `t` to end of `s`
- `void strncat(char *s. char *t, int n)`: concatenate `n` characters of `t` to
  end of `s`
- `int strcmp(char *s, char *t)`: return negative, zero, or positive for
  `s < t`, `s == t`, `s > t`
- `int strncmp(char *s, char *t, int n)`: same as `strcmp` but only in first `n`
  characters
- `void strcpy(char *s, char *t)`: copy `t` to `s`
- `void strncpy(char *s, char *t, int n)`: copy at most `n` characters of `t`
  to `s`
- `int strlen(char *s)`: return length of `s`
- `int strchr(char *s, int c)`: return pointer to first `c` in `s`, or `NULL`
  if not present
- `int strrchr(char *s, int c)`: return pointer to last `c` in `s`, or `NULL`
  if not present

### 7.8.2 Character Class Testing and Conversion

`<ctype.h>`

- `int isalpha(int c)`: non-zero if `c` is alphabetic, `0` if not
- `int isupper(int c)`: non-zero if `c` is upper case, `0` if not
- `int islower(int c)`: non-zero if `c` is lower case, `0` if not
- `int isdigit(int c)`: non-zero if `c` is digit, `0` if not
- `int isalnum(int c)`: non-zero if `isalpha(c)` or `isdigit(c)`, `0` if not
- `int isspace(int c)`: non-zero if `c` is blank, tab, newline, return,
  formfeed, vertical tab
- `char toupper(int c)`: return `c` converted to upper case
- `char tolower(int c)`: return `c` converted to lower case

### 7.8.3 Ungetc

`<stdio.h>`

`int ungetc(int c, FILE *fp)`: a rather restricted version of `ungetch`.
It pushes the character `c` back onto file `fp`, and returns either `c`, or
`EOF` for an error.

💡 `ungetc` may be used with any of the input functions like `scanf`, `getc`,
or `getchar`.

### 7.8.4 Command Execution

`system(char *s)` executes the command contained in the character string `s`,
then resumes execution of the current program.

### 7.8.5 Storage Management

`malloc` and `calloc` obtain blocks of memory dynamically.

`void *malloc(size_t n)` returns a pointer to `n` bytes of uninitialized
storage, or `NULL` if the request cannot be satisfied.

`void *calloc(size_t n, size_t size)` returns a pointer to enough free space for
an array of `n` objects of the specified size, or `NULL` if the request cannot
be satisfied. The storage is initialized to zero.

The pointer returned by `malloc` or `callod` has the proper alignment for the
object in question, but it must be cast into the appropriate type, as in

```c
int *ip;
ip = (int *) calloc(n, sizeof(int));
```

`free(p)` frees the space pointed to by `p`, where `p` was originally obtained
by a call to `malloc` or `calloc`.

⚠️ It is a ghastly error to free something not obtained by calling `malloc` or
`calloc`. It is also an error to use something after it has been freed.

A typical but incorrect piece of code is this loop that frees items from a list:

```c
// WRONG
for (p = head; p != NULL; p = p -> next)
{
    free(p);
}
```

The right way is to save whatever is needed before freeing:

```c
for (p = head; p != NULL; p = q)
{
    q = p -> next;
    free(p);
}
```

### 7.8.6 Mathematical Functions

`<math.h>`

- `double sin(double x)`: sine of `x`, `x` in radians
- `double cos(double x)`: cosine of `x`, `x` in radians
- `double atan2(double y, double x)`: arctangent of `y/x`, in radians
- `double exp(double x)`: exponetial function `e^x`
- `double log(double x)`: natural (base `e`) logarithm of `x` (x > 0)
- `double log10(double x)`: common (base `10`) logarithm of `x` (x > 0)
- `double pow(double x, double y)`: `x^y`
- `double sqrt(double x)`: square root of `x` (x > 0)
- `double fabs(double x)`: absolute value of `x`

### 7.8.7 Random Number Generation

`rand` computes a sequence of pseudo-random integers in the range zero to
`RAND_MAX`, which is defined in `<stdlib.h>`. One way to produce random
floating-point numbers greater than or equal to zero but less than one is

```c
#define frand() ((double) rand() / (RAND_MAX + 1.0))
```

`srand(unsigned)` sets the seed for `rand`.
