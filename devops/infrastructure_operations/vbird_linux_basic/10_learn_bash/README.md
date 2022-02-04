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
    - [10.1.6 命令下达与编辑快捷键](#1016-命令下达与编辑快捷键)
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
    - [10.3.1 命令别名设置: alias, unalias](#1031-命令别名设置-alias-unalias)
    - [10.3.2 历史命令: history](#1032-历史命令-history)
  - [10.4 Bash Shell 的操作环境](#104-bash-shell-的操作环境)
    - [10.4.1 路径与命令搜索顺序](#1041-路径与命令搜索顺序)
    - [10.4.2 bash 的登录欢迎信息: /etc/issue, /etc/motd](#1042-bash-的登录欢迎信息-etcissue-etcmotd)
    - [10.4.3 bash 的环境配置文件](#1043-bash-的环境配置文件)
    - [10.4.4 终端机的环境设置: stty, set](#1044-终端机的环境设置-stty-set)
    - [10.4.5 万用字符与特殊符号](#1045-万用字符与特殊符号)
  - [10.5 数据流重定向](#105-数据流重定向)
    - [10.5.1 什么是数据流重定向](#1051-什么是数据流重定向)
    - [10.5.2 命令执行的判断依据: ;, &&, ||](#1052-命令执行的判断依据---)
  - [10.6 管道命令 (pipe)](#106-管道命令-pipe)
    - [10.6.1 截取命令: cut, grep](#1061-截取命令-cut-grep)
    - [10.6.2 排序命令: sort, wc, uniq](#1062-排序命令-sort-wc-uniq)
    - [10.6.3 双重重定向: tee](#1063-双重重定向-tee)
    - [10.6.4 字符转换命令: tr, col, join, paste, expand](#1064-字符转换命令-tr-col-join-paste-expand)
    - [10.6.5 文件分割命令: split](#1065-文件分割命令-split)
    - [10.6.6 参数替换: xargs](#1066-参数替换-xargs)
    - [10.6.7 关于减号 - 的用途](#1067-关于减号---的用途)
  - [10.7 重点回顾](#107-重点回顾)
  - [10.8 本章习题](#108-本章习题)
  - [10.9 参考资料与延伸阅读](#109-参考资料与延伸阅读)

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

系统可用 shell: `cat /etc/shells`

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

- `help command`
- `type [-tpa] name`

### 10.1.6 命令下达与编辑快捷键

| 按键               | 功能                               |
| ------------------ | ---------------------------------- |
| \[enter]           | 转义`[enter]`符，将命令分行        |
| [ctrl]+u, [ctrl]+k | 删除光标前的部分; 删除光标后的部分 |
| [ctrl]+a, [ctrl]+e | 将光标移动到行首; 将光标移动到行尾 |

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
  - 反引号 \`\` 或 `$()` 中可以包含其他命令:
    `echo "/lib/modules/$(uname -r)/kernel"`
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
  - `PS2`: 换行提示符
  - `$`: 本 shell 的 PID
  - `?`: 上一个命令的返回值
  - `OSTYPE, HOSTTYPE, MACHTYPE`: 主机硬件与核心登记
- `export`: 将自定义变量 (`set`) 转换为环境变量 (`env`), 供子进程访问。

### 10.2.4 影响显示结果的语系变量 (locale)

- `-a`: 查看所有支持的语言编码
- 编码设置: `locale`, `$LANG` 和 `$LC_ALL` 作为其他设置的默认设置
- `/usr/lib/locale`
- `/etc/locale.conf`

### 10.2.5 变量的有效范围

- 环境变量等同于全局变量
- 自定义变量等同于局域变量

### 10.2.6 从输入读取变量、数组与声明: read, array, declare

- `read [-pt] variable`: 从输入读取变量
  - `-p`: 接提示字符
  - `-t`: 等待秒数
- `declare [-+aixr] variable`/`typeset`: 声明变量类型
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

- `-a`: 查看所有限制

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

### 10.3.1 命令别名设置: alias, unalias

- `alias [newname="command"]`
  - 例: `alias cls="clear"`
- `unalias name`
  - 例: `unalias cls`
- ⚠️ alias 相当于创建一个新的 "命令"，而不是一个变量

### 10.3.2 历史命令: history

- history [n]: 列出最近输入的 n 个命令
  - `-c`: 清除当前 shell 的历史
  - `-a [histfiles]`: 将新输入的命令记录输入到 histfiles 里，没指定 histfiles
    时则则追加到 `~/.bash_history`
  - `-r`: 将 histfiles 内容读到当前 shell 的 history 中
  - `-w [histfiles]`: 将当前 history 写入到 histfiles，exit 时自动执行
- `HISTSIZE`: shell history 的长度上限
- `HISTFILESIZE`: `~/.bash_history` 的长度上限
- `!number`: 执行第 number 个命令
- `!command`: 执行匹配到的第一个命令记录
- `!!`: 执行最近一条命令
- `[Ctrl]+r`: 搜索 bash history

## 10.4 Bash Shell 的操作环境

### 10.4.1 路径与命令搜索顺序

优先级：

1. 绝对路径/相对路径
2. alias
3. bash 内置命令
4. $PATH

### 10.4.2 bash 的登录欢迎信息: /etc/issue, /etc/motd

- `man issue`, `man agetty`
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

### 10.4.3 bash 的环境配置文件

>>>>> progress

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

### 10.4.4 终端机的环境设置: stty, set

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

### 10.4.5 万用字符与特殊符号

| 符号  | 意义                                               |
| ----- | -------------------------------------------------- |
| `*`   | 匹配 0 到无穷多个任意字符                          |
| `?`   | 匹配一个任意字符                                   |
| `[]`  | 匹配一个括号内的字符，`[abcd]`, `[0-9]`            |
| `[^]` | `^` 代表反向匹配，`[^abc]` 匹配一个 abc 之外的字符 |

bash 中的其他特殊符号

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

## 10.5 数据流重定向

### 10.5.1 什么是数据流重定向

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

### 10.5.2 命令执行的判断依据: ;, &&, ||

- 退出码: 0 为成功，其他 1-255 为失败
- `cmd1; cmd2`: 无论 cmd1 执行成功与否，cmd2 都会执行
- `$?`: 上一个命令的退出码
- 与 `cmd1 && cmd2`: cmd1 成功才执行 cmd2
- 或 `cmd1 || cmd2`: cmd1 失败才执行 cmd2

例:

- `ls aaa && echo "exist" || echo "not exist"`
- `ls aaa || echo "not exist" && echo "exist"`

## 10.6 管道命令 (pipe)

- `cmd1 | cmd2`: cmd1 的 stdout 作为 cmd2 的 stdin
- stderr 会被忽略
- cmd 必须支持 stdin，否则会被忽略。`ls`, `cp`, `mv` 等都不是管道命令

### 10.6.1 截取命令: cut, grep

- cut: 列处理
  - `-d'分隔符'`: 指定分隔符
  - `-f COL`: 取出分隔后的第 COL 列
  - `-c START[-END]`: 以字符为单位取出第 START-END 列
- grep: 行处理
  - `-c`: 匹配行数计数
  - `-i`: 忽略大小写
  - `-n`: 输出行号
  - `-v`: 反向搜索，即匹配没有关键字的行

### 10.6.2 排序命令: sort, wc, uniq

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

### 10.6.3 双重重定向: tee

- `-a`: filename

### 10.6.4 字符转换命令: tr, col, join, paste, expand

### 10.6.5 文件分割命令: split

### 10.6.6 参数替换: xargs

对于不支持 stdin 的命令 xargs 特别有用。

- `xargs [-0epn] command`
  - `-0`: 如果 stdin 有特殊字符，则将其还原成一般字符
  - `-e`: EOF, xargs 收到 EOF 时会停止工作
  - `-p`: 执行 command 时询问用户
  - `-n`: 每个 command 使用多少个参数

例: `cut -d ':' -f 1 /etc/passwd | head -n 3 | xargs -n 1 id`

### 10.6.7 关于减号 - 的用途

在使用管道命令时常常会使用 stdout 作为下一个命令的 stdin，某些命令的输出参数需要用文件名，
此时可以用减号代替:

```sh
# 将 tarball 通过 - 输出到 stdout, 再通过管道后的 - 读取 stdin
tar -cvf - /home | tar -xvf - -C /tmp/homeback
```

## 10.7 重点回顾

## 10.8 本章习题

## 10.9 参考资料与延伸阅读
