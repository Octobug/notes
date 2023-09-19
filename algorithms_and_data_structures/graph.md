# Graph

- [Graph](#graph)
  - [理论基础](#理论基础)
  - [DFS 代码框架](#dfs-代码框架)
  - [References](#references)

## 理论基础

- 深度优先搜索 (Depth-First Search)
- 广度优先搜索 (Breadth-First Search)

💡 二叉树的递归遍历其实就是 DFS，而迭代遍历就是 BFS。

## DFS 代码框架

```cpp
void dfs(参数) {
  if (终止条件) {
    存放结果;
    return;
  }

  for (选择：本节点所连接的其他节点) {
    处理节点;
    dfs(图，选择的节点); // 递归
    回溯，撤销处理结果
  }
}
```

## References

- [x] [图论](https://programmercarl.com/other/tulunshuoming.html)
  - 01~10
  - [x] [深度优先搜索理论基础](https://programmercarl.com/%E5%9B%BE%E8%AE%BA%E6%B7%B1%E6%90%9C%E7%90%86%E8%AE%BA%E5%9F%BA%E7%A1%80.html)
  - [x] [所有可能的路径](https://programmercarl.com/0797.%E6%89%80%E6%9C%89%E5%8F%AF%E8%83%BD%E7%9A%84%E8%B7%AF%E5%BE%84.html)
  - [x] [广度优先搜索理论基础](https://programmercarl.com/%E5%9B%BE%E8%AE%BA%E5%B9%BF%E6%90%9C%E7%90%86%E8%AE%BA%E5%9F%BA%E7%A1%80.html)
  - [x] [岛屿数量.深搜版](https://programmercarl.com/0200.%E5%B2%9B%E5%B1%BF%E6%95%B0%E9%87%8F.%E6%B7%B1%E6%90%9C%E7%89%88.html)
  - [x] [岛屿数量.广搜版](https://programmercarl.com/0200.%E5%B2%9B%E5%B1%BF%E6%95%B0%E9%87%8F.%E5%B9%BF%E6%90%9C%E7%89%88.html)
  - [x] [岛屿的最大面积](https://programmercarl.com/0695.%E5%B2%9B%E5%B1%BF%E7%9A%84%E6%9C%80%E5%A4%A7%E9%9D%A2%E7%A7%AF.html)
  - [x] [飞地的数量](https://programmercarl.com/1020.%E9%A3%9E%E5%9C%B0%E7%9A%84%E6%95%B0%E9%87%8F.html)
  - [ ] [被围绕的区域](https://programmercarl.com/0130.%E8%A2%AB%E5%9B%B4%E7%BB%95%E7%9A%84%E5%8C%BA%E5%9F%9F.html)
  - [ ] 太平洋大西洋水流问题
  - [ ] 最大人工岛
  - 11~20
  - [ ] 单词接龙
  - [ ] 钥匙和房间
  - [ ] 岛屿的周长
  - [ ] 并查集理论基础
  - [ ] 寻找图中是否存在路径
  - [ ] 冗余连接
  - [ ] 冗余连接II
