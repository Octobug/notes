# TypeScript

- [TypeScript](#typescript)
  - [The Basics](#the-basics)
    - [Static type-checking](#static-type-checking)
    - [Non-exception Failures](#non-exception-failures)
    - [Types for Tooling](#types-for-tooling)
    - [`tsc`, the TypeScript compiler](#tsc-the-typescript-compiler)
    - [Emitting with Errors](#emitting-with-errors)
    - [Explicit Types](#explicit-types)
    - [Erased Types](#erased-types)
    - [Downleveling](#downleveling)
    - [Strictness](#strictness)
    - [`noImplicitAny`](#noimplicitany)
    - [`strictNullChecks`](#strictnullchecks)
  - [Running TypeScript](#running-typescript)
    - [ts-node](#ts-node)
    - [TS Playground](#ts-playground)
  - [References](#references)

## The Basics

> <https://www.typescriptlang.org/docs/handbook/2/basic-types.html>

### Static type-checking

***Static types systems*** describe the shapes and behaviors of what our values
will be when we run our programs.

### Non-exception Failures

### Types for Tooling

- type-checker

### `tsc`, the TypeScript compiler

### Emitting with Errors

`tsc` default lets the original working `js` code stay as it was even there
are some type errors.

Using `--noEmitOnError` will stop this behavior.

```sh
tsc --noEmitOnError hello.ts
```

### Explicit Types

```ts
function greet(person: string, date: Date) {
  console.log(`Hello ${person}, today is ${date.toDateString()}!`);
}
```

### Erased Types

Type annotations aren’t part of JavaScript (or ECMAScript to be pedantic), so
there really aren’t any browsers or other runtimes that can just run TypeScript
unmodified. That’s why TypeScript needs a compiler in the first place - it
needs some way to strip out or transform any TypeScript-specific code so that
you can run it.

> Type annotations never change the runtime behavior of your program.

### Downleveling

```ts
`Hello ${person}, today is ${date.toDateString()}!`;
```

will be transformed by `tsc` to:

```ts
"Hello ".concat(person, ", today is ").concat(date.toDateString(), "!");
```

Template strings are a feature from a version of ECMAScript called ECMAScript
2015 (a.k.a. ECMAScript 6, ES2015, ES6, etc.). TypeScript has the ability to
rewrite code from newer versions of ECMAScript to older ones such as ECMAScript
3 or ECMAScript 5 (a.k.a. ES3 and ES5). This process of moving from a newer or
“higher” version of ECMAScript down to an older or “lower” one is sometimes
called ***downleveling***.

By default TypeScript targets ES3, an extremely old version of ECMAScript. We
could have chosen something a little bit more recent by using the target
option.

Running with `--target es2015` changes TypeScript to target ECMAScript 2015,
meaning code should be able to run wherever ECMAScript 2015 is supported.

```sh
tsc --target es2015 hello.ts
```

### Strictness

TypeScript has several type-checking strictness flags that can be turned on or
off. The `strict` flag in the CLI, or `"strict": true` in a `tsconfig.json`
toggles them all on simultaneously, but we can opt out of them individually.
The two biggest ones you should know about are `noImplicitAny` and
`strictNullChecks`.

### `noImplicitAny`

In some places, TypeScript doesn’t try to infer types for us and instead falls
back to the most lenient type: `any`. This isn’t the worst thing that can
happen - after all, falling back to `any` is just the plain JavaScript
experience anyway.

Turning on the `noImplicitAny` flag will issue an error on any variables whose
type is implicitly inferred as `any`.

### `strictNullChecks`

By default, values like `null` and `undefined` are assignable to any other
type. This can make writing some code easier, but forgetting to handle `null`
and `undefined` is the cause of countless bugs in the world. The
`strictNullChecks` flag makes handling `null` and `undefined` more explicit,
and spares us from worrying about whether we forgot to handle `null` and
`undefined`.

## Running TypeScript

```sh
tsc app.ts
node app.js
```

### ts-node

`ts-node` is a TypeScript execution and REPL (Read-Eval–Print Loop) for
node.js, with source map and native ESM support.

### TS Playground

> <https://www.typescriptlang.org/play>

## References

- [typescriptlang.org](https://www.typescriptlang.org/)
- [ ] [roadmap.sh](https://roadmap.sh/typescript)
- [x] [The TypeScript Handbook](https://www.typescriptlang.org/docs/handbook/intro.html)
