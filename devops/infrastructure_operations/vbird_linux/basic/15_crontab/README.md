# 第十五章 例行性工作调度（crontab）

> <https://linux.vbird.org/linux_basic/centos7/0430cron.php>

## 目录

- [第十五章 例行性工作调度（crontab）](#第十五章-例行性工作调度crontab)
  - [目录](#目录)
  - [15.1 什么是例行性工作调度](#151-什么是例行性工作调度)
    - [15.1.1 Linux 工作调度的种类：at, cron](#1511-linux-工作调度的种类at-cron)
    - [15.1.2 CentOS Linux 系统上常见的例行性工作](#1512-centos-linux-系统上常见的例行性工作)
  - [15.2 仅执行一次的工作调度](#152-仅执行一次的工作调度)

## 15.1 什么是例行性工作调度

### 15.1.1 Linux 工作调度的种类：at, cron

- `at`: 可以处理仅执行一次的就结束调度的命令，需要 `atd` 服务支持。
- `crontab`: 会一直循环的调度命令，需要 `crond` 服务支持。

### 15.1.2 CentOS Linux 系统上常见的例行性工作

- 日志文件的轮替 (logrotate)
- 日志文件分析的任务 (logwatch)
- 更新 locate 数据库 (updatedb)
- 更新 man page 数据库 (mandb)
- RPM 软件数据库的更新
- 移除暂存文件 (tmpwatch)
- 与网络服务有关的分析

## 15.2 仅执行一次的工作调度

>>>>> progress
