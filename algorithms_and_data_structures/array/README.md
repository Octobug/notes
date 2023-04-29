# Array

- [Array](#array)
  - [理论基础](#理论基础)
    - [二维数组的内存空间地址连续吗](#二维数组的内存空间地址连续吗)
  - [二分查找](#二分查找)
    - [左闭右闭写法](#左闭右闭写法)
    - [左闭右开写法](#左闭右开写法)
  - [双指针](#双指针)
    - [快慢指针](#快慢指针)
    - [相向双指针](#相向双指针)
  - [References](#references)

## 理论基础

数组是存放在连续内存空间上的相同类型数据的集合。

- 数组下标都是从0开始的。
- 数组内存空间的地址是连续的。

正因为数组在内存空间的地址是连续的，所以在删除或者增加元素时，就难免要移动其他元素的位置。

⚠️ C++ 的 vector 底层实现是 array，但严格来讲 vector 是容器，不是数组。

⚠️ 数组的元素是不能删的，只能覆盖。

### 二维数组的内存空间地址连续吗

不同编程语言的内存管理不一样。以 C++ 为例，在 C++ 中二维数组是连续分布的。

```cpp
void test_arr() {
  int array[2][3] = {
    {0, 1, 2},
    {3, 4, 5}
  };

  cout << &array[0][0] << " " << &array[0][1] << " " << &array[0][2] << endl;
  cout << &array[1][0] << " " << &array[1][1] << " " << &array[1][2] << endl;
}

int main() {
  test_arr();
}

// 0x7ffee4065820 0x7ffee4065824 0x7ffee4065828
// 0x7ffee406582c 0x7ffee4065830 0x7ffee4065834
```

可以看出二维数组地址是连续的。

像 Java 是没有指针的，同时也不对程序员暴露其元素的地址，寻址操作完全交给虚拟机。
因此看不到每个元素的地址情况。

```java
public static void test_arr() {
  int[][] arr = {{1, 2, 3}, {3, 4, 5}, {6, 7, 8}, {9,9,9}};

  System.out.println(arr[0]);
  System.out.println(arr[1]);
  System.out.println(arr[2]);
  System.out.println(arr[3]);
}

// [I@7852e922
// [I@4e25154f
// [I@70dea4e
// [I@5c647e05
```

这里输出的不是真正的地址，而是经过处理的数值。
从这里也可以看出，二维数组的每一行头结点的地址是没有规则的，更谈不上连续。

## 二分查找

区间定义可以分为两种：

- 左闭右闭：$[left, right]$
- 左闭右开：$[left, right)$

### 左闭右闭写法

`middle` 可以取值 `right`，因此 `left == right` 是有意义的，取
`while (left <= right)`。

### 左闭右开写法

`middle` 不可以取值 `right`，因此 `left == right` 在区间 $[left, right)$ 没有意义。

```cpp
class Solution {
public:
  int search(vector<int>& nums, int target) {
    int left = 0;
    int right = nums.size(); // 定义 target 在左闭右开的区间里，即：[left, right)

    while (left < right) {
      int middle = left + ((right - left) / 2);
      if (nums[middle] > target) {
        right = middle; // target 在左区间，右边界是开边界
      } else if (nums[middle] < target) {
        left = middle + 1;  // target 在右区间，左边界是闭边界
      } else {
        return middle;
      }
    }
    return -1;
  }
};
```

## 双指针

### 快慢指针

- 快指针：寻找新数组的元素，即不含有目标元素的数组
- 慢指针：指向更新新数组下标的位置

```cpp
// 时间复杂度：O(n)
// 空间复杂度：O(1)
class Solution {
public:
  int removeElement(vector<int>& nums, int val) {
    int slowIndex = 0;
    for (int fastIndex = 0; fastIndex < nums.size(); fastIndex++) {
      if (val != nums[fastIndex]) {
        nums[slowIndex++] = nums[fastIndex];
      }
    }
    return slowIndex;
  }
};
```

### 相向双指针

基于元素顺序可以改变的题目描述改变了元素相对位置，确保移动最少元素。

```cpp
/**
* 时间复杂度：O(n)
* 空间复杂度：O(1)
*/
class Solution {
public:
  int removeElement(vector<int>& nums, int val) {
    int leftIndex = 0;
    int rightIndex = nums.size() - 1;
    while (leftIndex <= rightIndex) {
      // 找左边等于val的元素
      while (leftIndex <= rightIndex && nums[leftIndex] != val){
        ++leftIndex;
      }
      // 找右边不等于val的元素
      while (leftIndex <= rightIndex && nums[rightIndex] == val) {
        -- rightIndex;
      }
      // 将右边不等于val的元素覆盖左边等于val的元素
      if (leftIndex < rightIndex) {
        nums[leftIndex++] = nums[rightIndex--];
      }
    }
    return leftIndex;   // leftIndex一定指向了最终数组末尾的下一个元素
  }
};
```

## References

- [x] 数组
  - [x] [数组理论基础](https://programmercarl.com/%E6%95%B0%E7%BB%84%E7%90%86%E8%AE%BA%E5%9F%BA%E7%A1%80.html)
  - [x] [二分查找](https://programmercarl.com/0704.%E4%BA%8C%E5%88%86%E6%9F%A5%E6%89%BE.html)
  - [x] [移除元素](https://programmercarl.com/0027.%E7%A7%BB%E9%99%A4%E5%85%83%E7%B4%A0.html)
  - [x] [有序数组的平方](https://programmercarl.com/0977.%E6%9C%89%E5%BA%8F%E6%95%B0%E7%BB%84%E7%9A%84%E5%B9%B3%E6%96%B9.html)
  - [x] [长度最小的子数组](https://programmercarl.com/0209.%E9%95%BF%E5%BA%A6%E6%9C%80%E5%B0%8F%E7%9A%84%E5%AD%90%E6%95%B0%E7%BB%84.html)
  - [x] [螺旋矩阵II](https://programmercarl.com/0059.%E8%9E%BA%E6%97%8B%E7%9F%A9%E9%98%B5II.html)
  - [ ] [总结篇](https://programmercarl.com/%E6%95%B0%E7%BB%84%E6%80%BB%E7%BB%93%E7%AF%87.html)
