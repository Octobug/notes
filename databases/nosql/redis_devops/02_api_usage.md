# 第2章 API的理解和使用

- [第2章 API的理解和使用](#第2章-api的理解和使用)
  - [2.1 预备](#21-预备)
    - [2.1.1 全局命令](#211-全局命令)
      - [1.查看所有键](#1查看所有键)
      - [2.键总数](#2键总数)
      - [3.检查键是否存在](#3检查键是否存在)
      - [4.删除键](#4删除键)
      - [5.键过期](#5键过期)
      - [6.键的数据结构类型](#6键的数据结构类型)
    - [2.1.2 数据结构和内部编码](#212-数据结构和内部编码)
    - [2.1.3 单线程架构](#213-单线程架构)
      - [1.引出单线程模型](#1引出单线程模型)
      - [2.为什么单线程还能这么快](#2为什么单线程还能这么快)
  - [2.2 字符串](#22-字符串)
    - [2.2.1 命令](#221-命令)
      - [1.常用命令](#1常用命令)
        - [1.1 设置值](#11-设置值)
        - [1.2 获取值](#12-获取值)
        - [1.3 批量设置值](#13-批量设置值)
        - [1.4 批量获取值](#14-批量获取值)
        - [1.5 计数](#15-计数)
      - [2.不常用命令](#2不常用命令)
        - [2.1 追加值](#21-追加值)
        - [2.2 字符串长度](#22-字符串长度)
        - [2.3 设置并返回原值](#23-设置并返回原值)
        - [2.4 设置置顶位置的字符](#24-设置置顶位置的字符)
        - [2.5 获取部分字符串](#25-获取部分字符串)
    - [2.2.2 内部编码](#222-内部编码)
    - [2.2.3 典型使用场景](#223-典型使用场景)
      - [1.缓存功能](#1缓存功能)
      - [2.计数](#2计数)
      - [3.共享Session](#3共享session)
      - [4.限速](#4限速)
  - [2.3 哈希](#23-哈希)
    - [2.3.1 命令](#231-命令)
    - [2.3.2 内部编码](#232-内部编码)
    - [2.3.3 使用场景](#233-使用场景)
  - [2.4 列表](#24-列表)
    - [2.4.1 命令](#241-命令)
      - [1.添加操作](#1添加操作)
      - [2.查找](#2查找)
      - [3.删除](#3删除)
      - [4.修改](#4修改)
      - [5.阻塞操作](#5阻塞操作)
    - [2.4.2 内部编码](#242-内部编码)
    - [2.4.3 使用场景](#243-使用场景)
      - [1.消息队列](#1消息队列)
      - [2.文章列表](#2文章列表)
  - [2.5 集合](#25-集合)
    - [2.5.1 命令](#251-命令)
      - [1.集合内操作](#1集合内操作)
      - [2.集合间操作](#2集合间操作)
    - [2.5.2 内部编码](#252-内部编码)
    - [2.5.3 使用场景](#253-使用场景)
  - [2.6 有序集合](#26-有序集合)
    - [2.6.1 命令](#261-命令)
      - [1.集合内](#1集合内)
      - [2.集合间的操作](#2集合间的操作)
    - [2.6.2 内部编码](#262-内部编码)
    - [2.6.3 使用场景](#263-使用场景)
  - [2.7 键管理](#27-键管理)
    - [2.7.1 单个键管理](#271-单个键管理)
      - [1.键重命名](#1键重命名)
      - [2.随机返回一个键](#2随机返回一个键)
      - [3.键过期](#3键过期)
      - [4.迁移键](#4迁移键)
        - [4.1 move](#41-move)
        - [4.2 dump + restore](#42-dump--restore)
        - [4.3 migrate（推荐）](#43-migrate推荐)
    - [2.7.2 遍历键](#272-遍历键)
      - [1.全量遍历键](#1全量遍历键)
      - [2.渐进式遍历](#2渐进式遍历)
    - [2.7.3 数据库管理](#273-数据库管理)
      - [1.切换数据库](#1切换数据库)
      - [2.flushdb/flushall](#2flushdbflushall)
  - [2.8 本章重点回顾](#28-本章重点回顾)

## 2.1 预备

### 2.1.1 全局命令

Redis 有 5 种数据结构，它们是键值对中的值，对于键来说有一些通用的命令。

#### 1.查看所有键

```redis
keys *

set hello world
set java jedis
set python redis-py

keys *
```

#### 2.键总数

```redis
dbsize
# 3

rpush mylist a b c d e f g
# (integer) 7
```

- `dbsize` 在计算键总数时不会遍历所有键，而是直接获取 Redis 内置变量，复杂度 `O(1)`。
- `keys *` 会遍历所有键，`O(n)`，因此生产环境最好别用。

#### 3.检查键是否存在

```redis
exists key
```

#### 4.删除键

```redis
del key1 key2 ... # 返回删除键的个数， O(k)

set a 1
set b 1
set c 1
del a b c
```

#### 5.键过期

```redis
expire KEY SECONDS

set hello world
expire hello 10

ttl hello
# 返回过期秒数
# -1: 没设置过期时间
# -2: 键不存在
```

#### 6.键的数据结构类型

```redis
type KEY

rpush mylist a b c d e f g
type mylist
```

### 2.1.2 数据结构和内部编码

`string`, `hash`, `list`, `set`, `zset` 是 Redis 对外的数据结构。
而实际上，每一种数据结构都有两种以上的内部实现，对应不同场景。

```redis
object encoding hello
# "embstr"

object encoding mylist
# "quicklist"
```

- string
  - raw
  - int
  - embstr
- hash
  - hashtable
  - ziplist
- list
  - linkedlist
  - quicklist
  - ziplist
- set
  - hashtable
  - intset
- zset
  - skiplist
  - ziplist

外部数据结构相当于 API，而内部实现可以替换、优化而不影响 API。

### 2.1.3 单线程架构

Redis 使用了单线程架构和 I/O 多路复用模型来实现高性能数据库服务。

#### 1.引出单线程模型

Redis 客户端与服务端的通讯模型：

1. 客户端发送命令
2. 服务端执行命令
3. 服务端返回结果

Redis 是单线程模型，所有到达的命令会先进入一个队列，然后逐个执行，而不存在并发执行。

#### 2.为什么单线程还能这么快

1. 纯内存访问：内存响应时长约为 100ns
2. 非阻塞I/O：使用 epoll I/O 多路复用技术，加上自身的事件处理模型，将 epoll 的连接、读写、关闭都转换为事件，减少网络I/O处理时间，
3. 单线程简化数据结构和算法的实现，避免线程切换和竞态产生的消耗。
    - 缺点：如果某个命令执行过久，会阻塞其他命令

## 2.2 字符串

- 键都是字符串
- 其他几种数据结构都是在字符串类型的基础上构建

### 2.2.1 命令

#### 1.常用命令

##### 1.1 设置值

```redis
set KEY VALUE [ex SECONDS] [px MILLISECONDS] [nx|xx]
```

- `ex`
  - 相当于 `setex`
- `nx`: 键必须不存在，用于新建。
  - 相当于 `setnx`
  - 可以作为分布式锁：只有一个 client 能设置成功
- `xx`: 键必须存在，用于更新

##### 1.2 获取值

get

##### 1.3 批量设置值

```redis
mset KEY1 VALUE1 KEY2 VALUE2 ... # O(k)
```

##### 1.4 批量获取值

```redis
mget ... # O(k)
```

- 1000 次 get: `1ms * 1000 + 0.1ms * 1000 = 1100ms`
- 1 次 mget: `1ms * 1 + 0.1ms * 1000 = 101ms`

⚠️ 一次如果传送太多键值对可能会导致长时间阻塞。

##### 1.5 计数

```redis
incr KEY
decr KEY
incrby KEY NUM
decrby KEY NUM
incrbyfloat KEY NUM
```

- 键不存在时从 0 自增
- 值不是整数时返回错误

#### 2.不常用命令

##### 2.1 追加值

- `append KEY VALUE`: 字符串追加值

##### 2.2 字符串长度

- `strlen KEY`

##### 2.3 设置并返回原值

- `getset KEY VALUE`

##### 2.4 设置置顶位置的字符

- `setrange KEY INDEX CHAR`

##### 2.5 获取部分字符串

- `getrange KEY START END` # O(n)

### 2.2.2 内部编码

Redis 更具当前值的类型和长度决定使用其中一种

- `int`: 8 bytes 的 `long int`
- `embstr`: <= 39 bytes
- `raw`: > 39 bytes

```redis
set key 8653
object encoding key
# "int"

set key hello
object encoding key
# "embstr"

set key "it's a loooooooooooooooooooooooooooooooooooooooo str"
object encoding key
# "raw"
```

### 2.2.3 典型使用场景

#### 1.缓存功能

加速读写、降低数据库压力。

```java
Userinfo getUserInfo(long id) {
    userRediskey = "user:info:" + id;
    value = redis.get(userRedisKey);
    if (value != null) {
        userInfo = deserialize(value)
        return userInfo;
    }

    userInfo = mysql.get(id);
    if (userInfo != null) {
        redis.setex(userRediskey, 3600, serialize(userInfo));
    }
    return userInfo;
}
```

Redis 没有命令空间，需要在应用层合理设计键名。可以对应数据库不同层级的元素，并适当缩短键名减少内存: `db:tb:pk:col`

#### 2.计数

利用 Redis 可以实现快速计数、查询缓存。

```java
long incrVideoCounter(long id) {
    key = "video:playCount:" + id;
    return redis.incr(key);
}
```

#### 3.共享Session

分布式 Web 服务的 Session 可以在 Redis 中集中管理，避免负载均衡导致的 Session 路由问题。

#### 4.限速

```java
// 发短信一分钟不能超过 5 次
phoneNum = "138xxxxxxxx";
key = "shortMsg:limit:" + phoneNum;
isExists = redis.set(key, 1, "EX 60", "NX");
if (isExists != null || redis.incr(key) <= 5) {
    // 通过
} else {
    // 限制
}
```

## 2.3 哈希

在 Redis 中，哈希类型是指键值本身又是一个键值对结构。

- `key:hash`
  - `hash`
    - `field:value`

### 2.3.1 命令

```redis
hset KEY FIELD VALUE
hget KEY FIELD
hdel KEY FIELD # O(k)
hlen KEY

hmget KEY FIELD1 FIELD2 ... # O(k)
hmset KEY FIELD1 VALUE1 FIELD2 VALUE2 ... # O(k)

hexists KEY FIELD
hkeys KEY # 获取所有 field，其实叫 hfields 更合适, # O(n)
hvals KEY # O(n)
hgetall KEY # O(n)

hincrby KEY FIELD NUM
hincrbyfloat KEY FIELD NUM

hstrlen KEY FIELD
```

⚠️ 如果 field 非常多，应该使用 `hscan` 代替 `hgetall`。

### 2.3.2 内部编码

哈希类型有两种内部编码：

- ziplist (压缩列表)
  - field 个数 `hash-max-ziplist-entries < 512`
  - value 大小 `hash-max-ziplist-value < 64 bytes`
- hashtable (哈希表): 当 ziplist 条件不满足时

```redis
hmset hashkey f1 v1 f2 v2 ...
object encoding hashkey
# "ziplist"

hset hashkey f3 "long long long long long ... long long"
object encoding hashkey
# "hashtable"
# 或者

hmset hashkey f1 v1 f2 v2 f3 v3 ............. f513 v513
object encoding hashkey
"hashtable"
```

### 2.3.3 使用场景

哈希类型和关系型数据库表的对应就更直观，并且更新操作会更便捷。

```redis
# HASH
KEY     FIELD   VALuE
user:1  name    Tom
```

```java
UserInfo getUserInfo(long id) {
    userRedisKey = "user:info:" + id;
    userInfoMap = redis.hgetAll(userRedisKey);
    UserInfo userInfo;
    if (userInfoMap != null) {
        // 将映射关系转换为 UserInfo
        userInfo = transferMapToUserInfo(userInfoMap);
    } else {
        userInfo = mysql.get(id);
        redis.hmset(userRedisKey, transferUserInfoToMap(userInfo));
         // 添加过期时间
        redis.expire(userRedisKey, 3600);
    }
    return userInfo;
}
```

哈希类型和关系型数据库的两点不同之处：

- 哈希类型是稀疏的，而关系型数据库是完全结构化的。
  - 哈希类型每个键可以有不同的 field
  - 关系型数据库一旦添加新列，所有现存行都要为其设置值
- 关系型数据库可以做复杂的关系查询，Redis 模拟关系型复杂查询开发困难

三种 redis 数据结构缓存用户信息的方案对比：

- 字符串类型：每个属性一个键
  - 优点：每个属性都支持更新
  - 缺点：
    - 键太多，占用内存大
    - 用户信息内聚性差
- 字符串类型 + 序列化：将用户信息序列化后用一个键保存
  - 优点：简化编程，提高内存使用效率
  - 缺点：序列化和反序列化都有开销，且每次更新都要先读后存
- 哈希类型：每个用户属性使用一对 field-value
  - 优点：简单直观，减少内存占用
  - 缺点：需要控制 ziplist 和 hashtable 的转换，hashtable 消耗内存更多

## 2.4 列表

列表用于存储多个有序的字符串。

- 数量限制：$2^{32} - 1$
- 有序，可重复

### 2.4.1 命令

#### 1.添加操作

```redis
rpush KEY VALUE # O(k)
lpush # O(k)
linsert KEY before|after PIVOT_VALUE NEW_VALUE # O(n)
```

#### 2.查找

```redis
lrange KEY START END # END 是闭区间，和大部分编程语言不一样，O(s+n)
# 0 -> N-1
# -1 <- -N

lindex KEY INDEX # O(n)

llen KEY
```

#### 3.删除

```redis
lpop KEY
rpop
lrem KEY COUNT VALUE # 删除值为 VALUE 的元素, # O(n)
ltrim KEY START END # 只保留 START-END 的元素, # O(n)
```

`count`：删除最多个数

- `> 0`: 从左到右
- `< 0`: 从右到左
- `= 0`: 删除所有

#### 4.修改

```redis
lset KEY INDEX VALUE # O(n)
```

#### 5.阻塞操作

```redis
blpop KEY1 KEY2 ... TIMEOUT
brpop KEY1 ... TIMEOUT
```

- 它们是 `lpop` 和 `rpop` 的阻塞版本
- `timeout`
  - `0`: 阻塞到列表不为空为止
  - `N`: 最多阻塞 `N` s
- 如果有多个键，`brpop` 是从左向右遍历键，一旦有一个键能弹出元素，则立即弹出并返回

### 2.4.2 内部编码

- ziplist
  - 元素个数 `< list-max-ziplist-entries` (默认 512)
  - 每个元素 `< list-max-ziplist-value` (默认 64 bytes)
- linkedlist: 不满足 ziplist 条件时
- quicklist (新增): 以一个 ziplist 为节点的 linkedlist，结合两者优势

### 2.4.3 使用场景

#### 1.消息队列

`lpush` + `brpop`

#### 2.文章列表

```redis
hmset article:1 title xx ts 1234

lpush user:1:articles article:1 article:2
lrange user:1:articles 0 -1
```

⚠️ 使用列表类型保存和获取文章列表会有两个问题：

1. 如果每次分页获取的文章个数较多，需要执行多次 `hgetall` 逐个获取文章内容
    - 可以考虑用 Pipeline 批量获取
    - 或者将文章内容序列化为字符串后使用 mget 批量获取
2. `lrange` 在列表两端性能较好，如果列表很大，访问中间范围性能会变差
    - 可以考虑将列表做二级拆分，或者使用 quicklist

使用场景总结：

- `lpush` + `lpop` = stack
- `lpush` + `rpop` = queue
- `lpush` + `ltrim` = capped collection (有限集合)
- `lpush` + `brpop` = message queue (消息队列)

## 2.5 集合

集合支持增删改查和取交集、并集、差集。

### 2.5.1 命令

#### 1.集合内操作

```redis
sadd KEY ELEMENT [ELEMENT ...] # O(k)
srem KEY ELEMENT [ELEMENT ...] # O(k)
scard KEY # 内部实现直接使用计数变量
sismember KEY ELEMENT
srandmember KEY [count] # 随机返回，不删除, O(count)
spop KEY [count]
smembers KEY # 获取所有元素 # O(n)
```

⚠️ `smembers` 和 `lrange`, `hgetall` 一样也可能导致长时间阻塞，可以用 `sscan` 替代。

#### 2.集合间操作

```redis
sinter KEY [KEY ...] # O(m*k)
sunion KEY [KEY ...] # O(k)
sdiff KEY [KEY ...] # O(k)

sinterstore DESTINATION KEY [KEY...] # O(m*k)
sunionstore DESTINATION KEY [KEY...] # O(k)
sdiffstore DESTINATION KEY [KEY...] # O(k)
```

### 2.5.2 内部编码

- intset
  - 都是 int
  - 元素个数 `< set-max-intset-entries` 默认 512
- hashtable: 不满足 intset 条件时

### 2.5.3 使用场景

- `sadd` = tagging (标签)
- `spop`/`srandmember` = Random item (抽奖)
- `sadd` + `sinter` = Social Graph (社交网络)

```redis
sadd user:1:tags tag1 tag2 ...
sadd user:2:tags tag2 tag3 ...

sadd tag1:users user:1 user:2
sadd tag2:users user:1 user:3

srem user:1:tags tag1 tag5
srem tag1:users user:1

sinter user:1:tags user:2:tags
```

user 和 tag 的关系应该使用事务维护，防止数据不一致。

## 2.6 有序集合

Redis 给有序集合的每一个元素设置一个分数 (score) 作为排序依据，元素不能重复，但分数可以重复。

### 2.6.1 命令

#### 1.集合内

```redis
zadd user:ranking 251 tom # O(k*logn)
```

- `nx`: member 不存在才设置成功
- `xx`: member 存在才设置成功
- `ch`: 返回元素和分数发生变化的个数
- `incr`: 增加分数

```redis
zcard user:ranking # 成员个数
zscore user:ranking tom # 某个成员的分数
zrank user:ranking tom # 升序, O(logn)
zrevrank user:ranking tom # 降序
zrem user:ranking mike  # O(k*logn)
zincrby user:ranking 9 tom # 增加分数, O(logn)

zrange user:ranking 0 2 [withscores] # 返回指定升序排名范围的成员, O(logn+k)
zrevrange user:ranking 0 2 [withscores] # 返回指定降序排名范围的成员, O()

# 分数范围成员, O(logn+k)
zrangebyscore KEY MIN MAX [withscores] [limit offset count]
zrevrangebyscore KEY MIN MAX [withscores] [limit offset count]

zcount user:ranking 200 221 # 返回分数范围的成员个数, O(logn)

zremrangebyrank KEY START END # 按升序删除指定排名内的元素, O(logn+k)
zremrangebyscore KEY MIN MAX # 按分数范围删除元素, O(logn+k)
```

```redis
# min max 支持指定开区间闭区间，-inf, +inf 代表无穷大无穷小
zrangebyscore user:ranking (200 +inf withscores
```

#### 2.集合间的操作

```redis
zinterstore DESTINATION NUMKEYS KEY [KEY ...] [weights WEIGHT [WEIGHT ...]]
  [aggregate sum|min|max]
```

- `destination`
- `numkeys`: 需要做交集计算的键个数？
- `key [key ...]`
- `weights weight [weight ...]`: 每个键的权重，做交集计算时，每个键中的每个 member 会将自己的分数乘以这个权重，默认为 `1`。
- `aggregate sum|min|max`: 分值按 `sum`, `min`, `max` 汇总，默认值是 `sum`

```redis
# O(n*k)+O(m*logm)
zinterstore user:ranking:1_inter_2 2 user:ranking:1 user:ranking:2
zinterstore user:ranking:1_inter_2 2 user:ranking:1 user:ranking:2 weights 1 0.5 aggregate max
```

```redis
# O(n)+O(m*logm)
zunionstore destination NUMKEYS KEY [KEY ...] [weights WEIGHT [WEIGHT ...]]
  [aggregate sum|min|max]
```

### 2.6.2 内部编码

- ziplist
  - 元素个数 `< zset-max-ziplist-entries` 默认 128
  - 元素值 `< zset-max-ziplist-value` 默认 64 bytes
  - 有效减少内存的使用
- skiplist

### 2.6.3 使用场景

例子：排行榜系统，需要多维度综合积分。

```redis
# 获赞
zadd user:ranking:2016_03_15 mike 3

# 获赞
zincrby user:ranking:2016_03_15 mike 1

# 取消作弊赞数
zrem user:ranking:2016_03_15 mike

# 展示获赞最多的 10 个用户
zrevrangebyrank user:ranking:2016_03_15 0 9

# 展示用户信息及用户分数：用户名作为键后缀，用户信息保存在哈希类型中
hgetall user:info:mike
zscore user:ranking:2016_03_15 mike
zrank user:ranking:2016_03_15 mike
```

## 2.7 键管理

### 2.7.1 单个键管理

#### 1.键重命名

```redis
# 如果 NEWKEY 已存在将被覆盖
rename KEY NEWKEY

# 确保 NEWKEY 不存在时才成功
renamenx KEY NEWKEY
```

- 重命名时会 `del` 旧键，如果原键值比较大可能会阻塞。
- 3.2 起 `rename key key` 会报错

#### 2.随机返回一个键

```redis
randomkey
```

#### 3.键过期

```redis
expire key seconds
expireat key timestamp # 秒级的时间戳

ttl key
pttl key # 毫秒级, -1 表示没设置过期，-2 表示键不存在

pexpire key miliseconds
pexpireat key miliseconds-timestamp

# 清除过期时间
persist key
```

以上的 `*expire*` 命令都是基于 `pexpireat` 实现

- `expire key` 如果键不存在返回 0
- 如果时间 `< 0` 则键马上删除

对于字符串类型的键，执行 `set` 会去掉过期时间

```redis
set hello world
expire hello 50
ttl hello
set hello newworld
ttl hello
```

- Redis 不支持二级数据结构内部元素的过期功能。
- `setex` 作为 `set` + `expire` 的组合，不但是原子执行，同时可以减少网络通讯

#### 4.迁移键

迁移部分数据到另一个 Redis 实例。

##### 4.1 move

`move` 用于在 Redis 内部的多个数据库进行迁移（较少用）

```redis
move key TARGET_DB
```

##### 4.2 dump + restore

在不同的 Redis 实例之间迁移：

```redis
dump key
restore key ttl VALUE
# ttl 代表过期时间，0 代表没有过期时间
```

1. 在源 Redis 上，`dump` 会序列化键值数据，格式为 RDB。
2. 在目标 Redis 上，`restore` 将序列化的数据复原导入

⚠️ 注意：

1. 迁移过程不是原子性的，而是通过客户端分步完成
2. 迁移过程是开启两个客户端连接，dump 结果不是源 Redis 和目标 Redis 之间直接传输

```redis
# 源 Redis
set hello world
dump hello
'\x00\x...........'

# 目标 Redis
restore hello 0 '\x00\x...........'
```

对应为代码如下：

```java
Redis sourceRedis = new Redis("sourceMachine", 6379);
Redis targetRedis = new Redis("targetMachine", 6379);
targetRedis.restore(key, 0, sourceRedis.dump(key));
```

##### 4.3 migrate（推荐）

```redis
migrate host port key|"" destination-db timeout [copy] [replace]
  [keys key [key...]]

migrate host port "" 0 5000 keys key1 key2 ...
```

`migrate` 将 `dump` `restore` `del` 组合起来，特点：

1. 原子化操作，只需要在源 Redis 上执行
2. migrate 数据直接传输到目标 Redis
3. 目标 Redis 完成 restore 后返回 OK，源 Redis 收到后根据 migrate 选项决定是否 del

参数：

- host
- port
- key|"": 单键时写键本身，多键时写 `""`
- destination-db: 目标数据库索引
- timeout
- copy: 只复制不删除
- replace: 不管目标是否存在该键，直接覆盖
- [keys key [key...]]: 迁移多个键

### 2.7.2 遍历键

#### 1.全量遍历键

```redis
keys pattern
```

pattern 使用 glob 风格的通配符：

- `*` 匹配任意字符
- `.` 匹配一个字符
- `[]`
  - `[1-10]`
- `\x` 转义

```sh
redis-cli keys video* | xargs redis-cli del
```

⚠️ 警告

- 一般不在生产环境使用 `keys`

#### 2.渐进式遍历

- scan 采用渐进式遍历避免长时间阻塞。
- 复杂度为 O(1)
- 每次遍历只扫描一部分键，真正遍历需要执行多次

```redis
scan cursor [match pattern] [count number]
```

- 每次遍历会返回当前游标值
  - 游标不一定是递增的，这和 Redis 存储键值对有关，实际上也是一个 hash 表
- 当返回的游标值为 0 说明遍历结束
- `count number` 表示每次遍历的键个数，默认为 10

具体数据结构的扫描遍历命令都有对应的 scan 版本：

- `hgetall`: `hscan`
- `smembers`: `sscan`
- `zrange`; `zscan`

例子：集合中有 "old:user" 和 "new:user" 两种数据，现需要将 "old:user" 全部删除

```java
String key = "myset";
String pattern = "old:user*"; // 游标每次从0开始
String cursor = "0";

while (true) {
  // 获取扫描结果
  ScanResult scanResult = redis.sscan(key, cursor, pattern);
  List elements = scanResult.getResult();
  if (elements != null && elements.size() > 0) {
    // 批量删除
    redis.srem(key, elements);
  }
  // 获取新的游标
  cursor = scanResult.getStringCursor();
  // 如果游标为0表示遍历结束
  if ("0".equals(cursor)) {
    break;
  }
}
```

⚠️ `scan` 过程中，如果有键的增删改，可能会：

- 新增的键没有遍历
- 遍历出重复的键

如果要保持数据一致，且数据量不大，还是可以考虑用 `keys *`。

### 2.7.3 数据库管理

#### 1.切换数据库

- Redis 用数字编号区分数据库，默认是 16 个
- 客户端连接时默认 `select 0`
- 不同数据库之间没有任何关系

```redis
select dbIndex
```

Redis 3.0 弱化了这个功能，Redis Cluster 只允许使用 0 号数据库：

- Redis 是单线程的，多个数据库使用的仍然是同一个 CPU
- 一个慢查询影响所有数据库，业务和运维都困难
- 有些客户端不支持切换数据库

需要多个数据库时，更建议多实例部署。

#### 2.flushdb/flushall

- `flushdb`: 清除当前数据库
- `flushall`: 清除所有数据库

这两个命令也可能会长时间阻塞。

## 2.8 本章重点回顾

1. Redis 提供 5 种数据结构，每种数据结构都有多种内部编码实现。
2. 纯内存存储、IO 多路复用技术、单线程架构是造就 Redis 高性能的三个因素。
3. 由于 Redis 的单线程架构，所以需要每个命令能被快速执行完，否则会存在阻塞的可能，理解 Redis
   单线程命令处理机制是开发和运维 Redis 的核心之一。
4. 批量操作 (例如 mget、mset、hmset 等) 能有效提高命令执行效率，但要注意每次批量操作的个数和字节数。
5. 了解每个命令的时间复杂度在开发中至关重要，例如在使用 keys、hgetall、smembers、zrange
   等时间复杂度较高的命令时，需要考虑数据规模对于 Redis 的影响。
6. persist 命令可以删除任意类型键的过期时间，但是 set 命令也会删除字符串类型键的过期时间，这在开发时容易被忽视。
7. move、dump+restore、migrate 是 Redis 发展过程中三种迁移键的方式，其中 move
   命令基本废弃，migrate 命令用原子性的方式实现了 dump+restore，并且支持批量操作，是
   Redis Cluster 实现水平扩容的重要工具。
8. scan 命令可以解决 keys 命令可能带来的阻塞问题，同时 Redis 还提供了
   hscan、sscan、zscan 渐进式地遍历 hash、set、zset。
