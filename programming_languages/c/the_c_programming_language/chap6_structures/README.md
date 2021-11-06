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
