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
    - [1.5.1 Statements](#151-statements)
    - [1.5.2 Compound Statements](#152-compound-statements)
    - [1.5.3 Defining Functions II: Local Assignment](#153-defining-functions-ii-local-assignment)
    - [1.5.4 Conditional Statements](#154-conditional-statements)
    - [1.5.5 Iteration](#155-iteration)
    - [1.5.6 Testing](#156-testing)
  - [Lab 1: Functions, Control](#lab-1-functions-control)
  - [Discussion 1: Control, Environment Diagrams](#discussion-1-control-environment-diagrams)
  - [1.6 Higher-Order Functions](#16-higher-order-functions)
    - [1.6.1 Functions as Arguments](#161-functions-as-arguments)
    - [1.6.2 Functions as General Methods](#162-functions-as-general-methods)
    - [1.6.3 Defining Functions III: Nested Definitions](#163-defining-functions-iii-nested-definitions)
    - [1.6.4 Functions as Returned Values](#164-functions-as-returned-values)
    - [1.6.5 Example: Newton's Method](#165-example-newtons-method)
    - [1.6.6 Currying](#166-currying)
    - [1.6.7 Lambda Expressions](#167-lambda-expressions)
    - [1.6.8 Abstractions and First-Class Functions](#168-abstractions-and-first-class-functions)
    - [1.6.9 Function Decorators](#169-function-decorators)
  - [Homework 2: Higher Order Functions and Lambdas](#homework-2-higher-order-functions-and-lambdas)
  - [Lab 2: Higher-Order Functions, Lambda Expressions](#lab-2-higher-order-functions-lambda-expressions)
  - [Project 1: The Game of Hog](#project-1-the-game-of-hog)
  - [Discussion 2: Environment Diagrams, Higher-Order Functions](#discussion-2-environment-diagrams-higher-order-functions)
  - [Lab 3: Midterm Review](#lab-3-midterm-review)
  - [1.7 Recursive Functions](#17-recursive-functions)
  - [Discussion 3: Recursion](#discussion-3-recursion)
  - [Homework 3: Recursion, Tree Recursion](#homework-3-recursion-tree-recursion)

## Lab 0: Getting Started

- [x] [Lab 0: Getting Started](https://inst.eecs.berkeley.edu/~cs61a/sp23/lab/lab00/)

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

- [x] [Homework 1: Functions, Control](https://inst.eecs.berkeley.edu/~cs61a/sp23/hw/hw01/)

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

**Statements** differ fundamentally from the expressions. They have no value.
Instead of computing something, executing a control statement determines what
the interpreter should do next.

### 1.5.1 Statements

Rather than being evaluated, statements are executed. Each statement describes
some change to the interpreter state, and executing a statement applies that
change.

Expressions can also be executed as statements, in which case they are
evaluated, but their value is discarded. Executing a pure function has no
effect, but executing a non-pure function can cause effects as a consequence of
function application.

```py
def square(x):
    mul(x, x) # Watch out! This call doesn't return a value.
```

An expression by itself is a valid statement.

Statements govern the relationship among different expressions in a program and
what happens to their results.

### 1.5.2 Compound Statements

A compound statement is so called because it is composed of other statements
(simple and compound). Compound statements typically span multiple lines and
start with a one-line header ending in a colon, which identifies the type of
statement. Together, a header and an indented suite of statements is called a
**clause**. A compound statement consists of one or more clauses:

```txt
<header>:
    <statement>
    <statement>
    ...
<separating header>:
    <statement>
    <statement>
    ...
...
```

A `def` statement is a compound statement. The suite that follows the `def`
header defines the function body.

- To execute a sequence of statements, execute the first statement. If that
  statement does not redirect control, then proceed to execute the rest of the
  sequence of statements, if any remain.

This definition exposes the essential structure of a recursively defined
sequence: a sequence can be decomposed into its first element and the rest of
its elements. The "rest" of a sequence of statements is itself a sequence of
statements! Thus, we can recursively apply this execution rule.

### 1.5.3 Defining Functions II: Local Assignment

### 1.5.4 Conditional Statements

**Boolean contexts**: The expressions inside the header statements of
conditional blocks are said to be in boolean contexts: their truth values
matter to control flow, but otherwise their values are not assigned or
returned.

### 1.5.5 Iteration

### 1.5.6 Testing

**Assertions**: Programmers use `assert` statements to verify expectations,
such as the output of a function being tested. An `assert` statement has an
expression in a boolean context, followed by a quoted line of text that will be
displayed if the expression evaluates to a false value.

```py
assert fib(8) == 13, 'The 8th Fibonacci number should be 13'
```

💡 It is generally **good practice** to release code with assertion statements
left in.

**Doctests**: Python provides a convenient method for placing **simple** tests
directly in the docstring of a function.

```py
def sum_naturals(n):
    """Return the sum of the first n natural numbers.

    >>> sum_naturals(10)
    55
    >>> sum_naturals(100)
    5050
    """
    total, k = 0, 1
    while k <= n:
        total, k = total + k, k + 1
    return total
```

```sh
python3 -m doctest PYTHON_SOURCE_FILE
```

## Lab 1: Functions, Control

- [x] [Lab 1: Functions, Control](https://inst.eecs.berkeley.edu/~cs61a/sp23/lab/lab01/)

## Discussion 1: Control, Environment Diagrams

- [Discussion 1: Control, Environment Diagrams](https://inst.eecs.berkeley.edu/~cs61a/sp23/disc/disc01/)

## 1.6 Higher-Order Functions

> <https://www.composingprograms.com/pages/16-higher-order-functions.html>

To express certain general patterns as named concepts, we will need to
construct functions that can accept other functions as arguments or return
functions as values.

Functions that manipulate functions are called **higher-order** functions.

### 1.6.1 Functions as Arguments

### 1.6.2 Functions as General Methods

An iterative improvement algorithm begins with a `guess` of a solution to an
equation. It repeatedly applies an `update` function to improve that guess, and
applies a `close` comparison to check whether the current `guess` is "close
enough" to be considered correct.

```py
def improve(update, close, guess=1):
    while not close(guess):
        guess = update(guess)
    return guess
```

This `improve` function is a general expression of repetitive refinement. It
doesn't specify what problem is being solved: those details are left to the
`update` and `close` functions passed in as arguments.

Two related big ideas in computer science:

1. Naming and functions allow us to abstract away a vast amount of complexity.
2. Second, it is only by virtue of the fact that we have an extremely general
   evaluation procedure for the Python language that small components can be
   composed into complex processes.

### 1.6.3 Defining Functions III: Nested Definitions

**Lexical scope**: Locally defined functions also have access to the name
bindings in the scope in which they are defined. This discipline of sharing
names among nested definitions is called **lexical scoping**. Critically, the
inner functions have access to the names in the environment where they are
defined (not where they are called).

We require two extensions to our environment model to enable lexical scoping.

1. Each user-defined function has a parent environment: the environment in
   which it was defined.
2. When a user-defined function is called, its local frame extends its parent
   environment.

The parent of a function value is the first frame of the environment in which
that function was defined.

**Extended Environments**: An environment can consist of an arbitrarily long
chain of frames, which always concludes with the global frame. By calling
functions that were defined within other functions, via nested `def`
statements, we can create longer chains.

Hence, we realize two key advantages of lexical scoping in Python.

- The names of a local function do not interfere with names external to the
  function in which it is defined, because the local function name will be
  bound in the current local environment in which it was defined, rather than
  the global environment.
- A local function can access the environment of the enclosing function,
  because the body of the local function is evaluated in an environment that
  extends the evaluation environment in which it was defined.

Because they "enclose" information in this way, locally defined functions are
often called **closures**.

### 1.6.4 Functions as Returned Values

### 1.6.5 Example: Newton's Method

```py
def approx_eq(x, y, tolerance=1e-15):
    return abs(x - y) < tolerance

def improve(update, close, guess=1):
    while not close(guess):
        guess = update(guess)
    return guess

def newton_update(f, df):
    def update(x):
        return x - f(x) / df(x)
    return update

def find_zero(f, df):
    def near_zero(x):
        return approx_eq(f(x), 0)
    return improve(newton_update(f, df), near_zero)

def square_root_newton(a):
    def f(x):
        return x * x - a
    def df(x):
        return 2 * x
    return find_zero(f, df)

def power(x, n):
    """Return x * x * x * ... * x for x repeated n times."""
    product, k = 1, 0
    while k < n:
        product, k = product * x, k + 1
    return product

def nth_root_of_a(n, a):
    def f(x):
        return power(x, n) - a
    def df(x):
        return n * power(x, n-1)
    return find_zero(f, df)
```

### 1.6.6 Currying

We can use higher-order functions to convert a function that takes multiple
arguments into a chain of functions that each take a single argument. More
specifically, given a function `f(x, y)`, we can define a function `g` such
that `g(x)(y)` is equivalent to `f(x, y)`. Here, `g` is a higher-order function
that takes in a single argument `x` and returns another function that takes in
a single argument `y`. This transformation is called ***currying***.

A curried version of the `pow` function:

```py
def curried_pow(x):
    def h(y):
        return pow(x, y)
    return h
```

Automate currying and the inverse uncurrying transformation:

```py
def curry2(f):
    """Return a curried version of the given two-argument function."""
    def g(x):
        def h(y):
            return f(x, y)
        return h
    return g

def uncurry2(g):
    """Return a two-argument version of the given curried function."""
    def f(x, y):
        return g(x)(y)
    return f
```

### 1.6.7 Lambda Expressions

A lambda expression evaluates to a function that has a single return expression
as its body. Assignment and control statements are not allowed. And this
function has no name.

```py
def compose1(f, g):
    return lambda x: f(g(x))
```

We can understand the structure of a lambda expression by constructing a
corresponding English sentence:

```txt
     lambda            x            :          f(g(x))
"A function that    takes x    and returns     f(g(x))"
```

The result of a lambda expression is called a lambda function. It has no
intrinsic name (and so Python prints `<lambda>` for the name), but otherwise it
behaves like any other function.

The term *lambda* is a historical accident resulting from the incompatibility
of written mathematical notation and the constraints of early type-setting
systems.

### 1.6.8 Abstractions and First-Class Functions

In general, programming languages impose restrictions on the ways in which
computational elements can be manipulated. Elements with the fewest
restrictions are said to have first-class status. Some of the "rights and
privileges" of first-class elements are:

1. They may be bound to names.
2. They may be passed as arguments to functions.
3. They may be returned as the results of functions.
4. They may be included in data structures.

### 1.6.9 Function Decorators

Python provides special syntax to apply higher-order functions as part of
executing a `def` statement, called a **decorator**. Perhaps the most common
example is a trace.

```py
def trace(fn):
    def wrapped(x):
        print('-> ', fn, '(', x, ')')
        return fn(x)
    return wrapped

@trace
def triple(x):
    return 3 * x
```

The `def` statement for triple has an annotation, `@trace`, which affects the
execution rule for def. As usual, the function `triple` is created. However,
the name `triple` is not bound to this function. Instead, the name `triple` is
bound to the returned function value of calling trace on the newly defined
`triple` function. In code, this decorator is equivalent to:

```py
def triple(x):
    return 3 * x

triple = trace(triple)
```

## Homework 2: Higher Order Functions and Lambdas

- [x] [Homework 2: Higher Order Functions and Lambdas](https://inst.eecs.berkeley.edu/~cs61a/sp23/hw/hw02/)

## Lab 2: Higher-Order Functions, Lambda Expressions

- [x] [Lab 2: Higher-Order Functions, Lambda Expressions](https://inst.eecs.berkeley.edu/~cs61a/sp23/lab/lab02/)

## Project 1: The Game of Hog

- [x] [Project 1: The Game of Hog](https://inst.eecs.berkeley.edu/~cs61a/sp23/proj/hog/)

## Discussion 2: Environment Diagrams, Higher-Order Functions

- [Discussion 2: Environment Diagrams, Higher-Order Functions](https://inst.eecs.berkeley.edu/~cs61a/sp23/disc/disc02/)

## Lab 3: Midterm Review

- [ ] [Lab 3: Midterm Review](https://inst.eecs.berkeley.edu/~cs61a/sp23/lab/lab03/)

## 1.7 Recursive Functions

> <https://www.composingprograms.com/pages/17-recursive-functions.html>

## Discussion 3: Recursion

- [Discussion 3: Recursion](https://inst.eecs.berkeley.edu/~cs61a/sp23/disc/disc03/)

## Homework 3: Recursion, Tree Recursion

- [ ] [Homework 3: Recursion, Tree Recursion](https://inst.eecs.berkeley.edu/~cs61a/sp23/hw/hw03/)
