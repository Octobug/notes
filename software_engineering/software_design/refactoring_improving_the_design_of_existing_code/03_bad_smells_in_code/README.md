# Chapter 3: Bad Smells in Code

- [Chapter 3: Bad Smells in Code](#chapter-3-bad-smells-in-code)
  - [Mysterious Name](#mysterious-name)
  - [Duplicated Code](#duplicated-code)
  - [Long Function](#long-function)
  - [Long Parameter List](#long-parameter-list)
  - [Global Data](#global-data)
  - [Mutable Data](#mutable-data)
  - [Divergent Change](#divergent-change)
  - [Shotgun Surgery](#shotgun-surgery)
  - [Feature Envy](#feature-envy)
  - [Data Clumps](#data-clumps)
  - [Primitive Obsession](#primitive-obsession)
  - [Repeated Switches](#repeated-switches)
  - [Loops](#loops)
  - [Lazy Element](#lazy-element)
  - [Speculative Generality](#speculative-generality)
  - [Temporary Field](#temporary-field)
  - [Message Chains](#message-chains)
  - [Middle Man](#middle-man)
  - [Insider Trading](#insider-trading)
  - [Large Class](#large-class)
  - [Alternative Classes with Different Interfaces](#alternative-classes-with-different-interfaces)
  - [Data Class](#data-class)
  - [Refused Bequest](#refused-bequest)
  - [Comments](#comments)

## Mysterious Name

> Perhaps the most common refactorings are the renames.

**Refactorings**:

- `Change Function Declaration`
- `Rename Variable`
- `Rename Field`

## Duplicated Code

**Refactorings**:

- `Extract Function`: eliminate duplicated code
- `Slide Statement`: arrange similiar items for easy extraction
- `Pull Up Method`: avoid calling duplicated code from subclasses methods

## Long Function

The longer a function is, the more difficult it is to understand.

There is overhead for the reader of the code base, which consist of short
functions, for you have to switch context to see what the function does.

The real key to making it easy to understand small functions is **good naming**.
A heuristic we follow is that whenever we feel the need to comment something, we
write a function instead.

**Refactorings**:

- `Extract Function`: find parts of the function that seem to go nicely together
- `Replace Temp with Query`: eliminate temp variables
- `Introduce Parameter Object`: slim down long lists of parameters
- `Preserve Whole Object`: slim down long lists of parameters
- `Replace Function with Command`: when you have too many temps and parameters
- `Decompose Conditional`: to deal with conditional expressions
- `Replace Conditional with Polymorphism`: when more than one switch statement
  switching on the same condition
- `Split Loop`: break out the separate tasks

## Long Parameter List

**Refactorings**:

- `Replace Parameter with Query`: if you can obtain one parameter by asking
  another parameter for it
- `Preserve Whole Object`: to pass the original data structure
- `Introduce Parameter Object`: if several parameters always fit together
- `Remove Flag Argument`: if a parameter is used as a flag to dispatch different
  behavior
- `Combine Functions into Class`: to capture common parameters as fields

## Global Data

The problem with global data is that it can be modified from anywhere in the
code base, and there's no mechanism to discover which bit of code touched it.

**Refactorings**:

- `Encapsulate Variable`: when confronted with data that is open to
  contamination by any part of a program

## Mutable Data

Functional programming is based on the notion that data should never change and
that updating a data structure should always return a new copy of the structure
with the change, leaving the old data pristine.

**Refactorings**:

- `Encapsulate Variable`: to ensure that all updates occur through narrow
  functions that can be easier to monitor and evolve
- `Split Variable`: use this if a variable is being updated to store different
  things, both to keep them separate and avoid the risky update
- `Slide Statements`: try as much as possible to move logic out of code that
  processes the update
- `Extract Function`: to separate the side-effect-free code from anything that
  performs the update
- `Separate Query from Modifier`: in APIs, use this to ensure callers don't need
  to call code that has side effects unless they really need to
- `Remove Setting Method`: spots opportunities to reduce the scope of a variable
- `Replace Derived Variable with Query`: mutable data that can be calculated
  elsewhere is particularly pungent
- `Combine Functions into Class`: to limit how much code needs to update a
  variable
- `Combine Functions into Transform`: to limit how much code needs to update a
  variable
- `Change Reference to Value`: replace the entire structure rather than modify
  it in place

## Divergent Change

Divergent change occurs when on module is often changed in different ways for
different reasons.

**Refactorings**:

- `Split Phase`: if interaction with database and business processing naturally
  form a sequence
- `Move Function`: to divide the processing up if there's more back-and-forth in
  the calls
- `Extract Function`: if functions mix types of processing within themselves
- `Extract Class`: helps formalize how to do the split

## Shotgun Surgery

**Refactorings**:

- `Move Function`: to put all the changes into a single module
- `Move Field`: to put all the changes into a single module
- `Combine Functions into Class`: if you have a bunch of functions operating on
  similar data
- `Combine Functions into Transform`: if you have functions that are
  transforming or enriching a data structure
- `Split Phase`: if the common function can combine thier output for a
  consuming phase of logic
- `Inline Function`: to pull together poorly separated logic
- `Inline Class`: to pull together poorly separated logic

## Feature Envy

A classic case of `Feature Envy` occurs when a function in one module spends
more time communicating with functions or data inside another module than it
does within its own module.

**Refactorings**:

- `Move Function`: when functions clearly wants to be with the data
- `Extract Function`: when only a part of a function has the *Feature Envy*
  problem, to break the function into pieces that go into different places
- ``

## Data Clumps

**Refactorings**:

- `Extract Class`: to turn the data clumps into an object
- `Introduce Parameter Object`: to slim down parameters
- `Preserve Whole Object`: to slim down parameters

## Primitive Obsession

- `Replace Primitive with Object`: create fundamental types which are useful for
  their domain
- `Replace Type Code with Subclasses`: if the primitive is a type code
  controlling conditional behavior
- `Replace Conditoinal with Polymorphism`
- `Extract Class`
- `Introduce Parameter Object`

## Repeated Switches

**Refactorings**:

- `Replace Conditional with Polymorphism`

## Loops

**Refactorings**:

- `Replace Loop with Pipeline`: filter, map, ...

## Lazy Element

**Refactorings**:

When program structures (function, class...) was expected to grow but it didn't:

- `Inline Function`
- `Inline Class`
- `Collapse Hierarchy`

## Speculative Generality

Adding all sorts of hooks and special cases to handle things that aren't
required. And causes it harder to understand and maintain.

**Refactorings**:

- `Collapse Hierarchy`: when you have abstract classes that aren't doing much
- `Inline Function`: to remove unnecessary delegation
- `Inline Class`: to remove unnecessary delegation
- `Change Function Declaration`: to remove unused parameters
- `Remove Dead Code`: when they only users of a function or class are test cases

## Temporary Field

Sometimes there is a class in which a field is set only in certain
circumstances. Such code is difficult to understand, because you expect an
object to need all of its fields.

**Refactorings**:

- `Extract Class`: to create a class for the temporary field
- `Move Function`: to pull all the code that concerns the fields into the new
  class
- `Introduce Special Case`: to eliminate conditional code

## Message Chains

You see message chains when a client asks one object for another object, which
the client then asks for yet another another object, which the client then asks
for yet another object, and so on.

**Refactorings**:

- `Hide Delegate`: you can do this to every object in the chain
- `Extract Function`: to take a piece of the code that uses it and then
- `Move Function`: to push it down the chain

## Middle Man

**Refactorings**:

- `Remove Middle Man`: talk to the object that really knows what's going on
- `Inline Function`: to inline methods into the caller
- `Replace Superclass with Delegate`: if there is additional behavior

## Insider Trading

**Refactorings**:

- `Move Function`: to reduce the need to chat
- `Move Field`: to reduce the need to chat
- `Hide Delegate`: to make another module act as an intermediary
- `Replace Subclass with Delegate`
- `Replace Superclass with Delegate`

## Large Class

**Refactorings**:

- `Extract Class`: to bundle a number of the variables
- `Extract Superclass`: if the component makes sense with inheritance
- `Replace Type Code with Subclasses`: if the component makes sense with
  inheritance
- `Extract Class`: to break a large class
- `Extract Superclass`: to break a large class
- `Replace Type Code with Subclasses`: to break a large class

## Alternative Classes with Different Interfaces

One of the great benefits of using classes is the support of substitution,
allowing one class to swap in for another in times of need. And this only works
if their interfaces are the same.

**Refactorings**:

- `Change Function Declaration`: to make functions match up
- `Move Function`: to move behavior into classes until the protocols match
- `Extract Superclass`: if `Move Function` leads to duplication

## Data Class

These are classes that have fields, getting and setting methods for the fields,
and nothing else.

Data classes are often a sign of behavior in the wrong place, which means you
can make big progress by moving it from the client into the data class itself.
But there are exceptions, and one of the best exceptions is a record that's
being used as a result record from a distinct function invocation.

**Refactorings**:

- `Encapsulate Record`: if classes have public fields
- `Remove Setting Method`: on any field that should not be changed
- `Move Function`: to move behavior into the data class
- `Extract Function`: if cannot move a whole function, use this to create a new
  one
- `Split Phase`: may ensue a result record which is created from a pure data
  class

## Refused Bequest

There are many cases that subclasses don't want or need all of what they were
given.

**Refactorings**:

- `Push Down Method`: to push all the unsed code to the sibling
- `Push Down Field`: to push all the unsed code to the sibling
- `Replace Subclass with Delegate`
- `Replace SUperclass with Delegate`

## Comments

When we're finished removing the bad codes by refoctoring, we often find that
the comments are superfluous.

**Refactorings**:

- `Extract Function`: if you need a comment to explain what a block of code does
- `Change Funcion Declaration`: rename the function if it is already extracted
  but you still need a comment to explain what it does
- `Introduce Assertion`: if you need to state some rules about the required
  state of the system

Good times to use a comment:

- you don't know what to do
- needs to describe what is going on
- indicates areas in which you aren't sure
- explain why you did something

💡 When you feel the need to write a comment, first try to refactor the code so
that any comment becomes superfluous.
