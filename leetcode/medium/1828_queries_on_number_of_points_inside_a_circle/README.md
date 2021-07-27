# 1828. Queries on Number of Points Inside a Circle

> origin: <https://leetcode.com/problems/queries-on-number-of-points-inside-a-circle/>

You are given an array `points` where <code>points[i] = [x<sub>i</sub>,
y<sub>i</sub>]</code> is the coordinates of the <code>i<sup>th</sup></code>
point on a 2D plane. Multiple points can have the **same** coordinates.

You are also given an array `queries` where <code>queries[j] = [x<sub>j</sub>,
y<sub>j</sub>, r<sub>j</sub>]</code> describes a circle centered at <code>
(x<sub>j</sub>, y<sub>j</sub>)</code> with a radius of <code>r<sub>j</sub>
</code>.

For each query `queries[j]`, compute the number of points **inside** the <code>
j<sup>th</sup></code> circle. Points **on the border** of the circle are
considered **inside**.

Return *an array `answer`, where `answer[j]` is the answer to the <code>
j<sup>th</sup></code> query*.

**Example 1:**

![example_1](./images/example1.png)

```text
Input: points = [[1,3],[3,3],[5,3],[2,2]], queries = [[2,3,1],[4,3,1],[1,1,2]]
Output: [3,2,2]
Explanation: The points and circles are shown above.
queries[0] is the green circle, queries[1] is the red circle, and queries[2] is
the blue circle.
```

**Example 2:**

![example_2](./images/example2.png)

```text
Input: points = [[1,1],[2,2],[3,3],[4,4],[5,5]], queries = [[1,2,2],[2,2,2],[4,3,2],[4,3,3]]
Output: [2,3,2,4]
Explanation: The points and circles are shown above.
queries[0] is green, queries[1] is red, queries[2] is blue, and queries[3] is purple.
```

**Constraints:**

* `1 <= points.length <= 500`
* `points[i].length == 2`
* <code>0 <= x<sub>i</sub>, y<sub>i</sub> <= 500</code>
* `1 <= queries.length <= 500`
* `queries[j].length == 3`
* <code>0 <= x<sub>j</sub>, y<sub>j</sub> <= 500</code>
* <code>1 <= r<sub>j</sub> <= 500</code>
* All coordinates are integers.

**Follow up**: Could you find the answer for each query in better complexity
than `O(n)`?
