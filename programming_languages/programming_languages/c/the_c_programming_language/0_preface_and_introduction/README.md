# Preface and Introduction

- [Preface and Introduction](#preface-and-introduction)
  - [Preface](#preface)
  - [Introduction](#introduction)
    - [Data Types](#data-types)
    - [Control-flow constructions](#control-flow-constructions)
    - [Functions](#functions)
    - [Source Files](#source-files)
    - [Macros](#macros)
    - [Language Level](#language-level)

## Preface

*The C Programming Language* was publicized in 1978.

In 1983, the American National Standards Institute (ANSI) established a
committee whose goal was to produce "an unambiguous and machine-independent
definition of the language C". And its result is the ANSI standard for C.

C is not a "very high level" language, nor a "big" one, and is not specialized
to any particular area of application.

C was originally designed for and implemented on the UNIX operating system on
the DEC PDP-11, by [Dennis Ritchie](https://en.wikipedia.org/wiki/Dennis_Ritchie)

## Introduction

C is a general-purpose programming language. Many of the important ideas of C
stem from the language BCPL. The influence of  BCPL on C preceeded indirectly
through the language B.

### Data Types

BCPL and B are "typeless" languages. By contrast, C provides a variety of data
types. The fundamental types are:

- characters
- integers
- floating-point numbers
- hierarchy of derived data types
  - pointers
  - arrays
  - structures
  - unions

### Control-flow constructions

- statement grouping
- decision making (if-else)
- selecting one of a set of possible cases (switch)
- looping with the termination test and early loop exit (break)
  - while
  - for
  - do-while

### Functions

- recursion
- lexical scope

### Source Files

- source code of a C origram may exist in separate source files
- variables may be internal to a function, external but known only within a
  single source file, or visible to the entire program

### Macros

- source code substitution
- inclusion of other source files

### Language Level

C is a relatively "low level" language. It deals with the same sort of objects
that most computers do, namely characters, numbers, and addresses.

C provides **no**:

- operations to deal directly with composite objects such as
  - character strings
  - sets
  - lists
  - arrays.
- storage allocation facility
  - heap
  - garbage collection
- I/O facilities
  - file access methods
- multiprogamming
- parallel operations
- synchronization
- coroutines

Some of the features above are provided by standard libraries, but some are
impossible to be achieved.

