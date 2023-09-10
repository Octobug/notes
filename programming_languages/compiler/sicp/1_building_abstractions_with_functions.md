# Chapter 1: Building Abstractions with Functions

- [Chapter 1: Building Abstractions with Functions](#chapter-1-building-abstractions-with-functions)
  - [Lab 0: Getting Started](#lab-0-getting-started)
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
  - [Homework 1: Functions, Control](#homework-1-functions-control)
  - [1.3 Defining New Functions](#13-defining-new-functions)
    - [1.3.1 Environments](#131-environments)
    - [1.3.2 Calling User-Defined Functions](#132-calling-user-defined-functions)
    - [1.3.3 Example: Calling a User-Defined Function](#133-example-calling-a-user-defined-function)
    - [1.3.4 Local Names](#134-local-names)
    - [1.3.5 Choosing Names](#135-choosing-names)
    - [1.3.6 Functions as Abstraction](#136-functions-as-abstraction)
    - [1.3.7 Operators](#137-operators)
  - [1.4 Designing Functions](#14-designing-functions)
    - [1.4.1 Documentation](#141-documentation)
    - [1.4.2 Default Argument Values](#142-default-argument-values)
  - [1.5 Control](#15-control)
  - [Lab 1: Functions, Control](#lab-1-functions-control)
  - [Discussion 1: Control, Environment Diagrams](#discussion-1-control-environment-diagrams)
  - [1.6](#16)
  - [Homework 2: Higher Order Functions and Lambdas](#homework-2-higher-order-functions-and-lambdas)

## Lab 0: Getting Started

> <https://inst.eecs.berkeley.edu/~cs61a/sp23/lab/lab00/>

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

## Homework 1: Functions, Control

> <https://inst.eecs.berkeley.edu/~cs61a/sp23/hw/hw01/>

## 1.3 Defining New Functions

> <https://www.composingprograms.com/pages/13-defining-new-functions.html>

Function definitions consist of a `def` **statement** that indicates a `<name>`
and a comma-separated list of named `<formal parameters>`, then a `return`
statement, called the function body, that specifies the `<return expression>`
of the function, which is an expression to be evaluated whenever the function
is applied:

```py
def <name>(<formal parameters>):
    return <return expression>
```

### 1.3.1 Environments

- **Function Signatures**: A description of the formal parameters of a function
  is called the function's signature.

### 1.3.2 Calling User-Defined Functions

As with any call expression, the interpreter evaluates the operator and operand
expressions, and then applies the named function to the resulting arguments.

Applying a user-defined function introduces a second *local* frame, which is
only accessible to that function. To apply a user-defined function to some
arguments:

1. Bind the arguments to the names of the function's formal parameters in a new
   *local* frame.
2. Execute the body of the function in the environment that starts with this
   frame.

The environment in which the body is evaluated consists of two frames:

1. The local frame that contains formal parameter bindings.
2. The global frame that contains everything else.

Each instance of a function application has its own independent local frame.

**Name Evaluation**. A name evaluates to the value bound to that name in the
earliest frame of the current environment in which that name is found.

### 1.3.3 Example: Calling a User-Defined Function

### 1.3.4 Local Names

The parameter names of a function must remain local to the body of the function.

### 1.3.5 Choosing Names

### 1.3.6 Functions as Abstraction

- **Aspects of a functional abstraction**: It is often useful to consider its
  three core attributes:
  - The domain of a function is the set of arguments it can take.
  - The range of a function is the set of values it can return.
  - The intent of a function is the relationship it computes between inputs and
    output (as well as any side effects it might generate).

### 1.3.7 Operators

Python expressions with infix operators each have their own evaluation
procedures, but you can often think of them as short-hand for call expressions.

When you see

```py
>>> 2 + 3
5
```

simply consider it to be short-hand for

```txt
>>> add(2, 3)
5
```

## 1.4 Designing Functions

> <https://www.composingprograms.com/pages/14-designing-functions.html>

Fundamentally, the qualities of good functions all reinforce the idea that
functions are abstractions.

- Each function should have exactly one job. That job should be identifiable
  with a short name and characterizable in a single line of text.
- Don't Repeat Yourself is a central tenet of software engineering. The
  so-called DRY principle states that multiple fragments of code should not
  describe redundant logic.
- Functions should be defined generally. Squaring is not in the Python Library
  precisely because it is a special case of the pow function, which raises
  numbers to arbitrary powers.

### 1.4.1 Documentation

A function definition will often include documentation describing the function,
called a `docstring`.

```py
def pressure(v, t, n):
    """Compute the pressure in pascals of an ideal gas.
    Applies the ideal gas law: http://en.wikipedia.org/wiki/Ideal_gas_law
    v -- volume of gas, in cubic meters
    t -- absolute temperature in degrees kelvin
    n -- particles of gas
    """
    k = 1.38e-23  # Boltzmann's constant
    return n * k * t / v
```

When you call help with the name of a function as an argument, you see its
docstring (type q to quit Python help).

```py
>>> help(pressure)
```

### 1.4.2 Default Argument Values

```py
def pressure(v, t, n=6.022e23):
    """Compute the pressure in pascals of an ideal gas.
    v -- volume of gas, in cubic meters
    t -- absolute temperature in degrees kelvin
    n -- particles of gas (default: one mole)
    """
    k = 1.38e-23  # Boltzmann's constant
    return n * k * t / v
```

## 1.5 Control

> <https://www.composingprograms.com/pages/15-control.html>

## Lab 1: Functions, Control

> <https://inst.eecs.berkeley.edu/~cs61a/sp23/lab/lab01/>

## Discussion 1: Control, Environment Diagrams

> <https://inst.eecs.berkeley.edu/~cs61a/sp23/disc/disc01/>

## 1.6

## Homework 2: Higher Order Functions and Lambdas

> <https://inst.eecs.berkeley.edu/~cs61a/sp23/hw/hw02/>
