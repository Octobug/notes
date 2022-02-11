# 第四章 首次登陆与在线求助 man page

> <https://linux.vbird.org/linux_basic/centos7/0160startlinux.php>

## 目录

- [第四章 首次登陆与在线求助 man page](#第四章-首次登陆与在线求助-man-page)
  - [目录](#目录)
  - [4.1 首次登录系统](#41-首次登录系统)
    - [4.1.1 首次登录 CentOS 7.x 图形接口](#411-首次登录-centos-7x-图形接口)
    - [4.1.2 GNOME 的操作与登出](#412-gnome-的操作与登出)
    - [4.1.3 X window 与文字模式的切换](#413-x-window-与文字模式的切换)
    - [4.1.4 在终端界面登陆 linux](#414-在终端界面登陆-linux)
  - [4.2 文本模式下指令的下达](#42-文本模式下指令的下达)
    - [4.2.1 开始下达指令](#421-开始下达指令)
      - [语系的支持](#语系的支持)
    - [4.2.2 基础指令的操作](#422-基础指令的操作)
    - [4.2.3 重要的几个热键 `[Tab]`, `[ctrl]-c`, `[ctrl]-d`](#423-重要的几个热键-tab-ctrl-c-ctrl-d)
    - [4.2.4 错误信息的查看](#424-错误信息的查看)
  - [4.3 Linux 系统的线上求助 man page 与 info page](#43-linux-系统的线上求助-man-page-与-info-page)
    - [4.3.1 指令的 --help 求助说明](#431-指令的---help-求助说明)
    - [4.3.2 man page](#432-man-page)
    - [4.3.3 info page](#433-info-page)
    - [4.3.4 其他有用的文件 (documents)](#434-其他有用的文件-documents)
  - [4.4 超简单文书编辑器：nano](#44-超简单文书编辑器nano)
  - [4.5 正确的关机方法](#45-正确的关机方法)
    - [数据同步写入磁盘: `sync`](#数据同步写入磁盘-sync)
    - [惯用的关机指令: `shutdown`](#惯用的关机指令-shutdown)
    - [重新开机/关机: `reboot`, `halt`, `poweroff`](#重新开机关机-reboot-halt-poweroff)
    - [实际使用管理工具 `systemctl` 关机](#实际使用管理工具-systemctl-关机)
  - [4.6 重点回顾](#46-重点回顾)
  - [4.7 本章习题](#47-本章习题)
  - [4.8 参考资料与延伸阅读](#48-参考资料与延伸阅读)
  - [4.9 针对本文的建议](#49-针对本文的建议)

## 4.1 首次登录系统

### 4.1.1 首次登录 CentOS 7.x 图形接口

### 4.1.2 GNOME 的操作与登出

- 重启 X Window
  - 登出再重新登录
  - `Ctrl + Alt + Backspace`: 需要自己设置 "砍除 X 服务器" 快捷键

### 4.1.3 X window 与文字模式的切换

文字模式也称为终端机接口，terminal 或 console。Linux 默认提供 6 个 Terminal，
快捷键为: `Ctrl + Alt + F1~F6`，对应 tty1~tty6。

在文本环境中启用 X window: `startx`

### 4.1.4 在终端界面登陆 linux

登录前的屏幕提示信息: `/etc/issue`

## 4.2 文本模式下指令的下达

### 4.2.1 开始下达指令

```sh
command [-options] parameter1 parameter2 ... \
  ...
```

#### 语系的支持

```sh
locale
```

### 4.2.2 基础指令的操作

1. 显示日期时间: `date`:

    时区定义: `/usr/share/zoneinfo`
    `TZ=Asia/Shanghai date "+%Y/%m/%d %H:%M:%S"`

2. 显示日历: `cal`: `cal [month] [year]`
3. 计算器: `bc`:
    - 小数位数: `scale=3`

### 4.2.3 重要的几个热键 `[Tab]`, `[ctrl]-c`, `[ctrl]-d`

- [Tab] 按键: 命令与文件名补全
  - 第一个位置为"命令补全"
  - 第二个位置及以后为"文件补全"
  - 如安装软件的 `bash-completion`，则会有子命令/选项/参数补全
- [Ctrl]-c 按键: 终止当前程序
- [Ctrl]-d 按键: `EOF`, 相当于输入 `exit`
- [Shift]-{[PageUp]|[PageDown]} 按键: 上下翻页. macOS 中按键为
  [Shift]+[fn]+{[Up]|[Down]}

### 4.2.4 错误信息的查看

## 4.3 Linux 系统的线上求助 man page 与 info page

### 4.3.1 指令的 --help 求助说明

### 4.3.2 man page

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

### 4.3.3 info page

info 是 Linux 特有的，与 man 的用途差不多，主要区别是 info page 将文件数据拆成一个个段落，
并提供链接跳转。

- `info info`: `h` 键显示操作帮助
  - File: 当前 info page 的数据来源
  - Node: 当前 info page 所属内容节点
  - Next: 当前 info page 的下一个节点，按键 "N"
  - Up: 回到上一层的节点总览，按键 "U"
  - Prev: 回到前一个节点，按键 "P"
- 存储位置: `/usr/share/info`

### 4.3.4 其他有用的文件 (documents)

- `/usr/share/doc`

## 4.4 超简单文书编辑器：nano

- 按键说明
  - `^KEY`: `^` 代表 [Ctrl]
  - `M-KEY`: `M` 代表 [Alt]

## 4.5 正确的关机方法

Linux 是多用户环境，不可随便关机。

- 观察系统使用状态
  - `who`: 查看在线用户
  - `netstat -a`: 网络连接状态
  - `ps -aux`: 进程列表
- 通知在线用户关机: `shutdown`
- 数据同步写入磁盘: `sync`
- 关机: `shutdown`
- 重启: `reboot`, `halt`, `poweroff`

### 数据同步写入磁盘: `sync`

为了加快数据读写速度，内存中的数据改动并不会立即被写回磁盘。`sync`
正是用于显式触发数据写入磁盘的。

`shutdown`/`reboot`/`halt` 执行时会自动调用 `sync`。

每个账号调用 `sync` 只会更新自身的数据，root 账号会同步全局的数据。

### 惯用的关机指令: `shutdown`

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

### 重新开机/关机: `reboot`, `halt`, `poweroff`

实际上以上几个关机/重启命令都是调用 `systemctl` 实现的。

```sh
# 停机
halt
# 关机
poweroff
```

### 实际使用管理工具 `systemctl` 关机

目前的 `init` 命令只是 Linux 为了兼容而提供，使用 `init 0` 也可以关机，但跟所谓的
“执行等级”已经无关。

```sh
systemctl [COMMAND]

# halt: 停机，屏幕可能会保留一些信息，这与电源管理模式有关
# poweroff: 彻底的关机，断开电源
# reboot: 重启
# suspend: 休眠
```

## 4.6 重点回顾

## 4.7 本章习题

1. `/etc/issue` 中的转移占位符, `\n`/`\l` 等，通过 `man agetty` 的 ISSUE ESCAPES
   部分了解详细信息。
2. Physical console / Virtual console / Terminal 的区别
   1. Physical console: 屏幕、键鼠等可以操控系统的实体界面
   2. Virtual console: 搭配实体控制台可以操控系统的环境
   3. Terminal: 提供 shell 环境的交互界面

## 4.8 参考资料与延伸阅读

## 4.9 针对本文的建议

<http://phorum.vbird.org/viewtopic.php?t=23877>
