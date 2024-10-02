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

>>>>> progress
