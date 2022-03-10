# 第六章 Linux 文件与目录管理

> <https://linux.vbird.org/linux_basic/centos7/0220filemanager.php>

- [第六章 Linux 文件与目录管理](#第六章-linux-文件与目录管理)
  - [6.1 目录与路径](#61-目录与路径)
    - [6.1.1 相对路径与绝对路径](#611-相对路径与绝对路径)
    - [6.1.2 目录的相关操作](#612-目录的相关操作)
    - [6.1.3 关于可执行文件路径的变量: `$PATH`](#613-关于可执行文件路径的变量-path)
  - [6.2 文件与目录管理](#62-文件与目录管理)
    - [6.2.1 文件与目录的检视: ls](#621-文件与目录的检视-ls)
    - [6.2.2 复制、删除与移动：cp, rm, mv](#622-复制删除与移动cp-rm-mv)
    - [6.2.3 获取路径文件名与目录名](#623-获取路径文件名与目录名)
  - [6.3 文件内容检视](#63-文件内容检视)
    - [6.3.1 完整检视文件](#631-完整检视文件)
    - [6.3.2 可翻页检视](#632-可翻页检视)
    - [6.3.3 部分检视](#633-部分检视)
    - [6.3.4 非纯文本文件: od](#634-非纯文本文件-od)
    - [6.3.5 修改文件时间或创建新文件: touch](#635-修改文件时间或创建新文件-touch)
  - [6.4 文件与目录的默认权限与隐藏权限](#64-文件与目录的默认权限与隐藏权限)
    - [6.4.1 文件默认权限: umask](#641-文件默认权限-umask)
    - [6.4.2 文件隐藏属性](#642-文件隐藏属性)
    - [6.4.3 文件特殊权限：SUID, SGID, SBIT](#643-文件特殊权限suid-sgid-sbit)
    - [6.4.4 观察文件类型: file](#644-观察文件类型-file)
  - [6.5 指令与文件的搜寻](#65-指令与文件的搜寻)
    - [6.5.1 指令文件名的搜寻](#651-指令文件名的搜寻)
    - [6.5.2 文件文件名的搜索](#652-文件文件名的搜索)
  - [6.6 极重要的复习！权限与指令间的关系](#66-极重要的复习权限与指令间的关系)
  - [6.7 重点回顾](#67-重点回顾)
  - [6.8 本章习题](#68-本章习题)
  - [6.9 参考资料与延伸阅读](#69-参考资料与延伸阅读)

## 6.1 目录与路径

### 6.1.1 相对路径与绝对路径

⚠️ 在使用 shell 脚本管理系统时，务必使用绝对路径，因为它更不容易被写错。

### 6.1.2 目录的相关操作

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

### 6.1.3 关于可执行文件路径的变量: `$PATH`

系统会从 `$PATH` 变量中的每个目录下搜索指定的可执行文件名，先搜索到的会被执行。

```sh
$ echo $PATH
/home/linshaobiao/bin:/usr/local/bin:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/snap/bin
```

例题：为什么 $PATH 目录不加入当前目录 `.`？

答：加入当前目录确实可以方便命令执行，但由于用户经常切换目录，如果不同目录之间有名称一致的命令，
可能反而造成混乱。此外，如果有人在 `/tmp` 目录下放了一个恶意的 `ls` 命令，
那么被攻击的概率就很高了。

## 6.2 文件与目录管理

### 6.2.1 文件与目录的检视: ls

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

### 6.2.2 复制、删除与移动：cp, rm, mv

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

### 6.2.3 获取路径文件名与目录名

- `basename`
- `dirname`

## 6.3 文件内容检视

### 6.3.1 完整检视文件

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

### 6.3.2 可翻页检视

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

### 6.3.3 部分检视

- head (显示前几行)
  - `-n`: 指定行数，当行数为负数时，代表显示文件除了最后 abs(n) 行前的所有行
- tail (显示后几行)
  - `-n`: 指定行数
  - `-f`: 持续显示文件追加的内容
  
### 6.3.4 非纯文本文件: od

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
  echo abc | od -t dCc
  ```

### 6.3.5 修改文件时间或创建新文件: touch

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

## 6.4 文件与目录的默认权限与隐藏权限

除了 rwx 外，Linux 传统的 Ext2/3/4 文件系统下还有其他文件属性，使用 `chattr` 设置
`lsattr` 查看。

### 6.4.1 文件默认权限: umask

- `-S`: 显示为符号类型

最大权限值减去 umask 值得到的就是创建文件时默认的权限。

- 文件：默认没有可执行权限，因此默认最大权限为 `-rw-rw-rw-`
- 目录：默认有可执行权限，最大默认权限值为 `drwxrwxrwx`

例：umask 为 `022`，创建文件时，默认权限为:

- 文件：644
- 目录：755

### 6.4.2 文件隐藏属性

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

### 6.4.3 文件特殊权限：SUID, SGID, SBIT

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

### 6.4.4 观察文件类型: file

## 6.5 指令与文件的搜寻

### 6.5.1 指令文件名的搜寻

- `which`
  - `-a`: 将 `$PATH` 中所有可找到的命令全部列出

### 6.5.2 文件文件名的搜索

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

## 6.6 极重要的复习！权限与指令间的关系

例题：使用户能执行 `cp /dir1/file1 /dir2` 的最小权限。

答：

- dir1: x
- file1: r
- dir2: w + x

## 6.7 重点回顾

- 文件具有 SUID 时，代表使用者在运行时能拥有命令 owner 的权限
- 目录具有 SGID 时，代表使用者在该目录下新建的文件 group 与该目录一致
- 目录具有 SBIT 时，代表使用者在该目录下新建的文件只有自己与 root 能删除

## 6.8 本章习题

1. 用户 alex 与 arod 都加入了 project 用户组，假设这两个用户需要共同拥有 `/srv/ahome`
   目录的开发权，且不允许其他用户进入，请问该目录的权限如何设置？使用 SGID 又该如何设置？

   ```sh
   chmod 770 /srv/ahome
   chmod 2770 /srv/ahome
   ```

## 6.9 参考资料与延伸阅读
