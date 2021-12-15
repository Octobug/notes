# 从 C10K 问题到高并发服务器开发

## 目录

- [从 C10K 问题到高并发服务器开发](#从-c10k-问题到高并发服务器开发)
  - [目录](#目录)
  - [1. C10K 问题](#1-c10k-问题)
    - [C10K 的意思](#c10k-的意思)
    - [背景](#背景)
    - [处理请求与连接的区别](#处理请求与连接的区别)
    - [I/O 策略](#io-策略)
      - [非阻塞I/O (`write` with `O_NONBLOCK`) 与异步I/O (`aio_write`) 的区别](#非阻塞io-write-with-o_nonblock-与异步io-aio_write-的区别)
    - [每个线程处理多个客户端，并使用非阻塞I/O和水平触发就绪通知](#每个线程处理多个客户端并使用非阻塞io和水平触发就绪通知)
    - [就绪通知与完成通知](#就绪通知与完成通知)
    - [非阻塞 I/O 与异步 I/O](#非阻塞-io-与异步-io)
    - [设计模式: 应答者 `Reactor` 与 `Proactor`](#设计模式-应答者-reactor-与-proactor)
    - [如何设计](#如何设计)
    - [水平触发 (level-triggered) 与边缘触发 (edge-triggered)](#水平触发-level-triggered-与边缘触发-edge-triggered)
    - [多进程/多线程/协程](#多进程多线程协程)
    - [应用层](#应用层)
  - [2. 底层机制](#2-底层机制)
  - [3. 如何写一个高性能服务器](#3-如何写一个高性能服务器)
    - [网络模型层次的划分设计](#网络模型层次的划分设计)
  - [4. 现状](#4-现状)
    - [业界哪些做得好](#业界哪些做得好)

## 1. C10K 问题

原文: <http://www.kegel.com/c10k.html>

### C10K 的意思

单机并发处理 10,000 (10K) 个客户端（Clients, 有些文章使用 "Connections" 即“连接”一词）。

### 背景

[Dan Kegel](http://www.kegel.com/resume.html) (`/dæn 'keɡəl/`) 在 1999 年提出了
C10K 问题。

![Dan Kegel](./images/dan_kegel0.png)

![Dan Kegel](./images/dan_kegel1.jpg)

那个年代的计算机硬件性能远不及今天，但主要的短板不在于硬件。当时的服务器软件在同时面对超过
10,000 个客户端时，即使硬件性能足够强大也无法正常提供服务。

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

>>>>> progress

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

## 4. 现状

c10m became reality in 2010s.

### 业界哪些做得好
