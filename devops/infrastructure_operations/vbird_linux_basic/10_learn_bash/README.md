# 第十章 认识与学习 BASH

> <http://cn.linux.vbird.org/linux_basic/0320bash.php>

## 目录

- [第十章 认识与学习 BASH](#第十章-认识与学习-bash)
  - [目录](#目录)
  - [10.1 认识 BASH 这个 Shell](#101-认识-bash-这个-shell)
    - [10.1.1 硬件、核心与 Shell](#1011-硬件核心与-shell)
    - [10.1.2 为何要学命令行的 shell？](#1012-为何要学命令行的-shell)
    - [10.1.3 系统的合法 shell 与 /etc/shells 功能](#1013-系统的合法-shell-与-etcshells-功能)
    - [10.1.4 Bash shell 的功能](#1014-bash-shell-的功能)
    - [10.1.5 查询指令是否为 Bash shell 的内置命令: type](#1015-查询指令是否为-bash-shell-的内置命令-type)
    - [10.1.6 指令的下达与快速编辑按钮](#1016-指令的下达与快速编辑按钮)
  - [10.2 Shell 的变量功能](#102-shell-的变量功能)
    - [10.2.1 什么是变量？](#1021-什么是变量)
    - [10.2.2 变量的取用与设置: echo, 变量设置规则, unset](#1022-变量的取用与设置-echo-变量设置规则-unset)
    - [10.2.3 环境变量的功能](#1023-环境变量的功能)
    - [10.2.4 影响显示结果的语系变量 (locale)](#1024-影响显示结果的语系变量-locale)
    - [10.2.5 变量的有效范围](#1025-变量的有效范围)
    - [10.2.6 从输入读取变量、数组与声明: read, array, declare](#1026-从输入读取变量数组与声明-read-array-declare)
    - [10.2.7 与文件系统及程序的限制关系: ulimit](#1027-与文件系统及程序的限制关系-ulimit)
    - [10.2.8 变量内容的删除、取代与替换 (Optional)](#1028-变量内容的删除取代与替换-optional)
  - [10.3 命令别名与历史命令](#103-命令别名与历史命令)

## 10.1 认识 BASH 这个 Shell

### 10.1.1 硬件、核心与 Shell

1. 硬件
2. 操作系统内核
3. 应用程序

Shell: 用户与操作系统交互的界面（接口）。

### 10.1.2 为何要学命令行的 shell？

### 10.1.3 系统的合法 shell 与 /etc/shells 功能

- sh: Bourne SHell
- bash: Bourne Again SHell

`cat /etc/shells`

### 10.1.4 Bash shell 的功能

- 大部分 Linux 发行版的标准 shell
- 兼容 sh
- 命令历史 (.bash_history)
- 命令与文件补全
- 命令别名
- 工作控制：前后台运行
- 脚本化
- `*` (wildcard)

### 10.1.5 查询指令是否为 Bash shell 的内置命令: type

bash 自带了很多指令，比如 cd, umask

- `type [-tpa] name`

### 10.1.6 指令的下达与快速编辑按钮

- `\[enter]`: 命令分行，中间不能有其他符号

## 10.2 Shell 的变量功能

### 10.2.1 什么是变量？

- 系统环境变量通常以全大写字符命名

### 10.2.2 变量的取用与设置: echo, 变量设置规则, unset

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

### 10.2.3 环境变量的功能

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
  - `$`: 本 shell 的 PID
  - `?`: 上一个命令的返回值
  - `OSTYPE, HOSTTYPE, MACHTYPE`: 主机硬件与核心登记

### 10.2.4 影响显示结果的语系变量 (locale)

### 10.2.5 变量的有效范围

### 10.2.6 从输入读取变量、数组与声明: read, array, declare

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

### 10.2.7 与文件系统及程序的限制关系: ulimit

### 10.2.8 变量内容的删除、取代与替换 (Optional)

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

## 10.3 命令别名与历史命令
