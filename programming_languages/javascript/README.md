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
    - [Type Casting](#type-casting)
      - [Explicit Type Casting](#explicit-type-casting)
      - [Implicit Type Casting](#implicit-type-casting)
  - [Data Structures](#data-structures)
    - [Indexed collections](#indexed-collections)
      - [Arrays](#arrays)
    - [Structured data](#structured-data)
      - [JSON](#json)
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
  - [Functions](#functions)
    - [Function Parameters](#function-parameters)
      - [Default Parameters](#default-parameters)
      - [Rest Parameters](#rest-parameters)
    - [Arrow Functions](#arrow-functions)
    - [Built-in functions](#built-in-functions)
  - [Asynchronous JavaScript](#asynchronous-javascript)
    - [XMLHttpRequest](#xmlhttprequest)
    - [Fetch](#fetch)
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

### Type Casting

#### Explicit Type Casting

Examples of typecasting methods are `parseInt()`, `parseFloat()`, `toString()`.

#### Implicit Type Casting

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

### Structured data

Structured data is used by search-engines to understand the content of the
page.

#### JSON

JavaScript Object Notation (JSON) is a standard text-based format for
representing structured data based on JavaScript object syntax.

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

## Asynchronous JavaScript

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

## References

- [ ] [roadmap.sh](https://roadmap.sh/javascript)
- [Google JavaScript Style Guide](https://google.github.io/styleguide/jsguide.html)
