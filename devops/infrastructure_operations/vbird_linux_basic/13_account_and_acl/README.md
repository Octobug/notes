# 第十三章 Linux 账号管理与 ACL 权限控制

> <https://linux.vbird.org/linux_basic/centos7/0410accountmanager.php>

## 目录

- [第十三章 Linux 账号管理与 ACL 权限控制](#第十三章-linux-账号管理与-acl-权限控制)
  - [目录](#目录)
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
- `chsh`: 修改用户 shell

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

>>>>> prorgess
