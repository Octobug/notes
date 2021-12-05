# Chapter 4: Functions and Program Structure

## 4.1 Basics of Functions

A minimal function is `dummy() {}`, which does nothing and returns nothing. It
is useful as a place holder during program development. If the return type is
omitted, `int` is assumed.

### The `return` statement

`return expression;`

The `expression` will be converted to the return type of the function if
neccessary.

*In any case, if a function fails to return a value, its "value" is certain to
be garbage.*

## 4.2 Functions Returning Non-integers

```c
sum += atof(line);
```

If a name that has not been previously declared occurs in an expression and is
followed by a left parenthesis, it is declared by context to be a function name,
the function is assumed to return an `int` and nothing is assumed about its
arguments.

If a function declaration does not include arguments, as in `double atof();`,
that too is taken to mean that nothing is to be assumed about the arguments of
`atof;` all parameter checking is turned off. This special meaning of the empty
argument list is intended to permit older C programs to compile with new
compilers. But it's a **bad idea** to use it with new programs. If the function
takes arguments, declare them; if it takes no arguments, use `void`.

`atoi` could be written based on `atof`:

```c
// atoi: convert string s to integer using atof
int atoi(char s[])
{
    double atof(char s[]);

    return (int) atof(s);
}
```

## 4.3 External Variables

External variables are defined outside of any function. Functions themselves are
always external, C does not allow functions to be defined inside other
functions.

External variables and functions have the property that all references to them
by the same name, even from functions compiled separately, are references to the
same thing. The standard calls this property `external linkage`.

If a large number of variables must be shared among functions, external
variables are more convient and efficient then long argument lists.

- Infix expression: `(1 - 2) * (4 + 5)`
- Polish notation: `1 2 - 4 5 + *`

The standard library includes a function `ungetc` that provides one character of
pushback.

## 4.4 Scope Rules

The scope of an external variable or a function lasts from the point at which it
is declared to the end of the file being compiled.

If an external variable is to be referred to before it is defined, or if it is
defined in a different source file from the one where it is being used, then an
`extern` declaration is mandatory.

### Declaration

A declaration announces the properties of a variable (primarily its type).

Below declares for the rest of the source file that `sp` is an `int` and that
`val` is a `double` array (whose size is determined elsewhere), but they do not
create the variables or reserve storage for them.

```c
extern int sp;
extern double val[];
```

### Definition

A definition also causes storage to be set aside.

Initialization of an external variable goes only with the definition.

Below defines the external variables `sp` and `val`, causes storage to be set
aside, and also serves as the declaration for the rest of that source file.

```c
int sp;
double val[MAXVAL];
```

## 4.5 Header Files

Each file have access only to the information it needs for its job.

vs.

It is harder to maintain more header files.

It is probably best to have one header file that contains everything that is to
be shared between any two parts of the program.

## 4.6 Static Variables

The `static` declaration, applied to an external variable or function, limits
the scope of that object to the rest of the source file being compiled.

It provides a way to hide names which must be shared among functions but hidden
from other source files of the same program.

The `static` declaration can also be applied to internal variables. They remain
in existence rather than coming and going each time the function is activated.

## 4.7 Register Variables

A `register` declaration advices the compiler that the variable in question will
be heavily used. The idea is that `register` variables are to be placed in
machine registers, which may result in smaller and faster programs. But
compilers are free to ignore the advice.

```c
register int x;
register char c;
```

It can only be applied to automatic variables and to the formal parameters of a
function, That is it cannot be applied to external variables.

```c
f(register unsigned m, register long n)
{
    register int i;
    ...
}
```

## 4.8 Block Structure

An automatic variable declared and initialized in a block is initialized each
time the block is entered. A `static` variable is initialized only the first
time the block is entered.

## 4.9 Initialization

In the absence of explict initialization, `external` and `static` variables are
guaranteed to be initialized to zero; `automatic` and `register` variables have
undefined initial value.

For external and static variables, the initializer must be a constant
expression; the initialization is done once, conceptually before the program
begins execution.

### Array

```c
int days[20] = { 1, 2, 3, 4 };
```

The missing elements within the specified length will be zero for external,
static and automatic variables. Excessing initializers will cause error.

A constant string is allowed to initialize a character array.

```c
char pattern[] = "ould";
```

## 4.10 Recursion

## 4.11 The C Preprocessor

### 4.11.1 File Inclusion

`#include "filename"` or `#include <filename>`

If the `filename` is quoted, searching for the file typically begins where the
source program was found. The searching for `<filename>` has a lower priority.

`#include` is the preferred way to tie the declarations together for a large
program.

Naturally, when an included file is changed, all files that depend on it must be
recompiled.

### 4.11.2 Macro Substitution

`#define name replacement text`

A long definition of replacement text mey be continued onto serveral lines by
placing a `\` at the end of each line to be continued.

The scope of a name defined is from its point of definition to the end of the
source file being compiled.

Substitutions are made only for tokens, and do not take palce within quoted
strings.

```c
// infinite loop
#define forever for (;;)
```

#### Macros with arguments

```c
#define max(A, B) ((A) > (B) ? (A) : (B))
```

#### Pitfalls

```c
max(i++, j++)
```

will be replaced by

```c
((i++) > (j++) > (i++) : (j++))
```

which is not actually we want.

Names may be undefined with `#undef`.

Formal parameters are not replaced within quoted strings. If a parameter name is
preceded by a `#` in the replacement text, the combination will be expanded into
a quoted string with the parameter replaced by the actual argument.

```c
#define dprint(expr) printf(#expr " = %g\n", expr)

// if invoked as
dprint(x/y);

// will be expanded into
printf("x/y" " = %g\n", x/y);

// and then will be concatenated to
printf("x/y = %g\n", x/y);
```

The `##` provides a way to concatenate actual arguments during macro expansion.
Surrounding white space will be removed.

```c
#define paste(front, back) front ## back

paste(name, 1);
// will be expanded into
name1
```

### 4.11.3 Conditional Inclusion

`#if` evaluates a constant integer expression.

e.g. To make sure that the contents of a file `hdr.h` are included only once:

```c
#if !defined(HDR)
#define HDR

// contents of hdr.h go here

#endif
```

is same as

```c
#ifndef HDR
#define HDR

// contents of hdr.h go here

#endif
```

```c
// tests the name SYSTEM to decide which version of a header to include
#if SYSTEM == SYSV
    #define HDR "sysv.h"
#elif SYSTEM == BSD
    #define HDR "bsd.h"
#elif SYSTEM == MSDOS
    #define HDR "msdos.h"
#else
    #define HDR "default.h"
#endif
#include HDR
```

`#ifdef` and `#ifndef` lines are specialized forms that test whether a name is
defined.
