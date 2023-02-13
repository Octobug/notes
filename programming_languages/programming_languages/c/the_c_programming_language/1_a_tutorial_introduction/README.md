# Chapter 1: A Tutorial Introduction

- [Chapter 1: A Tutorial Introduction](#chapter-1-a-tutorial-introduction)
  - [1.1 Getting Started](#11-getting-started)
    - [main() function](#main-function)
    - [Library](#library)
    - [character string (or string constant)](#character-string-or-string-constant)
  - [1.2 Variables and Arithmetic Expressions](#12-variables-and-arithmetic-expressions)
    - [Basic data types](#basic-data-types)
    - [Arithmetic](#arithmetic)
    - [`printf` args format](#printf-args-format)
  - [1.3 The For Statement](#13-the-for-statement)
  - [1.4 Symbolic Constants](#14-symbolic-constants)
  - [1.5 Character Input and Output](#15-character-input-and-output)
    - [1.5.1 File Copying](#151-file-copying)
    - [1.5.2 Character Counting](#152-character-counting)
      - [`while` and `for`](#while-and-for)
    - [1.5.3 Line Counting](#153-line-counting)
      - [character constant](#character-constant)
    - [1.5.4 Word Counting](#154-word-counting)
  - [1.6 Arrays](#16-arrays)
  - [1.7 Functions](#17-functions)
    - [Function Prototype](#function-prototype)
  - [1.8 Arguments -- Call by Value](#18-arguments----call-by-value)
  - [1.9 Character Arrays](#19-character-arrays)
    - [`\0`](#0)
  - [1.10 External Variables and Scope](#110-external-variables-and-scope)

## 1.1 Getting Started

```c
#include <stdio.h>              // include information about standard library

int main()                      // define a function called main that received
                                // no argument values
{                               // statements of main are enclosed in braces
    printf("Hello, world\n");   // main calls library function printf to print
                                // this sequence of characters
                                // \n represents the newline character
    return 0;               
}
```

### main() function

Every C program begins executing at the beginning of main. This means that
every program must have a main somewhere.

### Library

`#include <stdio.h>` tells the compiler to include information about the
standard input/output library.

### character string (or string constant)

is a sequence of characters in double quotes.

## 1.2 Variables and Arithmetic Expressions

### Basic data types

- `char`: character
- `int`: integer
- `short`: short interger
- `long`: long integer
- `float`: single-precision floating point
- `double`: double-precision floating point

The sizes of these objects are also machine-dependent. There are also types
of these basic types:

- arrays
- structures
- unions

And *pointers* to them, and *functions* that returns them.

### Arithmetic

In C, integer division *truncates*: any fractional part is discarded.

### `printf` args format

- %d: print as decimal integer
- %ld: print as decimal long interger
- %6d: print as decimal integer, at least 6 characters wide
- %f: print as floating(single or double) point
- %6f: print as floating point, at least 6 characters wide
- %.2f: print as floating point, 2 characters after decimal point
- %6.2f: print as floating point, at least 6 wide and 2 after decimal point
- %o: print as octal integer
- %x: print as hexadecimal integer
- %c: print as character
- %s: print as character string
- %%: print as % itself

## 1.3 The For Statement

## 1.4 Symbolic Constants

Magic number: constant numbers written in codes.

A `define` for them is a good practice.

```c
#define name    replacement_text // no semicolon here
```

Symbolic constant names are conventionally written in upper case so they can be
readily distinguished from lower case variable names.

## 1.5 Character Input and Output

Text input or output, regardless of where it originates or where it goes to,
is dealt with as **streams** of characters.

The standard library provides several functions for reading or writing one
character at a time, of which `getchar` and `putchar` are the simplest. Each
time it is called, `getchar` reads the *next input character* from a text stream
and returns that as its value.

The variable c contains the next character of input.

```c
c = getchar()
```

The function `putchar` prints a character each time it is called.

```c
putchar(c)
```

### 1.5.1 File Copying

`EOF`: the end-of-file indicator, it is an integer defined in `<stdio.h>`, the
specific numeric value doesn't matter as long as it is not the same as any char
value. `Ctrl + D` in macOS.

In C, any assignment, such as `c = getchar()`, is an expression and has a value
which is the value of the left hand side after the assignment.

### 1.5.2 Character Counting

`;`: a `null` statement

#### `while` and `for`

They test at the top of the loop, before proceeding with the body.

### 1.5.3 Line Counting

#### character constant

A character written between single quotes represents an integer value equal to
the numerical value of the character in the machine's character set.

### 1.5.4 Word Counting

`nl = nw = nc = 0;` sets all three variables to `0`. It is equivalent to
`nl = (nw = (nc = 0));`

## 1.6 Arrays

## 1.7 Functions

### Function Prototype

`int power(int m, int n);`

Parameter names of function prototype is optional. `int power(int, int);` is OK.

C version before ANSI C, would write the `power` function like this:

```c
/* power: raise base to n-th power; n >= 0 */
/*          (old-style version) */
power(base, n)
int base, n;
{
    // the body of the function is the same as ANSI C
}
```

And the declaration of `power` would have looked like this: `int power();`.

## 1.8 Arguments -- Call by Value

In C, all function arguments are passed **by value**. This means that the called
function is given the values of its arguments in temporary variables rather than
the originals.

The called function cannot directly alter a variable in the calling function; it
can only alter its private, temporary copy.

When the name of an array is used as an argument, the value passed to the
function is the location or address of the beginning of the array -- there is no
copying of array elements. By subscripting this value, the function can access
and alter any element of the array.

## 1.9 Character Arrays

### `\0`

The `null` character, whose value is `0`, is used to mark the end of a string
of characters.

The `%s` format specification in `printf` expects the corresponding argument to
be a string represented in this form.

## 1.10 External Variables and Scope

An external variable must be *defined* outside of any function. It must also be
*declared* in each function that wants to access it. This states the type of the
variable.

The declaration may be an explicit `extern` statement or may be implicit from
context.

In certain circumstances, the `extern` declaration can be omitted. If the
definition of an external variable occurs in the source file before its use in a
particular function, then there is no need for an `extern` declaration in the
function.

Common practice is to place definitions of all external variables at the
beginning of the source file, and then omit all `extern` declarations.

If the program is in several source files, and a variable is defined in `file1`
and used in `file2` and `file3`, then `extern` declarations are needed in
`file2` and `file3` to connect the occurrences of the variable.

The usual practice is to collect `extern` declarations of variables and
functions in a seperate file, historically called a `header`, that is included
by `#include` at the front of each source file. The suffix `.h` is conventional
for header names.

- `definition`: refers to the place where variable is created or assigned
  storage
- `declaration`: refers to the places where the nature of the variable is stated
  but no storage is allocated
