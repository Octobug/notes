# Analysis of Algorithms

- [Analysis of Algorithms](#analysis-of-algorithms)
  - [Order of Growth](#order-of-growth)
    - [什么是时间复杂度与大 O](#什么是时间复杂度与大-o)
    - [不同数据规模的差异](#不同数据规模的差异)
    - [对数阶以什么为底](#对数阶以什么为底)
    - [一个例子](#一个例子)
  - [递归算法的时间复杂度](#递归算法的时间复杂度)
  - [References](#references)

## Order of Growth

> 增长量级，或者叫复杂度。
>
> The letter O was chosen by Bachmann to stand for Ordnung, meaning the order
> of approximation.

### 什么是时间复杂度与大 O

时间复杂度是一个函数，它定性描述该算法的运行时间。

假设算法的问题规模为 N，那么操作单元数量便用函数 f(N) 来表示。
随着数据规模 N 的增大，算法执行时间的增长率和 f(N)
的增长率相同，这称为算法的渐近时间复杂度，简称时间复杂度，记为 O(f(N))。

- 大 O 是用来表示上界的，即最坏情况下的运行时间，通常忽略常数项；
- 在谈论算法复杂度时，通常指一般情况，而不是最坏情况，比如
  - 插入排序：
    - 一般情况：O(N^2)
    - 最好情况：O(N)
    - 最坏情况：O(N^2)
  - 快速排序：
    - 一般情况：O(NlogN)
    - 最好情况：O(NlogN)
    - 最坏情况：O(N^2)

### 不同数据规模的差异

- 选择算法时，除了考虑时间复杂度，还要考虑数据规模，如果数据规模很小，用 O(N^2) 有可能比用
  O(N) 更合适。
- 常见复杂度排序：
  - O(1) 常数阶
  - O($\log N$) 对数阶
  - O(N) 线性阶
  - O($N\log N$) 线性对数阶
  - O($N^2$) 平方阶
  - O($N^3$) 立方阶
  - O($2^N$) 指数阶级

### 对数阶以什么为底

$$
\log_2 N = \log_2 10 \times \log_{10}N
$$

$$
O(\log_2 N) = \log_2 10 \times O(\log_{10}N)
$$

一般化：

$$
O(\log_i N) = \log_i j \times O(\log_j N)
$$

忽略常数项：

$$
O(\log_i N) = O(\log_j N)
$$

因此，在大 O 场景下，对数具体是什么底并不重要。

### 一个例子

题目：找出 N 个字符串中相同的两个字符串（假设这里只有两个相同的字符串）。

如果是暴力枚举的话，时间复杂度是多少呢，是 O($N^2$) 么？

这里并不像 int 型数字比较那么简单，除了 $N^2$ 次的遍历次数外，字符串比较依然要消耗 M
次操作（M 是字母串的长度），所以时间复杂度是 O($m \times n \times n$)。

其他解题思路：

先排对 N 个字符串按字典序排序，排序后两个相同的字符串挨在一起，然后再遍历一遍 N 个字符串，这样就找到两个相同的字符串了。

快速排序时间复杂度为 O($N\log N$)，依然要考虑字符串的长度是 M。快速排序每次的比较都要有 M
次的字符比较的操作，就是 O($M \times N \times \log N$)。

之后再遍历这 N 个字符串找出两个相同的字符串，遍历的时候依然要比较字符串，所以总共的时间复杂度是
O($M \times N \times \log N + N \times M$)。

对 O($M \times N \times \log N + N \times M$) 进行简化，得到
O$(M \times N \times (\log N + 1))$，再省略常数项，最后的时间复杂度是
$O(M \times N \times \log N)$。

O($M \times N \times \log N$) 显然优于 O($M \times N \times N$)！

因此先把字符串集合排序再遍历一遍找到两个相同字符串的方法比直接暴力枚举的方式更快。

通过分析两种算法的时间复杂度，可以得到更好的结果。

⚠️ 这不是这道题目的最优解。

## 递归算法的时间复杂度

## References

- [x] 算法性能分析
  - [x] [时间复杂度分析](https://programmercarl.com/%E5%89%8D%E5%BA%8F/%E5%85%B3%E4%BA%8E%E6%97%B6%E9%97%B4%E5%A4%8D%E6%9D%82%E5%BA%A6%EF%BC%8C%E4%BD%A0%E4%B8%8D%E7%9F%A5%E9%81%93%E7%9A%84%E9%83%BD%E5%9C%A8%E8%BF%99%E9%87%8C%EF%BC%81.html)
  - [x] [算法为什么会超时](https://programmercarl.com/%E5%89%8D%E5%BA%8F/On%E7%9A%84%E7%AE%97%E6%B3%95%E5%B1%85%E7%84%B6%E8%B6%85%E6%97%B6%E4%BA%86%EF%BC%8C%E6%AD%A4%E6%97%B6%E7%9A%84n%E7%A9%B6%E7%AB%9F%E6%98%AF%E5%A4%9A%E5%A4%A7%EF%BC%9F.html)
  - [ ] [递归算法的时间复杂度](https://programmercarl.com/%E5%89%8D%E5%BA%8F/%E9%80%9A%E8%BF%87%E4%B8%80%E9%81%93%E9%9D%A2%E8%AF%95%E9%A2%98%E7%9B%AE%EF%BC%8C%E8%AE%B2%E4%B8%80%E8%AE%B2%E9%80%92%E5%BD%92%E7%AE%97%E6%B3%95%E7%9A%84%E6%97%B6%E9%97%B4%E5%A4%8D%E6%9D%82%E5%BA%A6%EF%BC%81.html)
  - [ ] 算法性能分析系列一
  - [ ] 空间复杂度分析
  - [ ] 递归算法的性能分析
  - [ ] 代码的内存消耗
