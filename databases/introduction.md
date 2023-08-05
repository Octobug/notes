# 数据库系统概述

- [数据库系统概述](#数据库系统概述)
  - [数据库系统发展简史](#数据库系统发展简史)
  - [数据库技术发展内在驱动](#数据库技术发展内在驱动)
    - [业务发展](#业务发展)
      - [数据（容量）架构演进](#数据容量架构演进)
    - [场景创新](#场景创新)
      - [数据模型与交互效率的演进](#数据模型与交互效率的演进)
    - [硬件与云计算的发展](#硬件与云计算的发展)

## 数据库系统发展简史

- 1980 年代：商业 RDBMS
- 1990 年代：开源 RDBMS
- 2000 互联网
  - 谷歌三驾马车开启大数据时代
    - GFS
    - Bigtable
    - Mapreduce
  - NoSQL
    - Hadoop
    - Redis
    - MongoDB
- 2010 移动互联网：NewSQL（集成分布式技术 + 关系模型）
  - Spanner
  - TiDB
- 2020 云计算时代：HTAP
  - TiDB

## 数据库技术发展内在驱动

### 业务发展

- 数据存储量
- 吞吐量
- 读写 QPS

#### 数据（容量）架构演进

- 单节点
- 共享状态 (Scale up)
- 分布式 (Scale out)

### 场景创新

- 查询语言
- 计算模型
- 数据模型
- 读写延时

#### 数据模型与交互效率的演进

- 标准 SQL 语言
  - 支持 ACID 事务 (OLTP, On-Line Transaction Processing)
    - Atomicity 原子性
    - Consistency 一致性
    - Isolation 隔离性
    - Durability 持久性
  - 结构化存储
- NoSQL (Not Only SQL)
  - 非结构化数据
    - Key-value
    - 文本
    - 图
    - 时序数据
    - 地理信息
  - 缺点：不支持事务
- NewSQL
  - 兼容数据模型的可扩展需求
  - 支持 ACID 事务
- HTAP (HybridTransactional/Analytical Processing)

### 硬件与云计算的发展

- 读写分离
- 一体机
- 云原生
