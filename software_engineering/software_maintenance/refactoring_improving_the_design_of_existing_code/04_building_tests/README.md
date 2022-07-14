# Chapter 4: Building Tests

- [Chapter 4: Building Tests](#chapter-4-building-tests)
  - [The Value of Self-Testing Code](#the-value-of-self-testing-code)
  - [Sample Code to Test](#sample-code-to-test)
  - [A First Test](#a-first-test)
  - [Add Another Test](#add-another-test)
  - [Modifying the Fixture](#modifying-the-fixture)
  - [Probing the Boundaries](#probing-the-boundaries)
  - [Much More Than This](#much-more-than-this)

## The Value of Self-Testing Code

💡 Make sure all tests are fully automatic and that they check their own
results.

💡 A suite of tests is a powerful bug detector that decapitates the time it
takes to find bugs.

TDD (Test-Driven Development) approach to programming relies on short cycles
(test-code-refactor) of writing a (failing) test, writing the code to make that
test work, and refactoring to ensure the result is as clean as possible.

## Sample Code to Test

[sample.js](sample.js)

## A First Test

💡 Always make sure a test will fail when it should.

💡 Run tests frequently. Run those exercising the code you're working on at
least every few minutes; run all test at least daily.

## Add Another Test

> ⚠️ Testing should be risk-driven; remember, I'm trying to find bugs, now or
> in the future. Therefore I don't trst accessors that just read and write a
> field: They are so simple that I'm not likely to find a bug there.

💡 It is better to write and run incomplete tests than not to run complete
tests.

⚠️ A shared fixture which causes tests to interact will end up with
intermittent test failures due to tests interacting through the shared fixture.

## Modifying the Fixture

Testing phases:

- `setup-exercise-verify`
- `given-when-then`
- `arrange-act-assert`

## Probing the Boundaries

It's good to throw tests at the boundaries of these conditions -- to see what
happens when things might go wrong.

💡 Think of the boundary conditions under which things might go wrong and
concentrate your tests there.

💡 Don't let the fear that testing can't catch all bugs stop you from writing
tests that catch most bugs.

You should concentrate on where the risk is. Look at the code and see where it
becomes complex. Look at a function and consider the likely areas of error.

## Much More Than This

💡 When you get a bug report, start by writing a unit test that exposes the bug.
