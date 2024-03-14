# 第1章 初识Redis

- [第1章 初识Redis](#第1章-初识redis)
  - [1.1 盛赞Redis](#11-盛赞redis)
  - [1.2 Redis特性](#12-redis特性)
  - [1.3 Redis使用场景](#13-redis使用场景)
    - [1.3.1 Redis可以做什么](#131-redis可以做什么)
    - [1.3.2 Redis不可以做什么](#132-redis不可以做什么)
  - [1.4 用好Redis的建议](#14-用好redis的建议)
  - [1.5 正确安装并启动Redis](#15-正确安装并启动redis)
    - [1.5.1 安装Redis](#151-安装redis)
    - [1.5.2 配置、启动、操作、关闭Redis](#152-配置启动操作关闭redis)
  - [1.6 Redis重大版本](#16-redis重大版本)
  - [1.7 本章重点回顾](#17-本章重点回顾)

## 1.1 盛赞Redis

**Re**mote **di**ctionaty **s**erver.

- 与很多 KV 数据库不同的是，Redis 中的值可以是
  - string
  - hash
  - list
  - set
  - zset
  - bitmaps
  - HyperLogLog
  - GEO
  - ...
- 高性能：所有数据都存放在内存中
- 持久化：快照、日志保存到硬盘
- 其他功能：
  - 键过期
  - 发布订阅
  - 事务
  - 流水线
  - Lua脚本

## 1.2 Redis特性

Google 给出的各层级硬件执行速度：<https://gist.github.com/jboner/2841832>

1. 速度快：读写性能可达到 100K/s
    - 所有数据都存放在内存中
    - 由C语言实现
    - 使用单线程架构，预防了很多多线程的竞争问题
    - 集性能和优雅于一身
2. 基于键值对的数据结构服务器：主要提供了五种数据结构，及其他衍生数据结构
    - string
    - hash
    - list
    - set
    - zset
    - Bitmaps
    - HyperLogLog
    - GEO
3. 丰富的功能
    - 键过期：实现缓存
    - 发布订阅：实现消息系统
    - Lua脚本：利用Lua定制Redis命令
    - 简单的事务：一定程度上保证事务特性
    - Pipeline：命令批量化，减少网络开销
4. 简单稳定
    - 源代码很少，早期才 2 万行
    - 单线程模型，使服务端、客户端都变得简单
    - 不依赖操作系统类库，自行实现事件处理
      - Memcache 依赖 `libevent`
5. 客户端语言多
    - Redis 支持 TCP 通信
    - Java, PHP, Python, C, C++, Node.js....
6. 持久化
    - RDB
    - AOF
7. 主从复制
    - 复制功能是分布式的基础
8. 高可用和分布式
    - Redis Sentinel: 保证节点的故障发现和故障自动转移
    - Redis Cluster: 高可用、读写和容量扩展

## 1.3 Redis使用场景

### 1.3.1 Redis可以做什么

1. 缓存：基于键值过期
2. 排行榜系统：基于丰富的数据结构
3. 计数器应用
4. 社交网络
5. 消息队列系统：基于发布订阅和阻塞队列（虽然比不上专门的消息队列）

### 1.3.2 Redis不可以做什么

- 不适合存储大规模数据
- 不适合存储冷数据

## 1.4 用好Redis的建议

1. 切勿当作黑盒使用，开发与运维同样重要
    - 很多线上故障和问题都是由于完全把它当作黑盒造成的，如
      - 因为不了解它是单线程模型，在上千万个键的实例上执行 `keys*` 操作
      - 因为不了解持久化原理，而在一个写操作量很大的实例上配置自动保存RDB
2. 阅读源码
    - 源码量不大；可以提升编码水平
    - 有能力做定制化

## 1.5 正确安装并启动Redis

### 1.5.1 安装Redis

1. 在Linux上安装Redis
    - 推荐使用源码安装
  
    ```sh
    wget ...
    tar xzf ...
    ln -s redis-3.0.7 redis # 方便版本升级
    cd redis
    make
    make install
    ```

2. 在Windows上安装Redis: <https://github.com/microsoftarchive/redis>

### 1.5.2 配置、启动、操作、关闭Redis

- `redis-server`: 启动 Redis
- `redis-cli`: 命令行客户端
- `redis-benchmark`: 基准测试工具
- `redis-check-aof`: AOF 持久化文件检测和修复工具
- `redis-check-dump`: RDB 持久化文件检测和修复工具
- `redis-sentinel`: 启动 Redis Sentinel

1. 启动 Redis
    - 默认配置: `redis-server`
      - `/usr/local/etc/redis/redis.conf` Docker 镜像默认无此文件
    - 运行配置: `redis-server --configKey1 --configValue1 ...`
    - 配置文件启动（推荐）: `redis-server /opt/redis/redis.conf`，重要参数
      - `port`: 端口
      - `logfile`: 日志文件
      - `dir`: 工作目录，存放持久化文件和日志文件
      - `daemonize`: 是否以守护进程的方式启动
2. Redis命令行客户端
    - 交互式: `redis-cli -h HOST -p PORT`
    - 命令式: `redis-cli -h HOST -p PORT COMMAND`
3. 停止Redis服务: `redis-cli shutdown nosave|save`
    - 关闭过程
      - 断开客户端连接
      - 生成持久化文件
    - 粗暴方式：kill-9，副作用
      - 不做持久化操作
      - 缓冲区不能被优雅关闭
      - 造成AOF和复制丢失数据

## 1.6 Redis重大版本

版本号第二位奇数代表非稳定版本（也叫开发版本）。

1. Redis 2.6 (2012)
2. Redis 2.8 (2013)
    - Sentinel 第二版，生产可用级别
3. Redis 3.0 (2015)
    - 支持 Cluster
4. Redis 3.2 (2016)
5. Redis 4.0 (2017)
    - 提供模块系统以支持第三方扩展

## 1.7 本章重点回顾

1. Redis 的 8 个特性
   1. 速度快
   2. 基于键值对的数据结构服务器
   3. 功能丰富
   4. 简单稳定
   5. 客户端语言多
   6. 持久化
   7. 主从复制
   8. 支持高可用和分布式
2. 有些场景不适合使用 Redis
3. 开发运维结合以及阅读源码是用好 Redis 的重要方法
4. 生产环境中使用配置文件启动 Redis
5. 生产环境选取稳定版本的Redis
6. Redis 3.0 是重要的里程碑，发布了官方的分布式实现 Redis Cluster
