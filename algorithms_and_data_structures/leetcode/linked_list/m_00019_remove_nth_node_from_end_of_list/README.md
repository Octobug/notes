# 19. Remove Nth Node From End of List

> <https://leetcode.com/problems/remove-nth-node-from-end-of-list/>

Given the `head` of a linked list, remove the $n^{th}$ node from the end of the
list and return its head.

**Example 1**:

```txt
Input: head = [1,2,3,4,5], n = 2
Output: [1,2,3,5]
```

**Example 2**:

```txt
Input: head = [1], n = 1
Output: []
```

**Example 3**:

```txt
Input: head = [1,2], n = 1
Output: [1]
```

**Constraints**:

- The number of nodes in the list is `sz`.
- `1 <= sz <= 30`
- `0 <= Node.val <= 100`
- `1 <= n <= sz`

**Follow up**: Could you do this in one pass?
