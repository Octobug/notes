# Testing Fundamentals

## Concepts/ Utils

### Spies

> Creates fake functions which we can use to track executions. This means we can
tell/ find out whether the function has been executed/ how many times its been
called etc. We can also use spies on existing functions and get the same
capability, to track those functions executions.
>
> Most of the time we'll probably not use spies but they are pretty useful to
test whether **callbacks** have been called and how many times they were called
during our code execution. Spies are the simplest to use in SinonJS and most
functionality is built on top of them.

### Stubs

> Enables us to replace functions. This gives us more control. We can return
whatever we want or have our functions work in a way that suites us to be able
to test multiple scenarios.
>
> * External calls which make tests slow and difficult to write (e.g HTTP
>   calls/ DB calls)
> * Triggering different outcomes for a piece of code (e.g. what happens if an
>   error is thrown/ if it passes)

### Mocks

> They are fake methods, that have pre-programmed behavior and pre-programmed
expectations.

### References

[mocha_chai_sino_2]: <https://blog.logrocket.com/unit-testing-node-js-applications-using-mocha-chai-and-sinon/>

* [Unit testing Node.js applications using Mocha, Chai, and Sinon][mocha_chai_sino_2]
