# Chapter 10: Simplifying Conditional Logic

- [Chapter 10: Simplifying Conditional Logic](#chapter-10-simplifying-conditional-logic)
  - [Decompose Conditional](#decompose-conditional)
    - [Motivation](#motivation)
    - [Mechanics](#mechanics)
    - [Example](#example)
  - [Consolidate Conditional Expression](#consolidate-conditional-expression)
    - [Motivation](#motivation-1)
    - [Mechanics](#mechanics-1)
    - [Example](#example-1)
    - [Example: Using `ands`](#example-using-ands)
  - [Replace Nested Conditional with Guard Clauses](#replace-nested-conditional-with-guard-clauses)
    - [Motivation](#motivation-2)
    - [Mechanics](#mechanics-2)
    - [Example](#example-2)
    - [Example: Reversing the Conditions](#example-reversing-the-conditions)
  - [Replace Conditional with Polymorphism](#replace-conditional-with-polymorphism)
    - [Motivation](#motivation-3)
    - [Mechanics](#mechanics-3)
    - [Example](#example-3)
    - [Example: Using Polymorphism for Variation](#example-using-polymorphism-for-variation)
  - [Introduce Special Case](#introduce-special-case)
    - [Motivation](#motivation-4)
    - [Mechanics](#mechanics-4)
    - [Example](#example-4)
    - [Example: Using an Object Literal](#example-using-an-object-literal)
    - [Example: Using a Transform](#example-using-a-transform)
  - [Introduce Assertion](#introduce-assertion)
    - [Motivatoin](#motivatoin)
    - [Mechanics](#mechanics-5)
    - [Example](#example-5)

## Decompose Conditional

```js
if (!aDate.isBefore(plan.summerStart) && !aDate.isAfter(plan.summerEnd)) {
  charge = quantity * plan.summerRate;
} else {
  charge = quantity * plan.regularRate + plan.regularServiceCharge;
}

// refactored:
if (summer()) {
  charge = summerCharge();
} else {
  charge = regularCharge();
}
```

### Motivation

As with any large block of code, we can make our intention clearer by
decomposing it and replacing each chunk of code with a function call named after
the intention of that chunk.

With conditions, doing this for the conditional part and each of the
alternatives highlight the condition and make it clear.

### Mechanics

- Apply `Extract Function` on the condition and each leg of the conditional.

### Example

[decompose_conditional.js](decompose_conditional.js)

## Consolidate Conditional Expression

```js
if (anEmployee.seniority < 2) return 0;
if (anEmployee.monthsDisabled > 12) return 0;
if (anEmployee.isPartTime) return 0;

// refactored:
if (isNotEligibleForDisability()) return 0;

function isNotEligibleForDisability() {
  return ((anEmployee.seniority < 2)
    || (anEmployee.monthDisabled > 12)
    || (anEmployee.isPartTime));
}
```

### Motivation

Consolidating the conditional code is important for two reasons. First, it makes
it clearer by showing that there is a single check that combines other checks.
The second reason is that it often sets up fot `Extract Function`.

### Mechanics

- Ensure that none of the conditionals have any side effects.
- Take two of the conditional statements and combine their condition using a
  logical operator.
- Test.
- Repeat combining conditionals until they are all in a single condition.
- Consider using `Extract Function` on the resulting condition.

### Example

[consolidate_conditional_expression.js](consolidate_conditional_expression.js)

### Example: Using `ands`

[using_ands.js](using_ands.js)

## Replace Nested Conditional with Guard Clauses

```js
function getPayAmount() {
  let result;
  if (isDead) {
    result = deadAmount();
  } else {
    if (isSeparated) {
      result = separatedAmount();
    } else {
      if (isRetired) {
        result = retiredAmount();
      } else {
        result = normalPayAmount();
      }
    }
  }
  return result;
}

// refactored:
function getPayAmount() {
  if (isDead) return deadAmount();
  if (isSeparated) return separatedAmount();
  if (isRetired) return retiredAmount();
  return normalPayAmount();
}
```

### Motivation

Conditional expressions come in two styles. In the first styles, both legs of
the conditional are part of normal behavior, while in the second style, one leg
is normal and the other indicates an unusual condition.

These kinds of conditionals have different intentions. If both are part of
normal behavior, use a condition with an `if` and an `else` leg. If the
condition is an unusual condition, check the condition and return if it's true.
The immediate return type is often called a **guard clause**.

Clarity is the key priciple: If the method is clearer with one exit point, use
one exit point; otherwise don't.

### Mechanics

- Select outermost condition that needs to be replaced, and change it into a
  guard clause.
- Test.
- Repeat as needed.
- If all the guard clauses return the same result, use
  `Consolidate Conditional`.

### Example

[replace_nested_conditional_with_guard_clauses.js](replace_nested_conditional_with_guard_clauses.js)

### Example: Reversing the Conditions

[reversing_the_conditions.js](reversing_the_conditions.js)

## Replace Conditional with Polymorphism

```js
switch (bird.type) {
  case 'EuropeanSwallow':
    return "average";
  case 'AfricanSwallow':
    return (bird.numberOfCoconuts > 2) ? "tired" : "average";
  case 'NorwegianBlueParrot':
    return (bird.voltage > 100) ? "scorched" : "beautiful";
  default:
    return "unknown";
}

// refactored:
class EuropeanSwallow {
  get plumage() {
    return "average";
  }
}

class AfricanSwallow {
  get plumage() {
    return (this.numberOfCoconuts > 2) ? "tired" : "average";
  }
}

class NorwegianBlueParrot {
  get plumage() {
    return (this.voltage > 100) ? "scorched" : "beautiful";
  }
}
```

### Motivation

Using classes and polymorphism can make the conditional separation more
explicit.

Duplication of common switch logic could be replaced by creating classes for
each case and using polymorphism to bringg out the type-specific behavior.

### Mechanics

- If classes do not exist for polymorphic behavior, create them together with a
  factory function to return the correct instance.
- Use the factory function in calling code.
- Move the conditional function to the superclass.
  
  If the conditional logic is not a self-contained function, use
  `Extract Function` to make it so.

- Pick one of the subclasses. Create a subclass method that overrides the
  conditional statement method. Copy the body of that leg of the conditional
  statement into the subclass method and adjust it to fit.
- Repeat for each leg of the conditional.
- Leave a default case for the superclass method. Or, if superclass should be
  abstract, declare that method as abstract or throw an error to show it should
  be the responsibility of a subclass.

### Example

[replace_conditional_with_polymorphism.js](replace_conditional_with_polymorphism.js)

### Example: Using Polymorphism for Variation

[using_polymorphism_for_variation_v1.js](using_polymorphism_for_variation_v1.js)

## Introduce Special Case

```js
if (aCustomer === "unknown") {
  customerName = "occupant";
}

// refactored:
class UnknownCustomer {
  get name() {
    return "occupant";
  }
}
```

### Motivation

A common case of duplicated code is when many users of a data structure check a
specific value, and then most of them do the same thing.

A good mechanism for this is the `Special Case` pattern where a special-case
element captures all the common behavior. This allows us to replace most of the
special-case checks with simple calls.

A common value that needs special-case processing is null, which is why this
pattern is often called the `Null Object` pattern. `Null Object` is a special
case of `Special Case`.

### Mechanics

- Add a special-case check property to the subject, returning `false`.
- Create a special-case object with only the special-case check property,
  returning `true`.
- Apply `Extract Function` to the special-case comparison code. Ensure that all
  clients use the new function instead of directly comparing it.
- Introduce the new special-case subject into the code, either by returning it
  from a function call or by applying a transform function.
- Change the body of the special-case comparison function so that it uses the
  special-case check property.
- Test.
- Use `Combine Functions into Class` or `Combine Functions into Transform` to
  move all of the common special-case behavior into the new element.
- Use `Inline Function` on the special-case comparison function for the places
  where it’s still needed.

### Example

[introduce_special_case_v1.js](introduce_special_case_v1.js)

### Example: Using an Object Literal

[using_an_object_literal.js](using_an_object_literal.js)

### Example: Using a Transform

[using_a_transform.js](using_a_transform.js)

## Introduce Assertion

```js
if (this.discountRate) {
  base = base - (this.discountRate * base);
}

// refactored:
assert(this.discountRate >= 0);
if (this.discountRate) {
  base = base - (this.discountRate * base);
}
```

### Motivatoin

An object may require that at least one of a group of fields has a value in it.
Such assumptions are often not stated but can only be deduced by looking through
an algorithm. Sometimes, the assumptions are stated with a comment. A better
technique is to make the assumption explicit by writing an assertion.

An assertion is a conditional statement that is assumed to be always true.
Failure of an assertion indicates a programmer error. Assertion failures should
never be checked by other parts of the system. (**This means, assertions are
used to warn the programmers, not the program users.**).

Assertions should be written so that the program functions equally correctly if
they are all removed; indeed, some languages provide assertions that can be
disabled by a compile-time switch.

Using assertion to find errors is certainly a good thing. And assertions are a
valuable form of communication -- they tell the reader something about the
assumed state of the program at this point of execution.

### Mechanics

- When you see that a condition is assumed to be true, add an assertion to
  state it.

### Example

[introduce_assertion.js](introduce_assertion.js)
