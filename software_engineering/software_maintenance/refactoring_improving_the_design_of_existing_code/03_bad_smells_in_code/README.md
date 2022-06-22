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

>>>>> progress
