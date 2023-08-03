# Software Architecture

- [Software Architecture](#software-architecture)
  - [架构设计](#架构设计)
    - [进程 vs. 线程](#进程-vs-线程)
      - [粒度选择](#粒度选择)
    - [进程划分](#进程划分)
      - [以业务逻辑为单元](#以业务逻辑为单元)
    - [进程间通信 (IPC)](#进程间通信-ipc)
    - [使用线程](#使用线程)

> <https://en.wikipedia.org/wiki/Software_architecture>

## 架构设计

### 进程 vs. 线程

#### 粒度选择

- 全部进程：性能糟糕
- 全部线程：健壮性差

### 进程划分

#### 以业务逻辑为单元

- 健壮性
- 分布式
- 跨编程语言

### 进程间通信 (IPC)

- Socket
- 共享内存
- 管道
- 文件

### 使用线程

- 性能优于进程
