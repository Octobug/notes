# 第2章 基础技术

- [第2章 基础技术](#第2章-基础技术)
  - [2.1 Linux Namespace 介绍](#21-linux-namespace-介绍)
    - [2.1.1 概念](#211-概念)
    - [2.1.2 UTS Namespace](#212-uts-namespace)
    - [2.1.3 IPC Namespace](#213-ipc-namespace)
    - [2.1.4 PID Namespace](#214-pid-namespace)
    - [2.1.5 Mount Namespace](#215-mount-namespace)
    - [2.1.6 User Namespace](#216-user-namespace)
    - [2.1.7 Network Namespace](#217-network-namespace)
  - [2.2 Linux Cgroups 介绍](#22-linux-cgroups-介绍)
    - [2.2.1 什么是 Linux Cgroups](#221-什么是-linux-cgroups)
      - [Cgroups 中的 3 个组件](#cgroups-中的-3-个组件)
      - [三个组件相互的关系](#三个组件相互的关系)
      - [Kernel 接口](#kernel-接口)
    - [2.2.2 Docker 是如何使用 Cgroups 的](#222-docker-是如何使用-cgroups-的)

## 2.1 Linux Namespace 介绍

### 2.1.1 概念

💡 题外话：`chroot` 可以把当前目录变成“根目录”。

Linux Namespace 可以隔离一系列系统资源，从用户的角度来看，每一个命名空间都像一台单独的 Linux 计算机，有自己的 `init` 进程 (PID
`1`)，其他进程 PID 递增。

子 namespace 的进程映射到父 namespace 的进程上，父 namespace 可以知道每一个子 namespace
的运行状态。e.g. `PID 1` (child namespace) -> `PID 3` (parent namespace)。

| Namespace Type      | System Call Params | Kernel   |
| ------------------- | ------------------ | -------- |
| `Mount Namespace`   | `CLONE_NEWNS`      | `2.4.19` |
| `UTS Namespace`     | `CLONE_NEWUTS`     | `2.6.19` |
| `IPC Namespace`     | `CLONE_NEWIPC`     | `2.6.19` |
| `PID Namespace`     | `CLONE_NEWPID`     | `2.6.24` |
| `Network Namespace` | `CLONE_NEWNET`     | `2.6.29` |
| `User Namespace`    | `CLONE_NEWUSER`    | `3.8`    |

System Calls:

- `clone()`: 创建新进程，子进程会被包含进新的 namespace 中
- `unshare()`: 将进程移出某个 namespace
- `setns()`: 将进程加入某个 namespace

### 2.1.2 UTS Namespace

UTS (Unix Time Sharing) Namespace 用于隔离 `nodename` 和 `domainname` 两个系统标识。
在 UTS Namespace 中，每个 Namespace 允许有自己的 hostname。

```sh
$ sudo make run
$ pstree -pl
systemd(1)─┬─ModemManager(809)─┬─{ModemManager}(815)
           ├─sh(1407)───node(1411)─┬─node(1461)─┬─{node}(1466)
           │....................................................................
           │                       ├─node(1509)─┬─zsh(1541)
           │                       │            ├─zsh(2558)───sudo(2624)───sudo(2625)───make(2626)───go(2627)─┬─main(2678)─┬─sh(2683)───pstree(3037)

$ echo $$
2683

$ readlink /proc/2678/ns/uts
uts:[4026531838]

$ readlink /proc/2683/ns/uts
uts:[4026532245]

# changing child namespace hostname doesn't affect parent namespace
$ hostname -b bird
```

### 2.1.3 IPC Namespace

IPC (Inter-process Communication) Namespace 用于隔离

- System V IPC
- POSIX message queues

```sh
# on host
$ ipcs -q

$ ipcmk -Q
Message queue id: 0

$ ipcs -q 

------ Message Queues --------
key        msqid      owner      perms      used-bytes   messages    
0xbb598da5 0          shaobiaoli 644        0
```

### 2.1.4 PID Namespace

同样一个进程在不同的 PID Namespace 中有不同的 PID。

在 docker 容器中，使用 `ps -ef` 可以发现前台进程 PID 是 1，但是在容器外是不一样的 PID。

```sh
$ pstree -pl
...
node(2314)─┬─zsh(2522)───sudo(4920)───sudo(4921)───go(4922)─┬─main(4953)─┬─sh(4957)
```

```sh
sudo go run cmd/main.go
$ echo $$ 
1
```

这⾥还不能⽤ `ps` 来查看 PID，因为 `ps` 和 `top` 等命令都是使用 `/proc` 内容。

### 2.1.5 Mount Namespace

用于隔离进程看到的挂载点视图，这是 Linux 实现的第一种 Namespace。

`proc` 是一个文件系统，提供额外的机制通过内核及内核模块发送信息给进程。

```sh
$ sudo go run cmd/main.go 
$ ls /proc
# 当前 /proc 仍然是宿主机的信息
1     22    349   4922  5623        crypto         misc
1049  2214  35    4953  5625        devices        modules
1052  2243  37    4957  57          device-tree    mounts
1071  2247  372   5     58          diskstats      net
1079  225   373   50    6           driver         pagetypeinfo
12    226   38    5013  60          dynamic_debug  partitions
13    2288  39    506   611         execdomains    pressure
14    2299  4     507   662         fb             schedstat
15    23    40    51    667         filesystems    scsi
158   2314  41    5284  674         fs             self
16    2378  42    5291  677         interrupts     slabinfo
17    2380  43    5295  68          iomem          softirqs
18    2389  434   53    699         ioports        stat
184   24    44    5317  7           irq            swaps
19    2522  45    5328  70          kallsyms       sys
1943  26    452   534   719         kcore          sysrq-trigger
2     27    454   5340  74          keys           sysvipc
20    28    4542  54    782         key-users      thread-self
2075  294   4598  5412  9           kmsg           timer_list
2077  3     4599  5468  asound      kpagecgroup    tty
2080  30    46    5469  bootconfig  kpagecount     uptime
2082  31    4658  5513  buddyinfo   kpageflags     version
2084  317   47    553   bus         latency_stats  version_signature
21    319   48    5582  cgroups     loadavg        vmallocinfo
2193  32    49    5583  cmdline     locks          vmstat
2194  33    4920  5584  consoles    mdstat         zoneinfo
2196  34    4921  5619  cpuinfo     meminfo
```

将 `/proc` 挂载到子 namespace 中：

```sh
# -t proc: 指定挂载类型为 proc
# proc: 挂载来源，proc 是特殊关键字
# /proc: 挂载目标
$ mount -t proc proc /proc
ls /proc
1            diskstats      keys           mounts        sysrq-trigger
5            driver         key-users      net           sysvipc
asound       dynamic_debug  kmsg           pagetypeinfo  thread-self
bootconfig   execdomains    kpagecgroup    partitions    timer_list
buddyinfo    fb             kpagecount     pressure      tty
bus          filesystems    kpageflags     schedstat     uptime
cgroups      fs             latency_stats  scsi          version
cmdline      interrupts     loadavg        self          version_signature
consoles     iomem          locks          slabinfo      vmallocinfo
cpuinfo      ioports        mdstat         softirqs      vmstat
crypto       irq            meminfo        stat          zoneinfo
devices      kallsyms       misc           swaps
device-tree  kcore          modules        sys

$ ps -ef
UID          PID    PPID  C STIME TTY          TIME CMD
root           1       0  0 10:09 pts/9    00:00:00 sh
root           7       1  0 12:36 pts/9    00:00:00 ps -ef
```

### 2.1.6 User Namespace

隔离用户的用户组 ID。一个进程的 UID 和 GID 在 User Namespace 内外可以是不同的。
比较常用的是，在宿主机上以非 root 用户创建一个 User Namespace，然后在子 namespace 中映射为 root（Kernel 3.8 起）。

```sh
# host
$ whoami
root
$ id
uid=0(root) gid=0(root) groups=0(root)

$ sudo go run cmd/main.go
$ id
uid=65534(nobody) gid=65534(nogroup) groups=65534(nogroup)
```

### 2.1.7 Network Namespace

用于隔离网络设备、IP 地址、端口等网络栈。Network Namespace 可以让每个容器拥有自己独立虚拟的网络设备。

```sh
# host
$ ip addr
ip addr
1: lo: <LOOPBACK,UP,LOWER_UP> mtu 65536 qdisc noqueue state UNKNOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
    inet 127.0.0.1/8 scope host lo
       valid_lft forever preferred_lft forever
    inet6 ::1/128 scope host noprefixroute 
       valid_lft forever preferred_lft forever
2: ...

$ sudo go run cmd/main.go 
$ ip addr
1: lo: <LOOPBACK> mtu 65536 qdisc noop state DOWN group default qlen 1000
    link/loopback 00:00:00:00:00:00 brd 00:00:00:00:00:00
```

## 2.2 Linux Cgroups 介绍

### 2.2.1 什么是 Linux Cgroups

Linux Cgroups (Control Groups) 可以限制、记录和隔离进程组使用的物理资源（CPU、内存、存储、网络等）。

#### Cgroups 中的 3 个组件

- 一个 ***cgroup*** 包含一组进程，可以在特定 cgroup 上增加 Linux subsystem 的参数配置。
- ***subsystem*** 是一组资源控制的模块，包含
  - `blkio` 设置对块设备的访问控制
  - `cpu` 设置进程的 CPU 调度策略
  - `cpuacct` 统计进程的 CPU 占用
  - `cpuset` 多核机器上进程允许使用的 CPU 和内存（仅 NUMA 架构）
  - `devices` 设备访问控制
  - `freezer` 用于挂起（suspend）和恢复（resume）cgroup 中的进程
  - `memory` 设置进程的内存使用限制
  - `net_cls` 分类网络包，以便 Linux 的 tc (traffic controller) 根据 cgroup 分类做限流或监控
  - `net_prio` 设置进程的网络流量优先级
  - `ns` 使 cgroup 中的进程在新的 Namespace 中 fork 新进程 (NEWNS) 时，创建出一个新的 cgroup，这个 cgroup 包含新的 Namespace 中的进程
- ***hierarchy*** 把一组 cgroup 串成一个树状结构，一棵树就是一个 hierarchy。
  - 通过这样的树状结构，cgroups 可以实现继承。
    - 通过 cgroup1 限制定时任务的 CPU 使用率
    - 继承 cgroup 1，并通过 cgroup2 限制其中一个定时任务的磁盘 IO

可以用 `cgroup` 的命令行工具查看 Kernel 支持哪些 subsystem。

```sh
$ apt install cgroup-bin
$ lssubsys -a
lssubsys -a
cpuset
cpu
cpuacct
blkio
memory
devices
freezer
net_cls
perf_event
net_prio
hugetlb
pids
rdma
misc
```

#### 三个组件相互的关系

- 系统在创建新的 hierarchy 之后，系统中的所有进程都会加入这个 hierarchy 的 cgroup
  根节点（hierarchy 默认创建），后续创建的 cgroup 都是其子节点。
- 一个 subsystem 只能附加到一个 hierarchy 上。
- 一个 hierarchy 可以附加多个 subsystem。
- 一个进程可以作为多个 cgroup 的成员，但是这些 cgroup 必须在不同的 hierarchy 中。
- 一个进程 fork 出子进程时，子进程和父进程在同一个 cgroup 中，也可以根据需要将其移动到其他
  cgroup 中。

#### Kernel 接口

Kernel 为了使对 Cgroups 的配置更直观，提供了一个虚拟的树状文件系统来配置 Cgroups，通过层级的目录虚拟出 cgroup 树。

1, 创建并挂在挂载一个 hierarchy (cgroup tree)

```sh
# 创建一个 hierarchy 挂载点
$ mkdir cgroup-test

# 挂载一个名为 cgroup-test 的 hierarchy
$ sudo mount -t cgroup -o none,name=cgroup-test cgroup-test ./cgroup-test

$ ls ./cgroup-test
cgroup.clone_children  cgroup.procs  cgroup.sane_behavior  notify_on_release  release_agent  tasks
```

挂载后目录下生成了一些默认文件，这些文件就是这个 hierarchy 中 cgroup 根节点的配置项。

- `cgroup.clone_children`: cpuset 的 subsystem 会读取这个配置文件
  - `1`: 子 cgroup 才会继承父 cgroup 的 cpuset
- `cgroup.procs`: 当前节点 cgroup 中的进程 ID，根节点文件会有当前系统中所有进程组的 ID
- `cgroup.sane_behavior`: deprecated
- `notify_on_release/release_agent`
  - `notify_on_release`: 标识当前 cgroup 最后一个进程退出时是否执行了 `release_agent`
  - `release_agent`: 是一个路径，通常作为进程退出之后自动清理掉不再使用的 cgroup
- `tasks`: 标识该 cgroup 下的进程 ID，如果把一个进程 ID 写入这个文件，系统会把这个进程加入到当前 cgroup 中。

2, 在 hierarchy 上的 cgroup 根节点中创建扩展出的两个子 cgroup

```sh
# 创建子 cgroup-1
$ sudo mkdir cgroup-1

# 创建子 cgroup-2
$ sudo mkdir cgroup-2

$ tree
.
├── cgroup-1
│   ├── cgroup.clone_children
│   ├── cgroup.procs
│   ├── notify_on_release
│   └── tasks
├── cgroup-2
│   ├── cgroup.clone_children
│   ├── cgroup.procs
│   ├── notify_on_release
│   └── tasks
├── cgroup.clone_children
├── cgroup.procs
├── cgroup.sane_behavior
├── notify_on_release
├── release_agent
└── tasks
```

可以看到，在一个 cgroup 的目录下创建文件夹时，Kernel 会把文件夹标记为这个 cgroup 的子
cgroup，它们会继承父 cgroup 的属性。

3, 在 cgroup 中添加和移动进程

一个进程在一个 cgroups 的 hierarchy 中，只能在一个 cgroup 节点上存在，系统的所有进程默认存在根节点上，要将进程移动到其他 cgroup 节点，只需要将进程 ID 写到目的 cgroup 节点的 tasks
文件中。

```sh
$ cd cgroup-1
$ echo $$
1595

# 将所在终端进程移动到 cgroup-1 中
$ sudo sh -c "echo $$ >> tasks"
$ cat /proc/1595/cgroup
cat /proc/1595/cgroup
1:name=cgroup-test:/cgroup-1
0::/user.slice/user-1000.slice/session-4.scope
```

4, 通过 subsystem 限制 cgroup 中进程的资源

上面创建的 hierarchy 还没有关联到任何 subsystem，所以没办法通过那个 hierarchy 中的
cgroup 节点来限制资源。

系统默认会为每个 subsystem 创建一个 hierarchy。

```sh
$ ls /sys/fs/cgroup/user.slice | grep memory  
memory.current
memory.events
memory.events.local
memory.high
memory.low
memory.max
memory.min
memory.numa_stat
memory.oom.group
memory.peak
memory.pressure
memory.reclaim
memory.stat
memory.swap.current
memory.swap.events
memory.swap.high
memory.swap.max
memory.swap.peak
memory.zswap.current
memory.zswap.max
memory.zswap.writeback
```

使用 memory subsystem 限制进程内存示例：

```sh
# 启动一个占用内存的 stress 进程
$ stress --vm-bytes 200m --vm-keep -m 1
stress: info: [1392] dispatching hogs: 0 cpu, 0 io, 1 vm, 0 hdd

# 创建一个 cgroup
$ cd /sys/fs/cgroup/user.slice
$ sudo mkdir test-limit-memory && cd test-limit-memory

# 设置 cgroup 的最大内存占用为 100MB
$ sudo sh -c "echo 100m > memory.max"

# 将当前进程移动到这个 cgroup 中
$ sudo sh -c "echo $$ >> cgroup.procs"

$ stress --vm-bytes 200m --vm-keep -m 1
$ systemd-cgtop
CGroup                              Tasks   %CPU   Memory  Input/s Output/s
user.slice                             14   14.7   139.5M        -        -
user.slice/test-limit-memory            3   14.3    99.8M        -        -
```

### 2.2.2 Docker 是如何使用 Cgroups 的
