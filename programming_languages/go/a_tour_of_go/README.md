# A Tour of Go

> <https://go.dev/tour/list>

- [A Tour of Go](#a-tour-of-go)
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
  - [Methods and interfaces](#methods-and-interfaces)
  - [Generics](#generics)
  - [Concurrency](#concurrency)

## Basics

### Packages, variables, and functions.

#### Packages

Programs start running package `main`.

#### Imports

It is good style to use the factored import statement.

#### Exported names

A name is exported if it begins with a capital letter.

#### Functions

A function can take zero or more arguments.

```go
func add(x int, y int) int {}
```

The type can be omitted from all but the last as:

```go
func add(x, y int) int {}
```

#### Multiple results

```go
func swap(x, y string) (string, string) {
    return y, x
}
```

#### Named return values

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

#### Variables

The `var` statement declares a list of variables; as in function argument lists,
the type is last.

A `var` statement can be at package or function level.

```go
var c, python, java bool
```

#### Variables with initializers

If an initializer is present, the type can be omitted; the variable will take
the type of the initializer.

```gp
var i, j int = 1, 2
```

#### Short variable declarations

```go
func main() {
    k := 3
}
```

Inside a function, the `:=` short assignment statement can be used.

Outside a function, every statement begins with a keyword (`var`, `func`, and
so on) and so the `:=` construct is not available.

#### Basic types

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

#### Zero values

Variables declared without an explicit initial value are given their *zero*
value.

The zero value is:

- `0` for numeric types,
- `false` for the boolean type, and
- `""` (the empty string) for strings.

#### Type conversions

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

#### Type inference

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

#### Constants

Constants can be character, string, boolean, or numeric values.

Constants cannot be declared using the `:=` syntax.

#### Numeric Constants

Numeric constants are high-precision **values**.

An untyped constant takes the type needed by its context.

### Flow control statements: for, if, else, switch and defer

> <https://go.dev/tour/flowcontrol/1>
>
>>>>> progress

## Methods and interfaces

## Generics

## Concurrency
