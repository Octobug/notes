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

>>>>> progress
