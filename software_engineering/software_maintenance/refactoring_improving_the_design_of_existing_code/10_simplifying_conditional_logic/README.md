# Chapter 10: Simplifying Conditional Logic

- [Chapter 10: Simplifying Conditional Logic](#chapter-10-simplifying-conditional-logic)
  - [Decompose Conditional](#decompose-conditional)
    - [Motivation](#motivation)
    - [Mechanics](#mechanics)
    - [Example](#example)
  - [Consolidate Conditional Expression](#consolidate-conditional-expression)

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

>>>>> progress
