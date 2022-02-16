# 第十七章 认识系统服务（daemon）

> <https://linux.vbird.org/linux_basic/centos7/0560daemons.php>

## 目录

- [第十七章 认识系统服务（daemon）](#第十七章-认识系统服务daemon)
  - [目录](#目录)
  - [17.1 什么是 daemon 与服务（service）](#171-什么是-daemon-与服务service)
    - [17.1.1 早期 System V 的 init 管理行为中 daemon 的主要分配（Optional）](#1711-早期-system-v-的-init-管理行为中-daemon-的主要分配optional)
    - [17.1.2 systemd 使用的 unit 分类](#1712-systemd-使用的-unit-分类)

## 17.1 什么是 daemon 与服务（service）

提供某些服务的进程称为 daemon。

### 17.1.1 早期 System V 的 init 管理行为中 daemon 的主要分配（Optional）

init 的管理机制特色：

- 服务的启动、关闭与查看：所有的服务启动脚本都在 `/etc/init.d/` 下，大部分是使用 shell
  script 写的脚本，大部分这样使用：
  - /etc/init.d/daemon start
  - /etc/init.d/daemon stop
  - /etc/init.d/daemon restart
  - /etc/init.d/daemon status
- 服务启动分类：
  - 独立启动模式（stand alone）：服务独立启动，常驻在内存中，提供本机、用户的服务，响应速度快
  - 总管程序（super daemon）：由特殊的 xinetd 或 inetd 提供 socket 对应或 port
    对应的管理。
- 服务的依赖性问题
- 执行等级的分类：init 是开机后内核主动调用的，随后根据用户指定的 runlevel
  来启动不同的服务。Linux 提供了 7 个执行等级，分别是：
  - 0: 停机状态
  - 1: 单用户维护模式
  - 2: 多用户模式，没有 NFS
  - 3: 完全的多用户，登录后进入纯文本命令行模式
  - 4: 保留
  - 5: 文字加图形界面
  - 6: 系统正常关闭并重启

  各个等级的启动脚本通过 `/etc/rc.d/rc[0-6]/SXXdaemon` 链接到 `/etc/init.d/daemon`。
  SXXdaemon：
  - S: start
  - XX: 数字，决定启动顺序
- 指定执行等级默认要启动的服务
  - 默认要启动：`chkconfig daemon on`
  - 默认不启动：`chkconfig daemon off`
  - 查看是否默认启动：`chkconfig --list daemon`
- 执行等级的切换：`init LEVEL`

### 17.1.2 systemd 使用的 unit 分类

>>>>> progress
