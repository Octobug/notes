# Unit Testing

## Test Double

> <https://en.wikipedia.org/wiki/Test_double>

A **test double** is a generic (meta) term used for these objects or procedures.

### Types of test doubles

There are at least five types of Test Doubles:

- **Test stub** — used for providing the tested code with "indirect input".
- **Mock object** — used for verifying "indirect output" of the tested code, by
  first defining the expectations before the tested code is executed.
- **Test spy** — used for verifying "indirect output" of the tested code, by
  asserting the expectations afterwards, without having defined the
  expectations before the tested code is executed. It helps in recording
  information about the indirect object created.
- **Fake object** — used as a simpler implementation, e.g. using an in-memory
  database in the tests instead of doing real database access.
- **Dummy object** — used when a parameter is needed for the tested method but
  without actually needing to use the parameter.

## Concepts/ Utils

[logrocket]: <https://blog.logrocket.com/unit-testing-node-js-applications-using-mocha-chai-and-sinon/>

> [Unit testing Node.js applications using Mocha, Chai, and Sinon][logrocket]

### Spy

- A spy is a fake function that keeps track of arguments, returns value, the
  value of this and exception is thrown (if any) for all its calls.

### Stub

- A stub is a spy with predetermined behavior.
- We can use a stub to:
  - Take a predetermined action, like throwing an exception
  - Provide a predetermined response
  - Prevent a specific method from being called directly (especially wfhen it
    triggers undesired behaviors like HTTP requests)

### Mock

- A mock is a fake function (like a spy) with pre-programmed behavior (like a
  stub) as well as pre-programmed expectations.
- We can use a mock to:
  - Verify the contract between the code under test and the external methods
    that it calls
  - Verify that an external method is called the correct number of times
  - Verify an external method is called with the correct parameters
- The rule of thumb for a mock is: if you are not going to add an assertion for
  some specific call, don’t mock it. Use a stub instead.
