# Chapter 2: Principles in Refactoring

- [Chapter 2: Principles in Refactoring](#chapter-2-principles-in-refactoring)
  - [Defining Refactoring](#defining-refactoring)
  - [The Two Hats](#the-two-hats)
  - [Why Should We Refactor?](#why-should-we-refactor)
    - [Refactoring Improves the Design of Software](#refactoring-improves-the-design-of-software)
    - [Refactoring Makes Software Easier to Understand](#refactoring-makes-software-easier-to-understand)
    - [Refactoring Helps Me Find Bugs](#refactoring-helps-me-find-bugs)
    - [Refactoring Helps Me Program Faster](#refactoring-helps-me-program-faster)
  - [When Should We Refactor?](#when-should-we-refactor)
    - [Preparatory Refactoring - Making It Easier to Add a Feature](#preparatory-refactoring---making-it-easier-to-add-a-feature)
    - [Comprehension Refactoring: Making Code Easier to Understand](#comprehension-refactoring-making-code-easier-to-understand)
    - [Litter-Pickup Refactoring](#litter-pickup-refactoring)
    - [Planned and Opportunistic Refactoring](#planned-and-opportunistic-refactoring)
    - [Long-Term Refactoring](#long-term-refactoring)
    - [Refactoring in a Code Review](#refactoring-in-a-code-review)
    - [What Do I Tell My Manager?](#what-do-i-tell-my-manager)
    - [When Should I Not Refactor?](#when-should-i-not-refactor)
  - [Problems with Refactoring](#problems-with-refactoring)

## Defining Refactoring

- **Refactoring** (noun): a change made to the internal structure of software to
  make it easier to understand and cheaper to modify without changing its
  observable behavior.
- **Refactoring** (verb): to restructure software by applying a series of
  refactorings without changing its observable behavior.

💡 If someone says their code was broken for a couple of days while they are
refactoring, you can be pretty sure they were not refactoring.

## The Two Hats

- **adding functionality**: should not be changing existing code, but just be
  adding new capabilities and tests.
- **refactoring**: should not be adding functionality but restructuring the
  code.

## Why Should We Refactor?

### Refactoring Improves the Design of Software

### Refactoring Makes Software Easier to Understand

### Refactoring Helps Me Find Bugs

### Refactoring Helps Me Program Faster

## When Should We Refactor?

💡 **The Rule of Three**

1. The first time you do something, you just do it.
2. The second time you do something similar, you wince at the duplication, but
   you do the duplicate thing anyway.
3. The third time you do something similar, you refactor.

### Preparatory Refactoring - Making It Easier to Add a Feature

> The best time to refactor is just before I need to add a new feature to the
> code base.

### Comprehension Refactoring: Making Code Easier to Understand

> By refactoring I move the understanding from my head into the code itself.

### Litter-Pickup Refactoring

> If it’s easy to change, I’ll do it right away. If it’s a bit more effort to
> fix, I might **make a note of it** and fix it when I’m done with my immediate
> task.

### Planned and Opportunistic Refactoring

> I don't put time on my plans to do refactoring.

💡 You have to refactor when you run into ugly code - but excellent code needs
plenty of refactoring too.

> For each desired change, make the **change** easy (warningL this may be hard),
> then make the **easy change**. -- Kent Beck

Planned refacroting is **not** always wrong. If a team has neglected
refactoring, it often needs dedicated time to get their code base into a better
state for new features, and a week spent refactoring now can repay itself over
the next couple of months.

### Long-Term Refactoring

### Refactoring in a Code Review

### What Do I Tell My Manager?

> Many managers and customer don't have the technical awareness to know how code
> base health impacts productivity. In these cases I give my more controversial
> advice: **Don't tell!**

### When Should I Not Refactor?

> - If I run across code that is a mess, but I don't need to modify it, then I
>   don't need to refactor it.
> - When it's easier to rewrite it than to refactor it.

## Problems with Refactoring

>>>>> progress
