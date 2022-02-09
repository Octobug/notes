# 第十三章 Linux 账号管理与 ACL 权限控制

> <https://linux.vbird.org/linux_basic/centos7/0410accountmanager.php>

## 目录

- [第十三章 Linux 账号管理与 ACL 权限控制](#第十三章-linux-账号管理与-acl-权限控制)
  - [目录](#目录)
  - [13.1 Linux 的账号与群组](#131-linux-的账号与群组)
    - [13.1.1 用户识别码：UID 与 GID](#1311-用户识别码uid-与-gid)
    - [13.1.2 用户账号](#1312-用户账号)

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
  - 每行的 7 个字段由 `:` 隔开，如下：
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

>>>>> prorgess
