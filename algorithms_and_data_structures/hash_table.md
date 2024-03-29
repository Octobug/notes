# Hash Table

- [Hash Table](#hash-table)
  - [理论基础](#理论基础)
    - [哈希表](#哈希表)
    - [哈希函数](#哈希函数)
    - [哈希碰撞](#哈希碰撞)
      - [拉链法](#拉链法)
      - [线性探测法](#线性探测法)
    - [三种常见的哈希结构](#三种常见的哈希结构)
      - [set](#set)
      - [map](#map)
  - [两个数组的交集](#两个数组的交集)
  - [References](#references)

## 理论基础

### 哈希表

哈希表是根据关键码的值而直接进行访问的数据结构。

最简单的哈希表：数组

一般哈希表都是用来快速判断一个元素是否出现在集合里。

### 哈希函数

- `index = hashFunction(input)`
- `hashCode = hassFunction(name) % tableSize`

如果 `input` 的数量大于 `tableSize` 怎么办，此时就算哈希函数计算的再均匀，也避免不了多个
`input` 同时映射到哈希表同一个索引下标的位置。

### 哈希碰撞

即 `hashFunction(input1) == hashFunction(input2)`

一般哈希碰撞有两种解决方法：拉链法和线性探测法。

#### 拉链法

当输入元素得到的 `hashCode` 相同时，它们会按添加顺序被存储在对应位置的链表中。

拉链法要选择适当的哈希表大小，这样既不会因为数组空值而浪费大量内存，也不会因为链表太长而在查找上浪费太多时间。

#### 线性探测法

使用线性探测法，一定要保证 `tableSize` 大于 `dataSize`。 我们需要依靠哈希表中的空位来解决碰撞问题。

如果出现了冲突的位置，那么就向下找一个空位放置新的信息。所以要求 `tableSize`
一定要大于 `dataSize`，否则哈希表上就没有空的位置来存放冲突的数据了。

### 三种常见的哈希结构

- 数组
- set (集合)
- map (映射)

在 C++ 中，`set` 和 `map` 分别提供以下三种数据结构，其底层实现以及优劣如下：

#### set

- `std::set`
  - 底层实现：红黑树
  - 是否有序：有序
  - 数值重复：不重复
  - 数值可改：不可改
  - 查询效率：$O(logn)$
  - 增删效率：$O(logn)$
- `std::multiset`
  - 底层实现：红黑树
  - 是否有序：有序
  - 数值重复：可重复
  - 数值可改：不可改
  - 查询效率：$O(logn)$
  - 增删效率：$O(logn)$
- `std::unordered_set`
  - 底层实现：哈希表
  - 是否有序：无序
  - 数值重复：不重复
  - 数值可改：不可改
  - 查询效率：$O(1)$
  - 增删效率：$O(1)$

红黑树是一种平衡二叉搜索树，所以 key 值是有序的，但 key 不可以修改，改动 key
值会导致整棵树的错乱，所以只能删除和增加。

当需要使用集合来解决哈希问题的时候，优先使用 `unordered_set`，因为它的查询和增删效率是最优的，如果需要集合是有序的，那么就用
`set`，如果要求不仅有序还要有重复数据的话，那么就用 `multiset`。

#### map

- `std::map`
  - 底层实现：红黑树
  - 是否有序：key 有序
  - 数值重复：key 不重复
  - 数值可改：key 不可改
  - 查询效率：$O(logn)$
  - 增删效率：$O(logn)$
- `std::multimap`
  - 底层实现：红黑树
  - 是否有序：key 有序
  - 数值重复：key 可重复
  - 数值可改：key 不可改
  - 查询效率：$O(logn)$
  - 增删效率：$O(logn)$
- `std::unordered_map`
  - 底层实现：哈希表
  - 是否有序：key 无序
  - 数值重复：key 不重复
  - 数值可改：key 不可改
  - 查询效率：$O(1)$
  - 增删效率：$O(1)$

虽然 `std::set`, `std::multiset` 的底层实现是红黑树，不是哈希表，但是其使用方式还是哈希法的使用方式，即 `key` 和 `value`。
所以使用这些数据结构来解决映射问题的方法，我们依然称之为哈希法。map 也是一样的道理。

一些 C++ 的经典书籍上说到了 `hash_set`, `hash_map`，这个与 `unordered_set`,
`unordered_map` 实际上功能都是一样的。
`unordered_set` 在 C++11 的时候被引入标准库了，而 `hash_set` 并没有。

`hash_set`, `hash_map`, `hash_multiset`, `hash_multimap` 等都是社区贡献的库。

## 两个数组的交集

```cpp
class Solution {
public:
  vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    unordered_set<int> result_set; // 存放结果，之所以用set是为了给结果集去重
    unordered_set<int> nums_set(nums1.begin(), nums1.end());
    for (int num : nums2) {
      // 发现nums2的元素 在nums_set里又出现过
      if (nums_set.find(num) != nums_set.end()) {
        result_set.insert(num);
      }
    }
    return vector<int>(result_set.begin(), result_set.end());
  }
};
```

## References

- [x] 哈希表
  - [x] [哈希表理论基础](https://programmercarl.com/%E5%93%88%E5%B8%8C%E8%A1%A8%E7%90%86%E8%AE%BA%E5%9F%BA%E7%A1%80.html)
  - [x] [有效的字母异位词](https://programmercarl.com/0242.%E6%9C%89%E6%95%88%E7%9A%84%E5%AD%97%E6%AF%8D%E5%BC%82%E4%BD%8D%E8%AF%8D.html)
  - [x] [两个数组的交集](https://programmercarl.com/0349.%E4%B8%A4%E4%B8%AA%E6%95%B0%E7%BB%84%E7%9A%84%E4%BA%A4%E9%9B%86.html)
  - [x] [快乐数](https://programmercarl.com/0202.%E5%BF%AB%E4%B9%90%E6%95%B0.html)
  - [x] [两数之和](https://programmercarl.com/0001.%E4%B8%A4%E6%95%B0%E4%B9%8B%E5%92%8C.html)
  - [x] [四数相加II](https://programmercarl.com/0454.%E5%9B%9B%E6%95%B0%E7%9B%B8%E5%8A%A0II.html)
  - [x] [赎金信](https://programmercarl.com/0383.%E8%B5%8E%E9%87%91%E4%BF%A1.html)
  - [x] [三数之和](https://programmercarl.com/0015.%E4%B8%89%E6%95%B0%E4%B9%8B%E5%92%8C.html)
  - [x] [四数之和](https://programmercarl.com/0018.%E5%9B%9B%E6%95%B0%E4%B9%8B%E5%92%8C.html)
  - [x] [总结篇](https://programmercarl.com/%E5%93%88%E5%B8%8C%E8%A1%A8%E6%80%BB%E7%BB%93.html)
