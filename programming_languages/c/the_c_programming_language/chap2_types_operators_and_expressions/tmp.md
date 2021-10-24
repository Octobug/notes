# Chapter 2: Types, Operators, and Expressions

## 2.7 Type Conversions

The only automatic conversions are those that convert a "narrower" operand into
a "wider" one without losing information. e.g.

```c
/* atoi: convert s to integer */
int atoi(char s[])
{
    int i, n;

    n = 0;
    for (i = 0; s[i] >= '0' && s[i] <= '9'; ++i)
        n = 10 * n + (s[i] - '0);
    return n;
}
```

The definition of C guarantees that any character in the machine's standard
**printing character** set will never be negative.

If there are no unsigned operands, the following set of rules will suffic:

- If either operand is `long double`, convert the other to `long double`
- Otherwise, if either operand is `double`, convert the other (except `float`)
  to `double`
- Otherwise, if either operand is `float`, convert the other to `float`
- Otherwise, convert `char` and `short` to int
- Then, if either operand is `long`, convert the other to `long`

## 2.8 Increment and Decrement Operators

```c
/* strcat: concatenate t to end of s; s must be big enough */
voif strcat(char s[], char t[])
{
    int i, j;

    i = j = 0;
    while (s[i] != '\0) /* find end of s */
        i++;
    while ((s[i++] = t[j++]) != '\0')   /* copy t */
        ;
}
```

## 2.9 Bitwise Operators

C provides six operators for bit manipulation; these may only be applied to
integral operands, that is, `char`, `short`, `int`, and `long`, whether signed
or unsigned.

- `&`: bitwise AND
- `|`: bitwise inclusive OR
- `^`: bitwise exclusive OR
- `<<`: left shift
- `>>`: right shift
- `~`: one's complement (unary)

e.g.

```c
/* getbits: get n bits from position p */
unfigned getbits(unsigned x, int p, int n)
{
    return (x >> (p + 1 - n)) & ~(~0 << n);
}
```

## 2.10 Assignment Operators and Expressions

Most binary operators have a corresponding assignment operator `op=`, where op
is one of `+ - * / % << >> & ^ |`.

e.g.

```c
/* bitcount: count 1 bits in x */
// declaring the argument x to be unsigned ensures that when it is right-shifted
//  vacated bits will be filled with zeros
int bitcount(unsigned x)
{
    int b;

    for (b = 0; x != 0; x >>= 1)
        if (x & 01)
            b++;
    return b;
}
```

## 2.11 Conditional Expressions

`expr1 ? expr2 : expr3`

if `expr2` and `expr3` are of different types, the type of the result is
determined by the conversion rules. For example, if `f` is a `float` and `n` is
an `int`, then the expression `(n > 0) ? f : n` is of type `float` regardless of
whether `n` is positive.

## 2.12 Precedence and Order of Evaluation

| Operators | Associativity |
| - | - |
| `()` `[]` `->` `.` | -> |
| `!` `~` `++` `--` `+` `-` `*` `&` `(type)` `sizeof` | <- |
| `*` `/` `%` | -> |
| `+` `-` | -> |
| `<<` `>>` | -> |
| `<` `<=` `>` `>=` | -> |
| `==` `!=` | -> |
| `&` | -> |
| `^` | -> |
| `\|` | -> |
| `&&` | -> |
| `\|\|` | -> |
| `?:` | <- |
| `=` `+=` `-=` `/=` `%=` `&=` `^=` `\|=` `<<=` `>>=` | <- |
| `,` | -> |

`a[i] = i++`, this situation is compiler-denpendent.

The moral is that writing code that depends on order of evaluation is a bad
programming practice in any language.
