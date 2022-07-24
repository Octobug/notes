# Chapter 6: A First Set of Refactorings

- [Chapter 6: A First Set of Refactorings](#chapter-6-a-first-set-of-refactorings)
  - [Extract Function](#extract-function)
    - [Motivation](#motivation)
    - [Mechanics](#mechanics)
    - [Example: No Variables Out of Scope](#example-no-variables-out-of-scope)
    - [Example: Using Local Variables](#example-using-local-variables)
    - [Example: Reassigning a Local Variable](#example-reassigning-a-local-variable)
  - [Inline Function](#inline-function)
  - [Extract Variable](#extract-variable)
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

## Extract Variable

## Introduce Parameter Object

>>>>> progress
