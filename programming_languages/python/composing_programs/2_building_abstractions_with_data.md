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
      - [Partition trees](#partition-trees)
    - [2.3.7 Linked Lists](#237-linked-lists)
      - [Recursive Construction](#recursive-construction)
  - [Lab 3: Recursion, Tree Recursion, Python Lists](#lab-3-recursion-tree-recursion-python-lists)
  - [Discussion 4: Tree Recursion, Python Lists](#discussion-4-tree-recursion-python-lists)
  - [Project 2: CS 61A Autocorrected Typing Software](#project-2-cs-61a-autocorrected-typing-software)
  - [Lab 4: Tree Recursion, Data Abstraction](#lab-4-tree-recursion-data-abstraction)
  - [Discussion 5: Trees](#discussion-5-trees)
  - [2.4 Mutable Data](#24-mutable-data)
    - [2.4.1 The Object Metaphor](#241-the-object-metaphor)
    - [2.4.2 Sequence Objects](#242-sequence-objects)
    - [2.4.3 Dictionaries](#243-dictionaries)
    - [2.4.4 Local State](#244-local-state)
    - [2.4.5 The Benefits of Non-Local Assignment](#245-the-benefits-of-non-local-assignment)
    - [2.4.6 The Cost of Non-Local Assignment](#246-the-cost-of-non-local-assignment)
    - [2.4.7 Implementing Lists and Dictionaries](#247-implementing-lists-and-dictionaries)
    - [2.4.8 Dispatch Dictionaries](#248-dispatch-dictionaries)
    - [2.4.9 Propagating Constraints](#249-propagating-constraints)
  - [Homework 4: Trees, Data Abstraction](#homework-4-trees-data-abstraction)
  - [2.5 Object-Oriented Programming](#25-object-oriented-programming)
    - [2.5.1 Objects and Classes](#251-objects-and-classes)
    - [2.5.2 Defining Classes](#252-defining-classes)
    - [2.5.3 Message Passing and Dot Expressions](#253-message-passing-and-dot-expressions)
    - [2.5.4 Class Attributes](#254-class-attributes)
    - [2.5.5 Inheritance](#255-inheritance)
    - [2.5.6 Using Inheritance](#256-using-inheritance)
    - [2.5.7 Multiple Inheritance](#257-multiple-inheritance)
    - [2.5.8 The Role of Objects](#258-the-role-of-objects)
  - [Homework 5: Generators](#homework-5-generators)
  - [Lab 6: OOP](#lab-6-oop)
  - [Project 3: Ants Vs. SomeBees](#project-3-ants-vs-somebees)
  - [Discussion 7: OOP](#discussion-7-oop)
  - [2.6 Implementing Classes and Objects](#26-implementing-classes-and-objects)

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

```py
def tree(root_label, branches=[]):
  for branch in branches:
    assert is_tree(branch), 'branches must be trees'
  return [root_label] + list(branches)

def label(tree):
  return tree[0]

def branches(tree):
  return tree[1:]

def is_tree(tree):
  if type(tree) != list or len(tree) < 1:
    return False
  for branch in branches(tree):
    if not is_tree(branch):
      return False
  return True

def is_leaf(tree):
  return not branches(tree)

def count_leaves(tree):
  if is_leaf(tree):
    return 1
  else:
    branch_counts = [count_leaves(b) for b in branches(tree)]
    return sum(branch_counts)
```

#### Partition trees

Trees can also be used to represent the partitions of an integer. A partition
tree for `n` using parts up to size `m` is a binary (two branch) tree that
represents the choices taken during computation. In a non-leaf partition tree:

- the left (index 0) branch contains all ways of partitioning `n` using at
  least one `m`,
- the right (index 1) branch contains partitions using parts up to `m-1`, and
- the root label is `m`.

The labels at the leaves of a partition tree express whether the path from the
root of the tree to the leaf represents a successful partition of `n`.

```py
def partition_tree(n, m):
  """Return a partition tree of n using parts of up to m."""
  if n == 0:
    return tree(True)
  elif n < 0 or m == 0:
    return tree(False)
  else:
    left = partition_tree(n-m, m)
    right = partition_tree(n, m-1)
    return tree(m, [left, right])

def print_parts(tree, partition=[]):
  if is_leaf(tree):
    if label(tree):
      print(' + '.join(partition))
  else:
    left, right = branches(tree)
    m = str(label(tree))
    print_parts(left, partition + [m])
    print_parts(right, partition)

>>> partition_tree(2, 2)
[2, [True], [1, [1, [True], [False]], [False]]]

>>> print_parts(partition_tree(6, 4))
4 + 2
4 + 1 + 1
3 + 3
3 + 2 + 1
3 + 1 + 1 + 1
2 + 2 + 2
2 + 2 + 1 + 1
2 + 1 + 1 + 1 + 1
1 + 1 + 1 + 1 + 1 + 1

def right_binarize(tree):
  """Construct a right-branching binary tree."""
  if is_leaf(tree):
    return tree
  if len(tree) > 2:
    tree = [tree[0], tree[1:]]
  return [right_binarize(b) for b in tree]

>>> right_binarize([1, 2, 3, 4, 5, 6, 7])
[1, [2, [3, [4, [5, [6, 7]]]]]]
```

### 2.3.7 Linked Lists

```py
empty = 'empty'

def is_link(s):
  """s is a linked list if it is empty or a (first, rest) pair."""
  return s == empty or (len(s) == 2 and is_link(s[1]))

def link(first, rest):
  """Construct a linked list from its first element and the rest."""
  assert is_link(rest), "rest must be a linked list."
  return [first, rest]

def first(s):
  """Return the first element of a linked list s."""
  assert is_link(s), "first only applies to linked lists."
  assert s != empty, "empty linked list has no first element."
  return s[0]

def rest(s):
  """Return the rest of the elements of a linked list s."""
  assert is_link(s), "rest only applies to linked lists."
  assert s != empty, "empty linked list has no rest."
  return s[1]

def len_link(s):
  """Return the length of linked list s."""
  length = 0
  while s != empty:
    s, length = rest(s), length + 1
  return length

def getitem_link(s, i):
  """Return the element at index i of linked list s."""
  while i > 0:
    s, i = rest(s), i - 1
  return first(s)

def len_link_recursive(s):
  """Return the length of a linked list s."""
  if s == empty:
    return 0
  return 1 + len_link_recursive(rest(s))

def getitem_link_recursive(s, i):
  """Return the element at index i of linked list s."""
  if i == 0:
    return first(s)
  return getitem_link_recursive(rest(s), i - 1)

def extend_link(s, t):
  """Return a list with the elements of s followed by those of t."""
  assert is_link(s) and is_link(t)
  if s == empty:
    return t
  else:
    return link(first(s), extend_link(rest(s), t))

def apply_to_all_link(f, s):
  """Apply f to each element of s."""
  assert is_link(s)
  if s == empty:
    return s
  else:
    return link(f(first(s)), apply_to_all_link(f, rest(s)))

def keep_if_link(f, s):
  """Return a list with elements of s for which f(e) is true."""
  assert is_link(s)
  if s == empty:
    return s
  else:
    kept = keep_if_link(f, rest(s))
    if f(first(s)):
      return link(first(s), kept)
    else:
      return kept

def join_link(s, separator):
  """Return a string of all elements in s separated by separator."""
  if s == empty:
    return ""
  elif rest(s) == empty:
    return str(first(s))
  else:
    return str(first(s)) + separator + join_link(rest(s), separator)
```

#### Recursive Construction

Counting the number of ways to partition an integer `n` using parts up to size
`m` via a tree-recursive process with sequences:

- partitioning `n-m` using integers up to `m`, or
- partitioning `n` using integers up to `m-1`.

```py
def partitions(n, m):
  """Return a linked list of partitions of n using parts of up to m.
  Each partition is represented as a linked list.
  """
  if n == 0:
    return link(empty, empty) # A list containing the empty partition
  elif n < 0 or m == 0:
    return empty
  else:
    using_m = partitions(n-m, m)
    with_m = apply_to_all_link(lambda s: link(m, s), using_m)
    without_m = partitions(n, m-1)
    return extend_link(with_m, without_m)

def print_partitions(n, m):
  lists = partitions(n, m)
  strings = apply_to_all_link(lambda s: join_link(s, " + "), lists)
  print(join_link(strings, "\n"))

>>> print_partitions(6, 4)
4 + 2
4 + 1 + 1
3 + 3
3 + 2 + 1
3 + 1 + 1 + 1
2 + 2 + 2
2 + 2 + 1 + 1
2 + 1 + 1 + 1 + 1
1 + 1 + 1 + 1 + 1 + 1
```

## Lab 3: Recursion, Tree Recursion, Python Lists

- [x] [Lab 3: Recursion, Tree Recursion, Python Lists](https://www.learncs.site/docs/curriculum-resource/cs61a/lab/lab03)

## Discussion 4: Tree Recursion, Python Lists

- [Discussion 4: Tree Recursion, Python Lists](https://inst.eecs.berkeley.edu/~cs61a/sp23/disc/disc04/)

## Project 2: CS 61A Autocorrected Typing Software

- [x] [Project 2: CS 61A Autocorrected Typing Software](https://inst.eecs.berkeley.edu/~cs61a/sp23/proj/cats/)

## Lab 4: Tree Recursion, Data Abstraction

A ***predicate function*** is a function that takes in an argument and returns
either `True` or `False`.

- [x] [Lab 4: Tree Recursion, Data Abstraction](https://www.learncs.site/docs/curriculum-resource/cs61a/lab/lab04)

## Discussion 5: Trees

- [Discussion 5: Trees](https://inst.eecs.berkeley.edu/~cs61a/sp23/disc/disc05/)

## 2.4 Mutable Data

> <https://www.composingprograms.com/pages/24-mutable-data.html>

### 2.4.1 The Object Metaphor

***Objects*** combine data values with behavior.

Numbers, strings, lists, and ranges are all objects, in fact, all values in
Python are objects. All values have behavior and attributes.

### 2.4.2 Sequence Objects

Instances of primitive built-in values such as numbers are *immutable*.
Some other values such as lists are *mutable*.

With mutable data, methods caled on one name can affect another name at the same
time.

Lists can be copied using the `list` constructor function.

```py
>>> nest = list(suits)  # Bind "nest" to a second list with the same elements
```

Python includes two comparison operators, called `is` and `is not`, that test
whether two expressions in fact evaluate to the identical object. Identity is
a stronger condition than equality.

```py
>>> suits = ['heart', 'diamond', 'spade', 'club']
>>> nest = ['heart', 'diamond', 'spade', 'club']
>>> nest[0] = suits
>>> suits is nest[0]
True
>>> suits is ['heart', 'diamond', 'spade', 'club']
False
>>> suits == ['heart', 'diamond', 'spade', 'club']
True
```

A list comprehension always creates a new list.

A tuple is an immutable sequence. Tuples are used implicitly in multiple
assignment. An assignment of two values to two names creates a two-element tuple
and then unpacks it.

### 2.4.3 Dictionaries

Dictionaries are ***unordered collections*** of key-value pairs. They have some
restrictions:

- A key of a dictionary cannot be or contain a mutable value. (tied to the
  underlying implementation in Python)
- There can be at most one value for a given key.

Tuples are commonly used for keys in dictionaries because lists cannot be used.

`get(KEY, default)` returns either the value for a key or a default value.

```py
{x: x*x for x in range(3,6)}
```

### 2.4.4 Local State

Lists and dictionaries have *local state*: they are changing values that have
some particular contents at any point in the execution of a program.

```py
def make_withdraw(balance):
  """Return a withdraw function that draws down balance with each call."""
  def withdraw(amount):
    nonlocal balance                 # Declare the name "balance" nonlocal
    if amount > balance:
      return 'Insufficient funds'
    balance = balance - amount       # Re-bind the existing balance name
    return balance
  return withdraw
```

The `nonlocal` statement declares that whenever we change the binding of the
name `balance`, the binding is changed in the first frame in which `balance` is
already bound.

After executing `nonlocal balance`, any assignment statement with `balance` on
the left-hand side of `=` will not bind `balance` in the first frame of the
current environment. Instead, it will find the first frame in which `balance`
was already defined and re-bind the name in that frame. If `balance` has not
previously been bound to a value, then the `nonlocal` statement will give an
error.

No `nonlocal` statement is required to *access* a non-local name. By contrast,
only after a `nonlocal` statement can a function *change* the binding of names
in these frames.

Most other languages do not require a `nonlocal` statement at all. Instead,
non-local assignment is often the default behavior of assignment statements.

⚠️ Python also has an unusual restriction regarding the lookup of names: within
the body of a function, all instances of a name must refer to the same frame.
As a result, Python cannot look up the value of a name in a non-local frame,
then bind that same name in the local frame, because the same name would be
accessed in two different frames in the same function. This restriction allows
Python to pre-compute which frame contains each name before executing the body
of a function. When this restriction is violated, a confusing error message
results.

```py
def make_withdraw(balance):
  def withdraw(amount):
    if amount > balance:        # causes an UnboundLocalError
      return 'Insufficient funds'
    balance = balance - amount  # becasue of this
    return balance
  return withdraw

wd = make_withdraw(20)
wd(5)

# This error occurs before line 5 is ever executed, implying that Python has
#   considered line 5 in some way before executing line 3.
```

### 2.4.5 The Benefits of Non-Local Assignment

### 2.4.6 The Cost of Non-Local Assignment

The key to correctly analyzing code with non-local assignment is to remember
that **only function calls can introduce new frames**. Assignment statements
always change bindings in existing frames.

An expression that contains only pure function calls is
***referentially transparent*** (引用透明).

### 2.4.7 Implementing Lists and Dictionaries

```py
def mutable_link():
  """Return a functional implementation of a mutable linked list."""
  contents = empty
  def dispatch(message, value=None):
    nonlocal contents
    if message == 'len':
      return len_link(contents)
    elif message == 'getitem':
      return getitem_link(contents, value)
    elif message == 'push_first':
      contents = link(value, contents)
    elif message == 'pop_first':
      f = first(contents)
      contents = rest(contents)
      return f
    elif message == 'str':
      return join_link(contents, ", ")
  return dispatch

def to_mutable_link(source):
  """Return a functional list with the same contents as source."""
  s = mutable_link()
  for element in reversed(source):
    s('push_first', element)
  return s
```

This approach encapsulates the logic for all operations on a data value within
one function that responds to different messages, is a discipline called
***message passing***.

```py
def dictionary():
  """Return a functional implementation of a dictionary."""
  records = []
  def getitem(key):
    matches = [r for r in records if r[0] == key]
    if len(matches) == 1:
      key, value = matches[0]
      return value
  def setitem(key, value):
    nonlocal records
    non_matches = [r for r in records if r[0] != key]
    records = non_matches + [[key, value]]
  def dispatch(message, key=None, value=None):
    if message == 'getitem':
      return getitem(key)
    elif message == 'setitem':
      setitem(key, value)
  return dispatch
```

### 2.4.8 Dispatch Dictionaries

```py
def account(initial_balance):
  def deposit(amount):
    dispatch['balance'] += amount
    return dispatch['balance']
  def withdraw(amount):
    if amount > dispatch['balance']:
      return 'Insufficient funds'
    dispatch['balance'] -= amount
    return dispatch['balance']
  dispatch = {'deposit':   deposit,
              'withdraw':  withdraw,
              'balance':   initial_balance}
  return dispatch

def withdraw(account, amount):
  return account['withdraw'](amount)
def deposit(account, amount):
  return account['deposit'](amount)
def check_balance(account):
  return account['balance']

a = account(20)
deposit(a, 5)
withdraw(a, 17)
check_balance(a)
```

By storing the balance in the dispatch dictionary rather than in the `account`
frame directly, we avoid the need for `nonlocal` statements in `deposit` and
`withdraw`.

### 2.4.9 Propagating Constraints

Expressing programs as constraints is a type of ***declarative programming***,
in which a programmer declares the structure of a problem to be solved, but
abstracts away the details of exactly how the solution to the problem is
computed.

```py
from operator import add, sub, mul, truediv

def inform_all_except(source, message, constraints):
  """Inform all constraints of the message, except source."""
  for c in constraints:
    if c != source:
      c[message]()

def connector(name=None):
  """A connector between constraints."""
  informant = None
  constraints = []
  def set_value(source, value):
    nonlocal informant
    val = connector['val']
    if val is None:
      informant, connector['val'] = source, value
      if name is not None:
        print(name, '=', value)
      inform_all_except(source, 'new_val', constraints)
    else:
      if val != value:
        print('Contradiction detected:', val, 'vs', value)
  def forget_value(source):
    nonlocal informant
    if informant == source:
      informant, connector['val'] = None, None
      if name is not None:
        print(name, 'is forgotten')
      inform_all_except(source, 'forget', constraints)

  connector = {'val': None,
              'set_val': set_value,
              'forget': forget_value,
              'has_val': lambda: connector['val'] is not None,
              'connect': lambda source: constraints.append(source)}
  return connector

def make_ternary_constraint(a, b, c, ab, ca, cb):
  """The constraint that ab(a,b)=c and ca(c,a)=b and cb(c,b) = a."""
  def new_value():
    av, bv, cv = [connector['has_val']() for connector in (a, b, c)]
    if av and bv:
      c['set_val'](constraint, ab(a['val'], b['val']))
    elif av and cv:
      b['set_val'](constraint, ca(c['val'], a['val']))
    elif bv and cv:
      a['set_val'](constraint, cb(c['val'], b['val']))
  def forget_value():
    for connector in (a, b, c):
      connector['forget'](constraint)
  constraint = {'new_val': new_value, 'forget': forget_value}
  for connector in (a, b, c):
    connector['connect'](constraint)
  return constraint

def adder(a, b, c):
  """The constraint that a + b = c."""
  return make_ternary_constraint(a, b, c, add, sub, sub)

def multiplier(a, b, c):
        """The constraint that a * b = c."""
        return make_ternary_constraint(a, b, c, mul, truediv, truediv)

def constant(connector, value):
  """The constraint that connector = value."""
  constraint = {}
  connector['set_val'](constraint, value)
  return constraint

def converter(c, f):
  """Connect c to f with constraints to convert from Celsius to Fahrenheit."""
  u, v, w, x, y = [connector() for _ in range(5)]
  multiplier(c, w, u)
  multiplier(v, x, u)
  adder(v, y, f)
  constant(w, 9)
  constant(x, 5)
  constant(y, 32)

celsius = connector('Celsius')
fahrenheit = connector('Fahrenheit')
converter(celsius, fahrenheit)
```

## Homework 4: Trees, Data Abstraction

- [x] [Homework 4: Trees, Data Abstraction](https://inst.eecs.berkeley.edu/~cs61a/sp23/hw/hw04/)

## 2.5 Object-Oriented Programming

> <https://www.composingprograms.com/pages/25-object-oriented-programming.html>

### 2.5.1 Objects and Classes

### 2.5.2 Defining Classes

```py
class <name>:
    <suite>
```

When a class statement is executed, a new class is created and bound to `<name>`
in the first frame of the current environment. The suite is then executed. Any
names bound within the `<suite>` of a class statement, through `def` or
assignment statements, create or modify attributes of the class.

```py
>>> class Account:
        def __init__(self, account_holder):
            self.balance = 0
            self.holder = account_holder

>>> a = Account('Kirk')
```

***By convention***, we use the parameter name `self` for the first argument of
a constructor, because it is bound to the object being instantiated. This
convention is adopted in virtually all Python code.

```py
>>> a.balance
0
>>> a.holder
'Kirk'

>>> b = Account('Spock')
>>> b.balance = 200
>>> [acc.balance for acc in (a, b)]
[0, 200]
```

To enforce this separation, every object that is an instance of a user-defined
class has a unique identity. Object identity is compared using the `is` and
`is not` operators.

```py
>>> a is a
True
>>> a is not b
True

>>> c = a
>>> c is a
True
```

```py
>>> class Account:
        def __init__(self, account_holder):
            self.balance = 0
            self.holder = account_holder
        def deposit(self, amount):
            self.balance = self.balance + amount
            return self.balance
        def withdraw(self, amount):
            if amount > self.balance:
                return 'Insufficient funds'
            self.balance = self.balance - amount
            return self.balance
```

```py
>>> spock_account = Account('Spock')
>>> spock_account.deposit(100)
100
>>> spock_account.withdraw(90)
10
>>> spock_account.withdraw(90)
'Insufficient funds'
>>> spock_account.holder
'Spock'
```

### 2.5.3 Message Passing and Dot Expressions

A **dot expression** consists of an expression, a dot, and a name:

```py
<expression> . <name>
```

The built-in function `getattr` also returns an attribute for an object by name.
It is the function equivalent of dot notation. Using `getattr`, we can look up
an attribute using a string, just as we did with a dispatch dictionary.

```py
>>> getattr(spock_account, 'balance')
10
```

We can also test whether an object has a named attribute with `hasattr`.

```py
>>> hasattr(spock_account, 'deposit')
True
```

Methods are attributes of the class that require special handling.

**Methods and functions**.

To achieve automatic `self` binding, Python distinguishes between functions,
and ***bound methods***, which couple together a function and the object on
which that method will be invoked. A bound method value is already associated
with its first argument, the instance on which it was invoked, which will be
named `self` when the method is called.

As an attribute of a ***class***, a method is just a function, but as an
attribute of an ***instance***, it is a bound method:

```py
>>> type(Account.deposit)
<class 'function'>
>>> type(spock_account.deposit)
<class 'method'>
```

These two results differ only in the fact that the first is a standard
two-argument function with parameters `self` and `amount`. The second is a
one-argument method, where the name `self` will be bound to the object named
`spock_account` automatically when the method is called, while the parameter
`amount` will be bound to the argument passed to the method.

We can call `deposit` in two ways: as a function and as a bound method. In the
former case, we must supply an argument for the `self` parameter explicitly.
In the latter case, the `self` parameter is bound automatically.

```py
# The deposit function takes 2 arguments
>>> Account.deposit(spock_account, 1001)
1011

# The deposit method takes 1 argument
>>> spock_account.deposit(1000)
2011
```

The function `getattr` behaves exactly like dot notation: if its first argument
is an object but the name is a method defined in the class, then `getattr`
returns a bound method value. On the other hand, if the first argument is a
class, then `getattr` returns the attribute value directly, which is a plain
function.

### 2.5.4 Class Attributes

***Class attributes*** may also be called ***class variables*** or
***static variables***.

```py
>>> class Account:
        interest = 0.02            # A class attribute
        def __init__(self, account_holder):
            self.balance = 0
            self.holder = account_holder
        # Additional methods would be defined here

>>> spock_account = Account('Spock')
>>> kirk_account = Account('Kirk')
>>> spock_account.interest
0.02
>>> kirk_account.interest
0.02
```

However, a single assignment statement to a class attribute changes the value
of the attribute for all instances of the class.

```py
>>> Account.interest = 0.04
>>> spock_account.interest
0.04
>>> kirk_account.interest
0.04
```

**Attribute names**.

```py
<expression> . <name>
```

To evaluate a dot expression:

1. Evaluate the `<expression>` to the left of the dot, which yields the object
   of the dot expression.
2. `<name>` is matched against the instance attributes of that object; if an
   attribute with that name exists, its value is returned.
3. If `<name>` does not appear among instance attributes, then `<name>` is
   looked up in the class, which yields a class attribute value.
4. That value is returned unless it is a function, in which case a bound method
   is returned instead.

**Attribute assignment**.

```py
>>> kirk_account.interest = 0.08
>>> kirk_account.interest
0.08

>>> spock_account.interest
0.04
```

```py
# changing the class attribute
>>> Account.interest = 0.05

# changes instances without like-named instance attributes
>>> spock_account.interest
0.05

# but the existing instance attribute is unaffected
>>> kirk_account.interest
0.08
```

### 2.5.5 Inheritance

```py
>>> ch = CheckingAccount('Spock')
>>> ch.interest     # Lower interest rate for checking accounts
0.01
>>> ch.deposit(20)  # Deposits are the same
20
>>> ch.withdraw(5)  # withdrawals decrease balance by an extra charge
14
```

### 2.5.6 Using Inheritance

```py
class Account:
    """A bank account that has a non-negative balance."""
    interest = 0.02
    def __init__(self, account_holder):
        self.balance = 0
        self.holder = account_holder
    def deposit(self, amount):
        """Increase the account balance by amount and return the new balance."""
        self.balance = self.balance + amount
        return self.balance
    def withdraw(self, amount):
        """Decrease the account balance by amount and return the new balance."""
        if amount > self.balance:
            return 'Insufficient funds'
        self.balance = self.balance - amount
        return self.balance

class CheckingAccount(Account):
    """A bank account that charges for withdrawals."""
    withdraw_charge = 1
    interest = 0.01
    def withdraw(self, amount):
        return Account.withdraw(self, amount + self.withdraw_charge)
```

```py
>>> checking = CheckingAccount('Sam')
>>> checking.deposit(10)
10
>>> checking.withdraw(5)
4
>>> checking.interest
0.01
```

When Python resolves a name in a dot expression that is not an attribute of the
instance, it looks up the name in the class. In fact, the act of "looking up" a
name in a class tries to find that name in every base class in the inheritance
chain for the original object's class. We can define this procedure recursively.
To look up a name in a class.

1. If it names an attribute in the class, return the attribute value.
2. Otherwise, look up the name in the base class, if there is one.

**Calling ancestors**.

**Interfaces**. It is extremely common in object-oriented programs that
different types of objects will share the same attribute names. An object
***interface*** is a collection of attributes and conditions on those
attributes. For example, all accounts must have `deposit` and `withdraw`
methods that take numerical arguments, as well as a `balance` attribute. The
classes `Account` and `CheckingAccount` both implement this interface.
Inheritance specifically promotes name sharing in this way.

💡 The parts of your program that use objects (rather than implementing them)
are most robust to future changes if they do not make assumptions about object
types, but instead only about their attribute names. That is, they use the
object abstraction, rather than assuming anything about its implementation.

```py
>>> def deposit_all(winners, amount=5):
        for account in winners:
            account.deposit(amount)
```

The following implementation will not necessarily work with new kinds of
accounts:

```py
>>> def deposit_all(winners, amount=5):
        for account in winners:
            Account.deposit(account, amount)
```

### 2.5.7 Multiple Inheritance

```py
>>> class SavingsAccount(Account):
        deposit_charge = 2
        def deposit(self, amount):
            return Account.deposit(self, amount - self.deposit_charge)
```

Then, a clever executive conceives of an `AsSeenOnTVAccount` account with the
best features of both `CheckingAccount` and `SavingsAccount`: withdrawal fees,
deposit fees, and a low interest rate.

```py
>>> class AsSeenOnTVAccount(CheckingAccount, SavingsAccount):
        def __init__(self, account_holder):
            self.holder = account_holder
            self.balance = 1           # A free dollar!

>>> such_a_deal = AsSeenOnTVAccount("John")
>>> such_a_deal.balance
1
>>> such_a_deal.deposit(20)            # $2 fee from SavingsAccount.deposit
19
>>> such_a_deal.withdraw(5)            # $1 fee from CheckingAccount.withdraw
13
```

Non-ambiguous references are resolved correctly as expected:

```py
>>> such_a_deal.deposit_charge
2
>>> such_a_deal.withdraw_charge
1
```

But what about when the reference is ambiguous, such as the reference to the
`withdraw` method that is defined in both `Account` and `CheckingAccount`?

Python resolves names from left to right, then upwards. In this example, Python
checks for an attribute name in the following classes, in order, until an
attribute with that name is found:

`AsSeenOnTVAccount, CheckingAccount, SavingsAccount, Account, object`

Any programming language that supports ***multiple inheritance*** must select
some ordering in a consistent way, so that users of the language can predict
the behavior of their programs.

Python resolves this name using a recursive algorithm called the C3 Method
Resolution Ordering. The method resolution order of any class can be queried
using the `mro` method on all classes.

```py
>>> [c.__name__ for c in AsSeenOnTVAccount.mro()]
['AsSeenOnTVAccount', 'CheckingAccount', 'SavingsAccount', 'Account', 'object']
```

### 2.5.8 The Role of Objects

💡 Functional abstractions provide a more natural metaphor for representing
relationships between inputs and outputs.

## Homework 5: Generators

- [x] [Homework 5: Generators](https://www.learncs.site/docs/curriculum-resource/cs61a/homework/hw05)

## Lab 6: OOP

>>>>> progress

- [ ] [Lab 6: OOP](https://www.learncs.site/docs/curriculum-resource/cs61a/lab/lab06)

## Project 3: Ants Vs. SomeBees

- [ ] [Project 3: Ants Vs. SomeBees](https://www.learncs.site/docs/curriculum-resource/cs61a/project/ants)

## Discussion 7: OOP

- [Discussion 7: OOP](https://www.learncs.site/docs/curriculum-resource/cs61a/dis/disc07)

## 2.6 Implementing Classes and Objects

> <https://www.composingprograms.com/pages/26-implementing-classes-and-objects.html>
