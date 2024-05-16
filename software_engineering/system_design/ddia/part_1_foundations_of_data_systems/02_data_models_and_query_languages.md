# 2. Data Models and Query Languages

> The limits of my language mean the limits of my world.
>
> —Ludwig Wittgenstein, Tractatus Logico-Philosophicus (1922)

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
      - [Which data model leads to simpler application code?](#which-data-model-leads-to-simpler-application-code)
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
    - [Triple-Stores and SPARQL](#triple-stores-and-sparql)
      - [The semantic web](#the-semantic-web)
      - [The RDF data model](#the-rdf-data-model)
      - [The SPARQL query language](#the-sparql-query-language)
        - [Graph Databases Compared to the Network Model](#graph-databases-compared-to-the-network-model)
    - [The Foundation: Datalog](#the-foundation-datalog)

## Relational Model Versus Document Model

关系型数据库早期主要用于

- 事务处理
- 批处理

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

面向文档的数据库：

- MongoDB
- RethingkDB
- CouchDB
- Espresso

### Many-to-One and Many-to-Many Relationships

- 使用 ID 的好处是，因为它对人类没有任何直接意义，所以永远不需要直接改变。
- 如果数据库本身不支持 join，则需要在应用代码中，通过多次查询间接实现 join。
- 关系模型区分了多种不同范式，但这些区分的实际价值并不大。一个经验法则是，如果复制了多份重复的数据，那么该模式通常就违背了规范化。

### Are Document Databases Repeating History

Hierarchical model works well for one-to-many relationships, but it made
many-to-many relationships difficult. Developers had to decide whether to
denormalize data or to manually resolve references from one record to another.

**Relational model** and **Network model** were created to solve this problem.

#### The network model

Also known as the ***CODASYL*** (Conference On DAta SYstem Languages) model. It
was a generalization of the hierarchical model.

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

- 在关系数据库中，查询优化器自动决定以何种顺序执行查询，以及使用哪些索引。
  这些选择实际上等价于网络模型中的“访问路径”，但最大的区别在于它们是由查询优化器自动生成的，而不是在应用层中维护，因此开发人员不用过多考虑它们。
- 索引的添加非常方便，关系模型使得应用程序添加新功能变得非常容易。

#### Comparison to document databases

文档数据库是某种方式的层次模型：storing nested records within their parent record
rather than in a separate table.

When it comes to representing many-to-one and many-to-many relationships,
relational and document databases are not **fundamentally** different: in both
cases, the related item is referenced by a unique identifier, which is called
a **foreign key** in the relational model and a **document reference** in the
document model.

### Relational Versus Document Databases Today

- The **document data model** is better at schema flexibility, performance due
  to locality, and it is closer to the data structures used by the application.
- The **relational model** is better at supporting for joins, and many-to-one
  and many-to-many relationships.

#### Which data model leads to simpler application code?

- If the data has a data structure like a tree of one-to-many relationships, use
  a document model.
  - Splitting a document-like structure into multiple tables can lead to
    cumbersome schemas and unnecessarily complicated application code.
- If the application uses many-to-many relationships, the document model becomes
  less appealing.
  - Joins can be emulated in application code by making multiple requests to
    the database, but is usually slower than a join performed by specialized
    code inside the database.
  - 这种情况下使用文档模型会导致应用代码更复杂。

For highly interconnected data, the document model is awkward, the relational
model is acceptable, and graph models are the most natural.

#### Schema flexibility in the document model

The code that reads the data usually assumes some kind of structure, which is
not enforced by the database. ***schema-on-read*** is a more accurate term than
***schemaless***. In contrast, ***schema-on-write*** refers to the traditional
approach of relational databases.

`schema-on-read` is similar to **dynamic type checking** in programming
languages, `schema-on-write` is similar to **static type checking**.

Most relational database systems execute the `ALTER TABLE` statement so quickly.
But MySQL is a notable exception -- it copies the entire table on `ALTER TABLE`,
which can lead to minutes or even hours of downtime.

Running the `UPDATE` statement on a large table is likely to be slow on any
databse. If that is unacceptable, the application can leave a new column set to
its default `NULL` and fill it in at read time just like it does with a
document database.

#### Data locality for queries

If data is splitted across multiple tables, multiple index lookups are required
to retrive it all requiring more disk seeks and taking more time.

The locality advantage only applies if large parts of the document is needed at
the same time.

On updates to a document, the entire document usually needs to be rewritten --
only modifications that don't change the encoded size of a document can easily
be performed in place.

#### Convergence of document and relational databases

It seems that relational and document databases are becoming more similar over
time, and that is a good thing.

## Query Languages for Data

SQL is a ***declarative*** (声明式) query language, whereas IMS and CODASYL use
***imperative*** code to query.

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

The `map` (也称为 `collect`) and `reduce` (也称为 `fold` 或 `inject`) functions
which used in this process are restricted in what they are allowed to do. They
must be *pure* functions.

- MapReduce 的一个可用性问题是，必须编写两个密切协调的 JavaScript 函数，这通常比写单个查询更难。
- 声明式查询语言为查询优化器提供了更多提高查询性能的机会。
- MongoDB 2.2 增加了称为“集合管道”的声明式查询语言的支持（相当于发明 SQL……）。

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

图模型的特点：

1. 任何顶点都可以连接到其他任何顶点。没有 schema 限制哪种事物可以或不可以关联。
2. 给定某个顶点，可以高效地得到它的所有入边和出边，从而遍历图，即沿着这些顶点链条一直向前或向后。
3. 通过对不同类型的关系使用不同的标签，可以在单个图中存储多种不同类型的信息，同时仍然保持整洁的数据模型。

Graphs are good for evolvability, as features is added to the application, a
graph can easily be extended to accommodate changes in the application's data
structures.

### The Cypher Query Language

***Cypher*** is a declarative query language for property graphs. 与密码学无关。

对于声明式查询语言，查询优化器会自动选择效率最高的执行策略，开发者可以专注于应用的其他部分。

### Graph Queries in SQL

In a relational database, which joins are needed are usually known in advance.

对于图查询，在找到要查找的顶点之前，可能需要遍历数量未知的边，也就是说，join 操作的数量并不是预先确定的。

Cypher 可以用 `:WITHIN*0..` 简洁地表达：沿着一个 WITHIN 边，遍历 0 次或多次。

在 SQL 中，这种可变的遍历路径可以使用称为**递归公用表表达式**（`WITH RECURSIVE`）表示。

### Triple-Stores and SPARQL

The triple-store model is mostly equivalent to the property graph model, using
different words to desctibe the same ideas.

In a triple-store, all information is stored in the form of very simple
three-part statements:

- ***subject*** (eg. Jim) `=` a vertex in a graph
- ***predicate*** (eg. likes) `=`
- ***object*** (eg. bananas) `=`
  - a value in a primitive datatype: `_:usa :name "United States"`
    - predicate `=` key of a property on the subject vertex (e.g. age)
    - object `=` value of a property on the subject vertex (e.g. 33)
  - another vertex in the graph: `_:idaho :within _:usa`
    - subject `=` the tail vertex
    - predicate `=` the edge
    - object `=` the head vertex (which has the arrow)

#### The semantic web

The triple-store data model is completely independent of the semantic web.

语义网从本质上讲源于一个简单而合理的想法：网站通常将信息以文字和图片方式发布给人类阅读，那为什么不把信息发布为机器可读的格式给计算机阅读呢？

The ***Resource Description Framework (RDF)*** was intended as a mechanism for
different websites to publish data in a consistent format, allowing data from
different websites to be aumatically combined into a web format -- a kind of
internet-wide "database of everything".

目前没有靠谱的实现。

#### The RDF data model

- Turtle 语言代表 RDF 数据的人类可读格式
- RDF 也用 XML 编写

#### The SPARQL query language

*SPARQL*(SPARQL Procotol and RDF Query Language, pronounced "sparkle") is a
query languagr for triple-stores using the RDF data model.

SPARQL 比 Cypher 更简洁一些：

- `(person) -[:BORN_IN]-> () -[:WITHIN*0..]-> (location)   # Cypher`
- `?person :bornIn / :within* ?location.                   # SPARQL`

RDF 不区分属性和边，可以同时对两者执行谓语操作，所以可以采用相同的语法来匹配属性上的查询条件：

- `(usa {name:'United States'})   # Cypher`
- `?usa :name "United States".    # SPARQL`

##### Graph Databases Compared to the Network Model

They differ in several important ways:

- In CODASYL, a database had a schema that specified which record type could be
  nested within other record type. In a graph database, there is no such
  restriction.
- In CODASYL, the only way to reach a particular record was to traverse one of
  the access paths to it. In a graph database, you can refer directly to any
  vertex by its unique ID.
- In CODASYL, the children of a record were an ordered set, so the database had
  to maintain that ordering, and applications had to worry about the positions
  of the new records in these sets. In a graph database, vertices and edges are
  not ordered.
- In CODASYL, all queries are imperative, easily broken by changes in the
  schema. Most graph databases support high-level, declarative query languages.

### The Foundation: Datalog

***Datalog*** provides the foundation that later query languages build upon.
***Cascalog*** is a Datalog implemantation for querying large datasets in
Hadoop.

- format: `predicate (subject, object)`
