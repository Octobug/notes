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
    - [Motivation](#motivation-3)
    - [Mechanics](#mechanics-3)
    - [Example](#example-2)
  - [Replace Inline Code with Function Call](#replace-inline-code-with-function-call)
    - [Motivation](#motivation-4)
    - [Mechanics](#mechanics-4)
  - [Slide Statements](#slide-statements)
    - [Motivation](#motivation-5)
    - [Mechanics](#mechanics-5)
    - [Example](#example-3)
    - [Example: Sliding with Conditionals](#example-sliding-with-conditionals)
  - [Split Loop](#split-loop)
    - [Motivation](#motivation-6)
    - [Mechanics](#mechanics-6)
    - [Example](#example-4)
  - [Replace Loop with Pipeline](#replace-loop-with-pipeline)
    - [Motivation](#motivation-7)
    - [Mechanics](#mechanics-7)
    - [Example](#example-5)
  - [Remove Dead Code](#remove-dead-code)
    - [Motivation](#motivation-8)
    - [Mechanics](#mechanics-8)

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

```js
emitPhotoData(outStream, person.photo);

function emitPhotoData(outStream, photo) {
  outStream.write(`<p>title: ${photo.title}</p>\n`);
  outStream.write(`<p>location: ${photo.location}</p>\n`);
}

// refactored:
emitPhotoData(outStream, person.photo);
outStream.write(`<p>location: ${person.photo.location}</p>\n`);

function emitPhotoData(outStream, photo) {
  outStream.write(`<p>title: ${photo.title}</p>\n`);
}
```

### Motivation

When common behavior used in several places needs to vary in some of its calls,
we need to move the varing behavior out of the function to its callers.

### Mechanics

- In simple circumstances, where you have only one or two callers and a simple
  function to call from, just cut the first line from the called function and
  paste (and perhaps fit) it into the callers. Test and you're done.
- Otherwise, apply `Extract Function` to all the statements that you **don't**
  wish to move; give it a temporary but easily searchable name.
- Use `Inline Function` on the original function.
- Apply `Change Function Declaration` on the extracted function to rename it to
  the original name.

### Example

[move_statements_to_callers.js](move_statements_to_callers.js)

## Replace Inline Code with Function Call

```js
let appliesToMass = false;
for (const s of states) ;{
  if (s === 'MA') {
    appliesToMass = true;
  }
}

// refactored:
let appliesToMass = states.includes('MA);
```

### Motivation

A named function can explain the purpose of the code rather than its mechanics.
It's also valuable to remove duplication: Instead of writing the same code
twice, we can just call the function.

### Mechanics

- Replace the inline code with a call to the existing function.
- Test.

## Slide Statements

```js
const pricingPlan = retrievePricingPlan();
const order = retrieveOrder();
let charge;
const chargePerUnit = pricingPlan.unit;

// refactored:
const pricingPlan = retrievePricingPlan();
const chargePerUnit = pricingPlan.unit;
const order = retrieveOrder();
let charge;
```

### Motivation

Code is easier to understand when things that are related to each other appear
together. If several lines of code access the same data structure, it's best for
them to be together rather than intermingled with code accessing other data
structures.

### Mechanics

- Identify the target position to move the fragment to. Examine statements
  between source and target to see if there is interference for the candidate
  fragment. Abandon action if there is any interference.
- Cut the fragment from the source and paste into the target position.
- Test.

### Example

[slide_statements.js](slide_statements.js)

### Example: Sliding with Conditionals

[sliding_with_conditionals.js](sliding_with_conditionals.js)

## Split Loop

```js
let averageAge = 0;
let totalSalary = 0;
for (const p of people) {
  averageAge += p.age;
  totalSalary += p.salary;
}
averageAge = averageAge / people.length;

// refactored:
let totalSalary = 0;
for (const p of people) {
  totalSalary += p.salary;
}

let averageAge = 0;
for (const p of people) {
  averageAge += p.age;
}
averageAge = averageAge / people.length;
```

### Motivation

If you're doing two different things in the same loop, then whenever you need to
modify the loop you have to understand both things. By splitting the loop, you
ensure you only need to understand the behavior you need to modify.

Splitting a loop can also make it easier to use.

### Mechanics

- Copy the loop.
- Identify and eliminate duplicate side effects.
- Test.

### Example

[split_loop.js](split_loop.js)

## Replace Loop with Pipeline

```js
const names = [];
for (const i of input) {
  if (i.job === 'programmer') {
    names.push(i.name);
  }
}

// refactored:
const names = input
  .filter(i => i.job === 'programmer')
  .map(i => i.name);
```

### Motivation

Collection Pipelines allow us to describe our processing as a series of
operations, each consuming and emitting a collection.

### Mechanics

- Create a new variable for the loop's collection.
- Starting at the top, take each bit of behavior in the loop and replace it with
  a collection pipeline operation in the derivation of the loop collection
  variable. Test after each change.
- Once all behavior is removed from the loop, remove it.

### Example

[replace_loop_with_pipeline.js](replace_loop_with_pipeline.js)

## Remove Dead Code

```js
if (false) {
  doSomethingThatUsedToMatter();
}

// refactored:
// empty
```

### Motivation

Unused code is a significant burden when trying to understand how the software
works. It doesn't carry any warning signs telling programmers that they can
ignore this function as it's never called any more, so they still have to spend
time understanding what it's doing and why changing it doesn't seem to alter the
output as they expected.

Once code isn't used any more, we should delete it.

### Mechanics

- If the dead code can be referenced from outside, e.g., when it's a full
  function, do a search to check for callers.
- Remove the dead code.
- Test.
