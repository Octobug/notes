# 第五章 Linux 文件权限与目录配置

## 目录

- [第五章 Linux 文件权限与目录配置](#第五章-linux-文件权限与目录配置)
  - [目录](#目录)
  - [5.1 使用者与群组](#51-使用者与群组)
  - [5.2 Linux 文件权限概念](#52-linux-文件权限概念)
    - [5.2.1 Linux 文件属性](#521-linux-文件属性)
    - [5.2.2 如何改变文件属性与权限](#522-如何改变文件属性与权限)
    - [5.2.3 目录与文件之权限意义](#523-目录与文件之权限意义)
    - [5.2.4 Linux 文件种类与扩展名](#524-linux-文件种类与扩展名)
  - [5.3 Linux 目录配置](#53-linux-目录配置)
    - [5.3.1 Linux 目录配置的依据 -- FHS](#531-linux-目录配置的依据----fhs)

## 5.1 使用者与群组

1. 文件拥有者
2. 群组概念
3. 其他人的概念

## 5.2 Linux 文件权限概念

### 5.2.1 Linux 文件属性

list: `ls -al`

```sh
# 类型与权限   属主      文件大小              文件名
-rw-r--r-- 1 root root  3796 Jan 11 03:24 .zshrc
#        链接数    属组         最后修改时间
```

1. 文件类型与权限:
    1. 文件类型
        - `[d]`: 目录
        - `[-]`: 文件
        - `[l]`: 连接文件
        - `[b]`: 块设备
        - `[c]`: 字符设备
    2. 三组 `rwx` 分别代表: 1. 属主的权限; 2. 属组的权限; 3. 其他用户的权限
        - `r`: read
        - `w`: write
        - `x`: execute
2. 链接到此 i-node 的文件数: 每个文件都会将其权限与属性记录到文件系统的 `i-node` 中
3. 文件属主名称
4. 文件属组名称
5. 文件大小，单位为 Bytes
6. 最近修改日期 (ls 的 `--full-time` 参数可显示完整日期)
7. 文件名

### 5.2.2 如何改变文件属性与权限

- `chgrp`: change group, 改变文件所属群组
- `chown`: change owner, 改变文件拥有者
- `chmod`: 改变文件权限, `SUID`/`SGID`/`SBIT` 等属性
  - 使用数字: r:4, w:2, x:1
  - 使用符号:

    ```sh
    chmod | u, g, o, a | +, -, = | r, w, x, <留空> | 文件

    # 例:
    chmod 755 filename
    # 逗号后不能有空格
    chmod u=rwx,go=rx filename
    ```

!`cp` 会复制**执行者**的属性与权限。

### 5.2.3 目录与文件之权限意义

- 权限对文件的重要性: `rwx` 是针对文件内容而言，而非文件的存在与否。
- 权限对目录的重要性: 目录主要内容为记录文件名清单
  - r: read contents in directory
    - 如使用 `ls`
  - w: modify contents of directory
    - 创建新文件与目录
    - 删除文件与目录 (无论文件的权限是什么)
    - 重命名文件或目录
  - x: access directory

| 类型 | 内容     | r            | w            | x                |
| ---- | -------- | ------------ | ------------ | ---------------- |
| 文件 | 详细数据 | 读取文件内容 | 修改文件内容 | 执行文件内容     |
| 目录 | 文件名   | 读取文件名   | 修改文件名   | 进入该目录的权限 |

例: 对于目录权限，有没有 r 权限的区别

- 有 r: 可列举目录内容

  ```sh
  ls: cannot access '/tmp/testing/testing': Permission denied
  total 0
  -????????? ? ? ? ?            ? testing
  ```

- 无 r: 无法列举目录内容

  ```sh
  ls -l /tmp/testing         
  ls: cannot open directory '/tmp/testing': Permission denied
  ```

### 5.2.4 Linux 文件种类与扩展名

- 文件种类
  - `-`: regular file, 普通文件
    - 文本文件 (text)
    - 二进制文件 (binary)
    - 数据格式文件 (data): 特定格式文件
  - `d`: directory, 目录
  - `l`: link, 链接
  - 设备文件
    - `b`: block, 块设备，可随机存取的周边设备，一般是存储设备
    - `c`: character, 字符设备，串行周边设备
  - `s`: sockets，数据接口文件
  - `p`: pipe, FIFO
- 文件扩展名: Linux 中没有所谓的扩展名，`.ext` 这种形式只是 convention
- 文件名限制
  - 单一文件或目录的最大文件名: 255Bytes, 即 255 个 ASCII 字符
  - 字符集: 不能用 ?><;&![]|\'"`(){}

## 5.3 Linux 目录配置

### 5.3.1 Linux 目录配置的依据 -- FHS

以 [FHS 3.0](../../fhs) 为准。
