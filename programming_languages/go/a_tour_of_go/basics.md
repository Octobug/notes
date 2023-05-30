# Basics

- [Basics](#basics)
  - [Packages, variables, and functions.](#packages-variables-and-functions)
    - [Packages](#packages)
    - [Imports](#imports)
    - [Exported names](#exported-names)
    - [Functions](#functions)
    - [Multiple results](#multiple-results)
    - [Named return values](#named-return-values)
    - [Variables](#variables)
    - [Variables with initializers](#variables-with-initializers)
    - [Short variable declarations](#short-variable-declarations)
    - [Basic types](#basic-types)
    - [Zero values](#zero-values)
    - [Type conversions](#type-conversions)
    - [Type inference](#type-inference)
    - [Constants](#constants)
    - [Numeric Constants](#numeric-constants)
  - [Flow control statements: for, if, else, switch and defer](#flow-control-statements-for-if-else-switch-and-defer)
    - [For](#for)
    - [If](#if)
      - [If with a short statement](#if-with-a-short-statement)
    - [Switch](#switch)
      - [Switch with no condition](#switch-with-no-condition)
    - [Defer](#defer)
      - [Stacking defers](#stacking-defers)
  - [More types: structs, slices, and maps.](#more-types-structs-slices-and-maps)
    - [Pointers](#pointers)
    - [Structs](#structs)
      - [Pointers to structs](#pointers-to-structs)
      - [Struct Literals](#struct-literals)
    - [Arrays](#arrays)
    - [Slices](#slices)
      - [Slices are like references to arrays](#slices-are-like-references-to-arrays)
      - [Slice literals](#slice-literals)
      - [Slice defaults](#slice-defaults)
      - [Slice length and capacity](#slice-length-and-capacity)
      - [Nil slices](#nil-slices)
      - [Creating a slice with make](#creating-a-slice-with-make)
      - [Slices of slices](#slices-of-slices)
      - [Appending to a slice](#appending-to-a-slice)
    - [Range](#range)
    - [Maps](#maps)
      - [Map literals](#map-literals)
      - [Mutating Maps](#mutating-maps)
    - [Function values](#function-values)
      - [Function closures](#function-closures)

## Packages, variables, and functions.

### Packages

Programs start running package `main`.

### Imports

It is good style to use the factored import statement.

### Exported names

A name is exported if it begins with a capital letter.

### Functions

A function can take zero or more arguments.

```go
func add(x int, y int) int {}
```

The type can be omitted from all but the last as:

```go
func add(x, y int) int {}
```

### Multiple results

```go
func swap(x, y string) (string, string) {
    return y, x
}
```

### Named return values

Go's return values may be named. If so, they are treated as variables defined
at the top of the function.

These names should be used to document the meaning of the return values.

A `return` statement without arguments returns the named return values. This is
known as a "naked" return.

```go
func split(sum int) (x, y int) {}
```

Naked return statements should be used only in short functions. They can harm
readability in longer functions.

### Variables

The `var` statement declares a list of variables; as in function argument lists,
the type is last.

A `var` statement can be at package or function level.

```go
var c, python, java bool
```

### Variables with initializers

If an initializer is present, the type can be omitted; the variable will take
the type of the initializer.

```gp
var i, j int = 1, 2
```

### Short variable declarations

```go
func main() {
    k := 3
}
```

Inside a function, the `:=` short assignment statement can be used.

Outside a function, every statement begins with a keyword (`var`, `func`, and
so on) and so the `:=` construct is not available.

### Basic types

```go
bool

string

int  int8  int16  int32  int64
uint uint8 uint16 uint32 uint64 uintptr

byte // alias for uint8

rune // alias for int32
     // represents a Unicode code point

float32 float64

complex64 complex128
```

The `int`, `uint`, and `uintptr` types are usually 32 bits wide on 32-bit
systems and 64 bits wide on 64-bit systems. When you need an integer value you
should use `int` unless you have a specific reason to use a sized or unsigned
integer type.

### Zero values

Variables declared without an explicit initial value are given their *zero*
value.

The zero value is:

- `0` for numeric types,
- `false` for the boolean type, and
- `""` (the empty string) for strings.

### Type conversions

The expression `T(v)` converts the value `v` to the type `T`.

Some numeric conversions:

```go
var i int = 42
var f float64 = float64(i)
var u uint = uint(f)
```

Or, put more simply:

```go
i := 42
f := float64(i)
u := uint(f)
```

Unlike in C, in Go assignment between items of different type requires an
explicit conversion.

### Type inference

When the right hand side of the declaration is typed, the new variable is of
that same type:

```go
var i int
j := i // j is an int
```

But when the right hand side contains an untyped numeric constant, the new
variable may be an `int`, `float64`, or `complex128` depending on the precision
of the constant:

```go
i := 42           // int
f := 3.142        // float64
g := 0.867 + 0.5i // complex128
```

### Constants

Constants can be character, string, boolean, or numeric values.

Constants cannot be declared using the `:=` syntax.

### Numeric Constants

Numeric constants are high-precision **values**.

An untyped constant takes the type needed by its context.

## Flow control statements: for, if, else, switch and defer

### For

Go has only one looping construct, the `for` loop.

The basic for loop has three components separated by semicolons `;`:

- **the init statement**: executed **before** the first iteration (Optional)
- **the condition expression**: evaluated **before** every iteration
- **the post statement**: executed at the end of every iteration (Optional)

```go
for i := 0; i < 10; i++ {
  //
}

for ; sum < 1000; {
  //
}
```

`while` in go is a `for` without `;`:

```go
for sum < 1000 {
  //
}
```

`forever`:

```go
for {
}
```

### If

Go's `if` statements need not be surrounded by parentheses `( )` but the braces
`{ }` are required.

```go
if x < 0 {
  // 
}
```

#### If with a short statement

Like `for`, the `if` statement can start with a short statement to execute
before the condition.

Variables declared by the statement are only in scope until the end of the `if`
and its `else` (if there is any).

```go
if v := math.Pow(x, n); v < lim {
  // 
} else {
  // 
}
```

### Switch

It runs the first case whose value is equal to the condition expression.

Go's switch is like the one in C, C++, Java, JavaScript, and PHP, except that
**Go only runs the selected case, not all the cases that follow**. In effect,
the `break` statement that is needed at the end of each case in those languages
is provided automatically in Go. Another important difference is that Go's
switch cases need not be constants, and the values involved need not be
integers.

```go
func main() {
  fmt.Println("When's Saturday?")
  today := time.Now().Weekday()
  switch time.Saturday {
  case today + 0:
    fmt.Println("Today.")
  case today + 1:
    fmt.Println("Tomorrow.")
  case today + 2:
    fmt.Println("In two days.")
  default:
    fmt.Println("Too far away.")
  }
}
```

#### Switch with no condition

Switch without a condition is the same as `switch true`.

💡 This construct can be a clean way to write long if-then-else chains.

```go
func main() {
  t := time.Now()
  switch {
  case t.Hour() < 12:
    fmt.Println("Good morning!")
  case t.Hour() < 17:
    fmt.Println("Good afternoon.")
  default:
    fmt.Println("Good evening.")
  }
}
```

### Defer

A `defer` statement defers the execution of a function until the surrounding
function returns.

The deferred call's arguments are evaluated immediately, but the function call
is not executed until the surrounding function returns.

```go
func main() {
  defer fmt.Println("world")

  fmt.Println("hello")
}
```

#### Stacking defers

Deferred function calls are pushed onto a stack. When a function returns, its
deferred calls are executed in last-in-first-out order.

## More types: structs, slices, and maps.

### Pointers

The type `*T` is a pointer to a `T` value. Its zero value is `nil`.

```go
var p *int
```

The `&` operator generates a pointer to its operand.

```go
i := 42
p = &i
```

The `*` operator denotes the pointer's underlying value.

```go
fmt.Println(*p) // read i through the pointer p
*p = 21         // set i through the pointer p
```

This is known as "dereferencing" or "indirecting".

Unlike C, Go has no pointer arithmetic.

### Structs

A `struct` is a collection of fields.

```go
type Vertex struct {
  X int
  Y int
}

v := Vertex{1, 2}
v.X = 4
fmt.Println(v.X)
```

#### Pointers to structs

Struct fields can be accessed through a struct pointer.

To access the field `X` of a struct when we have the struct pointer `p` we
could write `(*p).X`. However, that notation is cumbersome, so the language
permits us instead to write just `p.X`, without the explicit dereference.

#### Struct Literals

You can list just a subset of fields by using the `Name:` syntax.

The special prefix `&` returns a pointer to the struct value.

```go
type Vertex struct {
  X, Y int
}

var (
  v1 = Vertex{1, 2}  // has type Vertex
  v2 = Vertex{X: 1}  // Y:0 is implicit
  v3 = Vertex{}      // X:0 and Y:0
  p  = &Vertex{1, 2} // has type *Vertex
)
```

### Arrays

The type `[n]T` is an array of `n` values of type `T`.

```go
var a [10]int
primes := [6]int{2, 3, 5, 7, 11, 13}
```

declares a variable a as an array of ten integers.

An array's length is part of its type, so arrays **cannot be resized**.

### Slices

A slice is a dynamically-sized, flexible view into the elements of an array. In
practice, slices are much more common than arrays.

The type `[]T` is a slice with elements of type `T`.

A slice is formed by specifying two indices, a low and high bound, separated by
a colon:

```go
a[low : high]
```

This selects a half-open range which includes the first element, but excludes
the last one.

The following expression creates a slice which includes elements 1 through 3 of
a:

```go
a[1:4]
```

#### Slices are like references to arrays

A slice does not store any data, it just describes a section of an underlying
array.

Changing the elements of a slice modifies the corresponding elements of its
underlying array.

Other slices that share the same underlying array will see those changes.

```go
names := [4]string{
  "John",
  "Paul",
  "George",
  "Ringo",
}
fmt.Println(names)

a := names[0:2]
b := names[1:3]
fmt.Println(a, b)

b[0] = "XXX"
```

#### Slice literals

A slice literal is like an array literal without the length.

This is an array literal:

```go
[3]bool{true, true, false}
```

And this creates the same array as above, then builds a slice that references
it:

```go
[]bool{true, true, false}
```

#### Slice defaults

When slicing, you may omit the high or low bounds to use their defaults instead.

The default is zero for the low bound and the length of the slice for the high
bound.

For the array

```go
var a [10]int
```

these slice expressions are equivalent:

```go
a[0:10]
a[:10]
a[0:]
a[:]
```

#### Slice length and capacity

The length of a slice is the number of elements it contains.

The capacity of a slice is the number of elements in the underlying array,
counting from the first element in the slice.

The length and capacity of a slice `s` can be obtained using the expressions
`len(s)` and `cap(s)`.

You can extend a slice's length by re-slicing it, provided it has sufficient
capacity.

#### Nil slices

The zero value of a slice is `nil`.

A nil slice has a length and capacity of 0 and **has no underlying array**.

#### Creating a slice with make

Slices can be created with the built-in `make` function; this is how you create
dynamically-sized arrays.

The `make` function allocates a zeroed array and returns a slice that refers to
that array:

```go
a := make([]int, 5)  // len(a)=5
```

To specify a capacity, pass a third argument to make:

```go
b := make([]int, 0, 5) // len(b)=0, cap(b)=5

b = b[:cap(b)] // len(b)=5, cap(b)=5
b = b[1:]      // len(b)=4, cap(b)=4
```

#### Slices of slices

Slices can contain any type, including other slices.

#### Appending to a slice

Go provides a built-in `append` function.

```go
func append(s []T, vs ...T) []T
```

The first parameter `s` of `append` is a slice of type `T`, and the rest are
`T` values to append to the slice.

The resulting value of `append` is a slice containing all the elements of the
original slice plus the provided values.

If the backing array of `s` is too small to fit all the given values a bigger
array will be allocated. The returned slice will point to the newly allocated
array.

### Range

The `range` form of the `for` loop iterates over a `slice` or `map`.

When ranging over a slice, two values are returned for each iteration. The
first is the index, and the second is a copy of the element at that index.

```go
var pow = []int{1, 2, 4, 8, 16, 32, 64, 128}

for i, v := range pow {
  fmt.Printf("2**%d = %d\n", i, v)
}
```

You can skip the index or value by assigning to `_`.

```go
for i, _ := range pow
for _, value := range pow
```

If you only want the index, you can omit the second variable.

```go
for i := range pow
```

### Maps

The zero value of a map is `nil`. A `nil` map has no keys, nor can keys be
added.

The `make` function returns a map of the given type, initialized and ready for
use.

```go
type Vertex struct {
  Lat, Long float64
}

var m map[string]Vertex

m = make(map[string]Vertex)
m["Bell Labs"] = Vertex{
  40.68433, -74.39967,
}
```

#### Map literals

Map literals are like struct literals, but the keys are required.

```go

type Vertex struct {
  Lat, Long float64
}

var m = map[string]Vertex{
  "Bell Labs": Vertex{
    40.68433, -74.39967,
  },
  "Google": Vertex{
    37.42202, -122.08408,
  },
}


var m = map[string]Vertex{
  "Bell Labs": {40.68433, -74.39967},
  "Google":    {37.42202, -122.08408},
}
```

If the top-level type is just a type name, you can omit it from the elements of
the literal.

#### Mutating Maps

Insert or update an element in map `m`:

```go
m[key] = elem
```

Retrieve an element:

```go
elem = m[key]
```

Delete an element:

```go
delete(m, key)
```

Test that a key is present with a two-value assignment:

```go
elem, ok := m[key]
```

If key is in `m`, `ok` is `true`. If not, `ok` is `false`.

If key is not in the map, then `elem` is the zero value for the map's element
type.

### Function values

Functions are values too. They can be passed around just like other values.

Function values may be used as function arguments and return values.

#### Function closures

Go functions may be closures. A closure is a function value that references
variables from outside its body. The function may access and assign to the
referenced variables; in this sense the function is "bound" to the variables.

```go
func adder() func(int) int {
  sum := 0
  return func(x int) int {
    sum += x
    return sum
  }
}

func main() {
  pos, neg := adder(), adder()
  for i := 0; i < 10; i++ {
    fmt.Println(
      pos(i),
      neg(-2*i),
    )
  }
}
```

The `adder` function returns a closure. Each closure is bound to its own `sum`
variable.
