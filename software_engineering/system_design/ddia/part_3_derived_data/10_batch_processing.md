# 10. Batch Processing

> A system cannot be successful if it is too strongly influenced by a single
> person. Once the initial design is complete and fairly robust, the real test
> begins as people with many different viewpoints undertake their own
> experiments.
>
> —Donald Knuth

- [10. Batch Processing](#10-batch-processing)
  - [Batch Processing with Unix Tools](#batch-processing-with-unix-tools)
    - [Simple Log Analysis](#simple-log-analysis)
      - [Chain of commands versus custom program](#chain-of-commands-versus-custom-program)
      - [Sorting versus in-memory aggregation](#sorting-versus-in-memory-aggregation)
    - [The Unix Philosophy](#the-unix-philosophy)
      - [A uniform interface](#a-uniform-interface)
      - [Separation of logic and wiring](#separation-of-logic-and-wiring)
      - [Transparency and experimentation](#transparency-and-experimentation)
  - [MapReduce and Distributed Filesystems](#mapreduce-and-distributed-filesystems)
    - [MapReduce Job Execution](#mapreduce-job-execution)

Three different types of systems:

- ***Services (online systems)***: A service waits for a request or instruction
  from a client to arrive. When one is received, the service tries to handle it
  as quickly as possible and sends a response back.
- ***Batch processing systems (offline systems)***: A batch processing system
  takes a large amount of input data, runs a job to process it, and produces
  some output data. Jobs often take a while (from a few minutes to several
  days). Batch jobs are often scheduled to run periodically. The primary
  performance measure of a batch job is usually throughput (the time it takes
  to crunch through an input dataset of a certain size).
- ***Stream processing systems (near-real-time systems)***: Stream processing
  is somewhere between online and offline/batch processing (so it is sometimes
  called ***near-real-time*** or ***nearline*** processing). Like a batch
  processing system, a stream processor consumes inputs and produces outputs.
  However, a stream job operates on events shortly after they happen, whereas a
  batch job operates on a fixed set of input data. This difference allows
  stream processing systems to have lower latency than the equivalent batch
  systems.

Batch processing is an important building block in our quest to build reliable,
scalable, and maintainable applications. For example, MapReduce, was called
“the algorithm that makes Google so massively scalable”. It was subsequently
implemented in various open source data systems, including Hadoop, CouchDB, and
MongoDB.

MapReduce is a fairly low-level programming model compared to the parallel
processing systems that were developed for data warehouses many years
previously, but it was a major step forward in terms of the scale of processing
that could be achieved on commodity hardware. It provides a clear picture of
why and how batch processing is useful.

The ideas and lessons from Unix carry over to large-scale, heterogeneous
distributed data systems.

## Batch Processing with Unix Tools

Say you have a web server that appends a line to a log file every time it
serves a request. For example, using the nginx default access log format, one
line of the log might look like this:

```log
216.58.210.78 - - [27/Feb/2015:17:55:11 +0000] "GET /css/typography.css HTTP/1.1"
200 3377 "http://martin.kleppmann.com/" "Mozilla/5.0 (Macintosh; Intel Mac OS X
10_9_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/40.0.2214.115
Safari/537.36"
```

In order to interpret it, you need to look at the definition of the log format:

```log
$remote_addr - $remote_user [$time_local] "$request"
$status $body_bytes_sent "$http_referer" "$http_user_agent"
```

### Simple Log Analysis

Say you want to find the five most popular pages on your website:

```sh
cat /var/log/nginx/access.log | # 1.
  awk '{print $7}' |            # 2.
  sort             |            # 3.
  uniq -c          |            # 4.
  sort -r -n       |            # 5.
  head -n 5                     # 6.
```

1. Read the log file.
2. Split each line into fields by whitespace, and output only the seventh such
   field from each line, which happens to be the requested URL. In our example
   line, this request URL is `/css/typography.css`.
3. Alphabetically `sort` the list of requested URLs. If some URL has been
   requested `n` times, then after sorting, the file contains the same URL
   repeated `n` times in a row.
4. The `uniq` command filters out repeated lines in its input by checking
   whether two adjacent lines are the same. The `-c` option tells it to also
   output a counter: for every distinct URL, it reports how many times that URL
   appeared in the input.
5. The second `sort` sorts by the number (`-n`) at the start of each line,
   which is the number of times the URL was requested. It then returns the
   results in reverse (`-r`) order, i.e. with the largest number first.
6. Finally, `head` outputs just the first five lines (`-n 5`) of input, and
   discards the rest.

The preceding command line is incredibly powerful. It will process gigabytes of
log files in a matter of seconds, and you can easily modify the analysis to
suit your needs.

- For example, if you want to omit CSS files from the report, change the `awk`
  argument to `$7 !~ /\.css$/ {print $7}`.
- If you want to count top client IP addresses instead of top pages, change the
  `awk` argument to `{print $1}`.

#### Chain of commands versus custom program

You could write a simple program to do the same thing. For example, in Ruby, it
might look something like this:

```rb
counts = Hash.new(0) # 1.
File.open('/var/log/nginx/access.log') do |file|
  file.each do |line|
    url = line.split[6] # 2.
    counts[url] += 1 # 3.
  end
end

top5 = counts.map{|url, count| [count, url] }.sort.reverse[0...5] # 4.
top5.each{|count, url| puts "#{count} #{url}" } # 5.
```

This program is not as concise as the chain of Unix pipes, but it’s fairly
readable, and which of the two you prefer is partly a matter of taste. However,
besides the superficial syntactic differences between the two, there is a big
difference in the execution flow, which becomes apparent if you run this
analysis on a large file.

#### Sorting versus in-memory aggregation

The Ruby script keeps an in-memory hash table of URLs. The Unix pipeline
example does not have such a hash table, but instead relies on sorting a list
of URLs in which multiple occurrences of the same URL are simply repeated.

Which approach is better depends on how many different URLs you have.

If the job’s working set is larger than the available memory, the sorting
approach has the advantage that it can make efficient use of disks. The
principle: chunks of data can be sorted in memory and written out to disk as
segment files, and then multiple sorted segments can be merged into a larger
sorted file. **Mergesort** has sequential access patterns that perform well on
disks.

The `sort` utility in GNU Coreutils (Linux) automatically handles
larger-than-memory datasets by spilling to disk, and automatically parallelizes
sorting across multiple CPU cores. This means that the simple chain of Unix
commands easily scales to large datasets, without running out of memory. The
bottleneck is likely to be the rate at which the input file can be read from
disk.

### The Unix Philosophy

Using a chain of commands to do something complex was one of the key design
ideas of Unix, and it remains astonishingly relevant today.

Doug McIlroy, the inventor of Unix pipes, first described them like this: “We
should have some ways of connecting programs like [a] garden hose — screw in
another segment when it becomes necessary to massage data in another way. This
is the way of I/O also.” The idea of connecting pro grams with pipes became
part of what is now known as the Unix philosophy — a set of design principles:

1. Make each program do one thing well. To do a new job, build afresh rather
   than complicate old programs by adding new “features”.
2. Expect the output of every program to become the input to another, as yet
   unknown, program. Don’t clutter output with extraneous information. Avoid
   stringently columnar or binary input formats. Don’t insist on interactive
   input.
3. Design and build software, even operating systems, to be tried early,
   ideally within weeks. Don’t hesitate to throw away the clumsy parts and
   rebuild them.
4. Use tools in preference to unskilled help to lighten a programming task,
   even if you have to detour to build the tools and expect to throw some of
   them out after you’ve finished using them.

This approach — automation, rapid prototyping, incremental iteration, being
friendly to experimentation, and breaking down large projects into manageable
chunks — sounds remarkably like the Agile and DevOps movements of today.

#### A uniform interface

If you want to be able to connect any program’s output to any program’s input,
that means that all programs must use the same input/output interface.

In Unix, that interface is a file (more precisely, a file descriptor). A file
is just an ordered sequence of bytes. Because that is such a simple interface,
many different things can be represented using the same interface: an actual
file on the filesystem, a communication channel to another process (Unix
`socket`, `stdin`, `stdout`), a device driver (say `/dev/audio` or `/dev/lp0`),
a socket representing a TCP connection, and so on.

By convention, many Unix programs treat this sequence of bytes as ASCII text.

The parsing of each record is more vague. Unix tools commonly split a line into
fields by whitespace or tab characters, but CSV (comma-separated),
pipe-separated, and other encodings are also used.

The uniform interface of ASCII text mostly works, but it’s not exactly
beautiful.

Even databases with the same data model often don’t make it easy to get data
out of one and into the other. This lack of integration leads to Balkanization
of data.

#### Separation of logic and wiring

Another characteristic feature of Unix tools is their use of standard input
(`stdin`) and standard output (`stdout`). If you run a program and don’t
specify anything else, `stdin` comes from the keyboard and `stdout` goes to the
screen.

Separating the input/output wiring from the program logic makes it easier to
compose small tools into bigger systems.

However, there are limits to what you can do with `stdin` and `stdout`.
Programs that need multiple inputs or outputs are possible but tricky. You
can’t pipe a program’s output into a network connection.

- Except by using a separate tool, such as `netcat` or `curl`. Unix started out
  trying to represent everything as files, but the BSD sockets API deviated
  from that convention. The research operating systems Plan 9 and Inferno are
  more consistent in their use of files: they represent a TCP connection as a
  file in `/net/tcp`.

#### Transparency and experimentation

Part of what makes Unix tools so successful is that they make it quite easy to
see what is going on:

- The input files to Unix commands are normally treated as immutable. You can
  run the commands as often as you want, trying various command-line options,
  without damaging the input files.
- You can end the pipeline at any point, pipe the output into `less`, and look
  at it to see if it has the expected form.
- You can write the output of one pipeline stage to a file and use that file as
  input to the next stage. This allows you to restart the later stage without
  rerunning the entire pipeline.

However, the biggest limitation of Unix tools is that they run only on a single
machine — and that’s where tools like Hadoop come in.

## MapReduce and Distributed Filesystems

MapReduce is a bit like Unix tools, but distributed across potentially thousands of machines. Like Unix tools, it is a fairly blunt, brute-force, but surprisingly effective tool. A single MapReduce job is comparable to a single Unix process: it takes one or more inputs and produces one or more outputs.
As with most Unix tools, running a MapReduce job normally does not modify the input and does not have any side effects other than producing the output. The output files are written once, in a sequential fashion (not modifying any existing part of a file once it has been written).
While Unix tools use stdin and stdout as input and output, MapReduce jobs read and write files on a distributed filesystem. In Hadoop’s implementation of Map‐ Reduce, that filesystem is called HDFS (Hadoop Distributed File System), an open source reimplementation of the Google File System (GFS) [19].
Various other distributed filesystems besides HDFS exist, such as GlusterFS and the Quantcast File System (QFS) [20]. Object storage services such as Amazon S3, Azure Blob Storage, and OpenStack Swift [21] are similar in many ways.iv In this chapter we will mostly use HDFS as a running example, but the principles apply to any dis‐ tributed filesystem.
HDFS is based on the shared-nothing principle (see the introduction to Part II), in contrast to the shared-disk approach of Network Attached Storage (NAS) and Storage Area Network (SAN) architectures. Shared-disk storage is implemented by a central‐ ized storage appliance, often using custom hardware and special network infrastruc‐ ture such as Fibre Channel. On the other hand, the shared-nothing approach requires no special hardware, only computers connected by a conventional datacenter net‐ work.
HDFS consists of a daemon process running on each machine, exposing a network service that allows other nodes to access files stored on that machine (assuming that every general-purpose machine in a datacenter has some disks attached to it). A cen‐ tral server called the NameNode keeps track of which file blocks are stored on which machine. Thus, HDFS conceptually creates one big filesystem that can use the space on the disks of all machines running the daemon.
In order to tolerate machine and disk failures, file blocks are replicated on multiple machines. Replication may mean simply several copies of the same data on multiple machines, as in Chapter 5, or an erasure coding scheme such as Reed–Solomon codes, which allows lost data to be recovered with lower storage overhead than full replica‐ tion [20, 22]. The techniques are similar to RAID, which provides redundancy across several disks attached to the same machine; the difference is that in a distributed file‐ system, file access and replication are done over a conventional datacenter network without special hardware.

HDFS has scaled well: at the time of writing, the biggest HDFS deployments run on tens of thousands of machines, with combined storage capacity of hundreds of peta‐ bytes [23]. Such large scale has become viable because the cost of data storage and access on HDFS, using commodity hardware and open source software, is much lower than that of the equivalent capacity on a dedicated storage appliance [24].

### MapReduce Job Execution
