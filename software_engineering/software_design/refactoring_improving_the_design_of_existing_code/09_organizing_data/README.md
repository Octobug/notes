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
    - [Mechanics](#mechanics-2)
    - [Example](#example-1)
    - [Example: More Than One Source](#example-more-than-one-source)
  - [Change Reference to Value](#change-reference-to-value)
    - [Motivation](#motivation-3)
    - [Mechanics](#mechanics-3)
    - [Example](#example-2)
  - [Change Value to Reference](#change-value-to-reference)
    - [Motivation](#motivation-4)
    - [Mechanics](#mechanics-4)
    - [Example](#example-3)

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

One of the biggest sources of problems in software is mutable data. The scope
of mutable data should be minimized as much as possible.

### Mechanics

- Identify all points of update for the variable. If necessary, use
  `Split Variable` to separate each point of update.
- Create a function that calculates the value of the variable.
- Use `Introduce Assertion` to assert that the variable and the calculation
  give the same result whenever the variable is used.
- Test.
- Replace any reader of the variable with a call to the new function.
- Test.
- Apply `Remove Dead Code` to the declaration and updates to the variable.

### Example

[replace_derived_variable_with_query.js](replace_derived_variable_with_query.js)

### Example: More Than One Source

[more_than_one_source.js](more_than_one_source.js)

## Change Reference to Value

```js
class Product {
  applyDiscount(arg) { this._price.amount -= arg; }
}

// refactored:
class Product {
  applyDiscount(arg) {
    this._price = new Money(this._price.amount - arg, this._price.currency);
  }
}
```

### Motivation

The inner object, within another object or data structure, can be treated as a
reference or as a value. If it is treated as a reference, its property will be
updated keeping the original object. If it is treated as a value, it will be
entirely replaced with a new object that has the desired property.

Value objects are generally easier to reason about, particularly because they
are immutable. In general, immutable data structures are easier to deal with.
We can pass an immutable data value out to other parts of the program and not
worry that it might change without the enclosing object being aware of the
change. We can replicate values around the program and not worry about
maintaining memory links.

Value objects are especially useful in distributed and concurrent systems.

### Mechanics

- Check that the candidate class is immutable or can become immutable.
- For each setter, apply `Remove Setting Method`.
- Provide a value-based equality method that uses the fields of the value
  object.

### Example

[change_reference_to_value.js](change_reference_to_value.js)

## Change Value to Reference

```js
let customer = new Customer(customerData);

// refactored:
let customer = customerRepository.get(customerData.id);
```

### Motivation

A data structure may have several records linked to the same logical data
structure. When we have sharing like this, we can represent it by treating the
record either as a value or as a reference.

With a value, the object data is copied into each record within a collective
object; with a reference, there is only one data structure that multiple records
link to.

The biggest difficulty in having physical copies of the same logical data occurs
when we need to update the shared data. We have to find all the copies and
update them all. If any one of them is missed, we will get a troubling
inconsistency in this data.

In this case, it's often worthwhile to change the copied data into a single
reference. That way, any change is visible to all the records that reference
the object.

Changing a value to a reference results in only one object being present for an
entity, and it usually means that we need some kind of repository where we can
access these objects. In such situation, we only create the object for an entity
onece, and everywhere else we retrieve it from the repository.

### Mechanics

- Create a repository for instances of the related object (if one isn't already
  present).
- Ensure the constructor has a way of looking up the correct instance of the
  related object.
- Change the constructors for the host object to use the repository to obtain
  the related object. Test after each change.

### Example

[change_value_to_reference.js](change_value_to_reference.js)
