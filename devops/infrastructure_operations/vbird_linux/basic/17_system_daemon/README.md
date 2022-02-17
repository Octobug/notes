# 第十七章 认识系统服务（daemon）

> <https://linux.vbird.org/linux_basic/centos7/0560daemons.php>

## 目录

- [第十七章 认识系统服务（daemon）](#第十七章-认识系统服务daemon)
  - [目录](#目录)
  - [17.1 什么是 daemon 与服务（service）](#171-什么是-daemon-与服务service)
    - [17.1.1 早期 System V 的 init 管理行为中 daemon 的主要分配（Optional）](#1711-早期-system-v-的-init-管理行为中-daemon-的主要分配optional)
    - [17.1.2 systemd 使用的 unit 分类](#1712-systemd-使用的-unit-分类)
  - [17.2 通过 systemctl 管理服务](#172-通过-systemctl-管理服务)
    - [17.2.1 通过 systemctl 管理单一服务 (service unit) 的启动/开机启动与查看](#1721-通过-systemctl-管理单一服务-service-unit-的启动开机启动与查看)
    - [17.2.2 通过 systemctl 观察系统上的所有服务](#1722-通过-systemctl-观察系统上的所有服务)
    - [17.2.3 通过 systemctl 管理不同的操作环境 (target unit)](#1723-通过-systemctl-管理不同的操作环境-target-unit)
    - [17.2.4 通过 systemctl 分析各服务之间的依赖性](#1724-通过-systemctl-分析各服务之间的依赖性)
    - [17.2.5 与 systemd 的 daemon 运行过程相关的目录简介](#1725-与-systemd-的-daemon-运行过程相关的目录简介)
    - [17.2.6 关闭网络服务](#1726-关闭网络服务)
  - [17.3 systemctl 针对 service 类型的配置文件](#173-systemctl-针对-service-类型的配置文件)
    - [17.3.1 systemctl 配置文件相关目录简介](#1731-systemctl-配置文件相关目录简介)
    - [17.3.2 systemctl 配置文件的设置项目简介](#1732-systemctl-配置文件的设置项目简介)
    - [17.3.3 两个 vsftpd 运行实例](#1733-两个-vsftpd-运行实例)
    - [17.3.4 多重的重复设置方式: 以 getty 为例](#1734-多重的重复设置方式-以-getty-为例)
    - [17.3.5 自己的服务自己做](#1735-自己的服务自己做)
  - [17.4 systemctl 针对 timer 的配置文件](#174-systemctl-针对-timer-的配置文件)
  - [17.5 CentOS 7.x 默认启动的服务简易说明](#175-centos-7x-默认启动的服务简易说明)
  - [17.6 重点回顾](#176-重点回顾)
  - [17.7 本章习题](#177-本章习题)
  - [17.8 参考资料与延伸阅读](#178-参考资料与延伸阅读)

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

- systemd 的优点：
  - 平行处理所有服务，加速开机流程；init 是一项一项按序启动
  - on-demand 启动方式：systemd 只需要 systemd 服务搭配 systemctl 命令
  - 服务依赖的自我检查：依赖的服务会被自动启动
  - 依 daemon 功能分类：以每个服务为单位 (unit)，归类到不同类型中 (type)：
    - service
    - socket
    - target
    - path
    - snapshot
    - timer
  - 将多个 daemons 合为一个群组：类似 init 的 runlevel
  - 兼容旧有的 init 服务脚本
- systemd 的局限性：
  - 在 runlevel 上，只能对应 1, 3, 5 到 systemd 的某些 target 类型
  - 全部 systemd 用 systemctl 管理，而 systemctl 支持的语法有限，无法像
    `/etc/init.d/daemon` 一样自定义
  - systemd 无法感知手动直接启动的进程，即必须使用 systemctl 启动
  - systemd 启动过程中无法接收 stdin
- systemd 的配置文件放置目录，按优先级排序如下：
  1. `/etc/systemd/system`: 管理员定制的执行脚本，往往是链接文件
  2. `/run/systemd/system`: 系统执行过程中产生的服务脚本
  3. `/usr/lib/systemd/system/`: 每个服务最主要的启动脚本，是实际的启动脚本文件摆放位置
- systemd 的 unit 分类说明，对应启动脚本文件名后缀，如 `crond.service`

  | 类型       | 功能                                                           |
  | ---------- | -------------------------------------------------------------- |
  | .service   | 一般服务：主要是系统服务，包括本机及网络服务                   |
  | .socket    | 内部进程数据交互服务，即 IPC                                   |
  | .target    | 执行环境类型服务，是一群 unit 的集合                           |
  | .mount     | 文件系统挂载相关的服务，如 NFS 的自动挂载                      |
  | .automount | 文件系统挂载相关的服务，如 NFS 的自动挂载                      |
  | .path      | 检测特定文件或目录类型，如某些服务需要检测特定目录提供打印服务 |
  | .timer     | 循环执行的服务：有点类似 anacrontab，由 systemd 本身提供       |

## 17.2 通过 systemctl 管理服务

### 17.2.1 通过 systemctl 管理单一服务 (service unit) 的启动/开机启动与查看

- `systemctl [COMMAND] [UNIT]`
  - COMMAND
    - disable: 取消开机启动
    - enable: 开机启动
    - is-active: 是否运行中
    - is-enable: 是否设置了开机启动
    - restart: stop & start
    - reload: 重新加载配置
    - start: 启动
    - status: 查看状态
    - stop: 关闭

daemon 的 systemd 状态：

- active
  - running: 服务正在运行
  - exited: 仅执行一次就正常结束的服务，如 quotaon
  - waiting: 正在运行但是需要等待其他事件，如打印服务需要等待打印工作
- inactive: 服务没有运行
- enabled: 已启用开机启动
- disabled: 已关闭开机启动
- static: 该服务不会自行启动，可能会被其他服务唤醒
- mask: 已被强制注销的服务，启用需要使用 systemctl unmask 恢复

### 17.2.2 通过 systemctl 观察系统上的所有服务

- `systemctl [COMMAND] [--type=TYPE] [--all]`
  - COMMAND
    - list-units
    - list-unit-files
  - `--type=TYPE`

### 17.2.3 通过 systemctl 管理不同的操作环境 (target unit)

几个主要的 target:

- graphical.target: 文字加上图形界面
- multi-user.target: 纯文本模式
- rescue.target: 额外的临时系统，与原本的系统无关。此时可以取得 root 权限来维护
- emergency.target: 紧急处理系统错误，也需要 root 登录
- shutdown.target: 关机流程
- getty.target: tty 相关设置

查看当前的操作环境：

- `systemctl [COMMAND] [unit.target]`
  - COMMAND
    - get-default: 查看当前 target
    - set-default: 设置默认 target
    - isolate: 切换到新的 target
  - 直接的操作模式切换
    - poweroff
    - reboot
    - suspend
    - hibernate
    - rescue
    - emergency

### 17.2.4 通过 systemctl 分析各服务之间的依赖性

- `systemctl list-dependencies [UNIT] [--reverse]`

### 17.2.5 与 systemd 的 daemon 运行过程相关的目录简介

- `/usr/lib/systemd/system`: CentOS 默认的启用脚本配置文件
- `/run/systemd/system`: 系统运行过程中产生的服务脚本
- `/etc/systemd/system`: 管理员自定义的脚本
- `/etc/sysconfig/`: 几乎所有的五福都会把初始化参数写入到该目录下
- `/var/lib`: 会产生数据的服务都会将数据存储到该目录
- `/run/`: 放置 daemon 的暂存文件，如 lock file 及 PID file

socket 文件的管理：

- `systemctl list-sockets`

网络服务于端口对应简介：

- `cat /etc/services`

### 17.2.6 关闭网络服务

- netstat -tlunp

## 17.3 systemctl 针对 service 类型的配置文件

### 17.3.1 systemctl 配置文件相关目录简介

以 vsftpd.service 为例：

- `/usr/lib/systemd/system/vsftpd.service`: 官方默认配置文件
- `/etc/systemd/system/vsftpd.service.d/custom.conf`: 自定义配置在
  `/etc/systemd/system` 目录下创建同名目录且加上 `.d` 后缀，该目录下的配置文件建议以
  `.conf` 为文件后缀名
- `/etc/systemd/system/vsftpd.service.wants/*`: 目录内为链接文件，设置启动后依赖的服务
- `/etc/systemd/system/vsftpd.service.requires/*`: 目录内为链接文件，
  设置启动前依赖的服务

### 17.3.2 systemctl 配置文件的设置项目简介

以 sshd 为例：

```sh
# ubuntu
cat /lib/systemd/system/ssh.service

[Unit]
Description=OpenBSD Secure Shell server
After=network.target auditd.service
ConditionPathExists=!/etc/ssh/sshd_not_to_be_run

[Service]
EnvironmentFile=-/etc/default/ssh
ExecStartPre=/usr/sbin/sshd -t
ExecStart=/usr/sbin/sshd -D $SSHD_OPTS
ExecReload=/usr/sbin/sshd -t
ExecReload=/bin/kill -HUP $MAINPID
KillMode=process
Restart=on-failure
RestartPreventExitStatus=255
Type=notify
RuntimeDirectory=sshd
RuntimeDirectoryMode=0755

[Install]
WantedBy=multi-user.target
Alias=sshd.service
```

- `[Unit]`: unit 的说明，且包括其他依赖的服务

  | 参数          | 意义                                        |
  | ------------- | ------------------------------------------- |
  | Description   | 服务描述信息                                |
  | Documentation | 服务详细文档，Documentation=<http://www...> |
  |               | Documentation=man:sshd(8)                   |
  |               | Documentation=file:/etc/ssh/sshd_config     |
  | After         | 建议在某些 daemon 之后启动                  |
  | Before        | 建议在某些 daemon 之前启动                  |
  | Requires      | 必须在某些 daemon 启动后才启动              |
  | Wants         | 启动后最好启动的 daemon                     |
  | Conflicts     | 会产生冲突的 daemon，不会同时启动           |

- `[Service]`, `[Socket]`, `[Timer]`, `[Mount]`, `[Path]`: 不同的 unit type
  要使用对应的设置项，主要规范服务启动的脚本、环境配置文件、重启方式等

  | 参数            | 意义                                                    |
  | --------------- | ------------------------------------------------------- |
  | Type            | 说明 daemon 的启动方式                                  |
  |                 | simple: 默认值，启动之后常驻内存                        |
  |                 | forking: 启动的进程通过 spawns 创建子进程，父进程再退出 |
  |                 | oneshot: 与 simple 类似，不过工作完成后就退出           |
  |                 | dbus: 与 simple 类似，在取得 D-Bus 名称后才会继续工作   |
  |                 | idle: 与 simple 类似，在所有 daemon 顺利执行后才执行    |
  | EnvironmentFile | 指定启动脚本的环境设置文件                              |
  | ExecStart       | 实际执行 daemon 的命令或脚本                            |
  | ExecStop        | systemctl stop 时执行的命令                             |
  | ExecReload      | systemctl reload 时执行的命令                           |
  | Restart         | Restart=1 时，daemon 停止时会自动重启                   |
  | RemainAfterExit | RemainAfterExit=1 时，daemon 所属的进程退出后会再次启动 |
  | TimeoutSec      | 启动或关闭时出现故障，等多久才进入强制结束              |
  | KillMode        | 可以是 process, control-group, none 中的一种            |
  |                 | process: daemon 退出时只会终止主进程                    |
  |                 | control-group: daemon 产生的其他 control-group 也会关闭 |
  |                 | none: 没有进程会被关闭                                  |
  | RestartSec      | 与 Restart 相关，重新启动时 sleep 多少时间才重启        |

- `[Install]`: 将 unit 加入到某些 target

  | 参数     | 意义                                                      |
  | -------- | --------------------------------------------------------- |
  | WantedBy | 后面接的大部分是 `*.target` unit                          |
  | Also     | 当前 unit 被 enabled 时，也 enable 其他 daemon            |
  | Alias    | 链接别名，systemctl enable 时会创建链接当前配置的链接文件 |

### 17.3.3 两个 vsftpd 运行实例

可以设置两个 vsftpd 实例，监听于不同端口。

```sh
# 1. 先建立好所需要的設定檔
[root@study ~]# cd /etc/vsftpd
[root@study vsftpd]# cp vsftpd.conf vsftpd2.conf
[root@study vsftpd]# vim vsftpd.conf
#listen_port=555

[root@study vsftpd]# diff vsftpd.conf vsftpd2.conf
128c128
< #listen_port=555
---
> listen_port=555
# 注意這兩個設定檔的差別喔！只有這一行不同而已！

# 2. 開始處理啟動腳本設定
[root@study vsftpd]# cd /etc/systemd/system
[root@study system]# cp /usr/lib/systemd/system/vsftpd.service vsftpd2.service
[root@study system]# vim vsftpd2.service
[Unit]
Description=Vsftpd second ftp daemon
After=network.target

[Service]
Type=forking
ExecStart=/usr/sbin/vsftpd /etc/vsftpd/vsftpd2.conf

[Install]
WantedBy=multi-user.target
# 重點在改了 vsftpd2.conf 這個設定檔喔！

# 3. 重新載入 systemd 的腳本設定檔內容
[root@study system]# systemctl daemon-reload
[root@study system]# systemctl list-unit-files --all | grep vsftpd
vsftpd.service                              enabled
vsftpd2.service                             disabled
vsftpd@.service                             disabled
vsftpd.target                               disabled

[root@study system]# systemctl status vsftpd2.service
vsftpd2.service - Vsftpd second ftp daemon
   Loaded: loaded (/etc/systemd/system/vsftpd2.service; disabled)
   Active: inactive (dead)

[root@study system]# systemctl restart vsftpd.service vsftpd2.service
[root@study system]# systemctl enable  vsftpd.service vsftpd2.service
[root@study system]# systemctl status  vsftpd.service vsftpd2.service
vsftpd.service - Vsftpd ftp daemon
   Loaded: loaded (/usr/lib/systemd/system/vsftpd.service; enabled)
   Active: active (running) since Wed 2015-08-12 22:00:17 CST; 35s ago
 Main PID: 12670 (vsftpd)
   CGroup: /system.slice/vsftpd.service
           └─12670 /usr/sbin/vsftpd /etc/vsftpd/vsftpd.conf

Aug 12 22:00:17 study.centos.vbird systemd[1]: Started Vsftpd ftp daemon.

vsftpd2.service - Vsftpd second ftp daemon
   Loaded: loaded (/etc/systemd/system/vsftpd2.service; enabled)
   Active: active (running) since Wed 2015-08-12 22:00:17 CST; 35s ago
 Main PID: 12672 (vsftpd)
   CGroup: /system.slice/vsftpd2.service
           └─12672 /usr/sbin/vsftpd /etc/vsftpd/vsftpd2.conf

[root@study system]# netstat -tlnp 
Active Internet connections (only servers)
Proto Recv-Q Send-Q Local Address  Foreign Address   State    PID/Program name
tcp        0      0 0.0.0.0:22     0.0.0.0:*         LISTEN   1340/sshd
tcp        0      0 127.0.0.1:25   0.0.0.0:*         LISTEN   2387/master
tcp6       0      0 :::555         :::*              LISTEN   12672/vsftpd
tcp6       0      0 :::21          :::*              LISTEN   12670/vsftpd
tcp6       0      0 :::22          :::*              LISTEN   1340/sshd
tcp6       0      0 ::1:25         :::*              LISTEN   2387/master
```

### 17.3.4 多重的重复设置方式: 以 getty 为例

`/usr/lib/systemd/system/getty@.service`: `@` 会变为内容中的 `%I` 变量，例如 `tty1`

```sh
[root@study ~]# cat /usr/lib/systemd/system/getty@.service
[Unit]
Description=Getty on %I
Documentation=man:agetty(8) man:systemd-getty-generator(8)
Documentation=http://0pointer.de/blog/projects/serial-console.html
After=systemd-user-sessions.service plymouth-quit-wait.service
After=rc-local.service
Before=getty.target
ConditionPathExists=/dev/tty0

[Service]
ExecStart=-/sbin/agetty --noclear %I $TERM
Type=idle
Restart=always
RestartSec=0
UtmpIdentifier=%I
TTYPath=/dev/%I
TTYReset=yes
TTYVHangup=yes
TTYVTDisallocate=yes
KillMode=process
IgnoreSIGPIPE=no
SendSIGHUP=yes

[Install]
WantedBy=getty.target
```

```sh
[root@study ~]# systemctl show getty.target
# 那個 show 的指令可以將 getty.target 的預設設定值也取出來顯示！
Names=getty.target
Wants=getty@tty1.service
WantedBy=multi-user.target
Conflicts=shutdown.target
Before=multi-user.target
After=getty@tty1.service getty@tty2.service getty@tty3.service getty@tty4.service
  getty@tty6.service getty@tty5.service
  .....
```

将 tty 数量由 6 降到 4：

```sh
# 1. 修改預設的 logind.conf 內容，將原本 6 個虛擬終端機改成 4 個
[root@study ~]# vim /etc/systemd/logind.conf
[Login]
NAutoVTs=4
ReserveVT=0
# 原本是 6 個而且還註解，請取消註解，然後改成 4 吧！

# 2. 關閉不小心啟動的 tty5, tty6 並重新啟動 getty.target 囉！
[root@study ~]# systemctl stop getty@tty5.service
[root@study ~]# systemctl stop getty@tty6.service
[root@study ~]# systemctl restart systemd-logind.service

# 启动 tty8
[root@study ~]# systemctl start getty@tty8.service
```

### 17.3.5 自己的服务自己做

```sh
[root@study ~]# vim /backups/backup.sh
#!/bin/bash

source="/etc /home /root /var/lib /var/spool/{cron,at,mail}"
target="/backups/backup-system-$(date +%Y-%m-%d).tar.gz"
[ ! -d /backups ] && mkdir /backups
tar -zcvf ${target} ${source} &> /backups/backup.log

[root@study ~]# chmod a+x /backups/backup.sh
[root@study ~]# ll /backups/backup.sh
-rwxr-xr-x. 1 root root 220 Aug 13 01:57 /backups/backup.sh
# 記得要有可執行的權限才可以喔！
```

制作一个 `backup.service`：

```sh
[root@study ~]# vim /etc/systemd/system/backup.service
[Unit]
Description=backup my server
Requires=atd.service

[Service]
Type=simple
ExecStart=/bin/bash -c " echo /backups/backup.sh | at now"

[Install]
WantedBy=multi-user.target
# 因為 ExecStart 裡面有用到 at 這個指令，因此， atd.service 就是一定要的服務！

[root@study ~]# systemctl daemon-reload
[root@study ~]# systemctl start backup.service
[root@study ~]# systemctl status backup.service
backup.service - backup my server
   Loaded: loaded (/etc/systemd/system/backup.service; disabled)
   Active: inactive (dead)

Aug 13 07:50:31 study.centos.vbird systemd[1]: Starting backup my server...
Aug 13 07:50:31 study.centos.vbird bash[20490]: job 8 at Thu Aug 13 07:50:00 2015
Aug 13 07:50:31 study.centos.vbird systemd[1]: Started backup my server.
# 為什麼 Active 是 inactive 呢？這是因為我們的服務僅是一個簡單的 script 啊！
# 因此執行完畢就完畢了，不會繼續存在記憶體中喔！
```

## 17.4 systemctl 针对 timer 的配置文件

- systemd.timer 的优点
  - systemd 服务都有 log，debug 更方便
  - 各个 timer 工作可以跟 systemd 服务相结合
  - 各个 timer 的工作可以跟 control group 相结合
  - 时间上可以精确到毫秒

## 17.5 CentOS 7.x 默认启动的服务简易说明

## 17.6 重点回顾

## 17.7 本章习题

## 17.8 参考资料与延伸阅读
