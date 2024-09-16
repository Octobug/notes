# Chapter 5: Classes and Interfaces

- [Chapter 5: Classes and Interfaces](#chapter-5-classes-and-interfaces)
  - [Classes and Inheritance](#classes-and-inheritance)
    - [TSC Flags: strictNullChecks and strictPropertyInitialization](#tsc-flags-strictnullchecks-and-strictpropertyinitialization)
  - [super](#super)
  - [Using `this` as a Return Type](#using-this-as-a-return-type)
  - [Interfaces](#interfaces)
    - [Declaration Merging](#declaration-merging)
    - [Implementations](#implementations)
    - [Implementing Interfaces Versus Extending Abstract Classes](#implementing-interfaces-versus-extending-abstract-classes)
  - [Classes Are Structurally Typed](#classes-are-structurally-typed)
  - [Classes Declare Both Values and Types](#classes-declare-both-values-and-types)
  - [Polymorphism](#polymorphism)
  - [Mixins](#mixins)
  - [Decorators](#decorators)
    - [TSC Flag: experimentalDecorators](#tsc-flag-experimentaldecorators)
  - [Simulating final Classes](#simulating-final-classes)
  - [Design Patterns](#design-patterns)
    - [Factory Pattern](#factory-pattern)
    - [Builder Pattern](#builder-pattern)
  - [Summary](#summary)
  - [Exercises](#exercises)

TypeScript classes borrow heavily from C#, and support things like visibility
modifiers, property initializers, polymorphism, decorators, and interfaces. But
because TypeScript classes compile down to regular JavaScript classes, you can
also express JavaScript idioms like mixins in a typesafe way.

## Classes and Inheritance

```ts
// Represents a chess game
class Game {}

// A chess piece
class Piece {}

// A set of coordinates for a piece
class Position {}
```

There are six types of pieces:

```ts
// ...
class King extends Piece {}
class Queen extends Piece {}
class Bishop extends Piece {}
class Knight extends Piece {}
class Rook extends Piece {}
class Pawn extends Piece {}
```

Every piece has a color and a current position. In chess, positions are modeled
as (letter (file), number (rank)) coordinate pairs; letters run from left to
right along the x-axis, numbers from bottom to top along the y-axis.

```ts
type Color = 'Black' | 'White'
type File = 'A' | 'B' | 'C' | 'D' | 'E' | 'F' | 'G' | 'H'
type Rank = 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8

class Position {
  constructor(
    private file: File,
    private rank: Rank
  ) {}
}

class Piece {
  protected position: Position
  constructor(
    private readonly color: Color,
    file: File,
    rank: Rank
  ) {
    this.position = new Position(file, rank)
  }
}
```

The `private` ***access modifier*** in the constructor automatically assigns
the parameter to `this` (`this.file` and so on), and sets its visibility to
private.

Like `private`, `protected` assigns the property to `this`, but `protected`
makes the property visible both to instances of `Piece` and to instances of any
subclass of `Piece`.

We added two modifiers to color: `private` and `readonly`.

### TSC Flags: strictNullChecks and strictPropertyInitialization

To opt into definite assignment checks for class instance variables, enable
`strictNullChecks` and `strictPropertyInitialization` flags in your
`tsconfig.json`. If you’re already using the `strict` flag, you’re good to go.

TypeScript supports three access modifiers for properties and methods on a
class:

- `public`: Accessible from anywhere. This is the default access level.
- `protected`: Accessible from instances of this class and its subclasses.
- `private`: Accessible from instances of this class only.

We don’t want users to instantiate a new `Piece` directly. We can use the type
system to enforce that, using the `abstract` keyword:

```ts
// ...
abstract class Piece {
  constructor(
    // ...

new Piece('White', 'E', 1)  // Error TS2511: Cannot create an instance
                            // of an abstract class.
```

```ts
// ...
abstract class Piece {
  // ...
  moveTo(position: Position) {
    this.position = position
  }
  abstract canMoveTo(position: Position): boolean 
}
```

```ts
// ...
class Position {
  // ...
  distanceFrom(position: Position) {
    return {
      rank: Math.abs(position.rank - this.rank),
      file: Math.abs(position.file.charCodeAt(0) - this.file.charCodeAt(0))
    }
  }
}

class King extends Piece {
  canMoveTo(position: Position) {
    let distance = this.position.distanceFrom(position)
    return distance.rank < 2 && distance.file < 2
  }
}
```

When we make a new game, we’ll automatically create a board and some pieces:

```ts
// ...
class Game {
  private pieces = Game.makePieces()
  private static makePieces() {
    return [
      // Kings
      new King('White', 'E', 1),
      new King('Black', 'E', 8),

      // Queens
      new Queen('White', 'D', 1),
      new Queen('Black', 'D', 8),

      // Bishops
      new Bishop('White', 'C', 1),
      new Bishop('White', 'F', 1),
      new Bishop('Black', 'C', 8),
      new Bishop('Black', 'F', 8),

      // ...
    ]
  }
}
```

## super

There are two kinds of `super` calls:

- Method calls, like `super.take`.
- Constructor calls, which have the special form `super()` and can only be
  called from a `constructor` function.
  - If your child class has a constructor function, you must call `super()`
    from the child’s `constructor` to correctly wire up the class.

## Using `this` as a Return Type

Just like you can use `this` as a value, you can also use it as a type. When
working with classes, the `this` type can be useful for annotating methods’
return types.

```ts
let set = new Set set.add(1).add(2).add(3)
set.has(2)  // true
set.has(4)  // false

class Set {
  has(value: number): boolean {
  // ...
  }

add(value: number): Set {
  // ...
  }
}
```

What happens when we try to subclass `Set`?

```ts
class MutableSet extends Set {
  delete(value: number): boolean {
  // ...
  }
}
```

Of course, `Set`’s `add` method still returns a `Set`, which we’ll need to
override with `MutableSet` for our subclass:

```ts
class MutableSet extends Set {
  delete(value: number): boolean {
    // ...
  }

  add(value: number): MutableSet {
    // ...
  }
}
```

You can use `this` as a return type annotation to let TypeScript do the work
for you:

```ts
class Set {
  has(value: number): boolean {
    // ...
  }
  add(value: number): this {
    // ...
  }
}

class MutableSet extends Set {
  delete(value: number): boolean {
    // ...
  }
}
```

`this` in `Set` points to a `Set` instance, and `this` in `MutableSet` points
to a `MutableSet` instance.

## Interfaces

Like type aliases, interfaces are a way to name a type so you don’t have to
define it inline. **Type aliases** and **interfaces** are mostly two syntaxes
for the same thing, but there are a few small differences.

```ts
type Sushi = {
  calories: number
  salty: boolean
  tasty: boolean
}
```

It’s easy to rewrite it as an interface:

```ts
interface Sushi {
  calories: number
  salty: boolean
  tasty: boolean
}
```

Everywhere you used your `Sushi` type alias, you can also use your `Sushi`
interface. Both declarations define shapes, and those shapes are assignable to
one another (in fact, they’re identical!).

Things get more interesting when you start combining types.

```ts
type Cake = {
  calories: number
  sweet: boolean
  tasty: boolean
}
```

```ts
type Food = {
  calories: number
  tasty: boolean
}

type Sushi = Food & {
  salty: boolean
}

type Cake = Food & {
  sweet: boolean
}
```

Nearly equivalently, you can do that with interfaces too:

```ts
interface Food {
  calories: number
  tasty: boolean
}

interface Sushi extends Food {
  salty: boolean
}

interface Cake extends Food {
  sweet: boolean
}
```

💡 Interfaces don’t have to extend other interfaces. In fact, an interface can
extend any shape: an object type, a class, or another interface.

What are the differences between types and interfaces? There are three, and
they’re subtle.

The first is that type aliases are more general, in that their righthand side
can be any type, including a type expression (a type, and maybe some type
operators like `&` or `|`); for an interface, the righthand side must be a
shape. For example, there is no way to rewrite the following type aliases as
interfaces:

```ts
type A = number
type B = A | string
```

The second difference is that when you extend an interface, TypeScript will
make sure that the interface you’re extending is assignable to your extension.

```ts
interface A {
  good(x: number): string
  bad(x: number): string
}

interface B extends A {
  good(x: string | number): string
  bad(x: string): string  // Error TS2430: Interface 'B' incorrectly extends
}                         // interface 'A'. Type 'number' is not assignable
                          // to type 'string'.
```

This is not the case when you use intersection types: if you turn the
interfaces from the last example into type aliases and the extends into an
intersection (`&`), TypeScript will do its best to combine your extension with
the type it’s extending, resulting in an overloaded signature for `bad` instead
of a compile-time error.

The third difference is that multiple interfaces with the same name in the same
scope are automatically merged; multiple type aliases with the same name in the
same scope will throw a compile-time error. This is a feature called
***declaration merging***.

### Declaration Merging

***Declaration merging*** is TypeScript’s way of automatically combining
multiple declarations that share the same name.

- enums
- interfaces
- namespaces

If you declare two identically named `User` interfaces, then TypeScript will
automatically combine them for you into a single interface:

```ts
// User has a single field, name
interface User {
  name: string
}

// User now has two fields, name and age
interface User {
  age: number
}

let a: User = {
  name: 'Ashley',
  age: 30
}
```

Here’s what happens if you repeat that example with type aliases:

```ts
type User = {   // Error TS2300: Duplicate identifier 'User'.
  name: string
}

type User = {   // Error TS2300: Duplicate identifier 'User'.
  age: number
}
```

Note that the two interfaces can’t conflict; if one types property as a `T` and
the other types it as a `U`, and `T` and `U` aren’t identical, then you’ll get
an error:

```ts
interface User {
  age: string
}

interface User {
  age: number // Error TS2717: Subsequent property declarations must have
}             // the same type. Property 'age' must be of type 'string',
              // but here has type 'number'.
```

And if your interface declares generics, those generics have to be declared the
exact same way for two interfaces to be mergeable — down to the generic’s name!

```ts
interface User<Age extends number> {// Error TS2428: All declarations of 'User'
  age: Age                          // must have identical type parameters.
}

interface User<Age extends string> {
  age: Age
}
```

### Implementations

```ts
interface Animal {
  eat(food: string): void
  sleep(hours: number): void
}

class Cat implements Animal {
  eat(food: string) {
    console.info('Ate some', food, '. Mmm!')
  }

  sleep(hours: number) {
    console.info('Slept for', hours, 'hours')
  }
}
```

Interfaces can declare instance properties, but they can’t declare visibility
modifiers (`private`, `protected`, and `public`) and they can’t use the
`static` keyword.

You can also mark instance properties as `readonly`:

```ts
interface Animal {
  readonly name: string
  eat(food: string): void
  sleep(hours: number): void
}
```

You’re not limited to implementing just one interface — you can implement as
many as you want:

```ts
interface Animal {
  readonly name: string
  eat(food: string): void
  sleep(hours: number): void
}

interface Feline {
  meow(): void
}

class Cat implements Animal, Feline {
  name = 'Whiskers'
  eat(food: string) {
    console.info('Ate some', food, '. Mmm!')
  }

  sleep(hours: number) {
    console.info('Slept for', hours, 'hours')
  }

  meow() {
    console.info('Meow')
  }
}
```

### Implementing Interfaces Versus Extending Abstract Classes

Implementing an interface is really similar to extending an abstract class. The
difference is that ***interfaces are more general and lightweight***, and
***abstract classes are more special-purpose and feature-rich***.

An interface is a way to model a shape. At the value level, that means an
object, array, function, class, or class instance. Interfaces do not emit
JavaScript code, and only exist at compile time.

An abstract class can only model, well, a class. It emits runtime code that is
a JavaScript class. Abstract classes can have constructors, provide default
implementations, and set access modifiers for properties and methods.
Interfaces can’t do any of those things.

When an implementation is shared among multiple classes, use an abstract class.
When you need a lightweight way to say “this class is a `T`,” use an interface.

## Classes Are Structurally Typed

TypeScript compares classes by their structure, not by their name. A class is
compatible with any other type that shares its shape, including a regular old
object that defines the same properties or methods as the class. It means that
if you have a function that takes a `Zebra` and you give it a `Poodle`,
TypeScript might not mind:

```ts
class Zebra {
  trot() {
    // ...
  }
}

class Poodle {
  trot() {
    // ...
  }
}

function ambleAround(animal: Zebra) {
  animal.trot()
}

let zebra = new Zebra
let poodle = new Poodle

ambleAround(zebra) // OK
ambleAround(poodle) // OK
```

As long as `Poodle` is assignable to `Zebra`, TypeScript is OK with it because
from our function’s point of view, the two are interchangeable; all that
matters is that they implement `.trot`. TypeScript is structurally typed
through and through, so this code is perfectly acceptable.

The exception to this rule is classes with `private` or `protected` fields:
when checking whether or not a shape is assignable to a class, if the class has
any `private` or `protected` fields and the shape is not an instance of that
class or a subclass of that class, then the shape is not assignable to the
class:

```ts
class A {
  private x = 1
}

class B extends A {}

function f(a: A) {}

f(new A)  // OK
f(new B)  // OK

f({x: 1}) // Error TS2345: Argument of type '{x: number}' is not
          // assignable to parameter of type 'A'. Property 'x' is
          // private in type 'A' but not in type '{x: number}'.
```

## Classes Declare Both Values and Types

Most things that you can express in TypeScript are either values or types:

```ts
// values
let a = 1999
function b() {}

// types
type a = number
interface b {
  (): void
}
```

Types and values are namespaced separately in TypeScript. Depending on how you
use a term, TypeScript knows whether to resolve it to a type or to a value:

```ts
// ...
if (a + 1 > 3)  // TypeScript infers from context that you mean the value a
  //...

let x: a = 3    // TypeScript infers from context that you mean the type a
```

***Classes and enums*** are special. They are unique because they generate both
a type in the type namespace and a value in the value namespace:

```ts
class C {}
let c: C    // 1.  
  = new C   // 2.

enum E {F, G}
let e: E    // 3.
  = E.F     // 4.
```

1. In this context, `C` refers to the instance type of our `C` class.
2. In this context, `C` refers to `C` the value.
3. In this context, `E` refers to the type of our `E` enum.
4. In this context, `E` refers to `E` the value.

Because classes and enums generate types at the type level we’re able to
express this “is-a” relationship easily.

We also need a way to represent a class at runtime, so that we can instantiate
it with `new`, call static methods on it, do metaprogramming with it, and
operate on it with instanceof — so a class needs to generate a value too.

We use the `typeof` keyword (a type operator provided by TypeScript, which is
like JavaScript’s value-level `typeof` but for types).

```ts
type State = {
  [key: string]: string
}

class StringDatabase {
  state: State = {}
  get(key: string): string | null {
    return key in this.state ? this.state[key] : null
  }
  set(key: string, value: string): void {
    this.state[key] = value
  }
  static from(state: State) {
    let db = new StringDatabase
    for (let key in state) {
      db.set(key, state[key])
    }
    return db
  }
}
```

What types does this class declaration generate? The instance type
`StringDatabase`:

```ts
interface StringDatabase {
  state: State
  get(key: string): string | null
  set(key: string, value: string): void
}
```

And the constructor type `typeof StringDatabase`:

```ts
interface StringDatabaseConstructor {
  new(): StringDatabase
  from(state: State): StringDatabase
}
```

That is, `StringDatabaseConstructor` has a single method `.from`, and `new`-ing
the constructor gives a `StringDatabase` instance. Combined, these two
interfaces model both the constructor and instance sides of a class.

That `new()` bit is called a ***constructor signature***, and is TypeScript’s
way of saying that a given type can be instantiated with the `new` operator.
Because TypeScript is structurally typed, that’s the best we can do to describe
what a class is: ***a class is anything that can be `new`-ed***.

In this case the constructor doesn’t take any arguments, but you can use it to
declare constructors that take arguments too:

```ts
class StringDatabase {
  constructor(public state: State = {}) {}
  // ...
}
```

We could then type `StringDatabase`’s constructor signature as:

```ts
interface StringDatabaseConstructor {
  new(state?: State): StringDatabase
  from(state: State): StringDatabase
}
```

So, not only does a class declaration generate terms at the value and type
levels, but it generates two terms at the type level:

- one representing an instance of the class;
- one representing the class constructor itself (reachable with the `typeof`
  type operator).

## Polymorphism

You can scope a generic to your whole class or interface, or to a specific
method:

```ts
class MyMap<K, V> { // 1.
  constructor(initialKey: K, initialValue: V) { // 2.
    // ...
  }
  get(key: K): V {  // 3.
    // ...
  }
  set(key: K, value: V): void {
    // ...
  }
  merge<K1, V1>(map: MyMap<K1, V1>): MyMap<K | K1, V | V1> {  // 4.
    // ...
  }
  static of<K, V>(k: K, v: V): MyMap<K, V> {  // 5.
    // ...
  }
}
```

1. Bind class-scoped generic types when you declare your class. Here, `K` and
   `V` are available to every instance method and instance property on `MyMap`.
2. Note that you cannot declare generic types in a `constructor`. Instead, move
   the declaration up to your class declaration.
3. Use class-scoped generic types anywhere inside your class.
4. Instance methods have access to class-level generics, and can also declare
   their own generics on top. `.merge` makes use of the `K` and `V` class-level
   generics, and also declares two of its own generics, `K1` and `V1`.
5. Static methods do not have access to their class’s generics, just like at
   the value level they don’t have access to their class’s instance variables.
   `of` does not have access to the `K` and `V` declared in 1.; instead, it
   declares its own `K` and `V` generics.

You can bind generics to interfaces too:

```ts
interface MyMap<K, V> {
  get(key: K): V
  set(key: K, value: V): void
}
```

And like with functions, you can bind concrete types to generics explicitly, or
let TypeScript infer the types for you:

```ts
let a = new MyMap<string, number>('k', 1) // MyMap<string, number>
let b = new MyMap('k', true)              // MyMap<string, boolean>

a.get('k')
b.set('k', false)
```

## Mixins

JavaScript and TypeScript don’t have trait or `mixin` keywords. Both are ways
to simulate multiple inheritance (classes that extend more than one other class)
and do role-oriented programming, a style of programming where you don’t say
things like “this thing is a Shape" but instead describe properties of a thing,
like “it can be measured” or “it has four sides.” Instead of “is-a”
relationships, you describe “can” and “has-a” relationships.

Mixins are a pattern that allows us to mix behaviors and properties into a
class. By convention, mixins:

- Can have state (i.e., instance properties)
- Can only provide concrete methods (not abstract ones)
- Can have constructors, which are called in the same order as their classes
  were mixed in

For example, let’s design a debugging library for TypeScript classes. The
library works by letting you log out information about whatever classes use the
library, so that you can inspect them at runtime. We’ll use it like this:

```ts
class User {
  // ...
}

User.debug()  // evaluates to 'User({"id": 3, "name": "Emma Gluzman"})'
```

A mixin is just a function that takes a class constructor and returns a class
constructor, so our mixin might look like this:

```ts
type ClassConstructor = new(...args: any[]) => {} // 1.

function withEZDebug<C extends ClassConstructor>(Class: C) {  // 2.
  return class extends Class {  // 3.
    constructor(...args: any[]) { // 4.
      super(...args)  // 5.
    }
  }
}
```

1. We start by declaring a type `ClassConstructor`, which represents any
   constructor. Since TypeScript is completely structurally typed, we say that
   a constructor is anything that can be `new`-ed. We don’t know what types of
   parameters the constructor might have, so we say it takes any number of
   arguments of `any` type.
    - Note that TypeScript is picky here: the type of a constructor type’s
      arguments has to be `any[]` (not `void`, `unknown[]`, etc.) in order for
      us to be able to extend it.
2. We declare our `withEZDebug` mixin with a single type parameter, `C`. `C`
   has to be at least a class constructor, which we enforce with an extends
   clause. We let TypeScript infer `withEZDebug`’s return type, which is the
   intersection of `C` and our new anonymous class.
3. Since a mixin is a function that takes a constructor and returns a
   constructor, we return an anonymous class constructor.
4. The class constructor has to take at least the arguments that the class you
   pass in might take. But remember, since we don’t know what class you might
   pass in beforehand, we have to keep it as general as possible, which means
   any number of parameters of any type — just like `ClassConstructor`.
5. Finally, since this anonymous class extends another class, to wire
   everything up correctly we need to remember to call Class’s constructor too.

Like with regular JavaScript classes, if you don’t have any more logic in the
constructor, you can omit lines `4.` and `5.`. We aren’t going to put any logic
into the constructor for this `withEZDebug` example, so we can omit them.

When we call `.debug`, we want to log out the class’s constructor name and the
instance’s value:

```ts
type ClassConstructor = new(...args: any[]) => {}

function withEZDebug<C extends ClassConstructor>(Class: C) {
  return class extends Class {
    debug() {
      let Name = Class.constructor.name
      let value = this.getDebugValue()
      return Name + '(' + JSON.stringify(value) + ')'
    }
  }
}
```

How do we make sure the class implements a `.getDebugValue` method, so that we
can call it?

The answer is that instead of accepting any old class, we use a generic type to
make sure the class passed into `withEZDebug` defines a `.getDebugValue`
method:

```ts
type ClassConstructor<T> = new(...args: any[]) => T // 1.

function withEZDebug<C extends ClassConstructor<{
  getDebugValue(): object // 2.
}>>(Class: C) {
  // ...
}
```

1. We add a generic type parameter to `ClassConstructor`.
2. We bind a shape type to `ClassConstructor`, `C`, enforcing that the
   constructor we passed to `withEZDebug` at least defines the `.getDebugValue`
   method.

```ts
class HardToDebugUser {
  constructor(
    private id: number,
    private firstName: string,
    private lastName: string
  ) {}
  getDebugValue() {
    return {
      id: this.id,
      name: this.firstName + ' ' + this.lastName
    }
  }
}

let User = withEZDebug(HardToDebugUser)
let user = new User(3, 'Emma', 'Gluzman')
user.debug()  // evaluates to 'User({"id": 3, "name": "Emma Gluzman"})'
```

You can apply as many mixins to a class as you want to yield a class with
richer and richer behavior, all in a typesafe way. Mixins help encapsulate
behavior, and are an expressive way to specify reusable behaviors.

## Decorators

### TSC Flag: experimentalDecorators

Decorators are hidden behind a TSC flag. If you’re OK with that, and want to
play around with the feature, set `"experimentalDecorators": true` in your
`tsconfig.json`.

```ts
@serializable
class APIPayload {
  getValue(): Payload {
    // ...
  }
}
```

The `@serializable` class decorator wraps our `APIPayload` class, and
optionally returns a new class that replaces it. Without decorators, you might
implement the same thing with:

```ts
let APIPayload = serializable(class APIPayload {
  getValue(): Payload {
    // ...
  }
})
```

For each type of decorator, TypeScript requires that you have a function in
scope with the given name and the required signature for that type of decorator.

Expected type signatures for the different kinds of decorator functions:

- `Class`: `(Constructor: {new(...any[]) => any}) => any`
- `Method`: `(classPrototype: {}, methodName: string, descriptor: PropertyDescriptor) => any`
- `Static method`: `(Constructor: {new(...any[]) => any}, methodName: string, descriptor: PropertyDescriptor) => any`
- `Method parameter`: `(classPrototype: {}, paramName: string, index: number) => void`
- `Static method parameter`: `(Constructor: {new(...any[]) => any}, paramName: string, index: number) => void`
- `Property`: `(classPrototype: {}, propertyName: string) => any`
- `Static property`: `(Constructor: {new(...any[]) => any}, propertyName: string) => any`
- `Property getter/setter`: `(classPrototype: {}, propertyName: string, descriptor: PropertyDescriptor) => any`
- `Static property getter/ setter`: `(Constructor: {new(...any[]) => any}, propertyName: string, descriptor: PropertyDescriptor) => any`

TypeScript doesn’t come with any built-in decorators: whatever decorators you
use, you have to implement yourself. The implementation for each kind of
decorator — for classes, methods, properties, and function parameters — is a
regular function that satisfies a specific signature, depending on what it’s
decorating. For example, our `@serializable` decorator might look like this:

```ts
type ClassConstructor<T> = new(...args: any[]) => T // 1.

function serializable<
  T extends ClassConstructor<{
    getValue(): Payload // 2.
  }>
>(Constructor: T) { // 3.
  return class extends Constructor {
    serialize() {
      return this.getValue().toString()
    }
  }
}
```

1. Remember, `new()` is how we structurally type a class constructor in
   TypeScript. And for a class constructor that can be extended (with extends),
   TypeScript requires that we type its arguments with an `any` spread:
   `new(...any[])`.
2. `@serializable` can decorate any class whose instances implement the method
   `.getValue`, which returns a `Payload`.
3. Class decorators are functions that take a single argument — the class. If
   the decorator function returns a class it will replace the class it’s
   decorating at runtime; otherwise, it will return the original class.
4. To decorate the class, we return a class that extends it and adds a
   `.serialize` method along the way.

What happens when we try to call `.serialize`?

```ts
let payload = new APIPayload
let serialized = payload.serialize()  // Error TS2339: Property 'serialize' does
                                      // not exist on type 'APIPayload'.
```

TypeScript assumes that a decorator doesn’t change the shape of the thing it’s
decorating — meaning that you didn’t add or remove methods and properties. It
checks at compile time that the class you returned is assignable to the class
you passed in, but at the time of writing, TypeScript does not keep track of
extensions you make in your decorators.

Until decorators in TypeScript become a more mature feature, avoid using them
and stick to regular functions instead:

```ts
let DecoratedAPIPayload = serializable(APIPayload)
let payload = new DecoratedAPIPayload
payload.serialize()                   // string
```

## Simulating final Classes

Though TypeScript doesn’t support the `final` keyword for classes or methods,
it’s easy to simulate it for classes. `final` is the keyword some languages use
to mark a class as nonextensible, or a method as nonoverridable.

To simulate `final` classes in TypeScript, we can take advantage of private
constructors:

```ts
class MessageQueue {
  private constructor(private messages: string[]) {}
}
```

When a constructor is marked `private`, you can’t `new` the class or extend it:

```ts
class BadQueue extends MessageQueue {}  // Error TS2675: Cannot extend a class
                                        // 'MessageQueue'. Class constructor is
                                        // marked as private.

new MessageQueue([])                    // Error TS2673: Constructor of class
                                        // 'MessageQueue' is private and only
                                        // accessible within the class
                                        // declaration.
```

But for `final` classes we do want the ability to instantiate a class, just not
to extend it.

```ts
class MessageQueue {
  private constructor(private messages: string[]) {}
  static create(messages: string[]) {
    return new MessageQueue(messages)
  }
}

class BadQueue extends MessageQueue {}  // Error TS2675: Cannot extend a class
                                        // 'MessageQueue'. Class constructor is
                                        // marked as private.
MessageQueue.create([]) // MessageQueue
```

## Design Patterns

### Factory Pattern

The factory pattern is a way to create objects of some type, leaving the
decision of which concrete object to create to the specific factory that
creates that object.

```ts
type Shoe = {
  purpose: string
}

class BalletFlat implements Shoe {
  purpose = 'dancing'
}

class Boot implements Shoe {
  purpose = 'woodcutting'
}

class Sneaker implements Shoe {
  purpose = 'walking'
}
```

we could have just as well used an `interface` instead.

```ts
let Shoe = {
  create(type: 'balletFlat' | 'boot' | 'sneaker'): Shoe { // 1.
    switch (type) { // 2.
      case 'balletFlat': return new BalletFlat
      case 'boot': return new Boot
      case 'sneaker': return new Sneaker
    }
  }
}
```

1. Using a union type for `type` helps make `.create` as typesafe as possible,
   preventing consumers from passing in an invalid `type` at compile time.
2. Switching on `type` makes it easy for TypeScript to enforce that we’ve
   handled every type of `Shoe`.

In this example we use the ***companion object pattern*** to declare a type
`Shoe` and a value `Shoe` with the same name, as a way to signal that the value
provides methods for operating on the type. To use the factory, we can just
call `.create`:

```ts
Shoe.create('boot') // Shoe
```

Note that we could have gone further and indicated in `Shoe.create`’s type
signature that passing in `'boot'` will give a `Boot`, `'sneaker'` will give a
`Sneaker`, and so on, but that would break the abstraction that the factory
pattern gives us (that the consumer shouldn’t know what concrete class they’ll
get back, just that the class satisfies a particular interface).

### Builder Pattern

The builder pattern is a way to separate the construction of an object from the
way that object is actually implemented. If you’ve used JQuery, or ES6 data
structures like `Map` and `Set`, this style of API should look familiar.

```ts
new RequestBuilder()
  .setURL('/users')
  .setMethod('get')
  .setData({firstName: 'Anna'})
  .send()
```

```ts
class RequestBuilder {}
```

First we’ll add the `.setURL` method:

```ts
class RequestBuilder {
  private url: string | null = null // 1.

  setURL(url: string): this { // 2.
    this.url = url
    return this
  }
}
```

1. We keep track of the `URL` the user set in a private instance variable
   `url`, which we initialize to `null`.
2. `setURL`’s return type is `this`, that is, the specific instance of
   `RequestBuilder` that the user called `setURL` on.

```ts
class RequestBuilder {
  private data: object | null = null
  private method: 'get' | 'post' | null = null
  private url: string | null = null

  setMethod(method: 'get' | 'post'): this {
    this.method = method
    return this
  }
  setData(data: object): this {
    this.data = data
    return this
  }
  setURL(url: string): this {
    this.url = url
    return this
  }
  send() {
    // ...
  }
}
```

This traditional builder design is not completely safe: we can call `.send`
before we `set` the method, `URL`, or `data`, resulting in a runtime exception
(remember, that’s the bad kind of exception).

## Summary

## Exercises
