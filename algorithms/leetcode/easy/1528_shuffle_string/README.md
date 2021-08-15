# 1528. Shuffle String

> origin: <https://leetcode.com/problems/shuffle-string/>

Given a string `s` and an integer array `indices` of the **same length**.

The string `s` will be shuffled such that the character at the <code>i<sup>th
</sup></code> position moves to `indices[i]` in the shuffled string.

Return *the shuffled string*.

**Example 1:**

![example 1](./images/example1.jpg)

```text
Input: s = "codeleet", indices = [4,5,6,7,0,2,1,3]
Output: "leetcode"
Explanation: As shown, "codeleet" becomes "leetcode" after shuffling.
```

**Example 2:**

```text
Input: s = "abc", indices = [0,1,2]
Output: "abc"
Explanation: After shuffling, each character remains in its position.
```

**Example 3:**

```text
Input: s = "aiohn", indices = [3,1,4,2,0]
Output: "nihao"
```

**Example 4:**

```text
Input: s = "aaiougrt", indices = [4,0,2,6,7,3,1,5]
Output: "arigatou"
```

**Example 5:**

```text
Input: s = "art", indices = [1,0,2]
Output: "rat"
```

**Constraints:**

* `s.length == indices.length == n`
* `1 <= n <= 100`
* `s` contains only lower-case English letters.
* `0 <= indices[i] < n`
* All values of `indices` are unique (i.e. `indices` is a permutation of the
  integers from `0` to `n - 1`).
