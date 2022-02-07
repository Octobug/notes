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
    - [12.2.2 script 的执行方式差异 (source, sh script, ./script)](#1222-script-的执行方式差异-source-sh-script-script)

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

### 12.2.2 script 的执行方式差异 (source, sh script, ./script)

>>>>> progress
