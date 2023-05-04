# Linked List

- [Linked List](#linked-list)
  - [理论基础](#理论基础)
  - [链表的类型](#链表的类型)
    - [单链表](#单链表)
    - [双链表](#双链表)
    - [循环链表](#循环链表)
  - [链表的存储方式](#链表的存储方式)
  - [链表的定义](#链表的定义)
  - [链表的操作](#链表的操作)
    - [删除结点](#删除结点)
    - [添加结点](#添加结点)
  - [时间复杂度比较](#时间复杂度比较)
  - [翻转链表](#翻转链表)
    - [双指针](#双指针)
    - [递归](#递归)
      - [双指针逻辑](#双指针逻辑)
      - [递归拆分](#递归拆分)
  - [两两交换链表结点](#两两交换链表结点)
  - [References](#references)

## 理论基础

链表是一种通过指针串联在一起的**线性**结构，每一个结点由两部分组成：

1. 数据域
2. 指针域

最后一个结点的指针域指向 null。

## 链表的类型

### 单链表

每个结点只有一个指向下一个结点的指针。

### 双链表

每一个结点有两个指针域，一个指向下一个结点，一个指向上一个结点。

双链表既可以向前查询也可以向后查询。

### 循环链表

即链表首尾相连。

## 链表的存储方式

链表在内存中不是连续分布的。

链表通过指针域的指针链接在内存中散乱分布的各个结点，结点位置取决于操作系统的内存管理机制。

## 链表的定义

```cpp
// 单链表
struct ListNode {
  int val;                                  // 结点上存储的元素
  ListNode *next;                           // 指向下一个结点的指针
  ListNode(int x) : val(x), next(NULL) {}   // 结点的构造函数，不定义也行
                                            // 不过 C++ 默认生成的不会初始化成员变量
};

// 自定义构造函数的结点初始化：
ListNode* head = new ListNode(5);

// 默认构造函数的结点初始化：
ListNode* head = new ListNode();
head->val = 5;
```

## 链表的操作

### 删除结点

```cpp
ListNode* to_del;
prev->next = to_del->next;
free(to_del);
```

### 添加结点

```cpp
ListNode* head;
ListNode* new_node(val);
new_node->next = head->next;
head->next = new_node;
```

## 时间复杂度比较

| 类型 | 插入/删除 | 查询   | 适用场景                         |
| ---- | --------- | ------ | -------------------------------- |
| 数组 | $O(n)$    | $O(1)$ | 数据量固定，频繁查询，较少增删   |
| 链表 | $O(1)$    | $O(n)$ | 数据量不固定，频繁增删，较少查询 |

- 数组在定义时，长度就是固定的，如果想要改动数组长度，就需要重新定义 (C++)。
- 链表长度不固定，可以动态增删，适合数据量不固定，频繁增删，较少查询的场景。

## 翻转链表

### 双指针

```cpp
class Solution {
public:
  ListNode* reverseList(ListNode* head) {
    ListNode* temp;       // 保存cur的下一个节点
    ListNode* cur = head;
    ListNode* pre = NULL;
    while(cur) {
      temp = cur->next;   // 保存一下 cur的下一个节点，因为接下来要改变cur->next
      cur->next = pre;    // 翻转操作
      // 更新 pre 和 cur指针
      pre = cur;
      cur = temp;
    }
    return pre;
  }
};
```

### 递归

#### 双指针逻辑

```cpp
class Solution {
public:
  ListNode* reverse(ListNode* pre,ListNode* cur){
    if(cur == NULL) return pre;
    ListNode* temp = cur->next;
    cur->next = pre;
    // 可以和双指针法的代码进行对比，如下递归的写法，其实就是做了这两步
    // pre = cur;
    // cur = temp;
    return reverse(cur, temp);
  }
  ListNode* reverseList(ListNode* head) {
    // 和双指针法初始化是一样的逻辑
    // ListNode* cur = head;
    // ListNode* pre = NULL;
    return reverse(NULL, head);
  }
};
```

#### 递归拆分

```cpp
class Solution {
public:
  ListNode* reverseList(ListNode* head) {
    // 边缘条件判断
    if(head == NULL) return NULL;
    if (head->next == NULL) return head;

    // 递归调用，翻转第二个节点开始往后的链表
    ListNode *last = reverseList(head->next);
    // 翻转头节点与第二个节点的指向
    head->next->next = head;
    // 此时的 head 节点为尾节点，next 需要指向 NULL
    head->next = NULL;
    return last;
  }
};
```

## 两两交换链表结点

```cpp
class Solution {
public:
  ListNode* swapPairs(ListNode* head) {
    ListNode* dummyHead = new ListNode(0);  // 设置一个虚拟头结点
    dummyHead->next = head;                 // 虚拟结点指向 head，方便后面做删除操作
    ListNode* cur = dummyHead;
    while(cur->next != nullptr && cur->next->next != nullptr) {
      ListNode* tmp = cur->next;              // 记录临时节点
      ListNode* tmp1 = cur->next->next->next; // 记录临时节点

      cur->next = cur->next->next;
      cur->next->next = tmp;
      cur->next->next->next = tmp1;

      cur = cur->next->next;                  // cur 移动两位，准备下一轮交换
    }
    return dummyHead->next;
  }
};
```

## References

- [x] 链表
  - [x] [链表理论基础](https://programmercarl.com/%E9%93%BE%E8%A1%A8%E7%90%86%E8%AE%BA%E5%9F%BA%E7%A1%80.html)
  - [x] [移除链表元素](https://programmercarl.com/0203.%E7%A7%BB%E9%99%A4%E9%93%BE%E8%A1%A8%E5%85%83%E7%B4%A0.html)
  - [x] [设计链表](https://programmercarl.com/0707.%E8%AE%BE%E8%AE%A1%E9%93%BE%E8%A1%A8.html)
  - [x] [翻转链表](https://programmercarl.com/0206.%E7%BF%BB%E8%BD%AC%E9%93%BE%E8%A1%A8.html)
  - [x] [两两交换链表中的结点](https://programmercarl.com/0024.%E4%B8%A4%E4%B8%A4%E4%BA%A4%E6%8D%A2%E9%93%BE%E8%A1%A8%E4%B8%AD%E7%9A%84%E8%8A%82%E7%82%B9.html)
  - [ ] [删除链表的倒数第N个结点](https://programmercarl.com/0019.%E5%88%A0%E9%99%A4%E9%93%BE%E8%A1%A8%E7%9A%84%E5%80%92%E6%95%B0%E7%AC%ACN%E4%B8%AA%E8%8A%82%E7%82%B9.html)
  - [ ] 链表相交
  - [ ] 环形链表II
  - [ ] 总结篇
