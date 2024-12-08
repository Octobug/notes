# CHAPTER 1: Just Enough Microservices

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

>>>>> progress
