# Chapter 6: A First Set of Refactorings

- [Chapter 6: A First Set of Refactorings](#chapter-6-a-first-set-of-refactorings)
  - [Extract Function](#extract-function)
    - [Motivation](#motivation)
    - [Mechanics](#mechanics)
    - [Example: No Variables Out of Scope](#example-no-variables-out-of-scope)

## Extract Function

- inverse of: `Inline Function`
- [extract_function.js](extract_function.js)

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

>>>>> progress
