# 第十二章 学习 shell scripts

> <https://linux.vbird.org/linux_basic/centos7/0340bashshell-scripts.php>

- [第十二章 学习 shell scripts](#第十二章-学习-shell-scripts)
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
    - [12.4.2 利用 case ... esac 判断](#1242-利用-case--esac-判断)
    - [12.4.3 利用 function 功能](#1243-利用-function-功能)
  - [12.5 循环 (loop)](#125-循环-loop)
    - [12.5.1 while do done, until do done (不定循环)](#1251-while-do-done-until-do-done-不定循环)
    - [12.5.2 for...do...done (固定循环)](#1252-fordodone-固定循环)
    - [12.5.3 for...do...done 的数值处理](#1253-fordodone-的数值处理)
    - [12.5.4 搭配随机数与数组的实验](#1254-搭配随机数与数组的实验)
  - [12.6 Shell script 的追踪与 debug](#126-shell-script-的追踪与-debug)
  - [12.7 重点回顾](#127-重点回顾)
  - [12.8 本章习题](#128-本章习题)

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
#   This program shows "Hello World!" in your screen.
# History:
# 2015/07/16  VBird First release
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
    # 2015/07/16  VBird First release
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
    # 2015/08/25  VBird First release
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
  - 语法

    ```sh
    if [ condition ]; then
        # do something
    fi
    ```

  - 多条件组合: `&&`, `||`: `[ "$yn" == "Y" -o "$yn" == "y" ]` 等同
    `[ "$yn" == "Y" ] || [ "$yn" == "y" ]`
  - 例子

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
  - 语法

    ```sh
    if [ condition1 ]; then
        # do something
    elif [ condition2 ]; then
        # do something
    else
        # do something
    fi
    ```

- 例子1

  ```sh
  #!/bin/bash
  # Program:
  #   This program shows the user's choice
  # History:
  # 2015/07/16  VBird First release
  PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
  export PATH

  read -p "Please input (Y/N): " yn

  if [ "$yn" == "Y" ] || [ "$yn" == "y" ]; then
    echo "OK, continue"
  elif [ "$yn" == "N" ] || [ "$yn" == "n" ]; then
    echo "Oh, interrupt!"
  else
    echo "I don't know what your choice is"
  fi
  ```

- 例子2

  ```sh
  #!/bin/bash
  # Program:
  #   Check $1 is equal to "hello"
  # History:
  # 2015/07/16  VBird First release
  PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
  export PATH

  if [ "$1" == "hello" ]; then
    echo "Hello, how are you ?"
  elif [ "$1" == "" ]; then
    echo "You MUST input parameters, ex> {$0 someword}"
  else
    echo "The only parameter is 'hello', ex> {$0 hello}"
  fi
  ```

- 例子3: `netstat -tuln`

  ```sh
  #!/bin/bash
  # Program:
  #   Using netstat and grep to detect WWW,SSH,FTP and Mail services.
  # History:
  # 2015/07/16  VBird First release
  PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
  export PATH

  # 1. 先作一些告知的动作而已～
  echo "Now, I will detect your Linux server's services!"
  echo -e "The www, ftp, ssh, and mail will be detect! \n"

  # 2. 开始进行一些测试的工作，并且也输出一些资讯罗！
  testing=$(netstat -tuln | grep ":80 ")   # 侦测看 port 80 在否？
  if [ "$testing" != "" ]; then
    echo "WWW is running in your system."
  fi
  testing=$(netstat -tuln | grep ":22 ")   # 侦测看 port 22 在否？
  if [ "$testing" != "" ]; then
    echo "SSH is running in your system."
  fi
  testing=$(netstat -tuln | grep ":21 ")   # 侦测看 port 21 在否？
  if [ "$testing" != "" ]; then
    echo "FTP is running in your system."
  fi
  testing=$(netstat -tuln | grep ":25 ")   # 侦测看 port 25 在否？
  if [ "$testing" != "" ]; then
    echo "Mail is running in your system."
  fi
  ```

- 例子4

  ```sh
  #!/bin/bash
  # Program:
  #   You input your demobilization date, I calculate how many days
  #     before you demobilize.
  # History:
  # 2015/07/16  VBird First release
  PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
  export PATH

  # 1. 告知使用者这支程序的用途，并且告知应该如何输入日期格式？
  echo "This program will try to calculate:"
  echo "How many days before your demobilization date..."
  read -p "Please input your demobilization date (YYYYMMDD ex>20090401): " date2

  # 2. 测试一下，这个输入的内容是否正确？利用正规表示法罗～
  date_d=$(echo $date2 |grep '[0-9]\{8\}')   # 看看是否有八个数字
  if [ "$date_d" == "" ]; then
    echo "You input the wrong date format...."
    exit 1
  fi

  # 3. 开始计算日期罗～
  declare -i date_dem=`date --date="$date2" +%s`    # 退伍日期秒数
  declare -i date_now=`date +%s`                    # 现在日期秒数
  declare -i date_total_s=$(($date_dem-$date_now))  # 剩余秒数统计
  declare -i date_d=$(($date_total_s/60/60/24))     # 转为日数
  if [ "$date_total_s" -lt "0" ]; then              # 判断是否已退伍
    echo "You had been demobilization before: "$((-1*$date_d))" days ago"
  else
    declare -i date_h=$(($(($date_total_s-$date_d*60*60*24))/60/60))
    echo "You will demobilize after $date_d days and $date_h hours."
  fi
  ```

### 12.4.2 利用 case ... esac 判断

- 语法

  ```sh
  case $var in
    "value1")
      # do something
      ;;
    "value2")
      # do something
      ;;
    *)
      # do something
      ;;
  esac
  ```

- 例子1

  ```sh
  #!/bin/bash
  # Program:
  #   Show "Hello" from $1.... by using case .... esac
  # History:
  #   2015/07/16  VBird First release
  PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
  export PATH

  case $1 in
    "hello")
      echo "Hello, how are you ?"
      ;;
    "")
      echo "You MUST input parameters, ex> {$0 someword}"
      ;;
    *)   # 其实就相当於万用字节，0~无穷多个任意字节之意！
      echo "Usage $0 {hello}"
      ;;
  esac
  ```

- 例子2

  ```sh
  #!/bin/bash
  # Program:
  #   This script only accepts the flowing parameter: one, two or three.
  # History:
  # 2015/07/17  VBird First release
  PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
  export PATH

  echo "This program will print your selection !"
  # read -p "Input your choice: " choice # 暂时取消，可以替换！
  # case $choice in                      # 暂时取消，可以替换！
  case $1 in                             # 现在使用，可以用上面两行替换！
    "one")
      echo "Your choice is ONE"
      ;;
    "two")
      echo "Your choice is TWO"
      ;;
    "three")
      echo "Your choice is THREE"
      ;;
    *)
      echo "Usage $0 {one|two|three}"
      ;;
  esac
  ```

### 12.4.3 利用 function 功能

- 语法

  ```sh
  function fname() {
    # do something
  }
  ```

  - 函数必须在被使用之前定义
  - 函数特殊变量
    - `$0`: 函数名称
    - `$1`: 函数第 1 个参数
    - `$2`: 函数第 2 个参数，以此类推
- 例子1

  ```sh
  #!/bin/bash
  # Program:
  #   Use function to repeat information.
  # History:
  # 2015/07/17  VBird First release
  PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
  export PATH

  function printit(){
    echo -n "Your choice is "     # 加上 -n 可以不断行继续在同一行显示
  }

  echo "This program will print your selection !"
  case $1 in
    "one")
      printit; echo $1 | tr 'a-z' 'A-Z'  # 将参数做大小写转换！
      ;;
    "two")
      printit; echo $1 | tr 'a-z' 'A-Z'
      ;;
    "three")
      printit; echo $1 | tr 'a-z' 'A-Z'
      ;;
    *)
      echo "Usage $0 {one|two|three}"
      ;;
  esac
  ```

- 例子2

  ```sh
  #!/bin/bash
  # Program:
  #   Use function to repeat information.
  # History:
  # 2015/07/17  VBird First release
  PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
  export PATH

  function printit(){
    echo "Your choice is $1"   # 这个 $1 必须要参考底下命令的下达
  }

  echo "This program will print your selection !"
  case $1 in
    "one")
      printit 1  # 请注意， printit 命令后面还有接参数！
      ;;
    "two")
      printit 2
      ;;
    "three")
      printit 3
      ;;
    *)
      echo "Usage $0 {one|two|three}"
      ;;
  esac
  ```

## 12.5 循环 (loop)

### 12.5.1 while do done, until do done (不定循环)

- 语法

  ```sh
  # while do
  while [ condition ]
  do
    # do something
  done

  # until do
  until [ condition ]
    # do something
  done
  ```

- 例子1

  ```sh
  #!/bin/bash
  # Program:
  # Repeat question until user input correct answer.
  # History:
  # 2015/07/17  VBird First release
  PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
  export PATH

  while [ "$yn" != "yes" -a "$yn" != "YES" ]; do
      read -p "Please input yes/YES to stop this program: " yn
  done
  echo "OK! you input the correct answer."
  ```

- 例子2

  ```sh
  #!/bin/bash
  # Program:
  #   Repeat question until user input correct answer.
  # History:
  # 2015/07/17  VBird First release
  PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
  export PATH

  until [ "$yn" == "yes" -o "$yn" == "YES" ]
  do
    read -p "Please input yes/YES to stop this program: " yn
  done
  echo "OK! you input the correct answer."
  ```

- 例子3

  ```sh
  #!/bin/bash
  # Program:
  #   Use loop to calculate "1+2+3+...+100" result.
  # History:
  # 2015/07/17  VBird First release
  PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
  export PATH

  s=0  # 这是加总的数值变量
  i=0  # 这是累计的数值，亦即是 1, 2, 3....
  while [ "$i" != "100" ]
  do
    i=$(($i+1))   # 每次 i 都会添加 1 
    s=$(($s+$i))  # 每次都会加总一次！
  done
  echo "The result of '1+2+3+...+100' is ==> $s"
  ```

### 12.5.2 for...do...done (固定循环)

- 语法

  ```sh
  for var in con1 con2 con3 ...
  do
    # do something
  done
  ```

- 例子1

  ```sh
  #!/bin/bash
  # Program:
  #   Using for .... loop to print 3 animals
  # History:
  # 2015/07/17  VBird First release
  PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
  export PATH

  for animal in dog cat elephant
  do
    echo "There are ${animal}s.... "
  done
  ```

- 例子2

  ```sh
  #!/bin/bash
  # Program
  #   Use id command to check system account's information.
  # History
  # 2015/07/17  VBird first release
  PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
  export PATH
  users=$(cut -d ':' -f1 /etc/passwd)  # 撷取帐号名称
  for username in $users               # 开始回圈进行！
  do
    id $username
  done
  ```

- 例子3

  ```sh
  #!/bin/bash
  # Program
  #   Use ping command to check the network's PC state.
  # History
  # 2015/07/17  VBird first release
  PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
  export PATH
  network="192.168.1"             # 先定义一个网域的前面部分！
  for sitenu in $(seq 1 100)      # seq 为 sequence(连续) 的缩写之意
                                  # $(seq 1 100) 可以用 {1..100} 代替
  do
    # 底下的程序在取得 ping 的回传值是正确的还是失败的！
    ping -c 1 -w 1 ${network}.${sitenu} &> /dev/null && result=0 || result=1
    # 开始显示结果是正确的启动 (UP) 还是错误的没有连通 (DOWN)
    if [ "$result" == 0 ]; then
      echo "Server ${network}.${sitenu} is UP."
    else
      echo "Server ${network}.${sitenu} is DOWN."
    fi
  done
  ```

- 例子4

  ```sh
  #!/bin/bash
  # Program:
  #   User input dir name, I find the permission of files.
  # History:
  # 2015/07/17  VBird First release
  PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
  export PATH

  # 1. 先看看这个目录是否存在啊？
  read -p "Please input a directory: " dir
  if [ "$dir" == "" -o ! -d "$dir" ]; then
    echo "The $dir is NOT exist in your system."
    exit 1
  fi

  # 2. 开始测试文件罗～
  filelist=$(ls $dir)        # 列出所有在该目录下的文件名称
  for filename in $filelist
  do
    perm=""
    test -r "$dir/$filename" && perm="$perm readable"
    test -w "$dir/$filename" && perm="$perm writable"
    test -x "$dir/$filename" && perm="$perm executable"
    echo "The file $dir/$filename's permission is $perm "
  done
  ```

### 12.5.3 for...do...done 的数值处理

- 语法

  ```sh
  for ((单次表达式; 条件表达式; 末尾循环体))
  do
    # do something
  done
  ```

- 例子

  ```sh
  #!/bin/bash
  # Program:
  #   Try do calculate 1+2+....+${your_input}
  # History:
  # 2015/07/17  VBird First release
  PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
  export PATH

  read -p "Please input a number, I will count for 1+2+...+your_input: " nu

  s=0
  for (( i=1; i<=$nu; i=i+1 ))
  do
    s=$(($s+$i))
  done
  echo "The result of '1+2+3+...+$nu' is ==> $s"
  ```

### 12.5.4 搭配随机数与数组的实验

例子1

```sh
#!/bin/bash
# Program:
#   Try to tell you what you may eat.
# History:
# 2015/07/17  VBird First release
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH

eat[1]="麦当劳"
eat[2]="肯德基"
eat[3]="小女当家"
eat[4]="大米先生"
eat[5]="津味源"
eat[6]="猪脚饭"
eat[7]="老碗会"
eat[8]="萨莉亚"
eat[9]="711"
eatnum=9      # 可用餐厅数

check=$((${RANDOM} * ${eatnum} / 32767 + 1))
echo "you may eat ${eat[${check}]}"
```

例子2

```sh
#!/bin/bash
# Program:
#   Try to tell you what you may eat.
# History:
# 2015/07/17  VBird First release
PATH=/bin:/sbin:/usr/bin:/usr/sbin:/usr/local/bin:/usr/local/sbin:~/bin
export PATH

eat[1]="麦当劳"
eat[2]="肯德基"
eat[3]="小女当家"
eat[4]="大米先生"
eat[5]="津味源"
eat[6]="猪脚饭"
eat[7]="老碗会"
eat[8]="萨莉亚"
eat[9]="711"
eatnum=9 # 可用餐厅数

eated=0
while [ "${eated}" -lt 3 ]; do
    check=$((${RANDOM} * ${eatnum} / 32767 + 1))
    mycheck=0
    if [ "${eated}" -ge 1 ]; then
        for i in $(seq 1 ${eated}); do
            if [ ${eatedcon[$i]} == $check ]; then
                mycheck=1
            fi
        done
    fi
    if [ ${mycheck} == 0 ]; then
        echo "you may eat ${eat[${check}]}"
        eated=$((${eated} + 1))
        eatedcon[${eated}]=${check}
    fi
done
```

## 12.6 Shell script 的追踪与 debug

- `sh [-nvx] script.sh`
  - `-n`: 不执行 script，仅检查语法
  - `-v`: 在执行 script 前将 script 内容显示到屏幕上
  - `-x`: 将 script 的执行过程显示到屏幕

## 12.7 重点回顾

## 12.8 本章习题

1.请创建一支 script ，当你运行该 script 的时候，该 script 可以显示： 1. 你目前的身份 (用
whoami ); 2.你目前所在的目录 (用 pwd).

```sh
#!/bin/bash
echo -e "Your name is ==> $(whoami)"
echo -e "The current directory is ==> $(pwd)"
```

2.请自行创建一支程序，该程序可以用来计算『你还有几天可以过生日』啊？

```sh
#!/bin/bash
read -p "Pleas input your birthday (MMDD, ex> 0709): " bir
now=$(date +%m%d)
if [ "$bir" == "$now" ]; then
    echo "Happy Birthday to you!!!"
elif [ "$bir" -gt "$now" ]; then
    year=$(date +%Y)
    total_d=$(($(($(date --date="$year$bir" +%s) - $(date +%s))) / 60 / 60 / 24))
    echo "Your birthday will be $total_d later"
else
    year=$(($(date +%Y) + 1))
    total_d=$(($(($(date --date="$year$bir" +%s) - $(date +%s))) / 60 / 60 / 24))
    echo "Your birthday will be $total_d later"
fi
```

3.让使用者输入一个数字，程序可以由 1+2+3... 一直累加到使用者输入的数字为止。

```sh
#!/bin/bash
read -p "Please input an integer number: " number
i=0
s=0
while [ "$i" != "$number" ]; do
    i=$(($i + 1))
    s=$(($s + $i))
done
echo "the result of '1+2+3+...$number' is ==> $s"
```

4.撰写一支程序，他的作用是:
1.) 先查看一下 /root/test/logical 这个名称是否存在；
2.) 若不存在，则创建一个文件，使用 touch 来创建，创建完成后离开；
3.) 如果存在的话，判断该名称是否为文件，若为文件则将之删除后创建一个目录，档名为 logical
，之后离开；
4.) 如果存在的话，而且该名称为目录，则移除此目录！

```sh
#!/bin/bash
if [ ! -e logical ]; then
    touch logical
    echo "Just make a file logical"
    exit 1
elif [ -e logical ] && [ -f logical ]; then
    rm logical
    mkdir logical
    echo "remove file ==> logical"
    echo "and make directory logical"
    exit 1
elif [ -e logical ] && [ -d logical ]; then
    rm -rf logical
    echo "remove directory ==> logical"
    exit 1
else
    echo "Does here have anything?"
fi
```

5.我们知道 /etc/passwd 里面以 : 来分隔，第一栏为帐号名称。请写一只程序，可以将
/etc/passwd 的第一栏取出，而且每一栏都以一行字串『The 1 account is "root" 』来显示，
那个 1 表示行数。

```sh
#!/bin/bash
accounts=$(cat /etc/passwd | cut -d':' -f1)
for account in $accounts; do
    declare -i i=$i+1
    echo "The $i account is \"$account\" "
done
```
