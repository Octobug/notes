# 第十六章 进程管理与 SELinux 初探

> <https://linux.vbird.org/linux_basic/centos7/0440processcontrol.php>

## 目录

- [第十六章 进程管理与 SELinux 初探](#第十六章-进程管理与-selinux-初探)
  - [目录](#目录)
  - [16.1 什么是进程（process）](#161-什么是进程process)
    - [16.1.1 进程与程序（process & program）](#1611-进程与程序process--program)
    - [16.1.2 Linux 的多用户多任务环境](#1612-linux-的多用户多任务环境)
  - [16.2 工作管理（job control）](#162-工作管理job-control)
    - [16.2.1 什么是工作管理？](#1621-什么是工作管理)
    - [16.2.2 job control 的管理](#1622-job-control-的管理)
    - [16.2.3 离线管理问题](#1623-离线管理问题)
    - [16.2.x screen](#162x-screen)
  - [16.3 进程管理](#163-进程管理)

## 16.1 什么是进程（process）

在 Linux 中，系统会在运行进程时，为其分配一个 ID，称为 PID。
同时根据启动这个进程的用户与相关属性关系，为这个进程分配相应的权限。

### 16.1.1 进程与程序（process & program）

- 程序（program）：通常为 binary 程序，为实体文件。
- 进程（process）：程序被执行后，执行者的权限与属性、程序本身、所需数据都会被载入内存中，
  操作系统会为进程分配 PID 及其相关资源。
  - 子进程与父进程：每个子进程都会有 PPID (Parent PID) ，可用 `ps -l` 查看。
- `fork` 与 `exec`：进程调用的流程，父进程 fork（复制）一个一样的子进程，再以 exec
  的方式执行子进程。
- 系统或网络服务：常驻在内存的进程（daemon），这类命令名称通常以 "d" 结尾，如 httpd, sshd

### 16.1.2 Linux 的多用户多任务环境

- 多人环境
- 多任务（进程）行为
- 多重登录环境的七个基本终端窗口：6 个文字界面登录窗口 + 1 个图像界面
- bash 环境下的工作管理（job control）
  - `&`: 背景执行
- 多用户多任务的系统资源分配问题

## 16.2 工作管理（job control）

job control: bash 环境下的工作管理。

### 16.2.1 什么是工作管理？

bash 的 job control：

- 触发的新进程来自于 shell 的子进程
- 前景（foreground）：可以控制与下达命令的环境称为前景工作
- 背景（backgroup）：可以自行运行的工作，使用 bg/fg 管理，这里的背景是指 bash 实例的背景
- 在背景中执行的进程不能等待 terminal/shell 的输入

### 16.2.2 job control 的管理

bash 实例只能管理自己的工作而不能管理其他 bash 实例的工作。工作分前景与背景，
背景的工作状态又分暂停（stopped）与运行中（running）。

- 直接将命令放到背景中执行：`&`
- 将当前工作放到背景中“暂停”：`[ctrl]+z`
- 观察目前的背景工作状态：`jobs [-lrs]`
  - `-l`: 列出 job number, PID, 命令等信息
  - `-r`: 列出背景中 running 的工作
  - `-s`: 列出背景中 stopped/suspended 的工作
  - 列出结果的第二列
    - `-`: 代表 `+` 下一个被取用的工作
    - `+`: fg 默认取用的工作
- 将背景工作切换到前景处理：`fg [%JOBNUMBER]`
  - `fg -`: 将 `-` 标记的工作取到前景
- 让背景工作变成运行中：`bg [%JOBNUMBER]`
- 管理背景工作：`kill`
  - `kill -signal %jobnumber`
    - `signal`: 数字, SIGNAME, NAME 均可
      - `1`: `SIGHUP`
      - `2`: `SIGINT`，相当于 `[ctrl]+c`
      - `9`: `SIGKILL`，强制终止进程
      - `15`: `SIGTERM`，kill 的默认值，以正常的方式终止一项工作。
        通常程序接收到该信号会执行正常的退出流程。
  - `kill -l`
    - `-l`: 列出 kill 能使用的信号

### 16.2.3 离线管理问题

背景工作在用户离开 bash 之后会被终止。如果需要在用户离开时扔保留进程，可以使用 `nohup`。

- 在 terminal 背景工作：`nohup [命令与参数] &`
- nohup 不支持 bash 的内置命令，需要使用 bash命令时，可以 `/bin/bash -c "SCRIPT"`

### 16.2.x screen

`screen` 终端管理器，终端多路复用器，它可以管理多个虚拟终端。与 bash 的 job control
不一样。

- `screen -dmS NAME COMMAND`

## 16.3 进程管理

>>>>> progress
