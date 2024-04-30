# 3. Storage and Retrieval

- [3. Storage and Retrieval](#3-storage-and-retrieval)
  - [Data Structures That Power Your Database](#data-structures-that-power-your-database)
    - [Hash Indexes](#hash-indexes)
    - [SSTables and LSM-Trees](#sstables-and-lsm-trees)
      - [Constructing and maintaining SSTables](#constructing-and-maintaining-sstables)
      - [Making an LSM-tree out of SSTables](#making-an-lsm-tree-out-of-sstables)
      - [Performance optimizations](#performance-optimizations)
    - [B-Trees](#b-trees)
      - [Making B-trees reliable](#making-b-trees-reliable)
      - [B-tree optimizations](#b-tree-optimizations)
    - [Comparing B-Trees and LSM-Trees](#comparing-b-trees-and-lsm-trees)
      - [Advantages of LSM-trees](#advantages-of-lsm-trees)
      - [Downsides of LSM-trees](#downsides-of-lsm-trees)
    - [Other Indexing Structures](#other-indexing-structures)
      - [Storing values within the index](#storing-values-within-the-index)
      - [Multi-column indexes](#multi-column-indexes)
      - [Full-text search and fuzzy indexes](#full-text-search-and-fuzzy-indexes)
      - [Keeping everything in memory](#keeping-everything-in-memory)
  - [Transaction Processing or Analytics](#transaction-processing-or-analytics)
    - [Data Warehousing](#data-warehousing)
      - [The divergence between OLTP databases and data warehouses](#the-divergence-between-oltp-databases-and-data-warehouses)
    - [Stars and Snowflakes: Schemas for Analytics](#stars-and-snowflakes-schemas-for-analytics)
  - [Column-Oriented Storage](#column-oriented-storage)
    - [Column Compression](#column-compression)
      - [Memory bandwidth and vectorized processing](#memory-bandwidth-and-vectorized-processing)
    - [Sort Order in Column Storage](#sort-order-in-column-storage)
      - [Several different sort orders](#several-different-sort-orders)
    - [Writing to Column-Oriented Storage](#writing-to-column-oriented-storage)
    - [Aggregation: Data Cubes and Materialized Views](#aggregation-data-cubes-and-materialized-views)

There is a big difference between storage engines that are optimized for
transactional workloads and those that are optimized for analytics.

## Data Structures That Power Your Database

**log**: (in the more general sense) an append-only sequence of records.

**index**: additional structure that is derived from the primary data.

- Maintaining additional structures incurs overhead, especially on writes.
- It's hard to beat the performance of simply appending to a file, because it's
  the simplest possible write operation.
- Any kind of index usually slows down writes, because the index also needs to
  be updated every time data is written.

### Hash Indexes

Some of the issues that are important in a real implementation for a key-value
storage engine with hash indexs:

- File format: CSV-like vs. others such as a binary format
- Deleting records: append a special deletion record (***tombstone***) to the
  data file
- Crash recovery: Bitcask speeds up recovery by storing a snapshot of each
  segment's hash map on disk, which can be loaded into memory more quickly.
- Partially written records: Bitcask files include checksums, allowing such
  corrupted parts of the log to be detected and ignored.
- Concurrency control: A common implementation choice is to have only one writer
  thread.

An append-only design turns out to be good for several reasons:

- Appending and segment merging are sequential write operations, which are
  generally much faster than random writes, especially on magnetic spinning-disk
  hard drives.
- Concurrency and crash recovery are much simpler if segment files are
  append-only or immutable.
- Merging old segments avoids the problem of data files getting fragmented over
  time.

Limitations:

- The hash table must fit in memory. If a hash map is maintained on disk, a lot
  of random access I/O is needed. And hash collisions require fiddly logic.
- Range queries are not efficient. You would have to look up each key
  individually in the hash map.

### SSTables and LSM-Trees

**SSTable (Sorted String Table)**:

- the sequence of key-value pairs is sorted by key.
- each key only appears once within each merged segment file (the compaction
  process already ensures that).

SSTables have several big advantages over log segments with hash indexes:

1. Merging segments is simple and efficient, even if the files are bigger than
   the available memory. The approach is like the one used in the mergesort
   algorithm.
2. In order to find a particular key in the file, keeping an index of all the
   keys in memory is no longer needed. But a sparse index is still needed: You
   can first search for a key which is indexed, and then start scanning from
   there.
3. Since read requests need to scan over several key-value pairs in the
   requested range anyway, it is possible to group those records into a block
   and compress it before writing it to disk.

#### Constructing and maintaining SSTables

> LSM-trees

The storage engine works as follows:

- When a write comes in, add it to an in-memory balanced tree data structure.
  This tree is sometimes called a ***memtable***.
- When the memtable gets bigger than some threshold, write it out to disk as an
  SSTable file. The new SSTable file becomes the most recent segment of the
  database.
- In order to serve a read request, first try to find the key in the memtable,
  then in most recent on-disk segment, then in the next-older segment, etc.
- From time to time, run a merging and compaction process in the background to
  combine segment files and to discard overwritten or deleted values.

This scheme only suffers from one problem: if the database crashes, the most
recent writes which are in the memtable are lost.

In order to avoid that problem, we can keep a separate log on disk to which
every write is immediately appended, which is an append-only file and is not in
sorted order. Every time the memtable is written out to an SSTable, its log file
can be discarded.

#### Making an LSM-tree out of SSTables

This indexing structure is under the name
**LSM-tree (Log-Structured Merge-Tree)**.

Storage engines that are based on this principle of merging and compacting
sorted files are often called LSM storage engines.

> <https://stackoverflow.com/a/71106360/7267801>

- Now there is only one file to read in a case of a crash: the memtable backup
- Indexes could be sparse, thus fitting the RAM is easier
- Range queries are now possible

An SSTable is a key-sorted append-only key-value storage. An LSM-tree is a
layered data structure, based on a balanced tree, that allows SSTables to exist
without the controversy of being both sorted and append-only at the same time.

#### Performance optimizations

The LSM-tree algorithm can be slow when looking up keys that do not exist in the
database: you have to check the memtable, then the segment all the way back to
the oldest before you can be sure that the key does not exist.

In order to optimize this kind of access, storage engines often use additional
**Bloom filters**.

A Bloom filter is a memory-efficient data structure for approximating the
contents of a set. It can tell you if a key does not appear in the database.

There are also different stratigies to determine the order and timing of how
SSTables are compacted and merged. The most common options are ***size-tiered***
and ***leveled*** compaction.

### B-Trees

Like SSTables, B-trees keep key-value pairs sorted by key, which allows
efficient key-value lookups and range queries.

The log-structured indexes break the database down into variable-size
***segments***, typically several megabytes or more in size, and always write a
segment sequentially.

By contrast, B-trees break the database down into fixed-size ***blocks*** or
***pages***, traditionally 4 KB in size (sometimes bigger), and read or write
one page at a time to correspond more closely to the underlying hardware.

One page is designated as the root of the B-tree. The page contains several keys
and references to child pages.

The number of references to child pages in one page of the B-tree is called the
***branching factor***. In practice, the branching factor is typically several
hundred.

If there isn't enough free space in the page to accommodate a new key, it is
split into two half-full pages, and the parent page is updated to account for
the new subdivision of key ranges.

Most databases can fit into a B-tree that is 3 or 4 levels deep. A 4-level tree
of 4 KB pages with a branching factor of 500 can store up to 256 TB.

#### Making B-trees reliable

The basic underlying write operation of a B-tree is to overwrite a page on disk
with new data.

Some operations require several different pages to be overwritten. For example,
if a page is splited because an insertion caused it to be overfull, there will
be two new pages to be written, and also their parent page to be updated the
references to the two new child pages. This is a dangerous operation because the
database may crash, ending up with a corrupted index.

In order to make the database resilient to crashes, it is common for B-tree
implementations to include an additional data structure on disk: a
***write-ahead log (WAL)***, also known as a ***redo log***. This is an
append-only file to which every B-tree modification must be written before it
can be applied to the pages of the tree itself.

***latches*** (lightweight locks) is used to provide concurrency control to
protect the consistency of the tree's data structures.

Log-structured approaches are simpler in this regard, because they do all the
merging in the background without interfering with incoming queries and
atomically swap old segments for new segments from time to time.

#### B-tree optimizations

- Instead of overwriting pages and maintaining a WAL for crash recovery, some
  databases use a copy-on-write scheme. A modified page is written to a
  different location, and a new version of the parent pages in the tree is
  created, pointing at the new location.
- We can save space in pages by not storing the entire key, but abbrevating it.
  Packing more keys into a page allows the tree to have a higher branching
  factor, and thus fewer levels. This variant is sometimes known as a
  $B^+tree$ (InnoDB).
- Many B-tree implementations try to lay out the tree so that leaf pages appear
  in sequential order on disk. However, it's difficult to maintain that order as
  the tree grows. By contrast, since LSM-trees rewrite large segments of the
  storage in one go during merging, it's easier for them to keep sequential keys
  close to each other on disk.
- Additional pointers have been added to the tree. Each leaf page may have
  references to its sibling pages to the left and right, which allows scanning
  keys in order without jumping back to parent pages.
- B-tree variants such as **fractal trees** borrow some log-structured ideas to
  reduce disk seeks.

### Comparing B-Trees and LSM-Trees

As a rule of thumb, LSM-trees are typically faster for writes, whereas B-trees
are thought to be faster for reads. Reads are typically slower on LSM-trees
because they have to check several different data structures and SSTables at
different stages of compaction.

⚠️ However, benchmarks are often inconclusive and sensitive to details of the
workload.

#### Advantages of LSM-trees

A B-tree index must write every piece of data at least **twice**: once to the
write-ahead log, and once to the tree page itself. There is also overhead from
having to write an entire page at a time, even if only a few bytes in that page
changed.

Log-structured indexes also rewrite data multiple times due to repeated
compaction and merging of SSTables. This one write to the database resulting in
multiple writes to the disk is known as ***write amplification***.

LSM-trees are typically able to sustain higher write throughput than B-trees,
partly because they sometimes have lower write amplification. and partly because
they sequentially write compact SSTable files rather than having to overwrite
several pages in the tree.

LSM-trees can be compressed better, and thus often produce smaller files on disk
than B-trees. B-tree storage engines leave some disk space unused due to
fragmentation: when a page is split or when a row cannot fit into an existing
page, some space in a page remains unused.

#### Downsides of LSM-trees

A downside of log-structured storage is that the compaction process can
sometimes interfere with the performance of ongoing reads and writes. It can
easily happen that a request needs to wait while the disk finishes an expensive
compaction operation.

The bigger the database gets, the more disk bandwidth is required for
compaction.

If write throughput is high and compaction is not configured carefully, it can
happen that compaction cannot keep up with the rate of incoming writes. Reads
slow down because they need to check more segment files.

An advantage of B-trees is that each key exists in exactly one place in the
index, whereas a log-structured storage engine may have multiple copies of the
same key in different segments. This aspect makes B-trees attractive in
databases that want to offer strong transactional semantics. Transaction
isolation is implemented using locks on ranges of keys, and in a B-tree index,
those locks can be directly attached to the tree.

Testing empirically is needed for determining which type of storage engine is
better for your use case.

### Other Indexing Structures

It is also very common to have *secondary indexes*. In relational databases,
they are often crucial performing joins efficiently.

A secondary index can easily be constructed from a key-value index. The main
difference is that keys are not unique. This can be solved in two ways:

- making each value in the index a list of matching row identifiers
- making each key unique by appending a row identifier to it

#### Storing values within the index

The value in an index could be a reference to the row stored elsewhere.
A *heap file* stores these rows in no particular order. This approach avoids
duplicating data when multiple secondary indexes are present: each index
references a location in the heap file, and the actual data is kept in one
place.

If the new value is larger than the old value, it probably needs to be moved to
a new location in the heap where there is enough space. In that case, either all
indexes need to be updated to point at the new heap location, or a forwarding
pointer is left behind in the old heap location.

A *clustered index* is what stores the indexed row directly within an index.
In MySQL's InnoDB storage engine, the primary key of a table is always a
clustered index, and secondary indexes refer to the primary key rather than a
heap file location.

A compromise between a clustered index and a nonclustered index is known as a
*covering index* or *index with included columns*, which stores some of a
table's columns within the index. Thus corresponding queries could use the index
alone.

#### Multi-column indexes

The most common type of multi-column index is called a ***concatenated index***,
which simply combines several fields into one key by appending one column to
another.

Multi-dimentional indexes are a more general way of querying several columns at
once. Commonly, specialized indexes such as R-trees are used.

#### Full-text search and fuzzy indexes

- Lucene

#### Keeping everything in memory

Some in-memory-key-value stores are intended for caching use only, some others
aim for durability, which can be achieved with special hardware, by writing a
log of changes to disk, by writing periodic snapshots to disk, or by replicating
the in-memory-state to other machines.

When an in-memory database is restarted, it needs to reload its state, either
from disk or over the network from a replica.

Products:

- relational:
  - VoltDB
  - MemSQL
  - Oracle TimesTen
- non-relational
  - RAMCloud
  - Redis
  - Counchbase

Counterintuitively, the performance advantage of in-memory databases is not due
to the fact that they don't need to read from disk: the operating system caches
recently used disk blocks in memory. They can be faster because they avoid the
overheads of encoding in-memory data structures in a form that can be written to
disk.

Besides performance, it's easier to provide some data models that are difficult
to implement with disk-based indexes with in-memory databases.

To support datasets larger than the available memory, the so-called
*anti-caching* approach works by evicting the least recently used data from
memory to disk when there is not enough memory.

## Transaction Processing or Analytics

A transaction needn't necessarily have ACID (atomicity, consistency, isolation,
and durability) properties. ***Transaction processing*** just means allowing
clients to make low-latency reads and writes -- as opposed to
***batch processing*** jobs, which only run periodically.

***OLTP (OnLine Transaction Processing)*** typically exists in applications that
are interactive.

An analytic query in *data analytics* needs to scan over a huge numbers of
records, only reading a few columns per record, and calculates aggregate
statistics rather than returning the raw data to the user. This has been called
***OLAP (OnLine Analytic Processing)*** to differentiate from transaction
processing.

**Comparing characteristics of transaction processing versus analytic systems**.

| Property   | OLTP                              | OLAP                        |
| ---------- | --------------------------------- | --------------------------- |
| Read       | Small number, fetched by key      | Aggregate over many records |
| Write      | Random-access, low latency writes | Bulk import or event stream |
| Used by    | End user                          | Internal analyst            |
| Represents | Latest state of data              | History of events           |
| Data size  | Gigabytes to terabytes            | Terabytes to petabytes      |

### Data Warehousing

The data warehouse contains a read-only copy of the data in all the various OLTP
systems in the company. Data is extracted from OLTP databases, transformed into
an analysis-friendly schema, cleaned up, and then loaded into the data
warehouse. This process of getting data into the warehouse is known as
***Extract-Transform-Load (ETL)***.

A big advantage of using a separate data warehouse, rather than querying OLTP
systems directly for analytics, is that the data warehouse can be optimized for
analytic access patterns. Indexing algorithms work well for OLTP, but are not
very good at answering analytic queries.

#### The divergence between OLTP databases and data warehouses

The data model of a data warehouse is most commonly relational, because SQL is
generally a good fit for analytic queries.

A data warehouse and a relational OLTP database look similar on the surface, but
in the internals they can look quite different, because they are optimized for
very different query patterns.

### Stars and Snowflakes: Schemas for Analytics

Many data warehouses are used in a fairly formulaic style, known as a
***star schema***, also known as *dimensional modeling*.

At the center of a star schema is a so-called ***fact table***. Each row of the
fact table represents an event that occurred at a particular time.

Usually, facts are captured as individual events, because this allows maximum
flexibitily of analysis later. However, this means that the fact table can
become extremely large.

Some of the columns in the fact table are attributes, other columns in the fact
table are foreign key references to other tables, called *dimension tables*. As
each row in the fact table represents an event, the dimensions represent the
who, what, where, when, how, and why of the event.

The name "star schema" comes from the fact that when the table relationships are
visualized, the fact table is in the middle, surrounded by its dimension tables;
the connections to these tables are like the rays of a star.

A variation of this template is known as the *snowflake schema*, where
dimensions are further broken down into subdimensions.

Snowflake schemas are more normalized than star schemas, but star are often
preferred because they are simpler for analysts to work with.

Fact tables often have over 100 columns, sometimes several hundreds. Dimension
tables can also be very wide.

## Column-Oriented Storage

In most OLTP databases, storage is laid out in a *row-oriented* fashion: all the
values from one row of a table are stored next to each other. Document databases
are similar: an entire documents is typically stored as one contiguous sequence
of bytes.

A row-oriented storage engine needs to load all of those rows with all of their
columns from disk into memory, parse them, and filter out those that don't meet
the required conditions.

The idea behind *column-oriented storage* is simple: don't store all the values
from one row together, but store all the values from each column together. If
each column is stored in a separate file, a query only needs to read and parse
those columns that are used in that query.

The column-orientied storage layout relies on each column file containing the
rows in the same order.

### Column Compression

Depending on the data in the column, different compression techniques can be
used. One techique that is particularly effective in data warehouses is
***bitmap encoding***.

```bitmap
Column values:
product_sk:       69 69 69 69 74 31 31 31 31 29 30 30 31 31 31 68 69 69

Bitmap for each possible value:
product_sk = 29:  0  0  0  0  0  0  0  0  0  1
product_sk = 30:  0  0  0  0  0  0  0  0  0  0  1  1
product_sk = 31:  0  0  0  0  0  1  1  1  1  0  0  0  1  1  1
product_sk = 68:  0  0  0  0  0  0  0  0  0  0  0  0  0  0  0  1
product_sk = 69:  1  1  1  1  0  0  0  0  0  0  0  0  0  0  0  0  1  1
product_sk = 74:  0  0  0  0  1

Run-length encoding:
product_sk = 29:  9,1           (9 zeros, 1 one, rest zeros)
product_sk = 30:  10,2
product_sk = 31:  5,4,3,3       (5 zeros, 4 ones, 3 zeros, 3 ones, rest zeros)
product_sk = 68:  15,1
product_sk = 69:  0,4,12,2
product_sk = 74:  4,1
```

A column with `n` distinct values can turn into `n` separate bitmaps: one
bitmap for each distinct value, with one bit for each row.

If `n` is very small, those bitmaps can be stored with one bit per row.

But if `n` is bigger, there will be a lot of zeros in most of the bitmaps. In
that case, the bitmaps can additionally be run-length encoded.

#### Memory bandwidth and vectorized processing

The bandwidth for getting data from disk into memory and the bandwidth from
main memory into the CPU cache can both be the bottleneck.

Column-oriented storage layouts reduce the volume of data that needs to be
loaded from disk. Column compression and bitwise operations fit better in CPU
executions.

### Sort Order in Column Storage

#### Several different sort orders

Data can be stored redundantly in multiple machines sorted in different ways.

### Writing to Column-Oriented Storage

An update-in-place approach is not possible with compressed columns. If you
wanted to insert a row in the middle of a sorted table, you would most likely
have to rewrite all the column files.

The solution used by LSM-trees is also good for column-oriented storage. Queries
need to examine both the column data on disk and the recent writes in memory.

### Aggregation: Data Cubes and Materialized Views

Column-oriented storage can be significantly faster than row-oriented storage
for ad hod analytical queries.

A ***materialized view*** could be used to create a cache of aggregation
queries. In a relational data model, it is often defined like a standard view.
A materialized view is an actual copy of the query results, written to disk.

Data updates make writes more expensive, which is why materialized view are not
often used in OLTP databases.
