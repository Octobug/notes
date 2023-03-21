# Appendix A - Reference Manual

- [Appendix A - Reference Manual](#appendix-a---reference-manual)
  - [A.1 Introduction](#a1-introduction)
  - [A.2 Lexical Conventions](#a2-lexical-conventions)
    - [A.2.1 Tokens](#a21-tokens)
    - [A.2.2 Comments](#a22-comments)
    - [A.2.3 Identifiers](#a23-identifiers)
    - [A.2.4 Keywords](#a24-keywords)
    - [A.2.5 Constants](#a25-constants)
      - [A.2.5.1 Integer constants](#a251-integer-constants)
      - [A.2.5.2 Charater Constants](#a252-charater-constants)
      - [A.2.5.3 Floating Constants](#a253-floating-constants)
      - [A.2.5.4 Enumeration Constants](#a254-enumeration-constants)
    - [A.2.6 String Literals](#a26-string-literals)
  - [A.3 Syntax Notation](#a3-syntax-notation)
  - [A.4 Meaning of Identifiers](#a4-meaning-of-identifiers)
    - [A.4.1 Storage Class](#a41-storage-class)
    - [A.4.2 Basic Types](#a42-basic-types)
    - [A.4.3 Derived Types](#a43-derived-types)
    - [A.4.4 Type Qualifiers](#a44-type-qualifiers)
  - [A.5 Objects and Lvalues](#a5-objects-and-lvalues)
  - [A.6 Conversions](#a6-conversions)
    - [A.6.1 Integral Promotion](#a61-integral-promotion)
    - [A.6.2 Integral Conversions](#a62-integral-conversions)
    - [A.6.3 Integer and Floating](#a63-integer-and-floating)
    - [A.6.4 Floating Types](#a64-floating-types)
    - [A.6.5 Arithmetic Conversions](#a65-arithmetic-conversions)
    - [A.6.6 Pointers and Integers](#a66-pointers-and-integers)
    - [A.6.7 Void](#a67-void)
    - [A.6.8 Pointers to Void](#a68-pointers-to-void)
  - [A.7 Expressions](#a7-expressions)
    - [A.7.1 Pointer Conversion](#a71-pointer-conversion)
    - [A.7.17 Assignment Expressions](#a717-assignment-expressions)
  - [A.8 Declarations](#a8-declarations)
    - [A.8.2 Type Specifiers](#a82-type-specifiers)

## A.1 Introduction

This manual is an interpretation of the proposed standard, not the standard
itself.

## A.2 Lexical Conventions

A program is translated in several phases. The first phases do low-level
lexical transformations, carry out directives introduced by the lines beginning
with the `#` character, and perform macro definition and expansion. When the
preprocessing is complete, the program has been reduced to a sequence of tokens.

### A.2.1 Tokens

There are six classes of tokens:

- identifiers
- keywords
- constants
- string literals
- operators
- other separators

### A.2.2 Comments

### A.2.3 Identifiers

An identifiers is a sequence of letters (including `_`) and digits.

### A.2.4 Keywords

(`asm`) `auto`,
`break`,
`case`, `char`, `const`, `continue`,
`default`, `do`, `double`,
`else`, `enum`, `extern`
`float`, `for`, (`fortran`),
`goto`,
`if`, `int`,
`long`,
`register`, `return`,
`short`, `signed`, `sizeof`, `static`, `struct`, `switch`,
`typedef`,
`union`, `unsigned`,
`void`, `volatile`
`while`

### A.2.5 Constants

There are several kinds of constants:

- integer-constant
- character-constant
- floating-constant
- enumeration-constant

#### A.2.5.1 Integer constants

prefix

- octal: `0`
- decimal
- hexadecimal: `0x` or `0X`

suffix

- unsigned: `u` or `U`
- long: `l` or `L`
- unsigned + long: `UL`, `ul`, ...

#### A.2.5.2 Charater Constants

A character constant is a sequence of one or more characters enclosed in single
quotes as in `'x'`. The value of a multi-character constant is
implementation-defined.

#### A.2.5.3 Floating Constants

A floating constants consists of an integer part, a decimal part, a fraction
part, an `e` or `E`, an optionally signed integer exponent and an optional type
suffix. one of `f`, `F`, `l` or `L`. The type is determined by the suffix; `F`
or `f` makes it `float`, `L` or `l` makes it `long double`, otherwise it is
`double`.

#### A.2.5.4 Enumeration Constants

Indentifiers declared as enumerators are constants of type `int`.

### A.2.6 String Literals

A string literal, also called a string constant, is a sequence of characters
surrounded by double quotes as in `"..."`.

## A.3 Syntax Notation

## A.4 Meaning of Identifiers

Identifiers, or names, refer to a variety of things: functions; tags of
structures, unions, and enumerations; members of structures or unions;
enumeration constants; typedef names; and objects. An object, sometimes called
a variable, is a location in storage, and its interpretation depends on two
main attributes: its `storage class` and its `type`. The storage class
determines the lifetime of the storage associated with the identified object;
the type determines the meaning of the values found in the identified object. A
name also has a scope, which is the region of the program in which it is known,
and a linkage, which determines whether the same name in another scope refers
to the same object or function.

### A.4.1 Storage Class

There are two storage classes:

- **automatic**: automatic objects are local to a block, and are discarded on
  exit from the block.
- **static**: static objects may be local to a block or external to all blocks,
  but in either case retain their values across exit from and reentry to
  functions and blocks.

### A.4.2 Basic Types

The standard header `<limits.h>` defines the largest and smallest values of each
type in the local implementation.

Types `char`, and `int` of all sizes, each with or without sign, and also
enumeration types, will collectively be called ***integral*** types. The types
`float`, `double`, and `long double` will be called ***floating*** types. All
these types are referred to as ***arithmetic*** types.

### A.4.3 Derived Types

- `arrays` of objects of a given types;
- `functions` returning objects of a given types;
- `pointers` to objects of a given types;
- `structures` containing a sequence of objects of various types;
- `unions` capable of containing any of one of several objects of various types.

### A.4.4 Type Qualifiers

Declaring an object `const` announces that its value will not be changed;
declaring it `volatile` announces that it has special properties relevant to
optimization. Neither qualifier affects the range of values or arithmetic
properties of the object.

## A.5 Objects and Lvalues

An `Object` is a named region of storage; an `lvalue` is an expression referring
to an object. If `E` is an expression of pointer type, then `*E` is an lvalue
expression referring to the object to which `E` points. The name `lvalue` comes
from the assignment expression `E1 = E2` in which the left operand `E1` must be
an lvalue expression.

> lvalue 是可以被赋值的表达式或变量，它总是代表着一个可修改的内存位置。

## A.6 Conversions

### A.6.1 Integral Promotion

### A.6.2 Integral Conversions

### A.6.3 Integer and Floating

### A.6.4 Floating Types

### A.6.5 Arithmetic Conversions

### A.6.6 Pointers and Integers

### A.6.7 Void

### A.6.8 Pointers to Void

## A.7 Expressions

The precedence of expression operators is the same as the order of the major
subsections of this section, highest precedence first. Within each subsection,
the operators have the same precedence. Left- or right-associativity is
specified in each subsection for the operators discussed therein.

The precedence and associativity of operators is fully specified, but the order
of evaluation of expressions is, with certain exceptions, undefined, even if
the subexpressions involve side effects.

The handling of overflow, divide check, and other exceptions in expression
evaluation is not defined by the language. Most existing implementations of C
ignore overflow in evaluation of signed integral expressions and assignments,
but this behavior is not guaranteed.

### A.7.1 Pointer Conversion

>>>>> progress

### A.7.17 Assignment Expressions

There are several assignment operators; all group right-to-left.

```pseudo
    assignment-expression:
conditional-expression
unary-expression assignment-operator assignment-expression

    assignment-operator: one of
= *= /= %= += -= <<= >>= &= ^= |=
```

All require an lvalue as left operand, and the lvalue must be modifiable: it
must not be an array, and must not have an incomplete type, or be a function.
Also, its type must not be qualified with `const`; if it is a structure or
union, it must not have any member or, recursively, submember qualified with
`const`. The type of an assignment expression is that of its left operand, and
the value is the value stored in the left operand after the assignment has
taken place.

An expression of the form `E1 op= E2` is equivalent to `E1 = E1 op (E2)` except
that `E1` is evaluated only once.

## A.8 Declarations

Declarations specify the interpretation given to each identifier; they do not
necessarily reserve storage associated with the identifier. Declarations that
reserve storage are called definitions. Declarations have the form

```pseudo
    declaration:
declaration-specifiers init-declarator-list(opt);
```

The declarators in the init-declarator list contain the identifiers being
declared; the declaration-specifiers consist of a sequence of type and storage
class specifiers.

```pseudo
    declaration-specifiers:
storage-class-specifier declaration-specifiers(opt)
type-specifier declaration-specifiers(opt)
type-qualifier declaration-specifiers(opt)


    init-declarator-list:
init-declarator
init-declarator-list , init-declarator

    init-declarator:
declarator
declarator = initializer
```

Declarators contain the names being declared. A declaration must have at least
one declarator, or its type specifier must declare a structure tag, a union
tag, or the members of an enumeration; empty declarations are not permitted.

### A.8.2 Type Specifiers

The type-specifiers are

```pseudo
    type specifier:
void
char
short
int
long
float
double
signed
unsigned
struct-or-union-specifier
enum-specifier
typedef-name
```

At most one of the words `long` or `short` may be specified together with int;
the meaning is the same if `int` is not mentioned. The word `long` may be
specified together with double. At most one of `signed` or `unsigned` may be
specified together with `int` or any of its `short` or `long` varieties, or
with `char`. Either may appear alone in which case `int` is understood. The
`signed` specifier is useful for forcing `char` objects to carry a sign; it is
permissible but redundant with other integral types.

Otherwise, at most one type-specifier may be given in a declaration. If the
type-specifier is missing from a declaration, it is taken to be `int`.

Types may also be qualified, to indicate special properties of the objects
being declared.

```pseudo
    type-qualifier:
const
volatile
```

Type qualifiers may appear with any type specifier. A `const` object may be
initialized, but not thereafter assigned to. There are no
implementation-dependent semantics for `volatile` objects.

The purpose of `const` is to announce objects that may be placed in read-only
memory, and perhaps to increase opportunities for optimization. The purpose of
`volatile` is to force an implementation to suppress optimization that could
otherwise occur. For example, for a machine with memory-mapped input/output, a
pointer to a device register might be declared as a pointer to `volatile`, in
order to prevent the compiler from removing apparently redundant references
through the pointer. Except that it should diagnose explicit attempts to change
`const` objects, a compiler may ignore these qualifiers.
