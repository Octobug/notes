# Stack and Queue

- [Stack and Queue](#stack-and-queue)
  - [理论基础](#理论基础)
  - [References](#references)

## 理论基础

栈和队列是 `STL` (`C++` 标准库) 里面的两个数据结构。
栈是以底层容器完成其所有的工作，在底层容器之上对外提供统一的接口，底层容器是可插拔的，即我们可以控制使用哪种容器来实现栈的功能。

栈的底层实现可以是 `vector`, `deque` (double-ended queue), `list` 都是可以的，主要是数组和链表的底层实现。

所以 **STL** 中栈往往不被归类为容器，而被归类为 **container adapter (容器适配器)**。
常用的 `SGI STL`，如果没有指定底层实现，默认是以 `deque` 为栈的底层结构。

`deque` 是一个双向队列，只要封住一端，只开通另一端就可以实现栈的逻辑了。

我们也可以指定 `vector` 为栈的底层实现，初始化语句如下：

```cpp
std::stack<int, std::vector<int> > third;  // 使用vector为底层容器的栈
```

队列是先进先出的数据结构，和栈同样不允许遍历，不提供迭代器, `SGI STL` 中，队列一样默认是以
`deque` 为底层数据结构。

同样可以指定 `list` 为其底层实现，初始化 `queue` 的语句如下：

```cpp
std::queue<int, std::list<int>> third; // 定义以list为底层容器的队列
```

所以 STL 队列也不被归类为容器，而被归类为 **container adapter (容器适配器)**。

## References

- [x] 栈与队列
  - [x] [栈与队列理论基础](https://programmercarl.com/%E6%A0%88%E4%B8%8E%E9%98%9F%E5%88%97%E7%90%86%E8%AE%BA%E5%9F%BA%E7%A1%80.html)
  - [x] [用栈实现队列](https://programmercarl.com/0232.%E7%94%A8%E6%A0%88%E5%AE%9E%E7%8E%B0%E9%98%9F%E5%88%97.html)
  - [ ] [用队列实现栈](https://programmercarl.com/0225.%E7%94%A8%E9%98%9F%E5%88%97%E5%AE%9E%E7%8E%B0%E6%A0%88.html)
  - [ ] 有效的括号
  - [ ] 删除字符串中的所有相邻重复项
  - [ ] 逆波兰表达式求值
  - [ ] 滑动窗口最大值
  - [ ] 前K个高频元素
  - [ ] 栈与队列总结
