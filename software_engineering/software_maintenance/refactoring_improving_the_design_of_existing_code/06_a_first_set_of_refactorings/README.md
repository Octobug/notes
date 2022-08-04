# Chapter 6: A First Set of Refactorings

- [Chapter 6: A First Set of Refactorings](#chapter-6-a-first-set-of-refactorings)
  - [Extract Function](#extract-function)
    - [Motivation](#motivation)
    - [Mechanics](#mechanics)
    - [Example: No Variables Out of Scope](#example-no-variables-out-of-scope)
    - [Example: Using Local Variables](#example-using-local-variables)
    - [Example: Reassigning a Local Variable](#example-reassigning-a-local-variable)
  - [Inline Function](#inline-function)
    - [Motivation](#motivation-1)
    - [Mechanics](#mechanics-1)
    - [Example](#example)
  - [Extract Variable](#extract-variable)
    - [Motivation](#motivation-2)
    - [Mechanics](#mechanics-2)
    - [Example](#example-1)
    - [Example: With a Class](#example-with-a-class)
  - [Inline Variable](#inline-variable)
    - [Motivation](#motivation-3)
    - [Mechanics](#mechanics-3)
  - [Change Function Declaration](#change-function-declaration)
    - [Motivation](#motivation-4)
    - [Mechanics](#mechanics-4)
      - [Simple Mechanics](#simple-mechanics)
      - [Migration Mechanics](#migration-mechanics)
    - [Example: Renaming a Function (Simple Mechanics)](#example-renaming-a-function-simple-mechanics)
    - [Example: Renaming a Function (Migration Mechanics)](#example-renaming-a-function-migration-mechanics)
    - [Example: Adding a Parameter](#example-adding-a-parameter)
    - [Example: Changing a Parameter to One of Its Properties](#example-changing-a-parameter-to-one-of-its-properties)
  - [Encapsulate Variable](#encapsulate-variable)
    - [Motivation](#motivation-5)
    - [Mechanics](#mechanics-5)
    - [Example](#example-2)
      - [Encapsulating the Value](#encapsulating-the-value)
  - [Rename Variable](#rename-variable)
    - [Motivation](#motivation-6)
    - [Mechanics](#mechanics-6)
    - [Example](#example-3)
      - [Renaming a Constant](#renaming-a-constant)
  - [Introduce Parameter Object](#introduce-parameter-object)

## Extract Function

Inverse of: `Inline Function`

```js
function printOwing(invoice) {
  printBanner();
  let outstanding = calculateOutstanding();

  // print details
  console.log(`name: ${invoice.customer}`);
  console.log(`amount: ${outstanding}`);
}

// refactored:
function printOwing(invoice) {
  printBanner();
  let outstanding = calculateOutstanding();
  printDetails(outstanding);

  function printDetails(outstanding) {
    console.log(`name: ${invoice.customer}`);
    console.log(`amount: ${outstanding}`);
  }
}
```

### Motivation

Arguments:

- 👌🏻 Functions should be no larger than fit on a screen.
- 👌🏻 Any code used more than once should be put in its own function, but code
  used once should be left inline.
- 👍🏻 The separation between **intention** and **implementation**. There is a
  big distance between the intention of the code and its implementation.

If you have to spend effort looking at a fragment of code and figuring out
"what" it's doing, then you should extract it into a function and name the
function after the "what".

The comment is often a good hint for the name of the function that is to be
extracted.

### Mechanics

- Create a new function, and name it after the intent of the function.
  - If the code is very simple, such as a single function call, it still
    should be extracted ig the name of the new function will reveal the intent
    of the code in a better way.
- Copy the extracted code from the source function into the new target function.
- Scan the extracted code for references to any variables that are local in
  scope to the source function and will not be in scope for the extracted
  function. Pass them as parameters.
- Compile after all variables are dealt with.
- Replace the extracted code in the source function with a call to the target
  function.
- Test.
- Look for other code that's the same or similar to the code just extracted, and
  consider using `Replacing Inline Code with Function Call` to call the new
  function.

### Example: No Variables Out of Scope

[extract_function.js #version1, #version2, #version3](extract_function.js)

### Example: Using Local Variables

The easiest case with local variables is when they are used but not assigned.
In this case, just pass them in as parameters.

[extract_function.js #version4, version5](extract_function.js)

### Example: Reassigning a Local Variable

> If I see an assignment to a parameter, I immediately use `Split Variable`,
> which turns it into a temp.

For temps that are assigned to, there are two cases:

1. The variable is a temporary variable used only within the extracted code.
2. The variable is used outside the extracted function. In this case, new value
   needs to be returned.

[extract_function.js #version6](extract_function.js)

**What happens if more than one variable needs to be returned?**

A function to return one value is preferred, so try to arrange for multiple
functions for different values.

If it really needs to extract with multiple values, just form a record and
returned it. But usually it is better to rework **the temporary variables**
first, with `Replace Temp with Query` and `Split Variable`.

## Inline Function

Inverse of: `Extract Function`

```js
function getRating(driver) {
  return moreThanFiveLateDeliveries(driver) ? 2 : 1;
}

function moreThanFiveLateDeliveries(driver) {
  return driver.numberOfLateDeliveries > 5;
}

// refactored:
function getRating(driver) {
  return (driver.numberOfLateDeliveries > 5) ? 2 : 1;
}
```

### Motivation

Sometimes the body of the function is as clear as the name, and this needless
indirection should be got rid of.

### Mechanics

- Check that this isn't a polymorphic method.
  - If this is a method in a class, and has subclasses that override it, then
    it can't be inlined.
- Find all the callers of the function.
- Replace each call with the function's body.
- Test after each replacement.
- Remove the function definition.

### Example

[inline_function.js #version1, #version2, #version3, #version4](inline_function.js)

## Extract Variable

Inverse of: `Inline Variable`

```js
return order.quantity * order.itemPrice -
  Math.max(0, order.quantity - 500) * order.itemPrice * 0.05 +
  Math.min(order.quantity * order.itemPrice * 0.1, 100);

// refactored:
const basePrice = order.quantity * order.itemPrice;
const quantityDiscount = Max.max(0, order.quantity - 500) * order.itemPrice * 0.05;
const shipping = Math.min(basePrice * 0.1, 100);
return basePrice - quantityDiscount + shipping;
```

### Motivation

Expressions can become very complex and hard to read. In such situations, local
variable may help break the expression down into something more manageable.

### Mechanics

- Ensure that the expression you want to extract does not have side effects.
- Declare an immutable variable. Set it to a copy of the expression you want to
  name.
- Replace the original expression with the new variable.
- Test.

### Example

[extract_variable.js #version1, #version2](extract_variable.js)

### Example: With a Class

[extract_variable.js #version3, #version4](extract_variable.js)

## Inline Variable

Inverse of: `Extract Variable`

```js
let basePrice = anOrder.basePrice;
return (basePrice > 1000);

// refactored:
return anOrder.basePrice > 1000;
```

### Motivation

Sometimes the name of a variable doesn't really communicate more than the
expression itself.

### Mechanics

- Check that the right-hand side of the assignment is free of side effects.
- If the variable isn't already declared immutable, do so and test.
- Find the first reference to the variable and replace it with the right-hand
  side of the assignment.
- Test.
- Repeat replacing references to the variable until you've replaced all of them.
- Remove the declaration and assignment of the variable.
- Test.

## Change Function Declaration

```js
function circum(radius) {...}

// refactored:
function circumference(radius) {...}
```

### Motivation

Bad functions make it harder to figure out what the software does and how to
modify it as needs change.

The most important element is the name of the function. A good name allows us
to understand what the function does.

The parameters of a function dictate how a function fits in with the rest of its
world.

### Mechanics

#### Simple Mechanics

- If you're removing a parameter, ensure it isn't referenced in the body of the
  function.
- Change the method declaration to the disired declaration.
- Find all references to the old method declaration, update them to the new one.
- Test.

#### Migration Mechanics

- If necessary, refactor the body of the function to make it easy to do the
  following extraction step.
- Use `Extract Function` on the function body to create the new function.
- If the extracted function needs additional parameters, use the simple
  mechanics to add them.
- Test.
- Apply `Inline Function` to the old function.
- If you used a temporary name, use `Change Function Declaration` again to
  restore it to the original name.
- Test.

### Example: Renaming a Function (Simple Mechanics)

[change_function_declaration.js #version1, #version2](change_function_declaration.js)

### Example: Renaming a Function (Migration Mechanics)

[change_function_declaration.js #version3, #version4](change_function_declaration.js)

### Example: Adding a Parameter

[change_function_declaration.js #version5, #version6, #version7, #version8](change_function_declaration.js)

### Example: Changing a Parameter to One of Its Properties

[change_function_declaration.js #version9, #version10, #version11, #version12](change_function_declaration.js)

## Encapsulate Variable

```js
let defaultOwner = { firstName: 'Martin', lastName: 'Fowler' };

// refactored:
let defaultOwnerData = { firstName: 'Martin', lastName: 'Fowler' };
export function defaultOwner() { return defaultOwnerData; }
export function setDefaultOwner(arg) { defaultOwnerData = arg; }
```

### Motivation

If we move data around, we have to change all the references to the data in a
single cycle to keep the code working.

So if we want to move widely accessed data, often the best approach is to first
encapsulate it by routing all its access through functions.

That way, we turn the difficult task of reorganizing data into the simpler task
of reorganizing functions.

Encapsulating data provides a clear point to monitor changes and use of the
data; We can easily add validation or consequential logic on the updates.
The greater the scope of the data, the more important it is to encapsulate.

Whenever the legacy code needs to be changed or added a new reference to such a
variable, we should take the opportunity to encapsulate it. That way we prevent
the increase of coupling to commonly used data.

This principle is why the object-oriented approach puts so much emphasis on
keeping an object's data peivate.

Keeping data encapsulated is much less important for immutable data.

### Mechanics

- Create encapsulating functions to access and update the variable.
- Run static checks
- For each reference to the variable, replace with a call to the appropriate
  encapsulating function. Test after each replacement.
- Restrict the visibility of the variable.
- Test
- If the value of the variable is a record, consider `Encapsulate Record`.

### Example

[encapsulate_variable.js #version1, #version2, #version3, #version4](encapsulate_variable.js)

#### Encapsulating the Value

[encapsulate_variable.js #version5, #version6, #version7](encapsulate_variable.js)

## Rename Variable

```js
let a = height * width;

// refactored:
let area = height * width;
```

### Motivation

The importance of a name depends on how widely it's used. Persistent fields
that last beyond a single function invocation require more careful naming.

### Mechanics

- If the variable is used widely, consider `Encapsulate Variable`.
- Find all reference to the variable, and change every one.
  - If there are references from another code base, the variable is a published
    variable, and you cannot do this refactoring.
  - If the variable does not change, you can copy it to one with the new name,
    then change gradually, testing after each change.
- Test.

### Example

[rename_variable.js #version1, #version2](rename_variable.js)

💡 If the variable is used widely enough that it should be encapsulted it in
order to change its name, it's worth keeping it encapsulated behind functions
for the future, rather than inlining the wrapping functions.

#### Renaming a Constant

[rename_variable.js #version3, #version4](rename_variable.js)

When renaming a constant, the rename can be done gradually by copying.
With the copy, its references can be gradually changed from the old name to the
new name.

## Introduce Parameter Object

>>>>> progress
