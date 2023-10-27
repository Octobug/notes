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
- Deleting records: append a special deletion record to the data file
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

>>>>> progress

The most common type of multi-column index is called a *concatenated index*,
which simply combines several fields into one key by appending one column to
another.

Multi-dimentional indexes are a more general way of querying several columns at
once.
