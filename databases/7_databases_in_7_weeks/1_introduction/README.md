# 1. Introduction

- [1. Introduction](#1-introduction)
  - [It Starts with a Question](#it-starts-with-a-question)
  - [The Genres](#the-genres)

The relational model is still going strong and for many reasons:

- Databases such as PostgreSQL, MySQL, Microsoft SQL Server, and Oracle, amongst
  many others, are still widely used, discussed, and actively developed.
- Knowing how to run SQL queries remains a highly sought-after skill for
  software engineers, data analyst, and others.
- There remains a vast universe of use cases for which a relational database is
  still beyond any reasonable doubt the way to go.

## It Starts with a Question

What database or combination of databases best resolves your problem?

- What type of database is this?
- What was the driving force?
- How do you talk to it?
- What makes it unique?
- How does it perform?
- How does it scale?

## The Genres

- Relational: set-theory-based system implemented as two-dimensional tables with
  rows and columns.
  - PostgreSQL
- Key-Value: a KV store pairs keys to values.
  - Redis
  - DynamoDB
- Columnar: column-oriented, data from a given column is stored together. Adding
  columns is quite inexpensive. Each row can have a different set of columns, or
  none at all. With respect to structure, columnar is about midway between
  relational and key-value.
  - HBase
- Document: A document is like a hash, with a unique ID field and values that
  may be any of a variety of types, including more hashes. Documents can contain
  nested structures.
  - MongoDB
  - CouchDB
- Graph: Graph databases excel at dealing with highly interconnected data. A
  database consists of nodes and relationships between nodes. The real strength
  of graph databases is traversing through the nodes by following relationships.
  - Neo4J
- Polyglot: Using several databases together, leveraging their strengths to
  create an ecosystem that is more powerful, capable, and robust than the sum of
  its parts.
