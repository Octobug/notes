# String

- [String](#string)
  - [Differences between char array and string](#differences-between-char-array-and-string)
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

## References

- [x] 字符串
  - [x] [反转字符串](https://programmercarl.com/0344.%E5%8F%8D%E8%BD%AC%E5%AD%97%E7%AC%A6%E4%B8%B2.html)
  - [x] [反转字符串II](https://programmercarl.com/0541.%E5%8F%8D%E8%BD%AC%E5%AD%97%E7%AC%A6%E4%B8%B2II.html)
  - [x] [替换空格](https://programmercarl.com/%E5%89%91%E6%8C%87Offer05.%E6%9B%BF%E6%8D%A2%E7%A9%BA%E6%A0%BC.html)
  - [x] [翻转字符串里的单词](https://programmercarl.com/0151.%E7%BF%BB%E8%BD%AC%E5%AD%97%E7%AC%A6%E4%B8%B2%E9%87%8C%E7%9A%84%E5%8D%95%E8%AF%8D.html)
  - [ ] [左旋转字符串](https://programmercarl.com/%E5%89%91%E6%8C%87Offer58-II.%E5%B7%A6%E6%97%8B%E8%BD%AC%E5%AD%97%E7%AC%A6%E4%B8%B2.html)
  - [ ] 实现 `strStr()`
  - [ ] 重复的子字符串
  - [ ] 总结篇
