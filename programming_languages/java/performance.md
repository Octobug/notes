# Performance

- [Performance](#performance)
  - [基本类型与引用类型](#基本类型与引用类型)
    - [Java 中的 8 种内置类型](#java-中的-8-种内置类型)
      - [基本类型的存储方式](#基本类型的存储方式)
    - [引用类型](#引用类型)
      - [引用类型的存储方式](#引用类型的存储方式)
    - [堆和栈的性能差异](#堆和栈的性能差异)
    - [为什么这么设计](#为什么这么设计)
      - [这种设计的弊端](#这种设计的弊端)
  - [字符串操作的性能问题](#字符串操作的性能问题)
    - [测试代码](#测试代码)
    - [Version 1](#version-1)
    - [Version 2](#version-2)
    - [Version 3](#version-3)
    - [Version 4](#version-4)
    - [Version 5](#version-5)
      - [5 个版本的总结](#5-个版本的总结)
      - [时间和空间的平衡](#时间和空间的平衡)
  - [引用类型常见注意点](#引用类型常见注意点)
    - [创建对象](#创建对象)
    - [引用对象之间的赋值与等价判断](#引用对象之间的赋值与等价判断)
    - [final 常量的问题](#final-常量的问题)
    - [传值还是传引用](#传值还是传引用)
  - [垃圾回收 Garbage Collection](#垃圾回收-garbage-collection)
    - [JVM 的内存空间](#jvm-的内存空间)
    - [垃圾回收机制](#垃圾回收机制)
      - [什么时候进行垃圾回收](#什么时候进行垃圾回收)
      - [谁负责垃圾回收](#谁负责垃圾回收)
      - [如何发现垃圾对象](#如何发现垃圾对象)
      - [如何清理/回收垃圾](#如何清理回收垃圾)
      - [分代](#分代)
    - [GC 对性能的影响](#gc-对性能的影响)
      - [造成当前运行线程的停顿](#造成当前运行线程的停顿)
      - [遍历对象引用的开销](#遍历对象引用的开销)
      - [清理和回收垃圾的开销](#清理和回收垃圾的开销)
    - [几种收集器](#几种收集器)
      - [两个性能指标](#两个性能指标)
      - [串行收集器 (Serial Collector)](#串行收集器-serial-collector)
      - [并行收集器 (Parallel Throughput Collector)](#并行收集器-parallel-throughput-collector)
      - [并发收集器 (Concurrent Low Pause Collector)](#并发收集器-concurrent-low-pause-collector)
      - [增量收集器 (Incremental Collector)](#增量收集器-incremental-collector)
    - [如何降低 GC 的影响](#如何降低-gc-的影响)
      - [尽量减少堆内存的使用](#尽量减少堆内存的使用)
      - [设置合适的堆内存大小](#设置合适的堆内存大小)
      - [吞吐量和停顿的取舍](#吞吐量和停顿的取舍)
  - [finalize 函数](#finalize-函数)
    - [finalize 函数的调用机制](#finalize-函数的调用机制)
      - [何时被调用](#何时被调用)
      - [由谁调用](#由谁调用)
    - [finalize 函数的误解和误用](#finalize-函数的误解和误用)
      - [把 finalize 理解为“析构函数”](#把-finalize-理解为析构函数)
      - [依靠 finalize 释放资源](#依靠-finalize-释放资源)
    - [使用 finalize 函数的注意事项](#使用-finalize-函数的注意事项)
      - [调用时间不确定——有资源浪费的风险](#调用时间不确定有资源浪费的风险)
      - [可能不被调用——有资源泄漏的风险](#可能不被调用有资源泄漏的风险)
      - [对象可能在 finalize 函数调用时复活](#对象可能在-finalize-函数调用时复活)
      - [要记得自己做异常捕获](#要记得自己做异常捕获)
      - [要小心线程安全](#要小心线程安全)
    - [finalize 的总结](#finalize-的总结)

## 基本类型与引用类型

### Java 中的 8 种内置类型

- boolean
- char
- byte
- short
- int
- long
- float
- double

#### 基本类型的存储方式

在函数中创建一个基本类型的变量时，比如：

```java
int n = 123;
```

变量 `n` 的值也是存储在栈（Stack）上的，这个语句不需要再从堆中申请内存。

### 引用类型

引用类型则是那些可以通过 `new` 来创建对象的类型（基本上都派生自 Object）。

#### 引用类型的存储方式

在函数中创建一个引用类型的对象时，比如：

```java
StringBuffer str = new StringBuffer();
```

该 `StringBuffer` 对象的内容是存储在堆（Heap）上的，需要申请堆内存。而变量 `str`
只不过是针对该 `StringBuffer` 对象的一个引用（或者叫地址）。

变量 `str` 的值（也就是 `StringBuffer` 对象的地址）是存储在栈上的。

### 堆和栈的性能差异

- 堆相对进程来说是全局的，能够被所有线程访问；
- 栈是线程局部的，只能本线程访问。

由于堆是所有线程共有的，从堆里面申请内存要进行相关的加锁操作，因此申请堆内存的复杂度和时间开销比栈要大很多；

从栈里面申请内存，虽然又简单又快，但是栈的大小有限，分配不了太多内存。

### 为什么这么设计

如果把各种东西都放置到栈中，显然不现实。一来栈是线程私有的（不便于共享），二来栈的大小是有限的，三来栈的结构也间接限制了它的用途。

那为什么不把所有东西都放置到堆里面？申请堆内存要办很多手续，太繁琐，影响性能。

把类型分为“基本类型”和“引用类型”，两者使用不同的创建方式。这种差异从 Java 语法上也可以看出来：
引用类型总是用 `new` 创建对象（某些单键对象/单例对象，表面上没用 `new`，但是在
`getInstance()` 内部也还是用 `new` 创建的）；而基本类型则不需要用 `new` 创建。

#### 这种设计的弊端

- 由于基本类型不是派生自 Object，因此不能算是纯对象。
- 由于基本类型不是派生自 Object，出于某些场合（比如容器类）的考虑，不得不为每个基本类型加上对应的包装类（比如 Integer、Byte 等），使得语言变得有点冗余。

使用 `new` 创建对象的开销是不小的。在程序中能避免就应该尽量避免。
另外，使用 `new` 创建对象，不光是创建时开销大，将来垃圾回收销毁对象也是有开销的。

## 字符串操作的性能问题

> 举例：过滤字符串
>
> 给定一个 `String` 对象，过滤掉除了数字以外的其它字符。
>
> 函数原型 `String filter(String str);`

### 测试代码

```java
class Test
{
  public static void main(String[] args)
  {
    if(args.length != 1)
      return;

    String str = "";
    long tBegin = System.currentTimeMillis();

    for(int i = 0; i < 1024 * 1024; i++)
      str = filterN(args[0]);

    long tEnd = System.currentTimeMillis();

    System.out.println(tEnd-tBegin);
    System.out.println(str);
  }
};
```

### Version 1

```java
private static String filter1(String strOrigin)
{
  String result = new String();
  for(int i=0; i<strOrigin.length(); i++)
  {
    if('0'<=strOrigin.charAt(i) && strOrigin.charAt(i)<='9')
    {
      result += strOrigin.charAt(i);
    }
  }
  return result;
}
```

### Version 2

在 Java 中，字符串拼接最好使用 `StringBuilder`。在 JDK 1.5 之前是 `StringBuffer`。

```java
private static String filter2(String strOrigin)
{
  StringBuffer result = new StringBuffer();
  for(int i = 0; i < strOrigin.length(); i++)
  {
    if('0' <= strOrigin.charAt(i) && strOrigin.charAt(i) <= '9')
      result.append(strOrigin.charAt(i));
  }
  return result.toString();
}
```

### Version 3

```java
private static String filter3(String strOrigin)
{
  StringBuffer result = new StringBuffer();
  int nLen = strOrigin.length();
  for(int i = 0; i < nLen; i++)
  {
    char ch = strOrigin.charAt(i);
    if('0' <= ch && ch <= '9')
      result.append(ch);
  }
  return result.toString();
}
```

先把 `strOrigin.charAt(i)` 赋值给 `char` 变量，节省了重复调用 `charAt()` 方法的开销；
另外把 `strOrigin.length()` 先保存为 `nLen`，也节省了重复调用 `length()` 的开销。

由于 `charAt()` 和 `length()` 的内部实现都挺简单的，所以提升的性能不太明显。

补充：在 JDK 1.6 上，`filter3` 和 `filter2` 的性能基本相同。可能是因为 JDK 1.6 在编译时已经进行相关优化。

### Version 4

```java
private static String filter4(String strOrigin)
{
  int nLen = strOrigin.length();
  StringBuffer result = new StringBuffer(nLen);
  for(int i = 0; i < nLen; i++)
  {
    char ch = strOrigin.charAt(i);
    if('0' <= ch && ch <= '9')
      result.append(ch);
  }
  return result.toString();
}
```

`filter4` 和 `filter3` 唯一差别在于调用了 `StringBuffer` 带参数的构造函数。
通过 `StringBuffer` 的构造函数设置初始的容量大小，可以有效避免 `append()`
追加字符时重新分配内存，从而提高性能。

### Version 5

```java
private static String filter5(String strOrigin)
{
  int nLen = strOrigin.length();
  char[] chArray = new char[nLen];
  int index = 0;
  for(int i = 0; i < nLen; i++)
  {
    char ch = strOrigin.charAt(i);
    if('0' <= ch && ch <= '9')
    {
      chArray[index] = ch;
      index++;
    }
  }
  return new String(chArray, 0, index);
}
```

`filter5` 既没有用 `String` 也没有用 `StringBuffer`，而是拿字符数组进行中间处理。

虽然 `filter5` 有一个字符数组的创建开销，但是相对于 `filter4` 来说，`StringBuffer`
的构造函数内部也会有字符数组的创建开销。
所以 `filter5` 比 `filter4` 还多节省了 `StringBuffer` 对象本身的创建开销。

由于 `StringBuffer` 是线程安全的（它的方法都是 `synchronized`），因此调用它的方法有一定的同步开销，而字符数组则没有。

#### 5 个版本的总结

`filter1` 和 `filter5` 的性能相差超过 10 倍。除了 `filter3` 相对于 `filter2`
是通过消除函数重复调用来提升性能，其它的几个版本都是通过节省内存分配，降低了时间开销。

#### 时间和空间的平衡

假如被过滤的字符串很大，并且数字字符的比例很低，`filter4` 和 `filter5` 这种方式就不太划算。

假如被处理的字符串中，绝大部分都只含有不到 `10%` 的数字字符，只有少数字符串包含较多的数字字符，这种情况应该怎么处理？

对于 `filter4` 来说，可以把 `new StringBuffer(nLen);` 修改为
`new StringBuffer(nLen/10);` 来节约空间开销。而 `filter5` 无法做到。

因此，该用 `filter4` 还是 `filter5`，要看具体情况。

## 引用类型常见注意点

### 创建对象

假设在函数中写了如下语句：

```java
StringBuffer str = new StringBuffer("Hello world");
```

这个语句包含了三个步骤：

1. `new` 操作符会在堆 (`Heap`) 里申请内存，把创建好的 `StringBuffer` 对象放进去。
2. `StringBuffer str` 声明了一个“指针”。这个指针本身存储在栈 (`Stack`) 上，用来指向某个
   `StringBuffer` 类型的对象。
3. 等于号 (`=`) 把两者关联起来，也就是把申请的内存的地址保存成 `str` 的值。

### 引用对象之间的赋值与等价判断

```java
StringBuffer str2 = str;
```

这个赋值语句把 `str` 的地址复制给 `str2`，`StringBuffer` 对象本身并没有复制。所以两个指针指向的是同一个对象。

```java
if(str2 == str)
```

上面这个语句只是判断两个指针的值（也就是对象的地址）是否相等，并不是判断“被指向的对象”是否内容相同。

### final 常量的问题

`final` 只是修饰指针的值（限定指针保存的地址不能变）。至于该指针指向的对象，内容可能会变可能不变。对于如下语句：

```java
final StringBuffer strConst = new StringBuffer();
```

可以修改它指向的对象的内容，比如：

```java
strConst.append("hello world");
```

但是不能修改它的值，比如：

```java
strConst = null;
```

### 传值还是传引用

对于如下语句可以有两种理解：

```java
System.out.println(str);
```

- 传进函数的是 `str` 这个指针，指针是一个地址的值，就是个整数。按照这种理解，就是传值。
- 传进去的是 `StringBuffer` 对象，按照这种理解，就是传引用方式。

## 垃圾回收 Garbage Collection

### JVM 的内存空间

在 Java 虚拟机规范中，提及如下几种内存空间：

- 栈内存 (`Stack`)：每个线程有私有的栈。
- 堆内存 (`Heap`)：所有线程公用。
- 方法区 (`Method Area`)：类似“进程代码段”，里面存放每个加载类的反射信息、类函数的代码、编译时常量等信息。
- 原生方法栈 (`Native Method Stack`)：主要用于 `JNI` 中的原生代码，平时很少涉及。

### 垃圾回收机制

Java 虚拟机规范中没有规定垃圾回收的相关细节。所以，不同的 JVM GC 行为可能会有一定差异。

#### 什么时候进行垃圾回收

一般情况下，当 JVM 发现堆内存比较紧张、不太够用时，它就会着手进行垃圾回收工作。
但是，JVM 进行 GC 的时间点是无法准确预知的。因为 GC 启动的时刻会受到各种运行环境因素的影响，随机性太大。

通过 JVM 的命令行参数 `-XX:+PrintGC` 可以把每次垃圾回收执行的相关信息打印出来。

另外，调用 `System.gc()` 只是建议 JVM 进行 GC。至于 JVM 到底什么时候执行 GC 不能保证。
所以，通常不建议自己手动调用 `System.gc()`。另外，使用 JVM 命令行参数
`-XX:+DisableExplicitGC` 可以让 `System.gc()` 不起作用。

#### 谁负责垃圾回收

JVM 有一个或多个专门的垃圾回收线程，由它们负责清理回收垃圾内存。

#### 如何发现垃圾对象

垃圾回收线程会从“根集 (`Root Set`)”开始进行对象引用的遍历。
“根集”就是正在运行的线程中，可以访问的引用变量的集合（比如所有线程当前函数的参数和局部变量、当前类的成员变量等等）。
垃圾回收线程先找出被根集直接引用的所有对象（集合1），然后再找出被集合1直接引用的所有对象（集合2），然后再找出被集合2直接引用的所有对象……
如此循环递归，直到把能遍历到的对象都遍历完。

凡是从“根集”通过这个遍历过程可以到达的对象，都称为可达对象或有效对象；
反之，则是不可达对象或失效对象，也就是垃圾。

#### 如何清理/回收垃圾

包括：

- 把垃圾内存重新变为可用内存
- 进行内存整理以消除内存碎片

#### 分代

早期的 JVM 没有采用分代技术，所有被 GC 管理的对象都存放在同一个堆里面。
这么做的缺点比较明显：每次进行 GC 都要遍历所有对象，开销很大。
而大部分的对象生命周期都很短，只有少数对象存在时间比较长；
在那些短命对象里，又只有少数对象占用的内存空间大；其它大量的短命对象都属于小对象。

因此，从 JDK 1.2 之后 JVM 开始使用分代垃圾回收 (Generational Garbage Collection)。
JVM 把 GC 的内存分为“年老代” (Tenured) 和“年轻代” (Nursery)、“持久代”
(Permanent，对应于 JVM 规范的“方法区”)。

大部分对象在刚创建时都属于“年轻代”。如果某对象经历了几轮 GC 还活着就把它移到“年老代”。
如果某个对象在创建时比较大，可能就直接被丢到年老代。

这种策略使得年轻代总是保存那些短命的小对象。在空间尺寸上，“年轻代”相对较小，而“年老代”相对较大。

有了分代技术，JVM 的 GC 也相应分为两种——主要收集 (Major Collection) 和次要收集
(Minor Collection)。“主要收集”同时清理年老代和年轻代，因此开销很大，不常进行；
“次要收集”仅仅清理年轻代，开销很小，经常进行。

### GC 对性能的影响

#### 造成当前运行线程的停顿

早期的 GC 比较弱，在它工作期间所有其它线程都被暂停。等到 GC 完成其它线程再继续运行。
所以，早期 JDK 的 GC 一旦开始工作，整个程序就会陷入假死状态，失去各种响应。

经过技术改进，从 JDK 1.4 开始 GC 已经比较精明。
在它执行期间，只会偶尔暂停一下其它线程的运行，从长时间假死变为暂时性停止。

#### 遍历对象引用的开销

#### 清理和回收垃圾的开销

包括复制内存块、更新对象引用等等。

### 几种收集器

#### 两个性能指标

- 吞吐量 (Throughput)：JVM 不用于 GC 的时间占总时间的比率，越大越好
- 停顿时间 (Pause Time)：越小越好

不同的收集器采用的收集策略不一样，以满足不同应用程序对这两个指标的权衡。

#### 串行收集器 (Serial Collector)

- 选项 `-XX:+UseSerialGC`

这种收集器是最传统的收集器。它使用单线程进行垃圾回收，比较适合单 CPU 机器以及小型应用。

#### 并行收集器 (Parallel Throughput Collector)

这种收集器使用多个线程进行垃圾回收以达到高吞吐量。
垃圾回收线程的数量通过选项 `-XX:ParallelGCThreads=n` 指定。
可以设置该数值以充分利用多 CPU 或多核。

- 使用选项 `-XX:+UseParallelGC` 时，它会针对年轻代使用多个垃圾回收线程，对年老代依然使用单个线程的串行方式。
- 使用选项 `-XX:+UseParallelOldGC` 时：它针对年轻代和年老代都使用多个垃圾回收线程的方式。

#### 并发收集器 (Concurrent Low Pause Collector)

- 选项 `-XX:+UseConcMarkSweepGC`

这种收集器优先保证程序的响应。它会尽量让垃圾回收线程和应用自身的线程同时运行，从而降低停顿时间。

#### 增量收集器 (Incremental Collector)

> JDK 已不维护这种方式。

### 如何降低 GC 的影响

#### 尽量减少堆内存的使用

GC 是针对堆内存的对象进行的，如果在程序中减少引用对象的分配，就可以减少堆内存分配，从而减少 GC
开销。

#### 设置合适的堆内存大小

JVM 的堆内存不能太大也不能太小。

- 如果堆内存太小，可能会导致 JVM 频繁进行垃圾回收而影响性能；
- 如果堆内存太大，以至于操作系统的大部分物理内存都被 JVM 霸占了，则可能会影响其它应用程序甚至操作系统本身的性能。
- 另外，年轻代的大小对于 GC 的性能也有明显影响。
  - 如果年轻代太小，可能导致次要收集很频繁；
  - 如果年轻代太大，导致次要收集的停顿很明显。

JVM 提供了若干和堆内存大小相关的命令行选项，具体如下：

| 选项             | 含义                          |
| ---------------- | ----------------------------- |
| `-Xms`           | 设置初始堆内存                |
| `-Xmx`           | 设置最大堆内存                |
| `-Xmn`           | 设置年轻代的大小              |
| `-XX:NewRatio=n` | 设置年轻代与年老代的比例为“n” |
| `-XX:NewSize=n`  | 设置年轻代大小为“n”           |

一般情况下，JVM 的默认参数值已经够用。如果需要自行调整，要做深入的性能对比测试。

#### 吞吐量和停顿的取舍

- 对于某些在后台的、运算密集型的应用，属于吞吐量优先。此时建议使用并行收集器。
- 对于涉及用户 UI 交互的、实时性要求比较高、程序需要快速响应的，属于优先减少停顿。此时建议使用并发收集器。

## finalize 函数

### finalize 函数的调用机制

#### 何时被调用

一般来说，要等到 JVM 开始进行垃圾回收的时候，它才有可能被调用。
而 JVM 进行垃圾回收的时间点是不确定的，依赖于各种运行时的环境因素。
正是由于 finalize 函数的调用时间点不确定，才导致存在某些缺点。

#### 由谁调用

常见的 JVM 会通过 GC 的垃圾回收线程调用 finalize 函数。
由于垃圾回收线程比较重要，为了防止 finalize 函数抛出的异常影响垃圾回收线程，
垃圾回收线程会在调用每一个 finalize 函数时进行 try/catch，如果捕获到异常，就直接丢弃，
然后接着处理下一个失效对象的 finalize 函数。

### finalize 函数的误解和误用

#### 把 finalize 理解为“析构函数”

在 C++ 中，析构函数是在对象离开作用域时立即被调用的。

由于 Java 的 finalize 函数和 C++ 的析构函数之间有许多关键性差异，把 finalize
当析构函数用会造成很多问题。

#### 依靠 finalize 释放资源

误用：比如通过 `finalize()` 完成类对象中某些资源的释放，如关闭数据库连接。

### 使用 finalize 函数的注意事项

#### 调用时间不确定——有资源浪费的风险

假如把某些稀缺资源放到 `finalize()` 中释放，可能会导致该稀缺资源再很久以后才被释放。

另外，某些类对象所携带的资源可能本身就很耗费内存，这些资源的延迟释放会造成很大的性能问题。

#### 可能不被调用——有资源泄漏的风险

在某些情况下，`finalize()` 根本不被调用。比如在 JVM 退出时，内存中那些对象的 `finalize`
函数可能就不会被调用。

一旦依赖 `finalize()` 来释放资源，就会有资源泄漏的风险。

#### 对象可能在 finalize 函数调用时复活

当某个对象完全没有引用，垃圾回收器才会调用该对象的 finalize 函数。
然而，万一有人在 `finalize()` 函数内部再把对象自身的引用 `this`
重新保存在某处，就相当于把对象复活了（因为重新有了引用，不再处于失效状态）。

为了防止这种情况，垃圾回收器在每次调用完 `finalize()` 之后再次检查对象是否还处于失效状态。

JVM 对于每一个类对象实例最多只会调用一次 `finalize()`。
所以，对于那些复活的对象，当它们真正失效时，`finalize()` 反而不会被调用了。

#### 要记得自己做异常捕获

`finalize()` 的调用机制是一旦有异常抛出到 `finalize()` 函数外面，会被垃圾回收线程捕获并丢弃。

也就是说，异常被直接忽略掉了。为了防止这种情况，凡是 `finalize()` 中有可能抛出异常的代码，
都得写上 try/catch 语句自己处理。

#### 要小心线程安全

由于调用 `finalize()` 的是垃圾回收线程，和自己代码的线程不是同一个线程；
甚至不同对象的 `finalize()` 可能会被不同的垃圾回收线程调用。
所以，当 `finalize()` 里面访问某些数据的时候，还得注意线程安全的问题。

### finalize 的总结

`finalize` 是比较鸡肋的特性，极容易被误用，而只对极少数程序员有用。
