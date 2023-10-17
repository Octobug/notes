# Chapter 2: Building Abstractions with Data

- [Chapter 2: Building Abstractions with Data](#chapter-2-building-abstractions-with-data)
  - [2.1 Introduction](#21-introduction)
    - [2.1.1 Native Data Types](#211-native-data-types)
  - [2.2 Data Abstraction](#22-data-abstraction)
    - [2.2.1 Example: Rational Numbers](#221-example-rational-numbers)
    - [2.2.2 Pairs](#222-pairs)
    - [2.2.3 Abstraction Barriers](#223-abstraction-barriers)
    - [2.2.4 The Properties of Data](#224-the-properties-of-data)
  - [2.3 Sequences](#23-sequences)
    - [2.3.1 Lists](#231-lists)
    - [2.3.2 Sequence Iteration](#232-sequence-iteration)
    - [2.3.3 Sequence Processing](#233-sequence-processing)
      - [List Comprehensions](#list-comprehensions)
      - [Aggregation](#aggregation)
      - [Higher-Order Functions](#higher-order-functions)
      - [Conventional Names](#conventional-names)
    - [2.3.4 Sequence Abstraction](#234-sequence-abstraction)
    - [2.3.5 Strings](#235-strings)
    - [2.3.6 Trees](#236-trees)
  - [Lab 4: Recursion, Tree Recursion, Python Lists](#lab-4-recursion-tree-recursion-python-lists)

## 2.1 Introduction

> <https://www.composingprograms.com/pages/21-introduction.html>

### 2.1.1 Native Data Types

```py
>>> type(2)
<class 'int'>
```

***Native*** data types have the following properties:

- There are expressions that evaluate to values of native types, called
  ***literals***.
- There are built-in functions and operators to manipulate values of native
  types.

## 2.2 Data Abstraction

> <https://www.composingprograms.com/pages/22-data-abstraction.html>

The general technique of isolating the parts of a program that deal with how
data are represented from the parts that deal with how data are manipulated is
a powerful design methodology called **data abstraction**.

We can make an abstraction that separates the way the function is used from the
details of how the function is implemented. Analogously, data abstraction
isolates how a compound data value is used from the details of how it is
constructed.

### 2.2.1 Example: Rational Numbers

A rational number such as 1/3 or 17/29 is typically written as:

```pseudo
<numerator>/<denominator>
```

```py
def add_rationals(x, y):
  nx, dx = numer(x), denom(x)
  ny, dy = numer(y), denom(y)
  return rational(nx * dy + ny * dx, dx * dy)

def mul_rationals(x, y):
  return rational(numer(x) * numer(y), denom(x) * denom(y))

def print_rational(x):
  print(numer(x), '/', denom(x))

def rationals_are_equal(x, y):
  return numer(x) * denom(y) == numer(y) * denom(x)
```

### 2.2.2 Pairs

Any way of bundling two values together into one can be considered a pair in
Python.

```py
from fractions import gcd

def rational(n, d):
  g = gcd(n, d)
  return (n//g, d//g)

# def rational(n, d):
#   return [n, d]

def numer(x):
  return x[0]

def denom(x):
  return x[1]
```

### 2.2.3 Abstraction Barriers

An abstraction barrier violation occurs whenever a part of the program that can
use a higher level function instead uses a function in a lower level.

Abstraction barriers make programs easier to maintain and to modify. The fewer
functions that depend on a particular representation, the fewer changes are
required when one wants to change that representation.

### 2.2.4 The Properties of Data

## 2.3 Sequences

> <https://www.composingprograms.com/pages/23-sequences.html>

A sequence is an **ordered** collection of values. Sequences all share common
behavior. In particular,

- **Length**. A sequence has a finite length. An empty sequence has length `0`.
- **Element selection**. A sequence has an element corresponding to any
  non-negative integer index less than its length, starting at `0` for the
  first element.

### 2.3.1 Lists

### 2.3.2 Sequence Iteration

### 2.3.3 Sequence Processing

#### List Comprehensions

#### Aggregation

- `sum`
- `min`
- `max`
- ...

#### Higher-Order Functions

```py
def apply_to_all(map_fn, s):
  return [map_fn(x) for x in s]

def keep_if(filter_fn, s):
  return [x for x in s if filter_fn(x)]

def reduce(reduce_fn, s, initial):
  reduced = initial
  for x in s:
      reduced = reduce_fn(reduced, x)
  return reduced
```

#### Conventional Names

- `map`: apply_to_all
- `filter`: keep_if
- `reduce`

### 2.3.4 Sequence Abstraction

- Membership
  - `in`
  - `not in`
- Slicing

### 2.3.5 Strings

### 2.3.6 Trees

>>>>> progress

## Lab 4: Recursion, Tree Recursion, Python Lists

- [ ] [Lab 4: Recursion, Tree Recursion, Python Lists](https://inst.eecs.berkeley.edu/~cs61a/sp23/lab/lab04/)
