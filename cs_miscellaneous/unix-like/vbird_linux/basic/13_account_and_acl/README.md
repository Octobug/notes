# 第十三章 Linux 账号管理与 ACL 权限控制

> <https://linux.vbird.org/linux_basic/centos7/0410accountmanager.php>

- [第十三章 Linux 账号管理与 ACL 权限控制](#第十三章-linux-账号管理与-acl-权限控制)
  - [13.1 Linux 的账号与群组](#131-linux-的账号与群组)
    - [13.1.1 用户识别码：UID 与 GID](#1311-用户识别码uid-与-gid)
    - [13.1.2 用户账号](#1312-用户账号)
    - [13.1.3 关于用户组：有效与初始用户组，groups, newgrp](#1313-关于用户组有效与初始用户组groups-newgrp)
  - [13.2 账号管理](#132-账号管理)
    - [13.2.1 新增与移除用户：useradd，相关配置文件，passwd，usermod，userdel](#1321-新增与移除用户useradd相关配置文件passwdusermoduserdel)
    - [13.2.2 用户功能](#1322-用户功能)
    - [13.2.3 新增与移除用户组](#1323-新增与移除用户组)
    - [13.2.4 账号管理实例](#1324-账号管理实例)
    - [13.2.5 使用外部身份认证系统](#1325-使用外部身份认证系统)
  - [13.3 主机的详细权限规划：ACL 的使用](#133-主机的详细权限规划acl-的使用)
    - [13.3.1 什么是 ACL 与如何支持启动 ACL](#1331-什么是-acl-与如何支持启动-acl)
    - [13.3.2 ACL 的设置技巧：getfacl, setfacl](#1332-acl-的设置技巧getfacl-setfacl)
  - [13.4 用户身份切换](#134-用户身份切换)
    - [13.4.1 su](#1341-su)
    - [13.4.2 sudo](#1342-sudo)
    - [13.4.x `su` vs.`sudo`](#134x-su-vssudo)
  - [13.5 用户的特殊 shell 与 PAM 模块](#135-用户的特殊-shell-与-pam-模块)
    - [13.5.1 特殊的 shell, /sbin/nologin](#1351-特殊的-shell-sbinnologin)
    - [13.5.2 PAM 模块简介](#1352-pam-模块简介)
    - [13.5.3 PAM 模块设置语法](#1353-pam-模块设置语法)
    - [13.5.4 常用模块简介](#1354-常用模块简介)
    - [13.5.5 其他相关文件](#1355-其他相关文件)
  - [13.6 Linux 主机上的用户信息传递](#136-linux-主机上的用户信息传递)
    - [13.6.1 查询使用者: w, who, last, lastlog](#1361-查询使用者-w-who-last-lastlog)
    - [13.6.2 用户对话: write, mesg, wall](#1362-用户对话-write-mesg-wall)
    - [13.6.3 使用邮箱: mail](#1363-使用邮箱-mail)
  - [13.7 CentOS 7 环境下大量创建账号的办法](#137-centos-7-环境下大量创建账号的办法)
    - [13.7.1 一些账号相关的检查工具](#1371-一些账号相关的检查工具)
    - [13.7.2 大量创建账号范例（使用 passwd --stdin 选项）](#1372-大量创建账号范例使用-passwd---stdin-选项)
  - [13.8 重点回顾](#138-重点回顾)
  - [13.9 本章习题](#139-本章习题)
  - [13.10 参考资料与延伸阅读](#1310-参考资料与延伸阅读)

## 13.1 Linux 的账号与群组

### 13.1.1 用户识别码：UID 与 GID

- 每一个文件都具有 owner 与 group 属性
- 每一个登录用户都会获得两个 ID，即 UID 与 GID

### 13.1.2 用户账号

- 账号登录的大致流程
  1. 查找 `/etc/passwd` 是否存在输入的账号。没有则退出，有则将 UID 与 GID (/etc/group)
    读取出来，另外还有 home 目录与 shell 等设置；
  2. 通过 `/etc/shadow` 找出对应账号，然后校验输入的密码是否相符；
  3. 密码正确则进入 Shell 程序。
- `/etc/passwd` 文件结构
  - 每行代表一个账号，其中有些账号是系统正常运行需要的，这些可简称为系统账号，如 bin,
    daemon, adm, nobody 等
  - 每行的 7 个字段由 `:` 隔开，分别如下：
    1. 账号名称
    2. 密码：通常只有一个 `x`；早期 Unix 系统密码存放位置，后来密码改为存放在
        `/etc/shadow`
    3. UID
        - 0: root 用户
        - 1~999: 保留给系统使用的 ID
          - 1~200：由 distributions 自行建立的系統账号
          - 201~999：当用户有系統账号需求，可以使用该范围的 UID
        - 1000 以上: 一般用户使用这个范围的 UID；新的 linux 核心 (3.10.x 版) 支持
          到 4294967295 (2^32-1) 这么大 UID
    4. GID: 用户组 ID，与 `/etc/group` 相关联
    5. 用户信息说明
    6. 用户 Home 目录
    7. 用户默认的登录 Shell
- `/etc/shadow` 文件结构
  - 将原本存在 `/etc/passwd` 的密码转移到 `/etc/passwd`，这样可以分隔密码的读取权限
  - 每行对应 passwd 中的一个账号
  - shadow 中的日期均使用天数，从 1970.1.1 开始计起
  - 每行的 9 个字段由 `:` 隔开，分别如下：
    1. 账号名称 (和 passwd 一致)；
    2. 散列过的密码；
    3. 密码的最近修改天数；
    4. 密码不可修改的天数：即 N 天之内密码最多只能修改一次，0 表示不受限制；
    5. 密码需要修改的天数：即 N 天之内密码最少需要修改一次；
    6. 密码修改期限前的警告天数；
    7. 密码过期后的账号宽限天数：在宽限期内账号仍然可以使用旧密码登录，
      系统会要求用户修改密码；过了宽限期后账号无法登录；
    8. 账号失效天数，不管密码是否过期
    9. 保留字段
- 遗忘密码
  - 普通用户：通过 root 处理
  - root 用户
    - 进入维护模式修改
    - 使用 Live CD 修改 `/etc/shadow` 文件，清空 root 密码字段
    - 云主机通常可以通过服务商提供的界面获取 root 密码

### 13.1.3 关于用户组：有效与初始用户组，groups, newgrp

- `/etc/group` 文件结构
  - 每行代表一个用户组
  - 每行的 4 个字段由 `:` 隔开，分别如下：
    1. 用户组名称
    2. 用户组密码：痛痒的，通常只有一个 `x`；密码改为存放在 `/etc/gshadow`
    3. GID
    4. 用户组成员用户名列表（使用 `,` 隔开）
  - 初始用户组（initial group）：`/etc/passwd` 中用户 GID 对应的用户组，
    用户登录之后即拥有该组的相关权限；非初始用户组则需要在 `/etc/group`
    中第四个字段加入用户；
  - 有效用户组（effective group）：用户创建新文件时使用的默认用户组，
    默认情况下和初始用户组一致。
    - `groups`: 输出的第一个用户组即为有效用户组。
    - `newgrp`: 临时切换有效用户组（进入新的 shell，并改变 $GID）
- `/etc/gshadow` 文件结构
  - 每行对应 group 中的一个账号
  - 每行的 4 个字段由 `:` 隔开，分别如下：
    1. 用户组名称
    2. 密码，如果为空或为 `!` 则表明没有管理员
    3. 用户组管理员账号
    4. 用户组成员用户名列表（和 /etc/group 一致）

## 13.2 账号管理

### 13.2.1 新增与移除用户：useradd，相关配置文件，passwd，usermod，userdel

- `useradd`: 用户管理
  - `-r`: 创建系统账号（system account）
  - `-D`: 查看 useradd 的默认配置 (`/etc/default/useradd`)
  - 其他默认设置: `/etc/login.defs` 例子

    ```txt
    MAIL_DIR        /var/spool/mail  <==用户默认邮箱目录

    PASS_MAX_DAYS   99999    <==/etc/shadow 内的第 5 个字段
    PASS_MIN_DAYS   0        <==/etc/shadow 内的第 4 个字段
    PASS_MIN_LEN    5        <==密码最小长度，已被 pam 模块取代
    PASS_WARN_AGE   7        <==/etc/shadow 内的第 6 个字段

    UID_MIN          1000    <==用户最小 UID
    UID_MAX         60000    <==用户最大 UID
    SYS_UID_MIN       201    <==保留给用户的系统账号最小 UID
    SYS_UID_MAX       999    <==保留给用户的系统账号最大 UID
    GID_MIN          1000    <==用户组最小 GID
    GID_MAX         60000    <==用户组最大 GID
    SYS_GID_MIN       201    <==保留给用户的的系统用户组最小 GID
    SYS_GID_MAX       999    <==保留给用户的的系统用户组最大 GID

    CREATE_HOME     yes      <==在不加 -M 及 -m 时，是否自动创建 Home 目录
    UMASK           077      <==创建用户 Home 目录的 umask
    USERGROUPS_ENAB yes      <==使用 userdel 删除用户时，是否删除初始用户组（无成员时）
    ENCRYPT_METHOD SHA512    <==密码加密机制
    ```

- `passwd`: 用户密码管理
  - 新发行版的密码使用 PAM 模块检查，配置位于 `/etc/pam.d/passwd`
- `chage`: 用户密码有效期管理
  - `chage -d 0 username`: 要求 username 登录后修改密码
- `usermod`: 修改用户信息
- `userdel`: 删除用户相关数据

### 13.2.2 用户功能

- `id`: 查询用户信息
- `chfn`: 用户修改个人信息
- `chsh`: 用户修改 shell

### 13.2.3 新增与移除用户组

- `groupadd`: 用户组管理
- `groupmod`: 修改用户组信息
- `groupdel`: 删除用户组
- `gpasswd`: 用户组管理员功能，将用户组成员的管理从 root 下放到用户组管理员
  - `gpasswd group_a`: 为 group_a 设置密码
  - `gpasswd -A user_a group_a`: 添加 user_a 为 group_a 管理员
  - `gpasswd -a user_b group_a`: 添加 user_b 为 group_a 成员

### 13.2.4 账号管理实例

- 任务一

  | 账号名称 | 账号全名 | 支持次要群组 | 是否可登陆主机 | 口令     |
  | -------- | -------- | ------------ | -------------- | -------- |
  | myuser1  | 1st user | mygroup1     | 可以           | password |
  | myuser2  | 2nd user | mygroup1     | 可以           | password |
  | myuser3  | 3rd user | 无额外支持   | 不可以         | password |

  ```sh
  # 先处理账号相关属性的数据：
  groupadd mygroup1
  useradd -G mygroup1 -c "1st user" myuser1
  useradd -G mygroup1 -c "2nd user" myuser2
  useradd -c "3rd user" -s /sbin/nologin myuser3

  # 再处理账号的口令相关属性的数据：
  echo "password" | passwd --stdin myuser1
  echo "password" | passwd --stdin myuser2
  echo "password" | passwd --stdin myuser3
  ```

- 任务二：我的使用者 pro1, pro2, pro3 是同一个项目计划的开发人员，
  我想要让这三个用户在同一个目录底下工作， 但这三个用户还是拥有自己的家目录与基本的私有群组。
  假设我要让这个项目计划在 `/srv/projecta` 目录下开发，可以如何进行？

  ```sh
  # 1. 假设这三个账号都尚未创建，可先创建一个名为 projecta 的群组，
  #    再让这三个用户加入其次要群组的支持即可：
  [root@www ~]# groupadd projecta
  [root@www ~]# useradd -G projecta -c "projecta user" pro1
  [root@www ~]# useradd -G projecta -c "projecta user" pro2
  [root@www ~]# useradd -G projecta -c "projecta user" pro3
  [root@www ~]# echo "password" | passwd --stdin pro1
  [root@www ~]# echo "password" | passwd --stdin pro2
  [root@www ~]# echo "password" | passwd --stdin pro3

  # 2. 开始创建此项目的开发目录：
  [root@www ~]# mkdir /srv/projecta
  [root@www ~]# chgrp projecta /srv/projecta
  [root@www ~]# chmod 2770 /srv/projecta
  [root@www ~]# ll -d /srv/projecta
  drwxrws--- 2 root projecta 4096 Feb 27 11:29 /srv/projecta
  ```

### 13.2.5 使用外部身份认证系统

## 13.3 主机的详细权限规划：ACL 的使用

### 13.3.1 什么是 ACL 与如何支持启动 ACL

ACL (Access Control List): 在传统的 owner, group, others 与 read, write, execute
之外提供更细致的权限设置。ACL 可以针对单一用户，单一文件或目录进行 r,w,x 的权限规范。
包括以下几个方面：

- 用户 (user)
- 用户组 (group)
- 默认属性 (mask): 规范新数据的默认权限

ACL 是 Unix-like 系统的额外支持项目，目前 ACL 几乎被默认加入到所有常见的 Linux
文件系统的挂载参数中。查看系统是否支持 ACL: `dmesg | grep -i acl`

### 13.3.2 ACL 的设置技巧：getfacl, setfacl

- `getfacl FILENAME`: 获取某个文件/目录的 ACL 规范
- `setfacl [-bdkR] [{-m|-x} acl参数] FILENAME`: 设置某个文件/目录的 ACL 规范
  - `-b`: 移除所有 ACL 参数
  - `-d`: 设置默认 ACL 参数
  - `-k`: 移除默认 ACL 参数
  - `-R`: 递归设置子目录
  - `-m`: 设置指定的 ACL 参数，不可与 `-x` 合用
  - `-x`: 移除指定的 ACL 参数，不可与 `-m` 合用
  - 设置单一用户权限：`u:[使用者账号列表]:[rwx-]`

    ```sh
    # 1. 针对特定使用者的方式：
    [root@www ~]# touch acl_test1
    [root@www ~]# ll acl_test1
    -rw-r--r-- 1 root root 0 Feb 27 13:28 acl_test1
    [root@www ~]# setfacl -m u:vbird1:rx acl_test1
    [root@www ~]# ll acl_test1
    -rw-r-xr--+ 1 root root 0 Feb 27 13:28 acl_test1
    # 权限部分多了个 + ，且与原本的权限 (644) 看起来差异很大！但要如何查阅呢？

    [root@www ~]# setfacl -m u::rwx acl_test1
    [root@www ~]# ll acl_test1
    -rwxr-xr--+ 1 root root 0 Feb 27 13:28 acl_test1
    # 无使用者列表，代表配置该文件拥有者，所以上面显示 root 的权限成为 rwx 了！
    ```
  
  - 设置单一用户组权限：`g:[用户组列表]:[rwx-]`

    ```sh
    # 2. 针对特定群组的方式：
    [root@www ~]# setfacl -m g:mygroup1:rx acl_test1
    [root@www ~]# getfacl acl_test1
    # file: acl_test1
    # owner: root
    # group: root
    user::rwx
    user:vbird1:r-x
    group::r--
    group:mygroup1:r-x  <==这里就是新增的部分！多了这个群组的权限配置！
    mask::r-x
    other::r--
    ```

  - 设置有效权限 (mask)：`m:[rwx-]`，用户与用户组的权限必须在 mask 的权限范围内才会生效

    ```sh
    # 3. 针对有效权限 mask 的配置方式：
    [root@www ~]# setfacl -m m:r acl_test1
    [root@www ~]# getfacl acl_test1
    # file: acl_test1
    # owner: root
    # group: root
    user::rwx
    user:vbird1:r-x        #effective:r-- <==vbird1+mask均存在者，仅有 r 而已！
    group::r--
    group:mygroup1:r-x     #effective:r--
    mask::r--
    other::r--
    ```

  - 使用默认权限设置目录的 ACL 权限继承：`d:[u|g]:[user|group]:[rwx-]`

    ```sh
    # 4. 针对默认权限的配置方式：

    # 让 myuser1 在 /srv/projecta 底下一直具有 rx 的默认权限！
    [root@www ~]# setfacl -m d:u:myuser1:rx /srv/projecta
    [root@www ~]# getfacl /srv/projecta
    # file: srv/projecta
    # owner: root
    # group: projecta
    user::rwx
    user:myuser1:r-x
    group::rwx
    mask::rwx
    other::---
    default:user::rwx
    default:user:myuser1:r-x
    default:group::rwx
    default:mask::rwx
    default:other::---

    [root@www ~]# cd /srv/projecta
    [root@www projecta]# touch zzz1
    [root@www projecta]# mkdir zzz2
    [root@www projecta]# ll -d zzz*
    -rw-rw----+ 1 root projecta    0 Feb 27 14:57 zzz1
    drwxrws---+ 2 root projecta 4096 Feb 27 14:57 zzz2
    # 看吧！确实有继承喔！然后我们使用 getfacl 再次确认看看！

    [root@www projecta]# getfacl zzz2
    # file: zzz2
    # owner: root
    # group: projecta
    user::rwx
    user:myuser1:r-x
    group::rwx
    mask::rwx
    other::---
    default:user::rwx
    default:user:myuser1:r-x
    default:group::rwx
    default:mask::rwx
    default:other::---
    ```

例题：将前一小节任务二中 `/srv/projecta` 这个目录，让 myuser1 可以进入查阅，但 myuser1
不具有修改的权力。

答：由于 myuser1 是独立的使用者与群组，而 /srv 是附属于 / 之下的，因此 /srv 已经具有 acl 的功能。 透过如下的配置即可搞定：

```sh
# 1. 先测试看看，使用 myuser1 能否进入该目录？
[myuser1@www ~]$ cd /srv/projecta
-bash: cd: /srv/projecta: Permission denied  <==确实不可进入！

# 2. 开始用 root 的身份来配置一下该目录的权限吧！
[root@www ~]# setfacl -m u:myuser1:rx /srv/projecta
[root@www ~]# getfacl /srv/projecta
# file: srv/projecta
# owner: root
# group: projecta
user::rwx
user:myuser1:r-x  <==还是要看看有没有配置成功喔！
group::rwx
mask::rwx
other::---

# 3. 还是得要使用 myuser1 去测试看看结果！
[myuser1@www ~]$ cd /srv/projecta
[myuser1@www projecta]$ ll -a
drwxrws---+ 2 root projecta 4096 Feb 27 11:29 .  <==确实可以查询档名
drwxr-xr-x  4 root root     4096 Feb 27 11:29 ..

[myuser1@www projecta]$ touch testing
touch: cannot touch `testing': Permission denied <==确实不可以写入！
```

## 13.4 用户身份切换

- 使用一般账号：日常操作尽量避免使用 root
- 用较低权限启动系统服务
- 软件本身的限制：如 telnet 本身拒绝 root 登录

### 13.4.1 su

- `su [-lm] [-c CMD] [USERNAME]`: 使用目标用户密码
  - `-`/`-l`: 使用 login-shell 的变量文件读取方式来登录系统，省略 USERNAME 时代表 root
  - `-m`/`-p`: 保留使用当前的 Shell 环境
  - `-c`: 以指定用户身份执行一次命令

### 13.4.2 sudo

- `sudo [-b] [-u USERNAME] [CMD]`: 使用当前用户密码
  - `-b`: 在后台运行命令
  - `-u`: 目标用户，省略时代表 root
- sudo 的大致执行流程
  1. 用户执行 sudo 时，系统通过 `/etc/sudoers` 文件判断用户是否满足权限
  2. 用户满足权限时，要求用户输入自己的密码
  3. 若密码正确，则开始执行 sudo 后指定的命令
  4. 若目标用户和当前用户一致，则不需要输入密码
- visudo 与 `/etc/sudoers`
  - sudoers 配置文件有语法，因此修改配置时应该使用 visudo，visudo 会做语法检查
  - `man sudoers`
- `sudo` 的时间间隔问题：5 分钟内不需要再输入密码
- 配置示例

  ```sudo
  # 管理员组配置: /etc/sudoers.d/admin
  %admin ALL=(ALL) ALL

  # 项目用户组配置: /etc/sudoers.d/project0
  %project0 ALL=(project0:project0) NOPASSWD:ALL
  ```

  添加了以上两项规则后，把个人用户加入 `admin` 组即可拥有 `root` 权限；把个人用户加入
  `project0` 组即可免密码维护 `project0` 项目，部署时使用 `sudo -iu project0`
  进入到对应的用户中操作。

  `%project0 ALL=(project0:project0) NOPASSWD:ALL` 详解：允许 `project0`
  用户组成员用户在当前系统中以 `project0` 用户的名义免密码执行 `project0`
  用户可以执行的任意命令。

  ```sudoers
  #Who       Where       As whom                     Tag          What
  #User_List Host_List = [(Runas_List1:Runas_List2)] [Tag_Spec:]  Cmnd_Spec
  %project0  ALL       = (project0     :project0  )  NOPASSWD:    ALL
  ```

  - `User_Spec`
    - `User_List`: 匹配执行 `sudo` 命令的用户，使用 `%` 符号时代表用户组。
    - `Host_List`: 匹配系统 hostname，当所有服务器维护同一份配置时该参数可以写成多个
      hostname 使不同用户在不同服务器上有不一样的权限，但这样会使规则复杂化，
      我们不采用这种方式，因此这个参数默认写 ALL。
  - `Runas_Spec`
    - `Runas_List1`: user，运行 `sudo` 命令时指向的目标用户。
    - `Runas_List2`: group，运行 `sudo` 命令时指向的目标用户组。
  - `Tag_Spec`: `sudo` 命令使用的 `tag`, `NOPASSWD` 表示不需要密码。
  - `Cmnd_Spec`: 允许 `sudo` 运行的命令。

  ⚠️ 某个用户可能会匹配中多条规则，而生效的是最后一条规则。由于 "项目用户" 的切换一般允许
  `NOPASSWD`，因此在写 "项目用户" 的 `sudoers` 配置文件时，统一在其配置文件名称前加个
  `z-` 前缀，确保免密码配置优先生效，如 `/etc/sudoers.d/z-project0`。

### 13.4.x `su` vs.`sudo`

- su 使用目标用户密码，sudo 使用当前用户密码
- su 无法切换到 `/bin/nologin` 这类用户，sudo 可以

## 13.5 用户的特殊 shell 与 PAM 模块

### 13.5.1 特殊的 shell, /sbin/nologin

- `/sbin/nologin`: shell 为 nologin 的用户无法登录
  - 定制拒绝登录信息: `/etc/nologin.txt`

### 13.5.2 PAM 模块简介

PAM (Pluggable Authentication Modules): 提供验证机制的一套 API

### 13.5.3 PAM 模块设置语法

- 调用 PAM 的流程，以 passwd 为例
  1. 用户执行 passwd 命令，并输入密码
  2. passwd 调用 PAM 模块进行验证
  3. PAM 模块到 `/etc/pam.d/` 中寻找和 passwd 同名的配置文件
  4. 根据 `/etc/pam.d/passwd` 的设置，引用相关的 PAM 模块进行验证
  5. 将验证结果返回给 passwd
  6. passwd 根据验证结果进行下一步
- PAM 配置
  - 第一个字段：Type，验证类型
    - auth (authentication): 校验用户身份
    - account: 主要进行 authorization (授权)，校验用户是否有正确的使用权限
    - session: 管理用户在当前登录会话内，PAM 提供的环境设置。
      如记录用户的登录登出时的信息。
    - password: 提供变更密码的校验机制
  - 第二个字段：Control Flag，控制标志，是验证通过的标准。
    - required: 验证成功则带有 success 标志，失败则带有 failure 标志。
      不论成功与否都会进行后续的验证。
    - requisite: 验证成功则带有 success 标志，并继续后续流程。验证失败则立即返回 failure
      标志，并终止后续流程。
    - sufficient: 验证成功则立即返回 success 给原程序，并终止后续流程。验证失败则带有
      failure 标志并继续后续流程。
    - optional: 显示讯息，没有验证作用。

### 13.5.4 常用模块简介

- `/etc/pam.d/*`: 每个程序对应的 PAM 配置文件
- `/lib64/security/*`: PAM 模块文件的实际放置目录
- `/etc/seciruty/*`: 其他 PAM 环境的配置文件
- `/usr/share/doc/pam-*`: 详细的 PAM 说明文档

常用模块：

- `pam_securetty.so`：限制系统管理员 (root) 只能够从安全的 (secure) 终端机登陆；
  什么是终端机？例如 tty1, tty2 等就是传统的终端机装置名称。而安全的终端机配置就写在
  `/etc/securetty` 这个文件中。
- `pam_nologin.so`：这个模块可以限制一般用户是否能够登陆主机。当 `/etc/nologin`
  这个文件存在时，所有一般使用者均无法再登陆系统了。一般使用者在登陆时，
  在他们的终端机上会将该文件的内容显示出来！所以，正常的情况下，这个文件应该是不能存在系统中的。但这个模块对 root 以及已经登陆系统中的一般账号并没有影响。
- `pam_selinux.so`：SELinux 是个针对程序来进行细部管理权限的功能。
- `pam_console.so`：当系统出现某些问题，或者是某些时刻你需要使用特殊的终端接口 (例如
  RS232 之类的终端联机设备) 登陆主机时， 这个模块可以帮助处理一些文件权限的问题，
  让使用者可以透过特殊终端接口 (console) 顺利的登陆系统。
- `pam_loginuid.so`：系统账号与一般账号的 UID 是不同的！为了验证使用者的 UID
  真的是我们所需要的数值，可以使用这个模块来进行规范！
- `pam_env.so`：用来配置环境变量的一个模块，如果你有需要额外的环境变量配置，可以参考
  `/etc/security/pam_env.conf` 这个文件的详细说明。
- `pam_unix.so`：这个模块可以用在验证阶段的认证功能，可以用在授权阶段的账号许可证管理，
  可以用在会议阶段的登录文件记录等，甚至也可以用在口令升级阶段的检验！
- `pam_pwquality.so`：用于检验密码的强度。包括密码是否在字典中，
  密码输入几次都失败就断掉此次连线等功能。此模块兼容早期使用的 `pam_cracklib.so` 模块，
  同时提供了 `/etc/security/pwquality.conf` 这个配置文件提供额外默认值。
- `pam_limits.so`：ulimit 使用的模块。更多详细配置可以参考
  `/etc/security/limits.conf`。

login 的 PAM 验证机制流程：

1. 验证阶段 (auth)：
    1. 先经过 `pam_securetty.so` 判断，如果使用者是 root，则会参考 `/etc/securetty`
    的配置；
    2. 经过 `pam_env.so` 配置额外的环境变量；
    3. 通过 `pam_unix.so` 检验口令，若通过则回报 login 程序；
    4. 若不通过则继续往下以 `pam_succeed_if.so` 判断 UID 是否大于 500 ，若小于 500
      则返回失败；
    5. 否则再往下以 `pam_deny.so` 拒绝联机。
2. 授权阶段 (account)：
    1. 先以 `pam_nologin.so` 判断 `/etc/nologin` 是否存在，
      若存在则不许一般使用者登陆；
    2. 接下来以 `pam_unix.so` 以及 `pam_localuser.so` 进行账号管理;
    3. 再以 `pam_succeed_if.so` 判断 UID 是否小于 1000，若小于 1000 则不记录登录信息。
    4. 最后以 `pam_permit.so` 允许该账号登陆。
3. 口令阶段 (password)：
    1. 先以 `pam_cracklib.so` 配置口令仅能尝试错误 3 次；
    2. 接下来以 `pam_unix.so` 透过 sha512, shadow 等功能进行口令检验，若通过则返回
      login 程序；
    3. 若不通过则以 `pam_deny.so` 拒绝登陆。
4. 会话阶段 (session)：
    1. 先以 `pam_selinux.so` 暂时关闭 SELinux；
    2. 使用 `pam_limits.so` 配置好用户能够操作的系统资源；
    3. 登陆成功后开始记录相关信息在登录文件中；
    4. 以 `pam_loginuid.so` 规范不同的 UID 权限；
    5. 开启 `pam_selinux.so` 的功能。

telnet 拒绝 root 登录的原因？

答：telnet 基于 login 的 PAM 模块，telnet 的终端属于 pts/n，并没有写入到
`/etc/securetty` 中。而 SSH 使用的是 /etc/pam.d/sshd` 模块，它的验证阶段没有使用
pam_securetty。

### 13.5.5 其他相关文件

- `/etc/security/limits.conf`: ulimit 配置
- `/var/log/secure`, `/var/log/messages`: 记录 PAM 模块的登录日志

## 13.6 Linux 主机上的用户信息传递

### 13.6.1 查询使用者: w, who, last, lastlog

- `w`/`who`: 查看当前登录用户
- `last`: 查看系统最近的用户登录记录
- `lastlog`: 查看所有用户的最近登录记录

### 13.6.2 用户对话: write, mesg, wall

- `write USERNAME TERMIANL`: 发送信息给指定终端的用户
- `mesg`: 设置是否接收其他用户的信息
- `wall`: 发送广播消息

### 13.6.3 使用邮箱: mail

- `mail`: 发送邮件给用户
  - `mail -s "TITLE" USERNAME < FILENAME`

## 13.7 CentOS 7 环境下大量创建账号的办法

### 13.7.1 一些账号相关的检查工具

- `pwck`: 检查 `/etc/passwd` 信息是否正确，与 `/etc/shadow` 是否一致。
- `grpck`: 检查 `/etc/group` 信息是否正确。
- `pwconv`: 校验、修改 `/etc/passwd` 与 `/etc/shadow`。
  - 比对  `/etc/passwd` 与 `/etc/shadow`，如果 passwd 中的账号没有对应的 shadow 密码，
    pwconv 会去 `/etc/login.defs` 中获取相关密码数据，并创建其 shadow 数据。
  - 将 passwd 中的密码转移到 shadow 中，passwd 中的密码会被修改为 `x`。
- `pwunconv`: 将 `/etc/shadow` 中的密码转移回 `/etc/passwd`，且删除掉 `/etc/shadow`
- `chpasswd`: 读入加密前的密码，并将加密后的密码写入 `/etc/shadow`。可用于大量创建账号。

### 13.7.2 大量创建账号范例（使用 passwd --stdin 选项）

```sh
#!/bin/bash
# This shell script will create amount of linux login accounts for you.
# 1. check the "accountadd.txt" file exist? you must create that file manually.
#    one account name one line in the "accountadd.txt" file.
# 2. use openssl to create users password.
# 3. User must change his password in his first login.
# 4. more options check the following url:
# http://linux.vbird.org/linux_basic/0410accountmanager.php#manual_amount
# 2015/07/22    VBird
export PATH=/bin:/sbin:/usr/bin:/usr/sbin

# 0. userinput
usergroup=""     # if your account need secondary group, add here.
pwmech="openssl" # "openssl" or "account" is needed.
homeperm="no"    # if "yes" then I will modify home dir permission to 711

# 1. check the accountadd.txt file
action="${1}" # "create" is useradd and "delete" is userdel.
if [ ! -f accountadd.txt ]; then
    echo "There is no accountadd.txt file, stop here."
    exit 1
fi

[ "${usergroup}" != "" ] && groupadd -r ${usergroup}
rm -f outputpw.txt
usernames=$(cat accountadd.txt)

for username in ${usernames}; do
    case ${action} in
    "create")
        [ "${usergroup}" != "" ] && usegrp=" -G ${usergroup} " || usegrp=""
        useradd ${usegrp} ${username} # 新增帳號
        [ "${pwmech}" == "openssl" ] && usepw=$(openssl rand -base64 6) || usepw=${username}
        echo ${usepw} | passwd --stdin ${username} # 建立密碼
        chage -d 0 ${username}                     # 強制登入修改密碼
        [ "${homeperm}" == "yes" ] && chmod 711 /home/${username}
        echo "username=${username}, password=${usepw}" >>outputpw.txt
        ;;
    "delete")
        echo "deleting ${username}"
        userdel -r ${username}
        ;;
    *)
        echo "Usage: $0 [create|delete]"
        ;;
    esac
done
```

## 13.8 重点回顾

- UID
  - 0: root
  - 非0: 一般账号
    - 系统用户 (1-900)
    - 可登录用户 (1000+)
- useradd 相关的配置文件
  - `/etc/default/useradd`
  - `/etc/login.defs`
  - `/etc/skel/*`
- 用户可自行修改信息的命令
  - chsh
  - chfn

## 13.9 本章习题

## 13.10 参考资料与延伸阅读
