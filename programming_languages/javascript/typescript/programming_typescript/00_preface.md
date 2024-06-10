# Preface

- [Preface](#preface)
  - [How This Book Is Organized](#how-this-book-is-organized)
  - [Style](#style)
    - [Conventions Used in This Book](#conventions-used-in-this-book)
  - [Using Code Examples](#using-code-examples)

## How This Book Is Organized

## Style

Some aspects of the code style are things that good to follow. A few of these
are:

- You should use the latest JavaScript syntax and features (the latest
  JavaScript version is usually just called `esnext`).
  - This will keep your code in line with the latest standards, improving
    interoperability and Googleability,
  - and it can help reduce ramp-up time for new hires.
  - It also lets you take advantage of powerful, modern JavaScript features like
    arrow functions, promises, and generators.
- You should keep your data structures immutable with spreads (`...`) most of
  the time.
- You should make sure everything has a type, inferred when possible.
  - Be careful not to abuse explicit types; this will help keep your code clear
    and terse, and improve safety by surfacing incorrect types rather than
    bandaiding over them.
- You should keep your code reusable and generic. Polymorphism is your best
  friend.

JavaScript doesn’t expose pointers and references; instead it has value and
reference types.

- Values are immutable, and include things like strings, numbers, and booleans,
- while references point to often-mutable data structures like arrays, objects,
  and functions.

### Conventions Used in This Book

## Using Code Examples

An attribution usually includes the title, author, publisher, and ISBN. For
example: “Programming TypeScript by Boris Cherny (O’Reilly). Copyright 2019
Boris Cherny, 978-1-492-03765-1.”
