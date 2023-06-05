# Binary Tree

- [Binary Tree](#binary-tree)
  - [理论基础](#理论基础)
    - [二叉树的种类](#二叉树的种类)
      - [满二叉树](#满二叉树)
      - [完全二叉树](#完全二叉树)
      - [二叉搜索树](#二叉搜索树)
      - [平衡二叉搜索树](#平衡二叉搜索树)
    - [二叉树的存储方式](#二叉树的存储方式)
    - [二叉树的遍历方式](#二叉树的遍历方式)
    - [二叉树的定义](#二叉树的定义)
  - [递归遍历](#递归遍历)
  - [迭代遍历](#迭代遍历)
    - [前序遍历](#前序遍历)
    - [中序遍历](#中序遍历)
    - [后序遍历](#后序遍历)
    - [前中后统一迭代](#前中后统一迭代)
    - [由遍历序列构造二叉树](#由遍历序列构造二叉树)
  - [References](#references)

## 理论基础

### 二叉树的种类

#### 满二叉树

如果一棵二叉树只有度为 0 的结点和度为 2 的结点，并且度为 0 的结点在同一层上，则这棵二叉树为满二叉树。

一棵满二叉树如果深度为 `k`，则其结点数为 $2^{k-1}$。

#### 完全二叉树

在完全二叉树中，除了最底层节点可能没填满外，其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最左边的若干位置。

若最底层为第 k 层，则该层包含 1~$2^{k-1}$ 个节点。

#### 二叉搜索树

**二叉搜索树是一个有序树**。

- 若它的左子树不空，则左子树上所有结点的值均小于它的根结点的值；
- 若它的右子树不空，则右子树上所有结点的值均大于它的根结点的值；
- 它的左、右子树也分别为二叉排序树。

C++ 中 `map`, `set`, `multimap`, `multiset` 的底层实现都是平衡二叉搜索树，所以 `map`,
`set` 的增删操作时间时间复杂度是 $O(logn)$。

`unordered_map`, `unordered_set`, `unordered_map`, `unordered_set`
的底层实现则是哈希表。

#### 平衡二叉搜索树

平衡二叉搜索树又被称为 AVL (Adelson-Velsky and Landis) 树，且具有以下性质：它是一棵空树或它的左右两个子树的高度差的绝对值不超过
`1`，并且左右两个子树都是一棵平衡二叉树。

### 二叉树的存储方式

二叉树可以链式（链表）存储，也可以顺序（数组）存储。

### 二叉树的遍历方式

- 深度优先（递归法，迭代法）
  - 前序遍历
  - 中序遍历
  - 后序便利
- 广度优先（迭代法）
  - 层次遍历

栈是递归的一种实现结构，因此，前中后序遍历的逻辑其实可以借助栈用非递归的方式实现。

而广度优先遍历的实现一般借助队列。

### 二叉树的定义

```cpp
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};
```

## 递归遍历

以**前序遍历**为例：

1. **确定递归函数的参数和返回值**：因为要打印出前序遍历结点的数值，所以参数里需要传入 vector
   存放结点数值，除了这一点就不需要再处理什么数据了，也不需要有返回值，所以递归函数返回类型是
   `void`：

   ```cpp
   void traversal(TreeNode* cur, vector<int>& vec);
   ```

2. **确定终止条件**：在递归的过程中，如果当前遍历的结点是空的，那么本层递归就可以结束了：

    ```cpp
    if (cur == NULL) return;
    ```

3. **确定单层递归的逻辑**：前序遍历是中左右的循序，所以在单层递归的逻辑，是先取中结点的数值：

    ```cpp
    vec.push_back(cur->val);    // 中
    traversal(cur->left, vec);  // 左
    traversal(cur->right, vec); // 右
    ```

前序遍历：

```cpp
class Solution {
public:
    void traverse(TreeNode* cur, vector<int>& vec) {
        if (cur == NULL) return;
        vec.push_back(cur->val);    // 中
        traverse(cur->left, vec);  // 左
        traverse(cur->right, vec); // 右
    }

    vector<int> preorderTraversal(TreeNode* root) {
        vector<int> result;
        traverse(root, result);
        return result;
    }
};
```

中序遍历：

```cpp
void traverse(TreeNode* cur, vector<int>& vec) {
    if (cur == NULL) return;
    traverse(cur->left, vec);  // 左
    vec.push_back(cur->val);    // 中
    traverse(cur->right, vec); // 右
}
```

后序遍历：

```cpp
void traverse(TreeNode* cur, vector<int>& vec) {
    if (cur == NULL) return;
    traverse(cur->left, vec);  // 左
    traverse(cur->right, vec); // 右
    vec.push_back(cur->val);    // 中
}
```

## 迭代遍历

### 前序遍历

```cpp
class Solution {
public:
  vector<int> preorderTraversal(TreeNode* root) {
    stack<TreeNode*> st;
    vector<int> result;
    if (root == NULL) return result;
    st.push(root);
    while (!st.empty()) {
      TreeNode* node = st.top();                       // 中
      st.pop();
      result.push_back(node->val);
      if (node->right) st.push(node->right);           // 右（空节点不入栈）
      if (node->left) st.push(node->left);             // 左（空节点不入栈）
    }
    return result;
  }
};
```

### 中序遍历

```cpp
class Solution {
public:
  vector<int> inorderTraversal(TreeNode* root) {
    vector<int> result;
    stack<TreeNode*> st;
    TreeNode* cur = root;
    while (cur != NULL || !st.empty()) {
      if (cur != NULL) { // 指针来访问节点，访问到最底层
        st.push(cur); // 将访问的节点放进栈
        cur = cur->left;                // 左
      } else {
        cur = st.top(); // 从栈里弹出的数据，就是要处理的数据（放进result数组里的数据）
        st.pop();
        result.push_back(cur->val);     // 中
        cur = cur->right;               // 右
      }
    }
    return result;
  }
};
```

### 后序遍历

先序遍历是“中左右”，后序遍历是“左右中”，调整一下先序遍历的代码顺序就可以变成“中右左”，输出的结果就是左右中了：

```cpp
class Solution {
public:
  vector<int> postorderTraversal(TreeNode* root) {
    stack<TreeNode*> st;
    vector<int> result;
    if (root == NULL) return result;
    st.push(root);
    while (!st.empty()) {
      TreeNode* node = st.top();
      st.pop();
      result.push_back(node->val);
      if (node->left) st.push(node->left); // 相对于前序遍历，这更改一下入栈顺序
      if (node->right) st.push(node->right); // 空节点不入栈
    }
    reverse(result.begin(), result.end()); // 将结果反转之后就是左右中的顺序了
    return result;
  }
};
```

### 前中后统一迭代

```cpp
// 前序遍历
class Solution {
public:
  vector<int> preorderTraversal(TreeNode* root) {
    vector<int> result;
    stack<TreeNode*> st;
    if (root != NULL) st.push(root);
    while (!st.empty()) {
      TreeNode* node = st.top();
      if (node != NULL) {
        st.pop();
        if (node->right) st.push(node->right);  // 右
        if (node->left) st.push(node->left);    // 左
        st.push(node);                          // 中
        st.push(NULL);
      } else {
        st.pop();
        node = st.top();
        st.pop();
        result.push_back(node->val);
      }
    }
    return result;
  }
};
```

```cpp
// 中序遍历
class Solution {
public:
  vector<int> inorderTraversal(TreeNode* root) {
    vector<int> result;
    stack<TreeNode*> st;
    if (root != NULL) st.push(root);
    while (!st.empty()) {
      TreeNode* node = st.top();
      if (node != NULL) {
        st.pop(); // 将该节点弹出，避免重复操作，下面再将右中左节点添加到栈中
        if (node->right) st.push(node->right);  // 添加右节点（空节点不入栈）

        st.push(node);                          // 添加中节点
        st.push(NULL); // 中节点访问过，但是还没有处理，加入空节点做为标记。

        if (node->left) st.push(node->left);    // 添加左节点（空节点不入栈）
      } else { // 只有遇到空节点的时候，才将下一个节点放进结果集
        st.pop();           // 将空节点弹出
        node = st.top();    // 重新取出栈中元素
        st.pop();
        result.push_back(node->val); // 加入到结果集
      }
    }
    return result;
  }
};
```

```cpp
// 后序遍历
class Solution {
public:
  vector<int> postorderTraversal(TreeNode* root) {
    vector<int> result;
    stack<TreeNode*> st;
    if (root != NULL) st.push(root);
    while (!st.empty()) {
      TreeNode* node = st.top();
      if (node != NULL) {
        st.pop();
        st.push(node);                          // 中
        st.push(NULL);

        if (node->right) st.push(node->right);  // 右
        if (node->left) st.push(node->left);    // 左
      } else {
        st.pop();
        node = st.top();
        st.pop();
        result.push_back(node->val);
      }
    }
    return result;
  }
};
```

### 由遍历序列构造二叉树

- 中序 + 前序 ✅
- 中序 + 后序 ✅
- 中序 + 层序 ✅
- 前序 + 后序 ❌

## References

- [x] 二叉树
  - [x] [二叉树理论基础](https://programmercarl.com/%E4%BA%8C%E5%8F%89%E6%A0%91%E7%90%86%E8%AE%BA%E5%9F%BA%E7%A1%80.html)
  - [x] [二叉树的递归遍历](https://programmercarl.com/%E4%BA%8C%E5%8F%89%E6%A0%91%E7%9A%84%E9%80%92%E5%BD%92%E9%81%8D%E5%8E%86.html)
  - [x] [二叉树的迭代遍历](https://programmercarl.com/%E4%BA%8C%E5%8F%89%E6%A0%91%E7%9A%84%E8%BF%AD%E4%BB%A3%E9%81%8D%E5%8E%86.html#%E5%89%8D%E5%BA%8F%E9%81%8D%E5%8E%86-%E8%BF%AD%E4%BB%A3%E6%B3%95)
  - [x] [二叉树的统一迭代法](https://programmercarl.com/%E4%BA%8C%E5%8F%89%E6%A0%91%E7%9A%84%E7%BB%9F%E4%B8%80%E8%BF%AD%E4%BB%A3%E6%B3%95.html)
  - [x] [二叉树的层序遍历](https://programmercarl.com/0102.%E4%BA%8C%E5%8F%89%E6%A0%91%E7%9A%84%E5%B1%82%E5%BA%8F%E9%81%8D%E5%8E%86.html)
  - [x] [翻转二叉树](https://programmercarl.com/0226.%E7%BF%BB%E8%BD%AC%E4%BA%8C%E5%8F%89%E6%A0%91.html)
  - [x] [二叉树周末总结](https://programmercarl.com/%E5%91%A8%E6%80%BB%E7%BB%93/20200927%E4%BA%8C%E5%8F%89%E6%A0%91%E5%91%A8%E6%9C%AB%E6%80%BB%E7%BB%93.html)
  - [x] [对称二叉树](https://programmercarl.com/0101.%E5%AF%B9%E7%A7%B0%E4%BA%8C%E5%8F%89%E6%A0%91.html)
  - [x] [二叉树的最大深度](https://programmercarl.com/0104.%E4%BA%8C%E5%8F%89%E6%A0%91%E7%9A%84%E6%9C%80%E5%A4%A7%E6%B7%B1%E5%BA%A6.html)
  - [x] [二叉树的最小深度](https://programmercarl.com/0111.%E4%BA%8C%E5%8F%89%E6%A0%91%E7%9A%84%E6%9C%80%E5%B0%8F%E6%B7%B1%E5%BA%A6.html)
  - [x] [完全二叉树的节点个数](https://programmercarl.com/0222.%E5%AE%8C%E5%85%A8%E4%BA%8C%E5%8F%89%E6%A0%91%E7%9A%84%E8%8A%82%E7%82%B9%E4%B8%AA%E6%95%B0.html)
  - [x] [平衡二叉树](https://programmercarl.com/0110.%E5%B9%B3%E8%A1%A1%E4%BA%8C%E5%8F%89%E6%A0%91.html)
  - [x] [二叉树的所有路径](https://programmercarl.com/0257.%E4%BA%8C%E5%8F%89%E6%A0%91%E7%9A%84%E6%89%80%E6%9C%89%E8%B7%AF%E5%BE%84.html)
  - [x] [二叉树周末总结](https://programmercarl.com/%E5%91%A8%E6%80%BB%E7%BB%93/20201003%E4%BA%8C%E5%8F%89%E6%A0%91%E5%91%A8%E6%9C%AB%E6%80%BB%E7%BB%93.html)
  - [x] [左叶子之和](https://programmercarl.com/0404.%E5%B7%A6%E5%8F%B6%E5%AD%90%E4%B9%8B%E5%92%8C.html)
  - [x] [找树左下角的值](https://programmercarl.com/0513.%E6%89%BE%E6%A0%91%E5%B7%A6%E4%B8%8B%E8%A7%92%E7%9A%84%E5%80%BC.html)
  - [x] [路径总和](https://programmercarl.com/0112.%E8%B7%AF%E5%BE%84%E6%80%BB%E5%92%8C.html)
  - [x] [从中序与后序遍历序列构造二叉树](https://programmercarl.com/0106.%E4%BB%8E%E4%B8%AD%E5%BA%8F%E4%B8%8E%E5%90%8E%E5%BA%8F%E9%81%8D%E5%8E%86%E5%BA%8F%E5%88%97%E6%9E%84%E9%80%A0%E4%BA%8C%E5%8F%89%E6%A0%91.html)
  - [ ] [最大二叉树](https://programmercarl.com/0654.%E6%9C%80%E5%A4%A7%E4%BA%8C%E5%8F%89%E6%A0%91.html)
  - [ ] 二叉树周末总结
  - [ ] 合并二叉树
  - [ ] 二叉搜索树中的搜索
  - [ ] 验证二叉搜索树
  - [ ] 二叉搜索树的最小绝对差
  - [ ] 二叉搜索树中的众数
  - [ ] 二叉树的最近公共祖先
  - [ ] 二叉树周末总结
  - [ ] 二叉搜索树的最近公共祖先
  - [ ] 二叉搜索树中的插入操作
  - [ ] 删除二叉搜索树中的节点
  - [ ] 修剪二叉搜索树
  - [ ] 将有序数组转换为二叉搜索树
  - [ ] 把二叉搜索树转换为累加树
  - [ ] 二叉树总结篇
