# Protocol Buffers

> <https://protobuf.dev/>

- [Protocol Buffers](#protocol-buffers)
  - [简介](#简介)
  - [特色](#特色)
    - [性能好/效率高](#性能好效率高)
    - [代码生成机制](#代码生成机制)
    - [“向后兼容”和“向前兼容”](#向后兼容和向前兼容)
    - [支持多种编程语言](#支持多种编程语言)
  - [缺点](#缺点)
    - [应用不够广](#应用不够广)
    - [二进制格式导致可读性差](#二进制格式导致可读性差)
    - [缺乏自描述](#缺乏自描述)

## 简介

Protocol Buffers 和 XML, JSON 等标准类似，它把某种结构化的信息，以某种格式保存起来。
主要用于“数据存储、传输协议格式”等场合。

## 特色

### 性能好/效率高

Google 不用 XML 等现成协议的根本原因是，XML 这类现有协议性能不够好。

- 序列化/反序列化的时间开销；
- 存储空间开销；

### 代码生成机制

举例：有个电子商务系统（C++ 实现），其中的模块 A 需要发送大量订单信息给模块 B，通讯方式为
socket。

假设订单包括如下属性：

```txt
时间：time（用整数表示）
客户id：userid（用整数表示）
交易金额：price（用浮点数表示）
交易的描述：desc（用字符串表示）
```

如果使用 protobuf 实现，首先要写一个 proto 文件 (`Order.proto`)，在该文件中添加一个名为
`Order` 的 `message` 结构，用来描述通讯协议中的结构化数据。该文件的内容大致如下：

```proto
message Order
{
    required int32 time = 1;
    required int32 userid = 2;
    required float price = 3;
    optional string desc = 4;
}
```

然后，使用 protobuf 的编译器编译该 proto 文件，生成一个 C++ 的“订单包装类”。

然后就可以使用类似下面的代码来序列化/解析该订单包装类：

```cpp
// 发送方代码示例
Order order;
order.set_time(XXXX);
order.set_userid(123);
order.set_price(100.0f);
order.set_desc("a test order");

string sOrder;
order.SerailzeToString(&sOrder);
// 然后调用某种 socket 通讯库把序列化之后的字符串发送出去
// ......
```

```cpp
// 接收方代码示例
string sOrder;
// 先通过网络通讯库接收到数据，存放到某字符串 sOrder
// ......

Order order;
if(order.ParseFromString(sOrder))  // 解析该字符串
{
    cout << "userid:" << order.userid() << endl
         << "desc:" << order.desc() << endl;
}
else
{
    cerr << "parse error!" << endl;
}
```

有了这种代码生成机制，开发人员再也不用自己编写“协议解析代码”。

假如将来需求发生变更，要求给订单增加一个“状态”属性，那么只需要在 `Order.proto`
文件中增加一行代码。对于发送方，只要增加一行设置状态的代码；对于接收方只要增加一行读取状态的代码。

如果通讯双方使用不同的编程语言实现，使用这种机制可以有效确保两边的模块对于协议的处理是一致的。
从这个意义上讲，可以把 `proto` 文件看成是描述通讯协议的规格说明书。

### “向后兼容”和“向前兼容”

以上面的电商场景为例：

所谓向后兼容 (backward compatible)，就是指在模块 B 升级之后，它能够正确识别模块 A
发出的老版本的协议。

由于老版本没有“状态”这个属性，在扩充协议时，可以考虑把“状态”属性设置成非必填的，或者设置一个默认值。

所谓向前兼容 (forward compatible)，就是指在模块 A 升级了之后，模块 B 能够正常识别模块 A
发出的新版本协议。这时候，新增加的“状态”属性会被忽略。

### 支持多种编程语言

Google 官方发布的源代码中包含：

- C++
- C#
- Go
- Java
- Python
- ...

## 缺点

### 应用不够广

普及程度依然不及 XML, JSON 等。

### 二进制格式导致可读性差

为了提高性能，protobuf 采用了二进制格式编码。这直接导致其内容对人类没有可读性。
（为此 protobuf 提供了 `TextFormat` 这个工具类）。

当通讯双方出现问题，由于无法直接看出传输内容的对错，难以确认是哪一方出错。

### 缺乏自描述

其他协议比如 XML 是自描述的，而 protobuf 格式则不是。
一段二进制格式的协议内容，如果不配合相应的 proto 文件几乎无法读懂。
