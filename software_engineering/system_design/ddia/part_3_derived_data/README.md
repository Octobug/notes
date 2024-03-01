# Part III. Derived Data

- [Part III. Derived Data](#part-iii-derived-data)
  - [Systems of Record and Derived Data](#systems-of-record-and-derived-data)
  - [Overview of Chapters](#overview-of-chapters)

In a large application you often need to be able to access and process data in
many different ways, and there is no one database that can satisfy all those
different needs simultaneously. Applications thus commonly use a combination of
several different datastores, indexes, caches, analytics systems, etc. and
implement mechanisms for moving data from one store to another.

## Systems of Record and Derived Data

On a high level, systems that store and process data can be grouped into two
broad categories:

- ***Systems of record***: A system of record, also known as source of truth,
  holds the authoritative version of your data. When new data comes in it is
  first written here. Each fact is represented exactly once (the representation
  is typically normalized). If there is any discrepancy between another system
  and the system of record, then the value in the system of record is the
  correct one.
- ***Derived data systems***: Data in a derived system is the result of taking
  some existing data from another system and transforming or processing it in
  some way. If you lose derived data, you can recreate it from the original
  source. A classic example is a cache: data can be served from the cache if
  present, but if the cache doesn’t contain what you need, you can fall back to
  the underlying database. Denormalized values, indexes, and materialized views
  also fall into this category. In recommendation systems, predictive summary
  data is often derived from usage logs.

Technically speaking, derived data is ***redundant***, in the sense that it
duplicates existing information. However, it is often essential for getting
good performance on read queries. It is commonly denormalized. You can derive
several different datasets from a single source, enabling you to look at the
data from different “points of view.”

Not all systems make a clear distinction between *systems of record* and
*derived data* in their architecture, but it’s a very helpful distinction to
make, because it clarifies the dataflow through your system: it makes explicit
which parts of the system have which inputs and which outputs, and how they
depend on each other.

Most databases, storage engines, and query languages are not inherently either
a system of record or a derived system. A database is just a tool: how you use
it is up to you. The distinction between *system of record* and
*derived data system* depends not on the tool, but on how you use it in your
application.

By being clear about which data is derived from which other data, you can bring
clarity to an otherwise confusing system architecture.

## Overview of Chapters
