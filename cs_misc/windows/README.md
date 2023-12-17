# Windows

- [Windows](#windows)
  - [Network](#network)
  - [CA 证书管理](#ca-证书管理)
  - [Microsoft](#microsoft)

## Network

```bat
netsh winsock reset
```

## CA 证书管理

1. 打开证书管理器: `certmgr.msc`
2. 受信任的根证书颁发机构 -> 证书
3. 把目标证书导入到“不信任的证书”

## Microsoft

- [MSDN I Tell You](https://msdn.itellyou.cn/)
