# 第十四章 磁盘配额（Quota）与进阶文件系统管理

> <https://linux.vbird.org/linux_basic/centos7/0420quota.php>

## 目录

- [第十四章 磁盘配额（Quota）与进阶文件系统管理](#第十四章-磁盘配额quota与进阶文件系统管理)
  - [目录](#目录)
  - [14.1 磁盘配额（Quota）的应用与实作](#141-磁盘配额quota的应用与实作)
    - [14.1.1 什么是 Quota](#1411-什么是-quota)
    - [14.1.2 一个 XFS 文件系统的 Quota 实践范例](#1412-一个-xfs-文件系统的-quota-实践范例)
    - [14.1.3 实践 Quota 流程-1：文件系统的支持与观察](#1413-实践-quota-流程-1文件系统的支持与观察)
    - [14.1.4 实践 Quota 流程-2：观察 Quota 报告数据](#1414-实践-quota-流程-2观察-quota-报告数据)
    - [14.1.5 实践 Quota 流程-3：限制值设置方式](#1415-实践-quota-流程-3限制值设置方式)
    - [14.1.6 实践 Quota 流程-4：project 的限制（针对目录限制）（Optional）](#1416-实践-quota-流程-4project-的限制针对目录限制optional)
    - [14.1.7 XFS Quota 的管理与额外命令对照表](#1417-xfs-quota-的管理与额外命令对照表)
    - [14.1.8 不变更既有系统的 Quota 实例](#1418-不变更既有系统的-quota-实例)
  - [14.2 软件磁盘阵列（Software RAID）](#142-软件磁盘阵列software-raid)
    - [14.2.1 什么是 RAID](#1421-什么是-raid)
    - [14.2.2 software, hardware RAID](#1422-software-hardware-raid)
    - [14.2.3 软件磁盘阵列的设置](#1423-软件磁盘阵列的设置)
    - [14.2.4 仿真 RAID 错误的救援模式](#1424-仿真-raid-错误的救援模式)
    - [14.2.5 开机自动启动 RAID 并自动挂载](#1425-开机自动启动-raid-并自动挂载)
    - [14.2.6 关闭软件 RAID (重要)](#1426-关闭软件-raid-重要)
  - [14.3 逻辑卷管理员 (Logical Volume Manager)](#143-逻辑卷管理员-logical-volume-manager)
    - [14.3.1 什么 LVM: PV, PE, VG, LV 的意义](#1431-什么-lvm-pv-pe-vg-lv-的意义)
    - [14.3.2 LVM 实践流程](#1432-lvm-实践流程)
    - [14.3.3 放大 LV 容量](#1433-放大-lv-容量)
    - [14.3.4 使用 LVM thin Volume 让 LVM 动态自动调整磁盘使用率](#1434-使用-lvm-thin-volume-让-lvm-动态自动调整磁盘使用率)
    - [14.3.5 LVM 的 LV 磁盘快照](#1435-lvm-的-lv-磁盘快照)
    - [14.3.6 LVM 相关指令与 LVM 的关闭](#1436-lvm-相关指令与-lvm-的关闭)
  - [14.4 重点回顾](#144-重点回顾)
  - [14.5 本章习题](#145-本章习题)
  - [14.6 参考资料与延伸阅读](#146-参考资料与延伸阅读)

## 14.1 磁盘配额（Quota）的应用与实作

### 14.1.1 什么是 Quota

- Quota 的使用场景
  - 网络服务
    - www server
    - mail server
    - file server
  - 主机使用
    - 限制某个用户组的最大磁盘配额
    - 限制某个用户的最大磁盘配额
    - 限制某个目录的最大磁盘配额
- Quota 的局限
  - 对于 Ext 系列文件系统来说只能针对整个文件系统，无法针对某个单一目录
  - 需要 Linux 内核支持 quota
  - 只对一般用户有效
  - 启用 SELinux 时并非所有目录都可以设置 Quota，默认只能针对 `/home` 目录进行设置
- XFS 下的 Quota 规范设置项目
  - 用户
  - 用户组
  - 目录
- 容量限制或文件数量限制（block 或 inode）
  - 限制 inode 用量
  - 限制 block 用量
- 柔性劝导与硬性规定（soft/hard）
  - soft: 用户在低于 soft 值时，可以正常使用磁盘；若超过 soft 且低于 hard 值，
    则每次登录系统都会收到警告磁盘警告信息，且会给一个宽限时间（grace time）
  - hard: 用户的使用量绝对不会超过 hard 值，超过时系统会锁住该用户的磁盘使用权
  - grace time: 宽限时间，默认为 7 天，超过宽限时间时会被锁住磁盘使用权

### 14.1.2 一个 XFS 文件系统的 Quota 实践范例

```sh
#!/bin/bash
# 使用 script 來建立實驗 quota 所需的環境
groupadd myquotagrp
for username in myquota1 myquota2 myquota3 myquota4 myquota5; do
    useradd -g myquotagrp $username
    echo "password" | passwd --stdin $username
done
mkdir /home/myquota
chgrp myquotagrp /home/myquota
chmod 2770 /home/myquota
```

### 14.1.3 实践 Quota 流程-1：文件系统的支持与观察

```fstab
# /etc/fstab
/dev/mapper/centos-home  /home  xfs  defaults,usrquota,grpquota   0 0
```

针对 quota 限制的项目只有有三项，如下

- uquota/usrquota/quota: 针对用户的设置
- gquota/grpquota: 针对用户组的设置
- pquota/prjquota: 针对单一目录的设置，无法与 grpquota 同时存在

修改后使用 `mount -a`。

### 14.1.4 实践 Quota 流程-2：观察 Quota 报告数据

- `xfs_quota -x -c COMMAND` MOUNTPOINT

### 14.1.5 实践 Quota 流程-3：限制值设置方式

- `xfs_quota -x -c "limit [-ug] b[soft|hard]=N i[soft|hard]=N name"`
- `xfs_quota -x -c "timer [-ug] [-bir] Ndays"`

### 14.1.6 实践 Quota 流程-4：project 的限制（针对目录限制）（Optional）

- 修改 `/etc/fstab` 以支持项目限制

  ```fstab
  /dev/mapper/centos-home /home xfs  defaults,usrquota,prjquota  0 0
  ```

- 设置规范目录、项目名称与项目 ID `/etc/projetcs`
- 实际设置规范与测试

### 14.1.7 XFS Quota 的管理与额外命令对照表

- disable: 暂时取消 quota 限制，系统会继续计算 quota，但不进行管制
- enable: 回到正常的管制状态
- off: 完全关闭 Quota 限制，需要卸载并重新挂载才能再次启动 Quota
- remove: 需要在 off 状态下进行，remove 可以移除 Quota 的设置

### 14.1.8 不变更既有系统的 Quota 实例

假设需要对 `/var/spool/mail` 进行限制：

1. 将 `/var/spool/mail` 移动到 `/home` 下
2. `ln -s /home/mail /var/spool/mail`
3. 对 `/home` 进行 Quota 限制

## 14.2 软件磁盘阵列（Software RAID）

### 14.2.1 什么是 RAID

RAID (Redundant Arrays of Inexpensive Disks): 容错式廉价磁盘阵列，
通过硬件或软件将多个磁盘组合成一个磁盘设备。

- RAID-0: 等量模式，stripe，性能最佳。但只要有一个盘坏掉所有的数据都会损坏。
- RAID-1: 映射模式，mirror，完整备份。如果是软件 RAID，将会导致南桥传输的数据量翻倍。
  读取性能较好。
- RAID 1+0, RAID 0+1
  - 先组两组 RAID 1；再将两组 RAID 1 组成 RAID 0
  - 先组两组 RAID 0；再将两组 RAID 0 组成 RAID 1
- RAID 5: 性能与数据备份的均衡考虑。至少需要 3 个磁盘才能组成。除了采用类似 RAID-0
  的数据存储写入方式，还会在每个磁盘中加入一个同位校验数据 (Parity)，
  这个数据会记录其他磁盘的备份数据。由于存储了校验数据，所以总容量为磁盘数-1。
  只能承受一个磁盘的损坏。
- RAID 6: 比 RAID 5 多一分 parity 数据，能承受两个磁盘的损坏。
- Spare Disk: 预备磁盘，阵列之外的磁盘，当阵列中有磁盘损坏时会将 Spare Disk 加入到阵列中，
  然后重建数据系统。

好处：

1. 数据安全与可靠性
2. 读写性能
3. 容量

### 14.2.2 software, hardware RAID

CentOS 的软件磁盘阵列为 `mdadm`，可以 partition 或 disk 为磁盘单位。
软件磁盘阵列的设备文件名为 `/dev/md[N]`。

### 14.2.3 软件磁盘阵列的设置

- 用 `mdadm` 创建 RAID 5：

  ```sh
  mdadm --create /dev/md0 --auto=yes --level=5 --chunk=256K \
    --raid-devices=4 --spare-devices=1 /dev/vda{5,6,7,8,9}
  ```

- 格式化与挂载使用 RAID

### 14.2.4 仿真 RAID 错误的救援模式

- 设置磁盘为错误 (fault): `mdadm --manage /dev/md0 --fail /dev/vda7`
- 将出错的磁盘移除并加入新磁盘
  1. 从 `/dev/md0` 阵列中移除 `/dev/vda7`:
    `dmadm --manage /dev/md0 --remove /dev/vda7`
  2. 关机，“移除” `/dev/vda7`，“安装”新的 `/dev/vda7`，重新开机
  3. 将新的 `/dev/vda7` 加入 `/dev/md0` 阵列:
    `mdadm --manage /dev/md0 --add /dev/vda7`

### 14.2.5 开机自动启动 RAID 并自动挂载

```sh
[root@study ~]# mdadm --detail /dev/md0 | grep -i uuid
           UUID : 2256da5f:4870775e:cf2fe320:4dfabbc6
# 後面那一串資料，就是這個裝置向系統註冊的 UUID 識別碼！

# 開始設定 mdadm.conf
[root@study ~]# vim /etc/mdadm.conf
ARRAY /dev/md0 UUID=2256da5f:4870775e:cf2fe320:4dfabbc6
#     RAID裝置      識別碼內容

# 開始設定開機自動掛載並測試
[root@study ~]# blkid /dev/md0
/dev/md0: UUID="494cb3e1-5659-4efc-873d-d0758baec523" TYPE="xfs"

[root@study ~]# vim /etc/fstab
UUID=494cb3e1-5659-4efc-873d-d0758baec523  /srv/raid xfs defaults 0 0

[root@study ~]# umount /dev/md0; mount -a
[root@study ~]# df -Th /srv/raid
Filesystem     Type  Size  Used Avail Use% Mounted on
/dev/md0       xfs   3.0G  111M  2.9G   4% /srv/raid
# 你得確定可以順利掛載，並且沒有發生任何錯誤！
```

### 14.2.6 关闭软件 RAID (重要)

RAID 相关数据会存在磁盘中，即使移除配置文件，用 mdadm 关闭 RAID，但由于没有重新分区，
系统重启后还是会创建相应的 RAID。

```sh
# 1. 先卸載且刪除設定檔內與這個 /dev/md0 有關的設定：
[root@study ~]# umount /srv/raid
[root@study ~]# vim /etc/fstab
UUID=494cb3e1-5659-4efc-873d-d0758baec523  /srv/raid xfs defaults 0 0
# 將這一行刪除掉！或者是註解掉也可以！

# 2. 先覆蓋掉 RAID 的 metadata 以及 XFS 的 superblock，才關閉 /dev/md0 的方法
[root@study ~]# dd if=/dev/zero of=/dev/md0 bs=1M count=50
[root@study ~]# mdadm --stop /dev/md0
mdadm: stopped /dev/md0  <==不囉唆！這樣就關閉了！
[root@study ~]# dd if=/dev/zero of=/dev/vda5 bs=1M count=10
[root@study ~]# dd if=/dev/zero of=/dev/vda6 bs=1M count=10
[root@study ~]# dd if=/dev/zero of=/dev/vda7 bs=1M count=10
[root@study ~]# dd if=/dev/zero of=/dev/vda8 bs=1M count=10
[root@study ~]# dd if=/dev/zero of=/dev/vda9 bs=1M count=10

[root@study ~]# cat /proc/mdstat
Personalities : [raid6] [raid5] [raid4]
unused devices: <none>  <==看吧！確實不存在任何陣列裝置！

[root@study ~]# vim /etc/mdadm.conf
#ARRAY /dev/md0 UUID=2256da5f:4870775e:cf2fe320:4dfabbc6
# 一樣啦！刪除他或是註解他！
```

## 14.3 逻辑卷管理员 (Logical Volume Manager)

LVM 可以动态调整文件系统容量，整合多个 partition 成一个。

### 14.3.1 什么 LVM: PV, PE, VG, LV 的意义

- PV (Physical Volume): 实体卷，`pvcreate`
- VG (Volume Group): 卷组，许多个 PV 的整合体
- PE (Physical Extent): 实体范围区块，LVM 的最小存储区块
- LV (Logical Volume): 逻辑卷，可以被格式化的单位，由 VG 分割而成。
  LV 的设备名格式通常为 `/dev/VGNAME/LVNAME`

LVM 的弹性文件系统容量通过“交换 PE”实现。即将 LV 的 PE 转移到其他 LV 中实现容量的增减。

![LVM](images/14_3_2_centos7_lvm.jpg)

LV 的数据写入有两种机制：

- 线性模式 (linear): PV1 被用完之后才使用 PV2
- 交错模式 (triped): 一份数据被分割写入 PV1, PV2, PV3, ...

### 14.3.2 LVM 实践流程

1. PV 阶段
2. VG 阶段
3. LV 阶段
4. 文件系统阶段

### 14.3.3 放大 LV 容量

1. VG 需要有剩余容量，以放大 LV
2. 使用 `lvresize` 将剩余容量加入 LV
3. 调整文件系统：需要文件系统支持调整容量，XFS 只支持放大，EXT 支持放大与缩小

### 14.3.4 使用 LVM thin Volume 让 LVM 动态自动调整磁盘使用率

即动态分配容量的卷。

### 14.3.5 LVM 的 LV 磁盘快照

快照：将当前的系统信息记录下来，未来如果有数据变更，则原始数据会被搬移到快照区，
没有变更的数据则有快照区域文件系统共享。

### 14.3.6 LVM 相关指令与 LVM 的关闭

1. 卸载 LVM 文件系统，包括快照于所有 LV
2. 使用 lvremove 移除 LV
3. 使用 vgchange -an VGname 让 VGname 这个 VG 不具有 Active 标志
4. 使用 vgremove 移除 VG
5. 使用 pvremove 移除 PV
6. 使用 fdisk 修改磁盘设备 ID

## 14.4 重点回顾

## 14.5 本章习题

## 14.6 参考资料与延伸阅读
