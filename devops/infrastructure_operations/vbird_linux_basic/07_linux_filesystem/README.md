# 第七章 Linux 磁盘与文件系统管理

## 目录

- [第七章 Linux 磁盘与文件系统管理](#第七章-linux-磁盘与文件系统管理)
  - [目录](#目录)
  - [7.1 认识 Linux 文件系统](#71-认识-linux-文件系统)
    - [7.1.1 磁盘组成与分区的复习](#711-磁盘组成与分区的复习)
    - [7.1.2 文件系统特性](#712-文件系统特性)
    - [7.1.3 Linux 的 Ext2 文件系统 (inode)](#713-linux-的-ext2-文件系统-inode)

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
