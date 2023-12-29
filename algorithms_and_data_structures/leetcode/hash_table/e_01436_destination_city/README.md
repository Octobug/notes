# 1436. Destination City

> <https://leetcode.com/problems/destination-city/>

You are given the array `paths`, where $paths[i] = [cityA_i, cityB_i]$ means
there exists a direct path going from $cityA_i$ to $cityB_i$. Return *the
destination city, that is, the city without any path outgoing to another city*.

It is guaranteed that the graph of paths forms a line without any loop,
therefore, there will be exactly one destination city.

**Example 1**:

```txt
Input: paths = [["London","New York"],["New York","Lima"],["Lima","Sao Paulo"]]
Output: "Sao Paulo" 
Explanation: Starting at "London" city you will reach "Sao Paulo" city which is
    the destination city. Your trip consist of:
    "London" -> "New York" -> "Lima" -> "Sao Paulo".
```

**Example 2**:

```txt
Input: paths = [["B","C"],["D","B"],["C","A"]]
Output: "A"
Explanation: All possible trips are: 
"D" -> "B" -> "C" -> "A". 
"B" -> "C" -> "A". 
"C" -> "A". 
"A". 
Clearly the destination city is "A".
```

**Example 3**:

```txt
Input: paths = [["A","Z"]]
Output: "Z"
```

**Constraints**:

- `1 <= paths.length <= 100`
- `paths[i].length == 2`
- $1 <= cityA_i.length, cityB_i.length <= 10$
- $cityA_i != cityB_i$
- All strings consist of lowercase and uppercase English letters and the space
  character.
