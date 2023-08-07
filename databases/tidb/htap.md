# 基于分布式数据库的 HTAP 数据服务

- [基于分布式数据库的 HTAP 数据服务](#基于分布式数据库的-htap-数据服务)
  - [概念](#概念)
  - [列式引擎 TiFlash](#列式引擎-tiflash)
    - [物理隔离](#物理隔离)
    - [行列数据同步](#行列数据同步)
  - [HTAP 之路](#htap-之路)

## 概念

HTAP = OLAP + OLTP

- Hybrid Transactional/Analytical Processing
- OnLine Analytical Processing
- OnLine Transactional Processing

数据容量使 OLAP 与 OLTP 的分道扬镳：

- OLTP 狭义的数据库
- OLAP 狭义的大数据

业务需要又使 OLAP 与 OLTP 边界变得模糊：数据与服务的统一。

## 列式引擎 TiFlash

### 物理隔离

列存天然对 OLAP 查询友好。

### 行列数据同步

TiFlash 以 Raft Learner 方式接入 Multi-Raft 组，使用异步方式传输数据，对 TiKV 产生非常小的负担。

当数据同步到 TiFlash 是，会被从行格式拆解为列格式。

## HTAP 之路

1. 分布式数据库是在大数据规模下提供 HTAP 的基础
2. TiDB-Server 最大程度下推算法与 Hash Join 关键算子提供了基础 AP 能力
3. 借助生态，让 Spark 运行在 TiKV 之上
4. 行列混合引擎，列式引擎提供实时写入能力
5. 行列引擎采取 Raft-Base replication，解决数据同步效率的问题
6. TiDB-Server 统一技术服务
7. MPP 算法解决技术节点的扩展性与并行计算
