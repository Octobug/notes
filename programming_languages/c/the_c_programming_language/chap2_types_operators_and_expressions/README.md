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
