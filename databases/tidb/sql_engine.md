# 分布式 SQL 引擎

- [分布式 SQL 引擎](#分布式-sql-引擎)
  - [如何实现](#如何实现)
    - [在全局有序的分布式 KV 存储之上实现逻辑表](#在全局有序的分布式-kv-存储之上实现逻辑表)
    - [基于 KV 的二级索引设计](#基于-kv-的二级索引设计)
    - [SQL 引擎过程](#sql-引擎过程)
    - [基于成本的优化器](#基于成本的优化器)
    - [主要优化策略](#主要优化策略)
    - [关键算子的分布式化](#关键算子的分布式化)
    - [构建一个 Online DDL 算法](#构建一个-online-ddl-算法)
    - [如何连接到 TiDB-Server](#如何连接到-tidb-server)
    - [从进程角度看 TiDB-Server](#从进程角度看-tidb-server)
    - [从内部结构看 TiDB-Server](#从内部结构看-tidb-server)
    - [其他功能](#其他功能)

## 如何实现

### 在全局有序的分布式 KV 存储之上实现逻辑表

TiVK 的数据 ID 管理：

- 每个表有一个 `TableID`
- 每个索引有一个 `IndexID`
- 每行数据有一个 `RowID` (可以视为主键)

### 基于 KV 的二级索引设计

二级索引也是一个全局有序的 Key-Value map，它的 key 相当于索引的列信息，value
相当于原表的主键。

通过这个主键，在原表的 KV map 进行再一次扫描找到 value，然后按照等位偏移量进行列解析，
这个过程和基于 B-tree 的数据库的回表逻辑类似。

### SQL 引擎过程

- SQL
  - 语法解析
  - 语义解析
  - 权限控制
- AST 抽象语法树
- 逻辑优化
- 物理优化：基于统计信息与成本生成执行计划
- 执行器

### 基于成本的优化器

- Power CBO Optimizer
  - Hash join, Sort merge, Index join, Apply (nested loop)
  - table_reader, table_scan, index_reader, index_scan, index_lookup
  - Steam aggregation, Hash aggregation
- Cost
  - `Cost(p) = N(p) * FN + M(p) * FM + C(p) * FC`
    - N: network cost
    - M: memory cost
    - C: CPU cost
- Task (handle on TiDB or TiKV)
  - corp, root

### 主要优化策略

最大程度让数据在分布式存储层尽快完成过滤及计算：

- 将每个存储节点的用户数据上传到 Server 端进行统一的过滤计算 ❌
- 在节点预先过滤计算，再将结果上传到 Server 端进行一次 SUM 处理
  - 充分利用分布式节点的计算能力 ✅

### 关键算子的分布式化

如 hash join 可以并行、分批处理。

### 构建一个 Online DDL 算法

- 在 TiDB 里没有分表概念，因此 DDL 可以快速完成；
- 把 DDL 分成几个状态，每个状态在多节点之间同步，最终完成完整的 DDL
  - Public
  - Delete-only
  - Write-only

### 如何连接到 TiDB-Server

TiDB-Server 节点的特点：

- 对等
- 无状态
- 可横向扩展
- 支持多点写入
- 可直接承接用户 SQL 入口

### 从进程角度看 TiDB-Server

```graph
[client/Driver]
       ^
       |
 MySQL Protocol
       |
       v
 [TiDB Server] <--> [PD Cluster]
       ^
       |
       V
[Storage Engine]
```

### 从内部结构看 TiDB-Server

```graph
    [MySQL Protocol]
    [TiDB SQL Layer]      (最核心的一层)
  [KV API][DistSQL API]
       [TiClient]
[TiDB Server (Stateless)]
```

### 其他功能

- 前台功能
  - 管理连接和账号权限管理
  - MySQL 协议编码解码
  - 独立的 SQL 执行
  - 库表元信息，以及系统变量
- 后台功能
  - 垃圾回收
  - 执行 DDL
  - 统计信息管理
  - SQL 优化器与执行器
