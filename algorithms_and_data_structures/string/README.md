# String

- [String](#string)
  - [Differences between char array and string](#differences-between-char-array-and-string)
  - [KMP](#kmp)
    - [模式串的前缀，后缀和部分匹配值](#模式串的前缀后缀和部分匹配值)
    - [生成前缀表](#生成前缀表)
    - [使用前缀表](#使用前缀表)
  - [References](#references)

## Differences between char array and string

字符串是若干字符组成的有限序列，也可以理解为是一个字符数组，但是很多语言对字符串做了特殊的规定。

在 C 语言中，把一个字符串存入一个数组时，也把结束符 `'\0'` 存入数组，并以此作为该字符串是否结束的标志。

```c
char a[5] = "asd";
for (int i = 0; a[i] != '\0'; i++) {
}
```

在 C++ 中，提供一个 `string` 类，`string` 类会提供 `size` 接口，可以用来判断 `string`
类字符串是否结束，就不用 `'\0'` 来判断是否结束。

```cpp
string a = "asd";
for (int i = 0; i < a.size(); i++) {
}
```

那么 `vector<char>` 和 `string` 有什么区别呢？

其实在基本操作上没有区别，但是 `string` 提供更多的字符串处理的相关接口，例如 `string` 重载了
`+`，而 `vector` 没有。

## KMP

> Knuth, Morris, and Pratt

设字符串 S，字串 T。匹配时 S 下标为 `i`，T 下表为 `j`。

KMP 的经典思想：**利用比较过的信息，`i` 指针不需要回溯，仅将子串向后滑动到一个合适的位置，并从这个位置开始和主串进行比较。
这个合适的位置仅与子串本身的结构有关，而与主串无关。**

### 模式串的前缀，后缀和部分匹配值

- 前缀：除最后一个字符以外，模式串的所有头部子串；
- 后缀：除第一个字符以外，模式串的所有尾部子串；
- 部分匹配值：字符串的前缀和后缀中，最长的相等的字符串的长度。

例子：`ababa`

- `a`: 前缀后缀都为空集，因此部分匹配值为 `0`
- `ab`: 前缀 `{a}`，后缀 `{b}`，部分匹配值为 `0`
- `aba`: 前缀 `{a,ab}`，后缀 `{a,ba}`，`a`==`a`，所以部分匹配值为 `1`
- `abab`: 前缀 `{a,ab,aba}`，后缀 `{b,ab,bab,}`，`ab`==`ab`，所以部分匹配值为 `2`
- `ababa`: 前缀 `{a,ab,aba,abab}`，后缀 `{a,ba,aba,baba}`，`aba`==`aba`，
  所以部分匹配值为 `3`

得到部分匹配值表：

```txt
T:    a b a b a
next: 0 0 1 2 3
```

对于 `abcac`，有：

```txt
T:    a b c a c
next: 0 0 0 1 0
```

由于当前匹配值是供下一个字符不匹配时使用，因此统一右移一位，这样不匹配时直接使用自己的匹配值即可，得到：

```txt
T:    a  b c a c
next: -1 0 0 0 1
```

`-1` 表示使 `i` 右移，最后一位因为不会被使用，所以溢出没关系。

```txt
    0 1 2 3 4 5 6 7 8 9 10 11 12
S:  a b a b c a b c a c b  a  b
T:  a b c
```

匹配时，`S[2] != T[2]`，根据右移后的 `next` 表，可知 `c` 对应的匹配值为 `0`，这时将 `j`
重置为 `0`，使子串右移。以此类推，直到完成匹配。

### 生成前缀表

```cpp
void get_next(string T, int next[]) {
  int i = 1, j = 0;
  next[j] = -1;
  while (i < T.size() - 1) {
    if (j == -1 || T[i] == T[j]) {
      // 自我比较的过程中，相等时继续往右匹配，next[i] 保存匹配时的部分匹配值
      i++;
      j++;
      next[i] = j;
    } else {
      // 不匹配时，j 按部分匹配值回溯
      j = next[j];
    }
  }
}
```

### 使用前缀表

```cpp
int kmp(string S, string T, int next[], int pos) {
  int i = pos, j = 0;
  while (i < S.size() && j < T.size()) {
    if (j == -1 || S[i] == T[j]) {
      i++;
      j++;
    } else {
      j = next[j];
    }
  }

  if (j >= T.size()) {
    return i - T.size();
  } else {
    return -1;
  }
}
```

## References

- [x] 字符串
  - [x] [反转字符串](https://programmercarl.com/0344.%E5%8F%8D%E8%BD%AC%E5%AD%97%E7%AC%A6%E4%B8%B2.html)
  - [x] [反转字符串II](https://programmercarl.com/0541.%E5%8F%8D%E8%BD%AC%E5%AD%97%E7%AC%A6%E4%B8%B2II.html)
  - [x] [替换空格](https://programmercarl.com/%E5%89%91%E6%8C%87Offer05.%E6%9B%BF%E6%8D%A2%E7%A9%BA%E6%A0%BC.html)
  - [x] [翻转字符串里的单词](https://programmercarl.com/0151.%E7%BF%BB%E8%BD%AC%E5%AD%97%E7%AC%A6%E4%B8%B2%E9%87%8C%E7%9A%84%E5%8D%95%E8%AF%8D.html)
  - [x] [左旋转字符串](https://programmercarl.com/%E5%89%91%E6%8C%87Offer58-II.%E5%B7%A6%E6%97%8B%E8%BD%AC%E5%AD%97%E7%AC%A6%E4%B8%B2.html)
  - [x] [实现 `strStr()`](https://programmercarl.com/0028.%E5%AE%9E%E7%8E%B0strStr.html)
  - [ ] [重复的子字符串](https://programmercarl.com/0459.%E9%87%8D%E5%A4%8D%E7%9A%84%E5%AD%90%E5%AD%97%E7%AC%A6%E4%B8%B2.html)
  - [ ] 总结篇
