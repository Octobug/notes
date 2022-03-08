# 第十一章 正则表达式与文件格式化处理

> <https://linux.vbird.org/linux_basic/centos7/0330regularex.php>

- [第十一章 正则表达式与文件格式化处理](#第十一章-正则表达式与文件格式化处理)
  - [11.1 开始之前：什么是正则表达式](#111-开始之前什么是正则表达式)
  - [11.2 基础正则表达式](#112-基础正则表达式)
    - [11.2.1 语系对正则表达式的影响](#1121-语系对正则表达式的影响)
    - [11.2.2 grep 的一些进阶选项](#1122-grep-的一些进阶选项)
    - [11.2.3 基础正则表达式练习](#1123-基础正则表达式练习)
    - [11.2.4 基础正则表达式字符表](#1124-基础正则表达式字符表)
    - [11.2.5 sed 工具](#1125-sed-工具)
  - [11.3 扩展正则表达式](#113-扩展正则表达式)
  - [11.4 文件的格式化与相关处理](#114-文件的格式化与相关处理)
    - [11.4.1 格式化打印: printf](#1141-格式化打印-printf)
    - [11.4.2 数据处理工具: awk](#1142-数据处理工具-awk)
    - [11.4.3 文件比对工具](#1143-文件比对工具)
    - [11.4.4 文件打印准备: pr](#1144-文件打印准备-pr)
  - [11.5 重点回顾](#115-重点回顾)
  - [11.6 本章习题](#116-本章习题)
  - [11.7 参考资料与延伸阅读](#117-参考资料与延伸阅读)

RE (Regular Expression): 正则表达式

## 11.1 开始之前：什么是正则表达式

- 什么是正则表达式：使用特殊符号代表特定意义的处理字符串的方法
- 正则表达式对于系统管理员的用途：配置文件管理、日志文件的分析与处理
- 正则表达式的广泛用途：垃圾信息的检测与过滤
- 正则表达式与 Shell 在 Linux 当中的角色定位：“任督二脉”
- 扩展的正则表达式
- 正则表达式和 Bash 的 `*`(wildcard) 完全是两回事

## 11.2 基础正则表达式

### 11.2.1 语系对正则表达式的影响

由于不同语言编码中相同的字符顺序可能不一样，因此使用诸如 `[A-Z]` 这样的正则表达式时，
匹配到的结果可能不一样。

| 特殊符号     | 代表意义                                                      |
| ------------ | ------------------------------------------------------------- |
| `[:alnum:]`  | 代表英文大小写字符及数字，亦即 0-9, A-Z, a-z                  |
| `[:alpha:]`  | 代表任何英文大小写字符，亦即 A-Z, a-z                         |
| `[:blank:]`  | 代表空白键与 [Tab] 按键两者                                   |
| `[:cntrl:]`  | 代表键盘上面的控制按键，亦即包括 CR, LF, Tab, Del.. 等等      |
| `[:digit:]`  | 代表数字，亦即 0-9                                            |
| `[:graph:]`  | 除了空白字符 (空白键与 [Tab] 按键) 外的其他所有按键           |
| `[:lower:]`  | 代表小写字符，亦即 a-z                                        |
| `[:print:]`  | 代表任何可以被列印出来的字符                                  |
| `[:punct:]`  | 代表标点符号 (punctuation symbol)，亦即：" ' ? ! ; : # $...   |
| `[:space:]`  | 任何会产生空白的字符，包括空白键, [Tab], CR 等等              |
| `[:upper:]`  | 代表大写字符，亦即 A-Z                                        |
| `[:xdigit:]` | 代表 16 进位的数字类型，因此包括： 0-9, A-F, a-f 的数字与字符 |

### 11.2.2 grep 的一些进阶选项

- `grep [-A] [-B]` "keywords" filename
  - `-A`: 后跟数字，after 的意思，除了列出该行，后面的 N 行也列出
  - `-B`: 后跟数字，before 的意思，除了列出该行，前面的 N 行也列出

### 11.2.3 基础正则表达式练习

练习文本：regular_express.txt

```txt
"Open Source" is a good mechanism to develop programs.
apple is my favorite food.
Football game is not use feet only.
this dress doesn't fit me.
However, this dress is about $ 3183 dollars.^M
GNU is free air not free beer.^M
Her hair is very beauty.^M
I can't finish the test.^M
Oh! The soup taste good.^M
motorcycle is cheap than car.
This window is clear.
the symbol '*' is represented as start.
Oh!     My god!
The gd software is a library for drafting programs.^M
You are the best is mean you are the no. 1.
The world <Happy> is the same with "glad".
I like dog.
google is the best tools for search keyword.
goooooogle yes!
go! go! Let's go.
# I am VBird
```

例子：

- `grep -n "the" regular_express.txt`
- `grep -vn the regular_express.txt`
- `grep -in the regular_express.txt`
- `grep -n 't[ae]st' regular_express.txt`
- `grep -n '[^g]oo' regular_express.txt`
- `grep -n '[^a-z]oo' regular_express.txt` /
  `grep -n '[^[:lower:]]oo' regular_express.txt`
- `grep -n '^the' regular_express.txt`
- `grep -n '^[a-z]' regular_express.txt`
- `grep -n '^[^a-zA-Z]' regular_express.txt`
- `grep -n '\.$' regular_express.txt`
- `grep -n '^$' regular_express.txt`
- `grep -v '^$' regular_express.txt| grep -vn '^#'`
- `grep -n 'g..d' regular_express.txt`
- `grep -n 'ooo*' regular_express.txt`
- `grep -n 'g.*g' regular_express.txt`
- `grep -n 'o\{2\}' regular_express.txt`
- `grep -n 'go\{2,5\}g' regular_express.txt`
- `grep -n 'go\{2,\}g' regular_express.txt`

### 11.2.4 基础正则表达式字符表

| RE 字符   | 意义                                         |
| --------- | -------------------------------------------- |
| `^word`   | 待搜索的字符串 word 在行首                   |
| `word$`   | 待搜索的字符串 word 在行尾                   |
| `.`       | 代表『一定有一个任意字符』的字符             |
| `\`       | 转义字符，将特殊符号的特殊意义去除           |
| `*`       | 重复 0 到无穷多个的前一个 RE 字符            |
| `[list]`  | 用字符集匹配单个 RE 字符                     |
| `[n1-n2]` | 用字符集匹配单个 RE 字符，以编码序用范围表示 |
| `[^list]` | 用字符集匹配单个 RE 字符，`^` 表示反向匹配   |
| `\{n,m\}` | 连续 n 到 m 个的『前一个 RE 字符』           |

### 11.2.5 sed 工具

sed: stream editor, 流编辑器.

> <https://www.gnu.org/software/sed/manual/sed.html#Introduction>
>
> A stream editor is used to perform basic text transformations on an input
> stream (a file or input from a pipeline).

- `sed [-efinr] '[[n1[,n2]]function]'`
  - `-e`: 提供 sed 脚本 (可省略)
  - `-f`: 指定 sed 脚本文件
  - `-i`: 直接修改读取的文件内容而非输出到屏幕
  - `-n`: 安静模式，只输出被 sed 处理过的行。默认 stdin 会被全部输出到屏幕。
  - `-r`: 支持扩展的正则表达式
  - `[[n1[,n2]]function]`
    - `n1, n2`: 指定将要处理的行号
    - `function`
      - `a`: 追加，a 后面接字符串，增加到当前行的下一行
      - `c`: 替换，c 后面接字符串
      - `d`: 删除
      - `i`: 插入，i 后面接字符串，增加到当前行的上一行
      - `p`: 打印
      - `s`: 替换，支持正则表达式
- 例子:
  - `nl /etc/passwd | sed '2,5d'`
  - `nl /etc/passwd | sed '3,$d'`
  - `nl /etc/passwd | sed '2a drink tea or ...\ drink beer?'`
  - `nl /etc/passwd | sed '2,5c No 2-5 number'`
  - `nl /etc/passwd | sed -n '5,7p'`
  - `ifconfig | grep "inet 192" | sed 's/^.*inet //g' | sed 's/ *netmask.*//g'`
  - `cat /etc/manpath.config| grep 'MAN' | sed 's/#.*$//g' | sed '/^$/d'`
  - `sed -i 's/\.$/\!/g' regular_express.txt.bak`
  - `sed -i '$a # This is a test' regular_express.txt.bak`

## 11.3 扩展正则表达式

`grep -E` 或 `egrep`

| RE 字符 | 意义                                   |
| ------- | -------------------------------------- |
| `+`     | 重复『一个或一个以上』的前一个 RE 字符 |
| `?`     | 『零个或一个』的前一个 RE 字符         |
| `\|`    | 条件或 (or) 的方式找出数个字符串       |
| `(\|)`  | 『群组』字符串                         |
| `()+`   | 多个重复群组                           |

例子：

- `egrep -n 'go+d' regular_express.txt`
- `egrep -n 'go?d' regular_express.txt`
- `egrep -n 'gd|good|dog' regular_express.txt`
- `egrep -n 'g(la|oo)d' regular_express.txt`
- `echo 'AxyzxyzxyzxyzC' | egrep 'A(xyz)+C'`

## 11.4 文件的格式化与相关处理

### 11.4.1 格式化打印: printf

练习文本：printf.txt

```txt
Name     Chinese   English   Math    Average
DmTsai        80        60     92      77.33
VBird         75        55     80      70.00
Ken           60        90     70      73.33
```

pay.txt

```txt
Name    1st     2nd     3th
VBird   23000   24000   25000
DMTsai  21000   20000   23000
Bird2   43000   42000   41000
```

- `printf '格式' 内容`
  - 格式
    - `\a`: 输出警告声音
    - `\b`: backspace 键
    - `\f`: 清除屏幕
    - `\n`: 换行
    - `\r`: enter 键
    - `\t`: 水平 tab 键
    - `\v`: 竖直 tab 键
    - `\xNN`: NN 为两位数字，转换数字为字符
    - `%ns`: n 为数字，s 代表 string，ns 代表 n 个字符
    - `%ni`: n 为数字，i 代表 integer，ni 代表 n 位整数
    - `%N.nf`: N, n 均为数字，f 代表 float, N.nf 代表长度为 N ，且有 n 位小数的浮点数
- 例子:
  - `printf '%10s %5i %5i %5i %8.2f \n' $(cat printf.txt | grep -v Name)`
  - `printf '\x45\n'`

### 11.4.2 数据处理工具: awk

通常行处理使用 sed，列处理使用 awk。

awk 的工作流程：

1. 读入第一行，将数据填入 $0, $1, $2... 等变量中；
2. 根据 condition 判断是否进行后面的 action；
3. 完成所有的 action；
4. 如果还有数据行，则重复步骤 1-3，直到所有数据行被处理完。

- `awk 'condition1{action1} condition2{action2} ...' filename`
  - 变量
    - `$0`: 代表完整的一行
    - `$1`: 代表分割后的第 1 列，以此类推
    - `NF`: 当前行的字段数
    - `NR`: 当前行为“第几行”
    - `FS`: 当前行的分隔符，默认为空格或 tab
  - 逻辑运算符
    - `>`: 大于
    - `<`: 小于
    - `>=`: 大于等于
    - `<=`: 小于等于
    - `==`: 等于
    - `!=`: 不等于
  - action: `{}` 中的内容
    - 多个命令使用 `;` 或 `[Enter]` 隔开
    - 支持条件语句 `if...else if...else...`
- 例子:
  - `last -n 5 | awk '{print $1 "\t" $3}'`
  - `last -n 5 | awk '{print $1 "\t lines: " NR "\t columns: " NF}'`
  - `cat /etc/passwd | awk '{FS=":"} $3 < 10 {print $1 "\t " $3}'`
  - `cat /etc/passwd | awk 'BEGIN {FS=":"} $3 < 10 {print $1 "\t " $3}'`

    ```sh
    cat pay.txt |\
      awk 'NR==1{printf "%10s %10s %10s %10s %10s\n",$1,$2,$3,$4,"Total" }
        NR>=2{total = $2 + $3 + $4
        printf "%10s %10d %10d %10d %10.2f\n", $1, $2, $3, $4, total}'
    ```

### 11.4.3 文件比对工具

- `diff [-bBi] from-file to-file`: 以行为单位对比，适用于文本文件
  - `-b`: 忽略仅有任意个空格差异的行
  - `-B`: 忽略空行的差异
  - `-i`: 忽略大小写差异
- `cmp [-l] from-file to-file`: 以"字节"为单位对比，适用于任意文件
  - `-l`: 列出所有有差异的字节位置；默认只会列出第一个差异点
- `patch [-pNR] < patch_file`:
  - `-pNUM`: p 后面接数字，代表“去掉 patch 文件里 header 包含的文件路径 NUM 层目录前缀”
  - `-R`: 还原
  - 例子：
    - `diff -Naur passwd.old passwd.new > passwd.patch`
    - `patch -p0 < passwd.patch`
    - `patch -R -p0 < passwd.patch`

### 11.4.4 文件打印准备: pr

- `pr file`

## 11.5 重点回顾

## 11.6 本章习题

1. 在列出的文件数太多以至于不能作为命令参数时，可以使用 xargs 处理。

    ```sh
    find /etc -type f 2>/dev/null | xargs -n 10 grep -l '\*'
    ```

2. 利用 sed 获取当前 IP。

    ```sh
    alias myip="ifconfig | grep 'inet 192' | sed 's/^.*inet //g' |\
      cut -d ' ' -f1"
    ```

## 11.7 参考资料与延伸阅读
