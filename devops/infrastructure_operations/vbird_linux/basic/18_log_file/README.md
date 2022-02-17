# 第十八章 认识与分析日志文件

> <https://linux.vbird.org/linux_basic/centos7/0570syslog.php>

## 目录

- [第十八章 认识与分析日志文件](#第十八章-认识与分析日志文件)
  - [目录](#目录)
  - [18.1 什么是日志文件](#181-什么是日志文件)
    - [18.1.1 CentOS 7 日志文件建议说明](#1811-centos-7-日志文件建议说明)
    - [18.1.2 日志文件内容的一般格式](#1812-日志文件内容的一般格式)
  - [18.2 rsyslog.service: 记录日志文件的服务](#182-rsyslogservice-记录日志文件的服务)
    - [18.2.1 rsyslog.service 的配置文件: /etc/rsyslog.conf](#1821-rsyslogservice-的配置文件-etcrsyslogconf)
    - [18.2.2 日志文件的安全性设置](#1822-日志文件的安全性设置)
    - [18.2.3 日志文件服务器的设置](#1823-日志文件服务器的设置)
  - [18.3 日志文件的轮替 (logrotate)](#183-日志文件的轮替-logrotate)
    - [18.3.1 logrotate 的配置文件](#1831-logrotate-的配置文件)
    - [18.3.2 实际测试 logrotate 动作](#1832-实际测试-logrotate-动作)
    - [18.3.3 自定义登录文件的轮替功能](#1833-自定义登录文件的轮替功能)
  - [18.4 systemd-journald.service 简介](#184-systemd-journaldservice-简介)
    - [18.4.1 使用 journalctl 查看日志信息](#1841-使用-journalctl-查看日志信息)
    - [18.4.2 logger 命令的应用](#1842-logger-命令的应用)
    - [18.4.3 保存 journal 的方式](#1843-保存-journal-的方式)
  - [18.5 分析日志文件](#185-分析日志文件)
    - [18.5.1 CentOS 默认提供的 logwatch](#1851-centos-默认提供的-logwatch)
    - [18.5.2 鸟哥自己写的日志文件分析工具](#1852-鸟哥自己写的日志文件分析工具)
  - [18.6 重点回顾](#186-重点回顾)
  - [18.7 本章习题](#187-本章习题)
  - [18.8 参考资料与延伸阅读](#188-参考资料与延伸阅读)

## 18.1 什么是日志文件

### 18.1.1 CentOS 7 日志文件建议说明

- 日志文件的重要性
  - 解决系统方面的错误
  - 解决网络服务的问题
  - 过往时间记录簿  
- Linux 常见的日志文件：通常只有 root 能访问
  - `/var/log/boot.log`: 只会有本次开机的 log
  - `/var/log/cron`: crontab 的 log
  - `/var/log/dmesg`: 系统开机时内核检测的各项信息
  - `/var/log/lastlog`: 系统所有账号最近一次登录的相关信息 (`lastlog`)
  - `/var/log/maillog` 或 `/var/log/mail/*`: 邮件往来信息
  - `/var/log/messages`: 系统发生的错误信息
  - `/var/log/secure`: 涉及账号密码的软件登录记录
  - `/var/log/wtmp`, `/var/log/faillog`: 登录系统成功/失败的信息 (`last`)
  - `/var/log/httpd/`, `/var/log/samba/`: 其他网络服务各自的日志
- 日志文件所需相关服务 (daemon) 与程序
  - `systemd-journald.service`: 信息接收者
  - `rsyslog.service`: 统一管理系统日志
  - `logrotate`: 日志文件轮替
- CentOS 使用 systemd 提供的 journalctl 管理

### 18.1.2 日志文件内容的一般格式

- 日期时间
- 主机名称
- 服务名称、命令与函数名称
- 信息实际内容

## 18.2 rsyslog.service: 记录日志文件的服务

### 18.2.1 rsyslog.service 的配置文件: /etc/rsyslog.conf

这个配置文件规定了：

1. 什么服务
2. 什么登记的信息
3. 记录在什么地方

格式：

```conf
服务名称.[=!]信息等级   信息记录的文件名或设备或主机
# 以 mail 服务产生的 info 等级日志为例：
mail.info   /var/log/maillog_info
```

- 服务名称：rsyslogd 依据 syslog 规范识别服务

  | 序号  | 服务                        | 说明                                 |
  | ----- | --------------------------- | ------------------------------------ |
  | 0     | kern(kernel)                | kernel 相关日志                      |
  | 1     | user                        | 用户级别相关                         |
  | 2     | mail                        | 与邮件相关日志                       |
  | 3     | daemon                      | 系统服务相关日志                     |
  | 4     | auth                        | 与认证授权相关的日志                 |
  | 5     | syslog                      | syslog 协议的日志，也就是 rsyslogd   |
  | 6     | lpr                         | 打印相关的日志                       |
  | 7     | news                        | 与新闻群组服务器相关                 |
  | 8     | uucp                        | Unix to Unix Copy Protocol 的日志    |
  | 9     | cron                        | crontab 的日志                       |
  | 10    | authpriv                    | 与 auth 类似，记录更多信息，包括 pam |
  | 11    | ftp                         | FTP 协议相关日志                     |
  | 16-23 | local0-7 保留给本机用户使用 |

- 信息等级

  | 数值 | 名称         | 说明               |
  | ---- | ------------ | ------------------ |
  | 7    | debug        | debug 信息         |
  | 6    | info         | 基本信息           |
  | 5    | notice       | 值得注意的正常信息 |
  | 4    | warn         | 警告信息           |
  | 3    | error        | 重大错误信息       |
  | 2    | critical     | 严重错误信息       |
  | 1    | alert        | 警报信息           |
  | 0    | emerg(panic) | 紧急信息           |

  - 文件名符号 `[.=!]` 的意义:
    - `.`: 和后面一样及更严重的等级都记录
    - `.=`: 只记录和后面一样的等级
    - `.!`: 除了和后面一样等级的都记录

### 18.2.2 日志文件的安全性设置

- rsyslogd 的日志文件一经编辑就无法继续记录，此时需要重启 `rsyslog.service` 才行。
- `chattr +a /var/log/admin.log`: 使文件只能追加内容，而不能删除

### 18.2.3 日志文件服务器的设置

```sh
# 1. Server 端：修改 rsyslogd 的啟動設定檔，在 /etc/rsyslog.conf 內！
[root@study ~]# vim /etc/rsyslog.conf
# 找到底下這幾行：
# Provides UDP syslog reception
#$ModLoad imudp
#$UDPServerRun 514

# Provides TCP syslog reception
#$ModLoad imtcp
#$InputTCPServerRun 514
# 上面的是 UDP 埠口，底下的是 TCP 埠口！如果你的網路狀態很穩定，就用 UDP 即可。
# 不過，如果你想要讓資料比較穩定傳輸，那麼建議使用 TCP 囉！所以修改底下兩行即可！
$ModLoad imtcp
$InputTCPServerRun 514 

# 2. 重新啟動與觀察 rsyslogd 喔！
[root@study ~]# systemctl restart rsyslog.service
[root@study ~]# netstat -ltnp | grep syslog
Proto Recv-Q Send-Q Local Address  Foreign Address   State    PID/Program name
tcp        0      0 0.0.0.0:514    0.0.0.0:*         LISTEN   2145/rsyslogd
tcp6       0      0 :::514         :::*              LISTEN   2145/rsyslogd
# 嘿嘿！你的登錄檔主機已經設定妥當囉！很簡單吧！
```

```sh
# 3.客户端的设置
[root@study ~]# vim /etc/rsyslog.conf
*.*       @@192.168.1.100
#*.*       @192.168.1.100  # 若用 UDP 傳輸，設定要變這樣！

[root@study ~]# systemctl restart rsyslog.service
```

## 18.3 日志文件的轮替 (logrotate)

### 18.3.1 logrotate 的配置文件

- `/etc/logrotate.conf`
- `/etc/logrotate.d/`

```conf
/var/logs/*.log  {
    daily
    rotate 3650
    copytruncate
    olddir /backup/logs/history
    missingok
    dateext
    dateformat .%Y%m%d
    extension .log
    compress
    delaycompress
    notifempty
    prerotate
      /usr/bin/chattr -a /var/log/messages
    endscript
    postrotate
      /bin/kill -HUP `cat /var/run/syslogd.pid 2> /dev/null` 2> /dev/null || true
      /usr/bin/chattr +a /var/log/messages
    endscript
    sharedscripts # prerotate/postrotate 只会执行一次，否则会对每个 log 文件都执行一次
}
```

### 18.3.2 实际测试 logrotate 动作

- `logrotate [-dfv] LOGFILE`
  - `-d`: debug 模式，实际不会执行
  - `-f`: 强制进行一次 rotate
  - `-v`: verbose 模式

### 18.3.3 自定义登录文件的轮替功能

```sh
# 1. 先建立 +a 這個屬性啊！
[root@study ~]# chattr +a /var/log/admin.log
[root@study ~]# lsattr /var/log/admin.log
-----a---------- /var/log/admin.log
[root@study ~]# mv /var/log/admin.log /var/log/admin.log.1
mv: cannot move `/var/log/admin.log' to `/var/log/admin.log.1': Operation not permitted
# 這裡確定了加入 a 的隱藏屬性！所以 root 無法移動此登錄檔！

# 2. 開始建立 logrotate 的設定檔，增加一個檔案在 /etc/logrotate.d 內就對了！
[root@study ~]# vim /etc/logrotate.d/admin
# This configuration is from VBird 2015/08/19
/var/log/admin.log {
  monthly   <==每個月進行一次
  size=10M  <==檔案容量大於 10M 則開始處置
  rotate 5  <==保留五個！
  compress  <==進行壓縮工作！
  sharedscripts
  prerotate
          /usr/bin/chattr -a /var/log/admin.log
  endscript
  sharedscripts
  postrotate
    /bin/kill -HUP `cat /var/run/syslogd.pid 2> /dev/null` 2> /dev/null || true
    /usr/bin/chattr +a /var/log/admin.log
  endscript
}

# 3. 測試一下 logrotate 相關功能的資訊顯示：
[root@study ~]# logrotate -v /etc/logrotate.conf
....(前面省略)....
rotating pattern: /var/log/admin.log  10485760 bytes (5 rotations)
empty log files are rotated, old logs are removed
considering log /var/log/admin.log
  log does not need rotating
not running prerotate script, since no logs will be rotated
not running postrotate script, since no logs were rotated
....(底下省略)....
# 因為還不足一個月，檔案也沒有大於 10M，所以不需進行輪替！

# 4. 測試一下強制 logrotate 與相關功能的資訊顯示：
[root@study ~]# logrotate -vf /etc/logrotate.d/admin
reading config file /etc/logrotate.d/admin
reading config file /etc/logrotate.d/admin

Handling 1 logs

rotating pattern: /var/log/admin.log  forced from command line (5 rotations)
empty log files are rotated, old logs are removed
considering log /var/log/admin.log
  log needs rotating
rotating log /var/log/admin.log, log->rotateCount is 5
dateext suffix '-20150820'
glob pattern '-[0-9][0-9][0-9][0-9][0-9][0-9][0-9][0-9]'
renaming /var/log/admin.log.5.gz to /var/log/admin.log.6.gz
  (rotatecount 5, logstart 1, i 5),
old log /var/log/admin.log.5.gz does not exist
renaming /var/log/admin.log.4.gz to /var/log/admin.log.5.gz
  (rotatecount 5, logstart 1, i 4),
old log /var/log/admin.log.4.gz does not exist
renaming /var/log/admin.log.3.gz to /var/log/admin.log.4.gz
  (rotatecount 5, logstart 1, i 3),
old log /var/log/admin.log.3.gz does not exist
renaming /var/log/admin.log.2.gz to /var/log/admin.log.3.gz
  (rotatecount 5, logstart 1, i 2),
old log /var/log/admin.log.2.gz does not exist
renaming /var/log/admin.log.1.gz to /var/log/admin.log.2.gz
  (rotatecount 5, logstart 1, i 1),
old log /var/log/admin.log.1.gz does not exist
renaming /var/log/admin.log.0.gz to /var/log/admin.log.1.gz
  (rotatecount 5, logstart 1, i 0),
old log /var/log/admin.log.0.gz does not exist
log /var/log/admin.log.6.gz doesn't exist -- won't try to dispose of it
running prerotate script
fscreate context set to system_u:object_r:var_log_t:s0
renaming /var/log/admin.log to /var/log/admin.log.1
running postrotate script
compressing log with: /bin/gzip

[root@study ~]# lsattr /var/log/admin.log*
-----a---------- /var/log/admin.log
---------------- /var/log/admin.log.1.gz  <==有壓縮過喔！
```

## 18.4 systemd-journald.service 简介

开机过程的所有信息都会记录到 systemd-journald 里，它的日志只存储在内存中。

### 18.4.1 使用 journalctl 查看日志信息

- `journalctl`
  - `-n`: 显示最近几行
  - `-r`: 反向输出，从新到旧
  - `-p`: 日志级别
  - `-f`: follow

### 18.4.2 logger 命令的应用

- `logger [-p NAME.LEVEL]` "CONTENT"

```sh
[root@study ~]# vim /backups/backup.sh
#!/bin/bash

if [ "${1}" == "log" ]; then
        logger -p syslog.info "backup.sh is starting"
fi
source="/etc /home /root /var/lib /var/spool/{cron,at,mail}"
target="/backups/backup-system-$(date +%Y-%m-%d).tar.gz"
[ ! -d /backups ] && mkdir /backups
tar -zcvf ${target} ${source} &> /backups/backup.log
if [ "${1}" == "log" ]; then
        logger -p syslog.info "backup.sh is finished"
fi

[root@study ~]# /backups/backup.sh log
[root@study ~]# journalctl SYSLOG_FACILITY=5 -n 3
Aug 19 18:09:37 study.centos.vbird dmtsai[29850]: backup.sh is starting
Aug 19 18:09:54 study.centos.vbird dmtsai[29855]: backup.sh is finished
```

### 18.4.3 保存 journal 的方式

```sh
# 1. 先處理所需要的目錄與相關權限設定
[root@study ~]# mkdir /var/log/journal
[root@study ~]# chown root:systemd-journal /var/log/journal
[root@study ~]# chmod 2775 /var/log/journal

# 2. 重新啟動 systemd-journald 並且觀察備份的日誌資料！
[root@study ~]# systemctl restart systemd-journald.service
[root@study ~]# ll /var/log/journal/
drwxr-sr-x. 2 root systemd-journal 27 Aug 20 02:37 309eb890d09f440681f596543d95ec7a
```

## 18.5 分析日志文件

### 18.5.1 CentOS 默认提供的 logwatch

logwatch 每天会发送一封 email 给 root 用户

### 18.5.2 鸟哥自己写的日志文件分析工具

## 18.6 重点回顾

## 18.7 本章习题

## 18.8 参考资料与延伸阅读
