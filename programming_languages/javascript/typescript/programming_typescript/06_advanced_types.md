# Chapter 6: Advanced Types

- [Chapter 6: Advanced Types](#chapter-6-advanced-types)
  - [Relationships Between Types](#relationships-between-types)
    - [Subtypes and Supertypes](#subtypes-and-supertypes)
      - [Subtype](#subtype)
      - [Supertype](#supertype)
    - [Variance](#variance)
      - [Shape and array variance](#shape-and-array-variance)
      - [Function variance](#function-variance)
        - [TSC Flag: `strictFunctionTypes`](#tsc-flag-strictfunctiontypes)
    - [Assignability](#assignability)
    - [Type Widening](#type-widening)
      - [The const type](#the-const-type)
      - [Excess property checking](#excess-property-checking)
    - [Refinement](#refinement)
      - [Discriminated union types](#discriminated-union-types)
  - [Totality](#totality)
    - [TSC Flag: noImplicitReturns](#tsc-flag-noimplicitreturns)
  - [Advanced Object Types](#advanced-object-types)
    - [Type Operators for Object Types](#type-operators-for-object-types)
      - [The keying-in operator](#the-keying-in-operator)
      - [The keyof operator](#the-keyof-operator)
        - [TSC Flag: keyofStringsOnly](#tsc-flag-keyofstringsonly)
    - [The Record Type](#the-record-type)
    - [Mapped Types](#mapped-types)
      - [Built-in mapped types](#built-in-mapped-types)
    - [Companion Object Pattern](#companion-object-pattern)
  - [Advanced Function Types](#advanced-function-types)
    - [Improving Type Inference for Tuples](#improving-type-inference-for-tuples)
    - [User-Defined Type Guards](#user-defined-type-guards)
  - [Conditional Types](#conditional-types)
    - [Distributive Conditionals](#distributive-conditionals)
    - [The infer Keyword](#the-infer-keyword)
    - [Built-in Conditional Types](#built-in-conditional-types)
  - [Escape Hatches](#escape-hatches)
    - [Type Assertions](#type-assertions)
    - [Nonnull Assertions](#nonnull-assertions)
    - [Definite Assignment Assertions](#definite-assignment-assertions)
  - [Simulating Nominal Types](#simulating-nominal-types)

## Relationships Between Types

### Subtypes and Supertypes

#### Subtype

If you have two types `A` and `B`, and `B` is a subtype of `A`, then you can
safely use a `B` anywhere an `A` is required.

#### Supertype

If you have two types `A` and `B`, and `B` is a supertype of `A`, then you can
safely use an `A` anywhere a `B` is required.

The subtype relations built into TypeScript:

- Array is a subtype of Object.
- Tuple is a subtype of Array.
- Everything is a subtype of `any`.
- `never` is a subtype of everything.
- If you have a class `Bird` that extends `Animal`, then `Bird` is a subtype of
  `Animal`.

That means:

- Anywhere you need an Object you can also use an Array.
- Anywhere you need an Array you can also use a Tuple.
- Anywhere you need an `any` you can also use an Object.
- You can use a `never` anywhere.
- Anywhere you need an `Animal` you can also use a `Bird`.

And vice versa:

- Array is a supertype of Tuple.
- Object is a supertype of Array.
- Any is a supertype of everything.
- Never is a supertype of nothing.
- `Animal` is a supertype of `Bird`.

### Variance

Consider these cases:

- When is `Array<A>` a subtype of `Array<B>`?
- When is a shape `A` a subtype of another shape `B`?
- When is a function `(a: A) => B` a subtype of another function `(c: C) => D`?

In fact, subtyping rules for these kinds of complex types are a big point of
disagreement among programming languages — almost no two languages are alike!

Definitions for  describing subtyping in this book:

- `A <: B` means "A is a subtype of or the same as the type B.”
- `A >: B` means "A is a supertype of or the same as the type B.”

#### Shape and array variance

```ts
// An existing user that we got from the server
type ExistingUser = {
    id: number
    name: string
}

// A new user that hasn't been saved to the server yet
type NewUser = {
    name: string
}
```

Now suppose an intern at your company is tasked with writing some code to delete a user:

```ts
function deleteUser(user: {id?: number, name: string}) {
    delete user.id
}

let existingUser: ExistingUser = {
    id: 123456,
    name: 'Ima User'
}

deleteUser(existingUser)
```

Notice that the type of the `id` property (`number`) is a subtype of the
expected type `(number | undefined)`. Therefore the entire object
`{id: number, name: string}` is a subtype of `{id?: number, name: string}`, so
TypeScript lets it fly.

After passing an `ExistingUser` to `deleteUser`, TypeScript doesn’t know that
the user’s `id` has been deleted, so if we read `existingUser.id` after
deleting it with `deleteUser(existingUser)`, TypeScript still thinks
`existingUser.id` is of type number!

So why does TypeScript allow it? In general, TypeScript is not designed to be
perfectly safe; instead, its type system tries to strike a balance between
catching real mistakes and being easy to use. This specific case of unsafety is
a practical one: since destructive updates (like deleting a property) are
relatively rare in practice, TypeScript is lax and lets you assign an object to
a place where its supertype is expected.

What about the opposite direction — can you assign an object to a place where
its subtype is expected?

```ts
type LegacyUser = {
  id?: number | string
  name: string
}

let legacyUser: LegacyUser = {
  id: '793331',
  name: 'Xin Yang'
}

deleteUser(legacyUser)  // Error TS2345: Argument of type 'LegacyUser' is not
                        // assignable to parameter of type '{id?: number |
                        // undefined, name: string}'. Type 'string' is not
                        // assignable to type 'number | undefined'.
```

When we pass a shape with a property whose type is a supertype of the expected
type, TypeScript complains.

TypeScript’s behavior is as follows: if you expect a shape, you can also pass a
type with property types that are <: their expected types, but you cannot pass
a shape with property types that are supertypes of their expected types.

For an object `A` to be assignable to an object `B`, each of its properties
must be `<:` its corresponding property in `B`.

More generally, covariance is just one of four sorts of variance:

- ***Invariance***: You want exactly a `T`.
- ***Covariance***: You want a `<:T`.
- ***Contravariance***: You want a `>:T`.
- ***Bivariance***: You’re OK with either `<:T` or `>:T`.

In TypeScript, every complex type is covariant in its members:

- objects
- classes
- arrays
- function return types

One exception: function parameter types, which are ***contravariant***.

In some languages objects are invariant in their property types, because as we
saw, covariant property types can lead to unsafe behavior. Some languages have
different rules for mutable and immutable objects. Some languages — like Scala,
Kotlin, and Flow — even have explicit syntax for programmers to specify
variance for their own data types.

When you make objects invariant in their property types, even though it’s safer,
it can make a type system tedious to use because you end up banning things that
are safe in practice (e.g., if we didn’t delete the id in `deleteUser`, then it
would have been perfectly safe to pass in an object that’s a supertype of the
expected type).

#### Function variance

A function `A` is a subtype of function `B` if `A` has the same or lower arity
(number of parameters) than `B` and:

1. `A`’s `this` type either isn’t specified, or is `>:` `B`’s `this` type.
2. Each of `A`’s parameters is `>:` its corresponding parameter in `B`.
3. `A`’s return type is `<:` `B`’s return type.

You might have noticed that for a function `A` to be a subtype of function `B`,
we say that its `this` type and parameters must be `>:` their counterparts in
`B`, while its return type has to be `<:`!

```ts
class Animal {}

class Bird extends Animal {
  chirp() {}
}

class Crow extends Bird {
  caw() {}
}
```

In this example, `Crow` is a subtype of `Bird`, which is a subtype of `Animal`.
That is, `Crow <: Bird <: Animal`.

```ts
function chirp(bird: Bird): Bird {
  bird.chirp()
  return bird
}
```

```ts
chirp(new Animal) // Error TS2345: Argument of type 'Animal' is not assignable
chirp(new Bird)   // to parameter of type 'Bird'.
chirp(new Crow)
```

Let’s make a new function. This time, its parameter will be a function:

```ts
function clone(f: (b: Bird) => Bird): void {
  // ...
}

function birdToBird(b: Bird): Bird {
  // ...
}
clone(birdToBird) // OK

function birdToCrow(d: Bird): Crow {
  // ...
}
clone(birdToCrow) // OK

function birdToAnimal(d: Bird): Animal {
  // ...
}
clone(birdToAnimal) // Error TS2345: Argument of type '(d: Bird) => Animal' is
                    // not assignable to parameter of type '(b: Bird) => Bird'.
                    // Type 'Animal' is not assignable to type 'Bird'.
```

Imagine that clone’s implementation looks like this:

```ts
function clone(f: (b: Bird) => Bird): void {
  let parent = new Bird
  let babyBird = f(parent)
  babyBird.chirp()
}
```

TypeScript has to make sure, at compile time, that the function we passed in
returns at least a `Bird`.

We say that functions are ***covariant*** in their return types, which is a
fancy way of saying that for a function to be a subtype of another function,
its return type has to be `<:` the other function’s return type.

```ts
function animalToBird(a: Animal): Bird {
  // ...
}
clone(animalToBird) // OK

function crowToBird(c: Crow): Bird {
  // ...
}
clone(crowToBird) // Error TS2345: Argument of type '(c: Crow) => Bird' is not
                  // assignable to parameter of type '(b: Bird) => Bird'.
```

For a function to be assignable to another function, its parameter types
(including `this`) all have to be `>:` their corresponding parameter types in
the other function. To see why:

```ts
function crowToBird(c: Crow): Bird {
  c.caw()
  return new Bird
}
```

`.caw` is only defined on Crows, not on all Birds.

This means functions are ***contravariant*** in their parameter and `this`
types. That is, for a function to be a subtype of another function, each of its
parameters and its `this` type must be `>:` its corresponding parameter in the
other function.

##### TSC Flag: `strictFunctionTypes`

For legacy reasons, functions in TypeScript are actually covariant in their
parameter and `this` types by default. To opt into the safer contravariant
behavior, be sure to enable the `{"strictFunctionTypes": true}` flag in
`tsconfig.json`.

`strict` mode includes `strictFunctionTypes`.

### Assignability

For non-enum types — like arrays, booleans, numbers, objects, functions,
classes, class instances, and strings, including literal types — `A` is
assignable to `B` if either of the following is true:

1. `A <: B`.
2. `A` is `any`.

Rule 1 is just the definition of what a subtype is: if `A` is a subtype of `B`,
then wherever you need a `B` you can also use an `A`.

Rule 2 is the exception to rule 1, and is a convenience for interoperating with
JavaScript code.

For `enum` types created with the `enum` or `const enum` keywords, a type `A`
is assignable to an enum `B` if either of these is true:

1. `A` is a member of enum `B`.
2. `B` has at least one member that’s a number, and `A` is a number.

Rule 1 is exactly the same as for simple types (if `A` is a member of enum `B`,
then `A`’s type is `B`, so all we’re saying is `B <: B`).

Rule 2 is a convenience for working with enums. Rule 2 is a big source of
unsafety in TypeScript, and this is one reason why avoiding enums entirely is a
good idea.

### Type Widening

In general, TypeScript will be lenient when inferring your types, and will err
on the side of inferring a more general type rather than the most specific type
possible.

When you declare a variable in a way that allows it to be mutated later (e.g.,
with `let` or `var`), its type is widened from its literal value to the base
type that literal belongs to:

```ts
let a = 'x'           // string
let b = 3             // number
var c = true          // boolean
const d = {x: 3}      // {x: number}

enum E {X, Y, Z}
let e = E.X           // E
```

Not so for immutable declarations:

```ts
const a = 'x'         // 'x'
const b = 3           // 3
const c = true        // true

enum E {X, Y, Z}
const e = E.X         // E.X
```

You can use an explicit type annotation to prevent your type from being widened:

```ts
let a: 'x' = 'x'          // 'x'
let b: 3 = 3              // 3
var c: true = true        // true
const d: {x: 3} = {x: 3}  // {x: 3}
```

When you reassign a nonwidened type using `let` or `var`, TypeScript widens it
for you. To tell TypeScript to keep it narrow, add an explicit type annotation
to your original declaration:

```ts
const a = 'x'         // 'x'
let b = a             // string

const c: 'x' = 'x'    // 'x'
let d = c             // 'x'
```

Variables initialized to `null` or `undefined` are widened to `any`:

```ts
let a = null    // any
a = 3           // any
a = 'b'         // any
```

But when a variable initialized to `null` or `undefined` leaves the scope it
was declared in, TypeScript assigns it a definite type:

```ts
function x() {
  let a = null    // any
  a = 3           // any
  a = 'b'         // any
  return a
}

x()               // string
```

#### The const type

Use it as a type assertion:

```ts
let a = {x: 3}              // {x: number}
let b: {x: 3}               // {x: 3}
let c = {x: 3} as const     // {readonly x: 3}
```

`const` opts your type out of widening and recursively marks its members as
`readonly`, even for deeply nested data structures:

```ts
let d = [1, {x: 2}]           // (number | {x: number})[]
let e = [1, {x: 2}] as const  // readonly [1, {readonly x: 2}]
```

💡 Use `as const` when you want TypeScript to infer your type as narrowly as
possible.

#### Excess property checking

```ts
type Options = {
  baseURL: string
  cacheSize?: number
  tier?: 'prod' | 'dev'
}

class API {
  constructor(private options: Options) {}
}

new API({
  baseURL: 'https://api.mysite.com',
  tier: 'prod'
})

new API({
  baseURL: 'https://api.mysite.com',
  tierr: 'prod'   // Error TS2345: Argument of type '{tierr: string}'
})                // is not assignable to parameter of type 'Options'.
                  // Object literal may only specify known properties,
                  // but 'tierr' does not exist in type 'Options'.
                  // Did you mean to write 'tier'?
```

TypeScript was able to catch this due to its ***excess property checking***,
which works like this: when you try to assign a fresh object literal type `T`
to another type `U`, and `T` has properties that aren’t present in `U`,
TypeScript reports an error.

A ***fresh object literal type*** is the type TypeScript infers from an object
literal. If that object literal either uses a type assertion or is assigned to
a variable, then the fresh object literal type is widened to a regular object
type, and its freshness disappears.

```ts
type Options = {
  baseURL: string
  cacheSize?: number
  tier?: 'prod' | 'dev'
}

class API {
  constructor(private options: Options) {}
}

new API({ // 1.
  baseURL: 'https://api.mysite.com',
  tier: 'prod'
})

new API({ // 2.
  baseURL: 'https://api.mysite.com',
  badTier: 'prod' // Error TS2345: Argument of type '{baseURL: string; badTier:
})                // string}' is not assignable to parameter of type 'Options'.

new API({ // 3.
  baseURL: 'https://api.mysite.com',
  badTier: 'prod'
} as Options)

let badOptions = {  // 4.
  baseURL: 'https://api.mysite.com',
  badTier: 'prod'
}
new API(badOptions)

let options: Options = {  // 5.
  baseURL: 'https://api.mysite.com',
  badTier: 'prod'   // Error TS2322: Type '{baseURL: string; badTier: string}'
}                   // is not assignable to type 'Options'.
new API(options)
```

1. We instantiate `API` with a `baseURL` and one of our two optional properties,
   `tier`. This works as expected.
2. Here, we misspell `tier` as `badTier`. The options object we pass to
   `new API` is fresh (because its type is inferred, it isn’t assigned to a
   variable, and we don’t make a type assertion about its type), so TypeScript
   runs an excess property check on it, revealing the excess `badTier` property.
3. We assert that our invalid options object is of type `Options`. TypeScript
   no longer considers it fresh, and bails out of excess property checking: no
   error.
4. We assign our options object to a variable, `badOptions`. TypeScript no
   longer considers it to be fresh, and bails out of excess property checking:
   no error.
5. When we explicitly type `options` as `Options`, the object we assign to
   `options` is fresh, so TypeScript performs excess property checking,
   catching our bug. Note that in this case the excess property check doesn’t
   happen when we pass options to `new API`; rather, it happens when we try to
   assign our options object to the variable `options`.

### Refinement

TypeScript performs ***flow-based*** type inference, which is a kind of
symbolic execution where the typechecker uses control flow statements like
`if`, `?`, `||`, and `switch`, as well as type queries like `typeof`,
`instanceof`, and `in`, to refine types as it goes, just like a programmer
reading through the code would. It’s an incredibly convenient feature for a typechecker to have, but is another one of those things that remarkably few lan‐ guages support.2

1. ***Symbolic execution*** is a form of program analysis where you use a
   special program called a ***symbolic evaluator*** to run your program the
   same way a runtime would, but without assigning definite values to variables;
   instead, each variable is modelled as a symbol whose value gets constrained
   as the program runs. Symbolic execution lets you say things like “this
   variable is never used,” or “this function never returns,” or “in the
   positive branch of the `if` statement on line 102, variable `x` is
   guaranteed not to be `null`.”
2. ***Flow-based type inference*** is supported by a handful of languages,
   including TypeScript, Flow, Kotlin, and Ceylon. It’s a way to refine types
   within a block of code, and is an alternative to C/Java-style explicit type
   annotations and Haskell/OCaml/Scala-style pattern matching. The idea is to
   take a symbolic execution engine and embed it right in the typechecker, in
   order to give feedback to the typechecker and reason through a program in a
   way that is closer to how a human programmer might do it.

```ts
// We use a union of string literals to describe
// the possible values a CSS unit can have
type Unit = 'cm' | 'px' | '%'

// Enumerate the units
let units: Unit[] = ['cm', 'px', '%']

// Check each unit, and return null if there is no match
function parseUnit(value: string): Unit | null {
  for (let i = 0; i < units.length; i++) {
    if (value.endsWith(units[i])) {
      return units[i]
    }
  }
  return null
}
```

We take advantage of type refinement a few times in this example:

```ts
type Width = {
  unit: Unit,
  value: number
}

function parseWidth(width: number | string | null | undefined): Width | null {
  // If width is null or undefined, return early
  if (width == null) {  // 1.
    return null
  }

  // If width is a number, default to pixels
  if (typeof width === 'number') {  // 2.
    return {unit: 'px', value: width}
  }

  // Try to parse a unit from width
  let unit = parseUnit(width)
  if (unit) {
    return {unit, value: parseFloat(width)}
  }

  // Otherwise, return null
  return null   // 4.
}
```

1. TypeScript is smart enough to know that doing a loose equality check against
   `null` will return `true` for both `null` and `undefined` in JavaScript. It
   knows that if this check passes then we will return, and if we didn’t return
   that means the check didn’t pass, so from then on `width`’s type is
   `number | string` (it can’t be `null` or `undefined` anymore). We say that
   the type was refined from `number | string | null | undefined` to
   `number | string`.
2. A `typeof` check queries a value at runtime to see what its type is.
   TypeScript takes advantage of `typeof` at compile time too: in the `if`
   branch where the check passes, TypeScript knows that `width` is a `number`;
   otherwise (since that branch returns) `width` must be a `string` — it’s the
   only type left.
3. Because calling `parseUnit` might return `null`, we check if it did by
   testing whether its result is truthy. TypeScript knows that if `unit` is
   truthy then it must be of type `Unit` in the if branch — otherwise, unit
   must be falsy, meaning it must be of type `null` (refined from
   `Unit | null`).
4. Finally, we return `null`. This can only happen if the user passed a `string`
   for `width`, but that string contained a unit that we don’t support.

#### Discriminated union types

```ts
type UserTextEvent = {value: string}
type UserMouseEvent = {value: [number, number]}

type UserEvent = UserTextEvent | UserMouseEvent

function handle(event: UserEvent) {
  if (typeof event.value === 'string') {
    event.value   // string
    // ...
    return
  }
  event.value     // [number, number]
}
```

```ts
type UserTextEvent = {value: string, target: HTMLInputElement}
type UserMouseEvent = {value: [number, number], target: HTMLElement}

type UserEvent = UserTextEvent | UserMouseEvent

function handle(event: UserEvent) {
  if (typeof event.value === 'string') {
    event.value   // string
    event.target  // HTMLInputElement | HTMLElement (!!!)
    // ...
    return
  }
  event.value     // [number, number]
  event.target    // HTMLInputElement | HTMLElement (!!!)
}
```

While the refinement worked for `event.value`, it didn’t carry over to
`event.target`. Why? When `handle` takes a parameter of type `UserEvent`, that
doesn’t mean we have to pass a `UserTextEvent` or `UserMouseEvent` — in fact,
we could pass an argument of type `UserMouseEvent | UserTextEvent`. And since
members of a union might overlap, TypeScript needs a more reliable way to know
when we’re in one case of a union type versus another case.

The way to do this is to use a literal type to tag each case of your union type.
A good tag is:

- On the same place in each case of your union type. That means the same object
  field if it’s a union of object types, or the same index if it’s a union of
  tuple types. In practice, tagged unions usually use object types.
- Typed as a literal type (a literal string, number, boolean, etc.). You can
  mix and match different types of literals, but it’s good practice to stick to
  a single type; typically, that’s a string literal type.
- Not generic. Tags should not take any generic type arguments.
- Mutually exclusive (i.e., unique within the union type).

With that in mind, let’s update our event types again:

```ts
type UserTextEvent = {
  type: 'TextEvent',
  value: string,
  target: HTMLInputElement
}
type UserMouseEvent = {
  type: 'MouseEvent',
  value: [number, number],
  target: HTMLElement
}

type UserEvent = UserTextEvent | UserMouseEvent

function handle(event: UserEvent) {
  if (event.type === 'TextEvent') {
    event.value   // string
    event.target  // HTMLInputElement
    // ...
    return
  }
  event.value     // [number, number]
  event.target    // HTMLElement
}
```

Now when we refine event based on the value of its tagged field (`event.type`),
TypeScript knows that in the `if` branch event has to be a `UserTextEvent`, and
after the `if` branch it has to be a `UserMouseEvent`. Since the tag is unique
per union type, TypeScript knows that the two are mutually exclusive.

Use tagged unions when writing a function that has to handle the different
cases of a union type.

## Totality

***Totality***, also called ***exhaustiveness checking***, is what allows the
typechecker to make sure you’ve covered all your cases.

```ts
type Weekday = 'Mon' | 'Tue'| 'Wed' | 'Thu' | 'Fri'
type Day = Weekday | 'Sat' | 'Sun'

function getNextDay(w: Weekday): Day {
  switch (w) {
    case 'Mon': return 'Tue'
  }
}
```

TypeScript comes to the rescue:

```txt
Error TS2366: Function lacks ending return statement and
return type does not include 'undefined'.
```

Because we annotated `getNextDay`’s return type, and not all branches are
guaranteed to return a value of that type, TypeScript warns us.

```ts
function isBig(n: number) {
  if (n >= 100) {
    return true
  }
}   // Error TS7030: Not all code paths return a value.
```

### TSC Flag: noImplicitReturns

To ask TypeScript to check that all of your functions’ code paths return a
value (and throw the preceding warning if you missed a spot), enable the
`noImplicitReturns` flag in `tsconfig.json`.

## Advanced Object Types

Objects are central to JavaScript, and TypeScript gives you a whole bunch of
ways to express and manipulate them safely.

### Type Operators for Object Types

#### The keying-in operator

Say you have a complex nested type to model the GraphQL API response you got
back from your social media API of choice:

```ts
type APIResponse = {
  user: {
    userId: string
    friendList: {
      count: number
      friends: {
        firstName: string
        lastName: string
      }[]
    }
  }
}

function getAPIResponse(): Promise<APIResponse> {
  // ...
}

function renderFriendList(friendList: unknown) {
  // ...
}

let response = await getAPIResponse()
renderFriendList(response.user.friendList)
```

What should the type of `friendList` be? (It’s stubbed out as `unknown` for
now.) You could type it out and reimplement your top-level `APIResponse` type
in terms of it:

```ts
type FriendList = {
  count: number
  friends: {
    firstName: string
    lastName: string
  }[]
}

type APIResponse = {
  user: {
    userId: string
    friendList: FriendList
  }
}

function renderFriendList(friendList: FriendList) {
  // ...
}
```

But then you’d have to come up with names for each of your top-level types,
which you don’t always want (e.g., if you used a build tool to generate
TypeScript types from your GraphQL schema). Instead, you can ***key in*** to
your type:

```ts
type APIResponse = {
  user: {
    userId: string
    friendList: {
      count: number
      friends: {
        firstName: string
        lastName: string
      }[]
    }
  }
}

type FriendList = APIResponse['user']['friendList']

function renderFriendList(friendList: FriendList) {
  // ...
}
```

You can key in to any shape (object, class constructor, or class instance), and
any array. For example, to get the type of an individual friend:

```ts
type Friend = FriendList['friends'][number]
```

`number` is a way to key in to an array type; for tuples, use `0`, `1`, or
another number literal type to represent the index you want to key in to.

⚠️ Note that you have to use bracket notation, not dot notation, to look up
property types when keying in.

#### The keyof operator

Use `keyof` to get all of an object’s keys as a union of `string` literal types.

```ts
type ResponseKeys = keyof APIResponse     // 'user'
type UserKeys = keyof APIResponse['user'] // 'userId' | 'friendList'
type FriendListKeys =
  keyof APIResponse['user']['friendList'] // 'count' | 'friends'
```

Combining the keying-in and `keyof` operators, you can implement a typesafe
`getter` function that looks up the value at the given key in an object:

```ts
function get< // 1.
  O extends object,
  K extends keyof O // 2.
>(
  o: O,
  k: K
): O[K] { // 3.
  return o[k]
}
```

1. `get` is a function that takes an object `o` and a key `k`.
2. `keyof O` is a union of string literal types, representing all of `o`’s keys.
   The generic type `K` extends — and is a subtype of — that union. For example,
   if `o` has the type `{a: number, b: string, c: boolean}`, then `keyof o` is
   the type `'a' | 'b' | 'c'`, and `K` could be the type `'a'`,
   `'b'`, `'a' | 'c'`, or any other subtype of `keyof o`.
3. `O[K]` is the type you get when you look up `K` in `O`. If `K` is `'a'`,
   then we know at compile time that `get` returns a `number`. Or, if `K` is
   `'b' | 'c'`, then we know `get` returns `string | boolean`.

What’s cool about these type operators is how precisely and safely they let you
describe shape types:

```ts
type ActivityLog = {
  lastEvent: Date
  events: {
    id: string
    timestamp: Date
    type: 'Read' | 'Write'
  }[]
}

let activityLog: ActivityLog = // ...
let lastEvent = get(activityLog, 'lastEvent') // Date
```

Let’s overload `get` to accept up to three keys:

```ts
type Get = {  // 1.
  <
    O extends object,
    K1 extends keyof O
  >(o: O, k1: K1): O[K1]  // 2.
  <
    O extends object,
    K1 extends keyof O,
    K2 extends keyof O[K1]  // 3.
  >(o: O, k1: K1, k2: K2): O[K1][K2]  // 4.
  <
    O extends object,
    K1 extends keyof O,
    K2 extends keyof O[K1],
    K3 extends keyof O[K1][K2]
  >(o: O, k1: K1, k2: K2, k3: K3): O[K1][K2][K3]  // 5.
}

let get: Get = (object: any, ...keys: string[]) => {
  let result = object
  keys.forEach(k => result = result[k])
  return result
}

get(activityLog, 'events', 0, 'type') // 'Read' | 'Write'
get(activityLog, 'bad')     // Error TS2345: Argument of type '"bad"'
                            // is not assignable to parameter of type
                            // '"lastEvent" | "events"'.
```

1. We declare an overloaded function signature for `get` with three cases for
   when we call `get` with one key, two keys, and three keys.
2. This one-key case is the same as the last example: `O` is a subtype of
   object, `K1` is a subtype of that object’s keys, and the return type is
   whatever specific type you get when you key in to `O` with `K1`.
3. The two-key case is like the one-key case, but we declare one more generic
   type, `K2`, to model the possible keys on the nested object that results
   from keying into `O` with `K1`.
4. We build on by keying in twice — we first get the type of `O[K1]`, then get
   the type of `[K2]` on the result.

##### TSC Flag: keyofStringsOnly

In JavaScript, objects and arrays can have both string and symbol keys. And by
convention, we usually use number keys for arrays, which are coerced to strings
at runtime.

Because of this, `keyof` in TypeScript returns a value of type
`number | string | symbol` by default (though if you call it on a more specific
shape, TypeScript can infer a more specific subtype of that union).

This behavior is correct, but can make working with `keyof` wordy, as you may
have to prove to TypeScript that the particular key you’re manipulating is a
`string`, and not a `number` or a `symbol`.

To opt into TypeScript’s legacy behavior—where keys must be strings — enable
the `keyofStringsOnly` `tsconfig.json` flag.

### The Record Type

TypeScript’s built-in `Record` type is a way to describe an object as a map
from something to something.

With `Record`, you can put some constraints on the keys and values in `nextDay`:

```ts
type Weekday = 'Mon' | 'Tue'| 'Wed' | 'Thu' | 'Fri'
type Day = Weekday | 'Sat' | 'Sun'

let nextDay: Record<Weekday, Day> = {
  Mon: 'Tue'
}
```

Now, you get a nice, helpful error message right away:

```txt
Error TS2739: Type '{Mon: "Tue"}' is missing the following properties
from type 'Record<Weekday, Day>': Tue, Wed, Thu, Fri.
```

Adding the missing `Weekdays` to your object, of course, makes the error go
away.

`Record` gives you one extra degree of freedom compared to regular object index
signatures: with a regular index signature you can constrain the types of an
object’s values, but the key can only be a regular `string`, `number`, or
`symbol`; with `Record`, you can also constrain the types of an object’s keys
to subtypes of `string` and `number`.

### Mapped Types

TypeScript gives us a second, more powerful way to declare a safer `nextDay`
type: mapped types.

```ts
let nextDay: {[K in Weekday]: Day} = {
  Mon: 'Tue'
}
```

This is another way to get a helpful hint for how to fix what you missed:

```txt
Error TS2739: Type '{Mon: "Tue"}' is missing the following properties
from type '{Mon: Weekday; Tue: Weekday; Wed: Weekday; Thu: Weekday;
Fri: Weekday}': Tue, Wed, Thu, Fri.
```

Like index signatures, you can have at most one mapped type per object:

```ts
type MyMappedType = {
  [Key in UnionType]: ValueType
}
```

As the name implies, it’s a way to map over an object’s key and value types. In
fact, TypeScript uses mapped types to implement its built-in `Record` type:

```ts
type Record<K extends keyof any, T> = {
  [P in K]: T
}
```

Mapped types give you more power than a mere `Record` because in addition to
letting you give types to an object’s keys and values, when you combine them
with keyed-in types, they let you put constraints on which value type
corresponds to which key name.

```ts
type Account = {
  id: number
  isEmployee: boolean
  notes: string[]
}

// Make all fields optional
type OptionalAccount = {
  [K in keyof Account]?: Account[K]   // 1.
}

// Make all fields nullable
type NullableAccount = {
  [K in keyof Account]: Account[K] | null   // 2.
}

// Make all fields read-only
type ReadonlyAccount = {
  readonly [K in keyof Account]: Account[K]   // 3.
}

// Make all fields writable again (equivalent to Account)
type Account2 = {
  -readonly [K in keyof ReadonlyAccount]: Account[K]  // 4.
}

// Make all fields required again (equivalent to Account)
type Account3 = {
  [K in keyof OptionalAccount]-?: Account[K]  // 5.
}
```

1. We create a new object type `OptionalAccount` by mapping over `Account`,
   marking each field as optional along the way.
2. We create a new object type `NullableAccount` by mapping over `Account`,
   adding `null` as a possible value for each field along the way.
3. We create a new object type `ReadonlyAccount` by taking `Account` and making
   each of its fields read-only.
4. We can mark fields as optional (`?`) or `readonly`, and we can also unmark
   them. With the minus (`–`) operator — a special type operator only available
   with mapped types — we can undo `?` and `readonly`, making fields required
   and writable again, respectively. Here we create a new object type
   `Account2`, equivalent to our `Account` type, by mapping over
   `ReadonlyAccount` and removing the `readonly` modifier with the minus (`–`)
   operator.
5. We create a new object type `Account3`, equivalent to our original `Account`
   type, by mapping over `OptionalAccount` and removing the optional (`?`)
   operator with the minus (`–`) operator.

💡 Minus (`–`) has a corresponding plus (`+`) type operator. You will probably
never use this operator directly, because it’s implied: within a mapped type,
`readonly` is equivalent to `+readonly`, and `?` is equivalent to `+?`. `+` is
just there for completeness.

#### Built-in mapped types

- `Record<Keys, Values>`: An object with keys of type `Keys` and values of type
  `Values`
- `Partial<Object>`: Marks every field in `Object` as optional
- `Required<Object>`: Marks every field in `Object` as nonoptional
- `Readonly<Object>`: Marks every field in `Object` as read-only
- `Pick<Object, Keys>`: Returns a subtype of `Object`, with just the given
  `Keys`

### Companion Object Pattern

We can use companion object pattern to pair together a type and an object.

```ts
type Currency = {
  unit: 'EUR' | 'GBP' | 'JPY' | 'USD'
  value: number
}

let Currency = {
  DEFAULT: 'USD',
  from(value: number, unit = Currency.DEFAULT): Currency {
    return {unit, value}
  }
}
```

In TypeScript, types and values live in separate namespaces. That means in the
same scope, you can have the same name (in this example, `Currency`) bound to
both a type and a value. With the companion object pattern, we exploit this
separate namespacing to declare a name twice: first as a type, then as a value.

This pattern lets you group type and value information that’s semantically part
of a single name (like `Currency`) together. It also lets consumers import both
at once:

```ts
import {Currency} from './Currency'

let amountDue: Currency = { // 1.
  unit: 'JPY',
  value: 83733.10
}

let otherAmountDue = Currency.from(330, 'EUR')  // 2.
```

1. Using `Currency` as a type
2. Using `Currency` as a value

Use the companion object pattern when a type and an object are semantically
related, with the object providing utility methods that operate on the type.

## Advanced Function Types

### Improving Type Inference for Tuples

```ts
let a = [1, true] // (number | boolean)[]
```

You could use a type assertion to cast your tuple to a tuple type. Or, you
could use an `as const` assertion to infer the tuple’s type as narrowly as
possible, marking it as read-only.

What if you want to type your tuple as a tuple, but avoid a type assertion, and
avoid the narrow inference and read-only modifier that `as const` gives you? To
do that, you can take advantage of the way TypeScript infers types for rest
parameters:

```ts
function tuple<   // 1.
  T extends unknown[]   // 2.
>(
  ...ts: T  // 3.
): T {  // 4.
 return ts  // 5
}

let a = tuple(1, true) // [number, boolean]
```

1. We declare a tuple function that we’ll use to construct tuple types.
2. We declare a single type parameter `T` that’s a subtype of `unknown[]`
   (meaning `T` is an array of any kind of type).
3. `tuple` takes a variable number of parameters, `ts`. Because `T` describes a
   rest parameter, TypeScript will infer a tuple type for it.
4. `tuple` returns a value of the same tuple type that it inferred `ts` as.
5. Our function returns the same argument that we passed it. The magic is all
   in the types.

Take advantage of this technique in order to avoid type assertions when your code
uses lots of tuple types.

### User-Defined Type Guards

For some kinds of boolean-returning functions, simply saying that your function
returns a boolean may not be enough.

```ts
function isString(a: unknown): boolean {
 return typeof a === 'string'
}
isString('a') // evaluates to true
isString([7]) // evaluates to false

function parseInput(input: string | number) {
 let formattedInput: string
 if (isString(input)) {
  formattedInput = input.toUpperCase()  // Error TS2339: Property 'toUpperCase'
 }                                      // does not exist on type 'number'.
}
```

`typeof` works for regular type refinement, why doesn’t it work here?

The thing about ***type refinement*** is it’s only powerful enough to refine
the type of a variable in the scope you’re in. As soon as you leave that scope,
the refinement doesn’t carry over to whatever new scope you’re in.

We refined the input parameter’s type to `string` using `typeof`, but all
TypeScript knows is that `isString` returned a `boolean`.

What we can do is tell the typechecker that not only does `isString` return a
`boolean`, but whenever that `boolean` is `true`, the argument we passed to
`isString` is a `string`.

To do that, we use something called a user-defined type guard:

```ts
function isString(a: unknown): a is string {
 return typeof a === 'string'
}
```

Type guards are a built-in TypeScript feature, and are what lets you refine
types with `typeof` and `instanceof`. But sometimes, you need the ability to
declare type guards yourself — that’s what the `is` operator is for. When you
have a function that refines its parameters’ types and returns a `boolean`, you
can use a user-defined type guard to make sure that refinement is flowed
whenever you use that function.

User-defined type guards are limited to a single parameter, but they aren’t
limited to simple types:

```ts
type LegacyDialog = // ...
type Dialog = // ...

function isLegacyDialog(
  dialog: LegacyDialog | Dialog
): dialog is LegacyDialog {
  // ...
}
```

You won’t use user-defined type guards often, but when you do, they’re awesome
for writing clean, reusable code. Without them, you’d have to inline all your
`typeof` and `instanceof` type guards instead of building functions like
`isLegacyDialog` and `isString` to perform those same checks in a
better-encapsulated, more readable way.

## Conditional Types

At a high level, conditional types let you say, “Declare a type `T` that depends
on types `U` and `V`; if `U <: V`, then assign `T` to `A`, and otherwise, assign
`T` to `B`.”

```ts
type IsString<T> = T extends string // 1.
  ? true  // 2.
  : false // 3.

type A = IsString<string> // true
type B = IsString<number> // false
```

1. We declare a new conditional type `IsString` that takes a generic type `T`.
   The “condition” part of this conditional type is `T extends string`; that is,
   “Is `T` a subtype of `string`?”
2. If `T` is a subtype of `string`, we resolve to the type `true`.
3. Otherwise, we resolve to the type `false`.

Conditional types aren’t limited to type aliases. You can use them almost
anywhere you can use a type: in type aliases, interfaces, classes, parameter
types, and generic defaults in functions and methods.

### Distributive Conditionals

If you have a conditional type, then the expressions on the right are equivalent
to those on the left: *Distributing conditional types*

- `string extends T ? A : B` <==> `string extends T ? A : B`
- `(string | number) extends T ? A:B` <==> `(string extends T ? A : B) | (number extends T ? A : B)`
- `(string | number | boolean) extends T ? A : B` <==> `(string extends T ? A : B) | (number extends T ? A : B) | (boolean extends T ? A : B)`

Let’s say we have a function that takes some variable of type `T`, and lifts it
to an array of type `T[]`. What happens if we pass in a union type for `T`?

```ts
type ToArray<T> = T[]
type A = ToArray<number>          // number[]
type B = ToArray<number | string> // (number | string)[]
```

Now what happens if we add a conditional type? (Note that the conditional
doesn’t actually do anything here because both its branches resolve to the same
type `T[]`; it’s just here to tell TypeScript to distribute `T` over the tuple
type.)

```ts
type ToArray2<T> = T extends unknown ? T[] : T[]
type A = ToArray2<number>           // number[]
type B = ToArray2<number | string>  // number[] | string[]
```

When you use a conditional type, TypeScript will distribute union types over the
conditional’s branches. It’s like taking the conditional type and mapping it
over each element in the union.

Why does any of this matter? Well, it lets you safely express a bunch of common
operations.

For example, TypeScript comes with `&` for computing what two types have in
common and `|` for taking a union of two types. Let’s build `Without<T, U>`,
which computes the types that are in `T` but not in `U`.

```ts
type Without<T, U> = T extends U ? never : T
```

You use `Without` like so:

```ts
type A = Without<
  boolean | number | string,
  boolean
> // number | string
```

1. Start with the inputs:

    ```ts
    type A = Without<boolean | number | string, boolean>
    ```

2. Distribute the condition over the union:

    ```ts
    type A = Without<boolean, boolean>
            | Without<number, boolean>
            | Without<string, boolean>
    ```

3. Substitute in `Without`’s definition and apply `T` and `U`:

    ```ts
    type A = (boolean extends boolean ? never : boolean)
            | (number extends boolean ? never : number)
            | (string extends boolean ? never : string)
    ```

4. Evaluate the conditions:

    ```ts
    type A = never
            | number
            | string
    ```

5. Simplify:

    ```ts
    type A = number | string
    ```

If it wasn’t for the distributive property of conditional types, we would have
ended up with `never`.

### The infer Keyword

Conditional types have their own syntax for declaring generic types inline: the
`infer` keyword.

Let’s declare a conditional type `ElementType`, which gets the type of an
array’s elements:

```ts
type ElementType<T> = T extends unknown[] ? T[number] : T
type A = ElementType<number[]> // number
```

Now, let’s rewrite it using infer:

```ts
type ElementType2<T> = T extends (infer U)[] ? U : T
type B = ElementType2<number[]> // number
```

In this simple example `ElementType` is equivalent to `ElementType2`. Notice how
the `infer` clause declares a new type variable, `U` — TypeScript will infer the
type of `U` from context, based on what `T` you passed to `ElementType2`.

Also notice why we declared `U` inline instead of declaring it up front,
alongside `T`. What would have happened if we did declare it up front?

```ts
type ElementUgly<T, U> = T extends U[] ? U : T
type C = ElementUgly<number[]>  // Error TS2314: Generic type 'ElementUgly'
                                // requires 2 type argument(s).
```

Because `ElementUgly` defines two generic types, `T` and `U`, we have to pass
both of them in when instantiating `ElementUgly`. But if we do that, that
defeats the point of having an `ElementUgly` type in the first place; it puts
the burden of computing `U` on the caller, when we wanted `ElementUgly` to
compute the type itself.

This example can also be done by the keying-in operator (`[]`) to look up the
type of an array’s elements. What about a more complicated example?

```ts
type SecondArg<F> = F extends (a: any, b: infer B) => any ? B : never

// Get the type of Array.slice
type F = typeof Array['prototype']['slice']
type A = SecondArg<F> // number | undefined
```

So, `[].slice`’s second argument is a `number | undefined`.

### Built-in Conditional Types

`Exclude<T, U>`: Like our `Without` type from before, computes those types in
`T` that are not in `U`:

```ts
type A = number | string
type B = string
type C = Exclude<A, B> // number
```

`Extract<T, U>`: Computes the types in `T` that you can assign to `U`:

```ts
type A = number | string
type B = string
type C = Extract<A, B> // string
```

`NonNullable<T>`: Computes a version of `T` that excludes `null` and
`undefined`:

```ts
type A = {a?: number | null}
type B = NonNullable<A['a']> // number
```

`ReturnType<F>`: Computes a function’s return type (note that this doesn’t work
as you’d expect for generic and overloaded functions):

```ts
type F = (a: number) => string
type R = ReturnType<F> // string
```

`InstanceType<C>`: Computes the instance type of a class constructor:

```ts
type A = {new(): B}
type B = {b: number}
type I = InstanceType<A> // {b: number}
```

## Escape Hatches

Sometimes you don’t have time to type something perfectly, and you just want
TypeScript to trust that what you’re doing is safe.

⚠️ In case it’s not obvious, you should use the following TypeScript features as
little as possible. If you find yourself relying on them, you might be doing
something wrong.

### Type Assertions

If you have a type `B` and `A <: B <: C`, then you can assert to the
typechecker that `B` is actually an `A` or a `C`. Notably, you can only assert
that a type is a supertype or a subtype of itself — you can’t assert that a
`number` is a `string`, because those types aren’t related.

TypeScript gives us two syntaxes for type assertions:

```ts
function formatInput(input: string) {
  // ...
}

function getUserInput(): string | number {
  // ...
}

let input = getUserInput()

// Assert that input is a string
formatInput(input as string)  // 1.

// This is equivalent to
formatInput(<string>input)  // 2
```

1. We use a type assertion (`as`) to tell TypeScript that `input` is a `string`,
   not a `string | number` as the types would have us believe. You might do
   this if you want to quickly test out your `formatInput` function and you
   know for sure that `getUserInput` returns a `string` for your test.
2. The legacy syntax for type assertions uses angle brackets. The two syntaxes
   are functionally equivalent.

💡 Prefer `as` syntax for type assertions over angle bracket (`<>`) syntax. The
former is unambiguous, but the latter can clash with TSX syntax. Use TSLint’s
`no-angle-bracket-type-assertion` rule to automatically enforce this for your
codebase.

Sometimes, two types might not be sufficiently related, so you can’t assert
that one is the other. To get around this, simply assert as `any`:

```ts
function addToList(list: string[], item: string) {
// ...
}
addToList('this is really,' as any, 'really unsafe')
```

Clearly, type assertions are unsafe, and you should avoid using them when
possible.

### Nonnull Assertions

For the special case of nullable types — that is, a type that’s
`T | null or T | null | undefined` — TypeScript has special syntax for
asserting that a value of that type is a `T`, and not `null` or `undefined`.

```ts
type Dialog = {
  id?: string
}

function closeDialog(dialog: Dialog) {
  if (!dialog.id) { // 1.
    return
  }
  setTimeout(() =>  // 2.
    removeFromDOM(
      dialog,
      document.getElementById(dialog.id)  // Error TS2345: Argument of type
                                          // 'string | undefined' is not
                                          // assignable to parameter of type
                                          // 'string'.  // 3.
    )
  )
}

function removeFromDOM(dialog: Dialog, element: Element) {
  element.parentNode.removeChild(element) // Error TS2531: Object is possibly
                                          // 'null'.
  delete dialog.id
}
```

1. If the `dialog` is already deleted (so it has no id), we return early.
2. We remove the `dialog` from the DOM on the next turn of the event loop, so
   that any other code that depends on `dialog` has a chance to finish running.
3. Because we’re inside the arrow function, we’re now in a new scope. TypeScript
   doesn’t know if some code mutated `dialog` between `1.` and `3.`, so it
   invalidates the refinement we made in `1.`. On top of that, while we know
   that if `dialog.id` is defined then an element with that ID definitely
   exists in the DOM, all TypeScript knows is that calling
   `document.getElementById` returns an `HTMLElement | null`. We know it’ll
   always be a nonnullable `HTMLElement`, but TypeScript doesn’t know that — it
   only knows about the types we gave it.
4. Similarly, while we know that the `dialog` is definitely in the DOM and it
   definitely has a parent DOM node, all TypeScript knows is that the type of
   `element.parentNode` is `Node | null`.

One way to fix this is to add a bunch of `if (_ === null)` checks everywhere.
While that’s the right way to do it if you’re unsure if something is `null` or
not, TypeScript comes with special syntax for when you’re sure it’s not
`null | undefined`:

```ts
type Dialog = {
  id?: string
}

function closeDialog(dialog: Dialog) {
  if (!dialog.id) {
    return
  }
  setTimeout(() =>
    removeFromDOM(
      dialog,
      document.getElementById(dialog.id!)!
    )
  )
}

function removeFromDOM(dialog: Dialog, element: Element) {
  element.parentNode!.removeChild(element)
  delete dialog.id
}
```

Notice the sprinkling of nonnull assertion operators (`!`) that tell TypeScript
that we’re sure `dialog.id`, the result of our `document.getElementById` call,
and `element.parentNode` are defined. When a nonnull assertion follows a type
that might be `null` or `undefined`, TypeScript will assume that the type is
defined: `T | null | undefined` becomes a `T`, `number | string | null` becomes
`number | string`, and so on.

When you find yourself using `nonnull` assertions a lot, it’s often a sign that
you should refactor your code. For example, we could get rid of an assertion by
splitting `Dialog` into a union of two types:

```ts
type VisibleDialog = {id: string}
type DestroyedDialog = {}
type Dialog = VisibleDialog | DestroyedDialog
```

We can then update `closeDialog` to take advantage of the union:

```ts
function closeDialog(dialog: Dialog) {
  if (!('id' in dialog)) {
    return
  }

  setTimeout(() =>
    removeFromDOM(
      dialog,
      document.getElementById(dialog.id)!
    )
  )
}

function removeFromDOM(dialog: VisibleDialog, element: Element) {
  element.parentNode!.removeChild(element)
  delete dialog.id
}
```

After we check that dialog has an `id` property defined — implying that it’s a
`VisibleDialog` — even inside the arrow function TypeScript knows that the
reference to `dialog` hasn’t changed: the dialog inside the arrow function is
the same `dialog` outside the function, so the refinement carries over.

### Definite Assignment Assertions

```ts
let userId: string
userId.toUpperCase()  // Error TS2454: Variable 'userId' is used
                      // before being assigned.
```

But, what if our code looks more like this?

```ts
let userId: string
fetchUser()

userId.toUpperCase()  // Error TS2454: Variable 'userId' is used
                      // before being assigned.

function fetchUser() {
  userId = globalCache.get('userId')
}
```

We can use a definite assignment assertion to tell TypeScript that `userId`
will definitely be assigned by the time we read it (notice the exclamation
mark):

```ts
let userId!: string
fetchUser()

userId.toUpperCase() // OK

function fetchUser() {
  userId = globalCache.get('userId')
}
```

As with type assertions and nonnull assertions, if you find yourself using
definite assignment assertions often, you might be doing something wrong.

## Simulating Nominal Types

>>>>> progress
