# Dynamic Programming

- [Dynamic Programming](#dynamic-programming)
  - [理论基础](#理论基础)
    - [什么是动态规划](#什么是动态规划)
    - [动态规划的解题步骤](#动态规划的解题步骤)
    - [动态规划如何 debug](#动态规划如何-debug)
  - [背包问题](#背包问题)
    - [背包问题理论基础](#背包问题理论基础)
    - [01 背包](#01-背包)
    - [01 背包：二维 dp 数组](#01-背包二维-dp-数组)
      - [1. 确定 dp 数组及下标的含义](#1-确定-dp-数组及下标的含义)
      - [2. 确定递推公式](#2-确定递推公式)
      - [3. `dp` 数组如何初始化](#3-dp-数组如何初始化)
      - [4. 确定遍历顺序](#4-确定遍历顺序)
      - [5. 举例推导 `dp` 数组](#5-举例推导-dp-数组)
      - [c++ 测试代码](#c-测试代码)
    - [01 背包：滚动数组](#01-背包滚动数组)
      - [1. 确定 `dp` 数组的定义](#1-确定-dp-数组的定义)
      - [2. 一维 `dp`数组的递推公式](#2-一维-dp数组的递推公式)
      - [3. 一维 `dp` 数组如何初始化](#3-一维-dp-数组如何初始化)
      - [4. 一维 `dp` 数组遍历顺序](#4-一维-dp-数组遍历顺序)
      - [5. 举例推导一维 `dp` 数组](#5-举例推导一维-dp-数组)
      - [一维 `dp` 01 背包完整 C++ 测试代码](#一维-dp-01-背包完整-c-测试代码)
  - [完全背包基础理论](#完全背包基础理论)
    - [完全背包总结](#完全背包总结)
  - [多重背包理论基础](#多重背包理论基础)
  - [References](#references)

## 理论基础

### 什么是动态规划

**动态规划 (DP, Dynamic Programming)**，如果某一问题有很多重叠子问题，使用动态规划是最有效的。

动态规划中每一个状态一定是由上一个状态推导出来的，这一点就区分于贪心，贪心没有状态推导，而是从局部直接选最优的，

例如：有 `N` 件物品和一个最多能背重量为 `W` 的背包。第 `i` 件物品的重量是 `weight[i]`，
价值是 `value[i]`。每件物品只能用一次，求解将哪些物品装入背包里物品价值总和最大。

动态规划中 `dp[j]` 是由 `dp[j-weight[i]]` 推导出来的，然后取
`max(dp[j], dp[j - weight[i]] + value[i])`。

但如果是贪心呢，每次拿物品选一个最大的或者最小的就完事了，和上一个状态没有关系。

所以贪心解决不了动态规划的问题。

DP 的核心思想是当前状态是由前一个状态推导出来的，而贪心是局部直接选最优。

### 动态规划的解题步骤

五步曲：

1. 确定 `dp` 数组 (dp table) 以及下标的含义
2. 确定递推公式
3. `dp` 数组如何初始化
4. 确定遍历顺序
5. 举例推导 dp 数组

**为什么要先确定递推公式，再考虑初始化**？

因为一些情况是递推公式决定了 `dp` 数组要如何初始化。

### 动态规划如何 debug

找问题的最好方式就是把 `dp` 数组打印出来，看看究竟是不是按照自己思路推导的。

## 背包问题

### 背包问题理论基础

- 背包：最大容量 v
- 物品
  - 价值 w
  - 体积 v
  - 每个物品的数量
    - **混合背包**
      - **01 背包**：只有一个
        - 不选
        - 选一个
      - **完全背包**：无数个
        - 不选
        - 选几个
      - **多重背包**：不同的物品数量不同
    - **分组背包**：按组打包每组最多选一个

### 01 背包

标准的背包问题：有 `n` 件物品和一个最多能背重量为 `w` 的背包。
第 `i` 件物品的重量是 `weight[i]`，得到的价值是 `value[i]`。
每件物品只能用一次，求解将哪些物品装入背包里物品价值总和最大。

暴力解法：每一件物品只有两个状态，取或者不取。所以可以使用回溯法搜索出所有的情况，时间复杂度是
$O(2^n)$，这里的 `n` 表示物品数量。

暴力的解法是指数级别的时间复杂度，因此需要使用动态规划的解法来进行优化。

举例：

背包最大重量为 `4`。物品为：

|       | 重量 | 价值 |
| ----- | ---- | ---- |
| 物品0 | 1    | 15   |
| 物品1 | 3    | 20   |
| 物品2 | 4    | 30   |

问背包能背的物品最大价值是多少？

### 01 背包：二维 dp 数组

#### 1. 确定 dp 数组及下标的含义

使用二维数组，即 `dp[i][j]` 表示从下标为 `[0-i]` 的物品里任意取，放进容量为 `j` 的背包，价值总和最大是多少。

#### 2. 确定递推公式

`dp[i][j]` 的含义：从下标为 `[0-i]` 的物品里任意取，放进容量为 `j` 的背包，价值总和最大是多少。

那么可以有两个方向推出 `dp[i][j]`：

- **不放物品 `i`**：由 `dp[i - 1][j]` 推出，即背包容量为 `j`，里面不放物品 `i`
  的最大价值，此时 `dp[i][j]` 就是 `dp[i - 1][j]`。也就是当物品 `i` 的重量大于背包 `j`
  的重量时，物品 `i` 无法放进背包中，所以背包内的价值依然和前面相同。
- **放物品 `i`**：由 `dp[i - 1][j - weight[i]]` 推出，`dp[i - 1][j - weight[i]]`
  为背包容量为 `j - weight[i]` 的时候不放物品 `i` 的最大价值，那么
  `dp[i - 1][j - weight[i]] + value[i]`，就是背包放物品 `i` 得到的最大价值。

所以递推公式：`dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i])`

#### 3. `dp` 数组如何初始化

关于初始化，一定要和 `dp` 数组的定义吻合，否则到递推公式的时候会越来越乱。

首先从 `dp[i][j]` 的定义出发，如果背包容量 `j` 为 `0` 的话，即 `dp[i][0]`，无论是选取哪些物品，背包价值总和一定为 `0`。

由状态转移公式 `dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i])`
可以看出 `i` 的价值是由 `i-1` 推导出来，那么 `i` 为 `0` 的时候就一定要初始化。

`dp[0][j]`，即：`i` 为 `0`，存放编号 `0` 的物品的时候，各个容量的背包所能存放的最大价值。

- 当 `j < weight[0]` 时，`dp[0][j]` 应该是 `0`，因为背包容量比编号 `0` 的物品重量还小。
- 当 `j >= weight[0]` 时，`dp[0][j]` 应该是 `value[0]`，因为背包容量放足够放编号 `0`
  物品。

而其他位置的值都可以由左上方推导而来，因此初始化为任意值都行。

代码初始化如下：

```cpp
// 初始化 dp
vector<vector<int>> dp(weight.size(), vector<int>(bagweight + 1, 0));

for (int j = weight[0]; j <= bagweight; j++) {
  dp[0][j] = value[0];
}
```

#### 4. 确定遍历顺序

有两个遍历的维度：

- 物品
- 背包重量

先遍历物品还是先遍历背包重量呢？其实都可以，但是先遍历物品更好理解。

```cpp
// 先遍历物品，再遍历背包重量
for(int i = 1; i < weight.size(); i++) { // 遍历物品
  for(int j = 0; j <= bagweight; j++) { // 遍历背包容量
    if (j < weight[i])
      dp[i][j] = dp[i - 1][j];
    else
      dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
  }
}
```

```cpp
// 先遍历背包重量，再遍历物品
for(int j = 0; j <= bagweight; j++) { // 遍历背包容量
  for(int i = 1; i < weight.size(); i++) { // 遍历物品
    if (j < weight[i])
      dp[i][j] = dp[i - 1][j];
    else
      dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
  }
}
```

#### 5. 举例推导 `dp` 数组

#### c++ 测试代码

```cpp
void test_2_wei_bag_problem1() {
  vector<int> weight = {1, 3, 4};
  vector<int> value = {15, 20, 30};
  int bagweight = 4;

  // 二维数组
  vector<vector<int>> dp(weight.size(), vector<int>(bagweight + 1, 0));

  // 初始化
  for (int j = weight[0]; j <= bagweight; j++) {
    dp[0][j] = value[0];
  }

  // weight数组的大小 就是物品个数
  for(int i = 1; i < weight.size(); i++) { // 遍历物品
    for(int j = 0; j <= bagweight; j++) { // 遍历背包容量
      if (j < weight[i])
        dp[i][j] = dp[i - 1][j];
      else
        dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
    }
  }

  cout << dp[weight.size() - 1][bagweight] << endl;
}

int main() {
  test_2_wei_bag_problem1();
}
```

### 01 背包：滚动数组

在使用二维数组的时候，递推公式：
`dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i])`

可以发现，如果把 `dp[i - 1]` 那一层拷贝到 `dp[i]` 层上，表达式就变成：
`dp[i][j] = max(dp[i][j], dp[i][j - weight[i]] + value[i])`

与其把 `dp[i - 1]` 这一层拷贝到 `dp[i]` 上，不如只用一个一维数组，只用 `dp[j]`（一维数组，也就是一个滚动数组）。

这就是滚动数组的由来，需要满足的条件是上一层可以重复利用，直接拷贝到当前层。

`dp[i][j]` 表示从下标为 `[0-i]` 的物品里任意取，放进容量为 `j` 的背包，价值总和最大是多少。

#### 1. 确定 `dp` 数组的定义

在一维 `dp` 数组中，`dp[j]` 表示：容量为 `j` 的背包，所背的物品价值可以最大为 `dp[j]`。

#### 2. 一维 `dp`数组的递推公式

`dp[j]` 可以通过 `dp[j - weight[i]]` 推导出来，`dp[j - weight[i]]` 表示容量为
`j - weight[i]` 的背包所背的最大价值。

`dp[j - weight[i]] + value[i]` 表示容量为 `j - weight[i]` 的背包加上物品 `i` 的价值
`value[i]`。

此时 `dp[j]` 有两个选择，一个是取自己 `dp[j]` 相当于二维 `dp` 数组中的 `dp[i-1][j]`，
即不放物品 `i`，一个是取 `dp[j - weight[i]] + value[i]`，即放物品 `i`，取其中最大的。

所以递推公式为：

```cpp
dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
```

#### 3. 一维 `dp` 数组如何初始化

`dp[j]` 表示：容量为 `j` 的背包，所背的物品价值可以最大为 `dp[j]`，那么 `dp[0]` 就应该是
`0`，因为背包容量为 `0` 所背的物品的最大价值就是 `0`。

那么 `dp` 数组除了下标 `0` 的位置，初始为 `0`，其他下标应该初始化多少呢？

看一下递推公式：`dp[j] = max(dp[j], dp[j - weight[i]] + value[i])`

`dp` 数组在推导的时候一定是取价值最大的数，如果题目给的价值都是正整数那么非 `0` 下标都初始化为
`0` 就可以了。

#### 4. 一维 `dp` 数组遍历顺序

```cpp
for(int i = 0; i < weight.size(); i++) { // 遍历物品
  for(int j = bagWeight; j >= weight[i]; j--) { // 遍历背包容量
    dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
  }
}
```

二维 `dp` 遍历的时候，背包容量是从小到大，而一维 `dp` 遍历的时候，背包是从大到小。

倒序遍历是为了保证物品 `i` 只被放入一次。

举一个例子：物品 `0` 的重量 `weight[0] = 1`，价值 `value[0] = 15`

如果正序遍历：

`dp[1] = dp[1 - weight[0]] + value[0] = 15`

`dp[2] = dp[2 - weight[0]] + value[0] = 30`

此时 `dp[2]` 就已经是30了，意味着物品 `0`，被放入了两次，所以不能正序遍历。

为什么倒序遍历，就可以保证物品只放入一次呢？

倒序就是先算 `dp[2]`：

`dp[2] = dp[2 - weight[0]] + value[0] = 15`

`dp[1] = dp[1 - weight[0]] + value[0] = 15`

所以从后往前循环，每次取得状态不会和之前取得状态重合，这样每种物品就只取一次了。

为什么二维 `dp` 数组遍历的时候不用倒序？

因为对于二维 `dp`，`dp[i][j]` 都是通过上一层即 `dp[i - 1][j]` 计算而来，本层的
`dp[i][j]` 并不会被覆盖。

再来看看两个嵌套 `for` 循环的顺序，代码中是先遍历物品嵌套遍历背包容量，那可不可以先遍历背包容量嵌套遍历物品呢？

不可以！

因为一维 `dp` 的写法，背包容量一定是要倒序遍历，如果遍历背包容量放在上一层，那么每个 `dp[j]`
就只会放入一个物品，即：背包里只放入了一个物品。

倒序遍历的原因是，本质上还是一个对二维数组的遍历，并且右下角的值依赖上一层左上角的值，因此需要保证左边的值仍然是上一层的，从右向左覆盖。

#### 5. 举例推导一维 `dp` 数组

#### 一维 `dp` 01 背包完整 C++ 测试代码

```cpp
void test_1_wei_bag_problem() {
  vector<int> weight = {1, 3, 4};
  vector<int> value = {15, 20, 30};
  int bagWeight = 4;

  // 初始化
  vector<int> dp(bagWeight + 1, 0);
  for(int i = 0; i < weight.size(); i++) { // 遍历物品
    for(int j = bagWeight; j >= weight[i]; j--) { // 遍历背包容量
      dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
    }
  }
  cout << dp[bagWeight] << endl;
}

int main() {
  test_1_wei_bag_problem();
}
```

## 完全背包基础理论

有 `N` 件物品和一个最多能背重量为 `W` 的背包。第 `i` 件物品的重量是 `weight[i]`，
得到的价值是 `value[i]`。每件物品都有无限个（也就是可以放入背包多次），
求解将哪些物品装入背包里物品价值总和最大。

完全背包和 01 背包问题唯一不同的地方就是，每种物品有无限件。

例子：

背包最大重量为 `4`。物品为：

|        | 重量 | 价值 |
| ------ | ---- | ---- |
| 物品 0 | 1    | 15   |
| 物品 1 | 3    | 20   |
| 物品 2 | 4    | 30   |

问背包能背的物品最大价值是多少？

01 背包和完全背包唯一的不同体现在遍历顺序上。首先再回顾一下 01 背包的核心代码：

```cpp
for(int i = 0; i < weight.size(); i++) { // 遍历物品
  for(int j = bagWeight; j >= weight[i]; j--) { // 遍历背包容量
    dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
  }
}
```

01 背包内嵌的循环是从大到小遍历，以保证每个物品仅被添加一次。
而完全背包的物品是可以添加多次的，所以要从小到大去遍历，即：

```cpp
// 先遍历物品，再遍历背包
for(int i = 0; i < weight.size(); i++) { // 遍历物品
  for(int j = weight[i]; j <= bagWeight; j++) { // 遍历背包容量
    dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
  }
}
```

其实还有一个很重要的问题，为什么遍历物品在外层循环，遍历背包容量在内层循环？

**在完全背包中，对于一维 `dp` 数组来说，其实两个 `for` 循环嵌套顺序是无所谓的**。
因为 `dp[j]` 是根据下标 `j` 之前所对应的 `dp[j]` 计算出来的。只要保证下标 `j`之前的
`dp[j]` 都是经过计算的就可以了。

```cpp
// 先遍历背包，再遍历物品
for(int j = 0; j <= bagWeight; j++) { // 遍历背包容量
  for(int i = 0; i < weight.size(); i++) { // 遍历物品
    if (j - weight[i] >= 0)
      dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
  }
}
```

完整的 C++ 测试代码如下：

```cpp
// 先遍历物品，再遍历背包
void test_CompletePack() {
  vector<int> weight = {1, 3, 4};
  vector<int> value = {15, 20, 30};
  int bagWeight = 4;
  vector<int> dp(bagWeight + 1, 0);
  for(int i = 0; i < weight.size(); i++) { // 遍历物品
    for(int j = weight[i]; j <= bagWeight; j++) { // 遍历背包容量
      dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
    }
  }
  cout << dp[bagWeight] << endl;
}

int main() {
  test_CompletePack();
}
```

```cpp
// 先遍历背包，再遍历物品
void test_CompletePack() {
  vector<int> weight = {1, 3, 4};
  vector<int> value = {15, 20, 30};
  int bagWeight = 4;

  vector<int> dp(bagWeight + 1, 0);

  for(int j = 0; j <= bagWeight; j++) { // 遍历背包容量
    for(int i = 0; i < weight.size(); i++) { // 遍历物品
      if (j - weight[i] >= 0)
        dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
    }
  }
  cout << dp[bagWeight] << endl;
}

int main() {
  test_CompletePack();
}
```

### 完全背包总结

对于纯完全背包问题，其 `for` 循环的先后循环是可以颠倒的。

但如果题目稍稍有点变化，可能就会体现在遍历顺序上。

如果问装满背包有几种方式的话，那么两个 `for` 循环的先后顺序就有很大区别。

- 如果是求组合数，就是外层 `for` 循环遍历物品，内层 `for` 遍历背包。
- 如果是求排列数，就是外层 `for` 遍历背包，内层 `for` 循环遍历物品。

## 多重背包理论基础

有 `N` 种物品和一个容量为 `V` 的背包。第 `i` 种物品最多有 $M_i$ 件可用，每件耗费的空间是
$C_i$ ，价值是 $W_i$。
求解将哪些物品装入背包可使这些物品的耗费的空间总和不超过背包容量，且价值总和最大。

多重背包和 01 背包非常像：每件物品最多有 $M_i$ 件可用，把 $M_i$ 件摊开，其实就是一个 01
背包问题了。

例如：背包最大重量为 `10`，物品为：

|        | 重量 | 价值 | 数量 |
| ------ | ---- | ---- | ---- |
| 物品 0 | 1    | 15   | 2    |
| 物品 1 | 3    | 20   | 3    |
| 物品 2 | 4    | 30   | 2    |

问背包能背的物品最大价值是多少？这和以下情况其实是等价的。

|        | 重量 | 价值 | 数量 |
| ------ | ---- | ---- | ---- |
| 物品 0 | 1    | 15   | 1    |
| 物品 0 | 1    | 15   | 1    |
| 物品 1 | 3    | 20   | 1    |
| 物品 1 | 3    | 20   | 1    |
| 物品 1 | 3    | 20   | 1    |
| 物品 2 | 4    | 30   | 1    |
| 物品 2 | 4    | 30   | 1    |

这就转成一个 01 背包问题了，每个物品只用一次。

```cpp
void test_multi_pack() {
  vector<int> weight = {1, 3, 4};
  vector<int> value = {15, 20, 30};
  vector<int> nums = {2, 3, 2};
  int bagWeight = 10;

  for (int i = 0; i < nums.size(); i++) {
    while (nums[i] > 1) { // nums[i]保留到1，把其他物品都展开
      weight.push_back(weight[i]);
      value.push_back(value[i]);
      nums[i]--;
    }
  }

  vector<int> dp(bagWeight + 1, 0);
  for(int i = 0; i < weight.size(); i++) { // 遍历物品
    for(int j = bagWeight; j >= weight[i]; j--) { // 遍历背包容量
      dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
    }
    for (int j = 0; j <= bagWeight; j++) {
      cout << dp[j] << " ";
    }
    cout << endl;
  }
  cout << dp[bagWeight] << endl;
}

int main() {
  test_multi_pack();
}
```

- 时间复杂度：$O(m × n × k)$
  - `m`: 物品种类个数
  - `n`: 背包容量
  - `k`: 单类物品数量

## References

- 动态规划
  - 01~10
  - [x] [动态规划理论基础](https://programmercarl.com/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92%E7%90%86%E8%AE%BA%E5%9F%BA%E7%A1%80.html)
  - [x] [斐波那契数](https://programmercarl.com/0509.%E6%96%90%E6%B3%A2%E9%82%A3%E5%A5%91%E6%95%B0.html)
  - [x] [爬楼梯](https://programmercarl.com/0070.%E7%88%AC%E6%A5%BC%E6%A2%AF.html)
  - [x] [使用最小花费爬楼梯](https://programmercarl.com/0746.%E4%BD%BF%E7%94%A8%E6%9C%80%E5%B0%8F%E8%8A%B1%E8%B4%B9%E7%88%AC%E6%A5%BC%E6%A2%AF.html)
  - [x] [动规周总结](https://programmercarl.com/%E5%91%A8%E6%80%BB%E7%BB%93/20210107%E5%8A%A8%E8%A7%84%E5%91%A8%E6%9C%AB%E6%80%BB%E7%BB%93.html)
  - [x] [不同路径](https://programmercarl.com/0062.%E4%B8%8D%E5%90%8C%E8%B7%AF%E5%BE%84.html)
  - [x] [不同路径II](https://programmercarl.com/0063.%E4%B8%8D%E5%90%8C%E8%B7%AF%E5%BE%84II.html)
  - [x] [整数拆分](https://programmercarl.com/0343.%E6%95%B4%E6%95%B0%E6%8B%86%E5%88%86.html)
  - [x] [不同的二叉搜索树](https://programmercarl.com/0096.%E4%B8%8D%E5%90%8C%E7%9A%84%E4%BA%8C%E5%8F%89%E6%90%9C%E7%B4%A2%E6%A0%91.html)
  - [x] [动规周总结](https://programmercarl.com/%E5%91%A8%E6%80%BB%E7%BB%93/20210114%E5%8A%A8%E8%A7%84%E5%91%A8%E6%9C%AB%E6%80%BB%E7%BB%93.html)
  - 11~20
  - [x] [0-1背包理论基础（一）](https://programmercarl.com/%E8%83%8C%E5%8C%85%E7%90%86%E8%AE%BA%E5%9F%BA%E7%A1%8001%E8%83%8C%E5%8C%85-1.html)
  - [x] [0-1背包理论基础（二）](https://programmercarl.com/%E8%83%8C%E5%8C%85%E7%90%86%E8%AE%BA%E5%9F%BA%E7%A1%8001%E8%83%8C%E5%8C%85-2.html)
  - [x] [分割等和子集](https://programmercarl.com/0416.%E5%88%86%E5%89%B2%E7%AD%89%E5%92%8C%E5%AD%90%E9%9B%86.html)
  - [x] [最后一块石头的重量II](https://programmercarl.com/1049.%E6%9C%80%E5%90%8E%E4%B8%80%E5%9D%97%E7%9F%B3%E5%A4%B4%E7%9A%84%E9%87%8D%E9%87%8FII.html)
  - [x] [动规周总结](https://programmercarl.com/%E5%91%A8%E6%80%BB%E7%BB%93/20210121%E5%8A%A8%E8%A7%84%E5%91%A8%E6%9C%AB%E6%80%BB%E7%BB%93.html)
  - [x] [目标和](https://programmercarl.com/0494.%E7%9B%AE%E6%A0%87%E5%92%8C.html)
  - [x] [一和零](https://programmercarl.com/0474.%E4%B8%80%E5%92%8C%E9%9B%B6.html)
  - [x] [完全背包理论基础](https://programmercarl.com/%E8%83%8C%E5%8C%85%E9%97%AE%E9%A2%98%E7%90%86%E8%AE%BA%E5%9F%BA%E7%A1%80%E5%AE%8C%E5%85%A8%E8%83%8C%E5%8C%85.html)
  - [x] [零钱兑换II](https://programmercarl.com/0518.%E9%9B%B6%E9%92%B1%E5%85%91%E6%8D%A2II.html)
  - [x] [动规周总结](https://programmercarl.com/%E5%91%A8%E6%80%BB%E7%BB%93/20210128%E5%8A%A8%E8%A7%84%E5%91%A8%E6%9C%AB%E6%80%BB%E7%BB%93.html)
  - 21~30
  - [x] [组合总和Ⅳ](https://programmercarl.com/0377.%E7%BB%84%E5%90%88%E6%80%BB%E5%92%8C%E2%85%A3.html)
  - [x] [爬楼梯（进阶版）](https://programmercarl.com/0070.%E7%88%AC%E6%A5%BC%E6%A2%AF%E5%AE%8C%E5%85%A8%E8%83%8C%E5%8C%85%E7%89%88%E6%9C%AC.html)
  - [x] [零钱兑换](https://programmercarl.com/0322.%E9%9B%B6%E9%92%B1%E5%85%91%E6%8D%A2.html)
  - [x] [完全平方数](https://programmercarl.com/0279.%E5%AE%8C%E5%85%A8%E5%B9%B3%E6%96%B9%E6%95%B0.html)
  - [x] [动规周总结](https://programmercarl.com/%E5%91%A8%E6%80%BB%E7%BB%93/20210204%E5%8A%A8%E8%A7%84%E5%91%A8%E6%9C%AB%E6%80%BB%E7%BB%93.html)
  - [x] [单词拆分](https://programmercarl.com/0139.%E5%8D%95%E8%AF%8D%E6%8B%86%E5%88%86.html)
  - [x] [多重背包理论基础](https://programmercarl.com/%E8%83%8C%E5%8C%85%E9%97%AE%E9%A2%98%E7%90%86%E8%AE%BA%E5%9F%BA%E7%A1%80%E5%A4%9A%E9%87%8D%E8%83%8C%E5%8C%85.html)
  - [x] [背包问题总结篇](https://programmercarl.com/%E8%83%8C%E5%8C%85%E6%80%BB%E7%BB%93%E7%AF%87.html)
  - [x] [打家劫舍](https://programmercarl.com/0198.%E6%89%93%E5%AE%B6%E5%8A%AB%E8%88%8D.html)
  - [x] [打家劫舍II](https://programmercarl.com/0213.%E6%89%93%E5%AE%B6%E5%8A%AB%E8%88%8DII.html)
  - 31~40
  - [x] [打家劫舍III](https://programmercarl.com/0337.%E6%89%93%E5%AE%B6%E5%8A%AB%E8%88%8DIII.html)
  - [x] [买卖股票的最佳时机](https://programmercarl.com/0121.%E4%B9%B0%E5%8D%96%E8%82%A1%E7%A5%A8%E7%9A%84%E6%9C%80%E4%BD%B3%E6%97%B6%E6%9C%BA.html)
  - [x] [动规周总结](https://programmercarl.com/%E5%91%A8%E6%80%BB%E7%BB%93/20210225%E5%8A%A8%E8%A7%84%E5%91%A8%E6%9C%AB%E6%80%BB%E7%BB%93.html)
  - [x] [买卖股票的最佳时机II](https://programmercarl.com/0122.%E4%B9%B0%E5%8D%96%E8%82%A1%E7%A5%A8%E7%9A%84%E6%9C%80%E4%BD%B3%E6%97%B6%E6%9C%BAII%EF%BC%88%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92%EF%BC%89.html)
  - [x] [买卖股票的最佳时机III](https://programmercarl.com/0123.%E4%B9%B0%E5%8D%96%E8%82%A1%E7%A5%A8%E7%9A%84%E6%9C%80%E4%BD%B3%E6%97%B6%E6%9C%BAIII.html)
  - [x] [买卖股票的最佳时机IV](https://programmercarl.com/0188.%E4%B9%B0%E5%8D%96%E8%82%A1%E7%A5%A8%E7%9A%84%E6%9C%80%E4%BD%B3%E6%97%B6%E6%9C%BAIV.html)
  - [x] [最佳买卖股票时机含冷冻期](https://programmercarl.com/0309.%E6%9C%80%E4%BD%B3%E4%B9%B0%E5%8D%96%E8%82%A1%E7%A5%A8%E6%97%B6%E6%9C%BA%E5%90%AB%E5%86%B7%E5%86%BB%E6%9C%9F.html)
  - [x] [动规周总结](https://programmercarl.com/%E5%91%A8%E6%80%BB%E7%BB%93/20210304%E5%8A%A8%E8%A7%84%E5%91%A8%E6%9C%AB%E6%80%BB%E7%BB%93.html)
  - [x] [买卖股票的最佳时机含手续费](https://programmercarl.com/0714.%E4%B9%B0%E5%8D%96%E8%82%A1%E7%A5%A8%E7%9A%84%E6%9C%80%E4%BD%B3%E6%97%B6%E6%9C%BA%E5%90%AB%E6%89%8B%E7%BB%AD%E8%B4%B9%EF%BC%88%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92%EF%BC%89.html)
  - [x] [股票问题总结篇](https://programmercarl.com/%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92-%E8%82%A1%E7%A5%A8%E9%97%AE%E9%A2%98%E6%80%BB%E7%BB%93%E7%AF%87.html)
  - 41~50
  - [x] [最长上升子序列](https://programmercarl.com/0300.%E6%9C%80%E9%95%BF%E4%B8%8A%E5%8D%87%E5%AD%90%E5%BA%8F%E5%88%97.html)
  - [x] [最长连续递增序列](https://programmercarl.com/0674.%E6%9C%80%E9%95%BF%E8%BF%9E%E7%BB%AD%E9%80%92%E5%A2%9E%E5%BA%8F%E5%88%97.html)
  - [x] [最长重复子数组](https://programmercarl.com/0718.%E6%9C%80%E9%95%BF%E9%87%8D%E5%A4%8D%E5%AD%90%E6%95%B0%E7%BB%84.html)
  - [x] [最长公共子序列](https://programmercarl.com/1143.%E6%9C%80%E9%95%BF%E5%85%AC%E5%85%B1%E5%AD%90%E5%BA%8F%E5%88%97.html)
  - [x] [不相交的线](https://programmercarl.com/1035.%E4%B8%8D%E7%9B%B8%E4%BA%A4%E7%9A%84%E7%BA%BF.html)
  - [x] [最大子序和](https://programmercarl.com/0053.%E6%9C%80%E5%A4%A7%E5%AD%90%E5%BA%8F%E5%92%8C%EF%BC%88%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92%EF%BC%89.html)
  - [x] [判断子序列](https://programmercarl.com/0392.%E5%88%A4%E6%96%AD%E5%AD%90%E5%BA%8F%E5%88%97.html)
  - [x] [不同的子序列](https://programmercarl.com/0115.%E4%B8%8D%E5%90%8C%E7%9A%84%E5%AD%90%E5%BA%8F%E5%88%97.html)
  - [x] [两个字符串的删除操作](https://programmercarl.com/0583.%E4%B8%A4%E4%B8%AA%E5%AD%97%E7%AC%A6%E4%B8%B2%E7%9A%84%E5%88%A0%E9%99%A4%E6%93%8D%E4%BD%9C.html)
  - [ ] [编辑距离](https://programmercarl.com/0072.%E7%BC%96%E8%BE%91%E8%B7%9D%E7%A6%BB.html)
  - 51~
  - [ ] 编辑距离总结篇
  - [ ] 回文子串
  - [ ] 最长回文子序列
  - [ ] 动态规划总结篇
