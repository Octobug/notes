# Chapter 5: Pointers and Arrays

## 5.1 Pointers and Addresses

A pointer is a group of cells (often two or four) that can hold an address.

The unary operator `&` gitves the address of an object, so the statement
`p = &c;` assigns the address of c to the variable p.

The unary operator `*` is the *indirection* or *dereferencing* operator.

```c
int x = 1, y = 2, z[10];
int *ip;

// ip points to x
ip = &x;
// y = x = 1
y = *ip;
// x = 0
*ip = 0;
// ip points to z[0]
ip = &z[0];
```

A "pointer to void" is used to hold any type of pointer but cannot be
dereferenced itself.

## 5.2 Pointers and Function Arguments

Since C passes arguments to functions by value, there is no direct way for the
called function to alter a variable in the calling function.

```c
void swap(int *px, int *py)
{
    int temp;

    temp = *px;
    *px = *py;
    *py = temp;
}

swap(&a, &b);
```

## 5.3 Pointers and Arrays

Any operations that can be achieved by array subscripting can also be done with
pointers.

If `pa` points to a particular element of an array, then by definition `pa + 1`
points to the next element, Regardless of the type or size of the elements.

The meaning of "adding 1 to a pointer", and by extension, all pointer
arithmetic, is that `pa + 1` points to the next object, and `pa + i` points to
the `i-th` object beyond `pa`.

Since the name of an array is a synonym for the location of the initial element,
the assignment `pa = &a[0]` can also be written as `pa = a`. And a reference to
`a[i]` can also be written as `*(a+i)`. In evaluating `a[i]`, C converts it to
`*(a+i)` immediately.

There is one difference between an array name and a pointer. A pointer is a
variable, so `pa = a` and `pa++` are legal. But an array name is not a variable,
constructions like `a = pa` and `a++` are illegal.

```c
// strlen: return length of string s
int strlen(char *s)
{
    int n;

    for (n = 0; *s != '\0'; s++)
        n++;
    return n;
}
```

Formal parameters in a function definition, `char s[]` and `char *s` are
equivalent. The latter is preferred because it says more explicitly that the
parameter is a pointer.

## 5.4 Address Arithmetic

C guarantees that zero is never a valid address for data. Zero is the sole
exception of interchange between pointers and integers. The symbolic constant
`NULL`(defined in <stdio.h>) is often used in place of zero, as a mnemonic to
indicate more clearly that this is a special value for a pointer.

The construction `p + n` means the address of the n-th object beyond the one p
currently points to, regardless of the kind of object `p` points to; `n` is
scaled according to the size of the objects `p` points to, which is determined
by the declaration of `p`. If an `int` is four bytes, then the `int` will be
scaled by four.

```c
// strlen: return length of string s
int strlen(char *s)
{
    char *p = s;

    while (*p != '\0)
    {
        p++;
    }
    return p - s;
}
```

`size_t` is the unsigned integer type returned by the `sizeof` operator.

To add, multiply, divide, shift or mask pointers are illegal, or to add `float`
or `double` to them.

## 5.5 Character Pointers and Functions

`string.h`

C does not provide any operators for processing an entire string of characters
as a unit.

```c
// an array
char amessage[] = "how is the time";
// a pointer
char *pmessage = "how is the time";
```

### strcpy: copy t to s

```c
// array subscript version
void strcpy(char *s, char *t)
{
    int i;

    i = 0;
    while ((s[i] = t[i]) != '\0)
        i++;
}

// pointer version 1
void strcpy(char *s, char *t)
{
    while ((*s = *t) != '\0)
    {
        s++;
        t++;
    }
}

// pointer version 2
void strcpy(char *s, char *t)
{
    while ((*s++ = *t++) != '\0)
        ;
}

// pointer version 3, a little bit cryptic
void strcpy(char *s, char *t)
{
    while (*s++ = *t++)
        ;
}
```

### strcmp: return <0 if s < t, 0 if s == t, >0 if s > t

```c
// array version
int strcmp(char *s, char *t)
{
    int i;

    for (i = 0; s[i] == t[i]; i++)
    {
        if (s[i] == '\0')
        {
            return 0;
        }
    }
    return s[i] - t[i];
}

// pointer version
int strcmp(char *s, char *t)
{
    for (; *s == *t; s++, t++)
    {
        if (*s == '\0')
        {
            return 0;
        }
    }
    return *s - *t;
}
```

## 5.6 Pointer Arrays; Pointers to Pointers

`int readlines(char *lineptr[], int maxlines);`

## 5.7 Multi-dimensional Arrays

```c
static char daytab[2][13] = {
    {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
    {0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31}
};

// day_of_year: set day of year from month & day
int day_of_year(int year, int month, int day)
{
    int i, leap;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    for (i = 1; i < month; i++>)
    {
        day += daytab[leap][i];
    }
    return day;
}

// month_day: set month, day from day of year
void month_day(int year, int yearday, int *pmonth, int *pday)
{
    int i, leap;

    leap = year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    for (i = 1; yearday > daytab[leap][i]; i++)
    {
        yearday -= daytab[leap][i];
    }
    *pmonth = i;
    *pday = yearday;
}
```

If a two-dimensional array is to be passed to a function, the parameter
declaration in the function must include the number of columns; the number of
rows is irrelevant.

e.g.

`f(int daytab[2][13]) {...}` or `f(int daytab[][13]) {...}s` or

`f(int (*daytab)[13]) {...}`: The parenthese is necessary since brackets [] have
higher precedence than *. Without parentheses, the declaration
`int *daytab[13]` is an array of 13 pointers to integers. Same as the above,
`char *lineptr[]` is an array of pointers to chars.

## 5.8 Initialization of Pointer Arrays

```c
// month_name: return name of n-th month
char *month_name(int n)
{
    static char *name[] = {
        "Illegal month",
        "January", "February", "March",
        "April", "May", "June",
        "July", "August", "September",
        "October", "November", "December"
    };

    return (n < 1 || n > 12) ? name[0] : name[n];
}
```

## 5.9 Pointers vs. Multi-dimensional Arrays

```c
// a is a two-dimensional array: 10 * 20 int-sized locations have been set aside
int a[10][20];
// an array of 10 int pointers, was not initialized
int *b[10];
```

a[3][4] and b[3][4] are both syntactically legal references to a single int.
If each element of b points to a 20-element array, then there will be 200 ints
set aside, plus ten cells for the pointers.

Rows of the pointers array may be of different lengths. While rows of 2d arrays
must be of a same length.

## 5.10 Command-line Arguments

When `main` is called, it is called with two arguments. The first (`argc`, for
argument count) is the number of command-line arguments; the second (`argv`, for
argument vector) is a pointer to an array of character strings that contain the
arguments.

By convention, `argv[0]` is the name by which the program was invoked, so `argc`
is at least 1. The standard requires that argv[argc] be a null pointer.

## 5.11 Pointers to Functions

In C, a function itself is not a variable, but it is possible to define pointers
to functions, which can be assignedm placed in arrays, passed to functions,
returned by functions.

Functions to be passed to other functions need not to use the `&` operator.

The generic pointer type `void *` is used for the pointer arguments. Any pointer
can be cast to `void *` and back again without loss of information.

e.g.

```c
void qsort(void *v[], int left, int right,
           int (*comp)(void *, void *));
```

The fourth parameter of `qsort` is `int (*comp)(void *, void *)`, which says
that `comp` is a pointer to a function that has two `void *` arguments and
returns an int.

The use of `comp` in the line `if ((*comp)(v[i], v[left]) < 0)` is consistent
with the declaration: `comp` is a pointer to a function, `*comp` is the
function, and `(*comp)(v[i], v[left])` is the call to it.

The parentheses are needed so the components are correctly associated; without
them, `int *comp(void *, void *)` says that `comp` is a function returning a
pointer to an int, which is very different.

## 5.12 Complicated Declarations
