# CHAPTER 1: Just Enough Microservices

- [CHAPTER 1: Just Enough Microservices](#chapter-1-just-enough-microservices)
  - [What Are Microservices?](#what-are-microservices)
    - [Independent Deployability](#independent-deployability)
    - [Modeled Around a Business Domain](#modeled-around-a-business-domain)
    - [Own Their Own Data](#own-their-own-data)
    - [What Advantages Can Microservices Bring?](#what-advantages-can-microservices-bring)
    - [What Problems Do They Create?](#what-problems-do-they-create)
    - [User Interfaces](#user-interfaces)
    - [Technology](#technology)
    - [Size](#size)
      - [History of the Term “Microservices”](#history-of-the-term-microservices)
    - [And Ownership](#and-ownership)
  - [The Monolith](#the-monolith)
    - [The Single Process Monolith](#the-single-process-monolith)
      - [And the modular monolith](#and-the-modular-monolith)
    - [The Distributed Monolith](#the-distributed-monolith)
    - [Third-Party Black-Box Systems](#third-party-black-box-systems)
    - [Challenges of Monoliths](#challenges-of-monoliths)
    - [Advantages of Monoliths](#advantages-of-monoliths)
  - [On Coupling and Cohesion](#on-coupling-and-cohesion)
    - [A Brief History of Coupling and Cohesion](#a-brief-history-of-coupling-and-cohesion)
    - [Cohesion](#cohesion)
    - [Coupling](#coupling)
      - [Information Hiding](#information-hiding)
      - [Implementation coupling](#implementation-coupling)
      - [Temporal coupling](#temporal-coupling)
      - [Deployment coupling](#deployment-coupling)
      - [Domain coupling](#domain-coupling)
  - [Just Enough Domain-Driven Design](#just-enough-domain-driven-design)
    - [Aggregate](#aggregate)
    - [Bounded Context](#bounded-context)
    - [Mapping Aggregates and Bounded Contexts to Microservices](#mapping-aggregates-and-bounded-contexts-to-microservices)
    - [Further Reading](#further-reading)
  - [Summary](#summary)

## What Are Microservices?

***Microservices*** are independently deployable services modeled around a
business domain. They communicate with each other via networks.

They are a type of service-oriented architecture (SOA), albeit one that is
opinionated about how service boundaries should be drawn, and that independent
deployability is key. Microservices also have the advantage of being technology
agnostic.

They also encapsulate data storage and retrieval, exposing data, via
well-defined interfaces. So databases are hidden inside the service boundary.

### Independent Deployability

***Independent deployability*** is the idea that we can make a change to a
microservice and deploy it into a production environment without having to
utilize any other services. More importantly, this is actually how you manage
deployments in your system.

To guarantee independent deployability, we need to ensure our services are
loosely coupled — in other words, we need to be able to change one service
without having to change anything else. This means we need explicit,
well-defined, and stable contracts between services.

### Modeled Around a Business Domain

If you need to make a change to two services to roll out a feature, and
orchestrate the deployment of these two changes, that takes more work than
making the same change inside a single service (a monolith).

The now famous Conway’s law states

> Any organization that designs a system...will inevitably produce a design
> whose structure is a copy of the organization’s communication structure.
>
> —Melvin Conway, How Do Committees Invent?

### Own Their Own Data

🚨 Don’t share databases, unless you really have to. And even then do
everything you can to avoid it.

### What Advantages Can Microservices Bring?

- opens up new models for improving the scale and robustness of systems, and
  allows you to mix and match technology.
- you can bring more developers to bear on a problem without them getting in
  each other’s way.
- easier for those developers to understand their part of the system, as they
  can focus their attention on just one part of it.
- Process isolation also makes it possible for us to vary the technology
  choices we make, perhaps mixing different programming languages, programming
  styles, deployment platforms, or databases to find the right mix.

### What Problems Do They Create?

One of the main challenges in all of this (Service-oriented architecture) is
the way in which these computers talk to each other: networks.

Networks make activities that are relatively simple with a single-process
monolith, like transactions, much more difficult. So difficult that as your
system grows in complexity, you will likely have to ditch transactions, and the
safety they bring, in exchange for other sorts of techniques.

😓 Honestly, microservices seem like a terrible idea, except for all the good
stuff.

💡 It’s worth noting that virtually all of the systems we categorize as
“monoliths” are also distributed systems. A single-process application likely
reads data from a database that runs on a different machine, and presents data
on to a web browser. The difference is the extent to which monolithic systems
are distributed compared to microservice architectures.

### User Interfaces

If we want an architecture that makes it easier for us to more rapidly deploy
new features, then leaving the UI as a monolithic blob can be a big mistake.
We can, and should, look at breaking apart our user interfaces too.

### Technology

Adopting any new technology will have a cost—it will create some upheaval.

### Size

However, when you get into what makes microservices work as a type of
architecture, the concept of size is actually one of the least interesting
things.

💡 That the goal of microservices is to have “as small an interface as
possible.”

It’s much more important that you focus on two key things:

1. How many microservices can you handle?
2. How do you define microservice boundaries to get the most out of them,
   without everything becoming a horribly coupled mess?

#### History of the Term “Microservices”

"micro-apps" utilized by a few companies that were using service-oriented
architecture.

The idea being that the scope of functionality should be easy to understand,
and therefore easy to change.

These things weren’t self-contained applications, so “micro-apps” wasn’t quite
right. Instead, “microservices” seemed a more appropriate name.

### And Ownership

Product owners work directly as part delivery teams, with these teams being
aligned around customer-facing product lines, rather than around arbitrary
technical groupings. Rather than centralized IT functions being the norm,
the existence of any central IT function is to support these customer-focused
delivery teams.

Reducing services that are shared across multiple teams is key to minimizing
delivery contention — business-domain-oriented microservice architectures make
this shift in organizational structures much easier.

## The Monolith

The unit of deployment is a good way to demarcate microservices and monoliths.

There are at least three types of monolithic systems that fit the bill:

1. the single-process system
2. the distributed monolith
3. third-party black-box systems

### The Single Process Monolith

#### And the modular monolith

The single process consists of separate modules, each of which can be worked on
independently, but which still need to be combined for deployment.

### The Distributed Monolith

A distributed monolith is a system that consists of multiple services, but for
whatever reason the entire system has to be deployed together.

⚠️ Distributed monoliths may have all the disadvantages of a distributed system,
and the disadvantages of a single-process monolith, without having enough
upsides of either.

### Third-Party Black-Box Systems

### Challenges of Monoliths

- more vulnerable to the perils of coupling
  - implementation
  - deployment
- delivery contention

### Advantages of Monoliths

- much simpler deployment topology can avoid many of the pitfalls associated
  with distributed systems.
- result in much simpler developer workflows; and monitoring, troubleshooting,
  and activities like end-to-end testing can be greatly simplified as well.
- Monoliths can also simplify code reuse within the monolith itself.

A monolithic architecture is a choice, and a valid one at that. It may not be
the right choice in all circumstances, any more than microservices are — but
it’s a choice nonetheless.

## On Coupling and Cohesion

### A Brief History of Coupling and Cohesion

### Cohesion

“The code that changes together, stays together.”

### Coupling

#### Information Hiding

The core idea with information hiding is to separate the parts of the code that
change frequently from the ones that are static. We want the module boundary to
be stable, and it should hide those parts of the module implementation that we
expect to change more often. The idea is that internal changes can be made
safely as long as module compatibility is maintained.

💡 Adopt the approach of exposing as little as possible from a module (or
microservice) boundary. Once something becomes part of a module interface, it’s
hard to walk that back. But if you hide it now, you can always decide to share
it later.

🔔 Encapsulation in OO programming has come to mean the bundling together of one
or more things into a container — think of a class containing both fields and
the methods that act on those fields.

#### Implementation coupling

***Implementation coupling*** is typically the most pernicious form of coupling,
but luckily it’s often one of the easiest to reduce. With implementation
coupling, `A` is coupled to `B` in terms of how `B` is implemented — when the
implementation of `B` changes, `A` also changes.

A classic and common example of implementation coupling comes in the form of
sharing a database. A better choice is to hide this implementation detail.

- Via API
- Via publishing a dataset, in the form of a database, which is meant to be used
  for bulk access by consumers. As long as the service can publish data
  accordingly, any changes made inside the service are invisible to consumers,
  as it maintains the public contract.

Another helpful trick is to use “outside-in” thinking when it comes to defining
a service interface — drive the service interface by thinking of things from the
point of the service consumers first, and then work out how to implement that
service contract.

💡 Treat the service interfaces that your microservice exposes like a user
interface. Use outside-in thinking to shape the interface design in partnership
with the people who will call your service.

#### Temporal coupling

***Temporal coupling*** is primarily a runtime concern that generally speaks to
one of the key challenges of synchronous calls in a distributed environment.
When a message is sent, and how that message is handled is connected in time,
we are said to have temporal coupling.

e.g. Three services making use of synchronous calls to perform an operation can
be said to be temporally coupled.

```mermaid
flowchart LR;
    Warehouse --"1.Get order
    Synchronous HTTP Call"--> Order --"2.Get Customer
    Synchronous HTTP Call"--> Customer
```

For this overall operation to complete, the Warehouse, Order, and Customer
services all needed to be up, and contactable. They are temporally coupled.

- We could consider the use of caching — if the Order service cached the
  information it needed from the Customer service, then the Order service would
  be able to avoid temporal coupling on the downstream service in some cases.
- We could also consider the use of an asynchronous transport to send the
  requests, perhaps using something like a message broker. This would allow a
  message to be sent to a downstream service, and for that message to be handled
  after the downstream service is available.

#### Deployment coupling

When everything must be deployed together, we have ***deployment coupling***.

#### Domain coupling

In a microservice architecture, ***domain coupling*** is the result — the
interactions between services model the interactions in our real domain.

Rather than send some full business objects to next microservice, you can wrap
those objects into a new object by picking some of their properties, and send
them via:

- API calls
- event messages

## Just Enough Domain-Driven Design

Modeling services around a business domain has significant advantages for
microservice architecture. The question is how to come up with that model — and
this is where ***domain-driven design (DDD)*** comes in.

### Aggregate

In DDD, an ***aggregate*** is a representation of a real domain concept — think
of something like an Order, Invoice, Stock Item, etc. Aggregates typically have
a life cycle around them, which opens them up to being implemented as a state
machine. We want to treat aggregates as self-contained units; we want to ensure
that the code that handles the state transitions of an aggregate are grouped
together, along with the state itself.

When thinking about aggregates and microservices, a single microservice will
handle the life cycle and data storage of one or more different types of
aggregates. If functionality in another service wants to change one of these
aggregates, it needs to either directly request a change in that aggregate, or
else have the aggregate itself react to other things in the system to initiate
its own state transitions.

The key thing to understand here is that if an outside party requests a state
transition in an aggregate, the aggregate can say no. You ideally want to
implement your aggregates in such a way that illegal state transitions are
impossible.

Aggregates can have relationships with other aggregates.

### Bounded Context

A ***bounded context*** typically represents a larger organizational boundary
inside an organization. Within the scope of that boundary, explicit
responsibilities need to be carried out.

From an implementation point of view, bounded contexts contain one or more
aggregates. Some aggregates may be exposed outside the bounded context; others
may be hidden internally. As with aggregates, bounded contexts may have
relationships with other bounded contexts — when mapped to services, these
dependencies become inter-service dependencies.

### Mapping Aggregates and Bounded Contexts to Microservices

The aggregate is a self-contained state machine that focuses on a single domain
concept in our system, with the bounded context representing a collection of
associated aggregates, again with an explicit interface to the wider world.

A trick here is that even if you decide to split a service that models an entire
bounded context into smaller services later on, you can still hide this decision
from the outside world — perhaps by presenting a coarser-grained API to
consumers. The decision to decompose a service into smaller parts is arguably an
implementation decision, so we might as well hide it if we can!

### Further Reading

- Eric Evans’s original Domain Driven Design
- Vaughn Vernon’s Domain-Driven Design Distilled

## Summary

Microservices are independently deployable services modeled around a business
domain. They communicate with each other via networks. We use the principles of
information hiding together with domain-driven design to create services with
stable boundaries that are easier to work on independently, and we do what we
can to reduce the many forms of coupling.
