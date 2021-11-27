# Fast UNIX Servers

> <https://nick-black.com/dankwiki/index.php/Fast_UNIX_Servers>
>
> Author: Nick Black
>
> Snapshotted on 2021-11-27

"I love the smell of 10GbE in the morning. Smells like...victory." -
W. Richard Stevens, "Secret Teachings of the UNIX Environment"

Dan Kegel's classic site "[The C10K Problem](http://www.kegel.com/c10k.html)"
(still updated from time to time) put a Promethean order to the arcana of
years, with Jeff Darcy's "[High-Performance Server Architecture](http://pl.atyp.us/content/tech/servers.html)"
adding to our understanding. I'm collecting here some followup material to
these excellent works (and of course the books of W. Richard Stevens, whose
torch we merely carry). Some of these techniques have found, or will find,
their way into [libtorque](https://nick-black.com/dankwiki/index.php?title=Libtorque),
my multithreaded event unification library (and master's thesis).

*FIXME* as of 2019, I need update this with information on [DPDK](https://nick-black.com/dankwiki/index.php?title=DPDK)
and [eBPF](https://nick-black.com/dankwiki/index.php?title=EBPF)/[XDP](https://nick-black.com/dankwiki/index.php?title=XDP)
at a minimum.

> Table of Contents

- [Fast UNIX Servers](#fast-unix-servers)
  - [Central Design Principles](#central-design-principles)
  - [Queueing Theory](#queueing-theory)
  - [Event Cores](#event-cores)
    - [Edge and Level Triggering](#edge-and-level-triggering)
  - [A Garden of Interfaces](#a-garden-of-interfaces)
  - [The Full Monty: A Theory of UNIX Servers](#the-full-monty-a-theory-of-unix-servers)
  - [DoS Prevention or, Maximizing Useful Service](#dos-prevention-or-maximizing-useful-service)
  - [The Little Things](#the-little-things)
    - [Hardware Esoterica](#hardware-esoterica)
    - [Operating System Esoterica](#operating-system-esoterica)
    - [Tuning for the Network](#tuning-for-the-network)
    - [Power Consumption](#power-consumption)
  - [See Also](#see-also)

## Central Design Principles

Varghese's [*Network Algorithmics: An Interdisciplinary Approach to Designing
Fast Networked Devices*](http://www.amazon.com/Network-Algorithmics-Interdisciplinary-Designing-Networking/dp/0120884771)
is in a league of its own in this regard.

- Principle 1: **Exploit all cycles/bandwidth.** Avoid blocking I/O and
  unnecessary evictions of cache, but prefetch into cache where appropriate
  (this applies to page caches just as much as processor caches or any other
  layer of the [memory hierarchy](https://nick-black.com/dankwiki/index.php?title=Architecture#Memory_Hierarchies)).
  Be prepared to exploit multiple processing elements. Properly align data and
  avoid cache-aliasing effects. Use jumbo frames in appropriate scenarios and
  proactively warn on network degradation (e.g., half-duplex Ethernet due to
  failed link negotiation).
- Principle 2: **Don't duplicate work.** Avoid unnecessary copies, context
  switches, system calls and signals. Use double-buffering or ringbuffers, and
  calls like [Linux's](https://nick-black.com/dankwiki/index.php?title=Linux_APIs)
  `splice(2)`.
- Principle 3: **Measure, measure, and measure again, preferably
  automatically.** Hardware, software and networks will all surprise you.
  Become friends with your hardware's [performance counters](https://nick-black.com/dankwiki/index.php?title=Performance_Counters)
  and tools like [eBPF](https://nick-black.com/dankwiki/index.php?title=EBPF),
  dtrace, ktrace, etc. Build explicit support for performance analysis into the
  application, especially domain-specific statistics.

  "I thought of another moral, more down to earth and concrete, and I believe
  that every militant chemist can confirm it: that one must distrust the
  almost-the-same (sodium is almost the same as potassium, but with sodium
  nothing would have happened), the practically identical, the approximate, all
  surrogates, and all patchwork. The differences can be small, but they can
  lead to radically different consequences, like a railroad's switch points:
  the chemist's trade consists in good part of being aware of these
  differences, knowing them close up and foreseeing their effects. And not only
  the chemist's trade." - Primo Levi, *The Periodic Table*

## Queueing Theory

- "[Introduction to Queueing](http://staff.um.edu.mt/jskl1/simweb/intro.htm"
- [Little's Law](http://en.wikipedia.org/wiki/Little's_law) (L = λW)
- Leonard Kleinrock's peerless *Queueing Systems*
  (Volume 1: [Theory](http://www.amazon.com/Queueing-Systems-Theory-Leonard-Kleinrock/dp/0471491101),
  Volume 2: [Computer Applications](http://www.amazon.com/Computer-Applications-2-Queueing-Systems/dp/047149111X))

## Event Cores

>>>>> progress

- as of Linux 5, [`io_uring`](https://nick-black.com/dankwiki/index.php?title=Io_uring&action=edit&redlink=1)
  is the only game in town on Linux
- [epoll](https://nick-black.com/dankwiki/index.php?title=Epoll) on
  [Linux](https://nick-black.com/dankwiki/index.php?title=Linux_APIs),
  `/dev/poll` on Solaris,
  [kqueue](https://nick-black.com/dankwiki/index.php?title=Kqueue) on
  [FreeBSD](https://nick-black.com/dankwiki/index.php?title=FreeBSD_APIs)
- [I/O Completion Ports](http://msdn.microsoft.com/en-us/library/aa365198%28VS.85%29.aspx)
  on Win32, [Event Completion Framework](http://developers.sun.com/solaris/articles/event_completion.html)
  on Solaris 10, POSIX.1b asynchronous I/O
- [liboop](http://liboop.ofb.net/),
  [libev](http://software.schmorp.de/pkg/libev.html) and
  [libevent](http://www.monkey.org/~provos/libevent/)
- Ulrich Drepper's "[The Need for Aynchronous, ZeroCopy Network I/O](http://people.redhat.com/drepper/newni-slides.pdf)"
  - If nothing else, Drepper's plans tend to
    [become sudden and crushing realities](http://sources.redhat.com/ml/libc-alpha/2002-01/msg00367.html)
    in the [glibc](https://nick-black.com/dankwiki/index.php?title=Glibc) world
- In a [flywheel design](https://nick-black.com/dankwiki/index.php?title=Libtorque),
  maximizing topological locality of the event set becomes the hinge on which
  manycore efficiency turns
  - **FIXME defend** this is a hypothesis and an active [research area](https://nick-black.com/dankwiki/index.php?title=Libtorque)
    of mine

### Edge and Level Triggering

## A Garden of Interfaces

## The Full Monty: A Theory of UNIX Servers

## DoS Prevention or, Maximizing Useful Service

## The Little Things

### Hardware Esoterica

### Operating System Esoterica

### Tuning for the Network

### Power Consumption

## See Also
