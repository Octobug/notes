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

## 5.7 Multi-dimenstional Arrays
