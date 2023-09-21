# Graph

- [Graph](#graph)
  - [理论基础](#理论基础)
  - [DFS 代码框架](#dfs-代码框架)
  - [并查集 (Disjoint-Set)](#并查集-disjoint-set)
    - [并查集理论基础](#并查集理论基础)
    - [路径压缩](#路径压缩)
    - [并查集代码模板](#并查集代码模板)
    - [拓展：按秩 (rank) 合并路径压缩](#拓展按秩-rank-合并路径压缩)
    - [路径压缩复杂度](#路径压缩复杂度)
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

## 并查集 (Disjoint-Set)

并查集常用来解决连通性问题。需要判断两个元素是否在同一个集合里的时候，就可以用并查集。
两个主要功能：

1. 将两个元素添加到一个集合中；
2. 判断两个元素在不在同一个集合。

### 并查集理论基础

将三个元素 A, B, C（分别是数字）放在同一个集合，其实就是将三个元素连通在一起。

只需要用一个一维数组表示，即：`father[A] = B`, `father[B] = C`。
这样就表示 A 与 B 与 C 连通了（有向连通图）。

```cpp
// 将v，u 这条边加入并查集
void join(int u, int v) {
    u = find(u); // 寻找u的根
    v = find(v); // 寻找v的根
    if (u == v) return; // 如果发现根相同，则说明在一个集合，不用两个节点相连直接返回
    father[v] = u;
}

// 并查集里寻根的过程
int find(int u) {
    if (u == father[u])
        return u; // 如果根就是自己，直接返回
    else
        return find(father[u]); // 如果根不是自己，就根据数组下标一层一层向下找
}
```

要表示 C 也在同一个集合里，需要 `father[C] = C`，即 C 的根也为 C，这样就表示 A, B, C
都在同一个集合里了。

```cpp
// 并查集初始化，默认指向自己
void init() {
    for (int i = 0; i < n; ++i) {
        father[i] = i;
    }
}

// 判断 u 和 v是否找到同一个根
bool isSame(int u, int v) {
    u = find(u);
    v = find(v);
    return u == v;
}
```

### 路径压缩

`find` 搜索过程像是在一个“多叉树”中从叶子反向搜索到根结点。
如果这棵多叉树高度很深的话，`find` 的寻跟过程会递归很多次。

由于查找的最终目的是只要知道这些结点在同一个根下就可以，所以这棵“多叉树”只需要构造成高度为 2。
即所有叶子结点指向根结点。

将 `father` 数组构造成“多叉树”的过程就叫路径压缩。

```cpp
// 并查集里寻根的过程
int find(int u) {
    if (u == father[u])
        return u;
    else
        return father[u] = find(father[u]); // 路径压缩
}
```

### 并查集代码模板

```cpp
int n = 1005; // n根据题目中节点数量而定，一般比节点数量大一点就好
vector<int> father = vector<int> (n, 0);

// 并查集初始化
void init() {
    for (int i = 0; i < n; ++i) {
        father[i] = i;
    }
}

// 并查集里寻根的过程
int find(int u) {
    if (u == father[u])
        return u;
    else
        return father[u] = find(father[u]); // 路径压缩
}

// 判断 u 和 v是否找到同一个根
bool isSame(int u, int v) {
    u = find(u);
    v = find(v);
    return u == v;
}

// 将v->u 这条边加入并查集
void join(int u, int v) {
    u = find(u); // 寻找u的根
    v = find(v); // 寻找v的根

    if (u == v)
        return ; // 如果发现根相同，则说明在一个集合，不用两个节点相连直接返回

    father[v] = u;
}
```

### 拓展：按秩 (rank) 合并路径压缩

rank 表示树的高度，即树中结点层次的最大值。

当有两个集合，即两个多叉树需要合并时，将高度小的树合并入高度大的树，使合成后的树高度最小。

```cpp
int n = 1005; // n根据题目中节点数量而定，一般比节点数量大一点就好
vector<int> father = vector<int> (n, 0); // C++里的一种数组结构
vector<int> rank = vector<int> (n, 1); // 初始每棵树的高度都为1

// 并查集初始化
void init() {
    for (int i = 0; i < n; ++i) {
        father[i] = i;
        rank[i] = 1; // 也可以不写
    }
}
// 并查集里寻根的过程
int find(int u) {
    return u == father[u] ? u : find(father[u]);// 注意这里不做路径压缩
}

// 判断 u 和 v是否找到同一个根
bool isSame(int u, int v) {
    u = find(u);
    v = find(v);
    return u == v;
}

// 将v->u 这条边加入并查集
void join(int u, int v) {
    u = find(u); // 寻找u的根
    v = find(v); // 寻找v的根

    if (rank[u] <= rank[v]) father[u] = v; // rank小的树合入到rank大的树
    else father[v] = u;

    // 如果两棵树高度相同，则 v 的高度 +1
    // if (rank[u] <= rank[v]) father[u] = v;
    if (rank[u] == rank[v] && u != v) rank[v]++;
}
```

### 路径压缩复杂度

- 空间复杂度: `O(n)`，申请一个 `father` 数组。
- 时间复杂度: 路径压缩后的并查集时间复杂度在 `O(logn)` 与 `O(1)` 之间，且随着查询或者合并操作的增加，时间复杂度会越来越趋于 `O(1)`。

在第一次查询的时候，相当于 `n` 叉树上从叶子节点到根节点的查询过程，时间复杂度是 `logn`。
但路径压缩后，后面的查询操作都是 `O(1)`，而 `join` 函数和 `isSame` 函数里涉及的查询操作也是一样的过程。

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
  - [x] [被围绕的区域](https://programmercarl.com/0130.%E8%A2%AB%E5%9B%B4%E7%BB%95%E7%9A%84%E5%8C%BA%E5%9F%9F.html)
  - [x] [太平洋大西洋水流问题](https://programmercarl.com/0417.%E5%A4%AA%E5%B9%B3%E6%B4%8B%E5%A4%A7%E8%A5%BF%E6%B4%8B%E6%B0%B4%E6%B5%81%E9%97%AE%E9%A2%98.html)
  - [x] [最大人工岛](https://programmercarl.com/0827.%E6%9C%80%E5%A4%A7%E4%BA%BA%E5%B7%A5%E5%B2%9B.html)
  - 11~20
  - [x] [单词接龙](https://programmercarl.com/0127.%E5%8D%95%E8%AF%8D%E6%8E%A5%E9%BE%99.html)
  - [x] [钥匙和房间](https://programmercarl.com/0841.%E9%92%A5%E5%8C%99%E5%92%8C%E6%88%BF%E9%97%B4.html)
  - [x] [岛屿的周长](https://programmercarl.com/0463.%E5%B2%9B%E5%B1%BF%E7%9A%84%E5%91%A8%E9%95%BF.html)
  - [x] [并查集理论基础](https://programmercarl.com/%E5%9B%BE%E8%AE%BA%E5%B9%B6%E6%9F%A5%E9%9B%86%E7%90%86%E8%AE%BA%E5%9F%BA%E7%A1%80.html)
  - [x] [寻找图中是否存在路径](https://programmercarl.com/1971.%E5%AF%BB%E6%89%BE%E5%9B%BE%E4%B8%AD%E6%98%AF%E5%90%A6%E5%AD%98%E5%9C%A8%E8%B7%AF%E5%BE%84.html)
  - [x] [冗余连接](https://programmercarl.com/0684.%E5%86%97%E4%BD%99%E8%BF%9E%E6%8E%A5.html)
  - [x] [冗余连接II](https://programmercarl.com/0685.%E5%86%97%E4%BD%99%E8%BF%9E%E6%8E%A5II.html)
