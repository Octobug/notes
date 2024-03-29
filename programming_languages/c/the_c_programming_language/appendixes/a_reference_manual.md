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
    - [A.7.2 Primary Expressions](#a72-primary-expressions)
    - [A.7.3 Postfix Expressions](#a73-postfix-expressions)
      - [A.7.3.1 Array References](#a731-array-references)
      - [A.7.3.2 Function Calls](#a732-function-calls)
      - [A.7.3.3 Structure References](#a733-structure-references)
      - [A.7.3.4 Postfix Incrementation](#a734-postfix-incrementation)
    - [A.7.4 Unary Operators](#a74-unary-operators)
      - [A.7.4.1 Prefix Incrementation Operators](#a741-prefix-incrementation-operators)
      - [A.7.4.2 Address Operator](#a742-address-operator)
      - [A.7.4.3 Indirection Operator](#a743-indirection-operator)
      - [A.7.4.4 Unary Plus Operator](#a744-unary-plus-operator)
      - [A.7.4.5 Unary Minus Operator](#a745-unary-minus-operator)
      - [A.7.4.6 One's Complement Operator](#a746-ones-complement-operator)
      - [A.7.4.7 Logical Negation Operator](#a747-logical-negation-operator)
      - [A.7.4.8 Sizeof Operator](#a748-sizeof-operator)
    - [A.7.5 Casts](#a75-casts)
    - [A.7.6 Multiplicative Operators](#a76-multiplicative-operators)
    - [A.7.7 Additive Operators](#a77-additive-operators)
    - [A.7.8 Shift Operators](#a78-shift-operators)
    - [A.7.9 Relational Operators](#a79-relational-operators)
    - [A.7.10 Equality Operators](#a710-equality-operators)
    - [A.7.11 Bitwise AND Operator](#a711-bitwise-and-operator)
    - [A.7.12 Bitwise Exclusive OR Operator](#a712-bitwise-exclusive-or-operator)
    - [A.7.13 Bitwise Inclusive OR Operator](#a713-bitwise-inclusive-or-operator)
    - [A.7.14 Logical AND Operator](#a714-logical-and-operator)
    - [A.7.15 Logical OR Operator](#a715-logical-or-operator)
    - [A.7.16 Conditional Operator](#a716-conditional-operator)
    - [A.7.17 Assignment Expressions](#a717-assignment-expressions)
    - [A.7.18 Comma Operator](#a718-comma-operator)
    - [A.7.19 Constant Expressions](#a719-constant-expressions)
  - [A.8 Declarations](#a8-declarations)
    - [A.8.1 Storage Class Specifiers](#a81-storage-class-specifiers)
    - [A.8.2 Type Specifiers](#a82-type-specifiers)
    - [A.8.3 Structure and Union Declarations](#a83-structure-and-union-declarations)
    - [A.8.4 Enumerations](#a84-enumerations)
    - [A.8.5 Declarators](#a85-declarators)
    - [A.8.6 Meaning of Declarators](#a86-meaning-of-declarators)
      - [A.8.6.1 Pointer Declaratiors](#a861-pointer-declaratiors)
      - [A.8.6.2 Array Declarators](#a862-array-declarators)
      - [A.8.6.3 Function Declarators](#a863-function-declarators)
    - [A.8.7 Initializations](#a87-initializations)
    - [A.8.8 Type names](#a88-type-names)
    - [A.8.9 Typedef](#a89-typedef)
    - [A.8.10 Type Equivalence](#a810-type-equivalence)
  - [A.9 Statements](#a9-statements)
    - [A.9.1 Labeled Statements](#a91-labeled-statements)
    - [A.9.2 Expression Statement](#a92-expression-statement)
    - [A.9.3 Compound Statement](#a93-compound-statement)
    - [A.9.4 Selection Statements](#a94-selection-statements)
    - [A.9.5 Iteration Statements](#a95-iteration-statements)
    - [A.9.6 Jump Statements](#a96-jump-statements)
  - [A.10 External Declarations](#a10-external-declarations)
    - [A.10.1 Function Definitions](#a101-function-definitions)
    - [A.10.2 External Declarations](#a102-external-declarations)
  - [A.11 Scope and Linkage](#a11-scope-and-linkage)
    - [A.11.1 Lexical Scope](#a111-lexical-scope)
    - [A.11.2 Linkage](#a112-linkage)
  - [A.12 Preprocessing](#a12-preprocessing)
    - [A.12.1 Trigraph Sequences](#a121-trigraph-sequences)
    - [A.12.2 Line Splicing](#a122-line-splicing)
    - [A.12.3 Macro Definition and Expansion](#a123-macro-definition-and-expansion)
    - [A.12.4 File Inclusion](#a124-file-inclusion)
    - [A.12.5 Conditional Compilation](#a125-conditional-compilation)
    - [A.12.6 Line Control](#a126-line-control)
    - [A.12.7 Error Generation](#a127-error-generation)
    - [A.12.8 Pragmas](#a128-pragmas)
    - [A.12.9 Null Directive](#a129-null-directive)
    - [A.12.10 Predefined Names](#a1210-predefined-names)
  - [A.13 Grammar](#a13-grammar)

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

### A.7.2 Primary Expressions

Primary expressions are identifiers, constants, strings, or expressions in
parentheses.

### A.7.3 Postfix Expressions

#### A.7.3.1 Array References

#### A.7.3.2 Function Calls

#### A.7.3.3 Structure References

#### A.7.3.4 Postfix Incrementation

### A.7.4 Unary Operators

#### A.7.4.1 Prefix Incrementation Operators

eg. `++var`

#### A.7.4.2 Address Operator

`&`

#### A.7.4.3 Indirection Operator

`*`

#### A.7.4.4 Unary Plus Operator

`+`

#### A.7.4.5 Unary Minus Operator

`-`

#### A.7.4.6 One's Complement Operator

`~`

#### A.7.4.7 Logical Negation Operator

`!`

#### A.7.4.8 Sizeof Operator

`sizeof`

### A.7.5 Casts

`(type-name)cast-expression`

### A.7.6 Multiplicative Operators

`*`, `/`, and `%`

### A.7.7 Additive Operators

`+`, `-`

A pointer to an object in an array and a value of any integral type may be
added. The latter is converted to an address offset by multiplying it by the
size of the object to which the pointer points. Thus if `p` is a pointer to an
object in an array, the expression `p + 1` is a pointer to the next object in
the array.

### A.7.8 Shift Operators

`<<`, `>>`

### A.7.9 Relational Operators

`<`, `>`, `<=`, `>=`

### A.7.10 Equality Operators

`==`, `!=`

### A.7.11 Bitwise AND Operator

`&`

### A.7.12 Bitwise Exclusive OR Operator

`^`

### A.7.13 Bitwise Inclusive OR Operator

`|`

### A.7.14 Logical AND Operator

`&&`

### A.7.15 Logical OR Operator

`||`

### A.7.16 Conditional Operator

`? E1 : E2`

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

### A.7.18 Comma Operator

`,`

### A.7.19 Constant Expressions

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

### A.8.1 Storage Class Specifiers

The storage class specifiers are:

- `auto`
- `register`
- `static`
- `extern`
- `typedef`

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

### A.8.3 Structure and Union Declarations

### A.8.4 Enumerations

### A.8.5 Declarators

### A.8.6 Meaning of Declarators

#### A.8.6.1 Pointer Declaratiors

#### A.8.6.2 Array Declarators

#### A.8.6.3 Function Declarators

### A.8.7 Initializations

### A.8.8 Type names

### A.8.9 Typedef

Declarations whose storage class specifier is `typedef` do not declare objects;
instead they define identifiers that name types. These identifiers are called
typedef names.

### A.8.10 Type Equivalence

## A.9 Statements

Except as described, statements are executed in sequence. Statements are
executed for their effect, and do not have values.

### A.9.1 Labeled Statements

```pseudo
case constant-expression: statement
default: statement
```

### A.9.2 Expression Statement

### A.9.3 Compound Statement

The body of a function definition is a compound statement.

### A.9.4 Selection Statements

`if...else`, `switch...case...`

### A.9.5 Iteration Statements

Iteration statements specify looping.

`while`, `do...while`, `for(;;)`

### A.9.6 Jump Statements

`goto`, `continue`, `break`, `return`

## A.10 External Declarations

The unit of input provided to the C compiler is called a translation unit; it
consists of a sequence of external declarations, which are either declarations
or function definitions.

### A.10.1 Function Definitions

### A.10.2 External Declarations

## A.11 Scope and Linkage

A program need not all be compiled at one time: the source text may be kept in
several files containing translation units, and precompiled routines may be
loaded from libraries.

There are two kinds of scope to consider:

1. The `lexical scope` of an identifier which is the region of the program text
   within which the identifier's characteristics are understood;
2. The scope associated with objects and functions with external linkage, which
   determines the connections between identifiers in separately compiled
   translation units.

### A.11.1 Lexical Scope

### A.11.2 Linkage

## A.12 Preprocessing

A preprocessor performs macro substitution, conditional compilation, and
inclusion of named files.

### A.12.1 Trigraph Sequences

The character set of C source programs is contained within seven-bit ASCII, but
is a superset of the ISO 646-1983 Invariant Code Set. In order to enable
programs to be represented in the reduced set, all occurrences of the following
trigraph sequences are replaced by the corresponding single character.

eg. `??=` -> `#`

### A.12.2 Line Splicing

`\`

### A.12.3 Macro Definition and Expansion

### A.12.4 File Inclusion

### A.12.5 Conditional Compilation

### A.12.6 Line Control

### A.12.7 Error Generation

A preprocessor line of the form

```c
# error token-sequence
```

causes the preprocessor to write a diagnostic message that includes the token
sequence.

### A.12.8 Pragmas

### A.12.9 Null Directive

### A.12.10 Predefined Names

## A.13 Grammar
