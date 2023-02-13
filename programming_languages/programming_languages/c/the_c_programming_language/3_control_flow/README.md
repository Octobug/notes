# Chapter 3: Control Flow

## 3.1 Statements and Blocks

In C, the semicolon is a statement terminator, rather than a seperator as it is
in languages like Pascal.

## 3.2 If-Else

## 3.3 Else-If

e.g.

```c
/* binserach: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, in v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else    /* found match */
            return mid;
    }
    return -1;  /* no match */
}
```

## 3.4 Switch

`cases` serve just as **lables**, so execution falls through to the next case.

```c
switch (expression) {
    case const-expr: statements
    case const-expr: statements
    default: statements
}

## 3.5 Loops -- While and For

The for statement

```c
for (expr1; expr2; expr3)
    statement
```

is equivalent to

```c
expr1;
while (expr2)
{
    statement
    expr3;
}
```

The three components of a `for` loop are expressions. Any of them can be
omitted, although the semicolons must remain.

The standard library provides a more elaborate function `strtol` for conversion
of strings to long integers.

### Shell Sort

In early stages, far-apart elements are compared, rather than adjacent ones as
in simpler interchange sorts. This tends to eliminate large amounts of disorder
quickly, so later stages have less work to do.

### The comma operator

Most often finds use in the `for` statement. A pair of expressions separated by
a comma is evaluated left to right, and the type and value of the result are the
type and value of the right operand.

The commas that separate function arguments, variables in declarations, etc.,
are **not** comma operators.

```c
for (i = 0, j = strlen(s) - 1; i < j; i++, j--)
    c = s[i], s[i] = s[j], s[j] = c;
```

## 3.6 Loops -- Do-while

## 3.7 Break and Continue

## 3.8 Goto and Labels

```c
for (...)
    for (...)
    {
        if (disaster)
            goto error;
    }

error:
    // clean up the mess
```

`label` can be attached to any statement in the same function as the `goto`. The
scope of a label is the entire function.
