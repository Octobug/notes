# 132. Palindrome Partitioning II

> <https://leetcode.com/problems/palindrome-partitioning-ii/>

Given a string `s`, partition `s` such that every **substring** of the
partition is a **palindrome**.

- A substring is a contiguous non-empty sequence of characters within a string.
- A palindrome is a string that reads the same forward and backward.

Return *the **minimum** cuts needed for a palindrome partitioning of `s`*.

**Example 1**:

```txt
Input: s = "aab"
Output: 1
Explanation: The palindrome partitioning ["aa","b"] could be produced using 1
    cut.
```

**Example 2**:

```txt
Input: s = "a"
Output: 0
```

**Example 3**:

```txt
Input: s = "ab"
Output: 1
```

**Constraints**:

- `1 <= s.length <= 2000`
- `s` consists of lowercase English letters only.
