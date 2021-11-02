# Data Structures

## Linked List

### 给定一个单链表结点，将一个新结点插入到该结点之后。

```pcode
Node l1;
Node nextNode;
nextNode->next = l1->next;
l1->next = nextNode;
```

### 给定一个单链表结点，将一个新结点插入到该结点之前。

```pcode
Node l1;
Node preNode;
Val tmp = l1->val;
l1->val = preNode->val;
preNode->val = tmp;

preNode->next = l1->next;
l1->next = preNode;
```
