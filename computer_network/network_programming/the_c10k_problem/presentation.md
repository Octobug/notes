# 从 C10K 问题到高并发服务器开发

## 目录

- [从 C10K 问题到高并发服务器开发](#从-c10k-问题到高并发服务器开发)
  - [目录](#目录)
  - [C10K 问题](#c10k-问题)
    - [C10K 的意思](#c10k-的意思)
    - [背景](#背景)
    - [处理请求与连接的区别](#处理请求与连接的区别)
    - [非阻塞 I/O 与异步 I/O](#非阻塞-io-与异步-io)
    - [网络模型层次的划分设计](#网络模型层次的划分设计)
    - [操作系统层](#操作系统层)
    - [应用层](#应用层)
  - [现状](#现状)
  - [如何解决](#如何解决)
    - [业界哪些做得好](#业界哪些做得好)
    - [如何设计](#如何设计)
    - [如何写一个高性能服务器](#如何写一个高性能服务器)

## C10K 问题

原文: <http://www.kegel.com/c10k.html>

### C10K 的意思

单机并发处理 10,000 (10K) 个客户端（Clients, 有些文章使用 "Connections" 即“连接”一词）。

### 背景

[Dan Kegel](http://www.kegel.com/resume.html) (`/dæn 'keɡəl/`) 在 1999 年提出了
C10K 问题。

![Dan Kegel](./images/dan_kegel0.png)

![Dan Kegel](./images/dan_kegel1.jpg)

那个年代的计算机硬件性能当然无法和当今的相比，问题在于即使硬件性能足够强大，
当一台服务器同时面对超过 10,000 个客户端时，它依然无法正常提供服务。

### 处理请求与连接的区别

- 大量请求：需要高吞吐率，更关心每个请求的处理速度
- 大量连接：需要高效的连接调度

### 非阻塞 I/O 与异步 I/O

怎样理解阻塞非阻塞与同步异步的区别？ - 萧萧的回答 - 知乎

<https://www.zhihu.com/question/19732473/answer/241673170>

### 网络模型层次的划分设计

UNP: 1.7

### 操作系统层

- 并发问题 (ostep concurrency)
- Multi-processing capabilities
- Memory management
- I/O management

- poll
  - `poll` can achieve O(1)

    [Benchmarking BSD and Linux - The connect latency benchmark](benchmarking_bsd_and_linux.md#the-connect-latency-benchmark)
- Nodejs 的事件循环

### 应用层

## 现状

c10m became reality in 2010s.

## 如何解决

### 业界哪些做得好

### 如何设计

Fast UNIX Servers - 核心设计原则

- 水平触发 (level-triggered)
- 边缘触发 (edge-triggered)

### 如何写一个高性能服务器

- UNP Introduction
  - 迭代式（iterative）服务器: 基于循环一次一个
  - multi-process: 按需开启多子进程/预设子进程
  - multi-thread: 按需开启多线程/预设子线程
- 不同系统调用性能差异 `poll`, `select`, `kqueue`, `epoll`
