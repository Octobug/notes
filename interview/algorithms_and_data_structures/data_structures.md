# Data Structures

## Linked List

### 给定一个单链表结点，将一个新结点插入到该结点之后。

```pcode
Node l1;
Node nextNode;
l1->next = nextNode;
nextNode->next = NULL;
```

### 给定一个单链表结点，将一个新结点插入到该结点之前。

```pcode
Node l1;
Node preNode;
Val tmp = l1->val;
l1->val = preNode->val;
l1->next = preNode;
preNode->val = tmp;
preNode->next = NULL;
```
