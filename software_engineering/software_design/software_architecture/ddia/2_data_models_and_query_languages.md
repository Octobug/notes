# 2. Data Models and Query Languages

- [2. Data Models and Query Languages](#2-data-models-and-query-languages)
  - [Relational Model Versus Document Model](#relational-model-versus-document-model)
    - [The Birth of NoSQL](#the-birth-of-nosql)
    - [The Object-Relational Mismatch](#the-object-relational-mismatch)
    - [Many-to-One and Many-to-Many Relationships](#many-to-one-and-many-to-many-relationships)
    - [Are Document Databases Repeating History](#are-document-databases-repeating-history)
      - [The network model](#the-network-model)
      - [The relational model](#the-relational-model)
      - [Comparison to document databases](#comparison-to-document-databases)
    - [Relational Versus Document Databases Today](#relational-versus-document-databases-today)
      - [Which data model leads to simpler application code](#which-data-model-leads-to-simpler-application-code)
      - [Schema flexibility in the document model](#schema-flexibility-in-the-document-model)
      - [Data locality for queries](#data-locality-for-queries)
      - [Convergence of document and relational databases](#convergence-of-document-and-relational-databases)
  - [Query Languages for Data](#query-languages-for-data)
    - [Declarative Queries on the Web](#declarative-queries-on-the-web)
    - [MapReduce Querying](#mapreduce-querying)
  - [Graph-Like Data Models](#graph-like-data-models)
    - [Property Graphs](#property-graphs)
    - [The Cypher Query Language](#the-cypher-query-language)
    - [Graph Queries in SQL](#graph-queries-in-sql)

## Relational Model Versus Document Model

### The Birth of NoSQL

**NoSQL** was originally intended simply as a catchy Twitter hashtag for a
meetup on open source, distributed, nonrelational databases in 2009.

But now it stands for ***Not Only SQL***.

There are several needs for NoSQL databases:

- For greater scalability than relational databases can achieve, including very
  large datasets or very high write throughput
- Preference for free and open source softwares
- Specialized query operations that are not well supported by the relational
  model
- Frustration with the restrictiveness of relational schemas, and a desire for
  a more dynamic and expressive data model

### The Object-Relational Mismatch

Criticism of the SQL data model: if data is stored in relational tables, a
translation layer is required between the objects in the application code and
the database model of tables, rows, and columns. The disconnect between the
models is sometimes called an ***impedance mismatch***.

### Many-to-One and Many-to-Many Relationships

### Are Document Databases Repeating History

Hierarchical model works well for one-to-many relationships, but it made
many-to-many relationships difficult. Developers had to decide whether to
denormalize data or to manually resolve references from one record to another.

**Relational model** and **Network model** were created to solve this problem.

#### The network model

Also known as the ***CODASYL*** model. It was a generalization of the
hierarchical model.

In the tree structure of the hierarchical model, every record has exactly one
parent; in the network model, a record could have multiple parents, and those
parents could be linked to the record.

The links between records in the network model were not foreign keys, but more
like pointers. The only way of accessing a record was to follow a path from a
root record along these chains of links. This was called an ***access path***.

If a record had multiple parents, the application code had to keep track of all
the various relationships. This was like navigating around an *n-dimensional*
data space.

And this made the code for querying and updating the database complicated and
inflexible.

#### The relational model

#### Comparison to document databases

Document databases reverted back to the hierarchical model in one aspect:
storing nested records within their parent record rather than in a separate
table.

When it comes to representing many-to-one and many-to-many relationships,
relational and document databases are not **fundamentally** different: in both
cases, the related item is referenced by a unique identifier, which is called
a **foreign key** in the relational model and a **document reference** in the
document model.

### Relational Versus Document Databases Today

- The documents data model is better at schema flexibility, performance due to
  locality, and it is closer to the data structures used by the application.
- The relational model is better at supporting for joins, and many-to-one and
  many-to-many relationships.

#### Which data model leads to simpler application code

If the data has a data structure like a tree of one-to-many relationships, use
a document model. Splitting a document-like structure into multiple tables can
lead to cumbersome schemas and unnecessarily complicated application code.

If the application uses many-to-many relationships, the document model becomes
less appealing. Joins can be emulated in application code by making multiple
requests to the database, but is usually slower than a join performed by
specialized code inside the database.

For highly interconnected data, the document model is awkward, the relational
model is acceptable, and graph models are the most natural.

#### Schema flexibility in the document model

The code that reads the data usually assumes some kind of structure, which is
not enforced by the database. *schema-on-read* is a more accurate term than
*schemaless*. In contrast, *schema-on-write* refers to the traditional approach
of relational databases.

schema-on-read is similar to dynamic type checking in programming languages,
schema-on-write is similar to static type checking.

Most relational database systems execute the `ALTER TABLE` statement so quick.
But MySQL is a notable exception -- it copies the entire table on `ALTER TABLE`,
which can lead to minutes or even hours of downtime.

Running the `UPDATE` statement on a large table is likely to be slow on any
databse. If that is unacceptable, the application can leave a new column set to
its default `NULL` and fill it in at read time just like it does with a
document database.

#### Data locality for queries

If data is split across multiple tables, multiple index lookups are required to
retrive it all requiring more disk seeks and taking more time.

The locality advantage only applies if large parts of the document is needed at
the same time.

On updates to a document, the entire document usually needs to be rewritten --
only modifications that don't change the encoded size of a document can easily
be performed in place.

#### Convergence of document and relational databases

It seems that relational and document databases are becoming more similar over
time, and that is a good thing.

## Query Languages for Data

SQL is a *declarative* query language, whereas IMS and CODASYL use *imperative*
code to query.

- Declarative languages often lend themselves to parallel execution.
- Imperative code is very hard to paralize across multiple cores and multiple
  machines, because it specifies instructions that must be performed in a
  particular order.

### Declarative Queries on the Web

Declarative queries with CSS can lower the implementation details to the
browser level.

### MapReduce Querying

***MapReduce*** is a programming model for processing large amounts of data in
bulk across many machines.

MapReduce is neither a declarative query language nor a fully imperative query
API, but somewhere in between: the logic of the query is expressed with snippets
of code, which are called repeatedly by the processing framework.

The `map` and `reduce` functions which used in this process are restricted in
what they are allowed to do. They must be *pure* functions.

## Graph-Like Data Models

As connections within data become more complex, it's more natural to model data
as a graph.

A graph consists of two kinds of objects:

- vertices
- edges

### Property Graphs

In the property graph model, each vertex consists of:

- A unique identifier
- A set of outgoing edges
- A set of incoming edges
- A collection of properties

Each edge consists of:

- A unique identifier
- The vertex at which the edge starts (the *tail* vertex)
- The vertex at which the edge ends (the *head* vertex)
- A label to describe the kind of relationship between the two vertices
- A collection of properties (key-value pairs)

Graphs are good for evolvability, as features is added to the application, a
graph can easily be extended to accommodate changes in the application's data
structures.

### The Cypher Query Language

***Cypher*** is a declarative query language for property graphs.

### Graph Queries in SQL

>>>>> progress

In a relational database, which joins are needed are usually known in advance.
