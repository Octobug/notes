# Linux 操作系统 - 基础使用

## 目录

- [Linux 操作系统 - 基础使用](#linux-操作系统---基础使用)
  - [目录](#目录)
  - [1. Linux 版本](#1-linux-版本)
    - [1.1 应用](#11-应用)
    - [1.2 获取 Linux 版本](#12-获取-linux-版本)
    - [1.3 Linux 发行版](#13-linux-发行版)
  - [2. 几个基本操作](#2-几个基本操作)
    - [2.1 几个日常命令](#21-几个日常命令)
    - [2.2 几个重要快捷键 `[Tab]`, `[ctrl]-c`, `[ctrl]-d`](#22-几个重要快捷键-tab-ctrl-c-ctrl-d)
    - [2.3 两个编辑器](#23-两个编辑器)
    - [2.4 正确的关机方法](#24-正确的关机方法)
      - [2.4.1 数据同步写入磁盘: `sync`](#241-数据同步写入磁盘-sync)
      - [2.4.2 惯用的关机指令: `shutdown`](#242-惯用的关机指令-shutdown)
      - [2.4.3 重新开机/关机: `reboot`, `halt`, `poweroff`](#243-重新开机关机-reboot-halt-poweroff)
      - [2.4.4 实际使用管理工具 `systemctl` 关机](#244-实际使用管理工具-systemctl-关机)
  - [3. 获取帮助信息 `重点`](#3-获取帮助信息-重点)
    - [3.1 命令的 -h, --help](#31-命令的--h---help)
    - [3.2 man page](#32-man-page)
    - [3.3 info page](#33-info-page)
    - [3.4 其他有用的文件 (documents)](#34-其他有用的文件-documents)
  - [4. Linux 文件权限与目录配置 `重点`](#4-linux-文件权限与目录配置-重点)
    - [4.1 使用者与群组](#41-使用者与群组)
    - [4.2 Linux 文件权限概念](#42-linux-文件权限概念)
      - [4.2.1 Linux 文件属性](#421-linux-文件属性)
      - [4.2.2 如何改变文件属性与权限](#422-如何改变文件属性与权限)
      - [4.2.3 权限的意义](#423-权限的意义)
      - [4.2.4 Linux 文件种类与扩展名](#424-linux-文件种类与扩展名)
    - [4.3 Linux 目录配置](#43-linux-目录配置)
      - [4.3.1 Linux 目录配置的依据 -- FHS](#431-linux-目录配置的依据----fhs)
      - [4.3.2 目录树 (directory tree)](#432-目录树-directory-tree)
  - [5. Linux 文件与目录管理 `重点`](#5-linux-文件与目录管理-重点)
    - [5.1 目录与路径](#51-目录与路径)
      - [5.1.1 相对路径与绝对路径](#511-相对路径与绝对路径)
      - [5.1.2 目录的相关操作](#512-目录的相关操作)
      - [5.1.3 关于可执行文件路径的变量: `$PATH`](#513-关于可执行文件路径的变量-path)
    - [5.2 文件与目录管理](#52-文件与目录管理)
      - [5.2.1 文件与目录的检视: ls](#521-文件与目录的检视-ls)
      - [5.2.2 复制、删除与移动：cp, rm, mv](#522-复制删除与移动cp-rm-mv)
      - [5.2.3 获取路径文件名与目录名](#523-获取路径文件名与目录名)
    - [5.3 文件内容检视](#53-文件内容检视)
      - [5.3.1 完整检视文件](#531-完整检视文件)
      - [5.3.2 可翻页检视](#532-可翻页检视)
      - [5.3.3 部分检视](#533-部分检视)
      - [5.3.4 非纯文本文件: od](#534-非纯文本文件-od)
      - [5.3.5 修改文件时间或创建新文件: touch](#535-修改文件时间或创建新文件-touch)
    - [5.4 文件与目录的默认权限与隐藏权限](#54-文件与目录的默认权限与隐藏权限)
      - [5.4.1 文件默认权限: umask](#541-文件默认权限-umask)
      - [5.4.2 文件隐藏属性](#542-文件隐藏属性)
      - [5.4.3 文件特殊权限：SUID, SGID, SBIT](#543-文件特殊权限suid-sgid-sbit)
      - [5.4.4 观察文件类型: file](#544-观察文件类型-file)
    - [5.5 指令与文件的搜寻](#55-指令与文件的搜寻)
      - [5.5.1 指令文件名的搜寻](#551-指令文件名的搜寻)
      - [5.5.2 文件文件名的搜索](#552-文件文件名的搜索)
  - [6. Linux 磁盘与文件系统管理 `重点`](#6-linux-磁盘与文件系统管理-重点)
    - [6.1 认识 Linux 文件系统](#61-认识-linux-文件系统)
      - [6.1.1 文件系统特性](#611-文件系统特性)
      - [6.1.2 Linux 的 Ext2 文件系统 (inode)](#612-linux-的-ext2-文件系统-inode)
      - [6.1.3 文件系统与目录树的关系](#613-文件系统与目录树的关系)
      - [6.1.4 EXT2/EXT3/EXT4 文件的存取与日志式文件系统的功能](#614-ext2ext3ext4-文件的存取与日志式文件系统的功能)
      - [6.1.5 Linux 文件系统的运行](#615-linux-文件系统的运行)
      - [6.1.6 挂载点的意义 (mount point)](#616-挂载点的意义-mount-point)
      - [6.1.7 其他 Linux 支持的文件系统与 VFS](#617-其他-linux-支持的文件系统与-vfs)
    - [6.2 文件系统的简单操作](#62-文件系统的简单操作)
      - [6.2.1 磁盘与目录的容量](#621-磁盘与目录的容量)
      - [6.2.2 实体链接与符号链接: ln](#622-实体链接与符号链接-ln)
    - [6.3 磁盘的分区、格式化、检验与挂载](#63-磁盘的分区格式化检验与挂载)
      - [6.3.1 观察磁盘分区状态](#631-观察磁盘分区状态)
      - [6.3.2 磁盘分区: gdisk/fdisk](#632-磁盘分区-gdiskfdisk)
      - [6.3.3 磁盘格式化（创建文件系统）](#633-磁盘格式化创建文件系统)
      - [6.3.4 文件系统检验](#634-文件系统检验)
      - [6.3.5 文件系统挂载与卸载](#635-文件系统挂载与卸载)
        - [挂载操作](#挂载操作)
    - [6.4 设置开机挂载](#64-设置开机挂载)
      - [6.4.1 开机挂载 /etc/fstab 及 /etc/mtab](#641-开机挂载-etcfstab-及-etcmtab)
  - [7. 文件的压缩与打包](#7-文件的压缩与打包)
    - [7.1 压缩文件的用途与技术](#71-压缩文件的用途与技术)
    - [7.2 Linux 系统常见的压缩指令](#72-linux-系统常见的压缩指令)
      - [7.2.1 gzip, zcat/zmore/zless/zgrep](#721-gzip-zcatzmorezlesszgrep)
      - [7.2.2 bzip2, bzcat/bzmore/bzless/bzgrep](#722-bzip2-bzcatbzmorebzlessbzgrep)
      - [7.2.3 xz, xzcat/xzmore/xzless/xzgrep](#723-xz-xzcatxzmorexzlessxzgrep)
        - [对比](#对比)
    - [7.3 打包指令: tar](#73-打包指令-tar)
      - [7.3.1 tar](#731-tar)
        - [tarfile 与 tarball?](#tarfile-与-tarball)
    - [7.4 其他相关工具](#74-其他相关工具)
  - [8. 认识与学习 BASH](#8-认识与学习-bash)
    - [8.1 认识 BASH 这个 Shell](#81-认识-bash-这个-shell)
      - [8.1.1 系统的合法 shell 与 /etc/shells 功能](#811-系统的合法-shell-与-etcshells-功能)
      - [8.1.2 Bash shell 的功能](#812-bash-shell-的功能)
      - [8.1.3 查询指令是否为 Bash shell 的内置命令: type](#813-查询指令是否为-bash-shell-的内置命令-type)
    - [8.2 Shell 的变量功能](#82-shell-的变量功能)
      - [8.2.1 变量的取用与设置: echo, 变量设置规则, unset](#821-变量的取用与设置-echo-变量设置规则-unset)
      - [8.2.2 环境变量](#822-环境变量)
      - [8.2.3 从输入读取变量、数组与声明: read, array, declare](#823-从输入读取变量数组与声明-read-array-declare)
      - [8.2.4 与文件系统及进程的限制关系: ulimit](#824-与文件系统及进程的限制关系-ulimit)
      - [8.2.5 变量内容的删除、取代与替换 (Optional)](#825-变量内容的删除取代与替换-optional)
    - [8.3 命令别名与历史命令](#83-命令别名与历史命令)
      - [8.3.1 命令别名设置: alias, unalias](#831-命令别名设置-alias-unalias)
      - [8.3.2 历史命令: history](#832-历史命令-history)
    - [8.4 Bash Shell 的操作环境](#84-bash-shell-的操作环境)
      - [8.4.1 路径与命令搜索顺序](#841-路径与命令搜索顺序)
      - [8.4.2 bash 的登录欢迎信息: /etc/issue, /etc/motd](#842-bash-的登录欢迎信息-etcissue-etcmotd)
      - [8.4.3 bash 的环境配置文件](#843-bash-的环境配置文件)
      - [8.4.4 终端机的环境设置: stty, set](#844-终端机的环境设置-stty-set)
      - [8.4.5 bash 中的特殊符号](#845-bash-中的特殊符号)
    - [8.5 数据流重定向](#85-数据流重定向)
      - [8.5.1 什么是数据流重定向](#851-什么是数据流重定向)
      - [8.5.2 命令执行的判断依据: ;, &&, ||](#852-命令执行的判断依据---)
    - [8.6 管道命令 (pipe)](#86-管道命令-pipe)
      - [8.6.1 截取命令: cut, grep](#861-截取命令-cut-grep)
      - [8.6.2 排序命令: sort, wc, uniq](#862-排序命令-sort-wc-uniq)
      - [8.6.3 双重重定向: tee](#863-双重重定向-tee)
      - [8.6.4 字符转换命令: tr, col, join, paste, expand](#864-字符转换命令-tr-col-join-paste-expand)
      - [8.6.5 文件分割命令: split](#865-文件分割命令-split)
      - [8.6.6 参数替换: xargs](#866-参数替换-xargs)
      - [8.6.7 关于减号 - 的用途](#867-关于减号---的用途)

## 1. Linux 版本

### 1.1 应用

- 桌面
- 服务器
- 嵌入式/移动设备

### 1.2 获取 Linux 版本

获取版本号：

```sh
$ uname -r
4.15.0-166-generic
```

- 格式: `major.minor.patch-build.desc`
  - generic: 通用版本

### 1.3 Linux 发行版

- 可完全安装的 Linux 发布套件：内核 + 应用软件 + 工具 + 文档
- 各大 Linux Distributions 的s支持标准
  - Linux Standard Base (LSB): <https://wiki.linuxfoundation.org/lsb/start>
  - Filesystem Hierarchy Standard (FHS): <https://refspecs.linuxfoundation.org/FHS_3.0/fhs/index.html>
- 两个主要派系
  - Debian
    - Debian GNU/Linux
    - Ubuntu
    - ...
  - Red Hat
    - Fedora
    - CentOS
    - ...

## 2. 几个基本操作

```sh
command [-options] parameter1 parameter2 ... \
  ...
```

### 2.1 几个日常命令

1. 显示日期时间: `date`:

    时区定义: `/usr/share/zoneinfo`
    `TZ=Asia/Shanghai date "+%Y/%m/%d %H:%M:%S"`

2. 显示日历: `cal`: `cal [month] [year]`
3. 计算器: `bc`:
    - 小数位数: `scale=3`

### 2.2 几个重要快捷键 `[Tab]`, `[ctrl]-c`, `[ctrl]-d`

- [Tab] 按键: 命令与文件名补全
  - 第一个位置为"命令补全"
  - 第二个位置及以后为"文件补全"
  - 如安装软件的 `bash-completion`，则会有子命令/选项/参数补全
- [Ctrl]-c 按键: 终止当前程序
- [Ctrl]-d 按键: `EOF`, 相当于输入 `exit`

### 2.3 两个编辑器

- nano
  - 按键说明
    - `^KEY`: `^` 代表 [Ctrl]
    - `M-KEY`: `M` 代表 [Alt]
- vim

### 2.4 正确的关机方法

Linux 是多用户环境，不可随便关机。

- 观察系统使用状态
  - `who`: 查看在线用户
  - `netstat -a`: 网络连接状态
  - `ps -aux`: 进程列表
- 通知在线用户关机: `shutdown`
- 数据同步写入磁盘: `sync`
- 关机: `shutdown`
- 重启: `reboot`, `halt`, `poweroff`

#### 2.4.1 数据同步写入磁盘: `sync`

为了加快数据读写速度，内存中的数据改动并不会立即被写回磁盘。`sync`
正是用于显式触发数据写入磁盘的。

`shutdown`/`reboot`/`halt` 执行时会自动调用 `sync`。

每个账号调用 `sync` 只会更新自身的数据，root 账号会同步全局的数据。

#### 2.4.2 惯用的关机指令: `shutdown`

- 自由选择关机模式：关机或重启 `-r`
- 设置关机时间：立刻 `-h` 或指定时刻
- 自定义关机消息：关机之前发送消息给在线用户
- 仅发出警告信息：发送消息给在线用户而不关机 `-k`
- 停机: `-H`/`--halt`, 指示硬件使 CPU 停止工作，但系统处于通电状态

例：

```sh
sudo shutdown -h 10 'I will shutdown after 10 mins'
# 取消关机计划
sudo shutdown -c
```

#### 2.4.3 重新开机/关机: `reboot`, `halt`, `poweroff`

实际上以上几个关机/重启命令都是调用 `systemctl` 实现的。

```sh
# 停机
halt
# 关机
poweroff
```

#### 2.4.4 实际使用管理工具 `systemctl` 关机

目前的 `init` 命令只是 Linux 为了兼容而提供，使用 `init 0` 也可以关机，但跟所谓的
“执行等级”已经无关。

```sh
systemctl [COMMAND]

# halt: 停机，屏幕可能会保留一些信息，这与电源管理模式有关
# poweroff: 彻底的关机，断开电源
# reboot: 重启
# suspend: 休眠
```

## 3. 获取帮助信息 `重点`

### 3.1 命令的 -h, --help

### 3.2 man page

- man page section: `man man`
- man page 结构:

  | 部分        | 内容说明                                     |
  | ----------- | -------------------------------------------- |
  | NAME        | 简短的指令、数据名称说明                     |
  | SYNOPSIS    | 简短的指令下达语法 (syntax) 简介             |
  | DESCRIPTION | 较为完整的说明                               |
  | OPTIONS     | 针对 SYNOPSIS 部分，列举所有可用的选项说明   |
  | COMMANDS    | 当前软件提供的命令                           |
  | FILES       | 这个程序或数据所使用或参考或链接到的某些文件 |
  | SEE ALSO    | 可以参考的，跟这个指令或数据相关的其他说明   |
  | EXAMPLE     | 一些参考范例                                 |

- man page 数据通常位于 `/usr/share/man` 目录，根据不同发行版，可通过以下文件修改。
  - `/etc/`
    - `man_db.conf`
    - `man.conf`
    - `man.config`
    - `manpath.conf`
    - `manpath.config`

- 搜索特定指令/文件的 man page 说明文档

  `man [section] keyword`, 没有指定 section number 时，man 会显示先搜索到的文档。
  - `man -f man` 或 `whatis`: 按照 manual 名称搜索
  - `man -k man` 或 `apropos`: 按照 manual 内容关键字搜索
  - mandb

### 3.3 info page

info 是 Linux 特有的，与 man 的用途差不多，主要区别是 info page 将文件数据拆成一个个段落，
并提供链接跳转。

- `info info`: `h` 键显示操作帮助
  - File: 当前 info page 的数据来源
  - Node: 当前 info page 所属内容节点
  - Next: 当前 info page 的下一个节点，按键 "N"
  - Up: 回到上一层的节点总览，按键 "U"
  - Prev: 回到前一个节点，按键 "P"
- `info coreutils`
- 存储位置: `/usr/share/info`

### 3.4 其他有用的文件 (documents)

- `/usr/share/doc`

## 4. Linux 文件权限与目录配置 `重点`

list: `ls -al`

### 4.1 使用者与群组

1. 文件拥有者
2. 群组
3. 其他人

### 4.2 Linux 文件权限概念

#### 4.2.1 Linux 文件属性

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

#### 4.2.2 如何改变文件属性与权限

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

#### 4.2.3 权限的意义

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

#### 4.2.4 Linux 文件种类与扩展名

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

### 4.3 Linux 目录配置

#### 4.3.1 Linux 目录配置的依据 -- FHS

- 可分享的：可以分享给其他系统挂载使用的目录，包括可执行文件与使用者的邮件等数据，
  是能够分享给网络上其他主机挂载用的目录；
- 不可分享的：自己机器上允许的设备文件或是与程序有关的 socket 文件等，由于仅与自身机器有关，
  所以不适合分享给其他主机；
- 不变的：有些数据不会经常变动，跟随着发行版而不变。如函数库、文件、说明文档、
  系统管理员管理的主机服务配置文件等；
- 可变的：经常改变的数据，例如登录日志、系统及进程的运行数据等。

浏览一下: [Filesystem Hierarchy Standard 3.0](./fhs)

FHS 针对目录树架构定义出三个目录下应该放置什么数据：

- `/`: 与开机系统相关；
- `/usr` (unix software resource): 与软件安装/执行相关；
- `/var` (variable): 与系统运行过程相关；

详解：

- 根目录 `/` 的意义与内容：其他目录都由此衍生，同时根目录也和开机/还原/修复等动作相关。
  系统开机需要特定的软件、内核文件、函数库文件等数据，系统出现错误时根目录必须包含能修复系统的
  程序。
  
  FHS 建议：根目录分区越小越好，且软件、数据不要和根目录放在同一分区。

  FHS 定义根目录下应该有以下目录：

  | Part 1: 必须目录 | 内容                                            |
  | ---------------- | ----------------------------------------------- |
  | /bin             | 所有用户使用的命令                              |
  | /boot            | Linux 内核文件, loader, 开机配置文件等          |
  | /dev             | 设备文件及特殊文件                              |
  | /etc             | 系统主要配置文件                                |
  | /lib             | 系统、程序的函数库，`/lib/modules` 放置内核模块 |
  | /media           | 可移除的媒体文件，软盘、光盘常挂载于此          |
  | /mnt             | 额外设备临时挂载点                              |
  | /opt             | 第三方附加软件                                  |
  | /run             | 系统运行的数据文件                              |
  | /sbin            | 系统、管理员使用的程序及命令。                  |
  | /srv             | 网络服务使用的数据目录                          |
  | /tmp             | 临时文件目录，FHS 建议系统开机时自动清空        |
  | /usr             | user system resources                           |
  | /var             | 放置变化的数据                                  |
  | Part 2: 建议目录 |                                                 |
  | /home            | 用户主目录                                      |
  | `/lib<qual>`     | 例如 /lib64                                     |
  | /root            | root home 目录                                  |

  其他非 FHS 规定的常见目录：

  | 其他目录    | 内容                                                        |
  | ----------- | ----------------------------------------------------------- |
  | /lost+found | ext2/3/4 文件系统产生的目录，发生错误时遗失的片段会放置在此 |
  | /proc       | 虚拟文件系统，存在于内存，存放内核、进程信息                |
  | /sys        | 虚拟文件系统，存在于内存，存放内核与硬件相关的信息          |

- `/usr` 的意义与内容：可分享(给其他主机)且不可变

  | Part 1: 必须目录 | 内容                                                 |
  | ---------------- | ---------------------------------------------------- |
  | /usr/bin         | 用户能使用的命令都在这里, 有些发行版将 /bin 链接于此 |
  | /usr/lib         | 有些发行版将 /lib 链接于此                           |
  | /usr/local       | 管理员为本机安装的软件                               |
  | /usr/sbin        | 有些发行版将 /sbin 链接于此                          |
  | /usr/share       | 不分架构的只读共享文件                               |
  | Part 2: 建议目录 |                                                      |
  | /usr/games       | 游戏数据文件                                         |
  | /usr/include     | 头文件                                               |
  | /usr/libexec     | 不被一般用户使用的命令或脚本                         |
  | `/usr/lib<qual>` | 有些发行版将 `/lib<qual>` 链接于此                   |
  | /usr/src         | 核心源码                                             |

- `/var` 的意义与内容：变化的数据文件，如缓存、日志、进程文件

  | Part 1: 必须目录 | 内容                                   |
  | ---------------- | -------------------------------------- |
  | /var/cache       | 缓存文件                               |
  | /var/lib         | 程序执行过程使用的库文件               |
  | /var/lock        | 锁文件，由 Debian 引入变动为 /run/lock |
  | /var/log         | 日志文件                               |
  | /var/mail        | 用户邮件                               |
  | /var/run         | PID 等进程数据                         |
  | /var/spool       | 待处理数据                             |

- 针对 FHS，各家发行版的差异
  - /bin --> /usr/bin
  - /sbin --> /usr/sbin
  - /lib --> /usr/lib
  - /lib64 --> /usr/lib64
  - /var/lock --> /run/lock
  - /var/run --> /run

#### 4.3.2 目录树 (directory tree)

- 目录树的起始点为 `/`
- 每一个目录可以使用本地磁盘分区的文件系统，也可以使用网络文件系统，比如使用 NFS (Network
  File System) 挂载特定目录
- 每一个文件的文件名 (完整路径) 都是独一无二的

## 5. Linux 文件与目录管理 `重点`

### 5.1 目录与路径

#### 5.1.1 相对路径与绝对路径

- 绝对 (absolute) 路径: 从 `/` 开始写起的文件路径
- 相对 (relative) 路径: 相对于当前路径的文件路径

⚠️ 在使用 shell 脚本管理系统时，务必优先使用绝对路径，因为它更不容易被写错。

#### 5.1.2 目录的相关操作

特殊目录：

- `.`: 当前目录
- `..`: 上层目录
- `-`: 前一个工作目录
- `~`: 当前用户 home 目录
- `~username`: 用户 username 的 home 目录

常用目录相关命令：

- cd
- pwd
- mkdir
- rmdir

#### 5.1.3 关于可执行文件路径的变量: `$PATH`

系统会从 `$PATH` 变量中的每个目录下搜索指定的可执行文件名，先搜索到的会被执行。

```sh
$ echo $PATH
/home/linshaobiao/bin:/usr/local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
```

例题：为什么 $PATH 目录不加入当前目录 `.`？

答：加入当前目录确实可以方便命令执行，但由于用户经常切换目录，如果不同目录之间有名称一致的命令，
可能反而造成混乱。此外，如果有人在 `/tmp` 目录下放了一个恶意的 `ls` 命令，
那么被攻击的概率就很高了。

### 5.2 文件与目录管理

#### 5.2.1 文件与目录的检视: ls

- `-a`: 列出所有文件
- `-A`: 列出除 `.` 和 `..` 的所有文件
- `-d`: 仅列出目录本身
- `-f`: 不排序, ls 默认以文件名排序
- `-F`: 显示文件类型
  - `*`: 可执行文件
  - `/`: 目录
  - `=`: socket
  - `|`: FIFO 文件
- `-h`: 人类易读的格式
- `-i`: 列出 inode 号
- `-l`: 列出详细信息
- `-n`: 列出 UID/GID 而非名称
- `-r`: 反向排序
- `-R`: 递归列出子目录
- `-S`: 按文件大小排序
- `-t`: 按修改时间排序
- `--full-time`: 列出完整时间

#### 5.2.2 复制、删除与移动：cp, rm, mv

- cp: 不同用户执行会产生不同结果，尤其对于 `-a` 和 `-p` 来说。
  - `-a`: 相当于 `-dr --preserve=all`
  - `-d`: 若 src 文件为链接文件，则复制链接文件而非文件本身
  - `-f`: force, 若目标文件已存在且无法打开，则移除后重试
  - `-i`: interactive 模式
  - `-l`: 使用硬链接创建，而非复制文件本身
  - `-p`: 连同文件的属性（权限、用户、时间）一并复制，而非使用默认属性
  - `-r`: 递归复制
  - `-s`: 符号链接
  - `-u`: dest 比 src 旧才更新
  - `--preserve=all`: 除了 `-p` 的权限相关参数外，还加入 SELinux 的属性。

  例:

  ```sh
  # 使用 root 复制 ~/.bashrc
  sudo cp ~/.bashrc /tmp/bashrc
  # 创建 /tmp/bashrc 的符号链接
  cp -s bashrc bashrc_slink
  # 创建 /tmp/bashrc 的硬链接
  cp -l bashrc bashrc_hlink
  # 将 bashrc_slink 复制为 bashrc_slink_1 与 bashrc_slink_2
  cp bashrc_slink bashrc_slink_1
  cp -d bashrc_slink bashrc_slink_2
  ```

- rm: 移除文件与目录
  - `-f`: 强制删除
  - `-i`: interactive 模式
  - `-r`: 递归删除

  ```sh
  # 反斜线可以忽略掉 alias
  \rm -r /tmp/etc
  ```

- mv: 移动文件目录，或重命名
  - `-f`: force
  - `-i`: interactive 模式
  - `-u`: dest 比 source 旧才会更新覆盖

#### 5.2.3 获取路径文件名与目录名

- `basename`
- `dirname`

### 5.3 文件内容检视

#### 5.3.1 完整检视文件

- cat (concatenate)
  - `-A`: 相当于 `-vET`
  - `-b`: 显示非空行的行号
  - `-E`: 显示换行号为 $
  - `-n`: 显示所有行的行号
  - `-T`: 显示 tab 键位 `^I`
  - `-v`: 显示不可打印字符

  ```sh
  cat /etc/issue
  ```

- tac: 行反向显示
- nl: 添加行号打印

#### 5.3.2 可翻页检视

- more: 翻页检视
  - `空格`键: 向下翻一页
  - `b`或`[Ctrl]+b`: 向上翻页
  - `回车`键: 向下翻一行
  - `/字符串`: 向下搜索"字符串"
  - `:f`: 显示出文件名及当前显示的行数
  - `q`: 离开
- less: 比 more 灵活一点的翻页检视, man page 使用的就是 less, 除了 more 支持的操作,
  less 还支持:
  - `[PageDown]`键: 向下翻一页
  - `[PageUp]`: 向上翻页
  - `?字符串`: 向上搜索"字符串"
  - `n`: 重复前一个搜索内容
  - `N`: 反向重复前一个搜索内容
  - `g`: 跳转到第一行
  - `G`: 跳转到最后一行
  - `q`: 离开

#### 5.3.3 部分检视

- head (显示前几行)
  - `-n`: 指定行数，当行数为负数时，代表显示文件除了最后 abs(n) 行前的所有行
- tail (显示后几行)
  - `-n`: 指定行数
  - `-f`: 持续显示文件追加的内容
  
#### 5.3.4 非纯文本文件: od

- `-t`: 指定文件类型
  - `a`: 使用默认字符输出
  - `c`: 使用 ASCII 字符输出
  - `d[size]`: 使用十进制输出
  - `f[size]`: 使用浮点数输出
  - `o[size]`: 使用八进制输出
  - `x[size]`: 使用十六进制输出
    - `[size]`: size 可以是数字，也可以是
      - C: sizeof(char)
      - D: sizeof(double)
      - F: sizeof(float)
      - I: sizeof(int)
      - L: sizeof(long)
      - S: sizeof(short)

  ```sh
  # 快速获取字符 ASCII 码
  echo abc | od dCc
  ```

#### 5.3.5 修改文件时间或创建新文件: touch

- mtime (modification time): 文件内容（不包括属性或权限）变更的时间
- ctime (status time): 文件权限、属性等状态变更的时间
- atime (access time): 文件内容被访问的时间

选项参数：

- `-a`: 只修改 atime
- `-c`: 只修改文件三种时间，文件不存在时不会创建新文件
- `-d`: 指定日期
- `-m`: 只修改 mtime
- `-t`: 指定时间 `[YYYYMMDDhhmm]`
- `--date="日期时间"`

复制文件时，即使使用了 `cp -a` 也无法复制 ctime 的属性。

### 5.4 文件与目录的默认权限与隐藏权限

除了 rwx 外，Linux 传统的 Ext2/3/4 文件系统下还有其他文件属性，使用 `chattr` 设置，
`lsattr` 查看。

#### 5.4.1 文件默认权限: umask

- `-S`: 显示为符号类型

最大权限值减去 umask 值得到的就是创建文件时默认的权限。

- 文件：默认没有可执行权限，因此默认最大权限为 `-rw-rw-rw-`
- 目录：默认有可执行权限，最大默认权限值为 `drwxrwxrwx`

例：umask 为 `022`，创建文件时，默认权限为:

- 文件：644
- 目录：755

#### 5.4.2 文件隐藏属性

仅适用于 Ext2/3/4 文件系统。

- `chattr`: 设置文件隐藏属性
  - `+`: 增加某个特殊属性
  - `-`: 移除某个特殊属性
  - `=`: 设置指定属性
  - 属性值
    - `A`: 文件将不会改变 atime
    - `S`: 文件变更即时 sync
    - `a`: 文件只能追加数据
    - `c`: 文件将被自动压缩
    - `d`: 不会被 dump 命令备份
    - `i`: 将文件变成完全只读
    - `s`: 文件被删除时将被彻底移除出磁盘，无法恢复
    - `u`: 与 `s` 相反，设置 u 的文件被删除后可被恢复
- `lsattr`: 显示文件隐藏属性
  - `-a`: 将隐藏文件的属性也显示出来
  - `-d`: 仅列出目录本身的属性
  - `-R`: 递归显示子目录数据属性

#### 5.4.3 文件特殊权限：SUID, SGID, SBIT

- Set UID: `s` 标志出现在 owner 的 x 权限位：
  - SUID 仅对二进制程序有效；
  - 执行者需要有 x 权限；
  - 执行者在运行时将拥有 owner 权限。

  ```sh
  # 典型文件 /usr/bin/passwd
  $ ls -l /usr/bin/passwd
  -rwsr-xr-x 1 root root 59640 Mar 22  2019 /usr/bin/passwd
  # 该命令会修改文件 /etc/shadow
  $ ls -l /etc/shadow
  -rw-r----- 1 root shadow 1253 Jan 11 03:38 /etc/shadow
  ```

- Set GID: `s` 标志出现在 group 的 x 权限位：
  - SGID 仅对二进制程序有效；
  - 执行者需要有 x 权限；
  - 执行者在运行时将拥有 group 权限。

  ```sh
  $ ls -lH /usr/bin/locate
  -rwxr-sr-x 1 root mlocate 43088 Mar  1  2018 /usr/bin/locate
  # locate 命令会使用文件 /var/lib/mlocate/mlocate.db 
  $ ls -l /var/lib/mlocate/mlocate.db 
  -rw-r----- 1 root mlocate 3002308 Jan 18 06:25 /var/lib/mlocate/mlocate.db
  ```

  - 对于某个目录
    - 使用者对该目录有 `r` 与 `x` 权限
    - 使用者在该目录下的生效 group 将变成该目录的 group；
    - 用途：若使用者在该目录下有 `w` 权限，则其创建的新文件 group 与该目录相同

- Sticky Bit: `t` 标志出现在 x 权限位：
  - 使用者对目录有 `w`, `x` 权限
  - 使用者在该目录下创建文件时，只有自己及 root (实测似乎是目录 owner 即可) 才有权限删除。

  ```sh
  # 典型目录
  $ ls -ld /tmp 
  drwxrwxrwt 7 root root 4096 Jan 18 09:12 /tmp
  ```

- SUID/SGID/SBIT 权限设置：权限的数字模式前再加一位
  - SUID: 4
  - SGID: 2
  - SBIT: 1
  
  例：将一个文件权限设置为 `-rwsr-xr-x`: `chmod 4755`。

  当权限位出现大写的 `S` 跟 `T` 时，说明设置无效，因为缺少 x 权限。

- 总结
  - 文件具有 SUID 时，代表使用者在运行时能拥有命令 owner 的权限
  - 目录具有 SGID 时，代表使用者在该目录下新建的文件 group 与该目录一致
  - 目录具有 SBIT 时，代表使用者在该目录下新建的文件只有自己与 root 能删除

#### 5.4.4 观察文件类型: file

### 5.5 指令与文件的搜寻

#### 5.5.1 指令文件名的搜寻

- `which`
  - `-a`: 将 `$PATH` 中所有可找到的命令全部列出

#### 5.5.2 文件文件名的搜索

- `whereis`: 在特定目录中寻找文件名
  - `-l`: 列出 whereis 搜索的目录
  - `-b`: 只寻找 binary 文件
  - `-m`: 只寻找 manual 文件
  - `-s`: 只寻找 source 文件
  - `-u`: 搜索其他文件
- `locate`: 基于数据库搜索，数据库会定期自动更新
  - `-i`: 忽略大小写
  - `-c`: 仅输出找到的文件数量
  - `-l`: 仅输出指定行数
  - `-S`: 输出 locate 使用的数据库文件相关信息
  - `-r`: 使用正则表达式
- `updatedb`: 手动更新 locate 数据库。(`/etc/updatedb.conf`)
- `find`: 直接搜索文件系统，`find [PATH] [option] [action]`
  - 1. 与时间有关的选项
    - `-atime`, `-ctime`, `-mtime`
      - `n`: n 天之前的"一天之内"
      - `+n`: n 天之前，不含 n 天本身
      - `-n`: n 天之内，含 n 天本身

      ```diagram
                <`4`>
      <---`+4`---|   |-----`-4`------>
      <--|---|---|---|---|---|---|---|
        7   6   5   4   3   2   1  now
      ```

    - `-newer` file: 比 file 更新的文件

  - 2. 与 user 和 group 有关的参数
    - `-uid n`: 按 user id 查找
    - `-gid n`: 按 group id 查找
    - `-user name`: 按 user name 查找
    - `-group name`: 按 group name 查找
    - `-nouser`: 寻找 user 不存在的文件
    - `-nogroup`: 寻找 group 不存在的用户
  - 3. 与文件权限及名称有关的参数
    - `-name filename`: 按文件名称搜索
    - `-size [+-]SIZE`: 按文件大小搜索
      - k
      - M
      - G
      - T
      - ...
    - `-type TYPE`
      - f: 普通文件
      - b: 块设备
      - c: 字符设备
      - d: 目录
      - l: 链接
      - s: socket
      - p: FIFO
    - `-perm mode`: 搜素权限等于 mode 的文件
    - `-perm -mode`: 搜索权限包含 mode 的文件 (dest >= mode)
    - `-perm /mode`: 搜索权限被 mode 包含的文件 (dest <= mode)
      - `mode` 为数字模式
  - 4. 额外动作
    - `-print`: 打印结果（默认动作）
    - `-exec command`: `-exec command {} \;`
      - `{}` 代表由 find 找到的内容，作为 command 的参数
      - `\;`: `-exec ... \;` 为关键字，`\;` 为结束符，其中 `\` 是为了转义

例题：使用户能执行 `cp /dir1/file1 /dir2` 的最小权限。

答：

- dir1: x
- file1: r
- dir2: w + x

## 6. Linux 磁盘与文件系统管理 `重点`

### 6.1 认识 Linux 文件系统

磁盘设备文件名：

- `/dev/sd[a-p][1-128]`: 实体磁盘的磁盘文件名
- `/dev/vd[a-d][1-128]`: 虚拟磁盘的磁盘文件名

#### 6.1.1 文件系统特性

格式化：初始化分区的文件系统，使操作系统能识别。

常见的文件系统有：

- FAT (File Allocation Table)
- NTFS (New Technology File System)
- Ext2 (Second Extended File System)/3/4

文件系统的文件数据除了文件实际内容外，通常还包含其他属性（权限、文件属性等）。
文件系统通常将这两部分数据分别存放在不同区块。权限与属性存在 inode 中，文件实际数据则在 data
block 中。另外还有一个超级区块 superblock 记录整个文件系统的整体信息，包括 inode 与 block
的总量、使用量、剩余量等。

每个 inode 与 block 都有编号：

- superblock: 记录此文件系统的整体信息，包括 inode/block 总量、使用量、剩余量及
  文件系统格式和其他信息
- inode: 记录文件的属性，一个文件占用一个 inode，同事记录此文件实际数据所在的 block 号
- block: 记录文件实际内容，如果文件较大会占用多个 block

假设文件系统格式化出了 inode 与 block 两种区块，某个 inode 记录了 4 个 block，
操作系统能一次性将 4 个 block 读取出来，则这种数据存储方式成为索引式文件系统
(indexed allocation)。

FAT 文件系统没有 inode 存在，每个 block 号都存在前一个 block 中，因此只能一个接一个读取。

#### 6.1.2 Linux 的 Ext2 文件系统 (inode)

inode: index node

最开始部分为 `boot sector`

文件系统在格式化时已经规划好 inode 与 block，除非重新格式化或使用 `resize2fs`
命令才能修改。

Ext2 在格式化时将 block 分成多个 block group，每个 group 里都有独立的
inode/block/superblock 系统。

每个 block group 有六个部分：

1. data block (数据区块): 用于放置文件内容数据，block 大小有 1K, 2K, 4K 三种。

    | Block 大小         | 1KB  | 2KB   | 4KB  |
    | ------------------ | ---- | ----- | ---- |
    | 最大单一文件限制   | 16GB | 256GB | 2TB  |
    | 最大文件系统总容量 | 2TB  | 8TB   | 16TB |

    - block 的大小与数量在格式化完成后就无法改变，除非重新格式化
    - 每个 block 最多存放一个文件的内容
    - 如果文件大于 block 的大小，则会占用多个 block
    - 如果文件小于 block，则剩余空间无法利用

    如果 block 太小，则大文件会占用更多的 block, 导致 inode 要记录跟多 block 编号。

2. inode table (inode 表)
    - 每个 inode 记录的内容
      - 文件的权限 (read/write/execute)
      - 文件的用户信息 (owner/group)
      - 文件的容量
      - 文件创建或状态改变的时间 (ctime)
      - 文件最近的访问时间 (access)
      - 文件最近的修改时间 (mtime)
      - 文件特殊属性 (SUID/GUID/SBIT)
      - 文件内容指向 (pointer)
    - inode 的数量与大小在格式化时已固定
      - 每个 inode 大小为 128 Bytes (ext4 与 xfs 支持 256 Bytes)
      - 每个文件只占用一个 inode
      - 文件系统能创建的文件数量与 inode 直接相关
      - 系统访问文件时会先找到 inode, 分析用户是否有权限访问后才开始访问 block
      - 记录每个 block 占用 4 Bytes
    - inode 的 block 索引组成 (以 1KB block 为例)
      - 12 个直接索引: 12 * 1K = 12K
      - 1 个 1 层间接索引: 每个 block 可记录 1K/4B=256 个 block, 1K * 256 = 256K
      - 1 个 2 层间接索引: 1K * 256^2 = 64M
      - 1 个 3 层间接索引: 1K * 256^3 = 16G
3. superblock (超级区块): 记录整个文件系统相关信息
    - superblock 大小为 1024Bytes
    - 记录的项目
      - block 与 inode 总量
      - 未使用与已使用的 inode 与 block 数量
      - block 与 inode 的大小 (block 可以是 1,2,4K, inode 为 128Bytes,
        256Bytes(Ext4))
      - 文件系统的挂载时间，最近一次写入时间，最近一次磁盘检查 (fsck) 时间等
      - 一个 valid bit 数值
        - 0: 已挂载
        - 1: 未挂载
    - 每个文件系统只有一个 superblock，除了第一个 block group，后续的 group
      里不一定会有 superblock，有的话则是作为副本备用
4. Filesystem Description (文件系统描述): 描述每个 block group 的开始与结束的 block
  号码，以及说明每个区段 (superblock, bitmap, inodemap, data block) 分别介于哪个
  block 号码之间。可用 `dumpe2fs` 观察。
5. block bitmap (区块对照表): 记录 block 是否已使用
6. inode bitmap (inode 对照表): 记录 inode 是否已使用

- `dumpe2fs`: 查询 Ext 家族文件系统 superblock 信息
- `blkid`: 列出系统已格式化设备

#### 6.1.3 文件系统与目录树的关系

目录与文件在文件系统中如何记录数据的呢？

- 目录: 创建目录时，文件系统至少分配一个 inode 与一个 block。
  - inode: 记录目录相关权限与属性，并记录分配到的 block 号码。
  - block: 记录目录下的文件信息
    - 文件名
    - 对应文件占用的 inode 号
  - `ls -li`: 查看文件 inode 号
- 文件: 创建普通文件时，文件系统会分配一个 inode 和适应文件大小的若干个 block

目录树的读取：文件名记录于目录 block 中，因此读写文件时必然经过目录的 inode 与 block，
最终获取到目标文件的 inode 与 block。

例：系统如何读取 `/etc/passwd` 文件？

```sh
$ ll -di / /etc /etc/passwd
     2 drwxr-xr-x 24 root root 4.0K Jan 11 03:22 /
655361 drwxr-xr-x 94 root root 4.0K Jan 18 13:02 /etc
665481 -rw-r--r--  1 root root 1.8K Jan 11 03:38 /etc/passwd
```

1. `/` 的 inode: 通过挂载点信息找到根目录 inode 为 2 号e，且权限允许读取 block
2. `/` 的 block: 读取 block 得到 `etc/` 目录的 inode 为 655361
3. `etc/` 的 inode: 读取 655361 号 inode，且权限允许读取 block
4. `etc/` 的 block: 读取 block 得到 `passwd` 文件的 inode 为 665481
5. `passwd` 的 inode: 读取 665481 号 inode，且权限允许读取 block
6. `passwd` 的 block: 读取 block 内容

#### 6.1.4 EXT2/EXT3/EXT4 文件的存取与日志式文件系统的功能

文件系统新增一个文件的流程：

1. 先确定用户对于新增文件目录是否有 `w` 与 `x` 权限
2. 根据 inode bitmap 找到空闲 inode 号码，将新文件的权限/属性写入
3. 根据 block bitmap 找到空闲的 block 号码，将实际数据写入 block，且更新 inode 的
 block 索引
4. 将写入的 inode 与 block 数据同步更新到 inode bitmap 与 block bitmap，并更新
 superblock 内容

数据的不一致 (Inconsistent) 状态: 系统故障导致写入过程不完整，使得 metadata
(inode bitmap、block bitmap、superblock) 信息不一致

- Ext2: 系统开机时根据 superblock 的 valid bit (是否挂载) 与文件系统状态 (clean 与否)
  等状态判断是否强制对整个文件系统进行数据一致性检查 (使用 `e2fsck`)
- 日志式文件系统 (Journaling filesystem): 文件系统中专门记录写入或修改文件时的步骤
  1. 预备: 系统要写入一个文件时，会先在日志记录区块中记录某个文件要写入的信息；
  2. 实际写入: 写入文件的权限与数据；更新 metadata；
  3. 结束: 完成数据与 metadata 更新后，在日志记录区块中完成改文件的记录。

  当写入过程发生问题，系统只需要检查日志记录区块再进行针对性的一致性检查，
  而不需要检查整个文件系统。

#### 6.1.5 Linux 文件系统的运行

系统加载一个文件到内存后，如果文件没有被更改过，那么内存里的文件数据会被标记为 clean,
否则为 dirty。系统定期将内存中标记为 dirty 的数据写回磁盘以确保一致性。

Linux 文件系统与内存：

- 常用文件数据放置于内存缓冲区，加速文件系统的读写；
- 可手动使用 `sync` 强制同步 dirty 文件到磁盘
- 正常关机时系统会自动调用 `sync`
- 非正常关机可能导致文件系统损坏

#### 6.1.6 挂载点的意义 (mount point)

将文件系统加入到目录树的动作成为挂载。挂载点一定是目录，该目录为进入文件系统的入口。

#### 6.1.7 其他 Linux 支持的文件系统与 VFS

- 传统文件系统
  - Ext2
  - Minix
  - MS-DOS
  - FAT
  - iso9660
- 日志式文件系统
  - Ext3/Ext4
  - ReiserFS
  - Windows' NTFS
  - IBM's JFS
  - SGI's XFS
  - ZFS
- 网络文件系统
  - NFS
  - SMBFS

```sh
# 查看当前 Linux 系统支持的文件系统:
ls -l /lib/modules/$(uname -r)/kernel/fs
# 查看系统当前载入内存中支持的文件系统
cat /proc/filesystem
# 查看系统已挂载的文件系统类型
df -T
```

- Linux VFS (Virtual Filesystem Switch): Linux 内核使用 VFS 管理文件系统，
  使实际的文件系统对用户透明。

### 6.2 文件系统的简单操作

#### 6.2.1 磁盘与目录的容量

- `df`: 列出文件系统整体磁盘使用情况，主要从 superblock 获取信息
  - `-a`: 列出所有文件系统，包括系统特有的 `/proc` 等
  - `-k`: 以 KBytes 显示容量
  - `-m`: 以 MBytes 显示容量
  - `-h`: 以人类易读的形式显示容量
  - `-H`: 以 10^3 进位取代 2^10 显示容量
  - `-T`: 列出分区的文件系统类型
  - `-i`: 显示 inode 数量而非容量
- `du`: 统计文件系统 (目录或文件) 的磁盘使用量，会访问文件系统获取相关的文件信息
  - `-a`: 列出所有的文件与目录容量，默认只统计目录的总容量
  - `-k`: 以 KBytes 显示容量
  - `-m`: 以 MBytes 显示容量
  - `-h`: 以人类易读的形式显示容量
  - `-s`: 只列出总量
  - `-S`: 只列出目录本身大小而不包括目录下其他文件的总量

#### 6.2.2 实体链接与符号链接: ln

- Hard Link (硬链接或实体链接)
  - 在某个目录的 block 新增一个文件记录，且该记录保存的是某个已使用的 inode 号
  - 新增 hark link 只有在目录 block 空间不够时才会增加 block 占用
  - 缺点
    - 不能跨文件系统
    - 不能链接目录
- Symbolic Link (符号链接或软链接)
  - 创建符号链接是创建一个独立的新文件，而这个新文件会使数据读取指向其他文件。
  - 符号链接会保存目标文件路径，因此其文件大小就是保存的路径名大小
  - 符号链接可以链接目录
- 为什么符号链接可以链接目录，而硬链接不行？

  假设可以成功执行如下命令:

  ```sh
  mkdir -p /tmp/a/b
  cd /tmp/a/b
  ln -d /tmp/a hl
  # 形成路径 /tmp/a/b/hl/b/hl/b/hl/b/...
  ```

  a 目录的文件列表记录了 b 的 inode, b 目录的文件列表记录了 hl 的 inode，
  hl 是硬链接，所以其 inode 与 a 目录相同，相当于 b 目录文件列表记录了 a 的 inode，造成
  inode 回环，导致文件系统难以处理文件删除等操作。

  更详细的原因请参考文章 [linux 为什么不能硬链接目录？](https://www.zhihu.com/question/50223526)

- 目录的 `.` 与 `..` 会增加相应目录的连接数

### 6.3 磁盘的分区、格式化、检验与挂载

新增一个磁盘的基本流程：

1. 分区
2. 格式化
3. 文件系统检查 (可选)
4. 把分区挂载到某个目录

#### 6.3.1 观察磁盘分区状态

- lsblk: 列出系统上所有磁盘
  - 选项
    - `-d`: 仅列出磁盘而不包括分区信息
    - `-f`: 显示文件系统名称
    - `-i`: 使用 ASCII 的线段输出，不使用复杂的文字编码
    - `-m`: 同时输出该设备在 /dev 下的权限
    - `-p`: 列出设备完整名
    - `-t`: 列出磁盘设备详细信息
  - 信息
    - NAME: 设备名
    - MAJ:MIN: 主要:次要设备号码
    - RM: 是否为可移除设备，如 U 盘、光盘等
    - SIZE: 容量
    - RO: 是否只读
    - TYPE: 磁盘、分区、或只读存储
    - MOUNTPOINT: 挂载点
- blkid: 列出设备 UUID 等信息
- parted: 列出磁盘分区表信息

#### 6.3.2 磁盘分区: gdisk/fdisk

- gdisk (支持 GPT)
- partprobe: 更新系统内核分区表信息
  - `-s`: 显示详细信息
  - `cat /proc/partitions`
- fdisk (MBR)
- parted: 两种分区格式都支持

#### 6.3.3 磁盘格式化（创建文件系统）

- XFS 文件系统 mkfs.xfs
  - `-d`
    - `agcount=数值`: 存储群组数量，可以加速格式化
  - `grep 'processor' /proc/cpuinfo`
- XFS 文件系统 for RAID 性能优化 (Optional)
- EXT4 文件系统 mkfs.ext4
- 其他文件系统 mkfs
  - `-t`: 指定具体的文件系统类型

#### 6.3.4 文件系统检验

- 检查修复文件系统时，必须先卸载文件系统
- 根目录出问题时，由于无法卸载，只能进入单人维护或救援模式修复
- `xfs_repair` 处理 XFS 文件系统
- `fsck.ext4` 处理 EXT4 文件系统

#### 6.3.5 文件系统挂载与卸载

- 单一文件系统**不应该**被重复挂载在不同的挂载点（目录）中
- 单一目录**不应该**重复挂载多个文件系统
- 作为挂载点的目录应该都是空目录
  - 挂载后原目录下的东西会被隐藏无法访问。直到文件系统卸载后才恢复。

##### 挂载操作

- `mount`
  - LABEL='' 目录名
  - UUID='' 目录名
  - 设备文件名 目录名
  - `-a`: 按照配置文件 `/etc/fstab` 的数据将所有未挂载磁盘都挂载
  - `-l`: 显示 Label
  - `-t`: 文件系统类型
  - `-n`: 默认情况下系统会将实际挂载情况实时写入 `/etc/mtab`，使用该选项可以避免写入
  - `-o`: 额外参数，比如账号、密码、读写权限
    - async, sync: 异步或同步写入磁盘
    - atime, noatime: 是否更新访问时间
    - ro, rw: 只读或读写
    - auto, noauto: 是否允许被 `-a` 自动挂载
    - dev, nodev: 是否允许创建 dev 文件
    - suid, nosuid: 是否允许创建含有 suid/sgid 的文件
    - exec, noexec: 是否允许有可执行文件
    - user, nouser: 是否允许任何用户执行 mount
    - defaults: rw, suid, dev, exec, auto, nouser, and async
    - remount: 重新挂载

  `-t` 一般不需要指定，系统通过 superblock 与以下信息测试挂载

  - `/etc/filesystems`: 系统指定的测试挂载文件系统类型优先顺序
  - `/proc/filesystems`: 系统已经载入的文件系统类型
  - `ls /lib/modules/$(uname -r)/kernel/fs`

- 重新挂载根目录与挂载不特定目录
  - `mount -o remount,rw,auto /`: 将根目录重新挂载为可读写
  - `mount --bind /var /data/var`: 将目录挂载到其他目录，用于不支持符号链接的程序
- umount (卸载设备文件) [-fn] 文件名或挂载点
  - `-f`: 强制卸载
  - `-l`: 立即卸载文件系统, 比 -f 更强
  - `-n`: 不更新 `/etc/mtab` 卸载
  
  进入挂载点目录内会导致设备忙，退出后才能卸载。

### 6.4 设置开机挂载

#### 6.4.1 开机挂载 /etc/fstab 及 /etc/mtab

系统挂载限制：

- 根目录 `/` 必须先于其他所有挂载点挂载
- 其他挂载点必须是已创建的目录，且遵守 FHS
- 所有挂载点只能挂载一次
- 所有分区只能挂载一次
- 卸载前必须将工作目录移到挂载点之外

`/etc/fstab` 文件内容的六个字段：

1. 设备文件名/UUID/LABEL name
2. 挂载点，即目录
3. 磁盘分区的文件系统格式
4. 文件系统参数，对应 `mount -o`
5. 能否被 dump 备份命令作用 (0 为关闭)
6. 是否在开机时以 fsck 检查扇区

修改后使用 `mount -a` 即可。

`/etc/fstab` 是开机时的配置文件，实际文件系统的挂载是记录在 `/etc/mtab` 与
`/proc/mounts` 中。

修复模式时需要先将根目录重新挂载为可写：

`mount -n -o remount,rw /`

## 7. 文件的压缩与打包

### 7.1 压缩文件的用途与技术

- 节省磁盘空间
- 减少流量传输

### 7.2 Linux 系统常见的压缩指令

常见扩展名（助记作用）

- `.Z`: compress
- `.zip`: zip
- `.gz`: gzip
- `.bz2`: bzip2
- `.xz`: xz
- `.tar`: tar
- `.tar.gz`: tar + gzip
- `.tar.bz2`: tar + bzip2
- `.tar.xz`: tar + xz

#### 7.2.1 gzip, zcat/zmore/zless/zgrep

- `-c`: 将压缩的数据输出到标准输出
- `-d`: 解压缩
- `-k`: 保留原文件，相当于 `-c >`
- `-t`: 检验文件是否有错误
- `-v`: 显示压缩过程信息
- `-数字`: 压缩等级

#### 7.2.2 bzip2, bzcat/bzmore/bzless/bzgrep

用法和 gzip 基本一致。

#### 7.2.3 xz, xzcat/xzmore/xzless/xzgrep

用法和 gzip 基本一致。

- `-l`: 显示压缩文件信息

##### 对比

`find /etc -maxdepth 1 -type f -exec du -sh {} \; | sort -h`

`find /bin -maxdepth 1 -type f -exec du -sh {} \; | sort -h`

`time gzip/bzip2/xz...`

### 7.3 打包指令: tar

#### 7.3.1 tar

- `-c`: 创建打包文件
- `-t`: 查看打包 tar 文件包含的文件名
- `-x`: 解包文件
- `-z`: 使用 gzip 压缩/解压 .tar.gz
- `-j`: 使用 bzip2 压缩/解压 .tar.bz2
- `-J`: 使用 xz 压缩/解压 .tar.xz
- `-v`: 显示处理过程
- `-f filename`: `f` 后必须紧跟被处理的文件名
- `-C directory`: 指定解压目录
- `-p`: 保留数据原本的权限与属性
- `-P`: 保留绝对路径，谨慎使用，因为解压时会按绝对路径放置
- `--exclude=FILE`: 排除某些文件
- `--newer TIMESTRING`: 只包含 mtime 与 ctime 比 TIMESTRING 更新的文件
- `--newer-mtime TIMESTRING`: 只包含 mtime 比 TIMESTRING 更新的文件

常用组合:

- 压缩: `tar -zcvf tarball.tar.gz directory`
- 查询: `tar -ztvf tarball.tar.gz`, `z` 可省略
- 解压: `tar -zxvf tarball.tar.gz -C directory`
- 只解压部分: `tar -zxvf tarball.tar.gz -C directory file_in_tarfile`

##### tarfile 与 tarball?

- tarfile: 只打包不压缩，即后缀为 .tar
- tarball: 打包加压缩

### 7.4 其他相关工具

- dd
  - `dd if="input_file" of="output_file" bs="block_size" count="number"`
  - `dd if=/dev/sr0 of=/tmp/system.iso`: 复制光驱内容
  - `dd if=/tmp/system.iso of=/dev/sda`: 写入到 U 盘中
  - dd 默认按扇区读写，因此可以不理会文件系统格式原样复制

## 8. 认识与学习 BASH

### 8.1 认识 BASH 这个 Shell

1. 硬件
2. 操作系统内核
3. 应用程序

Shell: 用户与操作系统交互的界面（接口）。

#### 8.1.1 系统的合法 shell 与 /etc/shells 功能

- sh: Bourne SHell
- bash: Bourne Again SHell

`cat /etc/shells`

#### 8.1.2 Bash shell 的功能

- 大部分 Linux 发行版的标准 shell
- 兼容 sh
- 命令历史 (.bash_history)
- 命令与文件补全
- 命令别名
- 工作控制：前后台运行
- 脚本化
- `*` (wildcard)
- ...

#### 8.1.3 查询指令是否为 Bash shell 的内置命令: type

bash 自带了很多指令，比如 cd, umask

- `type [-tpa] name`

### 8.2 Shell 的变量功能

#### 8.2.1 变量的取用与设置: echo, 变量设置规则, unset

- 显示变量值: `echo ${variable}`, `{}` 在部分情况下不能省略
- 变量设置规则
  - `variable=value`: 等号两边不能有空格
  - 变量名: 由字母、数字、下划线组成，其中数字不能作为开头
  - 变量内容有空白符时需要用引号括起来
    - 双引号: 引号内特殊字符保留其特性，可使用 `\` 转义
    - 单引号: 引号内的字符作为正常字符使用
  - 反引号 `` 或 $() 中可以包含其他命令
  - 变量需要被子程序使用时，需要用 `export` 导出为环境变量，子进程会继承父进程的环境变量
  - 全大写字母为系统默认变量，自定义变量一般使用小写字母
  - 取消变量使用 `unset`

#### 8.2.2 环境变量

- `env`: 列出当前 shell 下的所有环境变量

- 特殊变量
  - HOME
  - SHELL
  - HISTSIZE
  - MAIL
  - PATH
  - LANG
  - RANDOM
- `set`: 观察所有变量
  - `PS1`: 命令提示字符格式
  - `PS2`: 换行提示符
  - `$`: 本 shell 的 PID
  - `?`: 上一个命令的返回值
  - `OSTYPE, HOSTTYPE, MACHTYPE`: 主机硬件与核心登记

#### 8.2.3 从输入读取变量、数组与声明: read, array, declare

- `read [-pt] variable`: 从输入读取变量
  - `-p`: 接提示字符
  - `-t`: 等待秒数
- `declare [-aixr] variable`: 声明变量类型
  - `-a`: array
  - `-i`: integer
  - `-x`: 导出为环境变量
  - `-r`: 只读, 相当于常量
- 变量默认类型为字符串
- bash 的数字运算只支持 integer
- array:
  - `arr[index]=content`
  - `echo ${arr[index]}`

#### 8.2.4 与文件系统及进程的限制关系: ulimit

#### 8.2.5 变量内容的删除、取代与替换 (Optional)

- 变量内容的删除与取代

  | 变量设置方式               | 说明                                     |
  | -------------------------- | ---------------------------------------- |
  | ${变量#关键词}             | 若变量内容从头开始的数据符合『关键字』， |
  |                            | 则将符合的最短数据删除                   |
  | ${变量##关键词}            | 若变量内容从头开始的数据符合『关键字』， |
  |                            | 则将符合的最长数据删除                   |
  | ${变量%关键词}             | 若变量内容从尾向前的数据符合『关键字』， |
  |                            | 则将符合的最短数据删除                   |
  | ${变量%%关键词}            | 若变量内容从尾向前的数据符合『关键字』， |
  |                            | 则将符合的最长数据删除                   |
  | ${变量/旧字符串/新字符串}  | 若变量内容符合『旧字符串』，             |
  |                            | 则『第一个旧字符串会被新字符串取代』     |
  | ${变量//旧字符串/新字符串} | 若变量内容符合『旧字符串』，             |
  |                            | 则『全部的旧字符串会被新字符串取代』     |

  例:

    ```sh
    path=$PATH; echo $path
    /usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/snap/bin
    ```

  删除 `local/bin` 及其前面的路径:

    ```sh
    echo ${path#/*/local/bin:}
    ```

- 变量的测试与内容替换

  | 变量设置方式   | s 没有设置         | s 为空字符串       | s 为非空字符串 |
  | -------------- | ------------------ | ------------------ | -------------- |
  | var=${s-expr}  | var=expr           | var=               | var=$s         |
  | var=${s:-expr} | var=expr           | var=expr           | var=$s         |
  | var=${s+expr}  | var=               | var=expr           | var=expr       |
  | var=${s:+expr} | var=               | var=               | var=expr       |
  | var=${s=expr}  | s=expr var=expr    | s 不变 var=        | s 不变 var=$s  |
  | var=${s:=expr} | s=expr var=expr    | s=expr var=expr    | s 不变 var=$s  |
  | var=${s?expr}  | expr 输出至 stderr | var=               | var=$s         |
  | var=${s:?expr} | expr 输出至 stderr | expr 输出至 stderr | var=$s         |

### 8.3 命令别名与历史命令

#### 8.3.1 命令别名设置: alias, unalias

- `alias [newname="command"]`
  - `alias cls="clear"`
- `unalias name`
  - `unalias cls`
- ⚠️ alias 相当于创建一个新的 "命令"，而不是一个变量

#### 8.3.2 历史命令: history

- `HISTSIZE`: shell history 的长度上限
- `HISTFILESIZE`: `~/.bash_history` 的长度上限
- 常用参数
  - `n`: 列出最近输入的 n 个命令
  - `-c`: 清除当前 shell 的历史
  - `-a [histfiles]`: 将新输入的命令记录输入到 histfiles 里，没指定 histfiles
    时则则追加到 `~/.bash_history`
  - `-r`: 将 histfiles 内容读到当前 shell 的 history 中
  - `-w [histfiles]`: 将当前 history 写入到 histfiles，exit 时自动执行
- `!number`: 执行第 number 个命令
- `!command`: 执行匹配到的以一个命令记录
- `!!`: 执行最近一条命令
- `[Ctrl]+r`

### 8.4 Bash Shell 的操作环境

#### 8.4.1 路径与命令搜索顺序

优先级：

1. 绝对路径或相对路径
2. alias
3. bash 内置命令
4. $PATH

#### 8.4.2 bash 的登录欢迎信息: /etc/issue, /etc/motd

- `/etc/issue`: 登录前
  - `\d`: 本地日期
  - `\l`: 终端机接口编号 (tty, TeleTYpewriter)
  - `\m`: 硬件等级
  - `\n`: 主机名
  - `\O`: 域名
  - `\r`: 操作系统版本，相当于 `uname -r`
  - `\t`: 本地时间
  - `\S`: 操作系统名称
  - `\v`: 操作系统版本
- `/etc/motd`: 登录后

#### 8.4.3 bash 的环境配置文件

- login 与 non-login shell
  - login shell: 通过完整登录流程获得的 shell
    - `/etc/profile`
      - 设置环境变量
        - PATH
        - MAIL
        - USER
        - HOSTNAME
        - HISTSIZE
      - umask
      - 调用 /etc/profile.d/*.sh 设置颜色、语言、别名等
    - 按顺序尝试读取 `~/.bash_profile`, `~/.bash_login`, `~/.profile` 其中一个
  - `source` (`.`): 读入环境配置文件
  - non-login shell: 登录系统后，通过图形界面或命令行进入 bash
    - `/etc/bash.bashrc` (不同发行版可能不一样)
    - `~/.bashrc`
  - `~/.bash_logout`

#### 8.4.4 终端机的环境设置: stty, set

- `stty`: 设置终端属性
- `set`: 设置 bash 属性，其中部分设置和 tty 有关
  - `-OPTION`
  - `+OPTION`

| 按键     | 操作           |
| -------- | -------------- |
| Ctrl + C | 终止当前的进程 |
| Ctrl + D | 输入结束符 EOF |
| Ctrl + M | 输入 Enter     |
| Ctrl + S | 暂停屏幕输出   |
| Ctrl + Q | 恢复屏幕输出   |
| Ctrl + U | 删除当前输入   |
| Ctrl + Z | 暂停当前进程   |

#### 8.4.5 bash 中的特殊符号

匹配文件名的特殊符号:

| 符号  | 意义                                               |
| ----- | -------------------------------------------------- |
| `*`   | 匹配 0 到无穷多个任意字符                          |
| `?`   | 匹配一个任意字符                                   |
| `[]`  | 匹配一个括号内的字符，`[abcd]`, `[0-9]`            |
| `[^]` | `^` 代表反向匹配，`[^abc]` 匹配一个 abc 之外的字符 |

其他特殊符号:

| 符号       | 意义                         |
| ---------- | ---------------------------- |
| `#`        | 注释符号                     |
| `\`        | 命令断行；在字符串里可以转义 |
| `|`        | 管道符                       |
| `;`        | 多命令分隔符                 |
| `~`        | 用户的家目录                 |
| `$`        | 变量取值符                   |
| `&`        | 将命令变成后台工作           |
| `!`        | 逻辑非                       |
| `/`        | 目录符号                     |
| `>`, `>>`  | 输出重定向，分别是覆盖与累加 |
| `<`, `<<`  | 输入重定向                   |
| `''`       | 单引号，不具有变量置换的功能 |
| `""`       | 具有变量置换的功能           |
| `` 与 $( ) | 执行子命令                   |
| `()`       | 中间为子 shell 的起始与结束  |
| `{}`       | 中间为命令区块的组合         |

### 8.5 数据流重定向

#### 8.5.1 什么是数据流重定向

1. 标准输入 (stdin): 代号为 0，使用 `<` 或 `<<`
2. 标准输出 (stdout): 代号为 1，使用 `1>` 或 `1>>`, `1` 可省略
3. 标准错误输出 (stderr): 代号为 2，使用 `2>` 或 `2>>`

典型用法:

- 保存错误输出到文件: `command 2>err.log`
- 丢弃所有输出: `1>/dev/null 2>&1`
- 使用标准输入替代键盘输入: `cat > test.txt < somefile`
- 使用 `<<` 代替键盘 `Ctrl+d`:

  ```sh
  cat << EOF > somefile
  {
    "a": {
      "b": 1
    }
  }
  EOF
  ```

#### 8.5.2 命令执行的判断依据: ;, &&, ||

- 退出码: 0 为成功，其他 1-255 为失败
- `cmd1; cmd2`: 无论 cmd1 执行成功与否，cmd2 都会执行
- `$?`: 上一个命令的退出码
- 与 `cmd1 && cmd2`: cmd1 成功才执行 cmd2
- 或 `cmd1 || cmd2`: cmd1 失败才执行 cmd2

例:

- `ls aaa && echo "exist" || echo "not exist"`
- `ls aaa || echo "not exist" && echo "exist"`

### 8.6 管道命令 (pipe)

- `cmd1 | cmd2`: cmd1 的 stdout 作为 cmd2 的 stdin
- stderr 会被忽略
- cmd 必须支持 stdin，否则会被忽略。`ls`, `cp`, `mv` 等都不是管道命令

#### 8.6.1 截取命令: cut, grep

- cut: 列处理
  - `-d'分隔符'`: 指定分隔符
  - `-f COL`: 取出分隔后的第 COL 列
  - `-c START[-END]`: 以字符为单位取出第 START-END 列
- grep: 行处理
  - `-c`: 匹配行数计数
  - `-i`: 忽略大小写
  - `-n`: 输出行号
  - `-v`: 反向搜索，即匹配没有关键字的行

#### 8.6.2 排序命令: sort, wc, uniq

- sort
  - `-f`: 忽略大小写
  - `-b`: 忽略前面的空白符
  - `-M`: 按月份名字排序，如 JAN, FEB
  - `-n`: 按纯数字排序
  - `-r`: 反向排序
  - `-u`: unique, 相同数据只出现一次
  - `-t`: 分隔符，默认为 [tab]
  - `-k`: 以某一列排序

  例: `cat /etc/passwd | sort -t ':' -k 3 -n`

- uniq
  - `-i`: 忽略大小写
  - `-c`: 计数

  例: `last | cut -d' ' -f 1 | uniq -c`

- wc
  - `-l`: 行
  - `-w`: 单词
  - `-m`: 字符

#### 8.6.3 双重重定向: tee

- `-a`: filename

#### 8.6.4 字符转换命令: tr, col, join, paste, expand

#### 8.6.5 文件分割命令: split

#### 8.6.6 参数替换: xargs

对于不支持 stdin 的命令 xargs 特别有用。

- `xargs [-0epn] command`
  - `-0`: 如果 stdin 有特殊字符，则将其还原成一般字符
  - `-e`: EOF, xargs 收到 EOF 时会停止工作
  - `-p`: 执行 command 时询问用户
  - `-n`: 每个 command 使用多少个参数

例: `cut -d ':' -f 1 /etc/passwd | head -n 3 | xargs -n 1 id`

#### 8.6.7 关于减号 - 的用途

在使用管道命令时常常会使用 stdout 作为下一个命令的 stdin，某些命令的输出参数需要用文件名，
此时可以用减号代替:

```sh
# 将 tarball 通过 - 输出到 stdout, 再通过管道后的 - 读取 stdin
tar -cvf - /home | tar -xvf - -C /tmp/homeback
```
