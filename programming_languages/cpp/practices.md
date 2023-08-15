# Practices

- [Practices](#practices)
  - [enum idiom](#enum-idiom)

## enum idiom

```cpp
enum PROTO
{
    PROTO_HTTP,
    PROTO_FTP,
    PROTO_SMTP,
    PROTO_SSH,

    // 表示协议数量
    PROTO_NUM
};

// c
int nCntProto[PROTO_NUM];

// cpp
std::vector<int> vctCntProto(PROTO_NUM);
```

这种写法的好处在于，没有任何 Magic Number 出现在代码中。
不管是引用某个统计值还是循环遍历数组，都是用定义好的常量。
