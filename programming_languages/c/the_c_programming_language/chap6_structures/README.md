# Chapter 6: Structures

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
struct point pt;

// defines a variable pt which is a structure of type struct point.
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

structure parameters are passed by value like any others. Structure pointers are
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

- a pointer to the next of the word
- a count of the number of occurrences
- a pointer to the left child node
- a pointer to the right child node

It is illegal for a structure to contain an instance of itself, but

```c
struct tnode *left;
```

declaras `left` to be a pointer to a `tnode`, not a `tnode` itself.

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
