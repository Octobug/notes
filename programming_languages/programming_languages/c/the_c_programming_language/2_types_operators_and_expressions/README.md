# Chapter 2: Types, Operators, and Expressions

## 2.1 Variable Names

- **Do not** begin variable names with underscore, since library routines often
  use such names.
- lower case for variable names
- ALL UPPER CASE for symbolic constants

## 2.2 Data Types and Sizes

Basic data types:

- char: a single byte, capable of holding one character in the local character
  set.
- int: an integer, typically reflecting the natural size of integers on the host
  machine.
- float: single-precision floating point.
- double: double-precision floating point.

And there are a number of qualifiers that can be applied to these basic types,
such as: `short int sh;`, `long int counter`. `int` can be omitted in such
declarations.

`int` will normally be the natural size for a particular machine. `short` is
often 16 bits, `long` 32 bits, and `int` either 16 or 32 bits.

The standard restriction: `shorts` and `ints` are at least 16 bits, `longs` are
at least 32 bits, and `short` is no longer than `int`, `int` is no longer than
`long`.

The qualifier `signed` or `unsigned` may be applied to `char` or any `integer`.
Whether plain `chars` are signed or unsigned is machine-dependent, but printable
characters are always positive.

The standard headers `<limits.h>` and `<float.h>` contain symbolic constants
for all of these sizes.

## 2.3 Constants

### long

A long constant is written with a terminal `l` or `L`, as in `123456789L`; an
integer too big to fit into an `int` will also be taken as a `long`.

### unsigned

Unsigned constants are written with a terminal `u` or `U`, and the suffix `ul`
or `UL` indicates `unsigned long`.

### float and double

Floating-point constants contain a decimal point or an exponent (1e-2) or both;
their type is double, unless suffixed. The suffixes `f` or `F` indicate a
`float` constant; `l` or `L` indicate a long double.

### decimal, octal and hex

A leading `0` on an integer constant means octal; a leading `0x` or `0X` means
hexadecimal. `31` can be written as `037` in octal and `0x1f` or `0X1f` in hex.

### character

A `character constant` is an integer, written as one character within single
quotes, such as `'x'`. An arbitrary byte-sized bit pattern can be specified by
`\ooo` where `ooo` is one to three octal digits (0...7) or by `\xhh`, where `hh`
is one or more hexadecimal digits (0...9, a...f, A...F). We might write

```c
#define VTAB '\013' /* ASCII vertical tab */
#define BELL '\007' /* ASCII bell character */
```

or, in hexadecimal,

```c
#define VTAB '\xb' /* ASCII vertical tab */
#define BELL '\xb' /* ASCII bell character */
```

`\0` is often written instead of 0 to emphasize the character nature of some
expression, but the numeric value is just 0.

### constant expression

A `constant expression` is an expression that involves only constants. Such
expressions may be evaluated during compilation rather than run-time.

### string

A `string constant`, or `string literal`, is a sequence of zero or more
characters surrounded by double quotes. String constants can be concatenated
at compile time: `"hello," " world"` is equivalent to `"hello, world"`.
A string constant is an array of characters. It has a null character `\0` at the
end, so the physical storage required is one more than the number of characters
written between the quotes.

A function returning length of a given string could be implemented like this:

```c
/* strlen: return length of s */
int strlen(char s[])
{
  int i;

  i = 0;
  while (s[i] != '\0')
    ++i;
  return i;
}
```

- `'x'`: is essentially an integer
- `"x"`: is an array of characters, ['x', '\0']

### enumeration

An enumeration is a list of constant integer values, as in

```c
enum boolean { NO, YES };
```

Enumerations provide a convenient way to associate constant values with names,
an alternative to `#define` with the advantage that the values can be generated
for you. Enumeration variables offer the chance of checking and so are often
better than `#define`.

## 2.4 Declarations

A declaration specifies a type, and contains a list of one or more variables of
that types.

## 2.5 Arithmetic Operators

The direction of truncation for `/` and the sign of the result for `%` are
machine-dependent for negative operands, as is the action taken on overflow or
onderflow.

`unary operator`: 一元操作符

## 2.6 Relational and Logical Operators

e.g. Here is a loop from the input function `getline`:

```c
for (i = 0; i < lim - 1 && (c=getchar()) != '\n' && c != EOF; ++i)
    s[i] = c;
```

The unary negation operator `!` converts a non-zero operand in to `0`, and a
zero operand into `1`. A commone use of `!` is in constructions like
`if (!valid)` rather than `if (valid === 0)`.

## 2.7 Type Conversions

The only automatic conversions are those that convert a "narrower" operand into
a "wider" one without losing information.

Expression that might lose information, like assigning a longer integer type to
a shorter, or a floating-point type to an integer, may draw a warning, but they
not illegal.

e.g.

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
