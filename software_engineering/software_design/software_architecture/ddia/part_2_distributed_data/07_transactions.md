# 7. Transactions

- [7. Transactions](#7-transactions)
  - [The Slippery Concept of a Transaction](#the-slippery-concept-of-a-transaction)
    - [The Meaning of ACID](#the-meaning-of-acid)
      - [Atomicity](#atomicity)
      - [Consistency](#consistency)
      - [Isolation](#isolation)
      - [Durability](#durability)
      - [Replication and Durability](#replication-and-durability)
    - [Single-Object and Multi-Object Operations](#single-object-and-multi-object-operations)
      - [Single-object writes](#single-object-writes)

A ***transaction*** is a way for an application to group several reads and
writes together into a logical unit. All the reads and writes in a transaction
are executed as one operation: either the entire transaction succeeds (`commit`)
or it fails (`abort`, `rollback`).

Transactions were created to simplify the programming model for applications
accessing a database. By using transactions, the application is free to ignore
certain potential error scenarios and concurrency issues, because the database
takes care them instead.

Sometimes there are advantages to weakening transactional guarantees or
abandoning them entirely.

## The Slippery Concept of a Transaction

In the late 2000s, nonrelational (NoSQL) databases started gaining popularity.
Many of this new generation of databases abandoned transactions entirely, or
redefined the word to describe a much weaker set of guarantees than had
previously been understood.

### The Meaning of ACID

The safety guarantees provided by transactions are described by the well-known
acronym ***ACID***.

- Atomicity
- Consistency
- Isolation (there is a lot of ambiguity around the meaning)
- Durability

Systems that do not meet the ACID critera are sometimes called *BASE*, even more
vague than the definition of ACID:

- Basically Available
- Soft state
- Eventual consistency

#### Atomicity

In the context of ACID, atomicity is **not** about concurrency. It does not
describe what happens if several processes try to access the same data at the
same time, which is covered under **Isolation**.

Rather, atomicity describes what hapeens if a client wants to make several
writes, but a fault occurs after some of the writes have been processed.

Perhaps ***abortability*** would have neem a better term than *atomicity*.

#### Consistency

In the context of ACID, ***consistency*** refers to an application-specific
notion of the database being in a "good state".

The idea of *consistency* is that you have certain statements about your data
that must always be true.

This idea of consistency depends on the application's notion of invariants, and
it's the application's responsibility to define its transactions correctly.

***Atomicity***, ***isolation***, and ***durability*** are properties of the
database, whereas consistency is a property of the application. The application
may rely on the database's atomicity and isolation properties to achieve
consistency. The letter C doesn't really belong in ACID.

#### Isolation

```graph
            get counter: 42 + 1 = 43, set counter = 43
[User 1]    \    ^ 42                 \    ^
             \  /                      \  / ok
[Database]    --     --                 --    --
                    /  \                     /  \ ok
[User 2]           /    v 42                /    v
                  get counter: 42 + 1 = 43, set counter = 43
```

***Isolation*** means that concurrently executing transactions are isolated from
each other.

The classic database textbooks formalize isolation as ***serializability***,
which means that each transaction can pretend that it is the only transaction
running on the entire database. The database ensures that when the transactions
have commited, the result is the same as if they had run *serially*.

However, in practice, serializable isolation is rarely used, because it carries
a performance penalty. In Oracle there is an isolation level called
"serializable", but it actually implements something called
***snapshot isolation***, which is a weaker guarantee than serializability.

#### Durability

***Durability*** is the promise that once a transaction has committed
successfully, any data it has written will not be forgotten.

In a single-node database, durability means that the data has been written to
nonvolatile storage. It usually involves a write-ahead log or similar, which
allows recovery in the event that the data structures on disk are corrupted.

In a replicated database, durability may mean that the data has been
successfully copied to some number of nodes.

#### Replication and Durability

Recently, durability has been adapted to mean replication.

### Single-Object and Multi-Object Operations

In ACID, atomicity and isolation describe what the database should do if a
client makes several writes within the same transaction:

- Atomicity: giving an all-or-nothing guarantee
- Isolation: if one transaction makes several writes, then another transaction
  should see either all or none of those writes, but not some subset.

***Dirty read***: one transaction reads another transaction's uncommitted
writes.

Multi-object transactions require some way of determining which read and write
operations belong to the same transaction.

#### Single-object writes
