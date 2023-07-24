# Methods and interfaces

- [Methods and interfaces](#methods-and-interfaces)
  - [Methods](#methods)
    - [Methods are functions](#methods-are-functions)
    - [Pointer receivers](#pointer-receivers)
    - [Pointers and functions](#pointers-and-functions)
    - [Methods and pointer indirection](#methods-and-pointer-indirection)
    - [Choosing a value or pointer receiver](#choosing-a-value-or-pointer-receiver)
  - [Interfaces](#interfaces)
    - [Interfaces are implemented implicitly](#interfaces-are-implemented-implicitly)
    - [Interface values](#interface-values)
    - [Interface values with nil underlying values](#interface-values-with-nil-underlying-values)
    - [Nil interface values](#nil-interface-values)
    - [The empty interface](#the-empty-interface)
    - [Type assertions](#type-assertions)
    - [Type switches](#type-switches)
    - [Stringers](#stringers)
    - [Exercise: Stringers](#exercise-stringers)
  - [Errors](#errors)
    - [Exercise: Errors](#exercise-errors)
  - [Readers](#readers)
    - [Exercise: Readers](#exercise-readers)
    - [Exercise: rot13Reader](#exercise-rot13reader)
  - [Images](#images)
    - [Exercise: Images](#exercise-images)

## Methods

A method is a function with a special `receiver` argument.

The receiver appears in its own argument list between the `func` keyword and
the method name.

```go
type Vertex struct {
    X, Y float64
}

func (v Vertex) Abs() float64 {
    return math.Sqrt(v.X*v.X + v.Y*v.Y)
}

func main() {
    v := Vertex{3, 4}
    fmt.Println(v.Abs())
}
```

In this example, the `Abs` method has a `receiver` of type `Vertex` named `v`.

### Methods are functions

A method is just a function with a `receiver` argument.

```go
type Vertex struct {
    X, Y float64
}

func Abs(v Vertex) float64 {
    return math.Sqrt(v.X*v.X + v.Y*v.Y)
}

func main() {
    v := Vertex{3, 4}
    fmt.Println(Abs(v))
}
```

Here's `Abs` written as a regular function with no change in functionality.

You can declare a method on non-struct types, too.

```go
type MyFloat float64

func (f MyFloat) Abs() float64 {
    if f < 0 {
        return float64(-f)
    }
    return float64(f)
}

func main() {
    f := MyFloat(-math.Sqrt2)
    fmt.Println(f.Abs())
}
```

In this example we see a numeric type `MyFloat` with an `Abs` method.

You can only declare a method with a receiver whose type is defined in the same
package as the method. You cannot declare a method with a receiver whose type
is defined in another package (which includes the built-in types such as `int`).

### Pointer receivers

You can declare methods with `pointer receivers`.

This means the receiver type has the literal syntax `*T` for some type `T`.
(Also, `T` cannot itself be a pointer such as `*int`.)

```go
type Vertex struct {
    X, Y float64
}

func (v Vertex) Abs() float64 {
    return math.Sqrt(v.X*v.X + v.Y*v.Y)
}

func (v *Vertex) Scale(f float64) {
    v.X = v.X * f
    v.Y = v.Y * f
}

func main() {
    v := Vertex{3, 4}
    v.Scale(10)
    fmt.Println(v.Abs())
}
```

For example, the `Scale` method here is defined on `*Vertex`.

Methods with pointer receivers can modify the value to which the receiver
points (as `Scale` does here). Since methods often need to modify their
receiver, pointer receivers are more common than value receivers.

With a value receiver, the `Scale` method operates on a copy of the original
`Vertex` value. (This is the same behavior as for any other function argument.)
The `Scale` method must have a pointer receiver to change the `Vertex` value
declared in the `main` function.

### Pointers and functions

Here we see the `Abs` and `Scale` methods rewritten as functions.

```go
type Vertex struct {
    X, Y float64
}

func Abs(v Vertex) float64 {
    return math.Sqrt(v.X*v.X + v.Y*v.Y)
}

func Scale(v *Vertex, f float64) {
    v.X = v.X * f
    v.Y = v.Y * f
}

func main() {
    v := Vertex{3, 4}
    Scale(&v, 10)
    fmt.Println(Abs(v))
}
```

### Methods and pointer indirection

```go
type Vertex struct {
    X, Y float64
}

func (v *Vertex) Scale(f float64) {
    v.X = v.X * f
    v.Y = v.Y * f
}

func ScaleFunc(v *Vertex, f float64) {
    v.X = v.X * f
    v.Y = v.Y * f
}

func main() {
    v := Vertex{3, 4}
    v.Scale(2)
    ScaleFunc(&v, 10)

    p := &Vertex{4, 3}
    p.Scale(3)
    ScaleFunc(p, 8)

    fmt.Println(v, p)
}
```

Comparing the previous two programs, you might notice that functions with a
pointer argument must take a pointer:

```go
var v Vertex
ScaleFunc(v, 5)  // Compile error!
ScaleFunc(&v, 5) // OK
```

while methods with pointer receivers take either a value or a pointer as the
receiver when they are called:

```go
var v Vertex
v.Scale(5)  // OK
p := &v
p.Scale(10) // OK
```

For the statement `v.Scale(5)`, even though `v` is a value and not a pointer,
the method with the pointer receiver is called automatically. That is, as a
convenience, Go interprets the statement `v.Scale(5)` as `(&v).Scale(5)` since
the `Scale` method has a pointer receiver.

```go
type Vertex struct {
    X, Y float64
}

func (v Vertex) Abs() float64 {
    return math.Sqrt(v.X*v.X + v.Y*v.Y)
}

func AbsFunc(v Vertex) float64 {
    return math.Sqrt(v.X*v.X + v.Y*v.Y)
}

func main() {
    v := Vertex{3, 4}
    fmt.Println(v.Abs())
    fmt.Println(AbsFunc(v))

    p := &Vertex{4, 3}
    fmt.Println(p.Abs())
    fmt.Println(AbsFunc(*p))
}
```

The equivalent thing happens in the reverse direction.

Functions that take a value argument must take a value of that specific type:

```go
var v Vertex
fmt.Println(AbsFunc(v))  // OK
fmt.Println(AbsFunc(&v)) // Compile error!
```

while methods with value receivers take either a value or a pointer as the
receiver when they are called:

```go
var v Vertex
fmt.Println(v.Abs()) // OK
p := &v
fmt.Println(p.Abs()) // OK
```

In this case, the method call `p.Abs()` is interpreted as `(*p).Abs()`.

### Choosing a value or pointer receiver

There are two reasons to use a pointer receiver.

- The first is so that the method can modify the value that its receiver points
  to.
- The second is to avoid copying the value on each method call. This can be
  more efficient if the receiver is a large struct, for example.

```go
type Vertex struct {
    X, Y float64
}

func (v *Vertex) Scale(f float64) {
    v.X = v.X * f
    v.Y = v.Y * f
}

func (v *Vertex) Abs() float64 {
    return math.Sqrt(v.X*v.X + v.Y*v.Y)
}

func main() {
    v := &Vertex{3, 4}
    fmt.Printf("Before scaling: %+v, Abs: %v\n", v, v.Abs())
    v.Scale(5)
    fmt.Printf("After scaling: %+v, Abs: %v\n", v, v.Abs())
}
```

In this example, both `Scale` and `Abs` are methods with receiver type
`*Vertex`, even though the `Abs` method needn't modify its receiver.

In general, all methods on a given type should have either **value** or
**pointer** receivers, but not a mixture of both.

## Interfaces

An `interface` type is defined as a set of method signatures.

A value of interface type can hold any value that implements those methods.

```go
package main

import (
    "fmt"
    "math"
)

type MyFloat float64

func (f MyFloat) Abs() float64 {
    if f < 0 {
        return float64(-f)
    }
    return float64(f)
}

type Vertex struct {
    X, Y float64
}

func (v *Vertex) Abs() float64 {
    return math.Sqrt(v.X*v.X + v.Y*v.Y)
}
type Abser interface {
    Abs() float64
}

func main() {
    var a Abser
    f := MyFloat(-math.Sqrt2)
    v := Vertex{3, 4}

    a = f  // a MyFloat implements Abser
    a = &v // a *Vertex implements Abser

    // In the following line, v is a Vertex (not *Vertex)
    // and does NOT implement Abser.
    a = v

    fmt.Println(a.Abs())
}
```

### Interfaces are implemented implicitly

```go
package main

import "fmt"

type I interface {
    M()
}

type T struct {
    S string
}

// This method means type T implements the interface I,
// but we don't need to explicitly declare that it does so.
func (t T) M() {
    fmt.Println(t.S)
}

func main() {
    var i I = T{"hello"}
    i.M()
}
```

A type implements an interface by implementing its methods. There is no
explicit declaration of intent, no "implements" keyword.

Implicit interfaces decouple the definition of an interface from its
implementation, which could then appear in any package without prearrangement.

### Interface values

```go
package main

import (
    "fmt"
    "math"
)

type I interface {
    M()
}

type T struct {
    S string
}

func (t *T) M() {
    fmt.Println(t.S)
}

type F float64

func (f F) M() {
    fmt.Println(f)
}

func main() {
    var i I

    i = &T{"Hello"}
    describe(i)
    i.M()

    i = F(math.Pi)
    describe(i)
    i.M()
}

func describe(i I) {
    fmt.Printf("(%v, %T)\n", i, i)
}
```

`interface` values can be thought of as a tuple of **a value and a concrete
type**:

`(value, type)`

An `interface` value holds a value of a specific underlying concrete type.

Calling a method on an interface value executes the method of the same name on
its underlying type.

### Interface values with nil underlying values

```go
package main

import "fmt"

type I interface {
    M()
}

type T struct {
    S string
}

func (t *T) M() {
    if t == nil {
        fmt.Println("<nil>")
        return
    }
    fmt.Println(t.S)
}

func main() {
    var i I

    var t *T
    i = t
    describe(i)
    i.M()

    i = &T{"hello"}
    describe(i)
    i.M()
}

func describe(i I) {
    fmt.Printf("(%v, %T)\n", i, i)
}
```

If the concrete value inside the interface itself is `nil`, the method will be
called with a `nil` receiver.

In some languages this would trigger a `null` pointer exception, but in Go it
is common to write methods that gracefully handle being called with a `nil`
receiver.

Note that an `interface` value that holds a `nil` concrete value is itself
non-nil.

### Nil interface values

```go
package main

import "fmt"

type I interface {
    M()
}

func main() {
    var i I
    describe(i)
    i.M()
}

func describe(i I) {
    fmt.Printf("(%v, %T)\n", i, i)
}
```

A `nil` interface value holds neither value nor concrete type.

Calling a method on a `nil` interface is a run-time error because there is no
type inside the interface tuple to indicate which concrete method to call.

### The empty interface

```go
package main

import "fmt"

func main() {
    var i interface{}
    describe(i)

    i = 42
    describe(i)

    i = "hello"
    describe(i)
}

func describe(i interface{}) {
    fmt.Printf("(%v, %T)\n", i, i)
}
```

The interface type that specifies zero methods is known as the
`empty interface`:

```go
interface{}
```

An empty interface may hold values of any type. (Every type implements at least
zero methods.)

Empty interfaces are used by code that handles values of unknown type. For
example, `fmt.Print` takes any number of arguments of type `interface{}`.

### Type assertions

```go
package main

import "fmt"

func main() {
    var i interface{} = "hello"

    s := i.(string)
    fmt.Println(s)

    s, ok := i.(string)
    fmt.Println(s, ok)

    f, ok := i.(float64)
    fmt.Println(f, ok)

    f = i.(float64) // panic
    fmt.Println(f)
}
```

A `type assertion` provides access to an interface value's underlying concrete
value.

```go
t := i.(T)
```

This statement asserts that the interface value `i` holds the concrete type `T`
and assigns the underlying `T` value to the variable `t`.

If `i` does not hold a `T`, the statement will trigger a panic.

To *test* whether an interface value holds a specific type, a type assertion
can return two values:

- the underlying value
- a boolean value that reports whether the assertion succeeded.

```go
t, ok := i.(T)
```

If `i` holds a `T`, then `t` will be the underlying value and ok will be `true`.

If not, ok will be `false` and `t` will be the zero value of type `T`, and no
panic occurs.

Note the similarity between this syntax and that of reading from a map.

### Type switches

```go
package main

import "fmt"

func do(i interface{}) {
    switch v := i.(type) {
    case int:
        fmt.Printf("Twice %v is %v\n", v, v*2)
    case string:
        fmt.Printf("%q is %v bytes long\n", v, len(v))
    default:
        fmt.Printf("I don't know about type %T!\n", v)
    }
}

func main() {
    do(21)
    do("hello")
    do(true)
}
```

A `type switch` is a construct that permits several type assertions in series.

A `type switch` is like a regular switch statement, but the cases in a type
switch specify types (not values), and those values are compared against the
type of the value held by the given interface value.

```go
switch v := i.(type) {
case T:
    // here v has type T
case S:
    // here v has type S
default:
    // no match; here v has the same type as i
}
```

### Stringers

```go
package main

import "fmt"

type Person struct {
    Name string
    Age  int
}

func (p Person) String() string {
    return fmt.Sprintf("%v (%v years)", p.Name, p.Age)
}

func main() {
    a := Person{"Arthur Dent", 42}
    z := Person{"Zaphod Beeblebrox", 9001}
    fmt.Println(a, z)
}
```

One of the most ubiquitous interfaces is `Stringer` defined by the `fmt`
package.

```go
type Stringer interface {
    String() string
}
```

A `Stringer` is a type that can describe itself as a string. The `fmt` package
(and many others) look for this interface to print values.

### Exercise: Stringers

Make the `IPAddr` type implement `fmt.Stringer` to print the address as a
dotted quad.

For instance, `IPAddr{1, 2, 3, 4}` should print as `"1.2.3.4"`.

```go
package main

import "fmt"

type IPAddr [4]byte

// TODO: Add a "String() string" method to IPAddr.
func (ip IPAddr) String() string {
    return fmt.Sprintf("%v.%v.%v.%v", ip[0], ip[1], ip[2], ip[3])
}

func main() {
    hosts := map[string]IPAddr{
        "loopback":  {127, 0, 0, 1},
        "googleDNS": {8, 8, 8, 8},
    }
    for name, ip := range hosts {
        fmt.Printf("%v: %v\n", name, ip)
    }
}
```

## Errors

```go
package main

import (
    "fmt"
    "time"
)

type MyError struct {
    When time.Time
    What string
}

func (e *MyError) Error() string {
    return fmt.Sprintf("at %v, %s",
        e.When, e.What)
}

func run() error {
    return &MyError{
        time.Now(),
        "it didn't work",
    }
}

func main() {
    if err := run(); err != nil {
        fmt.Println(err)
    }
}
```

Go programs express error state with `error` values.

The `error` type is a built-in interface similar to `fmt.Stringer`:

```go
type error interface {
    Error() string
}
```

Functions often return an `error` value, and calling code should handle errors
by testing whether the error equals `nil`.

```go
i, err := strconv.Atoi("42")
if err != nil {
    fmt.Printf("couldn't convert number: %v\n", err)
    return
}
fmt.Println("Converted integer:", i)
```

A nil `error` denotes success; a non-nil `error` denotes failure.

### Exercise: Errors

Copy your `Sqrt` function from the earlier exercise and modify it to return an
`error` value.

`Sqrt` should return a non-nil `error` value when given a negative number, as
it doesn't support complex numbers.

Create a new type

```go
type ErrNegativeSqrt float64
```

and make it an `error` by giving it a

```go
func (e ErrNegativeSqrt) Error() string
```

method such that `ErrNegativeSqrt(-2).Error()` returns
`"cannot Sqrt negative number: -2"`.

**Note**: A call to `fmt.Sprint(e)` inside the `Error` method will send the
program into an infinite loop. You can avoid this by converting `e` first:
`fmt.Sprint(float64(e))`.

Change your `Sqrt` function to return an `ErrNegativeSqrt` value when given a
negative number. You can avoid this by converting `e` first:
`fmt.Sprint(float64(e))`. Why?

`fmt.Sprint(e)` will call `e.Error()` to convert the value `e` to a `string`.
If the `Error()` method calls `fmt.Sprint(e)`, then the program recurses until
out of memory.

```go
package main

import (
    "fmt"
)

type ErrNegativeSqrt float64

func (e ErrNegativeSqrt) Error() string {
    return fmt.Sprintf("Negative float %v is unacceptable!!!", float64(e))
}

func Sqrt(x float64) (float64, error) {
    if x < 0 {
        return 0, ErrNegativeSqrt(x)
    }

    z := float64(1)
    for i := 1.0; i > 0.000000001; {
        z -= (z*z - x) / (2*z)
        i = 2 - (z * z)
        if i < 0 {
            i *= -1
        }
    }
    return z, nil
}

func main() {
    fmt.Println(Sqrt(2))
    fmt.Println(Sqrt(-2))
}
```

## Readers

>>>>> <https://go.dev/tour/methods/21>

### Exercise: Readers

### Exercise: rot13Reader

## Images

### Exercise: Images
