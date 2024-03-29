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
    - [Slowing Down New Features](#slowing-down-new-features)
    - [Code Ownership](#code-ownership)
    - [Branches](#branches)
    - [Testing](#testing)
    - [Legacy Code](#legacy-code)
    - [Databases](#databases)
  - [Refactoring, Architecture, and Yagni](#refactoring-architecture-and-yagni)
  - [Refactoring and the Wider Software Development Process](#refactoring-and-the-wider-software-development-process)
  - [Refactoring and Performance](#refactoring-and-performance)
  - [Where Did Refactoring Come From?](#where-did-refactoring-come-from)
  - [Automated Refactorings](#automated-refactorings)
  - [Going Further](#going-further)

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

### Slowing Down New Features

💡 The whole purpose of refactoring is to make us program faster, producing more
value with less effort.

> I'm more likely to not refactor if it's part of the code I rarely touch and
> the cost of the inconvenience isn't something I feel very often.

The point of refactoring isn't to show how sparkly a code base is -- it is
purely economic. We refactor because it makes us faster -- faster to add
features, faster to fix bugs.

### Code Ownership

> My preference is to allow team ownership of code -- so that anyone in the same
> team can modify the team's code, even if originally written by someone else.

### Branches

Keeps feature branches short. Each team member integrates with mainline at least
once per day. This prevents any branches diverting too far from each other and
thus greatly reduces the complexity of merges.

### Testing

Self-testing code not only enables refactoring -- it also makes it much safer to
add new features. The key point here is that when a test fails, we can look at
the change we've made between when the tests were last running correctly and
the current code.

### Legacy Code

If you have a big legacy system with no tests, you can't safely refactor it into
clarity. The obvious answer to this problem is that you add tests.

> Even when I do have tests, I don't advocate trying to refactor a complicated
> legacy mess into beautiful code all at once. What I prefer to do is tackle it
> in relevant pieces. Each time I pass through a section of the code, I try to
> make it a little bit better.

### Databases

The essence of database refactoring is to combine the structural changes to a
database's schema and access code with data migration scripts that can easily
compose to handle large changes.

Database changes often are best separated over multiple releases to production.
This makes it easy to reverse any change that causes a problem in production.

## Refactoring, Architecture, and Yagni

One way of dealing with future changes is to put flexibility mechanisms into
the software.

> With refactoring, I can use a different strategy. Instead of speculating on
> what flexibility I will need in the future and what mechanisms will best
> enable that, I build software that solves only the currently understood needs,
> but I make this software excellently designed for those needs.

This approach to design goes under various names: simple design, incremental
design, or `yagni` (you aren't gonna need it). Yagni doesn't imply that
architectural thinking disappears, although it is sometimes naively applied
that way.

## Refactoring and the Wider Software Development Process

1. The first foundation for **refactoring** is **self-testing code**.
2. To refactor on a team, it's important that each member can refactor when they
   need to without interfering with other's work.
   (With **Continuous Integration**)

## Refactoring and Performance

Three general approaches to writing fast software:

1. Time budgeting, often used in hard real-time systems. It gives each component
   a budget for resources -- time and footprint.
2. Constant attention approach: Every programmer does whatever he/she can to
   keep performance high all the time.
3. In most programs, most of their time is spent in a small fraction of the
   code. We can build program without paying attention to performance until we
   began a deliberate performance optimization exercise.

## Where Did Refactoring Come From?

Two of the first people to recognize the importance of refactoring were
**Ward Cunningham** and **Kent Beck**.

**Bill Opdyke** researched the necessary semantics-preserving refactorings and
showed how to prove they were semantics-preserving and how a tool could
implement these ideas.

## Automated Refactorings

To do refactoring properly, the tool has to operate on the syntax tree of the
code, not on the text.

Refactoring isn't just understanding and updating the syntax tree. The tool also
needs to figure out how to rerender the code into text back in the editor view.

## Going Further

- Bill Wakes's *Refactoring Workbook*
- Josh Kerievsky's *Refactoring to Patterns*
- *Refactoring Databases*
- *Refactoring HTML*
- Michael Feathers's *Working Effectively with Legacy Code*
