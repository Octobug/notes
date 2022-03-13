# 5 Event-Driven Data Management for Microservices

- [5 Event-Driven Data Management for Microservices](#5-event-driven-data-management-for-microservices)
  - [Microservices and the Problem of Distributed Data Management](#microservices-and-the-problem-of-distributed-data-management)
  - [Event-Driven Architecture](#event-driven-architecture)

## Microservices and the Problem of Distributed Data Management

A key benefit of using a relational database in a monolithic application is that
it can use `ACID transactions`:

- **Atomicity**: Changes are made atomically.
- **Consistency**: The state of the database is always consistent.
- **Isolation**: Even though transactions are executed concurrently, it appears
  they are executed serially.
- **Durable**: Once a transaction has committed, it is not undone.

Data access becomes much more complex in microservices architecture.
Microservices-based applications often use a mixture of SQL and NoSQL databases,
the so-called **polyglot persistence** approach. It introduces some distributed
data management challenges.

The first: How to implement business transactions that maintain consistency
across multiple services.

*Figure 5-1. Microservices each have their own data*.

![Microservices each have their own data](images/5_1_microservices_each_have_their_own_data.png)

2PC (two-phase commit, distributed transactions) is usually not a viable option
in modern applications. The CAP theorem requires you to choose between
availability and ACID-style consistency. Many modern technologies do not support
2PC.

The second: How to implement queries that retrieve data from multiple services.

If a service's data only support the lookup of orders by their primary key,
there is no obvious way to retrieve the needed data.

## Event-Driven Architecture

In this architecture, a microservice publishes an event when something notable
happens, such as when it updates a business entity. Other microservices
subscribe to those events.

A business transaction consists of a series of steps. Each step consists of a
microservice **updating a business entity** and
**publishing an event that triggers the next step**.

Examples:

- The Order Service creates an Order with status `NEW` and publishes an
  `Order Created` event.

*Figure 5-2. The Order Service publishes an event*.

![The Order Service publishes an event](images/5_2_order_service_publish.png)

- The Customer Service consumes the `Order Created` event, reserves credit for
  the order, and publishes a `Credit Reserved` event.

*Figure 5-3. The Customer Service responds*.

![The Customer Service responds](images/5_3_the_customer_service_responds.png)

- The Order Service consumes the `Credit Reserved` event and changes the status
  of the order to `OPEN`.

*Figure 5-4. The Order Service acts on the response*.

![The Order Service acts on the response](images/5_4_the_order_service_acts_on_the_response.png)

>>>>> progress
