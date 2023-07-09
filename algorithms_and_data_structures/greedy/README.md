# Greedy

- [Greedy](#greedy)
  - [理论基础](#理论基础)
    - [什么是贪心](#什么是贪心)
    - [什么时候用贪心](#什么时候用贪心)
    - [贪心算法一般的解题步骤](#贪心算法一般的解题步骤)
  - [References](#references)

## 理论基础

### 什么是贪心

贪心的本质是选择每一阶段的局部最优，从而达到全局最优。

例如，有一堆钞票，你可以拿走十张，如果想达到最大的金额，你要怎么拿？

指定每次拿最大的，最终结果就是拿走最大数额的钱。

每次拿最大的就是局部最优，最后拿走最大数额的钱就是推出全局最优。

### 什么时候用贪心

核心：如何能看出局部最优是否能推出整体最优呢？

一般数学证明有如下两种方法：

- 数学归纳法
- 反证法

### 贪心算法一般的解题步骤

1. 将问题分解为若干个子问题
2. 找出适合的贪心策略
3. 求解每一个子问题的最优解
4. 将局部最优解堆叠成全局最优解

实际上，只要想清楚**局部最优**是什么，如果能推导出全局最优，其实就够了。

## References

- 贪心算法
  - [x] [贪心算法理论基础](https://programmercarl.com/%E8%B4%AA%E5%BF%83%E7%AE%97%E6%B3%95%E7%90%86%E8%AE%BA%E5%9F%BA%E7%A1%80.html)
  - [x] [分发饼干](https://programmercarl.com/0455.%E5%88%86%E5%8F%91%E9%A5%BC%E5%B9%B2.html)
  - [x] [摆动序列](https://programmercarl.com/0376.%E6%91%86%E5%8A%A8%E5%BA%8F%E5%88%97.html)
  - [x] [最大子序和](https://programmercarl.com/0053.%E6%9C%80%E5%A4%A7%E5%AD%90%E5%BA%8F%E5%92%8C.html)
  - [x] [贪心周总结](https://programmercarl.com/%E5%91%A8%E6%80%BB%E7%BB%93/20201126%E8%B4%AA%E5%BF%83%E5%91%A8%E6%9C%AB%E6%80%BB%E7%BB%93.html)
  - [x] [买卖股票的最佳时机II](https://programmercarl.com/0122.%E4%B9%B0%E5%8D%96%E8%82%A1%E7%A5%A8%E7%9A%84%E6%9C%80%E4%BD%B3%E6%97%B6%E6%9C%BAII.html)
  - [x] [跳跃游戏](https://programmercarl.com/0055.%E8%B7%B3%E8%B7%83%E6%B8%B8%E6%88%8F.html)
  - [x] [跳跃游戏II](https://programmercarl.com/0045.%E8%B7%B3%E8%B7%83%E6%B8%B8%E6%88%8FII.html)
  - [x] [K次取反后最大化的数组和](https://programmercarl.com/1005.K%E6%AC%A1%E5%8F%96%E5%8F%8D%E5%90%8E%E6%9C%80%E5%A4%A7%E5%8C%96%E7%9A%84%E6%95%B0%E7%BB%84%E5%92%8C.html)
  - [x] [贪心周总结](https://programmercarl.com/%E5%91%A8%E6%80%BB%E7%BB%93/20201203%E8%B4%AA%E5%BF%83%E5%91%A8%E6%9C%AB%E6%80%BB%E7%BB%93.html)
  - [x] [加油站](https://programmercarl.com/0134.%E5%8A%A0%E6%B2%B9%E7%AB%99.html)
  - [x] [分发糖果](https://programmercarl.com/0135.%E5%88%86%E5%8F%91%E7%B3%96%E6%9E%9C.html)
  - [x] [柠檬水找零](https://programmercarl.com/0860.%E6%9F%A0%E6%AA%AC%E6%B0%B4%E6%89%BE%E9%9B%B6.html)
  - [ ] [根据身高重建队列](https://programmercarl.com/0406.%E6%A0%B9%E6%8D%AE%E8%BA%AB%E9%AB%98%E9%87%8D%E5%BB%BA%E9%98%9F%E5%88%97.html)
  - [ ] 贪心周总结
  - [ ] 根据身高重建队列（vector原理讲解）
  - [ ] 用最少数量的箭引爆气球
  - [ ] 无重叠区间
  - [ ] 划分字母区间
  - [ ] 合并区间
  - [ ] 贪心周总结
  - [ ] 单调递增的数字
  - [ ] 监控二叉树
  - [ ] 贪心算法总结篇
