# Chapter 1: Building Abstractions with Functions

- [Chapter 1: Building Abstractions with Functions](#chapter-1-building-abstractions-with-functions)
  - [1.1 Getting Started](#11-getting-started)
    - [1.1.1 Programming in Python](#111-programming-in-python)
    - [1.1.2 Installing Python 3](#112-installing-python-3)
    - [1.1.3 Interactive Sessions](#113-interactive-sessions)
    - [1.1.4 First Example](#114-first-example)
    - [1.1.5 Errors](#115-errors)
  - [1.2 Elements of Programming](#12-elements-of-programming)
    - [1.2.1 Expressions](#121-expressions)
    - [1.2.2 Call Expressions](#122-call-expressions)
    - [1.2.3 Importing Library Functions](#123-importing-library-functions)
    - [1.2.4 Names and the Environment](#124-names-and-the-environment)
    - [1.2.5 Evaluating Nested Expressions](#125-evaluating-nested-expressions)
    - [1.2.4 The Non-Pure Print Function](#124-the-non-pure-print-function)
  - [1.3 Defining New Functions](#13-defining-new-functions)

## 1.1 Getting Started

> <https://www.composingprograms.com/pages/11-getting-started.html>

### 1.1.1 Programming in Python

> A language isn't something you learn so much as something you join.
> --Arika Okrent

### 1.1.2 Installing Python 3

### 1.1.3 Interactive Sessions

### 1.1.4 First Example

Python code consists of

- **expressions**: typically describe computations.
- **statements**: typically describe actions.

Broadly, computer programs consist of instructions to either

1. Compute some value
2. Carry out some action

```py
from urllib.request import urlopen

shakespeare = urlopen('https://www.composingprograms.com/shakespeare.txt')
words = set(shakespeare.read().decode().split())
{w for w in words if len(w) == 6 and w[::-1] in words}
```

- **functions**: encapsulate logic that manipulates data.
- **objects**: An object seamlessly bundles together data and the logic that
  manipulates that data, in a way that manages the complexity of both.
- **interpreters**: evaluating compound expressions requires a precise
  procedure that interprets code in a predictable way. A program that
  implements such a procedure, evaluating compound expressions, is called an
  interpreter.

### 1.1.5 Errors

> The fundamental equation of computers is:
>
> computer = powerful + stupid
>
> --Francisco Cai and Nick Parlante, Stanford CS101

Some guiding principles of **debugging** are:

1. **Test incrementally**: Every well-written program is composed of small,
   modular components that can be tested individually.
2. **Isolate errors**: An error in the output of a statement can typically be
   attributed to a particular modular component.
3. **Check your assumptions**: Interpreters do carry out your instructions to
   the letter -- no more and no less.
4. **Consult others**: A lot of valuable programming knowledge is shared in the
   process of group problem solving.

## 1.2 Elements of Programming

> <https://www.composingprograms.com/pages/12-elements-of-programming.html>

Every powerful language has three such mechanisms:

1. **primitive expressions and statements**, which represent the simplest
   building blocks that the language provides,
2. **means of combination**, by which compound elements are built from simpler
   ones, and
3. **means of abstraction**, by which compound elements can be named and
   manipulated as units.

### 1.2.1 Expressions

- Number: is one kind of primitive expression.
- Infix notation: is what mathematical expressions use, where the operator
  appears in between the operands.

### 1.2.2 Call Expressions

- **call expression**: applies a function to some arguments.

A call expression has **subexpressions**: the operator is an expression that
precedes parentheses, which enclose a comma-delimited list of
**operand expressions**.

`max(1, 2)`

```txt
  max       (  1   ,   2  )
--------    ------- -------
Operator    Operand Operand
```

Function notation has three principal advantages over the mathematical
convention of infix notation:

1. functions may take an arbitrary number of arguments;
2. function notation extends in a straightforward way to nested expressions,
   where the elements are themselves compound expressions.
3. mathematical notation has a great variety of forms: multiplication appears
   between terms, exponents appear as superscripts, division as a horizontal
   bar, and a square root as a roof with slanted siding. However, all of this
   complexity can be unified via the notation of call expressions.

### 1.2.3 Importing Library Functions

the `operator` module provides access to functions corresponding to infix
operators:

```py
>>> from operator import add, sub, mul
>>> add(14, 28)
42
>>> sub(100, mul(7, add(8, 4)))
16
```

### 1.2.4 Names and the Environment

### 1.2.5 Evaluating Nested Expressions

In evaluating nested call expressions, the interpreter is itself following a
procedure, Python will do the following:

1. Evaluate the operator and operand subexpressions, then
2. Apply the function that is the value of the operator subexpression to the
   arguments that are the values of the operand subexpressions.

The evaluation procedure is recursive in nature; that is, it includes, as one
of its steps, the need to invoke the rule itself.

This illustration is called an expression tree. In computer science, trees
conventionally grow from the top down. The objects at each point in a tree are
called nodes; in this case, they are expressions paired with their values.

### 1.2.4 The Non-Pure Print Function

- **Pure functions**: have some input (their arguments) and return some output
  (the result of applying them).
  - Pure functions have the property that applying them has no effects beyond
    returning a value.
  - Moreover, a pure function must always return the same value when called
    twice with the same arguments.
- **Non-pure functions**: In addition to returning a value, applying a non-pure
  function can generate side effects, which make some change to the state of
  the interpreter or computer.
  - A common side effect is to generate additional output beyond the return
    value, using the `print` function.

Pure functions are restricted in that they cannot have side effects or change
behavior over time. Imposing these restrictions yields substantial benefits.

1. pure functions can be composed more reliably into compound call expressions.
2. pure functions tend to be simpler to test.
3. pure functions are essential for writing concurrent programs.

## 1.3 Defining New Functions

> <https://www.composingprograms.com/pages/13-defining-new-functions.html>
