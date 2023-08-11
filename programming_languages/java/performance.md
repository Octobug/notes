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
