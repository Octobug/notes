# 第七章 Linux 磁盘与文件系统管理

> <http://cn.linux.vbird.org/linux_basic/0230filesystem.php>

## 目录

- [第七章 Linux 磁盘与文件系统管理](#第七章-linux-磁盘与文件系统管理)
  - [目录](#目录)
  - [7.1 认识 Linux 文件系统](#71-认识-linux-文件系统)
    - [7.1.1 磁盘组成与分区的复习](#711-磁盘组成与分区的复习)
    - [7.1.2 文件系统特性](#712-文件系统特性)
    - [7.1.3 Linux 的 Ext2 文件系统 (inode)](#713-linux-的-ext2-文件系统-inode)
    - [7.1.4 文件系统与目录树的关系](#714-文件系统与目录树的关系)
    - [7.1.5 EXT2/EXT3/EXT4 文件的存取与日志式文件系统的功能](#715-ext2ext3ext4-文件的存取与日志式文件系统的功能)
    - [7.1.6 Linux 文件系统的运行](#716-linux-文件系统的运行)
    - [7.1.7 挂载点的意义 (mount point)](#717-挂载点的意义-mount-point)
    - [7.1.8 其他 Linux 支持的文件系统与 VFS](#718-其他-linux-支持的文件系统与-vfs)
    - [7.1.9 XFS 文件系统简介](#719-xfs-文件系统简介)
  - [7.2 文件系统的简单操作](#72-文件系统的简单操作)
    - [7.2.1 磁盘与目录的容量](#721-磁盘与目录的容量)
    - [7.2.2 实体链接与符号链接: ln](#722-实体链接与符号链接-ln)
  - [7.3 磁盘的分区、格式化、检验与挂载](#73-磁盘的分区格式化检验与挂载)
    - [7.3.1 观察磁盘分区状态](#731-观察磁盘分区状态)
    - [7.3.2 磁盘分区: gdisk/fdisk](#732-磁盘分区-gdiskfdisk)
    - [7.3.3 磁盘格式化（创建文件系统）](#733-磁盘格式化创建文件系统)
    - [7.3.4 文件系统检验](#734-文件系统检验)
    - [7.3.5 文件系统挂载与卸载](#735-文件系统挂载与卸载)
      - [挂载](#挂载)
    - [7.3.6 磁盘/文件系统参数修订](#736-磁盘文件系统参数修订)

## 7.1 认识 Linux 文件系统

### 7.1.1 磁盘组成与分区的复习

盘片上的物理组成：

- 扇区 (Sector): 最小存储单位，目前有 512Bytes 和 4K 两种
- 柱面 (Cylinder): 和圆心距离一样的扇区组成的圆
- 早期的以柱面为最小分区单位，现在通常使用扇区
- 磁盘分区主要有两种格式，一种是传统的 MBR，另外一种是比较新且强大的 GPT
- MBR 分区中第一个扇区最重要，里面包含：
  1. 主要启动区记录 MBR (Master boot record)，占 446 Bytes
  2. 分区表 (partition table)，占 64 Bytes
- GPT 分区表没有主/扩展分区之分，可以认为所有分区都是主分区，容量可超过 2TB

磁盘设备文件名：

- `/dev/sd[a-p][1-128]`: 实体磁盘的磁盘文件名
- `/dev/vd[a-d][1-128]`: 虚拟磁盘的磁盘文件名

### 7.1.2 文件系统特性

格式化：初始化分区的文件系统，使操作系统能识别。

常见的文件系统有：

- FAT (File Allocation Table)
- NTFS (New Technology File System)
- Ext2 (Second Extended File System)/3/4

文件系统的文件数据除了文件实际内容外，通常还包含其他属性（权限、文件属性等）。
文件系统通常将这两部分数据分别存放在不同区块。权限与属性存在 inode 中，文件实际数据则在 data
block 中。另外还有一个超级区块 superblock 记录整个文件系统的整体信息，包括 inode 与 block
的总量、使用量、剩余量等。

每个 inode 与 block 都有编号：

- superblock: 记录此文件系统的整体信息，包括 inode/block 总量、使用量、剩余量及
  文件系统格式和其他信息
- inode: 记录文件的属性，一个文件占用一个 inode，同事记录此文件实际数据所在的 block 号
- block: 记录文件实际内容，如果文件较大会占用多个 block

假设文件系统格式化出了 inode 与 block 两种区块，某个 inode 记录了 4 个 block，
操作系统能一次性将 4 个 block 读取出来，则这种数据存储方式成为索引式文件系统
(indexed allocation)。

FAT 文件系统没有 inode 存在，每个 block 号都存在前一个 block 中，因此只能一个接一个读取。

### 7.1.3 Linux 的 Ext2 文件系统 (inode)

inode: index node

文件系统在格式化时已经规划好 inode 与 block，除非重新格式化或使用 `resize2fs`
命令才能修改。

Ext2 在格式化时将 block 分成多个 block group，每个 group 里都有独立的
inode/block/superblock 系统。

每个 block group 有六个部分：

1. data block (数据区块): 用于放置文件内容数据，block 大小有 1K, 2K, 4K 三种。

    | Block 大小         | 1KB  | 2KB   | 4KB  |
    | ------------------ | ---- | ----- | ---- |
    | 最大单一文件限制   | 16GB | 256GB | 2TB  |
    | 最大文件系统总容量 | 2TB  | 8TB   | 16TB |

    - block 的大小与数量在格式化完成后就无法改变，除非重新格式化
    - 每个 block 最多存放一个文件的内容
    - 如果文件大于 block 的大小，则会占用多个 block
    - 如果文件小于 block，则剩余空间无法利用

    如果 block 太小，则大文件会占用更多的 block, 导致 inode 要记录跟多 block 编号。

2. inode table (inode 表)
    - 每个 inode 记录的内容
      - 文件的权限 (read/write/execute)
      - 文件的用户信息 (owner/group)
      - 文件的容量
      - 文件创建或状态改变的时间 (ctime)
      - 文件最近的访问时间 (access)
      - 文件最近的修改时间 (mtime)
      - 文件特殊属性 (SUID/GUID/SBIT)
      - 文件内容指向 (pointer)
    - inode 的数量与大小在格式化时已固定
      - 每个 inode 大小为 128 Bytes (ext4 与 xfs 支持 256 Bytes)
      - 每个文件只占用一个 inode
      - 文件系统能创建的文件数量与 inode 直接相关
      - 系统访问文件时会先找到 inode, 分析用户是否有权限访问后才开始访问 block
      - 记录每个 block 占用 4 Bytes
    - inode 的 block 索引组成 (以 1KB block 为例)
      - 12 个直接索引: 12 * 1K = 12K
      - 1 个 1 层间接索引: 每个 block 可记录 1K/4B=256 个 block, 1K * 256 = 256K
      - 1 个 2 层间接索引: 1K * 256^2 = 64M
      - 1 个 3 层间接索引: 1K * 256^3 = 16G
3. superblock (超级区块): 记录整个文件系统相关信息
    - superblock 大小为 1024Bytes
    - 记录的项目
      - block 与 inode 总量
      - 未使用与已使用的 inode 与 block 数量
      - block 与 inode 的大小 (block 可以是 1,2,4K, inode 为 128Bytes,
        256Bytes(Ext4))
      - 文件系统的挂载时间，最近一次写入时间，最近一次磁盘检查 (fsck) 时间等
      - 一个 valid bit 数值
        - 0: 已挂载
        - 1: 未挂载
    - 每个文件系统只有一个 superblock，除了第一个 block group，后续的 group
      里不一定会有 superblock，有的话则是作为副本备用
4. Filesystem Description (文件系统描述): 描述每个 block group 的开始与结束的 block
  号码，以及说明每个区段 (superblock, bitmap, inodemap, data block) 分别介于哪个
  block 号码之间。可用 `dumpe2fs` 观察。
5. block bitmap (区块对照表): 记录 block 是否已使用
6. inode bitmap (inode 对照表): 记录 inode 是否已使用

- `dumpe2fs`: 查询 Ext 家族文件系统 superblock 信息
- `blkid`: 列出系统已格式化设备

### 7.1.4 文件系统与目录树的关系

目录与文件在文件系统中如何记录数据的呢？

- 目录: 创建目录时，文件系统至少分配一个 inode 与一个 block。
  - inode: 记录目录相关权限与属性，并记录分配到的 block 号码。
  - block: 记录目录下的文件信息
    - 文件名
    - 对应文件占用的 inode 号
  - `ls -li`: 查看文件 inode 号
- 文件: 创建普通文件时，文件系统会分配一个 inode 和适应文件大小的若干个 block

目录树的读取：文件名记录于目录 block 中，因此读写文件时必然经过目录的 inode 与 block，
最终获取到目标文件的 inode 与 block。

例：系统如何读取 `/etc/passwd` 文件？

```sh
$ ll -di / /etc /etc/passwd
     2 drwxr-xr-x 24 root root 4.0K Jan 11 03:22 /
655361 drwxr-xr-x 94 root root 4.0K Jan 18 13:02 /etc
665481 -rw-r--r--  1 root root 1.8K Jan 11 03:38 /etc/passwd
```

1. `/` 的 inode: 通过挂载点信息找到根目录 inode 为 2 号e，且权限允许读取 block
2. `/` 的 block: 读取 block 得到 `etc/` 目录的 inode 为 655361
3. `etc/` 的 inode: 读取 655361 号 inode，且权限允许读取 block
4. `etc/` 的 block: 读取 block 得到 `passwd` 文件的 inode 为 665481
5. `passwd` 的 inode: 读取 665481 号 inode，且权限允许读取 block
6. `passwd` 的 block: 读取 block 内容

### 7.1.5 EXT2/EXT3/EXT4 文件的存取与日志式文件系统的功能

文件系统新增一个文件的流程：

1. 先确定用户对于新增文件目录是否有 `w` 与 `x` 权限
2. 根据 inode bitmap 找到空闲 inode 号码，将新文件的权限/属性写入
3. 根据 block bitmap 找到空闲的 block 号码，将实际数据写入 block，且更新 inode 的
 block 索引
4. 将写入的 inode 与 block 数据同步更新到 inode bitmap 与 block bitmap，并更新
 superblock 内容

数据的不一致 (Inconsistent) 状态: 系统故障导致写入过程不完整，使得 metadata
(inode bitmap、block bitmap、superblock) 信息不一致

- Ext2: 系统开机时根据 superblock 的 valid bit (是否挂载) 与文件系统状态 (clean 与否)
  等状态判断是否强制对整个文件系统进行数据一致性检查 (使用 `e2fsck`)
- 日志式文件系统 (Journaling filesystem): 文件系统中专门记录写入或修改文件时的步骤
  1. 预备: 系统要写入一个文件时，会先在日志记录区块中记录某个文件要写入的信息；
  2. 实际写入: 写入文件的权限与数据；更新 metadata；
  3. 结束: 完成数据与 metadata 更新后，在日志记录区块中完成改文件的记录。

  当写入过程发生问题，系统只需要检查日志记录区块再进行针对性的一致性检查，
  而不需要检查整个文件系统。

### 7.1.6 Linux 文件系统的运行

系统加载一个文件到内存后，如果文件没有被更改过，那么内存里的文件数据会被标记为 clean,
否则为 dirty。系统定期将内存中标记为 dirty 的数据写回磁盘以确保一致性。

Linux 文件系统与内存：

- 常用文件数据放置于内存缓冲区，加速文件系统的读写；
- 可手动使用 `sync` 强制同步 dirty 文件到磁盘
- 正常关机时系统会自动调用 `sync`
- 非正常关机可能导致文件系统损坏

### 7.1.7 挂载点的意义 (mount point)

将文件系统加入到目录树的动作成为挂载。挂载点一定是目录，该目录为进入文件系统的入口。

### 7.1.8 其他 Linux 支持的文件系统与 VFS

- 传统文件系统
  - Ext2
  - Minix
  - MS-DOS
  - FAT
  - iso9660
- 日志式文件系统
  - Ext3/Ext4
  - ReiserFS
  - Windows' NTFS
  - IBM's JFS
  - SGI's XFS
  - ZFS
- 网络文件系统
  - NFS
  - SMBFS

```sh
# 查看当前 Linux 系统支持的文件系统:
ls -l /lib/modules/$(uname -r)/kernel/fs
# 查看系统当前载入内存中支持的文件系统
cat /proc/filesystem
# 查看系统已挂载的文件系统类型
df -T
```

- Linux VFS (Virtual Filesystem Switch): Linux 内核使用 VFS 管理文件系统，
  使实际的文件系统对用户透明。

### 7.1.9 XFS 文件系统简介

CentOS 7 之后默认使用 XFS 文件系统。

- Ext 家族: 支持度最广，但格式化超慢
- XFS 文件系统的配置
  - 数据区 (data section): 类似 ext 的 block group，包括以下几项。主要区别是 inode 与
    block 为动态产生，所以格式化较快
    - inode
    - block
    - superblock
  - 文件系统活动记录区 (log section): 类似 ext3/4 的日志记录区
  - 实时运行区 (realtime section):
    当文件要被创建，xfs 会在该区段里找到数个 extent 区块，将文件放入，再写入到 data
    section 的 inode 与 block 中。extent 区块大小需要在格式化时指定。
- XFS 文件系统的描述数据观察: `xfs_info`

## 7.2 文件系统的简单操作

### 7.2.1 磁盘与目录的容量

- `df`: 列出文件系统整体磁盘使用情况，主要从 superblock 获取信息
  - `-a`: 列出所有文件系统，包括系统特有的 `/proc` 等
  - `-k`: 以 KBytes 显示容量
  - `-m`: 以 MBytes 显示容量
  - `-h`: 以人类易读的形式显示容量
  - `-H`: 以 10^3 进位取代 2^10 显示容量
  - `-T`: 列出分区的文件系统类型
  - `-i`: 显示 inode 数量而非容量
- `du`: 统计文件系统 (目录或文件) 的磁盘使用量，会访问文件系统获取相关的文件信息
  - `-a`: 列出所有的文件与目录容量，默认只统计目录的总容量
  - `-k`: 以 KBytes 显示容量
  - `-m`: 以 MBytes 显示容量
  - `-h`: 以人类易读的形式显示容量
  - `-s`: 只列出总量
  - `-S`: 只列出目录本身大小而不包括目录下其他文件的总量

### 7.2.2 实体链接与符号链接: ln

- Hard Link (硬链接或实体链接)
  - 在某个目录的 block 新增一个文件记录，且该记录保存的是某个已使用的 inode 号
  - 新增 hark link 只有在目录 block 空间不够时才会增加 block 占用
  - 缺点
    - 不能跨文件系统
    - 不能链接目录
- Symbolic Link (符号链接或软链接)
  - 创建符号链接是创建一个独立的新文件，而这个新文件会使数据读取指向其他文件。
  - 符号链接会保存目标文件路径，因此其文件大小就是保存的路径名大小
  - 符号链接可以链接目录
- 为什么符号链接可以链接目录，而硬链接不行？

  假设可以成功执行如下命令:

  ```sh
  mkdir -p /tmp/a/b
  cd /tmp/a/b
  ln -d /tmp/a hl
  # 形成路径 /tmp/a/b/hl/b/hl/b/hl/b/...
  ```

  a 目录的文件列表记录了 b 的 inode, b 目录的文件列表记录了 hl 的 inode，
  hl 是硬链接，所以其 inode 与 a 目录相同，相当于 b 目录文件列表记录了 a 的 inode，造成
  inode 回环，导致文件系统难以处理文件删除等操作。

  更详细的原因请参考文章 [linux 为什么不能硬链接目录？](https://www.zhihu.com/question/50223526)

- 目录的 `.` 与 `..` 会增加相应目录的连接数

## 7.3 磁盘的分区、格式化、检验与挂载

新增一个磁盘的基本流程：

1. 分区
2. 格式化
3. 文件系统检查 (可选)
4. 把分区挂载到某个目录

### 7.3.1 观察磁盘分区状态

- lsblk: 列出系统上所有磁盘
  - 选项
    - `-d`: 仅列出磁盘而不包括分区信息
    - `-f`: 显示文件系统名称
    - `-i`: 使用 ASCII 的线段输出，不使用复杂的文字编码
    - `-m`: 同时输出该设备在 /dev 下的权限
    - `-p`: 列出设备完整名
    - `-t`: 列出磁盘设备详细信息
  - 信息
    - NAME: 设备名
    - MAJ:MIN: 主要:次要设备号码
    - RM: 是否为可移除设备，如 U 盘、光盘等
    - SIZE: 容量
    - RO: 是否只读
    - TYPE: 磁盘、分区、或只读存储
    - MOUNTPOINT: 挂载点
- blkid: 列出设备 UUID 等信息
- parted: 列出磁盘分区表信息

### 7.3.2 磁盘分区: gdisk/fdisk

- gdisk (支持 GPT)
- partprobe: 更新系统内核分区表信息
  - `-s`: 显示详细信息
  - `cat /proc/partitions`
- fdisk (MBR)

### 7.3.3 磁盘格式化（创建文件系统）

- XFS 文件系统 mkfs.xfs
  - `-d`
    - `agcount=数值`: 存储群组数量，可以加速格式化
  - `grep 'processor' /proc/cpuinfo`
- XFS 文件系统 for RAID 性能优化 (Optional)
- EXT4 文件系统 mkfs.ext4
- 其他文件系统 mkfs
  - `-t`: 指定具体的文件系统类型

### 7.3.4 文件系统检验

- 检查修复文件系统时，必须先卸载文件系统
- 根目录出问题时，由于无法卸载，只能进入单人维护或救援模式修复
- `xfs_repair` 处理 XFS 文件系统
- `fsck.ext4` 处理 EXT4 文件系统

### 7.3.5 文件系统挂载与卸载

- 单一文件系统**不应该**被重复挂载在不同的挂载点（目录）中
- 单一目录**不应该**重复挂载多个文件系统
- 作为挂载点的目录应该都是空目录
  - 挂载后原目录下的东西会被隐藏无法访问。直到文件系统卸载后才恢复。

#### 挂载

- `mount`
  - LABEL='' 目录名
  - UUID='' 目录名
  - 设备文件名 目录名
  - `-a`: 按照配置文件 `/etc/fstab` 的数据将所有未挂载磁盘都挂载
  - `-l`: 显示 Label
  - `-t`: 文件系统类型
  - `-n`: 默认情况下系统会将实际挂载情况实时写入 `/etc/mtab`，使用该选项可以避免写入
  - `-o`: 额外参数，比如账号、密码、读写权限
    - async, sync: 异步或同步写入磁盘
    - atime, noatime: 是否更新访问时间
    - ro, rw: 只读或读写
    - auto, noauto: 是否允许被 `-a` 自动挂载
    - dev, nodev: 是否允许创建 dev 文件
    - suid, nosuid: 是否允许创建含有 suid/sgid 的文件
    - exec, noexec: 是否允许有可执行文件
    - user, nouser: 是否允许任何用户执行 mount
    - defaults: rw, suid, dev, exec, auto, nouser, and async
    - remount: 重新挂载

  `-t` 一般不需要指定，系统通过 superblock 与以下信息测试挂载

  - `/etc/filesystems`: 系统指定的测试挂载文件系统类型优先顺序
  - `/proc/filesystems`: 系统已经载入的文件系统类型
  - `ls /lib/modules/$(uname -r)/kernel/fs`

- 重新挂载根目录与挂载不特定目录
  - `mount -o remount,rw,auto /`: 将根目录重新挂载为可读写
  - `mount --bind /var /data/var`: 将目录挂载到其他目录，用于不支持符号链接的程序
- umount (卸载设备文件) [-fn] 文件名或挂载点
  - `-f`: 强制卸载
  - `-l`: 立即卸载文件系统, 比 -f 更强
  - `-n`: 不更新 `/etc/mtab` 卸载
  
  进入挂载点目录内会导致设备忙，退出后才能卸载。

### 7.3.6 磁盘/文件系统参数修订
