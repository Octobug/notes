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

>>>>> progress
