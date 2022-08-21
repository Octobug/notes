# Chapter 8: Moving Features

- [Chapter 8: Moving Features](#chapter-8-moving-features)
  - [Move Function](#move-function)
    - [Motivation](#motivation)
    - [Mechanics](#mechanics)
    - [Example: Moving a Nested Function to Top Level](#example-moving-a-nested-function-to-top-level)
    - [Example: Moving between Classes](#example-moving-between-classes)
  - [Move Field](#move-field)
    - [Motivation](#motivation-1)
    - [Mechanics](#mechanics-1)
    - [Example](#example)
      - [Changing a Bare Record](#changing-a-bare-record)
    - [Example: Moving to a Shared Object](#example-moving-to-a-shared-object)

## Move Function

```js
class Account {
    get overdraftCharge() { ... }
}

// refactored:
class AccountType {
    get overdraftCharge() { ... }
}
```

### Motivation

The heart of a good software design is its modularity -- which is an ability to
make most modifications to a program while only having to understand a small
part of it. To get this modularity, it needs to be ensured that related software
elements are grouped together and the links between them are easy to find and
understand.

One of the most straightforward reasons to move a function is when it references
elements in other contexts more than the one it currently resides in. Moving it
together with those elements often improves encapsulation, allowing other parts
of the software to be less dependent on the details of this module.

### Mechanics

- Examine all the program elements used by the chosen function in its current
  context. Consider whether they should move too.
  - If a called function should also be moved, it is better to move it first.
- Check if the chosen function is a polymorphic method.
- Copy the function to the target context. Adjust it to fit in its new home.
- Perform static analysis.
- Figure out how to reference the target function from the source context.
- Turn the source function into a delegating function.
- Test.
- Consider `Inline Function` on the source function.

### Example: Moving a Nested Function to Top Level

[moving_a_nested_function_to_top_level.js](moving_a_nested_function_to_top_level.js)

### Example: Moving between Classes

[moving_between_classes.js](moving_between_classes.js)

## Move Field

```js
class Customer {
  get plan() { return this._plan; }
  get discountRate() { return this._discountRate; }
}

// refactored:
class Customer {
  get plan() { return this._plan; }
  get discountRate() { return this.plan.discountRate; }
}
```

### Motivation

Poor data structures lead to lots of code whose job is merely dealing with the
poor data. The messy code is harder to understand and the data structures
obscure what the program is doing.

### Mechanics

- Ensure the source field is encapsulated.
- Test.
- Create a field (and accessors) in the target.
- Run static checks.
- Ensure there is a reference from the source object to the target object.
- Adjust accessors to use the target field.
- Test.
- Remove the source field.
- Test.

### Example

[move_field.js](move_field.js)

#### Changing a Bare Record

If possible, the first move is better to use `Encapsulate Record` to turn the
record into a class so it could be changed more easily.

### Example: Moving to a Shared Object

>>>>> progress
