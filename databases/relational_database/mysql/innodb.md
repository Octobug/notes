# InnoDB

- [InnoDB](#innodb)
  - [B+ Tree](#b-tree)
    - [在文件系统的存储读写单位：页 (page)](#在文件系统的存储读写单位页-page)
    - [用户数据区](#用户数据区)
    - [页目录](#页目录)
    - [主键索引](#主键索引)
    - [查找方式](#查找方式)
    - [联合索引](#联合索引)
  - [Buffer Pool](#buffer-pool)
  - [Redo log](#redo-log)
  - [Binlog](#binlog)
  - [Undo log](#undo-log)
  - [事务](#事务)
    - [MVCC (多版本并发控制)](#mvcc-多版本并发控制)

## B+ Tree

> <https://www.cs.usfca.edu/~galles/visualization/BPlusTree.html>

特点：

1. 有序
2. 结点可以有多个元素
3. 叶子结点有**双向**指针顺序串联
4. 非叶子结点有数据冗余

### 在文件系统的存储读写单位：页 (page)

```sql
show global status like 'innodb_page_size';
-- 16384 / 1024 = 16KB
```

- 页结点存储下一层结点的页地址，每一个“指针”大小为 6 B
- `.frm` 文件：存储表结构信息
  - InnoDB：主键索引叶子结点会存储完整数据行（聚集索引）
    - `.ibd`: 数据和索引文件
  - MyISAM：索引只存储数据页地址（非聚集索引，相当于要回表）
    - `.MYD`: data
    - `.MYI`: index

### 用户数据区

即真正存储业务数据的区域

### 页目录

- 用户数据条目是分组的
- 页目录条目存储每一个组的用户数据条目最小的主键，并且有指针指向该用户数据条目
- 页内查找数据时，先按页目录查找，再查找对应的用户数据组
- 可以结合二分查找，快速定位数据组

💡 对于 InnoDB，从插入新数据的角度来说建议使用自增主键，因为这样插入新数据不会导致旧页数据的转移。而 UUID 作为主键时比较影响插入效率的。

相邻的页之间有指针记录：即 B+ 树叶子结点的顺序串联。一个页其实就是 B+ 树上的一个结点。

### 主键索引

- 主键索引树的叶子结点存储了完整的表数据，而非主键索引不会
- 聚集索引：索引和数据在同一棵树上

### 查找方式

- 全表扫描
- 索引查找

### 联合索引

- 联合索引叶子结点还会记录主键值，以便回表查询完整的一行数据
- 最左前缀原则

```sql
-- 索引: idx_bcd (b, c, d)
select * from t1 where b > 1;
-- 不走索引 `idx_bcd` 而是全表扫描，优化器评估后的结果是全表扫描的效率更高，走索引需要回表

select * from t1 where b > 6;
-- 假设 6 接近索引树的结尾，则很可能会走索引

select b, c, d from t1 where b > 1;
-- 索引树上有 select 需要的数据，所以不需要回表

select b, c, d, a from t1 where b > 1;
-- 索引树上有 select 需要的数据，因为 a 是主键，所以不需要回表
```

## Buffer Pool

- 属于 InnoDB
- 默认大小 128 MB，每个页大小也是 16 KB
- 位于内存
- 数据页会暂存于其中
- free 链表：用于管理 Buffer Pool 空闲页
  - 基结点：记录结点个数等统计信息
  - 控制块：指向每一个空白页的位置，有多少空白页就有多少控制块
- 从磁盘取新的数据页时，先查 free 链表，使用第一个结点指向的空白页
- flush 链表：和 free 链表很相似，只不过记录的是脏页
  - 执行 `update` 时，如果数据页已经在 Buffer Pool 中，则直接修改 Buffer Pool 中的数据页
  - 这些还没写回磁盘的页称为**脏页**
  - 后台有一个线程定期将脏页持久化到磁盘中
- LRU (Least Recently Used) 链表：淘汰策略
  - LRU 链表有长度限制
  - 新页（包括重新访问的页）加到链表头部，越是头部的结点越“新”
  - 🚨 如果只是使用以上机制，全表扫描会清空 Buffer Pool 的热点数据，导致 LRU 失效。
  - 实际上，LRU 链表分为两个区域：
    - 热数据：前 5/8
    - 冷数据：剩下的 3/8
    - 需要淘汰页时，仍然从冷数据中淘汰，但新页是先加到冷数据的头部
    - 当冷数据再次被访问，且时间间隔超过 1 秒，则把冷数据控制块转移到热数据区域中
    - 由于全表扫描访问同个数据页的时间极短，因此就只会影响冷数据区域。

## Redo log

1. Buffer Pool 出现脏页
2. 生成 redo log
3. redo log 持久化
4. 修改成功
5. 假如此时 MySQL crash 重启，它会读取磁盘数据，并结合 redo log 将数据恢复到 crash 前的状态。

这里 2 & 3 可以替换成“直接修改磁盘中的页数据”，但这样性能非常差：更新一行数据却要持久化整页。

- 记录页数据修改的物理数据，如哪一页
- redo log 持久化更好的原因是，它是顺序写，效率比 B+ 树的持久化高。
- InnoDB 启动时预分配 n 个 size 大小的 `ib_logfileN` 文件
  - n: `show global variables like '%innodb_log_files_in_group%'`
  - size: `show global variables like '%innodb_log_file_size%'`
- InnoDB 会循环使用这些 redo log 文件
  - write pos: 当前记录的位置
  - checkpoint: 当前要擦除的位置
  - 当 write pos 追上 checkpoint 时，就会触发脏页持久化
- 持久化之前的 redo log 数据存储于 Log buffer 中。
- `innodb_flush_log_at_trx_commit`
  - `0`: 事务提交时，不立即持久化，靠后台线程触发
  - `1`: 事务提交时，立即持久化（默认值）
  - `2`: 事务提交时，写到操作系统的缓冲区，由操作系统定期持久化

## Binlog

- 属于 MySQL Server 层
- 记录执行的 SQL
- Binlog 重放效率没有 redo log 高

## Undo log

- 修改数据时，修改的是 Buffer Pool 里的数据
- 假如需要 rollback，就需要把 Buffer Pool 的数据还原
- undo log 记录对应数据的原值
  - 以 sql 语句的形式，如
    - `update table set v=origin where ...`
    - `delete from table where ...`

## 事务

💡 MyISAM 不支持事务

```sql
begin

commit -- or rollback
```

### MVCC (多版本并发控制)

- 基于 undo log 实现
