# Analysis of Algorithms

- [Analysis of Algorithms](#analysis-of-algorithms)
  - [Order of Growth](#order-of-growth)
    - [什么是时间复杂度与大 O](#什么是时间复杂度与大-o)
    - [不同数据规模的差异](#不同数据规模的差异)
    - [对数阶以什么为底](#对数阶以什么为底)
    - [一个例子](#一个例子)
  - [递归算法的时间复杂度](#递归算法的时间复杂度)
    - [题目：求 x 的 n 次方](#题目求-x-的-n-次方)
  - [References](#references)

## Order of Growth

> 增长量级，或者叫复杂度。
>
> The letter O was chosen by Bachmann to stand for Ordnung, meaning the order
> of approximation.

### 什么是时间复杂度与大 O

时间复杂度是一个函数，它定性描述该算法的运行时间。

假设算法的问题规模为 n，那么操作单元数量便用函数 $f(n)$ 来表示。
随着数据规模 n 的增大，算法执行时间的增长率和 $f(n)$
的增长率相同，这称为算法的渐近时间复杂度，简称时间复杂度，记为 $O(f(n))$。

- 大 O 是用来表示上界的，即最坏情况下的运行时间，通常忽略常数项；
- 在谈论算法复杂度时，通常指一般情况，而不是最坏情况，比如
  - 插入排序：
    - 一般情况：$O(n^2)$
    - 最好情况：$O(n)$
    - 最坏情况：$O(n^2)$
  - 快速排序：
    - 一般情况：$O(n\log n)$
    - 最好情况：$O(n\log n)$
    - 最坏情况：$O(n^2)$

### 不同数据规模的差异

- 选择算法时，除了考虑时间复杂度，还要考虑数据规模，如果数据规模很小，用 $O(n^2)$ 有可能比用
  $O(n)$ 更合适。
- 常见复杂度排序：
  - $O(1)$ 常数阶
  - $O(\log n)$ 对数阶
  - $O(n)$ 线性阶
  - $O(n\log n)$ 线性对数阶
  - $O(n^2)$ 平方阶
  - $O(n^3)$ 立方阶
  - $O(2^n)$ 指数阶级

### 对数阶以什么为底

$$
\log_2 n = \log_2 10 \times \log_{10}n
$$

$$
O(\log_2 n) = \log_2 10 \times O(\log_{10}n)
$$

一般化：

$$
O(\log_i n) = \log_i j \times O(\log_j n)
$$

忽略常数项：

$$
O(\log_i n) = O(\log_j n)
$$

因此，在大 O 场景下，对数具体是什么底并不重要。

### 一个例子

题目：找出 n 个字符串中相同的两个字符串（假设这里只有两个相同的字符串）。

如果是暴力枚举的话，时间复杂度是多少呢，是 $O(n^2)$ 么？

这里并不像 int 型数字比较那么简单，除了 $n^2$ 次的遍历次数外，字符串比较还要消耗 m
次操作（m 是字母串的长度），所以时间复杂度是 $O(m \times n \times n)$。

其他解题思路：

先排对 n 个字符串按字典序排序，排序后两个相同的字符串挨在一起，然后再遍历一遍 n 个字符串，这样就找到两个相同的字符串了。

快速排序时间复杂度为 $O(n\log n)$，依然要考虑字符串的长度是 m。快速排序每次的比较都要有 m
次的字符比较的操作，就是 $O(m \times n \times \log n)$。

之后再遍历这 n 个字符串找出两个相同的字符串，遍历的时候依然要比较字符串，所以总共的时间复杂度是
$O(m \times n \times \log n + n \times m)$。

对 $O(m \times n \times \log n + n \times m)$ 进行简化，得到
$O(m \times n \times (\log n + 1))$，再省略常数项，最后的时间复杂度是
$O(m \times n \times \log n)$。

$O(m \times n \times \log n)$ 显然优于 $O(m \times n \times n)$！

因此先把字符串集合排序再遍历一遍找到两个相同字符串的方法比直接暴力枚举的方式更快。

通过分析两种算法的时间复杂度，可以得到更好的结果。

⚠️ 这不是这道题目的最优解。

## 递归算法的时间复杂度

### 题目：求 x 的 n 次方

最直接的解法：$O(n)$

```c
int function1(int x, int n) {
  int result = 1;
  for (int i = 0; i < n; i++) {
    result = result * x;
  }
  return result;
}
```

$O(n)$ 的递归解法：

```c
int function2(int x, int n) {
  if (n == 0) {
    return 1;
  }
  return function2(x, n - 1) * x;
}
```

递归算法的时间复杂度 = **递归次数** * **每次递归中的操作次数**

进一步分解的递归算法：

$$
x^n = x^\frac n 2 \times x^\frac n 2
$$

```c
int function3(int x, int n) {
  if (n == 0) return 1;
  if (n == 1) return x;

  if (n % 2 == 1) {
    return function3(x, n / 2) * function3(x, n / 2) * x;
  }
  return function3(x, n / 2) * function3(x, n / 2);
}
```

递归层数为：$\log_2 n$

递归调用次数：$2 \times 2^{\log_2 n} - 2$

乘法次数：$2^{\log_2 n} - 1$

因此总的运算次数（算上除法次数）为：

$2 \times 2 \times 2^{\log_2 n} - 2 + (2^{\log_2 n} - 1)$

最后依然得到：$O(n)$

```c
int function4(int x, int n) {
  if (n == 0) return 1;
  if (n == 1) return x;

  int t = function4(x, n / 2);
  if (n % 2 == 1) {
    return t * t * x;
  }
  return t * t;
}
```

递归层数为：$\log_2 n$

递归调用次数：$\log_2 n$

乘法次数：$\log_2 n$

因此总的运算次数（算上除法次数）为：

$2 \times \log_2 n$

最后得到：$O(\log n)$

## References

- [x] 算法性能分析
  - [x] [时间复杂度分析](https://programmercarl.com/%E5%89%8D%E5%BA%8F/%E5%85%B3%E4%BA%8E%E6%97%B6%E9%97%B4%E5%A4%8D%E6%9D%82%E5%BA%A6%EF%BC%8C%E4%BD%A0%E4%B8%8D%E7%9F%A5%E9%81%93%E7%9A%84%E9%83%BD%E5%9C%A8%E8%BF%99%E9%87%8C%EF%BC%81.html)
  - [x] [算法为什么会超时](https://programmercarl.com/%E5%89%8D%E5%BA%8F/On%E7%9A%84%E7%AE%97%E6%B3%95%E5%B1%85%E7%84%B6%E8%B6%85%E6%97%B6%E4%BA%86%EF%BC%8C%E6%AD%A4%E6%97%B6%E7%9A%84n%E7%A9%B6%E7%AB%9F%E6%98%AF%E5%A4%9A%E5%A4%A7%EF%BC%9F.html)
  - [x] [递归算法的时间复杂度](https://programmercarl.com/%E5%89%8D%E5%BA%8F/%E9%80%9A%E8%BF%87%E4%B8%80%E9%81%93%E9%9D%A2%E8%AF%95%E9%A2%98%E7%9B%AE%EF%BC%8C%E8%AE%B2%E4%B8%80%E8%AE%B2%E9%80%92%E5%BD%92%E7%AE%97%E6%B3%95%E7%9A%84%E6%97%B6%E9%97%B4%E5%A4%8D%E6%9D%82%E5%BA%A6%EF%BC%81.html)
  - [ ] [算法性能分析系列一](https://programmercarl.com/%E5%91%A8%E6%80%BB%E7%BB%93/20201210%E5%A4%8D%E6%9D%82%E5%BA%A6%E5%88%86%E6%9E%90%E5%91%A8%E6%9C%AB%E6%80%BB%E7%BB%93.html)
  - [ ] 空间复杂度分析
  - [ ] 递归算法的性能分析
  - [ ] 代码的内存消耗
