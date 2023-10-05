# 2883. Drop Missing Data

> <https://leetcode.com/problems/drop-missing-data/>

```txt
DataFrame students
+-------------+--------+
| Column Name | Type   |
+-------------+--------+
| student_id  | int    |
| name        | object |
| age         | int    |
+-------------+--------+
```

There are some rows having missing values in the `name` column.

Write a solution to remove the rows with missing values.

The result format is in the following example.

**Example 1**:

```txt
Input:
+------------+-------+-----+
| student_id | name  | age |
+------------+-------+-----+
| 32         | Piper | 5   |
| 217        | Grace | 19  |
| 779        | None  | 20  |
| 849        | None  | 14  |
+------------+-------+-----+
Output:
+------------+-------+-----+
| student_id | name  | age |
+------------+-------+-----+
| 32         | Piper | 5   |
| 217        | Grace | 19  |
+------------+-------+-----+
Explanation: 
Students with ids 779 and 849 have empty values in the name column, so they
    will be removed.
```
