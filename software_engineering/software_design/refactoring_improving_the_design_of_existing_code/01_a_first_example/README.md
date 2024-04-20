# Chapter 1: Refactoring: A First Example

- [Chapter 1: Refactoring: A First Example](#chapter-1-refactoring-a-first-example)
  - [The Starting Point](#the-starting-point)
  - [Comments on the Starting Program](#comments-on-the-starting-program)
  - [The First Step in Refactoring](#the-first-step-in-refactoring)
  - [Decomposing the `statement` Function](#decomposing-the-statement-function)
    - [Removing the `play` Variable](#removing-the-play-variable)
    - [Extracting Volume Credits](#extracting-volume-credits)
    - [Removing the `format` Variable](#removing-the-format-variable)
    - [Removing Total Volume Credits](#removing-total-volume-credits)
  - [Status: Lots of Nested Functions](#status-lots-of-nested-functions)
  - [Splitting the Phases of Calculation and Formatting](#splitting-the-phases-of-calculation-and-formatting)
  - [Status: Separated into Two Files (and Phases)](#status-separated-into-two-files-and-phases)
  - [Reorganizing the Calculations by Type](#reorganizing-the-calculations-by-type)
    - [Creating a Performance Calculator](#creating-a-performance-calculator)
    - [Moving Functions into the Calculator](#moving-functions-into-the-calculator)
    - [Making the Performance Calculator Polymorphic](#making-the-performance-calculator-polymorphic)
  - [Status: Creating the Data with the Polymorphic Calculator](#status-creating-the-data-with-the-polymorphic-calculator)
  - [Final Thoughts](#final-thoughts)

## The Starting Point

The code that prints the bill: [statement.v1.js](statement.v1.js)

## Comments on the Starting Program

⭐️ **When you have to add a feature to a program but the code is not structured
in a convenient way, first refactor the program to make it easy to add the
feature, then add the feature.**

**Refactorings**:

- `Building Tests`

## The First Step in Refactoring

⭐️ **Before you start refactoring, make sure you have a solid suite of tests.
These tests must be self-checking (test results that turned out differently).**

## Decomposing the `statement` Function

1. Look in the fragment for any variables that will no longer be in scope once
   they have been extracted into their own function.

    Extract `switch` as a Function: [statement.v2.switch.js](statement.v2.switch.js)

2. It's an important habit to test after every refactoring.

    ⭐️ **Refactoring changes the program in small steps, so if you make a
    mistake, it is easy to find where the bug is.**

3. After `Extract Function`, We can take a look at the new function to see if
   there are any quick and easy things we can do to clarify the extracted
   function: [statement.v3.clarify_func.js](statement.v3.clarify_func.js)

    ⭐️ **Any fool can write code that a computer can understand. Good
    programmers write code that humans can understand.**

**Refactorings**:

- `Extract Function`

### Removing the `play` Variable

[statement.v4.play.js](statement.v4.play.js)

**Refactorings**:

- `Replace Temp with Query`
- `Change Function Declaration`
- `Inline Variable`

### Extracting Volume Credits

[statement.v5.volume_credits.js](statement.v5.volume_credits.js)

### Removing the `format` Variable

[statement.v6.format.js](statement.v6.format.js)

**Refactorings**:

- `Change Function Declaration`

### Removing Total Volume Credits

[statement.v7.totol_credits.js](statement.v7.totol_credits.js)

**Refactorings**:

- `Split Loop`
- `Slide Statements`
- `Replace Temp with Query`
- `Extract Function`
- `Inline Variable`

Advice on performance with refactoring: ⭐️ **Most of the time you should ignore
it. If your refactoring introduces performance slow-downs, finish refactoring
first and do performance tuning afterwards**

## Status: Lots of Nested Functions

All the calculation logic has been moved out to a handful of supporting
functions. This makes it easier to understand each individual calculation as
well as the overall flow of the report.

## Splitting the Phases of Calculation and Formatting

[statement.v8.js](statement.v8.js)

**Refactorings**:

- `Extract Function`
- `Split Phase`
- `Move Function`
- `Replace Loop with Pipeline`

## Status: Separated into Two Files (and Phases)

⭐️ **When programming, follow the camping rule: Always leave the code base
healthier than when you found it.**

## Reorganizing the Calculations by Type

- [statement.v9.class.mjs](statement.v9.class.mjs)
- [statement.v9.createStatementData.mjs](statement.v9.createStatementData.mjs)

### Creating a Performance Calculator

### Moving Functions into the Calculator

### Making the Performance Calculator Polymorphic

**Refactorings**:

- `Replace Conditional with Polymorphism`
- `Change Function Declaration`
- `Move Function`
- `Inline Function`
- `Replace Type Code tieh Subclasses`
- `Replace Constructor with Factory Function`
- `Replace Conditional with Polymorphism`

## Status: Creating the Data with the Polymorphic Calculator

## Final Thoughts

Three major stages to this refactoring episode:

1. Decomposing the original function into a set of nested functions.
2. Using `Split Phase` to separate the calculation and printing code.
3. Introducing a polymorphic calculator for the calculation logic.

⭐️ **The tru test of good code is how easy it is to change it.**
