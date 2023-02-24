# Chapter 6: Structures

- [Chapter 6: Structures](#chapter-6-structures)
  - [6.1 Basics of Structures](#61-basics-of-structures)
  - [6.2 Structures and Functions](#62-structures-and-functions)
  - [6.3 Arrays of Structures](#63-arrays-of-structures)
  - [6.4 Pointers to Structures](#64-pointers-to-structures)
  - [6.5 Self-referential Structures](#65-self-referential-structures)
  - [6.6 Table Lookup](#66-table-lookup)
  - [6.7 Typedef](#67-typedef)
  - [6.8 Unions](#68-unions)
  - [6.9 Bit-fields](#69-bit-fields)

A structure is a collection of one or more variables, possibly of different
types, grouped together under a single name for convenient handling.

## 6.1 Basics of Structures

```c
struct point 
{
    int x;
    int y;
}
```

An optional name called a `structure tag` may follow the word `struct` (as with
`point` here). The tag names this kind of structure, and can be used
subsequently as a shorthand for the part of the declaration in braces.

The variables named in a structure are called `members`. A structure member or
tag and an ordinary variable can have the same name without conflict, since they
can always be distinguished by context.

A struct declaration defines a type.

```c
struct { ... } x, y, z;
```

is syntactically analogues to

```c
int x, y, z;
```

A structure declaration that is not followed by a list of variables reserves no
storage; it merely describes a template or the shape of a structure.

```c
// defines a variable pt which is a structure of type struct point.
struct point pt;

struct point maxpt = { 320, 200 };
printf("%d, %d", pt.x, pt.y);
```

Structures can be nested.

```c
struct rect {
    struct point pt1;
    struct point pt2;
};

struct rect screen;

// refers to the x coordinate of the pt1 member of screen
screen.pt1.x;
```

## 6.2 Structures and Functions

Structure parameters are passed by value like any others. Structure pointers are
just like pointers to ordinary variables.

```c
// pp is a pointer to a structure of type struct point.
struct point *pp;

// to use pp, we might write
struct point origin, *pp;

pp = &origin;
printf("origin is (%d, %d)\n", (*pp).x, (*pp).y);
printf("origin is (%d, %d)\n, pp->x, pp->y);
```

The parentheses are necessary in `(*pp).x` because the precedence of the
structure member operator `.` is higher than `*`. `*pp.x` means `x` is a
pointer. `(*pp).x` is equivalent to `pp->x`;

```c
struct
{
    int len;
    char *str;
} *p;

++p->len
// increments len, not p

*p->str++ // == *p->(str++)
// increments str after accessing whatever it points to

(*p->str)++
// increments whatever str points to

*p++->str
// increments p after accessing whatever str points to
```

## 6.3 Arrays of Structures

```c
struct key
{
    char *word;
    int count;
} keytab[NKEYS];

// is equivalent to

struct key
{
    char *word;
    int count;
};

struct key keytab[NKEYS];
```

C provides a compile-time unary operator called `sizeof` that can be used to
compute the size of any object. The expressions `sizeof object` and
`sizeof(type name)` yield an unsigned integer whose type is `size_t`, defined
in the header `<stddef.h>`, equal to the size of the specified object
or type **in bytes**.

A `sizeof` can not be used in a `#if` line, because the preprocessor does not
parse type names. But the expression in the `#define` is not evaluated by the
preprocessor, so `sizeof` in `#define` is OK.

## 6.4 Pointers to Structures

There may be unnamed "holes" in a structure because of alignment requirements
for different objects. If a `char` is one byte and an `int` four bytes, the
structure

```c
sturct
{
    char c;
    int i;
};
```

might well require eight bytes, **not** five. The `sizeof` operator returns the
proper value.

## 6.5 Self-referential Structures

e.g. Use a `binary tree` to store words. The tree contains one "node" per
distinct word; each node contains

- a pointer to the text of the word
- a count of the number of occurrences
- a pointer to the left child node
- a pointer to the right child node

```c
struct tnode {              // the tree node:
    char * word;            // points to the text
    int count;              // number of occurrences
    struct tnode *left      // left child
    struct tnode *right;    // right child
}
```

This recursive declaration of a node is correct. It is illegal for a structure
to contain an instance of itself, but

```c
struct tnode *left;
```

declares `left` to be a pointer to a `tnode`, not a `tnode` itself.

One needs a variation of self-referential structures: two structures that refer
to each other:

```c
struct t
{
    ...
    struct s *p;    // p points to an s
};
struct s
{
    ...
    struct t *q;    // q points to a t
};
```

`malloc` returns `NULL` if no space is available.

## 6.6 Table Lookup

The standard idiom for walking along a linked list:

```c
for (ptr = head; ptr != NULL; ptr = ptr->next)
    ...
```

## 6.7 Typedef

C provides a facility called `typedef` for creating new data type names. For
example, the declaration `typedef int Length;` makes the name `Length` a synonym
for `int`. The type `Length` can be used in declarations, casts.

```c
Length len, maxlen;
Length *lengths[];
```

Similarly, the declaration `typedef char *String;` makes `String` a synonym for
`char *` or character pointer, which may then be used in declarations and casts.

```c
String p, lineptr[MAXLINES], alloc(int);
int strcmp(String, String);
p = (String) malloc(100);
```

Using capitalized names for typedefs to make them out is a good convention.

```c
typedef struct tnode *Treeptr;

// the tree node:
typedef struct tnode
{
    char *word;     // points to the text
    int count;      // number of occurrences
    Treeptr left;   // left child
    Treeptr right;  // right child
} Treenode;
```

This creates two new type keywords called `Treenode` (a structure) and `Treeptr`
(a pointer to the structure). Then the routine `talloc` could become

```c
Treeptr talloc(void)
{
    return (Treeptr) malloc(sizeof(Treenode));
}
```

A `typedef` declaration does not create a new type in any sense; it merely adds
a new name for some existing type. Nor are there any new semantics: variables
declared this way have exactly the same properties as variables whose
declarations are spelled out explicitly. In effect, `typedef` is like `#define`,
except that since it is interpreted by the compiler, it can cope with textual
substitutions that are beyond the capabilities of the preprocessor. For example,

```c
typedef int (*PFI)(char *, char *);
```

creates the type `PFI`, for "pointer to function (of two char * arguments)
returning int", which can be used in context like

```c
PFI strcmp, numcmp;
```

There are two main reasons for using typedefs.

1. To parameterize a program against portability problems.

   If `typedef`s are used for data types that may be machine-dependent, only
   the typedefs need change when the program is moved. One common situation is
   to use `typedef` names for various integer quantities, then make an
   appropriate set of choices of `short`, `int`, and `long` for each host
   machine. Types like `size_t` and `ptrdiff_t` from the standard library are
   examples.

2. The second purpose of `typedef`s is to provide better documentation for a
   program -- a type called `Treeptr` may be easier to understand than one
   declared only as a pointer to a complicated structure.

## 6.8 Unions

A `union` is a variable that may hold (at different times) objects of different
types and sizes, with the compiler keeping track of size and alignment
requirements. Unions provide a way to manipulate different kinds of data in a
single area of storage, without embedding any machine-dependent information in
the program.

The value of a particular constant must be stored in a variable of the proper
type, yet it is most convenient for table management if the value occupies the
same amount of storage and is stored in the same place regardless of its type.
And the purpose of a union -- a single variable that can legitimately hold any
one of several types.

```c
union u_tag
{
    int ival;
    float fval;
    char *sval;
} u;
```

The variable `u` will be large enough to hold the largest of the three types;
Any one of these types may be assigned to `u` and then used in expressions, so
long as the usage is consistent: the type retrieved must be the type most
recently stored. It is the programmer's responsibility to `keep` track of which
type is currently stored in a union.

Syntactically, members of a union are accessed as `union-name.member` or
`union-pointer->member`, just as for structures. If the variable `utype` is used
to keep track of the current type stored in `u`, then one might see code such as

```c
if (utype == INT)
    printf("%d\n", u.ival);
else if (utype == FLOAT)
    printf("%f\n", u.fval);
else if (utype == STRING)
    printf("%s\n", u.sval);
else
    printf("bad type %d in utype\n", utype);
```

Unions may occur within structures and arrays, and vice versa. The notation for
accessing a member of a union in a structure (or vice versa) is identical to
that for nested structures.

```c
struct
{
    char *name;
    int flags;
    int utype;
    union
    {
        int ival;
        float fval;
        char *sval;
    } u;
} symtab[NSYM];
```

The member `ival` is referred to as `symtab[i].u.ival`.

In effect, a union is a structure in which all members have offset zero from the
base, the structure is big enough to hold the "widest" member, and the alignment
is appropriate for all of the types in the union.

A union may only be initialized with a value of the type of its first member;
thus the union `u` described above can only be initialized with an integer
value.

## 6.9 Bit-fields

The most compact way to encode information is a set of one-bit flags in a single
`char` or `int`.

The usual way this is done is to define a set of "masks" corresponding to the
relevant bit positions, as in

```c
#define KEYWORD  01
#define EXTERNAL 02
#define STATIC   04
```

or

```c
enum { KEYWORD = 01, EXTERNAL = 02, STATIC = 04 };
```

The numbers must be powers of two. Then accessing the bits becomes a matter of
"bit-fiddling" with the shifting, masking, and complementing operators.

Certain idioms appear frequently:

```c
flags |= EXTERNAL | STATIC;
```

turns on the `EXTERNAL` and `STATIC` bits in flags, while

```c
flags &= ~(EXTERNAL | STATIC);
```

turns them off, and

```c
if ((flags & (EXTERNAL | STATIC)) == 0)
    ...
```

is `true` if both bits are off.

Although these idioms are readily mastered, as an alternative C offers the
capability of defining and accessing fields within a word directly rather than
by bitwise logical operators. A *bit-field*, or *field* for short, is a set of
adjacent bits within a single implementation-defined storage unit that we call a
"word". The symbol table `#defines` above could be replaced by the definition of
three fields:

```c
struct
{
    unsigned int is_keyword :   1;
    unsigned int is_extern  :   1;
    unsigned int is_static  :   1;
} flages;
```

This defines a variable called `flags` that contains three 1-bit fields. The
number following the colon represents the field width in bits. The fields are
declared `unsigned int` to ensure that they are unsigned quantities.

Fields behave like small integers, and may participate in arithmetic expressions
just like other integers.

```c
// to turn the bits on
flags.is_extern = flags.is_static = 1;
```

Fields need not be named; unnamed fields (a colon and width only) are used for
padding. The special width 0 may be used to force alignment at the next word
boundary.

Fields are not arrays, and they do not have addresses, so the `&` operator
cannot be applied to them.
