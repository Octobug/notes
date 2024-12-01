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

>>>>> progress
