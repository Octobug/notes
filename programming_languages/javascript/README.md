# JavaScript

- [JavaScript](#javascript)
  - [Introduction](#introduction)
  - [Variables](#variables)
    - [var](#var)
    - [let](#let)
    - [const](#const)
    - [Hoisting](#hoisting)
    - [Scopes](#scopes)
      - [Global Scope](#global-scope)
      - [Function Scope](#function-scope)
      - [Block Scope](#block-scope)
  - [Data Types](#data-types)
    - [Primitive Types](#primitive-types)
      - [Symbol](#symbol)
        - [Shared Symbols in the global Symbol registry](#shared-symbols-in-the-global-symbol-registry)
        - [Well-known Symbols](#well-known-symbols)
        - [Finding Symbol properties on objects](#finding-symbol-properties-on-objects)
    - [Object](#object)
      - [Built-in objects](#built-in-objects)
      - [TypeOf Operator](#typeof-operator)
    - [Object Prototype](#object-prototype)
      - [The prototype chain](#the-prototype-chain)
      - [Shadowing properties](#shadowing-properties)
      - [Setting a prototype](#setting-a-prototype)
        - [Using Object.create](#using-objectcreate)
        - [Using a constructor](#using-a-constructor)
        - [Own properties](#own-properties)
    - [Prototype Inheritance](#prototype-inheritance)
  - [Type Casting](#type-casting)
    - [Explicit Type Casting](#explicit-type-casting)
    - [Implicit Type Casting](#implicit-type-casting)
  - [Data Structures](#data-structures)
    - [Indexed collections](#indexed-collections)
      - [Arrays](#arrays)
    - [Typed Arrays](#typed-arrays)
      - [Buffers and views: typed array architecture](#buffers-and-views-typed-array-architecture)
        - [ArrayBuffer](#arraybuffer)
        - [Typed array views](#typed-array-views)
    - [Structured data](#structured-data)
      - [JSON](#json)
    - [Keyed Collections](#keyed-collections)
      - [Map](#map)
      - [WeakMap](#weakmap)
      - [Set](#set)
      - [WeakSet](#weakset)
  - [Equality Comparisons](#equality-comparisons)
    - [Value Comparison Operators](#value-comparison-operators)
  - [Loops and Iterations](#loops-and-iterations)
    - [`for…in` statement](#forin-statement)
    - [`for…of` statement](#forof-statement)
    - [Labeled Statements](#labeled-statements)
  - [Control Flow](#control-flow)
  - [Exception Handling](#exception-handling)
    - [Utilizing error objects](#utilizing-error-objects)
      - [Types of Errors:](#types-of-errors)
  - [Expressions and Operators](#expressions-and-operators)
    - [Logical Operators](#logical-operators)
      - [nullish coalescing](#nullish-coalescing)
    - [Comma operators](#comma-operators)
    - [Unary operators](#unary-operators)
    - [Bitwise Operators](#bitwise-operators)
    - [BigInt Operators](#bigint-operators)
    - [Relational Operators](#relational-operators)
  - [Functions](#functions)
    - [Function Parameters](#function-parameters)
      - [Default Parameters](#default-parameters)
      - [Rest Parameters](#rest-parameters)
    - [Arrow Functions](#arrow-functions)
    - [Built-in functions](#built-in-functions)
    - [IIFE](#iife)
      - [Use cases](#use-cases)
        - [Avoid polluting the global namespace](#avoid-polluting-the-global-namespace)
        - [Execute an async function](#execute-an-async-function)
        - [The module pattern](#the-module-pattern)
    - [Arguments object](#arguments-object)
    - [Scope and function stack](#scope-and-function-stack)
      - [Scope](#scope)
      - [Function Stack (Call stack)](#function-stack-call-stack)
      - [Recursion](#recursion)
      - [Lexical scoping](#lexical-scoping)
      - [Closures](#closures)
  - [Strict Mode](#strict-mode)
    - [Invoking strict mode](#invoking-strict-mode)
      - [Strict mode for scripts](#strict-mode-for-scripts)
      - [Strict mode for functions](#strict-mode-for-functions)
      - [Strict mode for modules](#strict-mode-for-modules)
      - [Strict mode for classes](#strict-mode-for-classes)
    - [Changes in strict mode](#changes-in-strict-mode)
  - [`this` keyword](#this-keyword)
    - [In a method](#in-a-method)
    - [In a function](#in-a-function)
    - [Using alone](#using-alone)
    - [In event handlers](#in-event-handlers)
    - [In arrow functions](#in-arrow-functions)
    - [Function Borrowing](#function-borrowing)
      - [Difference between `apply` and `call`](#difference-between-apply-and-call)
    - [Explicit binding](#explicit-binding)
  - [Asynchronous JavaScript](#asynchronous-javascript)
    - [`setTimeout`](#settimeout)
    - [`setInterval`](#setinterval)
    - [Callbacks](#callbacks)
      - [Callback Hell](#callback-hell)
    - [Promises](#promises)
      - [Async/Await](#asyncawait)
  - [Working with APIs](#working-with-apis)
    - [XMLHttpRequest](#xmlhttprequest)
    - [Fetch](#fetch)
  - [Classes](#classes)
  - [Modules](#modules)
    - [CommonJS](#commonjs)
    - [ESModules](#esmodules)
  - [Javascript chrome dev tools](#javascript-chrome-dev-tools)
    - [Debugging issues](#debugging-issues)
  - [References](#references)

## Introduction

- **ECMAScript** is the official language name.
  - ES1
  - ES2
  - ES3
  - ES5
  - ES6

The Node.js **Read-Eval-Print-Loop (REPL)** is an interactive shell that
processes Node.js expressions. The shell reads JavaScript code the user enters,
evaluates the result of interpreting the line of code, prints the result to the
user, and loops until the user signals to quit.

## Variables

### var

The `var` statement declares a **function-scoped** or **globally-scoped**
variable, optionally initializing it to a value.

### let

The `let` declaration declares a **block-scoped** local variable, optionally
initializing it to a value.

### const

Constants are **block-scoped**, much like variables declared using the `let`
keyword. The value of a constant can’t be changed through reassignment, and it
can’t be redeclared. However, if a constant is an `object` or `array` its
properties or items can be updated or removed.

### Hoisting

> 提升机制

JavaScript Hoisting refers to the process whereby the interpreter appears to
move the declaration of **functions**, **variables**, or **classes** to the top
of their scope, prior to **execution** of the code.

### Scopes

The three types of Scope are:

#### Global Scope

Variables declared outside any function or curly braces `{}` have Global Scope,
and can be accessed from anywhere within the same Javascript code.

`var`, `let` and `const` all provide this Scope.

#### Function Scope

Variables declared within a function can only be used within that same
function. Outside that function, they are `undefined`.

`var`, `let` and `const` all provide this Scope.

#### Block Scope

A block is any part of JavaScript code bounded by `{}`. Variables declared
within a block can not be accessed outside that block.

This Scope is only provided by the `let` and `const` keywords.

If you declare a variable within a block using the `var` keyword, it will
**NOT** have Block Scope.

## Data Types

There are **seven** primitive data types (原始数据类型) in JavaScript. Objects
are non-primitives.

### Primitive Types

A primitive is data that is not an object and has no methods or properties.

There are 7 primitive data types:

- `string`
- `number`
- `bigint`
- `boolean`
- `undefined`
- `null`
- `Symbol`

#### Symbol

`Symbol` is a built-in object whose constructor returns a `Symbol` primitive —
also called a **Symbol value** or just a **Symbol** — that's guaranteed to be
unique.

Symbols are often used to add unique property keys to an object that won't
collide with keys any other code might add to the object, and which are hidden
from any mechanisms other code will typically use to access the object. That
enables a form of weak encapsulation, or a weak form of information hiding.

Every `Symbol()` call is guaranteed to return a unique Symbol. Every
`Symbol.for("key")` call will always return the same Symbol for a given value
of `"key"`. When `Symbol.for("key")` is called, if a Symbol with the given key
can be found in the global Symbol registry, that Symbol is returned. Otherwise,
a new Symbol is created, added to the global Symbol registry under the given
key, and returned.

```js
const sym1 = Symbol();
const sym2 = Symbol("foo");
const sym3 = Symbol("foo");
```

The above code creates three new Symbols. Note that `Symbol("foo")` does not
coerce the string `"foo"` into a Symbol. It creates a new Symbol each time:

```js
Symbol("foo") === Symbol("foo"); // false
```

The following syntax with the new operator will throw a TypeError:

```js
const sym = new Symbol(); // TypeError
```

This prevents authors from creating an explicit `Symbol` wrapper object instead
of a new Symbol value and might be surprising as creating explicit wrapper
objects around primitive data types is generally possible (for example,
`new Boolean`, `new String` and `new Number`).

If you really want to create a `Symbol` wrapper object, you can use the
`Object()` function:

```js
const sym = Symbol("foo");
typeof sym; // "symbol"
const symObj = Object(sym);
typeof symObj; // "object"
```

Because symbols are the only primitive data type that has reference identity
(that is, you cannot create the same symbol twice), they behave like objects in
some way. For example, they are garbage collectable and can therefore be stored
in `WeakMap`, `WeakSet`, `WeakRef`, and `FinalizationRegistry` objects.

##### Shared Symbols in the global Symbol registry

The above syntax using the `Symbol()` function will create a Symbol whose value
remains unique throughout the lifetime of the program. To create Symbols
available across files and even across realms (each of which has its own global
scope), use the methods `Symbol.for()` and `Symbol.keyFor()` to set and
retrieve Symbols from the global Symbol registry.

Note that the "global Symbol registry" is only a fictitious concept and may not
correspond to any internal data structure in the JavaScript engine — and even
if such a registry exists, its content is not available to the JavaScript code,
except through the `for()` and `keyFor()` methods.

The method `Symbol.for(tokenString)` takes a string key and returns a symbol
value from the registry, while `Symbol.keyFor(symbolValue)` takes a symbol
value and returns the string key corresponding to it. Each is the other's
inverse, so the following is `true`:

```js
Symbol.keyFor(Symbol.for("tokenString")) === "tokenString"; // true
```

Because registered symbols can be arbitrarily created anywhere, they behave
almost exactly like the strings they wrap. Therefore, they are not guaranteed
to be unique and are not garbage collectable. Therefore, registered symbols are
disallowed in `WeakMap`, `WeakSet`, `WeakRef`, and `FinalizationRegistry`
objects.

##### Well-known Symbols

All static properties of the `Symbol` constructor are Symbols themselves, whose
values are constant across realms. They are known as *well-known* Symbols, and
their purpose is to serve as "protocols" for certain built-in JavaScript
operations, allowing users to customize the language's behavior. For example,
if a constructor function has a method with `Symbol.hasInstance` as its name,
this method will encode its behavior with the `instanceof` operator.

Prior to well-known Symbols, JavaScript used normal properties to implement
certain built-in operations. For example, the `JSON.stringify` function will
attempt to call each object's `toJSON()` method, and the `String` function will
call the object's `toString()` and `valueOf()` methods. However, as more
operations are added to the language, designating each operation a "magic
property" can break backward compatibility and make the language's behavior
harder to reason with. Well-known Symbols allow the customizations to be
"invisible" from normal code, which typically only read string properties.

In MDN and other sources, well-known symbol values are stylized by prefixing
`@@`. For example, `Symbol.hasInstance` is written as `@@hasInstance`. This is
because symbols don't have actual literal formats, but using
`Symbol.hasInstance` does not reflect the ability of using other aliases to
refer to the same symbol. This is like the difference between `Function.name`
and `"Function"`.

Well-known symbols do not have the concept of garbage collectability, because
they come in a fixed set and are unique throughout the lifetime of the program,
similar to intrinsic objects such as `Array.prototype`, so they are also
allowed in `WeakMap`, `WeakSet`, `WeakRef`, and `FinalizationRegistry` objects.

##### Finding Symbol properties on objects

The method `Object.getOwnPropertySymbols()` returns an array of Symbols and
lets you find Symbol properties on a given object. Note that every object is
initialized with no own Symbol properties, so that this array will be empty
unless you've set Symbol properties on the object.

### Object

JavaScript object is a data structure that allows us to have key-value pairs;
so we can have distinct keys and each key is mapped to a value that can be of
any JavaScript data type.

#### Built-in objects

Built-in objects, or **global objects**, are those built into the language
specification itself. There are numerous built-in objects with the JavaScript
language, all of which are accessible at the global scope. Some examples are:

- `Number`
- `Math`
- `Date`
- `String`
- `Error`
- `Function`
- `Boolean`

#### TypeOf Operator

You can use the `typeOf` operator to find the data type of a JavaScript
variable.

### Object Prototype

JavaScript is an object-oriented language built around a prototype model. In
JavaScript, every object inherits properties from its prototype. A prototype is
simply an object from which another object inherits properties.

> <https://developer.mozilla.org/en-US/docs/Learn/JavaScript/Objects/Object_prototypes>

Prototypes are the mechanism by which JavaScript objects inherit features from
one another.

#### The prototype chain

```js
const myObject = {
  city: "Madrid",
  greet() {
    console.log(`Greetings from ${this.city}`);
  },
};

myObject.greet(); // Greetings from Madrid
```

Every object in JavaScript has a built-in property, which is called its
**prototype**. The prototype is itself an object, so the prototype will have
its own prototype, making what's called a **prototype chain**. The chain ends
when we reach a prototype that has null for its own prototype.

> ⚠️ **Note**: The property of an object that points to its prototype is **not**
> called `prototype`. Its name is not standard, but in practice all browsers
> use `__proto__`. The standard way to access an object's prototype is the
> `Object.getPrototypeOf()` method.

When you try to access a property of an object: if the property can't be found
in the object itself, the prototype is searched for the property. If the
property still can't be found, then the prototype's prototype is searched, and
so on until either the property is found, or the end of the chain is reached,
in which case `undefined` is returned.

So when we call `myObject.toString()`, the browser:

- looks for `toString` in `myObject`
- can't find it there, so looks in the prototype object of `myObject` for
  `toString`
- finds it there, and calls it.

`Object {}` is an object called `Object.prototype`, and it is the most basic
prototype, that all objects have by default. The prototype of `Object.prototype`
is `null`, so it's at the end of the prototype chain.

The prototype of an object is not always `Object.prototype`:

```js
const myDate = new Date();
let object = myDate;

do {
  object = Object.getPrototypeOf(object);
  console.log(object);
} while (object);

// Date.prototype
// Object { }
// null
```

It shows us that the prototype of `myDate` is a `Date.prototype` object, and
the prototype of that is `Object.prototype`.

In fact, when you call familiar methods, like `myDate2.getMonth()`, you are
calling a method that's defined on `Date.prototype`.

#### Shadowing properties

```js
const myDate = new Date(1995, 11, 17);

console.log(myDate.getYear()); // 95

myDate.getYear = function () {
  console.log("something else!");
};

myDate.getYear(); // 'something else!'
```

When we call `getYear()` the browser first looks in `myDate` for a property
with that name, and only checks the prototype if `myDate` does not define it.
So when we add `getYear()` to `myDate`, then the version in `myDate` is called.

This is called "shadowing" the property.

#### Setting a prototype

There are various ways of setting an object's prototype in JavaScript, and here
are two of them: `Object.create()` and constructors.

##### Using Object.create

The `Object.create()` method creates a new object and allows you to specify an
object that will be used as the new object's prototype.

```js
const personPrototype = {
  greet() {
    console.log("hello!");
  },
};

const carl = Object.create(personPrototype);
carl.greet(); // hello!
```

但是不推荐这么做: because this reassigns the `prototype` property and removes the
`constructor` property, it can be more error-prone

```js
function Base() {}
function Derived() {}
// Re-assigns `Derived.prototype` to a new object
// with `Base.prototype` as its `[[Prototype]]`
// DON'T DO THIS — use Object.setPrototypeOf to mutate it instead
Derived.prototype = Object.create(Base.prototype);
```

##### Using a constructor

In JavaScript, all functions have a property named `prototype`. When you call a
function as a constructor, this property is set as the prototype of the newly
constructed object (by convention, in the property named `__proto__`).

So if we set the `prototype` of a constructor, we can ensure that all objects
created with that constructor are given that prototype:

```js
const personPrototype = {
  greet() {
    console.log(`hello, my name is ${this.name}!`);
  },
};

function Person(name) {
  this.name = name;
}

Object.assign(Person.prototype, personPrototype);
// or
// Person.prototype.greet = personPrototype.greet;
```

- an object `personPrototype`, which has a `greet()` method
- a `Person()` constructor function which initializes the name of the person to
  create.

We then put the methods defined in `personPrototype` onto the `Person`
function's `prototype` property using `Object.assign`.

After this code, objects created using `Person()` will get `Person.prototype`
as their prototype, which automatically contains the `greet` method.

```js
const reuben = new Person("Reuben");
reuben.greet(); // hello, my name is Reuben!
```

##### Own properties

The objects we create using the `Person` constructor above have two properties:

- a `name` property, which is set in the constructor, so it appears directly on
  `Person` objects
- a `greet()` method, which is set in the prototype.

It's common to see this pattern, in which methods are defined on the prototype,
but data properties are defined in the constructor. That's because **methods are
usually the same for every object we create, while we often want each object to
have its own value for its data properties**.

Properties that are defined directly in the object, like `name` here, are
called **own properties**, and you can check whether a property is an own
property using the static `Object.hasOwn()` method:

```js
const irma = new Person("Irma");

console.log(Object.hasOwn(irma, "name")); // true
console.log(Object.hasOwn(irma, "greet")); // false
```

> ⚠️ Note: You can also use the non-static `Object.hasOwnProperty()` method
> here, but we recommend that you use `Object.hasOwn()` if you can.

### Prototype Inheritance

> <https://developer.mozilla.org/en-US/docs/Web/JavaScript/Inheritance_and_the_prototype_chain>

Classes are syntax sugar over constructor functions, which means you can still
manipulate `Box.prototype` to change the behavior of all instances.

## Type Casting

### Explicit Type Casting

Examples of typecasting methods are `parseInt()`, `parseFloat()`, `toString()`.

### Implicit Type Casting

Most of the time operators automatically convert a value to the right type.

## Data Structures

JavaScript has primitive (built-in) and non-primitive (not built-in) data
structures.

### Indexed collections

Indexed Collections are collections that have numeric indices i.e. the
collections of data that are ordered by an index value.

#### Arrays

An array is an indexed collection. An array is an ordered set of values that
has a numeric index.

### Typed Arrays

> <https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Typed_arrays>

JavaScript typed arrays are array-like objects that provide a mechanism for
reading and writing raw binary data in memory buffers.

As web applications become more and more powerful, adding features such as
audio and video manipulation, access to raw data using WebSockets, and so
forth, it has become clear that there are times when it would be helpful for
JavaScript code to be able to quickly and easily manipulate raw binary data.
This is where typed arrays come in.

Each entry in a JavaScript typed array is a raw binary value in one of a number
of supported formats, from 8-bit integers to 64-bit floating-point numbers.

#### Buffers and views: typed array architecture

To achieve maximum flexibility and efficiency, JavaScript typed arrays split
the implementation into *buffers and views*. A buffer (implemented by the
`ArrayBuffer` object) is an object representing a chunk of data; it has no
format to speak of, and offers no mechanism for accessing its contents. In
order to access the memory contained in a buffer, you need to use a view. A
view provides a *context* — that is, a data type, starting offset, and number
of elements — that turns the data into an actual typed array.

##### ArrayBuffer

The `ArrayBuffer` is a data type that is used to represent a generic,
fixed-length binary data buffer. You can't directly manipulate the contents of
an `ArrayBuffer`; instead, you create a typed array view or a `DataView` which
represents the buffer in a specific format, and use that to read and write the
contents of the buffer.

##### Typed array views

Typed array views have self-descriptive names and provide views for all the
usual numeric types like `Int8`, `Uint32`, `Float64` and so forth. There is one
special typed array view, `Uint8ClampedArray`, which clamps the values between
`0` and `255`. This is useful for Canvas data processing, for example.

```js
// create a buffer, here with a fixed length of 16-bytes:
const buffer = new ArrayBuffer(16);

// create a view that treats the data in the buffer as an array of 32-bit
//  signed integers:
const int32View = new Int32Array(buffer);

// This fills out the 4 entries in the array (4 entries at 4 bytes each makes
//  16 total bytes) with the values 0, 2, 4, and 6.
for (let i = 0; i < int32View.length; i++) {
  int32View[i] = i * 2;
}
```

### Structured data

Structured data is used by search-engines to understand the content of the
page.

#### JSON

JavaScript Object Notation (JSON) is a standard text-based format for
representing structured data based on JavaScript object syntax.

### Keyed Collections

Keyed collections are data collections that are **ordered by key** not index.
They are associative in nature. Map and set objects are keyed collections and
are iterable in the order of insertion.

#### Map

#### WeakMap

> <https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/WeakMap>

An object's presence as a key in a `WeakMap` does not prevent the object from
being garbage collected. Once an object used as a key has been collected, its
corresponding values in any `WeakMap` become candidates for garbage collection
as well — as long as they aren't strongly referred to elsewhere. The only
primitive type that can be used as a `WeakMap` key is `symbol` — more
specifically, non-registered symbols — because non-registered symbols are
guaranteed to be unique and cannot be re-created.

#### Set

#### WeakSet

> <https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Global_Objects/WeakSet>

A `WeakSet` is a collection of garbage-collectable values, including objects
and non-registered symbols. A value in the WeakSet may only occur once. It is
unique in the WeakSet's collection.

## Equality Comparisons

### Value Comparison Operators

- `==` operator does the type conversion of the operands before comparison.
  - The `==` operator applies various coercions to both sides (if they are not
    the same type) before testing for equality (resulting in such behavior as
    `"" == false` being true).
- `===` operator compares the values and the data types of the operands.
- `Object.is()` method determines whether two values are the same value:
  `Object.is(value1, value2)`.
  - `Object.is()` is not equivalent to the `==` operator. `Object.is()` doesn’t
    coerce either value.
  - `Object.is()` is also not equivalent to the `===` operator. The only
    difference between `Object.is()` and `===` is in their treatment of signed
    zeros and `NaN` values. The `===` operator (and the `==` operator) treats
    the number values `-0` and `+0` as equal but treats `NaN` as not equal to
    each other.

## Loops and Iterations

### `for…in` statement

The `for…in` statement iterates over all enumerable properties of an object
that are **keyed by strings** (ignoring ones keyed by Symbols), including
inherited enumerable properties.

```js
const object = { a: 1, b: 2, c: 3 };

for (const property in object) {
  console.log(`${property}: ${object[property]}`);
}

// Expected output:
// "a: 1"
// "b: 2"
// "c: 3"
```

### `for…of` statement

The `for…of` statement executes a loop that operates on a sequence of values
sourced from an iterable object. Iterable objects include instances of
built-ins such as `Array`, `String`, `TypedArray`, `Map`, `Set`, `NodeList`
(and other DOM collections), and the `arguments object`, `generators` produced
by generator functions, and user-defined iterables.

```js
const array1 = ['a', 'b', 'c'];

for (const element of array1) {
  console.log(element);
}

// Expected output: "a"
// Expected output: "b"
// Expected output: "c"
```

### Labeled Statements

JavaScript label statements are used to prefix a label to an identifier. It can
be used with `break` and `continue` statement to control the flow more
precisely.

A label is simply an identifier followed by a colon`(:)` that is applied to a
block of code.

```js
let str = '';

loop1:
for (let i = 0; i < 5; i++) {
  if (i === 1) {
    continue loop1;
  }
  str = str + i;
}

console.log(str);
// Expected output: "0234"
```

## Control Flow

We can control the flow of the program through any of these control structures:

- Sequential (default mode)
- Conditional Statements
- Exception Handling
- Loops and Iterations

## Exception Handling

In JavaScript, all exceptions are simply objects. While the majority of
exceptions are implementations of the global Error class, any old object can be
thrown. With this in mind, there are two ways to throw an exception:

- directly via an Error object
- through a custom object

### Utilizing error objects

When a runtime error occurs, a new `Error` object is created and thrown. With
this `Error` object, we can determine the type of the Error and handle it
according to its type.

#### Types of Errors:

Besides error constructors, Javascript also has other core Error constructors.

- AggregateError
- EvalError
- InternalError
- RangeError
- ReferenceError
- SyntaxError

```js
try {
  willGiveErrorSometime();
} catch (error) {
  if (error instanceof RangeError) {
    rangeErrorHandler(error);
  } else if (error instanceof ReferenceError) {
    referenceErrorHandle(error);
  } else {
    errorHandler(error);
  }
}
```

## Expressions and Operators

There are two types of expressions:

- those that have side effects (e.g. `x = 7`, the expression itself evaluates
  to 7).
- those that purely evaluate (e.g. `3 + 4`, this expression uses the `+`
  operator to add `3` and `4` together and produces a value, `7`).
  - However, if it’s not eventually part of a bigger construct (for example, a
    variable declaration like const `z = 3 + 4`), its result will be immediately
    discarded — this is usually a programmer mistake because the evaluation
    doesn’t produce any effects.

### Logical Operators

#### nullish coalescing

`??`: The **nullish coalescing** operator is a logical operator that returns its
right-hand side operand when its left-hand side operand is `null` or
`undefined`, and otherwise returns its left-hand side operand.

```js
const foo = null ?? 'default string';
console.log(foo);
// Expected output: "default string"

const baz = 0 ?? 42;
console.log(baz);
// Expected output: 0
```

### Comma operators

The comma operator `(,)` evaluates each of its operands (from left to right)
and returns the value of the last operand. This lets you create a compound
expression in which multiple expressions are evaluated, with the compound
expression’s final value being the value of the rightmost of its member
expressions. This is commonly used to provide multiple parameters to a `for`
loop.

```js
let x = 1;

x = (x++, x);

console.log(x);
// Expected output: 2

x = (2, 3);

console.log(x);
// Expected output: 3
```

### Unary operators

A unary operation is an operation with only one operand.

- `delete`: The `delete` operator deletes a property from an object.
- `void`: The `void` operator evaluates an expression and discards its return
  value.
- `typeof`: The `typeof` operator determines the type of a given object.
- `+`: The unary plus operator converts its operand to Number type.
- `-`: The unary negation operator converts its operand to Number type and then
  negates it.
- `~`: Bitwise NOT operator.
- `!`: Logical NOT operator.
- `await`: Pause and resume an async function and wait for the promise's
  fulfillment/rejection.

### Bitwise Operators

- `&` (AND)
- `|` (OR)
- `^` (XOR)
- `~` (NOT)
- `<<` (Left SHIFT)
- `>>` (Right SHIFT)
- `>>>` (Zero-Fill Right SHIFT)

### BigInt Operators

> <https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Expressions_and_Operators#bigint_operators>

```js
// BigInt addition
const a = 1n + 2n; // 3n
// Division with BigInts round towards zero
const b = 1n / 2n; // 0n
// Bitwise operations with BigInts do not truncate either side
const c = 40000000000000000n >> 2n; // 10000000000000000n
```

Most operators that can be used with the `Number` data type will also work with
`BigInt` values (e.g. arithmetic, comparison, etc.). However, the unsigned
right shift `>>>` operator is an exception and is not supported. Similarly,
some operators may have slight differences in behaviour (for example, division
with BigInt will round towards zero).

```js
const d = 8n >>> 2n; // TypeError: BigInts have no unsigned right shift, use >> instead
```

BigInts and numbers are not mutually replaceable — you cannot mix them in
calculations.

This is because `BigInt` is neither a subset nor a superset of numbers. BigInts
have higher precision than numbers when representing large integers, but cannot
represent decimals, so implicit conversion on either side might lose precision.

```js
const a = Number(1n) + 2; // 3
const b = 1n + BigInt(2); // 3n
```

### Relational Operators

- `<`: Less than operator.
- `>`: Greater than operator.
- `<=`: Less than or equal operator.
- `>=`: Greater than or equal operator.
- `instanceof`: The `instanceof` operator determines whether an object is an
  instance of another object.
- `in`: The `in` operator determines whether an object has a given property.

## Functions

### Function Parameters

There are two special kinds of parameter syntax: `default parameters` and
`rest parameters`.

#### Default Parameters

Default function parameters allow named parameters to be initialized with
default values if no value or `undefined` is passed.

#### Rest Parameters

The rest parameter syntax allows a function to accept an indefinite number of
arguments as an array, providing a way to represent variadic functions in
JavaScript.

```js
function multiply(multiplier, ...theArgs) {
  return theArgs.map((x) => multiplier * x);
}

const arr = multiply(2, 1, 2, 3);
console.log(arr); // [2, 4, 6]
```

### Arrow Functions

An **arrow function expression** is a compact alternative to a traditional
function expression, with some semantic differences and deliberate limitations
in usage:

- Arrow functions don't have their own bindings to `this`, `arguments`, or
  `super`, and should not be used as `methods`.
- Arrow functions cannot be used as `constructors`. Calling them with `new`
  throws a `TypeError`. They also don't have access to the `new.target` keyword.
- Arrow functions cannot use `yield` within their body and cannot be created as
  generator functions.

### Built-in functions

A JavaScript **method** is a property containing a **function definition**. In
other words, when the data stored on an object is a function we call that a
method.

To differentiate between properties and methods, we can think of it this way:
**A property is what an object has, while a method is what an object does**.

Since JavaScript methods are actions that can be performed on objects, we first
need to have objects to start with. There are several objects built into
JavaScript which we can use.

### IIFE

> <https://developer.mozilla.org/en-US/docs/Glossary/IIFE>

Immediately-Invoked Function Expression is a function that is executed
immediately after it is created.

```js
(function () {
  // …
})();

(() => {
  // …
})();

(async () => {
  // …
})();
```

It is a design pattern which is also known as a Self-Executing Anonymous
Function and contains two major parts:

1. The first is the anonymous function with lexical scope enclosed within the
   `Grouping Operator` `()`. This prevents accessing variables within the IIFE
   idiom as well as polluting the global scope.
2. The second part creates the immediately invoked function expression `()`
   through which the JavaScript engine will directly interpret the function.

#### Use cases

##### Avoid polluting the global namespace

```js
(() => {
  // some initiation code
  let firstVariable;
  let secondVariable;
})();

// firstVariable and secondVariable will be discarded after the function is executed.
```

##### Execute an async function

```js
const getFileStream = async (url) => {
  // implementation
};

(async () => {
  const stream = await getFileStream("https://domain.name/path/file.ext");
  for await (const chunk of stream) {
    console.log({ chunk });
  }
})();
```

##### The module pattern

```js
const makeWithdraw = (balance) =>
  ((copyBalance) => {
    let balance = copyBalance; // This variable is private
    const doBadThings = () => {
      console.log("I will do bad things with your money");
    };
    doBadThings();
    return {
      withdraw(amount) {
        if (balance >= amount) {
          balance -= amount;
          return balance;
        }
        return "Insufficient money";
      },
    };
  })(balance);

const firstAccount = makeWithdraw(100); // "I will do bad things with your money"
console.log(firstAccount.balance); // undefined
console.log(firstAccount.withdraw(20)); // 80
console.log(firstAccount.withdraw(30)); // 50
console.log(firstAccount.doBadThings); // undefined; this method is private
const secondAccount = makeWithdraw(20); // "I will do bad things with your money"
console.log(secondAccount.withdraw(30)); // "Insufficient money"
console.log(secondAccount.withdraw(20)); // 0
```

### Arguments object

> <https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Functions/arguments>
>
> ⚠️ In modern code, rest parameters should be preferred.

```js
function func1(a, b, c) {
  console.log(arguments[0]);
  // Expected output: 1

  console.log(arguments[1]);
  // Expected output: 2

  console.log(arguments[2]);
  // Expected output: 3
}

func1(1, 2, 3);
```

### Scope and function stack

#### Scope

JavaScript has the following kinds of scopes:

- **Global scope**: The default scope for all code running in script mode.
- **Module scope**: The scope for code running in module mode.
- **Function scope**: The scope created with a function.
- **Block scope**: The scope created with a pair of curly braces (a block).

#### Function Stack (Call stack)

The function stack is how the interpreter keeps track of its place in a script
that calls multiple functions, like which function is currently executing and
which functions within that function are being called.

#### Recursion

#### Lexical scoping

In simple words, the lexical environment for a function `f` simply refers to
the environment enclosing that function’s definition in the source code.

#### Closures

A closure refers to a function along with its lexical environment. It is
essentially what allows us to return a function `A`, from another function `B`,
that remembers the local variables defined in `B`, even after `B` exits.

## Strict Mode

> <https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Strict_mode>

Strict mode isn’t just a subset: it intentionally has different semantics from
regular code. Browsers not supporting strict mode will run strict mode code
with different behavior from browsers that do, so don’t rely on strict mode
without feature-testing for support for the relevant aspects of strict mode.
Strict mode code and non-strict mode code can coexist so that scripts can opt
into strict mode incrementally.

Strict mode makes several changes to normal JavaScript semantics:

- Eliminates some JavaScript silent errors by changing them to throw errors.
- Fixes mistakes that make it difficult for JavaScript engines to perform
  optimizations: strict mode code can sometimes run faster than identical code
  that’s not strict mode.
- Prohibits some syntax likely to be defined in future versions of ECMAScript.

### Invoking strict mode

#### Strict mode for scripts

```js
// Whole-script strict mode syntax
"use strict";
const v = "Hi! I'm a strict mode script!";
```

#### Strict mode for functions

```js
function myStrictFunction() {
  // Function-level strict mode syntax
  "use strict";
  function nested() {
    return "And so am I!";
  }
  return `Hi! I'm a strict mode function! ${nested()}`;
}

function myNotStrictFunction() {
  return "I'm not strict.";
}
```

The `"use strict"` directive can only be applied to the body of functions with
simple parameters. Using `"use strict"` in functions with `rest`, `default`, or
`destructured` parameters is a `syntax error`.

```js
function sum(a = 1, b = 2) {
  // SyntaxError: "use strict" not allowed in function with default parameter
  "use strict";
  return a + b;
}
```

#### Strict mode for modules

```js
function myStrictFunction() {
  // because this is a module, I'm strict by default
}
export default myStrictFunction;
```

#### Strict mode for classes

```js
class C1 {
  // All code here is evaluated in strict mode
  test() {
    delete Object.prototype;
  }
}
new C1().test(); // TypeError, because test() is in strict mode

const C2 = class {
  // All code here is evaluated in strict mode
};

// Code here may not be in strict mode
delete Object.prototype; // Will not throw error
```

### Changes in strict mode

Strict mode changes both syntax and runtime behavior. Changes generally fall
into these categories:

- changes converting mistakes into errors (as syntax errors or at runtime)
- changes simplifying how variable references are resolved
- changes simplifying `eval` and `arguments`
- changes making it easier to write "secure" JavaScript
- changes anticipating future ECMAScript evolution.

## `this` keyword

`this` refers to an object, but it depends on how or where it is being invoked.
It also has some differences between strict mode and non-strict mode.

- In an object method, `this` refers to the object
- Alone, `this` refers to the global object
- In a function, `this` refers to the global object
- In a function, in **strict mode**, `this` is `undefined`
- In an event, `this` refers to the element that received the event
- Methods like `call()`, `apply()`, and `bind()` can refer `this` to any object

### In a method

Methods are properties of an object which are functions. The value of `this`
inside a method is equal to the calling object. In simple words, `this` value
is the object “before dot”, the one used to call the method.

### In a function

The keyword `this` when used in a function refers to the global object.

> ⚠️ Note: in a browser window the global object is the `window` object.

### Using alone

The keyword `this` when used alone refers to the global object.

> ⚠️ Note: in a browser window the global object is the `window` object.

### In event handlers

The keyword `this` when used in an event handler refers to the element that
received the event.

### In arrow functions

The keyword `this` when used in an arrow function refers to the parent object.

### Function Borrowing

> <https://medium.com/@ensallee/function-borrowing-in-javascript-4bd671e9d7b4>

Function borrowing allows us to use the methods of one object on a different
object without having to make a copy of that method and maintain it in two
separate places. It is accomplished through the use of `.call()`, `.apply()`,
or `.bind()`, all of which exist to explicitly set `this` on the method we are
borrowing.

```js
class Dog {
  constructor(name, age, breed) {
    this.name = name
    this.age = age
    this.breed = breed
  }
  tellUsAboutYourSelf() {
    return `My name is ${this.name}. I am a ${this.breed} and I am ${this.age}
      years old.`
  }

  woof() {
    return "WOOF!!!"
  }
}

let fido = new Dog("Fido", 3, "dachshund")
fido.tellUsAboutYourSelf()
//=> 'My name is Fido. I am a dachshund and I am 3 years old.'
```

```js
class Cat {
  constructor(name, age, breed) {
    this.name = name
    this.age = age
    this.breed = breed
  }

  meow() {
    return "MEOW!!!"
  }
}

let sparkles = new Cat("Sparkles", 5, "Siamese")
sparkles.tellUsAboutYourSelf()
//=>TypeError: sparkles.tellUsAboutYourSelf is not a function
```

```js
fido.tellUsAboutYourSelf.call(sparkles)
//=>’My name is Sparkles. I am a Siamese and I am 5 years old.’
fido.tellUsAboutYourSelf.apply(sparkles)
//=>’My name is Sparkles. I am a Siamese and I am 5 years old.’
const describeSparkles = fido.tellUsAboutYourSelf.bind(sparkles)
describeSparkles()
//=>’My name is Sparkles. I am a Siamese and I am 5 years old.’
```

The most important practical application of function borrowing pertains to
native methods, and specifically, to `Array.prototype.slice`. There are several
list-like data structures that aren’t arrays, and it’s useful to be able to
treat them as arrays and operate on them as such. One of the most prevalent
list-like data structures that isn’t an array is `arguments`. The `arguments`
object represents all the parameters passed in to a given (non-arrow) function.

Take, for example, the below function:

```js
function findO() {
  var args = Array.prototype.slice.call(arguments)
  return args.filter(a => a.includes('o'))
}

findO("orchid", "tulip", "rose", "lilac")
=> [ 'orchid', 'rose' ]
```

#### Difference between `apply` and `call`

Pseudo syntax:

- `theFunction.apply(valueForThis, arrayOfArgs)`
- `theFunction.call(valueForThis, arg1, arg2, ...)`

### Explicit binding

Explicit binding is when you use the `call`, `apply`, or `bind` methods to
explicitly set the value of `this` in a function.

## Asynchronous JavaScript

Asynchronous programming is a technique that enables your program to start a
potentially long-running task and still be able to be responsive to other
events while that task runs, rather than having to wait until that task has
finished. Once that task has finished, your program is presented with the
result.

Many functions provided by browsers, especially the most interesting ones, can
potentially take a long time, and therefore, are asynchronous. For example:

- Making HTTP requests using `fetch()`
- Accessing a user’s camera or microphone using `getUserMedia()`
- Asking a user to select files using `showOpenFilePicker()`

### `setTimeout`

### `setInterval`

### Callbacks

A callback function is a function passed into another function as an argument,
which is then invoked inside the outer function to complete some kind of
routine or action.

#### Callback Hell

The callback hell is when we try to write asynchronous JavaScript in a way
where execution happens visually from top to bottom, creating a code that has a
pyramid shape with many `})` at the end.

### Promises

Promises were introduced into JavaScript with ECMAScript 6. Using promises, we
can manage extremely complex asynchronous code with rigorous error-handling
setup, write code in a more or less synchronous style, and keep ourselves from
running into the so-called callback hell.

#### Async/Await

`async`/`await` is a special syntax to work with promises in a more comfortable
fashion. We use `async` keyword to declare a async function that return a
`Promise`, and the `await` keyword makes a function wait for a `Promise`.

## Working with APIs

### XMLHttpRequest

`XMLHttpRequest` (XHR) is a built-in browser object that can be used to
interact with server. XHR allows you to update data without having to reload a
web page. Despite the word XML in its name, XHR not only used to retrieve data
with XML format, we can use it with any type of data, like `JSON`, file(s), and
much more.

### Fetch

The `fetch()` method in JavaScript is used to request to the server and load
the information on the webpages. The request can be of any APIs that return the
data of the format `JSON` or `XML`. This method returns a `promise`.

## Classes

> <https://developer.mozilla.org/en-US/docs/Web/JavaScript/Reference/Classes>

Classes in JS are built on prototypes but have some syntax and semantics that
are not shared with ES5 class-like semantics.

## Modules

Modules encapsulate all sorts of code like functions and variables and expose
all this to other files. Generally, we use it to break our code into separate
files to make it more maintainable. They were introduced into JavaScript with
ECMAScript 6.

### CommonJS

> <https://www.freecodecamp.org/news/modules-in-javascript/#commonjsmodules>

CommonJS modules (`module.exports` and `require`) are the original way to
package JavaScript code for Node.js. Node.js also supports the ESModules
standard used by browsers and other JavaScript runtimes, but CJS is still
widely used in backend Node.js applications. Sometimes these modules will be
written with a `.cjs` extension.

```js
// mod1.js
const mod1Function = () => console.log('Mod1 is alive!')
module.exports = mod1Function
```

```js
// main.js
mod1Function = require('./mod1.js')

const testFunction = () => {
    console.log('Im the main function')
    mod1Function()
}

testFunction()
```

### ESModules

> <https://developer.mozilla.org/en-US/docs/Web/JavaScript/Guide/Modules>

ESModules (`export` and `import from`) is a standard that was introduced with
ES6 (2015). The idea was to standardize how JS modules work and implement these
features in browsers. This standard is widely used with frontend frameworks
such as react and can also be used in the backend with Node.js. Sometimes these
modules will be written with a `.mjs` extension.

```js
export const name = "square";

export function draw(ctx, length, x, y, color) {
  ctx.fillStyle = color;
  ctx.fillRect(x, y, length, length);

  return { length, x, y, color };
}

export { name, draw, reportArea, reportPerimeter };
```

```js
import { name, draw, reportArea, reportPerimeter } from "./modules/square.js";
```

## Javascript chrome dev tools

A very useful feature in the Chrome dev tools is the Lighthouse (for checking
performance).

### Debugging issues

> <https://developer.chrome.com/docs/devtools/javascript/>

## References

- [ ] [roadmap.sh](https://roadmap.sh/javascript)
- [Google JavaScript Style Guide](https://google.github.io/styleguide/jsguide.html)
