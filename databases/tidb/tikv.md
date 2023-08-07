# TiKV

- [TiKV](#tikv)
  - [设计目标](#设计目标)
  - [分布式存储系统](#分布式存储系统)
    - [数据结构](#数据结构)
      - [传统 OLTP 系统](#传统-oltp-系统)
      - [TiKV 的数据结构](#tikv-的数据结构)
    - [数据副本的选择算法（共识算法）](#数据副本的选择算法共识算法)
    - [实现扩展](#实现扩展)
      - [分片算法](#分片算法)
      - [Region](#region)
      - [Region 的分裂与扩展](#region-的分裂与扩展)
    - [调度机制](#调度机制)
    - [多版本控制 (MVCC)](#多版本控制-mvcc)
    - [分布式事务模型](#分布式事务模型)
    - [协作处理器 (Coprocessor)](#协作处理器-coprocessor)
    - [分层架构](#分层架构)

## 设计目标

1. 更细粒度的弹性扩缩容
2. 高并发读写
3. 数据不丢不错
4. 多副本保障一致性及高可用
5. 支持分布式事务

## 分布式存储系统

### 数据结构

#### 传统 OLTP 系统

写入是最昂贵的成本。

B-tree 索引必须至少写入两次数据：

1. WAL
2. 写入 B-tree 结构中

- B-tree 缺点：B-tree 是严格的平衡树，对读友好，而写入触发的结点分裂与平衡成本很高；
- 主从架构缺点
  - 集群的写入容量完全由主库的机器配置决定

#### TiKV 的数据结构

LSM-tree: 本质上是一个用空间置换写入延迟，用顺序写入替换随机写入的数据结构。

RocksDB 引擎: 基于 LSM-tree，被 TiKV 采用。

- 支持批量写入 (Atomic Batch Write)
- 无锁快照读
  - 用于数据副本迁移

### 数据副本的选择算法（共识算法）

- Paxos
- Raft: 一种用于代替 Paxos 的共识算法，相对于 Paxos，它的逻辑更清晰、容易理解及工程化实现。
  - 通过先选出 leader 节点、有序日志等方式简化流程、提高效率
  - 通过约束减少不确定的状态空间

TiKV 使用 Raft 算法基于 RocksDB 构建多副本集群。

### 实现扩展

根本技术：数据分片

- 预先分片（静态）：传统偏好，主要解决表容量问题，而不能解决细粒度的弹性问题
- 自动分片（动态）

#### 分片算法

- 哈希 Hash
- 范围 Range (TiKV)
  - 可以高效地扫描连续的数据记录，OLTP 场景常用（hash 和 list 的数据是分散的，扫描的 I/O
    成本更高）
  - 可以简单地实现自动分裂与合并
  - 弹性优先，分片可以自由地调度
- 列举 List

#### Region

在 TiKV 节点中将整个 Key-Value 空间（全局有序 Map）分成若干段，每一段都是连续的
Key-Value。

每一个段就称为一个 Region，也就是数据分片的单元，每个 Region 可以使用
`[StartKey, EndKey)`  来描述。

数据的存储、访问、复制、调度都是以 Region 为单位。

#### Region 的分裂与扩展

确保各个 Region 的大小是大致接近的：

- 当某个 Region 的大小超过一定限制，TiKV 会将它分裂为两个或更多的 Region；
- 当某个 Region 因为大量删除而变得很小时，TiKV 会将相邻的两个小的 Region 合并；

### 调度机制

- 分片数量、Leader、吞吐量自动平衡
- 自定义调度接口
  - 支持跨 IDC 表级同时写入

### 多版本控制 (MVCC)

TiKV 的 MVCC 实现是通过在 Key 后面添加版本号来实现。
有了 MVCC 后，TiKV 得以实现并发控制，实现 SI 的隔离级别、事务支持以及历史数据恢复等功能。

### 分布式事务模型

- **去中心化**的两阶段提交
  - 通过 PD 全局授时 (TSO)
  - ~4M timestamp 每秒
  - 每个 TiKV 节点分配单独区域存放锁信息 (CF Lock)
- 在 Google Percolator 事务模型基础上优化改进
- TiKV 支持完整事务 KV API
- 默认乐观事务模型
  - 支持悲观事务模型
- 默认隔离级别：Snapshot Isolation

### 协作处理器 (Coprocessor)

每个 TiKV 节点中都有一个协作处理器，用于读取并计算数据。

### 分层架构

```graph
| [TiKV API] [Coprocessor API] |            | [TiKV API] [Coprocessor API] |
|                              |            |                              |
|        [Transaction]         |            |        [Transaction]         |
|                              |            |                              |
|           [Raft]             > Raft Group <           [Raft]             |
|                              |            |                              |
|         [RocksDB]            |            |         [RocksDB]            |
```
