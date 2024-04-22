# Performance

- [Performance](#performance)
  - [Best practices for MySQL performance optimization and MySQL use indexes](#best-practices-for-mysql-performance-optimization-and-mysql-use-indexes)
  - [读写分离 Read-Write Separation](#读写分离-read-write-separation)
  - [Partition Maintenance in MySQL](#partition-maintenance-in-mysql)
  - [Sharding 分库分表](#sharding-分库分表)
    - [垂直](#垂直)
    - [水平](#水平)
    - [常用中间件](#常用中间件)

## Best practices for MySQL performance optimization and MySQL use indexes

> <https://pankajconnect.medium.com/best-practices-for-mysql-performance-optimization-and-mysql-use-indexes-cd3dda51b8b0>

## 读写分离 Read-Write Separation

- 主从同步：binlog
- 读多写少
  - 主库：写
    - `show master status`
  - 从库：读
    - `show master status\G`
    - I/O Thread: 拷贝 binlog
    - SQL Thread: 读取 binlog 重放
- 强制路由
  - 由于主从同步延迟，会导致读从库时不能读到最新数据
  - 方式一：注解
    - atlas: `/*master*/ select * from table ...`

## Partition Maintenance in MySQL

> <http://mysql.rjweb.org/doc.php/partitionmaint>

## Sharding 分库分表

数据水平/垂直切分到不同的数据库实例中。

### 垂直

- 分库：按业务、数据规模将不同表分到各自的数据库里。
- 分表：将访问频率不同的字段分开成不同的表。

优点：

- 拆分后业务清晰
- 数据维护简单

缺点：

- 如果单表数据量大，读写压力依然很大
- 部分业务无法直接 join，要在应用层做关联

### 水平

优点：

- 单表/单库的数据量可控
- 切分的表结构相同，应用层改动少
- 提高系统的稳定性和负载能力

缺点：

- 扩容较难
  - 取模：模数变化时，需要迁移数据
- 拆分规则难以抽象
- 部分业务难以 join
- 分布式事务
- 分布式全局唯一 ID

### 常用中间件

- 应用层：性能比代理层好，可以跨数据库
- 代理层：跨语言能力突出
  - Mycat：已经逐渐衰落
  - Atlas：已经逐渐衰落
  - MySQL-Proxy
- ShardingSphere
