---
marp: true
theme: gaia
class: invert

---

<!-- class: lead invert -->

# 从 C10K 问题到高并发服务器开发

`2021.12.24`

---

<!-- class: invert -->

## 1. The C10K Problem

## 2. 并发策略

## 3. Demo: 简陋 HTTP Server

## 4. 了解 NGINX 架构

## 5. 参考资料

---

<!-- class: invert lead -->

## 1. The C10K Problem

---

<!-- class: invert -->

## 1. The C10K Problem

### 1.1 "C10K"?

单机并发处理 10,000 (10K) 个客户端 (C 代表 Clients, 有些文章使用 "Connections" 一词)。

---

<!-- class: invert -->

### 1.2 背景

Dan Kegel (`/dæn 'keɡəl/`) 于 1999 年在其 [个人站点](http://www.kegel.com) 提出了 [C10K 问题](http://www.kegel.com/c10k.html)。

![height:360px](./images/dan_kegel.jpeg)

---

### 1999 年互联网用户数

<!-- class: invert lead -->

![width:720px](images/internet_users.png)

<https://ourworldindata.org/internet>

---

> You can buy a 1000MHz machine with 2 gigabytes of RAM and an 1000Mbit/sec Ethernet card for $1200 or so. Let's see - at 20000 clients, that's 50KHz, 100Kbytes, and 50Kbits/sec per client. It shouldn't take any more horsepower than that to take four kilobytes from the disk and send them to the network once a second for each of twenty thousand clients. (That works out to $0.08 per client, by the way. Those $100/client licensing fees some operating systems charge are starting to look a little heavy!) So `hardware is no longer the bottleneck`.

---

<!-- class: invert -->

### 处理“请求”与“连接”的区别

- 大量请求：需要高吞吐率，更关心每个请求的处理速度
- 大量连接：无论连接上的数据交互繁忙与否都需要高效的网络连接管理

---

<!-- class: lead invert -->

### S0 服务

![height:480px](images/s0.jpg)

---

<!-- class: invert -->

> 早期的腾讯QQ也同样面临 C10K 问题，只不过他们是用了 UDP 这种原始的包交换协议来实现的，绕开了这个难题，当然过程肯定是痛苦的。

在 2000 年前后一段时间，C10K 是实实在在的难题。

Dan Kegel 对这个问题进行系统的归纳和总结，并提出解决方案。

---

<!-- class: invert -->

### 1.3 主要内容

> Here are a few notes on how to **configure operating systems** and **write code** to support thousands of clients.

-> *The C10K Problem (pdf)*

---

<!-- class: lead invert -->

# 先体验一下网站不响应的感觉

## Django `runserver`

---

<!-- class: invert lead -->

## 2. 并发策略 & 3. Demo: 简陋 HTTP Server

---

## 先实现一个低并发 HTTP Server

`demo`

---

<!-- class: invert -->

## 3. Demo: 简陋 HTTP Server

### 3.1 单进程(线程) HTTP Server 实现

1. 监听本地地址并接收 TCP 连接
2. 按照 HTTP 协议解析请求字节流
3. 实现业务
4. 按照 HTTP 协议返回字节流
5. 关闭 TCP 连接

---

<!-- class: lead invert -->

#### 操作系统维护的两个 TCP 队列

![height:540px](images/tcp_queues.png)

---

<!-- class: lead invert -->

#### 传输层及以下由操作系统管理

![height:540px](images/osi_ips_layers.png)

---

<!-- class: invert -->

## 2. 并发策略

### 2.1 从 I/O 角度: 是否在单个进程/线程内处理多个客户端

1. 进程/线程内只处理一个客户端，并完全使用阻塞/同步调用，结合多进程或多线程实现并发；
2. 使用非阻塞调用启动 I/O，结合就绪通知 (如 `poll()`) 来进行后续操作，通常只能用于网络 I/O；
3. 使用异步调用 (如 `aio_write()`) 启动 I/O，结合完成通知 (如信号 (`signals`), [IOCP](https://en.wikipedia.org/wiki/Input/output_completion_port) ) 来进行后续操作，可用于网络 I/O 与磁盘 I/O。

---

### 2.2 从进程/线程角度: 用什么执行单元去处理客户端

- 每个进程处理一个客户端（经典 Unix 做法，始于 1980 年）
- 每个系统级 (OS-level) 线程处理多个客户端，每个客户端使用如下方式处理
  - 用户级 (user-level) 线程
  - 状态机 (state machine)
  - [Continuation](https://en.wikipedia.org/wiki/Continuation)
- 每个系统级线程处理一个客户端 (Java 原生多线程)
- 每个系统级线程处理一个活跃客户端 (IOCP, 线程池)

---

### 2.3 从操作系统角度: 是否要使用标准系统服务？魔改内核？自己写驱动？

---

### 2.4 几种组合方案

1. **每个线程服务多个客户端，并使用非阻塞和水平触发 (level-triggered) 就绪通知**
2. **每个线程服务多个客户端，并使用非阻塞和边沿触发 (edge-triggered) 就绪通知**
3. **每个线程服务多个客户端，并使用异步 I/O**
4. **每个线程服务单个客户端，并使用阻塞 I/O**
5. **把服务器做到操作系统内核**
6. 把 TCP 协议栈带到用户空间

---

## 3. Demo: 简陋 HTTP Server

### 3.2 同步+阻塞的多进程 vs. 多线程

`demo`

---

<https://en.wikipedia.org/wiki/Linux_kernel_version_history>

---

### 每个线程处理多个客户端，并使用非阻塞I/O和水平触发就绪通知

### 就绪通知与完成通知

### 设计模式: 应答者 `Reactor` 与 `Proactor`

- [高性能IO模型分析-IO模型简介（一）](https://zhuanlan.zhihu.com/p/95550964)
- [高性能IO模型分析-Reactor模式和Proactor模式（二）](https://zhuanlan.zhihu.com/p/95662364)
- [高性能IO模型分析-浅析Select、Poll、Epoll机制（三）](https://zhuanlan.zhihu.com/p/95872805)

### 如何设计

Fast UNIX Servers - 核心设计原则

### 水平触发 (level-triggered) 与边缘触发 (edge-triggered)

### 多进程/多线程/协程

- 并发问题 (ostep concurrency)
- Multi-processing capabilities
- Memory management
- I/O management

- poll
  - `poll` can achieve O(1)

    [Benchmarking BSD and Linux - The connect latency benchmark](benchmarking_bsd_and_linux.md#the-connect-latency-benchmark)
- Nodejs 的事件循环

### 内核级线程 / 用户级线程

### 1:1 threading vs. M:N threading

### Map-Reduce?

### 应用层

## 2. 底层机制

## 3. 如何写一个高性能服务器

- UNP Introduction
  - 迭代式（iterative）服务器: 基于循环一次一个
  - multi-process: 按需开启多子进程/预设子进程
  - multi-thread: 按需开启多线程/预设子线程
- 不同系统调用性能差异 `poll`, `select`, `kqueue`, `epoll`

### 网络模型层次的划分设计

UNP: 1.7

---

## 2. 并发策略

---

## 3. Demo: 简陋 HTTP Server

---

## 4. 了解 NGINX 架构

c10m became reality in 2010s.

---

## 5. 参考资料

<!-- class: invert -->

### 文章

- [The C10K Problem](http://www.kegel.com/c10k.html) by Dan Kegel
- [C10k problem](https://en.wikipedia.org/wiki/C10k_problem) (Wikipedia)
- [C10K问题系列文章](http://www.52im.net/thread-561-1-1.html) (JackJiang, 即时通讯网)

---

### 书籍

- [Operating Systems: Three Easy Pieces](http://www.ostep.org/) by Remzi H. Arpaci-Dusseau Andrea C Arpaci-Dusseau (2018)
- [UNIX Network Programming](http://www.unpbook.com/), Volume 1: The Sockets Networking API, 3rd Edition by W. Richard Stevens, Bill Fenner, Andrew M. Rudoff (2003)
