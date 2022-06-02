# Chapter 3: Bad Smells in Code

- [Chapter 3: Bad Smells in Code](#chapter-3-bad-smells-in-code)
  - [Mysterious Name](#mysterious-name)
  - [Duplicated Code](#duplicated-code)
  - [Long Function](#long-function)
  - [Long Parameter List](#long-parameter-list)

## Mysterious Name

> Perhaps the most common refactorings are the renames.

**Refactorings**:

- Change Function Declaration
- Rename Field
- Rename Variable

## Duplicated Code

**Refactorings**:

- Extract Function: eliminate duplicated code
- Pull Up Method: avoid calling duplicated code from subclasses methods
- Slide Statement: arrange similiar items for easy extraction

## Long Function

The longer a function is, the more difficult it is to understand.

There is overhead for the reader of the code base, which consist of short
functions, for you have to switch context to see what the function does.

The real key to making it easy to understand small functions is **good naming**.
A heuristic we follow is that whenever we feel the need to comment something, we
write a function instead.

**Refactorings**:

- Decompose Conditional
- Extract Function: find parts of the function that seem to go nicely together
- Introduce Parameter Object: slim down long lists of parameters
- Preserve Whole Object: slim down long lists of parameters
- Replace Conditional with Polymorphism: when more than one switch statement
  switching on the same condition
- Replace Function with Command
- Replace Temp with Query: eliminate temp variables
- Split Loop: break out the separate tasks

## Long Parameter List

>>>>> progress
