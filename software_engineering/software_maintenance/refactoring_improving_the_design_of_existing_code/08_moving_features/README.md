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
  - [Move Statements into Function](#move-statements-into-function)
    - [Motivation](#motivation-2)
    - [Mechanics](#mechanics-2)
    - [Example](#example-1)
  - [Move Statements to Callers](#move-statements-to-callers)

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

[moving_to_a_shared_object.js](moving_to_a_shared_object.js)

## Move Statements into Function

```js
result.push(`<p>title: ${person.photo.title}</p>`);
result.concat(photoData(person.photo));

function photoData(aPhoto) {
  return [
    `<p>location: ${aPhoto.location}</p>`,
    `<p>date: ${aPhoto.date.toDateString()}</p>`,
  ];
}

// refactored:
result.concat(photoData(person.photo));

function photoData(aPhoto) {
  return [
    `<p>title: ${aPhoto.title}</p>`,
    `<p>location: ${aPhoto.location}</p>`,
    `<p>date: ${aPhoto.date.toDateString()}</p>`,
  ];
}
```

### Motivation

If some code executed every time when a particular function is called, that
repeating code should be combined into the function itself.

If these code don't make sense as part of the called function, but still should
be called with it, then use `Extract Function` on the statements and the called
function.

### Mechanics

- If the repetitive code isn't adjacent to the call of the target function, use
  `Slide Statements` to get it adjacent.
- If the target function is only called by the source function, just cut the
  code from the source, paste it into the target, test, and ignore the rest of
  these mechanics.
- If you have more callers, use `Extract Function` on one of the call sites to
  extract both the call to the target function and the statements you wish to
  move into it. Give it a name that's transient, but easy to grep.
- Convert every other call to use the new function. Test after each conversion.
- When all the original calls use the new function, use `Inline Function` to
  inline the original function completely into the new function, removing the
  original funciton.
- `Rename Funciton` to change the name of the new function to the same name as
  the original function.

### Example

[move_statements_into_function.js](move_statements_into_function.js)

## Move Statements to Callers

>>>>> progress
