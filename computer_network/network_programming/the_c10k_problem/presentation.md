# The C10K problem

## 什么是 c10k 问题

### 处理连接与请求的区别

#### 并行处理多各连接

- Handling many requests per second requires high throughput (processing them
  quickly.
- Handling many requests per second is concerned with the speed of handling
  requests.

#### 并行/并发处理多个请求

- A high number of concurrent connections requires efficient scheduling of
connections.
- A system capable of handling a high number of concurrent connections does not
  necessarily have to be a fast system, only one where each request will
  deterministically return a response within a (not necessarily fixed) finite
  amount of time.

## 是什么造成了这个问题

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
