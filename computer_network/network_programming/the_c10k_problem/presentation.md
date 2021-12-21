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

## 3. Demo: 简易 HTTP Server

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

Dan Kegel (`/dæn 'keɡəl/`) 于 1999 年在其[个人站点](http://www.kegel.com/resume.html)提出了 [C10K 问题](http://www.kegel.com/c10k.html)。

![Dan Kegel](./images/dan_kegel.jpeg)

---

> You can buy a 1000MHz machine with 2 gigabytes of RAM and an 1000Mbit/sec Ethernet card for $1200 or so. Let's see - at 20000 clients, that's 50KHz, 100Kbytes, and 50Kbits/sec per client. It shouldn't take any more horsepower than that to take four kilobytes from the disk and send them to the network once a second for each of twenty thousand clients. (That works out to $0.08 per client, by the way. Those $100/client licensing fees some operating systems charge are starting to look a little heavy!) So `hardware is no longer the bottleneck`.

---

### 1999 年互联网用户数

<!-- class: invert lead -->

![width:720px](images/internet_users.png)

<https://ourworldindata.org/internet>

---

> Here are a few notes on how to **configure operating systems** and **write code** to support thousands of clients

---

### 处理请求与连接的区别

- 大量请求：需要高吞吐率，更关心每个请求的处理速度
- 大量连接：需要高效的连接调度

### I/O 策略

#### 非阻塞I/O (`write` with `O_NONBLOCK`) 与异步I/O (`aio_write`) 的区别

- 是否以及如何在单个线程中发起多个I/O调用
  - 否；并彻底使用阻塞/同步调用，以多进程或多线程实现并发
  - 使用非阻塞I/O与就绪通知（适用于网络I/O）
  - 使用异步I/O与完成通知（适用于网络与磁盘I/O）
- 如何管理每一个客户端
  - 一个进程处理一个客户端 (经典 UNIX 方法 (1980前后开始))
  - 一个系统级线程处理多个客户端，每个客户端可以由以下几种方式控制
    - 一个用户级线程
    - 一个状态机（线程是为不懂状态机的人准备的）
    - Continuation 机制
  - 一个系统级线程处理一个客户端
  - 一个系统级线程处理一个活跃客户端
- 使用标准的系统服务或者改造内核

使用上面的策略可以组合出以下五种流行方案。

### 每个线程处理多个客户端，并使用非阻塞I/O和水平触发就绪通知

### 就绪通知与完成通知

### 非阻塞 I/O 与异步 I/O

[怎样理解阻塞非阻塞与同步异步的区别？ - 萧萧的回答](https://www.zhihu.com/question/19732473/answer/241673170)

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

## 3. Demo: 简易 HTTP Server

---

## 4. 了解 NGINX 架构

---

## 4. 了解 NGINX 架构

c10m became reality in 2010s.

---

## 5. 参考资料

<!-- class: invert -->

### 文章

- [The C10K Problem](http://www.kegel.com/c10k.html) by Dan Kegel
- [C10K问题系列文章](http://www.52im.net/thread-561-1-1.html) (即时通讯网)

---

### 书籍

- [Operating Systems: Three Easy Pieces](http://www.ostep.org/) by Remzi H. Arpaci-Dusseau Andrea C Arpaci-Dusseau (2018)
- [UNIX Network Programming](http://www.unpbook.com/), Volume 1: The Sockets Networking API, 3rd Edition by W. Richard Stevens, Bill Fenner, Andrew M. Rudoff (2003)
