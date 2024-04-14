# 第4章 客户端

- [第4章 客户端](#第4章-客户端)
  - [4.1 客户端通信协议](#41-客户端通信协议)
    - [1. 发送命令格式](#1-发送命令格式)
    - [2. 返回结果格式](#2-返回结果格式)
  - [4.2 Java 客户端 Jedis](#42-java-客户端-jedis)
    - [4.2.1 获取 Jedis](#421-获取-jedis)
    - [4.2.2 Jedis 的基本使用方法](#422-jedis-的基本使用方法)
      - [1. protostuff 的 Maven 依赖](#1-protostuff-的-maven-依赖)
      - [2. 定义实体类](#2-定义实体类)
      - [3. 使用 ProtostuffSerializer 序列化和反序列化](#3-使用-protostuffserializer-序列化和反序列化)
      - [4. 测试](#4-测试)
    - [4.2.3 Jedis 连接池的使用方法](#423-jedis-连接池的使用方法)
      - [1. Jedis 连接池 (通常 JedisPool 是单例的)](#1-jedis-连接池-通常-jedispool-是单例的)
      - [2. 从连接池直接获取获取 Jedis 对象](#2-从连接池直接获取获取-jedis-对象)
    - [4.2.4 Redis 中 Pipeline 的使用方法](#424-redis-中-pipeline-的使用方法)
    - [4.2.5 Jedis 的 Lua 脚本](#425-jedis-的-lua-脚本)
  - [4.3 Python 客户端 redis-py](#43-python-客户端-redis-py)
    - [4.3.1 获取 redis-py](#431-获取-redis-py)
    - [4.3.2 redis-py 的基本使用方法](#432-redis-py-的基本使用方法)
    - [4.3.3 redis-py 中 Pipeline 的使用方法](#433-redis-py-中-pipeline-的使用方法)
    - [4.3.4 redis-py 中的 Lua 脚本使用方法](#434-redis-py-中的-lua-脚本使用方法)
  - [4.4 客户端管理](#44-客户端管理)
    - [4.4.1 客户端 API](#441-客户端-api)
      - [1. client list](#1-client-list)
        - [1.1 客户端的四个标识属性](#11-客户端的四个标识属性)
        - [1.2 输入缓冲区: qbuf、qbuf-free](#12-输入缓冲区-qbufqbuf-free)
        - [1.3 输出缓冲区: obl、oll、omem](#13-输出缓冲区-oblollomem)
        - [1.4 客户端的存活状态](#14-客户端的存活状态)
        - [1.5 客户端的限制 maxclients 和 timeout](#15-客户端的限制-maxclients-和-timeout)
        - [1.6 客户端类型](#16-客户端类型)
      - [2. client setName 和 client getName](#2-client-setname-和-client-getname)
      - [3. client kill](#3-client-kill)
      - [4. client pause](#4-client-pause)
      - [5. monitor](#5-monitor)
    - [4.4.2 客户端相关配置](#442-客户端相关配置)
    - [4.4.3 客户端统计片段](#443-客户端统计片段)
  - [4.5 客户端常见异常](#45-客户端常见异常)
    - [1. 无法从连接池获取到连接](#1-无法从连接池获取到连接)
    - [2. 客户端读写超时](#2-客户端读写超时)
    - [3. 客户端连接超时](#3-客户端连接超时)
    - [4. 客户端缓冲区异常](#4-客户端缓冲区异常)
    - [5. Lua 脚本正在执行](#5-lua-脚本正在执行)
    - [6. Redis 正在加载持久化文件](#6-redis-正在加载持久化文件)
    - [7. Redis 使用的内存超过 maxmemory 配置](#7-redis-使用的内存超过-maxmemory-配置)
    - [8. 客户端连接数过大](#8-客户端连接数过大)
  - [4.6 客户端案例分析](#46-客户端案例分析)
    - [4.6.1 Redis 内存陡增](#461-redis-内存陡增)
      - [1. 现象](#1-现象)
      - [2. 分析原因](#2-分析原因)
      - [3. 处理方法和后期处理](#3-处理方法和后期处理)
    - [4.6.2 客户端周期性的超时](#462-客户端周期性的超时)
      - [1. 超时现象](#1-超时现象)
      - [2. 分析](#2-分析)
      - [3. 处理方法和后续处理](#3-处理方法和后续处理)
  - [4.7 本章重点回顾](#47-本章重点回顾)

Redis 用单线程处理多个客户端的访问。

## 4.1 客户端通信协议

1. 客户端与服务端之间的通信协议是在 TCP 协议之上构建的。
2. Redis 制定了 RESP (REdis Serialization Protocol，Redis 序列化协议) 实现客户端与服务端的正常交互。
    - 这种协议简单高效，既能够被机器解析，又容易被人类识别。
    - 例如客户端发送一条 `set hello world` 命令给服务端，按照 RESP 的标准，客户端需要将其封装为如下格式(每行用\r\n分隔)：

    ```resp
    *3
    $3
    SET
    $5
    hello
    $5
    world
    ```

    - Redis 服务端按照 RESP 将其解析为 `set hello world` 命令，执行后回复的格式如下：
      `+OK`

### 1. 发送命令格式

RESP 规定一条命令的格式如下，`CRLF` 代表 `\r\n`。

```resp
*<参数数量> CRLF
$<参数1的字节数量> CRLF
<参数1> CRLF
...
$<参数N的字节数量> CRLF
<参数N> CRLF
```

以 `set hell world` 这条命令进行说明。参数数量为3个，因此第一行为：

```resp
*3
```

参数字节数分别是3, 5, 5，因此后面几行为：

```resp
$3
SET
$5
hello
$5
world
```

⚠️ 上面只是格式化显示的结果，实际传输格式为如下代码：

```resp
*3\r\n$3\r\nSET\r\n$5\r\nhello\r\n$5\r\nworld\r\n
```

### 2. 返回结果格式

Redis 的返回结果类型分为以下五种:

1. 状态回复：在 `RESP` 中第一个字节为 `"+"`。如 `set`
2. 错误回复：在 `RESP` 中第一个字节为 `"-"`。如错误命令
3. 整数回复：在 `RESP` 中第一个字节为 `":"`。如 `incr`
4. 字符串回复：在 `RESP` 中第一个字节为 `"$"`。如 `get`
5. 多条字符串回复：在 `RESP` 中第一个字节为 `"*"`。如 `mget`

`redis-cli` 也是按照 RESP 进行结果解析的，所以看不到中间结果（例如看不到 `+` 号）。
`redis-cli.c` 源码对命令结果的解析结构如下:

```c
static sds cliFormatReplyTTY(redisReply *r, char *prefix) {
    sds out = sdsempty();
    switch (r->type) {
    case REDIS_REPLY_ERROR:
        // 处理错误回复
    case REDIS_REPLY_STATUS:
        // 处理状态回复
    case REDIS_REPLY_INTEGER:
        // 处理整数回复
    case REDIS_REPLY_STRING:
        // 处理字符串回复
    case REDIS_REPLY_NIL:
        // 处理空
    case REDIS_REPLY_ARRAY:
        // 处理多条字符串回复 return out;
}
```

为了看到 Redis 服务端返回的“真正”结果，可以使用 `nc`, `telnet` 命令、甚至写一个 socket
程序进行模拟。下面以 nc 命令进行演示，首先连接到 Redis:

```sh
nc 127.0.0.1 6379
# 返回结果为 `+OK`

sethx
# -ERR unknown command `sethx`, with args beginning with:

incr counter
# :1

get hello
# $5
# world

mset java jedis python redis-py
# +OK

mget java python
# *2
# $5
# jedis
# $8
# redis-py
```

⚠️ 无论是字符串回复还是多条字符串回复，如果有 `nil` 值，那么会返回 `$-1`。

例如，对一个不存在的键执行 `get` 操作，返回结果为:

```sh
get not_exist_key
# $-1
```

如果批量操作中包含一条为 `nil` 值的结果，那么返回结果如下:

```sh
mget hello not_exist_key java
# *3
# $5
# world
# $-1
# $5
# jedis
```

## 4.2 Java 客户端 Jedis

> <https://redis.io/docs/connect/clients/>

### 4.2.1 获取 Jedis

在 Java 中获取第三方开发包通常有两种方式:

1. 直接下载目标版本的 `Jedis-${version}.jar` 包加入到项目中。
2. 使用集成构建工具，例如 maven、gradle 等将 Jedis 目标版本的配置加入到项目中。

以 Maven 为例，在项目中加入下面的依赖:

```xml
<dependency>
    <groupId>redis.clients</groupId>
    <artifactId>jedis</artifactId>
    <version>2.8.2</version>
</dependency>
```

### 4.2.2 Jedis 的基本使用方法

```java
Jedis jedis = new Jedis("127.0.0.1", 6379);
jedis.set("hello", "world");
String value = jedis.get("hello");
```

还有一个包含了四个参数的构造函数是比较常用的:

```java
Jedis(final String host, final int port, final int connectionTimeout, final int soTimeout)
```

- `connectionTimeout`: 客户端连接超时。
- `soTimeout`: 客户端读写超时。

```java
String setResult = jedis.set("hello", "world");
String getResult = jedis.get("hello");
System.out.println(setResult);
// OK
System.out.println(getResult);
// world
```

在实际项目中推荐使用 `try catch finally` 的形式:

- 一方面可以在 Jedis 出现异常的时候，将异常捕获或者抛出;
- 另一个方面无论执行成功或者失败，将 Jedis 连接关闭掉

代码类似如下:

```java
Jedis jedis = null;
try {
    jedis = new Jedis("127.0.0.1", 6379);
    jedis.get("hello");
} catch (Exception e) {
    logger.error(e.getMessage(), e);
} finally {
    if (jedis != null) {
        jedis.close();
    }
}
```

```java
// 1.string
// 输出结果:OK
jedis.set("hello", "world");

// 输出结果:world
jedis.get("hello");

// 输出结果:1
jedis.incr("counter");

// 2.hash
jedis.hset("myhash", "f1", "v1");
jedis.hset("myhash", "f2", "v2");

// 输出结果:{f1=v1, f2=v2}
jedis.hgetAll("myhash");

// 3.list
jedis.rpush("mylist", "1");
jedis.rpush("mylist", "2");
jedis.rpush("mylist", "3");

// 输出结果:[1, 2, 3]
jedis.lrange("mylist", 0, -1);

// 4.set
jedis.sadd("myset", "a");
jedis.sadd("myset", "b");
jedis.sadd("myset", "a");

// 输出结果:[b, a]
jedis.smembers("myset");

// 5.zset
jedis.zadd("myzset", 99, "tom");
jedis.zadd("myzset", 66, "peter");
jedis.zadd("myzset", 33, "james");

// 输出结果:[[["james"],33.0], [["peter"],66.0], [["tom"],99.0]]
jedis.zrangeWithScores("myzset", 0, -1);
```

参数除了可以是字符串，还可以是字节数组:

```java
public String set(final String key, String value)
public String set(final byte[] key, final byte[] value)
public byte[] get(final byte[] key)
public String get(final String key)
```

有了这些 API 的支持，就可以将 Java 对象序列化为二进制，当应用需要获取 Java 对象时，使用
`get(final byte[]key)` 函数将字节数组取出，然后反序列化为 Java 对象即可。
和很多 NoSQL 数据库(例如 Memcache、Ehcache) 的客户端不同，Jedis 本身没有提供序列化的工具，也就是说开发者需要自己引入序列化工具。

序列化工具有很多，例如 XML、Json、谷歌的 Protobuf、Facebook 的 Thrift 等等。下面以
`protostuff` (Protobuf 的 Java 客户端)为例子进行说明。

#### 1. protostuff 的 Maven 依赖

```xml
<protostuff.version>1.0.11</protostuff.version>
<dependency>
    <groupId>com.dyuproject.protostuff</groupId>
    <artifactId>protostuff-runtime</artifactId>
    <version>${protostuff.version}</version>
</dependency>
<dependency>
    <groupId>com.dyuproject.protostuff</groupId>
    <artifactId>protostuff-core</artifactId>
    <version>${protostuff.version}</version>
</dependency>
```

#### 2. 定义实体类

```java
// 俱乐部
public class Club implements Serializable {
    private int id;
    private String name;
    private String info;
    private Date createDate;
    private int rank;
    // 省略了相应的 getter setter
}
```

#### 3. 使用 ProtostuffSerializer 序列化和反序列化

```java
package com.sohu.tv.serializer;
import com.dyuproject.protostuff.LinkedBuffer;
import com.dyuproject.protostuff.ProtostuffIOUtil;
import com.dyuproject.protostuff.Schema;
import com.dyuproject.protostuff.runtime.RuntimeSchema;
import java.util.concurrent.ConcurrentHashMap;

//序列化工具
public class ProtostuffSerializer {
    private Schema<Club> schema = RuntimeSchema.createFrom(Club.class);

    public byte[] serialize(final Club club) {
        final LinkedBuffer buffer = LinkedBuffer.allocate(LinkedBuffer.DEFAULT_ BUFFER_SIZE);
        try {
            return serializeInternal(club, schema, buffer);
        } catch (final Exception e) {
            throw new IllegalStateException(e.getMessage(), e);
        } finally {
            buffer.clear();
        }
    }

    public Club deserialize(final byte[] bytes) {
        try {
            Club club = deserializeInternal(bytes, schema.newMessage(), schema);
            if (club != null ) {
                return club;
            }
        } catch (final Exception e) {
            throw new IllegalStateException(e.getMessage(), e);
        }
        return null;
    }

    private <T> byte[] serializeInternal(final T source, final Schema<T> schema, final LinkedBuffer buffer) {
        return ProtostuffIOUtil.toByteArray(source, schema, buffer);
    }

    private <T> T deserializeInternal(final byte[] bytes, final T result, final Schema<T> schema) {
        ProtostuffIOUtil.mergeFrom(bytes, result, schema);
        return result;
    }
}
```

#### 4. 测试

生成序列化工具类:

```java
ProtostuffSerializer protostuffSerializer = new ProtostuffSerializer();
```

生成Jedis对象:

```java
Jedis jedis = new Jedis("127.0.0.1", 6379);
```

序列化:

```java
String key = "club:1";
// 定义实体对象
Club club = new Club(1, "AC", "米兰", new Date(), 1);
// 序列化
byte[] clubBtyes = protostuffSerializer.serialize(club);
jedis.set(key.getBytes(), clubBtyes);
```

反序列化:

```java
byte[] resultBtyes = jedis.get(key.getBytes());
// 反序列化[id=1, clubName=AC, clubInfo=米兰, createDate=Tue Sep 15 09:53:18 CST // 2015, rank=1]
Club resultClub = protostuffSerializer.deserialize(resultBtyes);
```

### 4.2.3 Jedis 连接池的使用方法

生产环境中一般使用连接池的方式对 Jedis 连接进行管理，所有 Jedis 对象预先放在池子中
(JedisPool)，每次要连接 Redis，只需要在池子中借用，之后再归还给连接池。

客户端连接 Redis 使用的是 TCP 协议，直连的方式每次需要建立 TCP 连接，而连接池的方式是预先初始化好
Jedis 连接，所以每次只需要从 Jedis 连接池借用已有连接，借用和归还操作是在本地进行的，只有少量的并发同步开销，远远小于新建 TCP 连接的开销。
另外直连的方式无法限制 Jedis 对象的个数，在极端情况下可能会造成连接泄露，而连接池的形式可以有效保护和控制资源的使用。

但是直连的方式也并不是一无是处，两种方式各自的优劣势：

- **直连**
  - 优点
    - 简单方便，适用于少量长期连接的场景
  - 缺点
    - 存在每次新建/关闭 TCP 连接的开销
    - 资源无法控制，可能会出现连接泄漏
    - Jedis 对象线程不安全
- **连接池**
  - 优点
    - 无需每次连接都生成 Jedis 对象，降低开销
    - 使用连接池的形式保护和控制资源的使用
  - 缺点
    - 使用相对麻烦，资源管理需要合理设计

Jedis 提供了 `JedisPool` 这个类作为 Jedis 的连接池，同时使用了 Apache 的通用对象池工具
`common-pool` 作为资源的管理工具。

#### 1. Jedis 连接池 (通常 JedisPool 是单例的)

```java
// common-pool 连接池配置，本例使用默认配置
GenericObjectPoolConfig poolConfig = new GenericObjectPoolConfig();

// 初始化Jedis连接池
JedisPool jedisPool = new JedisPool(poolConfig, "127.0.0.1", 6379);
```

#### 2. 从连接池直接获取获取 Jedis 对象

```java
Jedis jedis = null;
try {
    // 1. 从连接池获取jedis对象
    jedis = jedisPool.getResource();
    // 2. 执行操作
    jedis.get("hello");
} catch (Exception e) {
    logger.error(e.getMessage(),e);
} finally {
    if (jedis != null) {
        // 如果使用JedisPool，close操作不是关闭连接，代表归还连接池
        jedis.close();
    }
}
```

实际上 Jedis 的 `close()` 实现方式如下:

```java
public void close() {
    // 使用Jedis连接池
    if (dataSource != null) {
        if (client.isBroken()) {
            this.dataSource.returnBrokenResource(this);
        } else {
            this.dataSource.returnResource(this);
        }
    // 直连
    } else {
        client.close();
    }
}
```

- `dataSource != null` 代表使用的是连接池，所以 `jedis.close()` 代表归还连接给连接池，而且 Jedis 会判断当前连接是否已经断开。
- `dataSource == null` 代表直连，`jedis.close()` 代表关闭连接。

前面 `GenericObjectPoolConfig` 使用的是默认配置，它提供有很多参数，例如池子中最大连接数、最大空闲连接数、最小空闲连接数、连接活性检测等:

```java
GenericObjectPoolConfig poolConfig = new GenericObjectPoolConfig();

// 设置最大连接数为默认值的5倍
poolConfig.setMaxTotal(GenericObjectPoolConfig.DEFAULT_MAX_TOTAL * 5);

// 设置最大空闲连接数为默认值的3倍
poolConfig.setMaxIdle(GenericObjectPoolConfig.DEFAULT_MAX_IDLE * 3);

// 设置最小空闲连接数为默认值的2倍
poolConfig.setMinIdle(GenericObjectPoolConfig.DEFAULT_MIN_IDLE * 2);

// 设置开启jmx功能
poolConfig.setJmxEnabled(true);

// 设置连接池没有连接后客户端的最大等待时间(单位为毫秒)
poolConfig.setMaxWaitMillis(3000);
```

### 4.2.4 Redis 中 Pipeline 的使用方法

Redis 没有 `mdel` 方法，如果想实现这个功能，可以借助 Pipeline 来模拟批量删除，虽然不会像`mget` 和 `mset` 那样是一个原子命令，但是在绝大数场景下可以使用。

⚠️ 这里为了节省篇幅，没有写 `try catch finally`，没有关闭 `jedis`。

```java
public void mdel(List<String> keys) {
    Jedis jedis = new Jedis("127.0.0.1");

    // 1)生成pipeline对象
    Pipeline pipeline = jedis.pipelined();

    // 2)pipeline执行命令，注意此时命令并未真正执行
    for (String key : keys) {
        pipeline.del(key);
    }

    // 3)执行命令
    pipeline.sync();
}
```

除了 `pipeline.sync()`，还可以使用 `pipeline.syncAndReturnAll()` 将 pipeline
的命令结果返回：

```java
Jedis jedis = new Jedis("127.0.0.1");
Pipeline pipeline = jedis.pipelined();
pipeline.set("hello", "world");
pipeline.incr("counter");

List<Object> resultList = pipeline.syncAndReturnAll();
for (Object object : resultList) {
    System.out.println(object);
}
// OK
// 1
```

### 4.2.5 Jedis 的 Lua 脚本

Jedis 中执行 Lua 脚本和 redis-cli 十分类似，Jedis 提供了三个重要的函数实现 Lua 脚本的执行:

```java
Object eval(String script, int keyCount, String... params)
Object evalsha(String sha1, int keyCount, String... params)
String scriptLoad(String script)
```

以一个简单的 Lua 脚本为例

```lua
return redis.call('get',KEYS[1])
```

在 redis-cli 中执行上面的 Lua 脚本，方法如下:

```redis
127.0.0.1:6379> eval "return redis.call('get',KEYS[1])" 1 hello
"world"
```

在 Jedis 中执行，方法如下:

```java
String key = "hello";
String script = "return redis.call('get',KEYS[1])";
Object result = jedis.eval(script, 1, key);
// 打印结果为world
System.out.println(result)
```

`scriptLoad` 和 `evalsha` 函数要一起使用，首先使用 `scriptLoad` 将脚本加载到 Redis
中，代码如下:

```java
String scriptSha = jedis.scriptLoad(script);
```

`evalsha` 函数用来执行脚本的 SHA1 校验和，它需要三个参数:

```java
Stirng key = "hello";
Object result = jedis.evalsha(scriptSha, 1, key);
// 打印结果为world
System.out.println(result);
```

总体来说，Jedis 的使用重点注意以下几点即可:

1. Jedis 操作放在 `try catch finally` 里
2. 区分直连和连接池两种实现方式优缺点
3. `jedis.close()` 方法的两种实现方式
4. Jedis 依赖了 `common-pool`，有关 `common-pool` 的参数需要根据不同的使用场景，具体问题具体分析
5. 如果 `key` 和 `value` 涉及了字节数组，需要自己选择适合的序列化方法

## 4.3 Python 客户端 redis-py

### 4.3.1 获取 redis-py

> <https://redis.io/docs/connect/clients/python/>

### 4.3.2 redis-py 的基本使用方法

```py
import redis

client = redis.StrictRedis(host='127.0.0.1', port=6379)
key = "hello"

setResult = client.set(key, "python-redis")
print setResult
# True

value = client.get(key)
print "key:" + key + ", value:" + value
# key:hello, value:python-redis
```

```py
#1.string
#输出结果:True
client.set("hello","world")

#输出结果:world
client.get("hello")

#输出结果:1
client.incr("counter")

#2.hash
client.hset("myhash","f1","v1")
client.hset("myhash","f2","v2")

#输出结果:{'f1': 'v1', 'f2': 'v2'}
client.hgetall("myhash")

#3.list
client.rpush("mylist","1")
client.rpush("mylist","2")
client.rpush("mylist","3")

#输出结果:['1', '2', '3']
client.lrange("mylist", 0, -1)

#4.set
client.sadd("myset","a")
client.sadd("myset","b")
client.sadd("myset","a")

#输出结果:set(['a', 'b'])
client.smembers("myset")

#5.zset
client.zadd("myzset","99","tom")
client.zadd("myzset","66","peter")
client.zadd("myzset","33","james")

#输出结果:[('james', 33.0), ('peter', 66.0), ('tom', 99.0)]
client.zrange("myzset", 0, -1, withscores=True)
```

### 4.3.3 redis-py 中 Pipeline 的使用方法

```py
import redis

client = redis.StrictRedis(host='127.0.0.1', port=6379)
pipeline = client.pipeline(transaction=False)

# 将命令封装到Pipeline中，此时命令并没有真正执行:
pipeline.set("hello","world")
pipeline.incr("counter")

# 执行Pipeline:
#[True, 3]
result = pipeline.execute()
```

用 redis-py 的 Pipeline 实现 `mdel` 功能:

```py
import redis
def mdel(keys):
    client = redis.StrictRedis(host='127.0.0.1', port=6379)
    pipeline = client.pipeline(transaction=False)

    for key in keys:
        print pipeline.delete(key)
    return pipeline.execute();
```

### 4.3.4 redis-py 中的 Lua 脚本使用方法

`redis-py` 提供了三个重要的函数实现 Lua 脚本的执行:

```py
eval(String script, int keyCount, String... params)
script_load(String script)
evalsha(String sha1, int keyCount, String... params)
```

以一个最简单的 Lua 脚本为例进行说明:

```lua
return redis.call('get',KEYS[1])
```

```py
import redis

client = redis.StrictRedis(host='127.0.0.1', port=6379)
script = "return redis.call('get',KEYS[1])"
#输出结果为world
print client.eval(script,1,"hello")
```

`script_load` 和 `evalsha` 函数要一起使用，首先使用 `script_load` 将脚本加载到
Redis中，代码如下:

```py
import redis

client = redis.StrictRedis(host='127.0.0.1', port=6379)
script = "return redis.call('get',KEYS[1])"
scriptSha = client.script_load(script)
print client.evalsha(scriptSha, 1, "hello");
```

完整代码如下:

## 4.4 客户端管理

Redis 提供了客户端相关 API 对其状态进行监控和管理。

### 4.4.1 客户端 API

#### 1. client list

`client list` 命令能列出与 Redis 服务端相连的所有客户端连接信息

```redis
127.0.0.1:6379> client list
```

##### 1.1 客户端的四个标识属性

- `id`: 客户端连接的唯一标识，这个 `id` 随着 Redis 的连接自增，重启 Redis 后会重置为0。
- `addr`: 客户端连接的 ip 和端口。
- `fd`: socket 的文件描述符，与 lsof 命令结果中的 fd 是同一个，如果 `fd=-1` 代表当前客户端不是外部客户端，而是 Redis 内部的伪装客户端。
- `name`: 客户端的名字

##### 1.2 输入缓冲区: qbuf、qbuf-free

Redis为每个客户端分配了输入缓冲区，它的作用是将客户端发送的命令临时保存，同时Redis会从输入缓冲区拉取命令并执行，输入缓冲区为客户端发送命令到Redis执行命令提供了缓冲功能。

`client list` 中 `qbuf` 和 `qbuf-free` 分别代表这个缓冲区的总容量和剩余容量，Redis
没有相应的配置来规定每个缓冲区的大小，输入缓冲区会根据输入内容大小的不同动态调整，只是要求每个客户端缓冲区的大小不能超过 1G，超过后客户端将被关闭。下面是Redis源码中对于输入缓冲区的硬编码:

```c
/* Protocol and I/O related defines */
#define REDIS_MAX_QUERYBUF_LEN (1024*1024*1024) /* 1GB max query buffer. */
```

输入缓冲使用不当会产生两个问题:

- 一旦某个客户端的输入缓冲区超过1G，客户端将会被关闭。
- 输入缓冲区不受 `maxmemory` 控制，假设一个 Redis 实例设置了 `maxmemory` 为4G，已经存储了2G数据，但是如果此时输入缓冲区使用了 3G，已经超过 `maxmemory` 限制，可能会产生数据丢失、键值淘汰、OOM 等情况。
  - 执行效果如下:

    ```redis
    127.0.0.1:6390> info memory
    # Memory
    used_memory_human:5.00G
    ...
    maxmemory_human:4.00G
        ....
    ```

造成输入缓冲区过大的原因有哪些?

- 输入缓冲区过大主要是因为 Redis 的处理速度跟不上输入缓冲区的输入速度，并且每次进入输入缓冲区的命令包含了大量 bigkey，从而造成了输入缓冲区过大的情况。
- 还有一种情况就是 Redis 发生了阻塞，短期内不能处理命令，造成客户端输入的命令积压在了输入缓冲区。

如何快速发现和监控呢? 监控输入缓冲区异常的方法有两种:

- 通过定期执行 `client list` 命令，收集 `qbuf` 和 `qbuf-free` 找到异常的连接记录并分析，最终找到可能出问题的客户端。
- 通过 info 命令的 `info clients` 模块，找到最大的输入缓冲区，例如下面命令中，其中的 `client_biggest_input_buf` 代表最大的输入缓冲区，例如可以设置超过 10M 就进行报警:

    ```redis
    127.0.0.1:6379> info clients
    # Clients
    # connected_clients:1414
    # client_longest_output_list:0
    # client_biggest_input_buf:2097152
    # blocked_clients:0
    ```

这两种方法各有自己的优劣势：

- `client list`
  - 优点：能精准分析每个客户端来定位问题
  - 缺点：执行速度较慢，尤其是在连接数较多的情况下，频繁执行存在阻塞 Redis 的可能
- `info clients`
  - 优点：执行速度比 `client list` 快，分析过程较为简单
  - 缺点：不能精准定位到客户端；不能显示所有输入缓冲区的总量，只能显示最大量

💡 输入缓冲区问题出现概率比较低，但是也要做好防范，在开发中要减少 bigkey、减少 Redis 阻塞、合理设置监控报警。

##### 1.3 输出缓冲区: obl、oll、omem

Redis 为每个客户端分配了输出缓冲区，它的作用是保存命令执行的结果返回给客户端，为 Redis
和客户端交互返回结果提供缓冲。

与输入缓冲区不同的是，输出缓冲区的容量可以通过参数 `client-output-buffer-limit`
设置，并且输出缓冲区做得更加细致，按照客户端的不同分为三种:

- 普通客户端
- 发布订阅客户端
- slave 客户端

三种不同类型客户端的输出缓冲区对应的配置规则是: `client-output-buffer-limit <class> <hard limit> <soft limit> <soft seconds>`

- `<class>`: 客户端类型，分为三种
  - normal:普通客户端
  - slave:slave客户端，用于复制
  - pubsub:发布订阅客户端
- `<hard limit>`: 如果客户端使用的输出缓冲区大于 `<hard limit>`，客户端会被立即关闭。
- `<soft limit>` 和 `<soft seconds>`: 如果客户端使用的输出缓冲区超过了 `<soft limit>`
  并且持续了 `<soft limit>` 秒，客户端会被立即关闭。

Redis的默认配置是:

- `client-output-buffer-limit normal 0 0 0`
- `client-output-buffer-limit slave 256mb 64mb 60`
- `client-output-buffer-limit pubsub 32mb 8mb 60`

和输入缓冲区相同的是，输出缓冲区也不会受到 `maxmemory` 的限制，如果使用不当同样会造成
`maxmemory` 用满产生的数据丢失、键值淘汰、OOM 等情况。

实际上输出缓冲区由两部分组成:

- 固定缓冲区(16KB)：返回比较小的执行结果
- 动态缓冲区：返回比较大的结果，例如大的字符串、`hgetall`、`smembers` 命令的结果等

Redis 源码中 `redis.h` 的 `Client` 结构体可以看到两个缓冲区的实现细节:

```c
typedef struct Client {
    // 动态缓冲区列表
    list *reply;
    // 动态缓冲区列表的长度(对象个数)
    unsigned long reply_bytes;
    // 固定缓冲区已经使用的字节数

    int bufpos;
    // 字节数组作为固定缓冲区
    char buf[REDIS_REPLY_CHUNK_BYTES];
} redisClient;
```

固定缓冲区使用的是字节数组，动态缓冲区使用的是列表。当固定缓冲区存满后 Redis 会将新的返回结果存放在动态缓冲区的队列中，队列中的每个对象就是每个返回结果。

`client list` 中

- `obl` 代表固定缓冲区的长度
- `oll` 代表动态缓冲区列表的长度
- `omem` 代表使用的字节数

例如下面代表当前客户端的固定缓冲区的长度为 0，动态缓冲区有 4869 个对象，两个部分共使用了
133081288 字节 = 126M 内存:

```txr
id=7 addr=127.0.0.1:56358 fd=6 name= age=91 idle=0 flags=O db=0 sub=0 psub=0
multi=-1 qbuf=0 qbuf-free=0 obl=0 oll=4869 omem=133081288 events=rw cmd=monitor
```

监控输出缓冲区的方法依然有两种:

- 通过定期执行 `client list` 命令，收集 `obl`、`oll`、`omem` 找到异常的连接记录并分析，最终找到可能出问题的客户端。
- 通过 `info` 命令的 `info clients` 模块，找到输出缓冲区列表最大对象数，例如:

    ```redis
    127.0.0.1:6379> info clients
    # Clients
    # connected_clients:502
    # client_longest_output_list:4869
    # client_biggest_input_buf:0
    # blocked_clients:0
    ```

其中，`client_longest_output_list` 代表输出缓冲区列表最大对象数，这两种统计方法的优劣势和输入缓冲区是一样的。
相比于输入缓冲区，输出缓冲区出现异常的概率相对会比较大，那么如何预防呢？方法如下:

- 进行上述监控，设置阈值，超过阈值及时处理。
- 限制普通客户端输出缓冲区，把错误扼杀在摇篮中，例如如下设置: `client-output-buffer-limit normal 20mb 10mb 120`
- 适当增大 slave 输出缓冲区，如果 master 节点写入较大，slave 客户端的输出缓冲区可能会比较大，一旦 slave 客户端连接因为输出缓冲区溢出被 kill，会造成复制重连。
- 限制容易让输出缓冲区增大的命令，例如，高并发下的 monitor 命令就是一个危险的命令。
- 及时监控内存，一旦发现内存抖动频繁，可能就是输出缓冲区过大。

##### 1.4 客户端的存活状态

`client list` 中的 `age` 和 `idle` 分别代表当前客户端已经连接的时间和**最近一次**的空闲时间:

```txt
id=2232080 addr=10.16.xx.55:32886 fd=946 name= age=603382 idle=331060 flags=N
    db=0 sub=0 psub=0 multi=-1 qbuf=0 qbuf-free=0 obl=0 oll=0 omem=0 events=r
    cmd=get
```

例如上面这条记录代表当期客户端连接Redis的时间为603382秒，其中空闲了331060秒。

为了更加直观地描述 `age` 和 `idle`，下面用一个例子进行说明:

```java
String key = "hello";
Jedis jedis = new Jedis("127.0.0.1", 6379);
System.out.println(jedis.get(key));
TimeUnit.SECONDS.sleep(10);
System.out.println(jedis.ping());
TimeUnit.SECONDS.sleep(5);
jedis.close();
```

同时用 `client list` 命令来观察 `age` 和 `idle` 参数的相应变化。

##### 1.5 客户端的限制 maxclients 和 timeout

Redis 提供了 `maxclients` 参数限制最大客户端连接数，一旦连接数超过 `maxclients`，新的连接将被拒绝。`maxclients` 默认值是 `10000`，可以通过 `info clients` 来查询当前Redis的连接数:

```redis
127.0.0.1:6379> info clients
# Clients
# connected_clients:1414
...
```

可以通过 `config set maxclients` (`config rewrite` 持久化) 对最大客户端连接数进行动态设置:

```redis
127.0.0.1:6379> config get maxclients
1) "maxclients"
2) "10000"
 
127.0.0.1:6379> config set maxclients 50
OK

127.0.0.1:6379> config get maxclients
1) "maxclients"
2) "50"
```

一般来说 `maxclients=10000` 在大部分场景下已经绝对够用，但是某些情况由于业务方使用不当(例如没有主动关闭连接)可能存在大量 `idle` 连接， 无论是从网络连接的成本还是超过
`maxclients` 的后果来说都不是什么好事，因此 Redis 提供了 `timeout` (单位为秒)
参数来限制连接的最大空闲时间，一旦客户端连接的 `idle` 时间超过了 `timeout`，连接将会被关闭，例如设置 `timeout` 为 30 秒:

```redis
#Redis 默认的 timeout 是 0，也就是不会检测客户端的空闲
127.0.0.1:6379> config set timeout 30
OK
```

Jedis 示例:

```java
String key = "hello";
Jedis jedis = new Jedis("127.0.0.1", 6379);
System.out.println(jedis.get(key));
TimeUnit.SECONDS.sleep(31);
System.out.println(jedis.get(key));
TimeUnit.SECONDS.sleep(5);
jedis.close();
```

执行上述代码可以发现在执行完 sleep 之后，`client list` 中已经没有了 Jedis 的连接，也就是说
`timeout` 已经生效，将超过 30 秒空闲的连接关闭掉:

```redis
127.0.0.1:6379> client list
id=16 addr=10.7.40.98:63892 fd=6 name= age=19 idle=19 flags=N db=0 sub=0 psub=0
    multi=-1 qbuf=0 qbuf-free=0 obl=0 oll=0 omem=0 events=r cmd=get
# 超过timeout后，Jedis连接被关闭
redis-cli client list | grep “10.7.40.98”
# 结果为空
```

同时可以看到，`System.out.println(jedis.get(key));` 抛出了异常，因为此时客户端已经被关闭，所以抛出的异常是 `JedisConnectionException`。

如果将 Redis 的 `loglevel` 设置成 `debug` 级别，可以看到如下日志，也就是客户端被 Redis 关闭的日志:

```log
12885:M 26 Aug 08:46:40.085 - Closing idle client
```

Redis 源码中 `redis.c` 文件中 `clientsCronHandleTimeout` 函数就是针对 `timeout`
参数进行检验的，只不过在源码中 `timeout` 被赋值给了 `server.maxidletime`:

```c
int clientsCronHandleTimeout(redisClient *c) {
    // 当前时间
    time_t now = server.unixtime;
    // server.maxidletime就是参数timeout
    if (server.maxidletime &&
        // 很多客户端验证，这里就不占用篇幅，最重要的验证是下面空闲时间超过了maxidletime就会
        // 被关闭掉客户端
        (now - c->lastinteraction > server.maxidletime))
    {
        redisLog(REDIS_VERBOSE, "Closing idle client"); // 关闭客户端
        freeClient(c);
    }
}
```

Redis 的默认配置给出的 `timeout=0`，在这种情况下客户端基本不会出现上面的异常，这是基于对客户端开发的一种保护。
例如很多开发人员在使用 JedisPool 时不会对连接池对象做空闲检测和验证，如果设置了
`timeout>0`，可能就会出现上面的 Jedis 超时异常。

但是如果 Redis 的客户端使用不当或者客户端本身的一些问题，造成没有及时释放客户端连接，可能会造成大量的 idle 连接占据连接资源，导致超过 `maxclients`。

在实际开发和运维中，需要将 `timeout` 设置成大于 0，例如可以设置为 `300` 秒，同时在客户端使用上添加**空闲检测**和验证等措施，例如 JedisPool 使用 `common-pool` 的三个属性：

- `minEvictableIdleTimeMillis`
- `testWhileIdle`
- `timeBetweenEvictionRunsMillis`

##### 1.6 客户端类型

`client list` 中的 `flag` 是用于标识当前客户端的类型：

- N: normal
- M: master
- S: slave
- O: 正在执行 monitor 命令
- x: 正在执行事务
- b: 正在等待阻塞事件
- i: 正在等待 VM I/O (基本废弃不用)
- d: 一个受监视的键已被修改，EXEC 命令将失败
- u: 客户端未被阻塞
- c: 回复完整输出后，关闭连接
- A: 尽可能快地关闭连接

#### 2. client setName 和 client getName

```redis
client setName xx
client getName
```

`client setName` 用于给客户端设置名字，这样比较容易标识出客户端的来源，例如将当前客户端命名为 `test_client`:

```redis
127.0.0.1:6379> client setName test_client
# OK
127.0.0.1:6379> client list
id=55 addr=127.0.0.1:55604 fd=7 name=test_client age=23 idle=0 flags=N db=0
    sub=0 psub=0 multi=-1 qbuf=0 qbuf-free=32768 obl=0 oll=0 omem=0 events=r
    cmd=client
```

如果想直接查看当前客户端的 name，可以使用 `client getName` 命令:

```redis
127.0.0.1:6379> client getName
"test_client"
```

`client getName` 和 `setName` 命令可以做为标识客户端来源的一种方式，但通常来讲，在 Redis
只有一个应用方使用的情况下，IP 和端口作为标识会更加清晰。当多个应用方共同使用一个 Redis，那么此时 `client setName` 可以作为标识客户端的一个依据。

#### 3. client kill

```redis
client kill ip:port

127.0.0.1:6379> client kill 127.0.0.1:52343
OK
```

由于一些原因(例如设置timeout=0时产生的长时间idle的客户端)，需要手动杀掉客户端连接时，可以使用`client kill` 命令。

#### 4. client pause

```redis
client pause timeout(毫秒)
```

在此期间客户端连接将被阻塞。

例如在一个客户端执行:

```redis
127.0.0.1:6379> client pause 10000
```

在另一个客户端执行 `ping` 命令，发现整个 `ping` 命令执行了9.72秒:

```redis
127.0.0.1:6379> ping PONG
(9.72s)
```

该命令可以在如下场景起到作用:

- `client pause` 只对普通和发布订阅客户端有效，对于主从复制(从节点内部伪装了一个客户端)是无效的。所以此命令可以用来让主从复制保持一致。
- `client pause` 可以用一种可控的方式将客户端连接从一个 Redis 节点切换到另一个Redis节点。

#### 5. monitor

`monitor` 命令用于监控 Redis 正在执行的命令。但事实并非如此美好，每个客户端都有自己的输出缓冲区，既然 monitor 能监听到所有的命令，一旦 Redis 的并发量过大， monitor 客户端的输出缓冲会暴涨，可能瞬间会占用大量内存。

### 4.4.2 客户端相关配置

- `timeout`: 检测客户端空闲连接的超时时间，一旦 `idle` 时间达到了 timeout，客户端将会被关闭，如果设置为 `0` 就不进行检测。
- `maxclients`: 客户端最大连接数，这个参数会受到操作系统设置的限制
- `tcp-keepalive`: 检测 TCP 连接活性的周期，默认值为0，也就是不进行检测，如果需要设置，建议为 `60`，Redis 会每隔60秒对它创建的TCP连接进行活性检测，防止大量死连接占用系统资源。
- `tcp-backlog`: TCP 三次握手后，会将接受的连接放入队列中，tcp-backlog
  就是队列的大小，它在Redis中的默认值是 `511`。这个参数会受到操作系统的影响，例如在 Linux
  操作系统中，如果 `/proc/sys/net/core/somaxconn` 小于 `tcp-backlog`，那么在 Redis
  启动时会看到如下日志，并建议将 `/proc/sys/net/core/somaxconn` 设置更大。

  ```txt
  # WARNING: The TCP backlog setting of 511 cannot be enforced because /proc/ sys/net/core/somaxconn is set to the lower value of 128.
  ```

  修改方法:

  ```redis
  echo 511 > /proc/sys/net/core/somaxconn
  ```

### 4.4.3 客户端统计片段

```redis
127.0.0.1:6379> info clients
# Clients
connected_clients:1414
client_longest_output_list:0
client_biggest_input_buf:2097152
blocked_clients:0
```

- `connected_clients`: 当前Redis节点的客户端连接数，需要重点监控，一旦超过 `maxclients`，新的客户端连接将被拒绝。
- `client_longest_output_list`: 当前所有输出缓冲区中队列对象个数的最大值。
- `client_biggest_input_buf`: 当前所有输入缓冲区中占用的最大容量。
- `blocked_clients`: 正在执行阻塞命令(例如 `blpop`、`brpop`、 `brpoplpush` (deprecated)) 的客户端个数。

除此之外 `info stats` 中还包含了两个客户端相关的统计指标:

```redis
127.0.0.1:6379> info stats
# Stats
total_connections_received:80
...
rejected_connections:0
```

- `total_connections_received`: 自启动以来处理的客户端连接数总数。
- `rejected_connections`: 自启动以来拒绝的客户端连接数，需要重点监控。

## 4.5 客户端常见异常

### 1. 无法从连接池获取到连接

JedisPool 中的 Jedis 对象个数是有限的，默认是 `8` 个。如果有 `8` 个 Jedis
对象被占用，并且没有归还，此时调用者还要从 JedisPool 中借用 Jedis，就需要进行等待
(例如设置了 `maxWaitMillis>0`)，如果在 `maxWaitMillis` 时间内仍然无法获取到 Jedis
对象就会抛出异常 `redis.clients.jedis.exceptions.JedisConnectionException: Could not get a resource from the pool`:

还有一种情况是设置了 `blockWhenExhausted=false`，那么调用者发现池子中没有资源时，会立即抛出异常不进行等待。

造成连接池没有资源的原因非常多:

- `客户端`: 高并发下连接池设置过小，供不应求
- `客户端`: 没有正确使用连接池，比如没有进行释放:

    ```java
    GenericObjectPoolConfig poolConfig = new GenericObjectPoolConfig(); JedisPool jedisPool = new JedisPool(poolConfig, "127.0.0.1", 6379);
    // 借用8次连接，但是没有执行归还操作:
    for (int i = 0; i < 8; i++) {
        Jedis jedis = null;
        try {
            jedis = jedisPool.getResource();
            jedis.ping();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
    ```

- `客户端`: 存在慢查询操作，这些慢查询持有的 Jedis 对象归还速度比较慢，造成池子满了。
- `服务端`: 客户端是正常的，但是 Redis 服务端由于一些原因造成客户端命令执行过程的阻塞，也会使得客户端抛出这种异常。

### 2. 客户端读写超时

造成该异常的原因有以下几种:

- 读写超时间设置得过短
- 命令本身就比较慢
- 客户端与服务端网络不正常
- Redis 自身发生阻塞

### 3. 客户端连接超时

造成该异常的原因有以下几种:

- 连接超时设置得过短，设置办法: `jedis.getClient().setConnectionTimeout(time);`
- Redis 发生阻塞，造成 `tcp-backlog` 已满，造成新的连接失败。
- 客户端与服务端网络不正常。

### 4. 客户端缓冲区异常

原因可能有如下几种:

- 输出缓冲区满。例如将普通客户端的输出缓冲区设置为 `1M1M60`
  - `config set client-output-buffer-limit "normal 1048576 1048576 60 slave 268435456 67108864 60 pubsub 33554432 8388608 60"`
  - 如果使用 `get` 命令获取一个 bigkey(例如3M)，就会出现这个异常。
- 长时间闲置连接被服务端主动断开
- 不正常并发读写: Jedis 对象同时被多个线程并发操作，可能会出现上述异常。

### 5. Lua 脚本正在执行

如果 Redis 当前正在执行 Lua 脚本，并且超过了 `lua-time-limit`，此时 Jedis 调用 Redis
会收到下面的异常。此时只能等待或者 `script kill`。

### 6. Redis 正在加载持久化文件

### 7. Redis 使用的内存超过 maxmemory 配置

如果 Redis 的使用内存大于 `maxmemory` 的设置，Jedis 执行写操作时会收到异常，此时应该调整
`maxmemory` 并找到造成内存增长的原因:

`redis.clients.jedis.exceptions.JedisDataException: OOM command not allowed when used memory > 'maxmemory'.`

### 8. 客户端连接数过大

如果客户端连接数超过了 `maxclients`，新申请的连接会出现异常: `redis.clients.jedis.exceptions.JedisDataException: ERR max number of clients reached`

此时新的客户端连接执行任何命令，返回结果都是如下:

```redis
127.0.0.1:6379> get hello
(error) ERR max number of clients reached
```

此时无法执行 Redis 命令进行问题修复，一般来说可以从两个方面进行着手解决:

- `客户端`: 如果 `maxclients` 参数不是很小的话，应用方的客户端连接数基本不会超过`maxclients`，通常来看是由于应用方对于 Redis 客户端使用不当造成的。
  - 此时如果应用方是分布式结构的话，可以通过下线部分应用节点 (例如占用连接较多的节点)，使得
    Redis 的连接数先降下来。从而让绝大部分节点可以正常运行，此时再通过查找程序 bug
    或者调整 `maxclients` 进行问题修复。
- 服务端: 如果此时客户端无法处理，而当前 Redis 为高可用模式 (例如 Redis Sentinel 和 Redis Cluster)，可以考虑将当前 Redis 做故障转移。

此问题不存在确定的解决方式。

## 4.6 客户端案例分析

### 4.6.1 Redis 内存陡增

#### 1. 现象

- `服务端现象`: Redis 主节点内存陡增，几乎用满 `maxmemory`，而从节点内存并没有变化（正常情况下主从节点内存使用量基本相同）
- `客户端现象`: 客户端产生了 OOM(Out Of Memory) 异常，也就是 Redis 主节点使用的内存已经超过了 `maxmemory`
  的设置，无法写入新的数据: `redis.clients.jedis.exceptions.JedisDataException: OOM command not allowed when used memory > 'maxmemory'`

#### 2. 分析原因

从现象看，可能的原因有两个。

- 确实有大量写入，但是主从复制出现问题
  - 查询 Redis 复制的相关信息，以判断复制是否正常
  - 查询主从节点的键个数: `dbsize`
- 其他原因造成主节点内存使用过大:
  - 排查是否由客户端缓冲区造成主节点内存陡增，使用 `info clients` 命令查询相关信息

    ```redis
    127.0.0.1:6379> info clients
    # Clients
    connected_clients:1891
    client_longest_output_list:225698
    client_biggest_input_buf:0
    blocked_clients:0
    ```

    - 很明显输出缓冲区不太正常，最大的客户端输出缓冲区队列已经超过了 20 万个对象，需要通过
      `client list` 命令找到 `omem` 不正常的连接，一般来说大部分客户端的 `omem` 为 0
      (因为处理速度足够快)，于是执行如下代码，找到 `omem` 非零的客户端连接:

    ```sh
    redis-cli client list | grep -v "omem=0"
    ```

    - 找到了如下一条记录:

    ```redis
    id=7 addr=10.10.xx.78:56358 fd=6 name= age=91 idle=0 flags=O db=0 sub=0
        psub=0 multi=-1 qbuf=0 qbuf-free=0 obl=0 oll=224869 omem=2129300608
        events=rw cmd=monitor
    ```

已经很明显是因为有客户端在执行monitor命令造成的。

#### 3. 处理方法和后期处理

使用 `client kill` 命令杀掉这个连接，让其他客户端恢复正常写数据。

但是更为重要的是在日后如何及时发现和避免这种问题的发生，基本有三点:

- 从运维层面禁止 `monitor` 命令，例如使用 `rename-command` 命令重置 `monitor`
  命令为一个随机字符串。
  - 除此之外，如果 `monitor` 没有做 `rename-command`，也可以对 `monitor`
    命令进行相应的监控 (例如 `client list`)。
- 从开发层面培训，禁止在生产环境中使用 `monitor` 命令。
- 限制输出缓冲区的大小。
- 使用专业的 Redis 运维工具

### 4.6.2 客户端周期性的超时

#### 1. 超时现象

- `客户端现象`: 客户端出现大量超时，并且是周期性出现
- `服务端现象`: 服务端并没有明显的异常，只是有一些慢查询操作。

#### 2. 分析

- `网络原因`: 服务端和客户端之间的网络出现周期性问题
- `服务端`: 观察 Redis 日志统计
- `客户端`: 由于是周期性出现问题，可以和慢查询日志的历史记录对应一下时间，发现只要慢查询出现，客户端就会产生大量连接超时，两个时间点基本一致

最终找到问题是慢查询操作造成的：通过执行 `hlen` 发现有 200 万个元素，这种操作必然会造成阻塞，通过与开发方沟通了解到有个定时任务，每 5 分钟执行一次 `hgetall` 操作，导致慢查询。

以上问题之所以能够快速定位，得益于使用客户端监控工具把一些统计数据收集上来，才能更加直观地发现问题。

#### 3. 处理方法和后续处理

如何及时发现和避免这种问题的发生，基本有三点:

- 从运维层面，监控慢查询，一旦超过阀值，就发出报警。
- 从开发层面，加强对于Redis的理解，避免不正确的使用方式。
- 使用专业的Redis运维工具，例如 CacheCloud

## 4.7 本章重点回顾

1. RESP (REdis Serialization Protocol) 保证客户端与服务端的正常通信，是各种编程语言开发客户端的基础。
2. 要选择社区活跃客户端，在实际项目中使用稳定版本的客户端。
3. 区分直连和连接池的区别，在生产环境中，应该使用连接池。
4. `Jedis.close()` 在直连下是关闭连接，在连接池则是归还连接。
5. Jedis 客户端没有内置序列化，需要自己选用。
6. 客户端输入缓冲区不能配置，强制限制在1G之内，但是不会受到 `maxmemory` 限制。
7. 客户端输出缓冲区支持普通客户端、发布订阅客户端、复制客户端配置，同样会受到 `maxmemory`
   限制。
8. Redis 的 `timeout` 配置可以自动关闭闲置客户端，`tcp-keepalive` 参数可以周期性检查关闭无效TCP连接
9. `monitor` 命令虽然好用，但是在大并发下存在输出缓冲区暴涨的可能性。
10. `info clients` 帮助开发和运维人员找到客户端可能存在的问题。
11. 理解 Redis 通信原理和建立完善的监控系统对快速定位解决客户端常见问题非常有帮助。
