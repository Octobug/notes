# Chapter 4: Functions

- [Chapter 4: Functions](#chapter-4-functions)
  - [Declaring and Invoking Functions](#declaring-and-invoking-functions)
    - [Optional and Default Parameters](#optional-and-default-parameters)
    - [Rest Parameters](#rest-parameters)
    - [call, apply, and bind](#call-apply-and-bind)
      - [TSC Flag: `strictBindCallApply`](#tsc-flag-strictbindcallapply)
    - [Typing this](#typing-this)
      - [TSC Flag: `noImplicitThis`](#tsc-flag-noimplicitthis)
    - [Generator Functions](#generator-functions)
    - [Iterators](#iterators)
      - [TSC Flag: downlevelIteration](#tsc-flag-downleveliteration)
    - [Call Signatures](#call-signatures)
      - [Type Level and Value Level Code](#type-level-and-value-level-code)
    - [Contextual Typing](#contextual-typing)
    - [Overloaded Function Types](#overloaded-function-types)
      - [Keeping Overload Signatures Specific](#keeping-overload-signatures-specific)
  - [Polymorphism](#polymorphism)
    - [Generic type parameter](#generic-type-parameter)
    - [When Are Generics Bound?](#when-are-generics-bound)
    - [Where Can You Declare Generics?](#where-can-you-declare-generics)
      - [`filter` and `map` in the Standard Library](#filter-and-map-in-the-standard-library)
    - [Generic Type Inference](#generic-type-inference)
    - [Generic Type Aliases](#generic-type-aliases)
    - [Bounded Polymorphism](#bounded-polymorphism)
      - [Bounded polymorphism with multiple constraints](#bounded-polymorphism-with-multiple-constraints)
      - [Using bounded polymorphism to model arity](#using-bounded-polymorphism-to-model-arity)
    - [Generic Type Defaults](#generic-type-defaults)
  - [Type-Driven Development](#type-driven-development)

## Declaring and Invoking Functions

```ts
function add(a: number, b: number) {
    return a + b
}
```

In most cases TypeScript won’t infer types for your parameters, except for a
few special cases where it can infer types from context. The return type
***is*** inferred, but you can explicitly annotate it too if you want:

```ts
function add(a: number, b: number): number {
    return a + b
}
```

```ts
// Named function
function greet(name: string) {
    return 'hello ' + name
}

// Function expression
let greet2 = function(name: string) {
    return 'hello ' + name
}

// Arrow function expression
let greet3 = (name: string) => {
    return 'hello ' + name
}

// Shorthand arrow function expression
let greet4 = (name: string) =>
    'hello ' + name

// Function constructor
let greet5 = new Function('name', 'return "hello " + name')
```

Besides function constructors (which you shouldn’t use because they are totally
unsafe), all of these syntaxes are supported by TypeScript in a typesafe way.

- If you enter that last example into your code editor, you’ll see that its
  type is Function. It has all the prototype methods from `Function.prototype`.
  But its parameters and return type are untyped, so you can call the function
  with any arguments you want.

```ts
add(1, 2)           // evaluates to 3
greet('Crystal')    // evaluates to 'hello Crystal'

add(1)              // Error TS2554: Expected 2 arguments, but got 1.
add(1, 'a')         // Error TS2345: Argument of type '"a"' is not assignable
                    // to parameter of type 'number'.
```

### Optional and Default Parameters

Like in `object` and `tuple` types, you can use `?` to mark parameters as
optional. When declaring your function’s parameters, required parameters have
to come first, followed by optional parameters:

```ts
function log(message: string, userId?: string) {
  let time = new Date().toLocaleTimeString()
  console.log(time, message, userId || 'Not signed in')
}

log('Page loaded')              // Logs "12:38:31 PM Page loaded Not signed in"
log('User signed in', 'da763be')// Logs "12:38:31 PM User signed in da763be"
```

You can provide default values for optional parameters. Semantically it’s
similar to making a parameter optional, in that callers no longer have to pass
it in (a difference is that default parameters don’t have to be at the end of
your list of parameters, while optional parameters do).

```ts
function log(message: string, userId = 'Not signed in') {
  let time = new Date().toISOString()
  console.log(time, message, userId)
}

log('User clicked on a button', 'da763be')
log('User signed out')
```

You can also add explicit type annotations to your default parameters, the same
way you can for parameters without defaults:

```ts
type Context = {
  appId?: string
  userId?: string
}

function log(message: string, context: Context = {}) {
  let time = new Date().toISOString()
  console.log(time, message, context.userId)
}
```

💡 You’ll find yourself using default parameters over optional parameters often.

### Rest Parameters

```ts
function sum(numbers: number[]): number {
  return numbers.reduce((total, n) => total + n, 0)
}

sum([1, 2, 3]) // evaluates to 6
```

Traditionally, variadic parameters required using JavaScript’s magic
`arguments` object.

`arguments` is “magic” because your JavaScript runtime automatically defines it
for you in functions, and assigns to it the list of arguments you passed to
your function. Because `arguments` is only array-like, and not a true array,
you first have to convert it to an array before you can call the built-in
`.reduce` on it:

```ts
function sumVariadic(): number {
  return Array
    .from(arguments)
    .reduce((total, n) => total + n, 0)
}

sumVariadic(1, 2, 3) // evaluates to 6
```

⚠️ But there’s one big problem with using `arguments`: it’s totally unsafe!

This means TypeScript inferred that both `n` and `total` are of type `any`, and
silently let it pass — that is, until you try to use `sumVariadic`:

```ts
sumVariadic(1, 2, 3) // Error TS2554: Expected 0 arguments, but got 3.
```

Since we didn’t declare that `sumVariadic` takes arguments, from TypeScript’s
point of view it doesn’t take any arguments, so we get a `TypeError` when we
try to use it.

We can instead use rest parameters to safely make our `sum` function accept any
number of arguments:

```ts
function sumVariadicSafe(...numbers: number[]): number {
  return numbers.reduce((total, n) => total + n, 0)
}

sumVariadicSafe(1, 2, 3) // evaluates to 6
```

A function can have at most one rest parameter, and that parameter has to be
the last one in the function’s parameter list.

```ts
interface Console {
  log(message?: any, ...optionalParams: any[]): void
}
```

### call, apply, and bind

In addition to invoking a function with parentheses `()`, JavaScript supports
at least two other ways to call a function.

```ts
function add(a: number, b: number): number {
  return a + b
}

add(10, 20)                 // evaluates to 30
add.apply(null, [10, 20])   // evaluates to 30
add.call(null, 10, 20)      // evaluates to 30
add.bind(null, 10, 20)()    // evaluates to 30
```

- `apply` binds a value to `this` within your function, and spreads its second
  argument over your function’s parameters.
- `call` does the same, but applies its arguments in order instead of spreading.
- `bind()` is similar, in that it `binds` a `this`-argument and a list of
  arguments to your function.
  - The difference is that bind does not invoke your function; instead, it
    returns a new function that you can then invoke with `()`, `.call`, or
    `.apply`, passing more arguments in to be bound to the so far unbound
    parameters if you want.

#### TSC Flag: `strictBindCallApply`

To safely use `.call`, `.apply`, and `.bind` in your code, be sure to enable
the `strictBindCallApply` option in your `tsconfig.json` (it’s automatically
enabled if you already enabled `strict` mode).

### Typing this

The `this` variable is defined for every function, not just for those functions
that live as methods on classes. `this` has a different value depending on how
you called your function, which can make it notoriously fragile and hard to
reason about.

💡 For this reason, a lot of teams ban `this` everywhere except in class
methods — to do this for your codebase too, enable the `no-invalid-this` TSLint
rule.

The general rule is that `this` will take the value of the thing to the left of
the dot when invoking a method.

```ts
let x = {
  a() {
    return this
  }
}
x.a() // this is the object x in the body of a()
```

But if at some point you reassign `a` before calling it, the result will
change!

```ts
let a = x.a
a() // now, this is undefined in the body of a()
```

Say you have a utility function for formatting dates that looks like this:

```ts
function fancyDate() {
  return `${this.getDate()}/${this.getMonth}/${this.getFullYear()}`
}
```

To use `fancyDate`, you have to call it with a `Date` bound to this:

```ts
fancyDate.call(new Date) // evaluates to "4/14/2005"
```

If you forget to bind a `Date` to `this`, you’ll get a runtime exception!

```ts
fancyDate() // Uncaught TypeError: this.getDate is not a function
```

If your function uses `this`, be sure to declare your expected `this` type as
your function’s first parameter (before any additional parameters), and
TypeScript will enforce that `this` really is what you say it is at every call
site. `this` isn’t treated like other parameters — it’s a reserved word when
used as part of a function signature:

```ts
function fancyDate(this: Date) {
  return `${this.getDate()}/${this.getMonth()}/${this.getFullYear()}`
}

fancyDate.call(new Date) // evaluates to "6/13/2008"

fancyDate() // Error TS2684: The 'this' context of type 'void' is
            // not assignable to method's 'this' of type 'Date'.
```

#### TSC Flag: `noImplicitThis`

To enforce that `this` types are always explicitly annotated in functions,
enable the `noImplicitThis` setting in your `tsconfig.json`. `strict` mode
includes `noImplicitThis`.

Note that `noImplicitThis` doesn’t enforce `this`-annotations for classes, or
for functions on objects.

### Generator Functions

Generators are lazy — that is, they only compute the next value when a consumer
asks for it — they can do things that can be hard to do otherwise, like
generate infinite lists.

```ts
function* createFibonacciGenerator() {
  let a = 0
  let b = 1
  while (true) {
    yield a;
    [a, b] = [b, a + b]
  }
}

let fibonacciGenerator = createFibonacciGenerator() // IterableIterator<number>
fibonacciGenerator.next()               // evaluates to {value: 0, done: false}
fibonacciGenerator.next()               // evaluates to {value: 1, done: false}
fibonacciGenerator.next()               // evaluates to {value: 1, done: false}
fibonacciGenerator.next()               // evaluates to {value: 2, done: false}
fibonacciGenerator.next()               // evaluates to {value: 3, done: false}
fibonacciGenerator.next()               // evaluates to {value: 5, done: false}
```

Calling a generator returns an iterable iterator.

TypeScript is able to infer the type of our iterator from the type of the value
we yielded.

You can also explicitly annotate a generator, wrapping the type it yields in an
`IterableIterator`:

```ts
function* createNumbers(): IterableIterator<number> {
  let n = 0
  while (1) {
    yield n++
  }
}

let numbers = createNumbers()
numbers.next()                  // evaluates to {value: 0, done: false}
numbers.next()                  // evaluates to {value: 1, done: false}
numbers.next()                  // evaluates to {value: 2, done: false}
```

### Iterators

- **Generators** are a way to produce a stream of values while **iterators**
  are a way to consume those values.
- **Iterable**: Any object that contains a property called `Symbol.iterator`,
  whose value is a function that returns an **iterator**.
- **Iterator**: Any object that defines a method called `next`, which returns
  an object with the properties `value` and `done`.

An iterable iterator defines both a `Symbol.iterator` property and a `next`
method. You can manually define an iterator or an iterable by creating an
object (or a class) that implements `Symbol.iterator` or `next`.

```ts
let numbers = {
  *[Symbol.iterator]() {
    for (let n = 1; n <= 10; n++) {
      yield n
    }
  }
}
```

In other words, `numbers` is an iterable, and calling the generator function
`numbers[Symbol.iterator]()` returns an iterable iterator.

```ts
// Iterate over an iterator with for-of
for (let a of numbers) {
  // 1, 2, 3, etc.
}

// Spread an iterator
let allNumbers = [...numbers] // number[]

// Destructure an iterator
let [one, two, ...rest] = numbers // [number, number, number[]]
```

#### TSC Flag: downlevelIteration

If you’re compiling your TypeScript to a JavaScript version older than ES2015,
you can enable custom iterators with the `downlevelIteration` flag in your
`tsconfig.json`.

You may want to keep `downlevelIteration` disabled if your application is
especially sensitive to bundle size: it takes a lot of code to get custom
iterators working in older environments.

### Call Signatures

```ts
function sum(a: number, b: number): number {
  return a + b
}
```

Its type is: `Function`

But the `Function` type is not what you want to use most of the time.
`Function` is a catchall type for all functions, and doesn’t tell you anything
about the specific function that it types.

In TypeScript we can express its type as:

```ts
(a: number, b: number) => number
```

This is TypeScript’s syntax for a function’s type, or ***call signature***
(also called a ***type signature***). It looks remarkably similar to an arrow
function — this is intentional! When you pass functions around as arguments, or
return them from other functions, this is the syntax you’ll use to type them.

The parameter names `a` and `b` just serve as documentation, and don’t affect
the assignability of a function with that type.

Function ***call signatures*** only contain ***type-level*** code — that is,
types only, no values. That means function call signatures can express
parameter types, `this` types, return types, rest types, and optional types,
and they cannot express default values. And because they have no body for
TypeScript to infer from, call signatures require explicit return type
annotations.

#### Type Level and Value Level Code

- ***type-level code***: code that consists exclusively of types and type
  operators.
- ***value-level code***: which is everything else.

A rule of thumb is: if it’s valid JavaScript code, then it’s value-level;
if it’s valid TypeScript but not valid JavaScript, then it’s type-level.

- The exceptions to this rule of thumb are `enums`, `classes`, and `namespaces`.
  Enums and classes each generate both a type and a value, and namespaces exist
  just at the value level.

```ts
// function greet(name: string)
type Greet = (name: string) => string

// function log(message: string, userId?: string)
type Log = (message: string, userId?: string) => void

// function sumVariadicSafe(...numbers: number[]): number
type SumVariadicSafe = (...numbers: number[]) => number
```

How can you declare a function that implements a call signature? You simply
combine the call signature with a function expression that implements it.

Rewrite `Log` to use its shiny new signature:

```ts
type Log = (message: string, userId?: string) => void

let log: Log = (
  message,
  userId = 'Not signed in'
) => {
  let time = new Date().toISOString()
  console.log(time, message, userId)
}
```

1. We declare a function expression `log`, and explicitly type it as type `Log`.
2. We don’t need to annotate our parameters twice, since message is already
   annotated as a string as part of the definition for `Log`. Instead, we let
   TypeScript infer it for us from Log.
3. We add a default value for `userId`, since we captured `userId`’s type in
   our signature for `Log`, but we couldn’t capture the default value as part
   of `Log` because `Log` is a type and can’t contain values.
4. We don’t need to annotate our return type again, since we already declared
   it as `void` in our `Log` type.

### Contextual Typing

The last example didn’t have to explicitly annotate function parameter types.
Because we already declared that `log` is of type `Log`, TypeScript is able to
infer from context that `message` has to be of type `string`. This is called
***contextual typing***.

```ts
function times(
  f: (index: number) => void,
  n: number
) {
  for (let i = 0; i < n; i++) {
    f(i)
  }
}
```

When you call `times`, you don’t have to explicitly annotate the function you
pass to `times` if you declare that function inline:

```ts
times(n => console.log(n), 4)
```

TypeScript infers from context that `n` is a `number` — we declared that `f`’s
argument `index` is a `number` in times’s signature, and TypeScript infers that
`n` is that argument, so it must be a `number`.

⚠️ If we didn’t declare `f` inline, TypeScript wouldn’t have been able to infer
its type:

```ts
function f(n) { // Error TS7006: Parameter 'n' implicitly has an 'any' type.
  console.log(n)
}

times(f, 4)
```

### Overloaded Function Types

`type Fn = (...) => ...` is a ***shorthand call signature***.

```ts
// Shorthand call signature
type Log = (message: string, userId?: string) => void

// Full call signature
type Log = {
  (message: string, userId?: string): void
}
```

The two are completely equivalent in every way, and differ only in syntax.

For more complicated functions, there are a few good use cases for full
signatures.

The first of these is ***overloading*** a function type.

- ***Overloaded function***: A function with multiple call signatures

It’s a common pattern in JavaScript for there to be multiple ways to call a
given function; not only that, but sometimes the output type will actually
depend on the input type for an argument!

TypeScript models this dynamism — overloaded function declarations, and a
function’s output type depending on its input type — with its static type
system.

```ts
type Reserve = {
  (from: Date, to: Date, destination: string): Reservation
}

let reserve: Reserve = (from, to, destination) => {
  // ...
}
```

We might repurpose our API to support one-way trips too:

```ts
type Reserve = {
  (from: Date, to: Date, destination: string): Reservation
  (from: Date, destination: string): Reservation
}

// [ts] Type '(from: any, to: any, destination: any) => void' is not assignable
// to type 'Reserve'
let reserve: Reserve = (from, to, destination) => {
  // ...
}
```

If you declare a set of overload signatures for a function `f`, from a caller’s
point of view `f`’s type is the union of those overload signatures. But from
`f`’s ***implementation’s*** point of view, there needs to be a single,
combined type that can actually be implemented. You need to manually declare
this combined call signature when implementing `f` — it won’t be inferred for
you.

```ts
type Reserve = {
  (from: Date, to: Date, destination: string): Reservation
  (from: Date, destination: string): Reservation
}

let reserve: Reserve = (
  from: Date,
  toOrDestination: Date | string,
  destination?: string
) => {
  // ...
}
```

Note that the combined signature isn’t visible to functions that call
`reserve`; from a consumer’s point of view, `Reserve`’s signature is:

```ts
type Reserve = {
  (from: Date, to: Date, destination: string): Reservation
  (from: Date, destination: string): Reservation
}
```

Notably, this doesn’t include the combined signature we created:

```ts
// Wrong!
type Reserve = {
  (from: Date, to: Date, destination: string): Reservation
  (from: Date, destination: string): Reservation
  (from: Date, toOrDestination: Date | string,
    destination?: string): Reservation
}
```

Since `reserve` might be called in either of two ways, when you implement
`reserve` you have to prove to TypeScript that you checked how it was called:

```ts
let reserve: Reserve = (
  from: Date,
  toOrDestination: Date | string,
  destination?: string
) => {
  if (toOrDestination instanceof Date && destination !== undefined) {
    // Book a round trip
    } else if (typeof toOrDestination === 'string') {
    // Book a one-way trip
  }
}
```

#### Keeping Overload Signatures Specific

In general, each overload signature has to be assignable to the
implementation’s signature when declaring an overloaded function type. That
means you can be overly general when declaring the implementation’s signature,
so long as all of your overloads are assignable to it.

```ts
let reserve: Reserve = (
  from: any,
  toOrDestination: any,
  destination?: any
) => {
  // ...
}
```

💡 When using overloads, try to keep your implementation’s signature as specific
as possible to make it easier to implement the function. That means preferring
`Date` over `any`, and a union of `Date | string` over `any`.

❓ Why does keeping types narrow make it easier to implement a function with a
given signature?

If you type a parameter as `any` and want to use it as a `Date`, you have to
prove to TypeScript that it’s actually a date to use it safely, and to get the
benefit of autocomplete:

```ts
function getMonth(date: any): number | undefined {
  if (date instanceof Date) {
    return date.getMonth()
  }
}
```

But if you typed the parameter as a `Date` upfront, you don’t need to do extra
work in the implementation:

```ts
function getMonth(date: Date): number {
  return date.getMonth()
}
```

Overloads come up naturally in browser DOM APIs. The `createElement` DOM API is
used to create a new HTML element. It takes a `string` corresponding to an HTML
tag and returns a new HTML element of that tag’s type. TypeScript comes with
built-in types for each HTML element. These include:

- `HTMLAnchorElement` for `<a`> elements
- `HTMLCanvasElement` for `<canvas>` elements
- `HTMLTableElement` for `<table>` elements

Overloaded call signatures are a natural way to model how `createElement` works.

```ts
type CreateElement = {
  (tag: 'a'): HTMLAnchorElement       // 1.
  (tag: 'canvas'): HTMLCanvasElement
  (tag: 'table'): HTMLTableElement
  (tag: string): HTMLElement          // 2.
}

let createElement: CreateElement = (tag: string): HTMLElement => {  // 3.
  // ...
}
```

1. We overload on the parameter’s type, matching on it with string literal
   types.
2. We add a catchall case: if the user passed a custom tag name, or a
   cutting-edge experimental tag name that hasn’t made its way into
   TypeScript’s built-in type declarations yet, we return a generic
   `HTMLElement`.
    - Since TypeScript resolves overloads in the order they were declared, when
      you call `createElement` with a string that doesn’t have a specific
      overload defined, TypeScript will fall back to `HTMLElement`.
      - Mostly — TypeScript hoists literal overloads above nonliteral ones,
        before resolving them in order.
      - 💡 You might not want to depend on this feature, though, since it can
        make your overloads hard to understand for other engineers who aren’t
        familiar with this behavior.
3. To type the implementation’s parameter, we combine all the types that
   parameter might have in `createElement`’s overload signatures, resulting in
   `'a' | 'canvas' | 'table' | string`. Since the three string literal types
   are all subtypes of `string`, the type reduces to just `string`.

What if we want to overload a function declaration? You can use an equivalent
syntax for function declarations.

```ts
function createElement(tag: 'a'): HTMLAnchorElement
function createElement(tag: 'canvas'): HTMLCanvasElement
function createElement(tag: 'table'): HTMLTableElement
function createElement(tag: string): HTMLElement {
  // ...
}
```

Which syntax you use is up to you, and depends on what kind of function you’re
overloading (function expression or function declarations).

You can also use them to model properties on functions. Since JavaScript
functions are just callable objects, you can assign properties to them to do
things like:

```ts
function warnUser(warning) {
  if (warnUser.wasCalled) {
    return
  }
  warnUser.wasCalled = true
  alert(warning)
}

warnUser.wasCalled = false
```

Use TypeScript to type warnUser’s full signature:

```ts
type WarnUser = {
  (warning: string): void
  wasCalled: boolean
}
```

## Polymorphism

What’s a concrete type? Every type we’ve seen so far is concrete:

- `boolean`
- `string`
- `Date[]`
- `{a: number} | {b: string}`
- `(numbers: number[]) => number`

Concrete types are useful when you know precisely what type you’re expecting, and want to verify that type was actually passed. But sometimes, you don’t know what type to expect beforehand, and you don’t want to restrict your function’s behavior to a specific type!

```js
function filter(array, f) {
  let result = []
  for (let i = 0; i < array.length; i++) {
    let item = array[i]
    if (f(item)) {
      result.push(item)
    }
  }
  return result
}

filter([1, 2, 3, 4], _ => _ < 3) // evaluates to [1, 2]
```

`filter`’s full type signature, and adding some placeholder unknowns for the types:

```ts
type Filter = {
  (array: unknown, f: unknown) => unknown[]
}
```

```ts
type Filter = {
  (array: number[], f: (item: number) => boolean): number[]
}
```

Let’s try to use an overload to extend it to work on arrays of strings too:

```ts
type Filter = {
  (array: number[], f: (item: number) => boolean): number[]
  (array: string[], f: (item: string) => boolean): string[]
}
```

```ts
type Filter = {
  (array: number[], f: (item: number) => boolean): number[]
  (array: string[], f: (item: string) => boolean): string[]
  (array: object[], f: (item: object) => boolean): object[]
}
```

If you implement a `filter` function with that signature (that is, filter: Filter), and try to use it, you’ll get:

```ts
let names = [
  {firstName: 'beth'},
  {firstName: 'caitlyn'},
  {firstName: 'xin'}
]

let result = filter(
  names,
  _ => _.firstName.startsWith('b')
) // Error TS2339: Property 'firstName' does not exist on type 'object'.
result[0].firstName // Error TS2339: Property 'firstName' does not exist
                    // on type 'object'.
```

### Generic type parameter

A placeholder type used to enforce a type-level constraint in multiple places. Also known as ***polymorphic type parameter***.

Rewrite it with a generic type parameter `T`:

```ts
type Filter = {
  <T>(array: T[], f: (item: T) => boolean): T[]
}
```

TypeScript infers `T` from the type we pass in for array. Once TypeScript
infers what `T` is for a given call to filter, it substitutes that type in for
every `T` it sees.

`T` is like a placeholder type, to be filled in by the typechecker from context;
it *parameterizes* Filter’s type, which is why we call it a
***generic type parameter***.

You can declare as many comma-separated generic type parameters as you want
between a pair of angle brackets.

💡 `T` is just a type name, and we could have used any other name instead. By
convention, people use uppercase single-letter names starting with the letter
`T` and continuing to `U`, `V`, `W`, and so on depending on how many generics
they need.

If you’re declaring a lot of generics in a row or are using them in a
complicated way, consider deviating from this convention and using more
descriptive names like `Value` or `WidgetType` instead.

Some people prefer to start at `A` instead of `T`.

Like a function’s parameter gets re-bound every time you call that function, so
each call to `filter` gets its own binding for `T`:

```ts
type Filter = {
  <T>(array: T[], f: (item: T) => boolean): T[]
}

let filter: Filter = (array, f) => // ...

// (a) T is bound to number
filter([1, 2, 3], _ => _ > 2)

// (b) T is bound to string
filter(['a', 'b'], _ => _ !== 'b')

// (c) T is bound to {firstName: string}
let names = [
  {firstName: 'beth'},
  {firstName: 'caitlyn'},
  {firstName: 'xin'}
]
filter(names, _ => _.firstName.startsWith('b'))
```

How TypeScript binds `T` for (a):

1. From the type signature for `filter`, TypeScript knows that `array` is an
   array of elements of some type `T`.
2. TypeScript notices that we passed in the array `[1, 2, 3]`, so `T` must be
   `number`.
3. Wherever TypeScript sees a `T`, it substitutes in the `number` type. So the
   parameter `f: (item: T) => boolean` becomes `f: (item: number) => boolean`,
   and the return `type T[]` becomes `number[]`.
4. TypeScript checks that the types all satisfy assignability, and that the
   function we passed in as `f` is assignable to its freshly inferred signature.

Generic types can also be used in type aliases, classes, and interfaces.

💡 Use generics whenever you can. They will help keep your code general,
reusable, and terse.

### When Are Generics Bound?

The place where you declare a generic type doesn’t just scope the type, but
also dictates when TypeScript will bind a concrete type to your generic. From
the last example:

```ts
type Filter = {
  <T>(array: T[], f: (item: T) => boolean): T[]
}

let filter: Filter = (array, f) =>
  // ...
```

Because we declared `<T>` as part of a call signature (right before the
signature’s opening parenthesis, `()`, TypeScript will bind a concrete type to
`T` when we actually call a function of type `Filter`.

If we’d instead scoped `T` to the type alias `Filter`, TypeScript would have
required us to bind a type explicitly when we used `Filter`:

```ts
type Filter<T> = {
  (array: T[], f: (item: T) => boolean): T[]
}

let filter: Filter = (array, f) =>  // Error TS2314: Generic type 'Filter'
  // ...                            // requires 1 type argument(s).

type OtherFilter = Filter           // Error TS2314: Generic type 'Filter'
                                    // requires 1 type argument(s).

let filter: Filter<number> = (array, f) =>
  // ...

type StringFilter = Filter<string>
let stringFilter: StringFilter = (array, f) =>
  // ...
```

Generally, TypeScript will bind concrete types to your generic when you use the
generic: for functions, it’s when you call them; for classes, it’s when you
instantiate them; and for type aliases and interfaces, it’s when you use or
implement them.

### Where Can You Declare Generics?

```ts
// way 1.
type Filter = {
  <T>(array: T[], f: (item: T) => boolean): T[]
}
let filter: Filter = // ...

// way 2.
type Filter<T> = {
  (array: T[], f: (item: T) => boolean): T[]
}
let filter: Filter<number> = // ...

// way 3.
type Filter = <T>(array: T[], f: (item: T) => boolean) => T[]
let filter: Filter = // ...

// way 4.
type Filter<T> = (array: T[], f: (item: T) => boolean) => T[]
let filter: Filter<string> = // ...

// way 5.
function filter<T>(array: T[], f: (item: T) => boolean): T[] {
  // ...
}
```

1. A full call signature, with `T` scoped to an individual signature. Because
   `T` is scoped to a single signature, TypeScript will bind the `T` in this
   signature to a concrete type when you call a function of type `filter`. Each
   call to `filter` will get its own binding for `T`.
2. A full call signature, with `T` scoped to all of the signatures. Because `T`
   is declared as part of Filter’s type (and not part of a specific signature’s
   type), TypeScript will bind `T` when you declare a function of type `Filter`.
3. Like 1., but a shorthand call signature instead of a full one.
4. Like 2., but a shorthand call signature instead of a full one.
5. A named function call signature, with `T` scoped to the signature.
   TypeScript will bind a concrete type to `T` when you call `filter`, and each
   call to `filter` will get its own binding for `T`.

```ts
function map(array: unknown[], f: (item: unknown) => unknown): unknown[] {
  let result = []
  for (let i = 0; i < array.length; i++) {
    result[i] = f(array[i])
  }
  return result
}
```

```ts
function map<T, U>(array: T[], f: (item: T) => U): U[] {
  let result = []
  for (let i = 0; i < array.length; i++) {
    result[i] = f(array[i])
  }
  return result
}
```

#### `filter` and `map` in the Standard Library

```ts
interface Array<T> {
  filter(
    callbackfn: (value: T, index: number, array: T[]) => any,
    thisArg?: any
  ): T[]
  map<U>(
    callbackfn: (value: T, index: number, array: T[]) => U,
    thisArg?: any
  ): U[]
}
```

This definition says that `filter` and `map` are functions on an array of type
`T`. They both take a function `callbackfn`, and a type for `this` inside of
the function.

`filter` uses the generic `T` that’s scoped to the entire `Array` interface.
`map` uses `T` too, and adds a second generic `U` that’s scoped just to the
`map` function. That means TypeScript will bind a concrete type to `T` when you
create an array, and every call to `filter` and `map` on that array will share
that concrete type. Every time you call `map`, that call will get its own
binding for `U`, in addition to having access to the already-bound `T`.

Arrays can contain values of `any` type, so we call that type `T` and can say
things like "`.push` takes an argument of type `T`,” or "`.map` maps from an
array of `T`s to an array of `U`s”.

### Generic Type Inference

In most cases, TypeScript does a great job of inferring generic types for you.

```ts
function map<T, U>(array: T[], f: (item: T) => U): U[] {
  // ...
}

map(
  ['a', 'b', 'c'],  // An array of T
  _ => _ === 'a'    // A function that returns a U
)
```

Explicit annotations for generics are all-or-nothing; either annotate every
required generic type, or none of them:

```ts
map<string, boolean>(
  ['a', 'b', 'c'],
  _ => _ === 'a'
)

map<string>(       // Error TS2558: Expected 2 type arguments, but got 1.
  ['a', 'b', 'c'],
  _ => _ === 'a'
)
```

```ts
// OK, because boolean is assignable to boolean | string
map<string, boolean | string>(
  ['a', 'b', 'c'],
  _ => _ === 'a'
)

map<string, number>(
  ['a', 'b', 'c'],
  _ => _ === 'a'    // Error TS2322: Type 'boolean' is not assignable
)                   // to type 'number'.
```

Since TypeScript infers concrete types for your generics from the arguments you
pass into your generic function, sometimes you’ll hit a case like this:

```ts
let promise = new Promise(resolve =>
  resolve(45)
)
promise.then(result => // Inferred as {}
  result * 4  // Error TS2362: The left-hand side of an arithmetic operation
)             // must be of type 'any', 'number', 'bigint', or an enum type.
```

Why did TypeScript infer `result` to be `{}`? Because TypeScript only uses the
types of a generic function’s arguments to infer a generic’s type, it defaulted
`T` to `{}`!

To fix this, we have to explicitly annotate Promises generic type parameter:

```ts
let promise = new Promise<number>(resolve =>
  resolve(45)
)
promise.then(result => // number
  result * 4
)
```

### Generic Type Aliases

```ts
type MyEvent<T> = {
  target: T
  type: string
}
```

⚠️ This is the only valid place to declare a generic type in a type alias: right
after the type alias’s name, before its assignment (`=`).

`MyEvent`’s `target` property points to the element the event happened on:
a `<button />`, a `<div />`, and so on.

```ts
type ButtonEvent = MyEvent<HTMLButtonElement>
```

When you use a generic type like `MyEvent`, you have to explicitly bind its
type parameters when you use the type; they won’t be inferred for you:

```ts
let myEvent: MyEvent<HTMLButtonElement | null> = {
  target: document.querySelector('#myButton'),
  type: 'click'
}
```

You can use `MyEvent` to build another type — say, `TimedEvent`. When the
generic `T` in `TimedEvent` is bound, TypeScript will also bind it to
`MyEvent`:

```ts
type TimedEvent<T> = {
  event: MyEvent<T>
  from: Date
  to: Date
}
```

You can use a generic type alias in a function’s signature, too. When
TypeScript binds a type to `T`, it’ll also bind it to `MyEvent` for you:

```ts
function triggerEvent<T>(event: MyEvent<T>): void {
  // ...
}

triggerEvent({ // T is Element | null
  target: document.querySelector('#myButton'),
  type: 'mouseover'
})
```

1. We call `triggerEvent` with an object.
2. TypeScript sees that according to our function’s signature, the argument we
   passed has to have the type `MyEvent<T>`. It also notices that we defined
   `MyEvent<T>` as `{target: T, type: string}`.
3. TypeScript notices that the `target` field of the object we passed is
   `document.querySelector('#myButton')`. That implies that `T` must be
   whatever type `document.querySelector('#myButton')` is: `Element | null`. So
   `T` is now bound to `Element | null`.
4. TypeScript goes through and replaces every occurrence of `T` with
   `Element | null`.
5. TypeScript checks that all of our types satisfy assignability.

### Bounded Polymorphism

Sometimes, saying “this thing is of some generic type `T` and that thing has to
have the same type `T`" just isn’t enough. Sometimes you also want to say “the
type `U` should be at least `T`.” We call this putting an upper bound on `U`.

Let’s say we’re implementing a binary tree, and have three types of nodes:

1. Regular `TreeNodes`
2. `LeafNodes`, which are `TreeNodes` that don’t have children
3. `InnerNodes`, which are `TreeNodes` that do have children

```ts
type TreeNode = {
  value: string
}
type LeafNode = TreeNode & {
  isLeaf: true
}
type InnerNode = TreeNode & {
  children: [TreeNode] | [TreeNode, TreeNode]
}
```

What we’re saying is: a `TreeNode` is an object with a single property, `value`.
The `LeafNode` type has all the properties `TreeNode` has, plus a property
`isLeaf` that’s always `true`. `InnerNode` also has all of `TreeNode`’s
properties, plus a children property that points to either one or two children.

```ts
let a: TreeNode = {value: 'a'}
let b: LeafNode = {value: 'b', isLeaf: true}
let c: InnerNode = {value: 'c', children: [b]}

let a1 = mapNode(a, _ => _.toUpperCase()) // TreeNode
let b1 = mapNode(b, _ => _.toUpperCase()) // LeafNode
let c1 = mapNode(c, _ => _.toUpperCase()) // InnerNode
```

```ts
function mapNode<T extends TreeNode>( // 1.
  node: T,  // 2.
  f: (value: string) => string
): T {  // 3.
  return {
    ...node,
    value: f(node.value)
  }
}
```

1. `mapNode` is a function that defines a single generic type parameter, `T`.
   `T` has an upper bound of `TreeNode`. That is, `T` can be either a
   `TreeNode`, or a subtype of `TreeNode`.
2. `mapNode` takes two parameters, the first of which is a node of type `T`.
   Because we said `node` extends `TreeNode`, if we passed in something that’s
   not a `TreeNode` — say, an empty object `{}`, `null`, or an array of
   `TreeNodes` — that would be an instant red squiggly. `node` has to be either
   a `TreeNode` or a subtype of `TreeNode`.
3. `mapNode` returns a value of type `T`. Remember that `T` might be a
   `TreeNode`, or any subtype of `TreeNode`.

Why did we have to declare `T` that way?

- If we had typed `T` as just `T`, then `mapNode` would have thrown a
  compile-time error, because you can’t safely read `node.value` on an unbounded
  `node` of type `T` (what if a user passes in a `number`?).
- If we had left off the `T` entirely and declared `mapNode` as
  `(node: TreeNode, f: (value: string) => string) => TreeNode`, then we would
  have lost information after mapping a `node`: `a1`, `b1`, and `c1` would all
  just be `TreeNodes`.

By saying that `T extends TreeNode`, we get to preserve the input `node`’s
specific type (`TreeNode`, `LeafNode`, or `InnerNode`), even after mapping it.

#### Bounded polymorphism with multiple constraints

What if you want multiple type constraints?

Just extend the intersection (`&`) of those constraints:

```ts
type HasSides = {numberOfSides: number}
type SidesHaveLength = {sideLength: number}

function logPerimeter<  // 1.
  Shape extends HasSides & SidesHaveLength  // 2。
>(s: Shape): Shape {  // 3.
  console.log(s.numberOfSides * s.sideLength)
  return s
}

type Square = HasSides & SidesHaveLength
let square: Square = {numberOfSides: 4, sideLength: 3}
logPerimeter(square) // Square, logs "12"
```

1. `logPerimeter` is a function that takes a single argument `s` of type
   `Shape`.
2. `Shape` is a generic type that extends both the `HasSides` type and the
   `SidesHaveLength` type. In other words, a `Shape` has to at least have sides
   with lengths.
3. `logPerimeter` returns a value of the exact same type you gave it.

#### Using bounded polymorphism to model arity

***variadic functions***: functions that take any number of arguments.

```ts
function call(
  f: (...args: unknown[]) => unknown,
  ...args: unknown[]
): unknown {
  return f(...args)
}

function fill(length: number, value: string): string[] {
  return Array.from({length}, () => value)
}

call(fill, 10, 'a') // evaluates to an array of 10 'a's
```

The constraints we want to express are:

- `f` should be a function that takes some set of arguments `T`, and returns
  some type `R`. We don’t know how many arguments it’ll have ahead of time.
- `call` takes `f`, along with the same set of arguments `T` that `f` itself
  takes. Again, we don’t know exactly how many arguments to expect ahead of
  time.
- `call` returns the same type `R` that `f` returns.

```ts
function call<T extends unknown[], R>(  // 1.
  f: (...args: T) => R, // 2.
  ...args: T  // 3.
): R {  // 4.
  return f(...args)
}
```

1. `call` is a variadic function that has two type parameters: `T` and `R`. `T`
   is a subtype of `unknown[]`; that is, `T` is an array or tuple of any type.
2. `call`’s first parameter is a function `f`. `f` is also variadic, and its
   arguments share a type with `args`: whatever type `args` is, `f` arguments
   have the same exact type.
3. In addition to a function `f`, `call` has a variable number of additional
   parameters `...args`. `args` is a rest parameter — that is, a parameter that
   describes a variable number of arguments. `args`’s type is `T`, and `T` has
   to be an `array` type (in fact, if we forgot to say that T extends an `array`
   type, TypeScript would throw a squiggly at us), so TypeScript will infer a
   tuple type for `T` based on the specific arguments we passed in for `args`.
4. `call` returns a value of type `R` (`R` is bound to whatever type `f`
   returns).

```ts
let a = call(fill, 10, 'a')       // string[]
let b = call(fill, 10)            // Error TS2554: Expected 3 arguments; got 2.
let c = call(fill, 10, 'a', 'z')  // Error TS2554: Expected 3 arguments; got 4.
```

### Generic Type Defaults

```ts
type MyEvent<T> = {
  target: T
  type: string
}
```

To create a new event, we have to explicitly bind a generic type to `MyEvent`,
representing the type of HTML element that the event was dispatched on:

```ts
let buttonEvent: MyEvent<HTMLButtonElement> = {
  target: myButton,
  type: string
}
```

As a convenience for when we don’t know the specific element type that `MyEvent`
will be bound to beforehand, we can add a default for `MyEvent`’s generic:

```ts
type MyEvent<T = HTMLElement> = {
  target: T
  type: string
}
```

We can also add a bound to `T`, to make sure that `T` is an HTML element:

```ts
type MyEvent<T extends HTMLElement = HTMLElement> = {
  target: T
  type: string
}
```

Now, we can easily create an event that’s not specific to a particular HTML
element type, and we don’t have to manually bind `MyEvents T` to `HTMLElement`
when we create the event:

```ts
let myEvent: MyEvent = {
  target: myElement,
  type: string
}
```

Note that like optional parameters in functions, generic types with defaults
have to appear after generic types without defaults:

```ts
// Good
type MyEvent2<
  Type extends string,
  Target extends HTMLElement = HTMLElement,
> = {
  target: Target
  type: Type
}

// Bad
type MyEvent3<
  Target extends HTMLElement = HTMLElement,
  Type extends string // Error TS2706: Required type parameters may
> = {                 // not follow optional type parameters.
  target: Target
  type: Type
}
```

## Type-Driven Development

```ts
function map<T, U>(array: T[], f: (item: T) => U): U[] {
  // ...
}
```

You should have some intuition for what map does: it takes an `array` of `T`
and a function that maps from a `T` to a `U`, and returns an `array` of `U`.

By sketching out your program out at the type level first, you make sure that
everything makes sense at a high level before you get down to your
implementations.
