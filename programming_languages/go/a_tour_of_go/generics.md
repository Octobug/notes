# Generics

- [Generics](#generics)
  - [Type parameters](#type-parameters)
  - [Generic types](#generic-types)

## Type parameters

```go
package main

import "fmt"

// Index returns the index of x in s, or -1 if not found.
func Index[T comparable](s []T, x T) int {
    for i, v := range s {
        // v and x are type T, which has the comparable
        // constraint, so we can use == here.
        if v == x {
            return i
        }
    }
    return -1
}

func main() {
    // Index works on a slice of ints
    si := []int{10, 20, 15, -10}
    fmt.Println(Index(si, 15))

    // Index also works on a slice of strings
    ss := []string{"foo", "bar", "baz"}
    fmt.Println(Index(ss, "hello"))
}
```

Go functions can be written to work on multiple types using `type parameters`.
The `type parameters` of a function appear between brackets, before the
function's arguments.

```go
func Index[T comparable](s []T, x T) int
```

This declaration means that `s` is a slice of any type `T` that fulfills the
built-in constraint `comparable`. `x` is also a value of the same type.

`comparable` is a useful constraint that makes it possible to use the `==` and
`!=` operators on values of the type. In this example, we use it to compare a
value to all slice elements until a match is found. This `Index` function works
for any type that supports comparison.

## Generic types

In addition to generic functions, Go also supports generic types. A type can be
parameterized with a type parameter, which could be useful for implementing
generic data structures.

This example demonstrates a simple type declaration for a singly-linked list
holding any type of value.

As an exercise, add some functionality to this list implementation.

```go
package main

import "fmt"

// List represents a singly-linked list that holds
// values of any type.
type List[T any] struct {
    next *List[T]
    val  T
}

func main() {
    var head List[int]
    var node List[int]

    head.val = 1
    head.next = &node

    node.val = 2

    p := &head
    for {
        fmt.Println(p.val)
        p = p.next
        if p == nil {
            break
        }
    }
}
```
