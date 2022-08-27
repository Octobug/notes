# Chapter 9: Organizing Data

- [Chapter 9: Organizing Data](#chapter-9-organizing-data)
  - [Split Variable](#split-variable)
    - [Motivation](#motivation)
    - [Mechanics](#mechanics)
    - [Example](#example)
    - [Example: Assigning to an Input Parameter](#example-assigning-to-an-input-parameter)
  - [Rename Field](#rename-field)
    - [Motivation](#motivation-1)
    - [Mechanics](#mechanics-1)
    - [Example: Renaming a Field](#example-renaming-a-field)
  - [Replace Derived Variable with Query](#replace-derived-variable-with-query)
    - [Motivation](#motivation-2)

## Split Variable

```js
let temp = 2 * (height + width);
console.log(temp);
temp = height * width;
console.log(temp);

// refactored:
const perimeter = 2 * (height + width);
console.log(perimeter);
const area = height * width;
console.log(area);
```

### Motivation

Many variables are used to hold the result of a long-winded bit of code for easy
reference later. These kinds of variables should be set only once. If they are
set more than once, it is a sign that they have more than one responsibility
within the method. Any variable with more than one responsibility should be
replaced with multiple variables, one for each responsibility. Using a variable
for two different things is very confusing for the reader.

### Mechanics

- Change the name of the variable at its declaration and first assignment.
- If possible, declare the new variable as immutable.
- Change all references of the variable up to its second **assignment**.
- Test.
- Repeat in stages, at each stage renaming the variable at the declaration and
  changing references until the next assignment, until you reach the final
  assignment.

### Example

[split_variable.js](split_variable.js)

### Example: Assigning to an Input Parameter

[assigning_to_an_input_parameter.js](assigning_to_an_input_parameter.js)

## Rename Field

```js
class Organization {
  get name() { ... }
}

// refactored:
class Organization {
  get title() { ... }
}
```

### Motivation

Data structures are the key to understanding what's going on. Since data
structures are so important, it's essential to keep them clear. Our
understanding of data improves the more we work on the software, so it's vital
that this improved understanding is embedded into the program.

Renaming field of class is just as important as with bare record structures.

### Mechanics

- If the record has limited scope, rename all accesses to the field and test;
  no need to do the rest of the mechanics.
- If the record isn't already encapsulated, apply `Encapsulate Record`.
- Rename the private field inside the object, adjust internal methods to fit.
- Test.
- If the constructor uses the name, apply `Chaneg Function Declaration` to
  rename it.
- Apply `Rename Function` to the accessors.

### Example: Renaming a Field

[renaming_a_field.js](renaming_a_field.js)

## Replace Derived Variable with Query

```js
get discountedTotal() { return this._discountedTotal; }
set discount(aNumber) {
  const old = this._discount;
  this._discount = aNumber;
  this._discountedTotal += old - aNumber;
}

// refactored:
get discountedTotal() { return this._baseTotal - this._discount; }
set discount(aNumber) { this._discount = aNumber; }
```

### Motivation

>>>>> progress
