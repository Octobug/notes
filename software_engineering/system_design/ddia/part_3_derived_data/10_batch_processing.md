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

If you expect the output of one program to become the input to another program, that means those programs must use the same data format—in other words, a com‐ patible interface. If you want to be able to connect any program’s output to any pro‐ gram’s input, that means that all programs must use the same input/output interface.
In Unix, that interface is a file (or, more precisely, a file descriptor). A file is just an ordered sequence of bytes. Because that is such a simple interface, many different things can be represented using the same interface: an actual file on the filesystem, a communication channel to another process (Unix socket, stdin, stdout), a device driver (say /dev/audio or /dev/lp0), a socket representing a TCP connection, and so on. It’s easy to take this for granted, but it’s actually quite remarkable that these very different things can share a uniform interface, so they can easily be plugged together.ii
By convention, many (but not all) Unix programs treat this sequence of bytes as ASCII text. Our log analysis example used this fact: awk, sort, uniq, and head all treat their input file as a list of records separated by the \n (newline, ASCII 0x0A) charac‐ ter. The choice of \n is arbitrary—arguably, the ASCII record separator 0x1E would have been a better choice, since it’s intended for this purpose [14]—but in any case, the fact that all these programs have standardized on using the same record separator allows them to interoperate.

The parsing of each record (i.e., a line of input) is more vague. Unix tools commonly split a line into fields by whitespace or tab characters, but CSV (comma-separated), pipe-separated, and other encodings are also used. Even a fairly simple tool like xargs has half a dozen command-line options for specifying how its input should be parsed.
The uniform interface of ASCII text mostly works, but it’s not exactly beautiful: our log analysis example used {print $7} to extract the URL, which is not very readable. In an ideal world this could have perhaps been {print $request_url} or something of that sort. We will return to this idea later.
Although it’s not perfect, even decades later, the uniform interface of Unix is still something remarkable. Not many pieces of software interoperate and compose as well as Unix tools do: you can’t easily pipe the contents of your email account and your online shopping history through a custom analysis tool into a spreadsheet and post the results to a social network or a wiki. Today it’s an exception, not the norm, to have programs that work together as smoothly as Unix tools do.
Even databases with the same data model often don’t make it easy to get data out of one and into the other. This lack of integration leads to Balkanization of data.

#### Separation of logic and wiring
