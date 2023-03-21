# Appendix A - Reference Manual

## A.2 Lexical Conventions

A program is translated in several phases. The first phases do low-level
lexical transformations, carry out directives introduced by the lines beginning
with the `#` character, and perform macro definition and expansion. When the
preprocessing is complete, the program has been reduced to a sequence of tokens.

### A.2.4 Keywords

`auto`, (`asm`),
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

### A.4.4 Type Qualifiers

Declaring an object `const` announces that its value will not be changed;
declaring it `volatile` announces that it has special properties relevant to
optimization. Neither qualifier affects the range of values or arithmetic
properties of the object.

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
