# 3. Storage and Retrieval

- [3. Storage and Retrieval](#3-storage-and-retrieval)
  - [Data Structures That Power Your Database](#data-structures-that-power-your-database)
    - [Hash Indexes](#hash-indexes)
    - [SSTables and LSM-Trees](#sstables-and-lsm-trees)
      - [Constructing and maintaining SSTables](#constructing-and-maintaining-sstables)
      - [Making an LSM-tree out of SSTables](#making-an-lsm-tree-out-of-sstables)
      - [Performance optimizations](#performance-optimizations)
    - [B-Trees](#b-trees)

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

>>>>> progress
