# Chapter 3: Bad Smells in Code

- [Chapter 3: Bad Smells in Code](#chapter-3-bad-smells-in-code)
  - [Mysterious Name](#mysterious-name)
  - [Duplicated Code](#duplicated-code)
  - [Long Function](#long-function)
  - [Long Parameter List](#long-parameter-list)
  - [Global Data](#global-data)

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

>>>>> progress
