# Chapter 11: Refactoring APIs

- [Chapter 11: Refactoring APIs](#chapter-11-refactoring-apis)
  - [Separate Query from Modifier](#separate-query-from-modifier)
    - [Motivation](#motivation)
    - [Mechanics](#mechanics)
    - [Example](#example)
  - [Parameterize Function](#parameterize-function)
    - [Motivation](#motivation-1)
    - [Mechanics](#mechanics-1)
    - [Example](#example-1)
  - [Remove Flag Argument](#remove-flag-argument)
    - [Motivation](#motivation-2)
    - [Mechanics](#mechanics-2)
    - [Example](#example-2)
  - [Preserve Whole Object](#preserve-whole-object)
    - [Motivation](#motivation-3)
    - [Mechanics](#mechanics-3)
    - [Example](#example-3)
    - [Example: A Variation to Create the New Function](#example-a-variation-to-create-the-new-function)
  - [Replace Parameter with Query](#replace-parameter-with-query)
    - [Motivation](#motivation-4)
    - [Mechanics](#mechanics-4)
    - [Example](#example-4)
  - [Replace Query with Parameter](#replace-query-with-parameter)
    - [Motivation](#motivation-5)
    - [Mechanics](#mechanics-5)
    - [Example](#example-5)
  - [Remove Setting Method](#remove-setting-method)
    - [Motivation](#motivation-6)
    - [Mechanics](#mechanics-6)
    - [Example](#example-6)
  - [Replace Constructor with Factory Function](#replace-constructor-with-factory-function)
    - [Mechanics](#mechanics-7)
    - [Example](#example-7)
  - [Replace Function with Command](#replace-function-with-command)
    - [Motivation](#motivation-7)
    - [Mechanics](#mechanics-8)
    - [Example](#example-8)
  - [Replace Command with Function](#replace-command-with-function)
    - [Motivation](#motivation-8)
    - [Mechanics](#mechanics-9)
    - [Example](#example-9)

## Separate Query from Modifier

```js
function getTotalOutstandingAndSendBill() {
  const result = customer.invoices
    .reduce((total, each) => each.amount + total, 0);
  sendBill();
  return result;
}

// refactored:
function totalOutstanding() {
  return customer.invoices.reduce((total, each) => each.amount + total, 0);
}
function sendBill() {
  emailGateway.send(formatBill(customer));
}
```

### Motivation

It is a good idea to clearly signal the difference between functions with side
effects and those without. A good rule to follow is that any function that
returns a value should not have observable side effects -- the command-query
separation.

### Mechanics

- Copy the function, name it as a query.
- Remove any side effects from the new query function.
- Run static checks.
- Find each call of the original method. If that call uses the return value,
  replace the original call with a call to the query and insert a call to the
  original method below it. Test after each change.
- Remove return values from original.
- Test.

### Example

[separate_query_from_modifier.js](separate_query_from_modifier.js)

## Parameterize Function

```js
function tenPercentRaise(aPerson) {
  aPerson.salary = aPerson.salary.multiply(1.1);
}
function fivePercentRaise(aPerson) {
  aPerson.salary = aPerson.salary.multiply(1.05);
}

// refactored:
function raise(aPerson, factor) {
  aPerson.salary = aPerson.salary.multiply(1 + factor);
}
```

### Motivation

Use parameters to replace literal values.

### Mechanics

- Select one of the similar methods.
- Use `Change Function Declaration` to add any literals that need to turn into
  parameters.
- For each caller of the function, add the literal value.
- Test.
- Change the body of the function to use the new parameters. Test after each
  change.
- For each similar function, replace the call with a call to the parameterized
  function. Test after each one.

### Example

[parameterize_function.js](parameterize_function.js)

## Remove Flag Argument

```js
function setDimension(name, value) {
  if (name === "height") {
    this._height = value;
    return;
  }
  if (name === "width") {
    this._width = value;
    return;
  }
}

// refactored:
function setHeight(value) { this._height = value; }
function setWidth (value) { this._width = value; }
```

### Motivation

Flag arguments complicate the process of understanding what function calls are
available and how to call them. To be a flag argument, the callers must be
setting the boolean value to a literal value, not data that's flowing through
the program. The implementation function must be using the argument to influence
its control flow, not as data that it passes to further functions.

Removing flag arguments doesn't just keep the code clearer -- it also helps the
tooling. Code analysis tools can now more easily see the difference between
calling each logic.

### Mechanics

- Create an explicit function for each value of the parameter.
  - If the main function has a clear dispatch conditional, use
    `Decompose Conditional` to create the explicit functions.
  - Otherwise, create wrapping functions.
- For each caller that uses a literal value for the parameter, replace it with
  a call to the explicit function.

### Example

[remove_flag_argument.js](remove_flag_argument.js)

## Preserve Whole Object

```js
const low = aRoom.daysTempRange.low;
const high = aRoom.daysTempRange.high;
if (aPlan.withinRange(low, high)) {
  // 
}

// refactored:
if (aPlan.withinRange(aRoom.daysTempRange)) {
  // 
}
```

### Motivation

Passing the whole record handles change better should the called function need
more data from the whole in the future -- that change would not require to alter
the parameter list.

It also reduces the size of the parameter list, which usually makes the function
call easier to understand.

### Mechanics

- Create an empty function with the desired parameters.
- Fill the body of the new function with a call to the old function, mapping
  from the new parameters to the old ones.
- Run static checks.
- Adjust each caller to use the new function, testing after each change.
- Once all original callers have been changed, use `Inline Function` on the
  original function.
- Change the name of the new function and all its callers.

### Example

[preserve_whole_object.js](preserve_whole_object.js)

### Example: A Variation to Create the New Function

[a_variation_to_create_the_new_function.js](a_variation_to_create_the_new_function.js)

## Replace Parameter with Query

```js
availableVacation(anEmployee, anEmployee.grade);
function availableVacation(anEmployee, grade) {
  // calculate vacation...
}

// refactored:
availableVacation(anEmployee);
function availableVacation(anEmployee) {
  const grade = anEmployee.grade;
  // calculate vacation...
}
```

### Motivation

The parameter list to a function should summarize the points of variability of
that function, indicating the primary ways in which that function may behave
differently. It's good to avoid any duplication, and it's easier to understand
if the parameter list is short.

### Mechanics

- If necessary, use `Extract Function` on the calculation of the parameter.
- Replace references to the parameter in the function body with references to
  the expression that yields the parameter. Test after each change.
- Use `Change Function Declaration` to remove the parameter.

### Example

[replace_parameter_with_query.js](replace_parameter_with_query.js)

## Replace Query with Parameter

```js
targetTemperature(aPlan);

function targetTemperature(aPlan) {
  currentTemperature = thermostat.currentTemperature;
  // rest of function...
}

// refactored:
targetTemperature(aPlan, thermostat.currentTemperature);

function targetTemperature(aPlan, currentTemperature) {
  // rest of function...
}
```

### Motivation

References to something such as a global variable in the function's scope are
better to be moved away.

A function that will always give the same result when called with same parameter
values -- this is called **referential transparency**. If a function accesses
some element in its scope that isn’t referentially transparent, then the
containing function also lacks referential transparency.

### Mechanics

- Use `Extract Variable` on the query code to separate it from the rest of the
  function body.
- Apply `Extract Function` to the body code that isn’t the call to the query.
- Use `Inline Variable` to get rid of the variable you just created.
- Apply `Inline Function` to the original function.
- Rename the new function to that of the original.

### Example

[replace_query_with_parameter.js](replace_query_with_parameter.js)

## Remove Setting Method

```js
class Person {
  get name() {...}
  set name(aString) {...}
}

// refactored:
class Person {
  get name() {...}
}
```

### Motivation

Providing a setting method indicates that a field may be changed. Removing the
setting method makes it clear that updates make no sense after construction.

### Mechanics

- If the value that’s being set isn’t provided to the constructor, use
  `Change Function Declaration` to add it. Add a call to the setting method
  within the constructor.
- Remove each call of a setting method outside of the constructor, using the
  new constructor value instead. Test after each one.
- Use `Inline Function` on the setting method. Make the field immutable if
  possible.
- Test.

### Example

[remove_setting_method.js](remove_setting_method.js)

## Replace Constructor with Factory Function

```js
leadEngineer = new Employee(document.leadEngineer, 'E');

// refactored:
leadEngineer = createEngineer(document.leadEngineer);
```

### Mechanics

- Create a factory function, its body being a call to the constructor.
- Replace each call to the constructor with a call to the factory function.
- Test after each change.
- Limit the constructor’s visibility as much as possible.

### Example

[replace_constructor_with_factory_function.js](replace_constructor_with_factory_function.js)

## Replace Function with Command

```js
function score(candidate, medicalExam, scoringGuide) {
  let result = 0;
  let healthLevel = 0;
  // long body code
}

// refactored:
class Scorer {
  constructor(candidate, medicalExam, scoringGuide) {
    this._candidate = candidate;
    this._medicalExam = medicalExam;
    this._scoringGuide = scoringGuide;
  }

  execute() {
    this._result = 0;
    this._healthLevel = 0;
    // long body code
  }
}
```

### Motivation

There are times when it's useful to encapsulate a function into its own object,
which is refered to as a "command object" or simply a **command**.

A command offers a greater flexibility for the control and expression of a
function than the plain function mechanism.

Command objects provide a powerful mechanism for handling complex computations.

### Mechanics

- Create an empty class for the function. Name it based on the function.
- Use `Move Function` to move the function to the empty class.
  - Follow any convention the language has for naming commands. If there is no
    convention, choose a generic name for the command’s execute function, such
    as `execute` or `call`.
- Consider making a field for each argument, and move these arguments to the
  constructor.

### Example

[replace_function_with_command.js](replace_function_with_command.js)

## Replace Command with Function

```js
class ChargeCalculator {
  constructor (customer, usage) {
    this._customer = customer;
    this._usage = usage;
  }
  execute() {
    return this._customer.rate * this._usage;
  }
}

// refactored:
function charge(customer, usage) {
  return customer.rate * usage;
}
```

### Motivation

If the function isn't too complex, then a command object is more trouble than
its worth and should be turned into a regular function.

### Mechanics

- Apply `Extract Function` to the creation of the command and the call to the
  command’s execution method.
- For each method called by the command’s execution method, apply
  `Inline Function`.
  - If the supporting function returns a value, use `Extract Variable` on the
    call first and then `Inline Function`.
- Use `Change Function Declaration` to put all the parameters of the
  constructor into the command’s execution method instead.
- For each field, alter the references in the command’s execution method to use
  the parameter instead. Test after each change.
- Inline the constructor call and command’s execution method call into the
  caller (which is the replacement function).
- Test.
- Apply `Remove Dead Code` to the command class.

### Example

[replace_command_with_function.js](replace_command_with_function.js)
