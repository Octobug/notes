# 第十二章 学习 shell scripts

> <http://cn.linux.vbird.org/linux_basic/0340bashshell-scripts.php>

## 目录

- [第十二章 学习 shell scripts](#第十二章-学习-shell-scripts)
  - [目录](#目录)
  - [12.1 什么是 Shell scripts](#121-什么是-shell-scripts)
    - [12.1.1 为什么学习 Shell scripts](#1211-为什么学习-shell-scripts)
    - [12.1.2 第一个 script 的编写与执行](#1212-第一个-script-的编写与执行)
    - [12.1.3 编写 Shell script 的良好习惯](#1213-编写-shell-script-的良好习惯)
  - [12.2 简单的 Shell script 练习](#122-简单的-shell-script-练习)
    - [12.2.1 简单范例](#1221-简单范例)
    - [12.2.2 script 的执行方式差异 (source script, sh script, ./script)](#1222-script-的执行方式差异-source-script-sh-script-script)
  - [12.3 善用判断式](#123-善用判断式)
    - [12.3.1 利用 test 命令的测试功能](#1231-利用-test-命令的测试功能)
    - [12.3.2 利用判断符号 `[]`](#1232-利用判断符号-)
    - [12.3.x 利用判断符号 `[[]]`](#123x-利用判断符号-)
    - [12.3.3 Shell script 的默认变量 ($0, $1...)](#1233-shell-script-的默认变量-0-1)
  - [12.4 条件判断](#124-条件判断)
    - [12.4.1 利用 if...then](#1241-利用-ifthen)

## 12.1 什么是 Shell scripts

### 12.1.1 为什么学习 Shell scripts

- 自动化管理
- 追踪与管理系统
- 简单的入侵检测
- 连续命令一键化
- 简单的数据处理
- 跨平台（Unix-like）支持
- 学习成本较低

### 12.1.2 第一个 script 的编写与执行

```sh
#!/bin/bash
# Program:
#       This program shows "Hello World!" in your screen.
# History:
# 2005/08/23 VBird First release
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH
echo -e "Hello World! \a \n"
exit 0
```

1. `#!/bin/bash`: 声明脚本默认使用 `/bin/bash` 执行，执行时会加载 bash 的配置
   （non-login shell 的 ~/.bashrc）；
2. `#`: 注释；
3. `PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin`:
    自定义 PATH 变量；`export PATH`: 导出为环境变量，供子进程使用；
4. `echo -e "Hello World! \a \n"`: 输出字符串
5. `exit 0`: 退出码

### 12.1.3 编写 Shell script 的良好习惯

每个 script 文件的开始处记录下列信息：

- 功能
- 版本信息
- 作者与联系方式
- 版权声明
- 历史记录
- 比较特别的命令使用“绝对路径”
- 预先声明与设置需要的环境变量

## 12.2 简单的 Shell script 练习

### 12.2.1 简单范例

1. 交互式脚本：变量内容用使用者决定

    ```sh
    #!/bin/bash
    # Program:
    #   User inputs his first name and last name.  Program shows his full name.
    # History:
    # 2015/07/16 VBird First release
    PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
    export PATH

    read -p "Please input your first name: " firstname  # 提示使用者输入
    read -p "Please input your last name:  " lastname   # 提示使用者输入
    echo -e "\nYour full name is: $firstname $lastname" # 结果由萤幕输出
    ```

2. 随日期变化：利用 date 进行文件的创建

    ```sh
    #!/bin/bash
    # Program:
    #   Program creates three files, which named by user's input 
    #     and date command.
    # History:
    # 2015/07/16 VBird First release
    PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
    export PATH

    # 1. 让使用者输入文件名称，并取得 fileuser 这个变量；
    echo -e "I will use 'touch' command to create 3 files." # 纯粹显示资讯
    read -p "Please input your filename: " fileuser         # 提示使用者输入

    # 2. 为了避免使用者随意按 Enter ，利用变量功能分析档名是否有配置？
    filename=${fileuser:-"filename"}           # 开始判断有否配置档名

    # 3. 开始利用 date 命令来取得所需要的档名了；
    date1=$(date --date='2 days ago' +%Y%m%d)  # 前两天的日期
    date2=$(date --date='1 days ago' +%Y%m%d)  # 前一天的日期
    date3=$(date +%Y%m%d)                      # 今天的日期
    file1=${filename}${date1}                  # 底下三行在配置档名
    file2=${filename}${date2}
    file3=${filename}${date3}

    # 4. 将档名创建吧！
    touch "$file1"                             # 底下三行在创建文件
    touch "$file2"
    touch "$file3"
    ```

3. 数值运算：简单的加减乘除

    ```sh
    #!/bin/bash
    # Program:
    #   User inputs 2 integer numbers; program will cross these two numbers.
    # History:
    # 2015/07/16 VBird First release
    PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
    export PATH
    echo -e "You SHOULD input 2 numbers, I will cross them! \n"
    read -p "first number:  " firstnu
    read -p "second number: " secnu
    total=$(($firstnu*$secnu))
    echo -e "\nThe result of $firstnu x $secnu is ==> $total"
    ```

4. 数值运算：通过 `bc` 计算 pi

    ```sh
    #!/bin/bash
    # Program:
    #   User input a scale number to calculate pi number.
    # History:
    # 2015/07/16 VBird First release
    PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
    export PATH
    echo -e "This program will calculate pi value.\n"
    echo -e "You should input a float number to calculate pi value.\n"
    read -p "The scale number (10~10000) ?" checking
    num=${checking:-"10"}                         # 判断是否输入数值
    echo -e "Starting calculate pi value. Be patient."
    time echo "scale=${num}; 4*a(1)" | bc -lq     # 4*a(1) 为 bc 计算 pi 的函数
    ```

### 12.2.2 script 的执行方式差异 (source script, sh script, ./script)

- `sh script` / `./script`: 使用一个新的 bash 环境来执行脚本，即是在子进程 bash
  中执行。
- `source script`: 在当前 bash 中执行

## 12.3 善用判断式

- true: 返回 0
- false: 返回 1

### 12.3.1 利用 test 命令的测试功能

1. 关于文件的“文件类型”判断，如 `test -e filename` 表示文件存在否

    | 参数 | 意义                                      |
    | ---- | ----------------------------------------- |
    | `-b` | 文件名是否存在且为块设备                  |
    | `-c` | 文件名是否存在且为字符设备                |
    | `-d` | 文件名是否存在且为目录 (directory) (常用) |
    | `-e` | 文件名是否存在 (常用)                     |
    | `-f` | 文件名是否存在且为文件 (file) (常用)      |
    | `-p` | 文件名是否存在且为一个 FIFO (pipe) 文件   |
    | `-L` | 文件名是否存在且为一个链接文件            |
    | `-S` | 文件名是否存在且为 Socket 文件            |

2. 关于文件的权限判断，如 `test -r filename` 表示是否可读 (但 root 权限常有例外)

    | 参数 | 意义                                   |
    | ---- | -------------------------------------- |
    | `-g` | 文件名是否存在且具有 "SGID" 属性       |
    | `-k` | 文件名是否存在且具有 "Sticky bit" 属性 |
    | `-r` | 文件名是否存在且具有 "可读" 权限       |
    | `-s` | 文件名是否存在且为非空白文件           |
    | `-u` | 文件名是否存在且具有 "SUID" 属性       |
    | `-w` | 文件名是否存在且具有 "可写" 权限       |
    | `-x` | 文件名是否存在且具有 "可执行"权限      |

3. 文件之间的比较，如：`test file1 -nt file2`

    | 参数  | 意义                                                             |
    | ----- | ---------------------------------------------------------------- |
    | `-ef` | file1 与 file2 是否为同一文件 (判断硬链接，即是否指向同一 inode) |
    | `-nt` | (newer than) file1 是否比 file2 新                               |
    | `-ot` | (older than) file1 是否比 file2 旧                               |

4. 整数之间的比较，例如 `test n1 -eq n2`

    | 参数  | 意义                                   |
    | ----- | -------------------------------------- |
    | `-eq` | 两数值相等 (equal)                     |
    | `-ge` | n1 大于等于 n2 (greater than or equal) |
    | `-gt` | n1 大于 n2 (greater than)              |
    | `-le` | n1 小于等于 n2 (less than or equal)    |
    | `-lt` | n1 小于 n2 (less than)                 |
    | `-ne` | 两数值不等 (not equal)                 |

5. 字符串之间的比较

    | 参数           | 意义                                                    |
    | -------------- | ------------------------------------------------------- |
    | `-n string`    | 字符串是否不为空？若 string 为空则返回 false，-n 可省略 |
    | `-z string`    | 字符串是否为空？若 string 为空则返回 true               |
    | `str1 == str2` | str1 是否等于 str2，若相等则返回 true，`=` 等同 `==`    |
    | `str1 != str2` | str1 是否不等于 str2 ，若相等则返回 false               |

6. 多重条件判定，例如：`test -r filename -a -x filename`

    | 参数 | 意义                                   |
    | ---- | -------------------------------------- |
    | `-a` | (and) 两个条件同时为 true 则返回 true  |
    | `-o` | (or) 两个条件有一个为 true 则返回 true |
    | `!`  | (not) 非，条件不成立时返回 true        |

例子：

- `test -e /filename && echo "exist" || echo "Not exist"`
  
    ```sh
    #!/bin/bash
    # Program:
    #   User input a filename, program will check the flowing:
    #   1.) exist? 2.) file/directory? 3.) file permissions 
    # History:
    # 2015/08/25  VBird  First release
    PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
    export PATH

    # 1. 让使用者输入文件名，并且判断使用者是否真的有输入字串？
    echo -e "Please input a filename, I will check the filename's type and \
    permission. \n\n"
    read -p "Input a filename : " filename
    test -z $filename && echo "You MUST input a filename." && exit 0
    # 2. 判断文件是否存在？若不存在则显示信息并结束脚本
    test ! -e $filename && echo "The filename '$filename' DO NOT exist" && \
      exit 0
    # 3. 开始判断文件类型与属性
    test -f $filename && filetype="regulare file"
    test -d $filename && filetype="directory"
    test -r $filename && perm="readable"
    test -w $filename && perm="$perm writable"
    test -x $filename && perm="$perm executable"
    # 4. 开始输出资讯！
    echo "The filename: $filename is a $filetype"
    echo "And the permissions are : $perm"
    ```

### 12.3.2 利用判断符号 `[]`

- 中括号 `[]` 中间两端必须有空格分隔；
- 中括号中的变量最好用双引号括起来

    ```sh
    [root@www ~]# name="VBird Tsai"
    [root@www ~]# [ $name == "VBird" ]
    bash: [: too many arguments
    ```

    `[ $name == "VBird" ]` 会被处理成 `[ VBird Tsai == "VBird" ]`，
    使条件判断变成三个字段。

- 中括号中的常量最好用单/双引号括起来

例子：

- `[ -z "${HOME}" ]; echo $?`

    ```sh
    #!/bin/bash
    # Program:
    #   This program shows the user's choice
    # History:
    # 2015/07/16  VBird First release
    PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
    export PATH

    read -p "Please input (Y/N): " yn
    [ "$yn" == "Y" -o "$yn" == "y" ] && echo "OK, continue" && exit 0
    [ "$yn" == "N" -o "$yn" == "n" ] && echo "Oh, interrupt!" && exit 0
    echo "I don't know what your choice is" && exit 0
    ```

### 12.3.x 利用判断符号 `[[]]`

⚠️ 不是 POSIX 标准，只有一部分 Shell (包括 bash) 支持

> 以下内容来自@伍华龙

- `[]` 与 `[[]]` 的区别
  - 两者都是 test 命令，用于检查表达式的真值性。若表达式为 true，则返回 0，否则返回 1。
  - `[[]]` 是 bash 对 `[]` 的改进，bash 同时支持两者，而 sh 只支持 `[]`。
    **bash 脚本中始终使用 `[[]]` 即可**。
  - 两者都能执行逻辑与、逻辑或运算，但写法不同，`[]` 用 `-a` 和 `-o`，`[[]]` 用 `&&` 和
    `||`。
  - `[]` 不支持正则匹配，`[[]]` 支持正则匹配。如 `[[ $name =~ abc* ]]` 或
    `[[ $name == [Tt]om ]]`。其中 `=~` 为扩展正则表达式。
  - 在没有加引号并且变量含有空格时，`[]` 会展开为多个字段，`[[]]` 则不会展开。
- 例子：

    ```sh
    #!/bin/bash
    # Program:
    #   This program shows the user's choice
    # History:
    # 2022/01/16  Octobug First release
    PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
    export PATH

    read -p "Please input (Y/N): " yn
    [[ "$yn" == "Y" || "$yn" == "y" ]] && echo "OK, continue" && exit 0
    [[ "$yn" == "N" || "$yn" == "n" ]] && echo "Oh, interrupt!" && exit 0
    echo "I don't know what your choice is" && exit 1
    ```

### 12.3.3 Shell script 的默认变量 ($0, $1...)

- `$0`: 当前脚本文件名
- `$1`: 运行脚本时提供的第 1 个参数
- `$2`: 运行脚本时提供的第 2 个参数，以此类推
- `$#`: 参数个数，即 `$1~$N`
- `$@`: 代表 `"$1" "$2" ...`
- `$*`: 代表 `"$1[c]$2[c]$3[c]$4"`，其中 `[c]` 为分隔符，默认为空格
- `shift NUM`: 参数变量编号偏移, NUM 为从 `$1` 开始移除的参数数目

例子 1：

```sh
#!/bin/bash
# Program:
#   Program shows the script name, parameters...
# History:
#   2015/07/16  VBird First release
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH

echo "The script name is        ==> $0"
echo "Total parameter number is ==> $#"
[ "$#" -lt 2 ] && echo "The number of parameter is less than 2.  Stop here." \
  && exit 0
echo "Your whole parameter is   ==> '$@'"
echo "The 1st parameter         ==> $1"
echo "The 2nd parameter         ==> $2"
```

例子 2：

```sh
#!/bin/bash
# Program:
#   Program shows the effect of shift function.
# History:
#   2009/02/17  VBird First release
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH

echo "Total parameter number is ==> $#"
echo "Your whole parameter is   ==> '$@'"
shift   # 进行第一次『一个变量的 shift 』
echo "Total parameter number is ==> $#"
echo "Your whole parameter is   ==> '$@'"
shift 3 # 进行第二次『三个变量的 shift 』
echo "Total parameter number is ==> $#"
echo "Your whole parameter is   ==> '$@'"
```

## 12.4 条件判断

### 12.4.1 利用 if...then

- 单层、简单条件判断

    ```sh
    if [ condition expression ]; then
        # do something
    fi
    ```

- `&&`, `||`: `[ "$yn" == "Y" -o "$yn" == "y" ]` 等同
  `[ "$yn" == "Y" ] || [ "$yn" == "y" ]`

    ```sh
    #!/bin/bash
    # Program:
    #   This program shows the user's choice
    # History:
    #   2015/07/16  VBird First release
    PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
    export PATH

    read -p "Please input (Y/N): " yn

    if [ "$yn" == "Y" ] || [ "$yn" == "y" ]; then
      echo "OK, continue"
      exit 0
    fi
    if [ "$yn" == "N" ] || [ "$yn" == "n" ]; then
      echo "Oh, interrupt!"
      exit 0
    fi
    echo "I don't know what your choice is" && exit 0
    ```

- 多重、复杂条件判断

>>>>> progress
