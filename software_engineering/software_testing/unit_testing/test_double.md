# Test Double

> - <https://en.wikipedia.org/wiki/Test_double>

- [Test Double](#test-double)
  - [Types](#types)
  - [Concepts/ Tools](#concepts-tools)
    - [Fake](#fake)
      - [When to use fakes?](#when-to-use-fakes)
      - [Using fakes instead of spies](#using-fakes-instead-of-spies)
      - [Using fakes instead of stubs](#using-fakes-instead-of-stubs)
      - [Creating a fake](#creating-a-fake)
        - [Creating a fake without behavior](#creating-a-fake-without-behavior)
        - [Creating a fake with custom behaviour](#creating-a-fake-with-custom-behaviour)
      - [Fakes with behavior](#fakes-with-behavior)
        - [`sinon.fake.returns(value);`](#sinonfakereturnsvalue)
        - [`sinon.fake.throws(value);`](#sinonfakethrowsvalue)
        - [`sinon.fake.yields([value1, ..., valueN]);`](#sinonfakeyieldsvalue1--valuen)
        - [`sinon.fake.yieldsAsync([value1, ..., valueN]);`](#sinonfakeyieldsasyncvalue1--valuen)
      - [Instance properties](#instance-properties)
        - [`f.callback`](#fcallback)
        - [`f.firstArg`](#ffirstarg)
        - [`f.lastArg`](#flastarg)
      - [Adding the fake to the system under test](#adding-the-fake-to-the-system-under-test)
    - [Spy](#spy)
      - [What is a test spy?](#what-is-a-test-spy)
      - [Creating a spy as an anonymous function](#creating-a-spy-as-an-anonymous-function)
      - [Using a spy to wrap all object method](#using-a-spy-to-wrap-all-object-method)
        - [`sinon.spy(object)`](#sinonspyobject)
      - [Using a spy to wrap an existing method](#using-a-spy-to-wrap-an-existing-method)
      - [Using a spy to wrap property getter and setter](#using-a-spy-to-wrap-property-getter-and-setter)
    - [Stub](#stub)
      - [What are stubs?](#what-are-stubs)
      - [When to use stubs?](#when-to-use-stubs)
      - [Defining stub behavior on consecutive calls](#defining-stub-behavior-on-consecutive-calls)
        - [`stub.onCall(n);`](#stuboncalln)
        - [`stub.resetBehavior();`](#stubresetbehavior)
        - [`stub.callsFake(fakeFunction);`](#stubcallsfakefakefunction)
        - [`stub.callThrough();`](#stubcallthrough)
    - [Mock](#mock)
      - [What are mocks?](#what-are-mocks)
      - [When to use mocks?](#when-to-use-mocks)
      - [When to *not* use mocks?](#when-to-not-use-mocks)

## Types

A **test double** is a generic (meta) term used for these objects or procedures.

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

## Concepts/ Tools

> <https://sinonjs.org/releases/v13/>

### Fake

In Sinon, a `fake` is a `Function` that records arguments, return value, the
value of `this` and exception thrown (if any) for all of its calls.

A fake is immutable: once created, the behavior will not change.

Unlike `sinon.spy` and `sinon.stub` methods, the `sinon.fake` API knows only
how to create fakes, and doesn’t concern itself with plugging them into the
system under test. To plug the fakes into the system under test, you can use
the `sinon.replace*` methods.

#### When to use fakes?

Fakes are alternatives to the `Stubs` and `Spies`, and they can fully replace
all such use cases.

They are intended to be simpler to use, and avoids many bugs by having
immutable behaviour.

The created `fake` `Function`, with or without behavior has the same API as a
(`sinon.spy`)spies.

#### Using fakes instead of spies

```js
require("@fatso83/mini-mocha").install();
const sinon = require("sinon");
const referee = require("@sinonjs/referee");
const assert = referee.assert;

it("should be able to be used instead of spies", function () {
    const foo = {
        bar: () => "baz",
    };
    // wrap existing method without changing its behaviour
    const fake = sinon.replace(foo, "bar", sinon.fake(foo.bar));

    assert.equals(fake(), "baz"); // behaviour is the same
    assert.equals(fake.callCount, 1); // calling information is saved
});
```

#### Using fakes instead of stubs

```js
require("@fatso83/mini-mocha").install();
const sinon = require("sinon");
const referee = require("@sinonjs/referee");
const assert = referee.assert;

it("should be able to be used instead of stubs", function () {
    const foo = {
        bar: () => "baz",
    };
    // replace method with a fake one
    const fake = sinon.replace(foo, "bar", sinon.fake.returns("fake value"));

    assert.equals(fake(), "fake value"); // returns fake value
    assert.equals(fake.callCount, 1); // saves calling information
});
```

#### Creating a fake

##### Creating a fake without behavior

```js
require("@fatso83/mini-mocha").install();
const sinon = require("sinon");
const referee = require("@sinonjs/referee");
const assert = referee.assert;

it("should create fake without behaviour", function () {
    // create a basic fake, with no behavior
    const fake = sinon.fake();

    assert.isUndefined(fake()); // by default returns undefined
    assert.equals(fake.callCount, 1); // saves call information
});
```

##### Creating a fake with custom behaviour

```js
require("@fatso83/mini-mocha").install();
const sinon = require("sinon");
const referee = require("@sinonjs/referee");
const assert = referee.assert;

it("should create fake with custom behaviour", function () {
    // create a fake that returns the text "foo"
    const fake = sinon.fake.returns("foo");

    assert.equals(fake(), "foo");
});
```

#### Fakes with behavior

Fakes cannot change once created with behaviour.

##### `sinon.fake.returns(value);`

```js
require("@fatso83/mini-mocha").install();
const sinon = require("sinon");
const referee = require("@sinonjs/referee");
const assert = referee.assert;

it("should create a fake that 'returns'", function () {
    const fake = sinon.fake.returns("apple pie");

    assert.equals(fake(), "apple pie");
});
```

##### `sinon.fake.throws(value);`

```js
require("@fatso83/mini-mocha").install();
const sinon = require("sinon");
const referee = require("@sinonjs/referee");
const assert = referee.assert;

it("should create a fake that 'throws'", function () {
    const fake = sinon.fake.throws(new Error("not apple pie"));

    // Expected to throw an error with message 'not apple pie'
    assert.exception(fake, { name: "Error", message: "not apple pie" });
});
```

##### `sinon.fake.yields([value1, ..., valueN]);`

```js
require("@fatso83/mini-mocha").install();
const sinon = require("sinon");
const referee = require("@sinonjs/referee");
const assert = referee.assert;
const fs = require("fs");

it("should create a fake that 'yields'", function () {
    const fake = sinon.fake.yields(null, "file content");
    const anotherFake = sinon.fake();

    sinon.replace(fs, "readFile", fake);
    fs.readFile("somefile", (err, data) => {
        // called with fake values given to yields as arguments
        assert.isNull(err);
        assert.equals(data, "file content");
        // since yields is synchronous, anotherFake is not called yet
        assert.isFalse(anotherFake.called);

        sinon.restore();
    });

    anotherFake();
});
```

##### `sinon.fake.yieldsAsync([value1, ..., valueN]);`

```js
require("@fatso83/mini-mocha").install();
const sinon = require("sinon");
const referee = require("@sinonjs/referee");
const assert = referee.assert;
const fs = require("fs");

it("should create a fake that 'yields asynchronously'", function () {
    const fake = sinon.fake.yieldsAsync(null, "file content");
    const anotherFake = sinon.fake();

    sinon.replace(fs, "readFile", fake);
    fs.readFile("somefile", (err, data) => {
        // called with fake values given to yields as arguments
        assert.isNull(err);
        assert.equals(data, "file content");
        // since yields is asynchronous, anotherFake is called first
        assert.isTrue(anotherFake.called);

        sinon.restore();
    });

    anotherFake();
});
```

#### Instance properties

##### `f.callback`

```js
require("@fatso83/mini-mocha").install();
const sinon = require("sinon");
const referee = require("@sinonjs/referee");
const assert = referee.assert;

it("should have working callback", function () {
    const f = sinon.fake();
    const cb1 = function () {};
    const cb2 = function () {};

    f(1, 2, 3, cb1);
    f(1, 2, 3, cb2);

    assert.isTrue(f.callback === cb2);
    // spy call methods:
    assert.isTrue(f.getCall(1).callback === cb2);
    assert.isTrue(f.lastCall.callback === cb2);
});
```

##### `f.firstArg`

```js
require("@fatso83/mini-mocha").install();
const sinon = require("sinon");
const referee = require("@sinonjs/referee");
const assert = referee.assert;

it("should have working firstArg", function () {
    const f = sinon.fake();
    const date1 = new Date();
    const date2 = new Date();

    f(date1, 1, 2);
    f(date2, 1, 2);

    assert.isTrue(f.firstArg === date2);
});
```

##### `f.lastArg`

```js
require("@fatso83/mini-mocha").install();
const sinon = require("sinon");
const referee = require("@sinonjs/referee");
const assert = referee.assert;

it("should have working lastArg", function () {
    const f = sinon.fake();
    const date1 = new Date();
    const date2 = new Date();

    f(1, 2, date1);
    f(1, 2, date2);

    assert.isTrue(f.lastArg === date2);
    // spy call methods:
    assert.isTrue(f.getCall(0).lastArg === date1);
    assert.isTrue(f.getCall(1).lastArg === date2);
    assert.isTrue(f.lastCall.lastArg === date2);
});
```

#### Adding the fake to the system under test

Unlike `sinon.spy` and `sinon.stub`, `sinon.fake` only knows about creating
fakes, not about replacing properties in the system under test.

To replace a property, you can use the `sinon.replace` method. When you want to
restore the replaced properties, call the `sinon.restore` method.

```js
require("@fatso83/mini-mocha").install();
const sinon = require("sinon");
const referee = require("@sinonjs/referee");
const assert = referee.assert;

it("should be able to be added to the system under test", function () {
    const fake = sinon.fake.returns("42");

    sinon.replace(console, "log", fake);

    assert.equals(console.log("apple pie"), "42");

    // restores all replaced properties set by sinon methods (replace, spy, stub)
    sinon.restore();

    assert.isUndefined(console.log("apple pie"));
    assert.equals(fake.callCount, 1);
});
```

### Spy

#### What is a test spy?

A test spy is a function that records arguments, return value, the value of
`this` and exception thrown (if any) for all its calls. There are two types of
spies: Some are anonymous functions, while others wrap methods that already
exist in the system under test.

#### Creating a spy as an anonymous function

When the behavior of the spied-on function is not under test, you can use an
anonymous function spy. The spy won’t do anything except record information
about its calls. A common use case for this type of spy is testing how a
function handles a callback, as in the following simplified example:

```js
require("@fatso83/mini-mocha").install();
const sinon = require("sinon");
const PubSub = require("pubsub-js");
const referee = require("@sinonjs/referee");
const assertTrue = referee.assert;

describe("PubSub", function () {
    it("should call subscribers on publish", function () {
        const callback = sinon.spy();

        PubSub.subscribe("message", callback);
        PubSub.publishSync("message");

        assertTrue(callback.called);
    });
});
```

#### Using a spy to wrap all object method

##### `sinon.spy(object)`

Spies all the object’s methods.

Note that it’s usually better practice to spy individual methods, particularly
on objects that you don’t understand or control all the methods for (e.g.
library dependencies).

Spying individual methods tests intent more precisely and is less susceptible
to unexpected behavior as the object’s code evolves.

The following is a slightly contrived example:

```js
require("@fatso83/mini-mocha").install();

const sinon = require("sinon");
const referee = require("@sinonjs/referee");
const assert = referee.assert;

// This is just an example of an external library you might require()
const myExternalLibrary = {
  getJSON(url) {
      return this._doNetworkCall({ url: url, dataType: "json" });
  },
  _doNetworkCall(httpParams) {
      console.log("Simulating fetching stuff from the network: ", httpParams);
      return { result: 42 };
  },
};

describe("Wrap all object methods", function () {
  const sandbox = sinon.createSandbox();

  beforeEach(function () {
    sandbox.spy(myExternalLibrary);
  });

  afterEach(function () {
    sandbox.restore();
  });

  it(
    "should inspect the external lib's usage of its internal methods",
    function () {
      const url = "https://jsonplaceholder.typicode.com/todos/1";
      myExternalLibrary.getJSON(url);

      assert(myExternalLibrary.getJSON.calledOnce);
      assert(myExternalLibrary._doNetworkCall.calledOnce);
      assert.equals(
          url,
          myExternalLibrary._doNetworkCall.getCall(0).args[0].url
      );
      assert.equals(
          "json",
          myExternalLibrary._doNetworkCall.getCall(0).args[0].dataType
      );
    }
  );
});
```

#### Using a spy to wrap an existing method

`sinon.spy(object, "method")` creates a spy that wraps the existing function
`object.method`. The spy will behave exactly like the original method
(including when used as a constructor), but you will have access to data about
all calls. The following is a slightly contrived example:

```js
require("@fatso83/mini-mocha").install();

const sinon = require("sinon");
const referee = require("@sinonjs/referee");
const assert = referee.assert;
const jsdom = require("jsdom");
const JSDOM = jsdom.JSDOM;
const window = new JSDOM().window;
const document = new JSDOM("").window;
const jQuery = require("jquery")(window);
global.document = document;

describe("Wrap existing method", function () {
    const sandbox = sinon.createSandbox();

    beforeEach(function () {
        sandbox.spy(jQuery, "ajax");
    });

    afterEach(function () {
        sandbox.restore();
    });

    it("should inspect jQuery.getJSON's usage of jQuery.ajax", function () {
        const url = "https://jsonplaceholder.typicode.com/todos/1";
        jQuery.getJSON(url);

        assert(jQuery.ajax.calledOnce);
        assert.equals(url, jQuery.ajax.getCall(0).args[0].url);
        assert.equals("json", jQuery.ajax.getCall(0).args[0].dataType);
    });
});
```

#### Using a spy to wrap property getter and setter

```js
var object = {
  get test() {
    return this.property;
  },
  set test(value) {
    this.property = value * 2;
  },
};
var spy = sinon.spy(object, "test", ["get", "set"]);
object.test = 42;
assert(spy.set.calledOnce);
assert.equals(object.test, 84);
assert(spy.get.calledOnce);
```

### Stub

#### What are stubs?

Test stubs are functions (spies) with pre-programmed behavior.

They support the full test spy API in addition to methods which can be used to
alter the stub’s behavior.

As spies, stubs can be either anonymous, or wrap existing functions. When
wrapping an existing function with a stub, the original function is not called.

#### When to use stubs?

Use a stub when you want to:

1. Control a method’s behavior from a test to force the code down a specific
   path. Examples include forcing a method to throw an error in order to test
   error handling.
2. When you want to prevent a specific method from being called directly
   (possibly because it triggers undesired behavior, such as a XMLHttpRequest
   or similar).

The following example is yet another test from PubSubJS which shows how to
create an anonymous stub that throws an exception when called.

```js
require("@fatso83/mini-mocha").install();

const sinon = require("sinon");
const PubSub = require("pubsub-js");
const referee = require("@sinonjs/referee");
const assert = referee.assert;

describe("PubSub", function () {
    it("should call all subscribers, even if there are exceptions", function () {
        const message = "an example message";
        const stub = sinon.stub().throws();
        const spy1 = sinon.spy();
        const spy2 = sinon.spy();
        const clock = sinon.useFakeTimers();

        PubSub.subscribe(message, stub);
        PubSub.subscribe(message, spy1);
        PubSub.subscribe(message, spy2);

        assert.exception(() => {
            PubSub.publishSync(message, "some data");

            // PubSubJS reschedules exceptions using setTimeout(fn,0)
            // We have faked the clock, so just tick the clock to throw!
            clock.tick(1);
        });

        assert.exception(stub);
        assert(spy1.called);
        assert(spy2.called);
        assert(stub.calledBefore(spy1));

        clock.restore();
    });
});
```

#### Defining stub behavior on consecutive calls

Calling behavior defining methods like `returns` or `throws` multiple times
overrides the behavior of the stub. As of Sinon version 1.8, you can use the
`onCall` method to make a stub respond differently on consecutive calls.

##### `stub.onCall(n);`

Defines the behavior of the stub on the *nth* call. Useful for testing
sequential interactions.

```js
require("@fatso83/mini-mocha").install();

const sinon = require("sinon");
const referee = require("@sinonjs/referee");
const assert = referee.assert;

describe("stub", function () {
    it("should behave differently on consecutive calls", function () {
        const callback = sinon.stub();
        callback.onCall(0).returns(1);
        callback.onCall(1).returns(2);
        callback.returns(3);

        assert.equals(callback(), 1); // Returns 1
        assert.equals(callback(), 2); // Returns 2
        assert.equals(callback(), 3); // All following calls return 3
    });
});
```

There are methods `onFirstCall`, `onSecondCall`, `onThirdCall` to make stub
definitions read more naturally.

`onCall` can be combined with all of the behavior defining methods in this
section. In particular, it can be used together with `withArgs`.

```js
require("@fatso83/mini-mocha").install();

const sinon = require("sinon");
const referee = require("@sinonjs/referee");
const assert = referee.assert;

describe("stub", function () {
  it(
    "should behave differently on consecutive calls with certain argument",
    function () {
      const callback = sinon.stub();
      callback
          .withArgs(42)
          .onFirstCall()
          .returns(1)
          .onSecondCall()
          .returns(2);
      callback.returns(0);

      assert.equals(callback(1), 0);
      assert.equals(callback(42), 1);
      assert.equals(callback(1), 0);
      assert.equals(callback(42), 2);
      assert.equals(callback(1), 0);
      assert.equals(callback(42), 0);
  });
});
```

##### `stub.resetBehavior();`

```js
require("@fatso83/mini-mocha").install();

const sinon = require("sinon");
const { assert } = require("@sinonjs/referee");

describe("stub", function () {
    it("should reset behaviour", function () {
        const stub = sinon.stub();

        stub.returns(54);

        assert.equals(stub(), 54);

        stub.resetBehavior();

        assert.isUndefined(stub());
    });
});
```

##### `stub.callsFake(fakeFunction);`

```js
require("@fatso83/mini-mocha").install();

const sinon = require("sinon");
const referee = require("@sinonjs/referee");
const assert = referee.assert;

const myObj = {};
myObj.prop = function propFn() {
    return "foo";
};

describe("stub", function () {
    it("should call fake", function () {
        sinon.stub(myObj, "prop").callsFake(function fakeFn() {
            return "bar";
        });

        assert.equals(myObj.prop(), "bar");
    });
});
```

##### `stub.callThrough();`

Causes the original method wrapped into the stub to be called when none of the
conditional stubs are matched.

```js
require("@fatso83/mini-mocha").install();

const sinon = require("sinon");
const referee = require("@sinonjs/referee");
const assert = referee.assert;

const obj = {};
obj.sum = function sum(a, b) {
    return a + b;
};

describe("stub", function () {
    it("should call through", function () {
        sinon
            .stub(obj, "sum")
            .withArgs(2, 2)
            .callsFake(function foo() {
                return "bar";
            });

        obj.sum.callThrough();

        assert.equals(obj.sum(2, 2), "bar");
        assert.equals(obj.sum(1, 2), 3);
    });
});
```

### Mock

#### What are mocks?

Mocks (and mock expectations) are fake methods (like spies) with pre-programmed
behavior (like stubs) as well as **pre-programmed expectations**.

A mock will fail your test if it is not used as expected.

#### When to use mocks?

Mocks should only be used for the **method under test**. In every unit test,
there should be one unit under test.

If you want to control how your unit is being used and like stating
expectations upfront (as opposed to asserting after the fact), use a mock.

#### When to *not* use mocks?

Mocks come with built-in expectations that may fail your test.

Thus, they enforce implementation details. The rule of thumb is: if you
wouldn’t add an assertion for some specific call, don’t mock it. Use a stub
instead.

In general you should have **no more than one** mock (possibly with several
expectations) in a single test.

Expectations implement both the spies and stubs APIs.

To see what mocks look like in Sinon.JS, here is one of the PubSubJS tests
again, this time using a method as callback and using mocks to verify its
behavior

```js
"test should call all subscribers when exceptions": function () {
    var myAPI = { method: function () {} };

    var spy = sinon.spy();
    var mock = sinon.mock(myAPI);
    mock.expects("method").once().throws();

    PubSub.subscribe("message", myAPI.method);
    PubSub.subscribe("message", spy);
    PubSub.publishSync("message", undefined);

    mock.verify();
    assert(spy.calledOnce);
}
```
