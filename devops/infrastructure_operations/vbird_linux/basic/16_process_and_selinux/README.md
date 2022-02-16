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
    - [16.3.1 进程的观察](#1631-进程的观察)
    - [16.3.2 进程的管理](#1632-进程的管理)
    - [16.3.3 关于进程的执行顺序](#1633-关于进程的执行顺序)
    - [16.3.4 系统资源的观察](#1634-系统资源的观察)
  - [16.4 特殊文件与程序](#164-特殊文件与程序)
    - [16.4.1 具有 SUID/SGID 权限的命令执行状态](#1641-具有-suidsgid-权限的命令执行状态)
    - [16.4.2 /proc/* 代表的意义](#1642-proc-代表的意义)
    - [16.4.3 查询已打开的文件](#1643-查询已打开的文件)
  - [16.5 SELinux 初探](#165-selinux-初探)
    - [16.5.1 什么是 SELinux](#1651-什么是-selinux)
    - [16.5.2 SELinux 的运行模式](#1652-selinux-的运行模式)
    - [16.5.3 SELinux 三种模式的启动、关闭与观察](#1653-selinux-三种模式的启动关闭与观察)
    - [16.5.4 SELinux 政策内的规则管理](#1654-selinux-政策内的规则管理)
    - [16.5.5 SELinux 安全性上下文的修改](#1655-selinux-安全性上下文的修改)
    - [16.5.6 一个网络服务案例及登录文件协助](#1656-一个网络服务案例及登录文件协助)
  - [16.6 重点回顾](#166-重点回顾)
  - [16.7 本章习题](#167-本章习题)
  - [16.8 参考资料与延伸阅读](#168-参考资料与延伸阅读)

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
      - `19`: `SIGSTOP`，相当于 `[ctrl]+z`
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

### 16.3.1 进程的观察

`ps` 命令：获取某个时间点的进程信息

- `ps -l`
  - `F`: 进程标志（process flags），表明进程的权限和
    - 0: 无
    - 1: 该子进程只进行 fork 而还没 exec
    - 4: 该进程的权限为 root
    - 5: 1 + 4
  - `S`: 进程状态码（state codes）
    - D: uninterruptible sleep (usually IO)
    - R: running or runnable (on run queue)
    - S: interruptible sleep (waiting for an event to complete)
    - T: stopped by job control signal
    - t: stopped by debugger during the tracing
    - W: paging (not valid since the 2.6.xx kernel)
    - X: dead (should never be seen)
    - Z: defunct ("zombie") process, terminated but not reaped by its parent
  - 输出信息
    - UID/PID/PPID
    - C: CPU 使用率 (%)
    - PRI/NI: Priority/Nice，代表此进程被 CPU 执行的优先级，数值越小代表优先级越高
    - ADDR/SZ/WCHAN
      - ADDR: 该进程在内存的哪个部分，running 的进程一般显示 "-"
      - SZ: 该进程使用的内存量
      - WCHAN: 进程黄台，"-" 表示 running
    - TTY: 用户的终端机接口，远程登录为用户为动态终端接口（pts/n）
    - TIME: 实际使用的 CPU 时间
    - CMD: 启动此进程的具体命令
- `ps aux`
  - USER: 所属用户
  - PID: 进程 ID
  - %CPU: CPU 使用率
  - %MEM: 内存使用率
  - VSZ: 虚拟内存使用量（KBytes）
  - RSS: 物理内存使用率（KBytes）
  - TTY: 进程在哪个终端机运行，如果和终端机无关则显示 `?`
    - tty1-tty6 表示本机登录的用户进程
    - pts/n 表示远程登录的用户进程
  - STAT: 进程状态
  - START: 进程的启动时间
  - TIME: 实际使用的 CPU 时间
  - COMMAND: 启用此进程的具体命令
- 僵尸进程 `Z`: 进程终止，但父进程没有回收子进程，没有释放子进程占用的资源
  （PID，退出状态，运行时间等，不包含内存、文件描述符等资源）。
  可以通过 kill 父进程使僵尸进程被 systemd 接管，systemd 会清理僵尸进程。如果连 systemd
  都清除不了，就只能 reboot。

`top` 命令：动态观察进程的变化

- `top [-d NUM] | [-bnp]`
  - `-d`: 每 NUM 秒更新一次
  - `-b`: batch 模式，top 会以追加的形式输出信息，而不是“刷新”，并且会输出所有进程的信息
  - `-n`: 指定获取进程信息的次数
  - `-p`: 指定 PID
  - 按键命令
    - `?/h`: 显示 top 支持的按键命令
      - k: 给某个 PID 发送信号
      - r: 给某个 PID 定制一个 nice 值（优先级）
      - q: 退出
    - 兼容的旧版按键，用于排序
      - A: START TIME
      - M: %MEM
      - N: PID
      - P: %CPU
      - T: TIME+
- 输出信息
  - 第一行: `top - 08:53:54 up  4:49,  1 user,  load average: 0.00, 0.00, 0.00`
    - 当前时间与系统已启动时长
    - 登录人数
    - 平均负载: 1, 5, 15 (min)
  - 第二行: `Tasks: 90 total,   1 running,  46 sleeping,   0 stopped,   0 zombie`
  - 第三行: `%Cpu(s): 0.0 us,0.0 sy,0.0 ni,99.7 id,0.0 wa,0.0 hi,0.3 si,0.0 st`
    - us, user    : time running un-niced user processes
    - sy, system  : time running kernel processes
    - ni, nice    : time running niced user processes
    - id, idle    : time spent in the kernel idle handler
    - wa, IO-wait : time waiting for I/O completion
    - hi : time spent servicing hardware interrupts
    - si : time spent servicing software interrupts
    - st : time stolen from this vm by the hypervisor
  - 第四行: `KiB Mem: 1008712 total, 556152 free, 103384 used, 349176 buff/cache`
  - 第五行: `KiB Swap: 2017276 total, 2017276 free, 0 used. 747100 avail Mem`
  - 第六行: top 的命令输入状态
  - 进程信息列表
    - PID
    - USER
    - PR: Priority value
    - NI: Nice value
    - %CPU: CPU 使用率
    - %MEM: 内存使用率
    - TIME+: 实际使用的 CPU 时间

`pstree` 命令：进程树信息

- `pstree [-AU] [-up]`
  - `-A`: 树形使用 ASCII 字符显示
  - `-U`: 树形使用 Unicode 字符显示
  - `-p`: 列出每个进程的 PID
  - `-u`: 列出每个进程所属用户

### 16.3.2 进程的管理

- `kill -signal PID`
- `killall -signal COMMAND_NAME`

### 16.3.3 关于进程的执行顺序

- Priority 与 Nice
  - 关系: Priority (old) = Priority (old) + nice
  - Priority: 由系统管理，不能直接修改。可通过 `chrt` 间接修改
  - Nice
    - 用户可调整
      - `nice`: 运行时指定
      - `renice`: 调整进程 Nice 值
    - 取值范围
      - root 为 `-20~19`
      - 普通用户为 `0~19`，且只能调为比原来高的值

### 16.3.4 系统资源的观察

- `free`: 观察内存使用情况
  - `shared`: 主要被 tmpfs 使用
  - `buffer/cached`: 缓冲区或缓存占用的内存，可被释放而继续使用
- `uname`: 查询系统与内核相关信息
- `uptime`: 获取系统启动时间与工作负载
- `dmesg`: 分析内核产生的信息

netstat 命令：

- `netstat [-alnptu]`: 观察网络使用情况
  - `-a`: 列出所有连接、监听、socket 信息
  - `-l`: 列出所有监听的服务
  - `-n`: 以端口号显示
  - `-p`: 列出 PID
  - `-t`: 只列出 TCP
  - `-u`: 只列出 UDP
- 输出信息
  - Proto: 协议
  - Recv-Q: 接收的且未被进程取用的数据 Bytes 数
  - Send-Q: 发送的且未被远程接收的数据 Bytes 数
  - Local Address: 本地 IP:Port
  - Foreign Address: 远端 IP:Port
  - State: 状态

vmstat 命令：

```sh
[root@study ~]# vmstat [-a] [延遲 [總計偵測次數]] <==CPU/記憶體等資訊
[root@study ~]# vmstat [-fs]                      <==記憶體相關
[root@study ~]# vmstat [-S 單位]                  <==設定顯示數據的單位
[root@study ~]# vmstat [-d]                       <==與磁碟有關
[root@study ~]# vmstat [-p 分割槽]                <==與磁碟有關
選項與參數：
-a  ：使用 inactive/active(活躍與否) 取代 buffer/cache 的記憶體輸出資訊；
-f  ：開機到目前為止，系統複製 (fork) 的程序數；
-s  ：將一些事件 (開機至目前為止) 導致的記憶體變化情況列表說明；
-S  ：後面可以接單位，讓顯示的資料有單位。例如 K/M 取代 bytes 的容量；
-d  ：列出磁碟的讀寫總量統計表
-p  ：後面列出分割槽，可顯示該分割槽的讀寫總量統計表

範例一：統計目前主機 CPU 狀態，每秒一次，共計三次！
[root@study ~]# vmstat 1 3
procs --------memory--------- ---swap-- -----io---- -system-- ------cpu-----
 r  b   swpd    free   buff  cache   si   so    bi    bo   in   cs us sy id wa st
 1  0   0 1838092   1504 722216    0    0     4     1    6    9  0  0 100  0  0
 0  0   0 1838092   1504 722200    0    0     0     0   13   23  0  0 100  0  0
 0  0   0 1838092   1504 722200    0    0     0     0   25   46  0  0 100  0  0
```

- 程序欄位 (procs) 的項目分別為：
  - r ：等待運作中的程序數量；
  - b：不可被喚醒的程序數量。這兩個項目越多，代表系統越忙碌
     (因為系統太忙，所以很多程序就無法被執行或一直在等待而無法被喚醒之故)。
- 記憶體欄位 (memory) 項目分別為：
  - swpd：虛擬記憶體被使用的容量；
  - free：未被使用的記憶體容量；
  - buff：用於緩衝記憶體；
  - cache：用於快取記憶體。
- 記憶體置換空間 (swap) 的項目分別為：
  - si：由磁碟中將程序取出的量；
  - so：由於記憶體不足而將沒用到的程序寫入到磁碟的 swap 的容量。
    如果 si/so 的數值太大，表示記憶體內的資料常常得在磁碟與主記憶體之間傳來傳去，
    系統效能會很差！
- 磁碟讀寫 (io) 的項目分別為：
  - bi：由磁碟讀入的區塊數量；
  - bo：寫入到磁碟去的區塊數量。如果這部份的值越高，代表系統的 I/O 非常忙碌！
- 系統 (system) 的項目分別為：
  - in：每秒被中斷的程序次數；
  - cs：每秒鐘進行的事件切換次數；這兩個數值越大，代表系統與周邊設備的溝通非常頻繁！
    這些周邊設備當然包括磁碟、網路卡、時間鐘等。
- CPU 的項目分別為：
  - us：非核心層的 CPU 使用狀態；
  - sy：核心層所使用的 CPU 狀態；
  - id：閒置的狀態；
  - wa：等待 I/O 所耗費的 CPU 狀態；
  - st：被虛擬機器 (virtual machine) 所盜用的 CPU 使用狀態 (2.6.11 以後才支援)。

## 16.4 特殊文件与程序

### 16.4.1 具有 SUID/SGID 权限的命令执行状态

- SUID 權限僅對二進位程式(binary program)有效；
- 執行者對於該程式需要具有 x 的可執行權限；
- 本權限僅在執行該程式的過程中有效 (run-time)；
- 執行者將具有該程式擁有者 (owner) 的權限。

### 16.4.2 /proc/* 代表的意义

`/proc` 文件系统由内核创建，存在于内存中。`/proc/{PID}` 为每个进程的目录。
其中有两个值得注意的文件：

- cmdline: 启动进程的命令
- environ: 进程的环境变量

系统相关信息：

| 文件名              | 内容                               |
| ------------------- | ---------------------------------- |
| `/proc/cmdline`     | 加载 kernel 使用的命令与参数       |
| `/proc/cpuinfo`     | 本机的 CPU 信息                    |
| `/proc/devices`     | 系统设备名命名与代号信息           |
| `/proc/filesystems` | 系统已加载的文件系统               |
| `/proc/interrupts`  | 系统的 IRQ 分配状态                |
| `/proc/ioports`     | 系统各个设备配置的 I/O 地址        |
| `/proc/kcore`       | 系统可用内存 (64位系统最大有 128T) |
| `/proc/loadavg`     | 系统负载信息 (uptime)              |
| `/proc/meminfo`     | 内存信息 (free)                    |
| `/proc/modules`     | 系统已加载的模块                   |
| `/proc/mounts`      | 系统的挂载信息                     |
| `/proc/swaps`       | 系统虚拟内存使用信息               |
| `/proc/partitions`  | 系统分区信息 (fdisk -l)            |
| `/proc/uptime`      | 已开机时间 (uptime)                |
| `/proc/version`     | 内核版本 (uname -a)                |
| `/proc/bus/*`       | 一些总线设备                       |

### 16.4.3 查询已打开的文件

- `fuser [-muv] [-k [i] [-signal]] FILE/DIR`: 找出使用指定文件的进程
  - `-m`: 列出使用某个文件系统或块设备的所有进程
  - `-u`: 列出进程用户
  - `-v`: 列出更详细的信息
  - `-k`: 列出使用指定文件/目录的 PID 并发送 SIGKILL 信号
  - `-i`: 发送信号前询问用户
  - `-signal`: 指定具体信号
- `lsof [-aUu] [+d]`: 列出被进程打开的文件
  - `-a`: 条件与
  - `-U`: 列出 Unix domain socket
  - `-u`: 列出特定用户打开的文件
  - `+d`: 列出某个目录下已被打开的文件
- `pidof [-sx] PROGRAM`: 按程序名查找 PID

## 16.5 SELinux 初探

### 16.5.1 什么是 SELinux

SELinux: Security Enhanced Linux

- 最开始的设计目标：避免资源误用。
- 传统的文件权限与账号关系：DAC (Discretionary Access Control)，自主访问控制，
  即 ugo + rwx 的访问控制。
- 以规则限制特定程序访问特定文件：MAC (Mandatory Access Control)，强制访问控制。
  管控主体为“程序”而不是“用户”。

**DAC 与 MAC 对比**：

![DAC/MAC](images/16_5_1_dac_mac.jpg)

### 16.5.2 SELinux 的运行模式

SELinux 采用 MAC 模式。

- Subject: 主体，SELinux 管控的主体是程序
- Object: 目标，主体能否访问目标资源（文件系统）
- Policy: 政策，政策内会细化为规则（Rule）来限制不同服务对不同资源的访问。
  CentOS 提供的主要三种政策：
  - targeted: 主要针对网络服务限制，对本地限制较少，是默认政策；
  - minimum: 仅保护少数选择的程序；
  - mls: 完整的 SELinux 限制，较为严格。
- Security Context: 安全上下文，主体访问资源除了满足政策，还要满足上下文。
  - Identify: 身份识别
    - unconfined_u: 不受限的用户，该文件来是不受限的程序产生的
    - system_u: 系统用户，该文件是系统产生的
  - Role: 角色
    - object_r: 代表文件或目录等文件资源
    - system_r: 代表程序
  - Type: 类型
    - 在 Subject 上称为域 (domain)
    - 在 Object 上称为类型 (type)

观察程序的 SELinux 信息：`ps -eZ`，targeted 政策下的身份角色意义：

| 身份识别     | 角色         | 在 targeted 中的意义             |
| ------------ | ------------ | -------------------------------- |
| unconfined_u | unconfined_r | 一般登录用户的程序，限制较为宽松 |
| system_u     | system_r     | 系统账号                         |

### 16.5.3 SELinux 三种模式的启动、关闭与观察

- enforcing: 强制模式，代表 SELinux 运行中，且已经开始限制 domain/type
- permissive: 宽容模式，代表 SELinux 运行中，但只会有相应的警告
- disabled: 关闭，SELinux 没有实际运行

相关命令：

- `getenforce`: 获取目前的 SELinux 状态
- `sestatus`: 获取 SELinux  政策
  - `/etc/sestatus.conf`: Security Context 配置
  - `/etc/selinux/config`: SELinux 配置
- SELinux 的启动与关闭（需要 reboot 生效）
- enforcing 与 permissive 切换（不需要 reboot）
  - setenforce 0: permissive
  - setenforce 1: enforcing

### 16.5.4 SELinux 政策内的规则管理

- SELinux 各个规则的布尔值查询 `getsebool`
- SELinux 各个规则的主体程序能够读取的文件 SELinux type 查询 seinfo, sesearch
- 修改 SELinux 规则的布尔值 setsebool

### 16.5.5 SELinux 安全性上下文的修改

- 使用 chcon 手动修改文件的 SELinux type
- 使用 restorecon 让文件恢复正确的 SELinux type
- semanage 默认目录的安全性上下文查询与修改

### 16.5.6 一个网络服务案例及登录文件协助

- setrobleshoot --> 错误讯息写入 /var/log/messages
- 实例说明：通过 vsftpd 这个 FTP 服务器来存取系统上的文件
- 匿名者无法下载
- 无法从主文件夹下载文件的问题分析与解决
- 一般用户从非正规目录上传/下载文件
- 无法变更 FTP 服务端口问题分析与解决

## 16.6 重点回顾

## 16.7 本章习题

## 16.8 参考资料与延伸阅读
