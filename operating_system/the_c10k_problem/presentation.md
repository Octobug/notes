# The C10K problem

## 什么是 c10k 问题

### 相关问题

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

### 操作系统层

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

## 解决方案

### 业界是如何解决的

### 如何写一个高性能服务器
