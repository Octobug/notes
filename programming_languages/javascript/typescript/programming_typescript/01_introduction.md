# Chapter 1 Introduction

- [Chapter 1 Introduction](#chapter-1-introduction)

A few examples of things that are invalid:

```js
3 + []          // Evaluates to the string "3"

let obj = {}
obj.foo         // Evaluates to undefined

function a(b) {
    return b/2
}
a("z")          // Evaluates to NaN
```

Notice that instead of throwing exceptions when you try to do things that are
obviously invalid, JavaScript tries to make the best of it and avoids exceptions
whenever it can. Is JavaScript being helpful? Certainly. Does it make it easier
for you to catch bugs quickly? Probably not.

If JavaScript threw more exceptions instead of quietly making the best of what
we gave it. We might get feedback like this instead:

```js
3 + []          // Error: Did you really mean to add a number and an array?

let obj = {}
obj.foo         // Error: You forgot to define the property "foo" on obj.

function a(b) {
    return b/2
}
a("z")          // Error: The function "a" expects a number,
                // but you gave it a string.
```

Here’s a question: when exactly does JavaScript tell you that you made a
mistake?

Right: when you actually *run* your program.

Even cooler than the fact that TypeScript gives you helpful error messages is
when it gives them to you: TypeScript gives you error messages in your text
editor, as you type.

```ts
3 + []          // Error TS2365: Operator '+' cannot be applied to types '3'
                // and 'never[]'.
let obj = {}
obj.foo         // Error TS2339: Property 'foo' does not exist on type '{}'.

function a(b: number) {
    return b / 2
}
a("z")          // Error TS2345: Argument of type '"z"' is not assignable to
                // parameter of type 'number'.
```

- You will find yourself sketching out a program at the type level before you
  fill it in at the value level;
- you will think about edge cases as you design your program, not as an
  afterthought;
- and you will design programs that are simpler, faster, easier to understand,
  and easier to maintain.
