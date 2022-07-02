# 第三章 安装 CentOS 7.x 与多重开机小技巧

> <https://linux.vbird.org/linux_basic/centos7/0157installcentos7.php>

- [第三章 安装 CentOS 7.x 与多重开机小技巧](#第三章-安装-centos-7x-与多重开机小技巧)
  - [3.1 本练习机的规划--尤其是分割参数](#31-本练习机的规划--尤其是分割参数)
  - [3.2 开始安装 CentOS 7](#32-开始安装-centos-7)
    - [3.2.1 调整开机媒体 (BIOS) 与虚拟机创建流程](#321-调整开机媒体-bios-与虚拟机创建流程)
    - [3.2.2 选择安装模式与开机 - inst.gpt](#322-选择安装模式与开机---instgpt)
      - [加入强制使用 GPT 分区表的安装参数](#加入强制使用-gpt-分区表的安装参数)
    - [3.2.3 在地设置之时区、语系与键盘设置](#323-在地设置之时区语系与键盘设置)
    - [3.2.4 安装来源设置与软件选择](#324-安装来源设置与软件选择)
    - [3.2.5 磁盘分区与文件系统设置](#325-磁盘分区与文件系统设置)
    - [3.2.6 核心管理与网络设置](#326-核心管理与网络设置)
    - [3.2.7 开始安装、设置 root 密码与新增可切换身份之一般用户](#327-开始安装设置-root-密码与新增可切换身份之一般用户)
    - [3.2.8 准备使用系统前的授权同意](#328-准备使用系统前的授权同意)
    - [3.2.9 其他功能：RAM testing, 安装笔记本电脑的核心参数 (Option)](#329-其他功能ram-testing-安装笔记本电脑的核心参数-option)
  - [3.x 安装后的首次设定](#3x-安装后的首次设定)
  - [3.3 多重开机安装流程与管理（Option）](#33-多重开机安装流程与管理option)
    - [3.3.1 安装 CentOS 7.x + Windows 7 的规划](#331-安装-centos-7x--windows-7-的规划)
    - [3.3.2 进阶安装 CentOS 7.x 与 Windows 7](#332-进阶安装-centos-7x-与-windows-7)
    - [3.3.3 救援 MBR 内的开机管理程序与设置多重开机菜单](#333-救援-mbr-内的开机管理程序与设置多重开机菜单)
    - [3.3.x 旧主机有两颗以上硬盘](#33x-旧主机有两颗以上硬盘)
    - [3.4.x 旧主机只有一颗硬盘](#34x-旧主机只有一颗硬盘)
  - [3.5.x 关於大硬盘导致无法开机的问题](#35x-关於大硬盘导致无法开机的问题)
  - [3.4 重点回顾](#34-重点回顾)
  - [3.5 本章习题](#35-本章习题)
  - [3.6 参考资料与延伸阅读](#36-参考资料与延伸阅读)
  - [3.7 针对本文的建议](#37-针对本文的建议)

## 3.1 本练习机的规划--尤其是分割参数

- Linux 主机的角色定位：练习 Linux 的相关技术，包含 X Window System；
- 选择的 distribution：CentOS 7.x；
- 计算机系统硬件配备：使用 Linux 原生的 KVM 搭建
  - 主板与 CPU：Intel i7 2600；
  - 内存：1.2GB；
  - 硬盘：40GB 的 VirtI/O 硬盘，文件名应该为 `/dev/vda`，同时接了一个 2GB 的 IDE 硬盘，
    文件名为 `/dev/sda`；
  - 网卡：桥接 (bridge)
  - 显示卡(VGA)：分配 64MB 显存
  - 输入/输出装置：DVD 光驱、1.44MB 软盘机、USB 光学滑鼠、300W 电源供应器、17寸显示器。
- 磁盘分区配置

  | 所需目录/设备 | 磁盘容量 | 文件系统   | 分区格式 |
  | ------------- | -------- | ---------- | -------- |
  | BIOS boot     | 2MB      | 系统自定义 | primary  |
  | `/boot`       | 1GB      | xfs        | primary  |
  | `/`           | 10GB     | xfs        | LVM 方式 |
  | `/home`       | 5GB      | xfs        | LVM 方式 |
  | `swap`        | 1GB      | swap       | LVM 方式 |

- 开机管理程序 (boot loader)：使用 CentOS 7.x 预设的 grub2 软件，并且安装到 MBR 上。
- 选择软件：所有的软件通通安装。

## 3.2 开始安装 CentOS 7

### 3.2.1 调整开机媒体 (BIOS) 与虚拟机创建流程

制作 U 盘镜像：

```sh
# 假设 USB 设备为 /dev/sdc , ISO 文件名为 centos7.iso
dd if=centos7.iso of=/dev/sdc
```

> Tips:
> 如果是 USB3.0 设备，主板可能将 U 盘识别为磁盘

- 在 Linux KVM 上面创建虚拟机的过程：应用程序 -> 系统工具 -> 虚拟机管理员，用法与其他 VM
  工具类似。

### 3.2.2 选择安装模式与开机 - inst.gpt

#### 加入强制使用 GPT 分区表的安装参数

1. 将光标移动到 "Install CentOS 7"
2. 按下 Tab 键，使光标移动到最下方的参数输入处
3. 输入如下内容：

  ```gpt
  vmlinuz initrd=initrd.img inst.stage2=hd:LABEL=CentOS_x86_64 rd.live.check
    quiet inst.gpt
  ```

Boot Options:

- linux noprobe: 不进行硬件侦测；
- linux askmethod: 进入互动模式，安装程序会进行一些询问。如果你的硬盘内含有安装媒体时，
  或者是你的环境内有安装服务器 (Installation server)，那就可以用来填入网络主机来安装；
- memtest86: 这个项目会一直进行内存的读写，如果怀疑内存稳定度不足，可以使用这个项目来测试。

- 选择语系数据

### 3.2.3 在地设置之时区、语系与键盘设置

### 3.2.4 安装来源设置与软件选择

考虑选择如下选项：

- 含有 GUI 的服务器
- GNOME 桌面环境
- KDE Plasma Workspaces

### 3.2.5 磁盘分区与文件系统设置

设备类型有三种：

1. 标准分区: 可理解为主分区，类似 `/dev/vda1`
2. LVM: 支持弹性伸缩文件系统容量的分区格式，分配固定容量
3. LVM 动态分区: 按需动态分配容量

CentOS 预设了四种分割模式，分别为：

1. 移除所选磁碟上的所有分割区，并建立预设分割模式；
2. 移除所选磁碟上的 Linux 分割区，并建立预设的分割模式；
3. 使用所选取磁碟上的未使用空间，建立预设的分割模式；
4. 建立自订的分割模式。

几种文件系统类型分别是：

- ext2/ext3/ext4：Linux 适用的档案系统类型。ext3/4 多了日志记录，
 对於系统的复原比较快速，因此建议务必要选择 ext3/4；
- swap：内存置换空间，由於 swap 并不会使用到目录树的挂载，所以用 swap 不需要指定挂载点；
- BIOS Boot: GPT 分区表可能用到的选项；
- xfs: CentOS 默认文件系统，最早用于大型服务器，格式化速度快；
- physical volume (LVM)：这是用来弹性调整档案系统容量的一种机制，
 可以让你的档案系统容量变大或变小而不改变原有的档案数据内容。
- software RAID：利用 Linux 操作系统的特性，用软件模拟出磁盘阵列的功能。
- vfat：同时被 Linux 与 Windows 所支援的档案系统类型。如果主机硬盘内同时存在 Windows
 与 Linux 操作系统，为了数据交换确实可以建置一个 vfat 的档案系统。

1. BIOS Boot 分区: 设备类型为"标准分区"，文件系统为 "BIOS Boot"
2. `/boot` 分区: 1G, LVM
   - 对于 MBR 分区：如果有 `/boot` 独立分割槽，务必让该它在整颗硬盘的最前面部分。
     因此，选择『强制成为主要分割』。安装程序会主动将 `/boot` 这个特殊目录移到磁碟最前面，
     所以你会看到 `/boot` 所在的磁碟分割槽为 `/dev/hda1`，起始磁柱则为 1 号。
     而根目录的分区会变成 `/dev/hda2`。
3. `/` 分区: 10G, LVM
4. `/home` 分区: 5G, LVM
5. `swap`: 1G，LVM
  
- 建立软件磁盘阵列的方法：(Option, 看看就好别实作)：创建两个『Software RAID』分区，然后选择
  『RAID』来建立软件磁盘阵列的装置。与一般装置档名不同，第一个软件磁盘阵列的装置名称为
  `/dev/md0`。由於仅建立两个软件磁盘阵列分割槽，因此只能选择 RAID0 或 RAID1。
  挂载后实际分割区会显示 `/dev/md0`，由於这个装置是 Linux 系统模拟来的，
  所以磁柱号码的地方会留白。

### 3.2.6 核心管理与网络设置

- KDUMP: 用于内核开发者 debug
- 网络设置: 虚拟机的网卡名为 `eth0`, 而如果是实体机可能会是 `p1p1`, `em1` 之类。
  - IPv4: 手动指定 IP 为 `192.168.1.100/255.255.255.0`

### 3.2.7 开始安装、设置 root 密码与新增可切换身份之一般用户

- 开机管理程序的处理
- 将开机管理程序安装到 boot sector (Option, 看看就好，不要实作)：如果有特殊原因，Linux
  的开机管理程序无法安装到 MBR 时，就得安装到每块 partition 的开机磁区 (boot sector)。
  主机名称通常的格式都是『主机名.网域名』。
- 时区的选择：由於广泛使用的 GMT 时间与现实的时间有点脱节了，因此我们可以透过 UTC
  这个原子钟时间的计算方式，取得较为正确的时间。
- 设定 root 的密码。

### 3.2.8 准备使用系统前的授权同意

开发商将某些相似功能的软件绑在一起成为一个群组。并且选择的所有项目会写入到
`/root/anaconda-ks.cfg`，安装过程会写入到 `/root/install.log`。

### 3.2.9 其他功能：RAM testing, 安装笔记本电脑的核心参数 (Option)

- 内存压力测试：memtest86
- 安装笔记本电脑或其他类 PC 计算机的参数：在安装的时候，告诉安装程序的 linux
  核心不要载入一些特殊功能即可。使用DVD开机时，加入底下这些选项：

    ```conf
    nofb apm=off acpi=off pci=noacpi
    ```

  - apm (Advanced Power Management) 是早期的电源管理模组
  - acpi (Advanced Configuration and Power Interface) 则是近期的电源管理模组
  
  这两者都是硬件本身就有支援的，但是笔记本电脑可能不使用这些机制.

  - nofb 则是取消显示卡上面的缓冲内存侦测，因为笔记本电脑的显示卡常常是整合型的，Linux
    安装程序可能无法侦测到该显示卡模组。

## 3.x 安装后的首次设定

1. 防火墙与 SELinux：对于练习机，防火墙的功能可以先取消，选择『停用』。SELinux (Security
   Enhanced Linux) 并不是防火墙，而是 Linux 系统存取控制 (Access control) 的细部设定，
   重点在於控制程序对於系统档案的存取权限限制。务必打开这个功能。
2. Kdump 与时区的校正：当核心出现错误的时候，是否要将当时的内存内的讯息写到档案中，
   而这个档案就能够给核心开发者研究为啥会当机之用。内存的数据实在太大了，常常进行 Kdump
   会造成硬盘空间的浪费。 所以，这里建议不要启动 Kdump 的功能。台湾的时间服务器：
   `tock.stdtime.gov.tw`。
3. 建立一般使用者：管理员 (root) 的权限太大了，建立一个一般身份使用者来操作是好习惯。
4. 音效卡与其他软件的安装。
  
## 3.3 多重开机安装流程与管理（Option）

### 3.3.1 安装 CentOS 7.x + Windows 7 的规划

假设以目前主流的 160GB 硬盘作为规划，而你想要有 WindowsXP, WindowsXP 的数据碟, Linux, Swap 及一个共用分割槽，可以这样规划：

旧版：

| Linux 装置档名 | Windows 装置 | 内容               | 档案系统 | 容量(GB) |
| -------------- | ------------ | ------------------ | -------- | -------- |
| `/dev/sda1`    | C            | Windows 系统       | NTFS     | 30       |
| `/dev/sda2`    | D            | Windows 数据碟     | NTFS     | 60       |
| `/dev/sda3`    | 不要挂载     | Linux 根目录 (/)   | Ext3     | 50       |
| `/dev/sda5`    | 不要挂载     | 内存置换空间 swap  | swap     | 1        |
| `/dev/sda6`    | E            | Windows/Linux 共用 | vfat     | 其他所有 |

1. 先装 Windows XP
2. 安装 CentOS 7.x：grub 务必要安装到 MBR 上头。
3. 后续维护的注意事项
    1. Windows 环境中最好将 Linux 的根目录与 swap 取消挂载；的Linux系统就毁了。 (2)
    2. 你的 Linux 不可以随便的删除！ 因为 grub 会去读取 Linux 根目录下的 `/boot/`
      目录内容，如果你将 Linux 移除了，Windows 会无法开机。

新版：

| Linux 设备名 | Linux | Windows | 内容           | 文件系统 | 容量     |
| ------------ | ----- | ------- | -------------- | -------- | -------- |
| `/dev/vda1`  | /boot | -       | Linux 开机信息 | xfs      | 2GB      |
| `/dev/vda2`  | /     | -       | Linux 根目录   | xfs      | 50GB     |
| `/dev/vda3`  | -     | C       | Windows 系统盘 | NTFS     | 100GB    |
| `/dev/vda5`  | /data | D       | 共享数据       | vfat     | 剩余容量 |

### 3.3.2 进阶安装 CentOS 7.x 与 Windows 7

使用 ctrl+alt+f2 进入 shell:

```sh
# 创建 MBR 分区
parted /dev/vda mklabel msdos
# 创建 /boot
parted /dev/vda mkpart primary 1M 2G
# 创建 /
parted /dev/vda mkpart primary 2G 52G
# 创建 C
parted /dev/vda mkpart primary 52G 152G
# 创建扩展分区
parted /dev/vda mkpart extended 152G 100%
# 创建逻辑分区
parted /dev/vda mkpart logical 152G 100%
# 显示分区结果
parted /dev/vda print
```

### 3.3.3 救援 MBR 内的开机管理程序与设置多重开机菜单

- 修复 Linux 开机管理程序：
  
  放入 Linux 安装光盘，进入 Troubleshooting 模式，选择 "Rescue a CentOS system".

  这个工具会在 `/mnt/sysimage` 找到原来的系统，使用以下命令修复：

  ```sh
  $ chroot /mnt/sysimage
  $ grub2-install /dev/vda
  Installing for...
  $ exit
  $ reboot
  ```

- 修改开机菜单任务：先登录到 Linux 中

  ```sh
  vim /etc/grub.d/40_custom
  ```

  ```sh
  #!/bin/sh
  exec tail -n +3 $0
  # This file provides an easy way to add custom menu entries. Simply type the
  # menu entries you want to add after this comment. Be careful not to change
  # the 'exec tail' line above.
  menuentry "Windows 7" {
    set root='(hd0, 3)'
    chainloader +1
  }
  ```

  ```sh
  vim /etc/default/grub
  # 将默认的 5 秒改成 30 秒
  GRUB_TIMEOUT=30 
  ```

  ```sh
  grub2-mkconfig -o /boot/grub2/grub.cfg
  ```

- 后续维护的注意事项
  1. Windows 环境中将 Linux 根目录与 swap 取消挂载，防止误操作；
  2. Linux 不可随便删除，因为 grub 回去读取 /boot 目录的内容，移除 Linux 会导致 Windows
    也无法开机。

### 3.3.x 旧主机有两颗以上硬盘

整部个人计算机仅会有一个 MBR，即使有两颗硬盘。因为在 BIOS 里面指定的开机的装置，
只有第一个可开机装置内的 MBR 会被系统主动读取。所以理论上，你不会将 Windows
的开机管理程序安装到 `/dev/sda` 而将 Linux 安装到 `/dev/sdb`，而是要将 grub 安装到
`/dev/sda`，由 grub 来管理 Windows/Linux。

『我可以调整BIOS内的开机装置，使得要进入不同的操作系统时，就用不同的开机装置来开机，
如此一来应该就能够避免将 grub 安装到 /dev/sda 了吧？』因为 SATA
的装置档名是利用侦测的顺序来决定的，所以你如果这样调整来调整去的话，你的 SATA
装置档名可能会产生不同，这对於 linux的 运作会有问题，因此如果这样随时调整 BIOS 时，
可能还是会造成无法开机成功的问题！

spfdisk 这个开机管理程序可以替代 grub。只要在安装 Linux 的时候，grub 安装到开机磁区
(boot sector)，然后重新开机进入 Windows，以 spfdisk 来设定正确的开机选单。

spfdisk官网：<http://spfdisk.sourceforge.net/>

### 3.4.x 旧主机只有一颗硬盘

Windows/Linux 不能共存在同一个 partition 上。如果需要安装双系统，至少要有两个主分区。

## 3.5.x 关於大硬盘导致无法开机的问题

无法开机的问题：

```sh
# 前面是一些奇怪的提示字元啊！
grub> _
```

如果不幸发生了这样的问题，那么可能的主要原因是：

- 主板 BIOS 太旧，导致捉不到新硬盘；
- 硬盘容量太大，主板并不支援。

可能可以这样解决：

- 下载最新的 BIOS 档案并且更新；
- 将硬盘的 cylinders, heads, sectors 抄下来，进入 BIOS 内，
  将硬盘的型号以使用者设定的方式手动设定好。

还有一个最简单的解决方法：重新安装 Linux，并且在磁碟分割的地方，建立一个 100MB 左右的分割槽，
将他挂载到 `/boot` 这个挂载点。并且要注意，`/boot` 必须要在整个硬盘的最前面！例如，必须是
`/dev/hda1` 才行。

## 3.4 重点回顾

- 不论你要安装什么样的 Linux 操作系统角色，都应该要事先规划例如分割、开机管理程序等；
- 建议练习机安装时的磁碟分割能有 `/`, `/boot`, `/home`, `swap` 四个分割槽；
- 调整开机装置的顺序必须要重新开机并进入 BIOS 系统调整；
- 安装 CentOS 7.x 的模式至少有两种，分别是图形介面与文字介面；
- 若安装笔记本电脑时失败，可尝试在开机时加入『linux nofb apm=off acpi=off』
  来关闭省电功能；
- 安装过程进入分割后，请以『自订的分割模式』来处理自己规划的分割方式；
- 在安装的过程中，可以建立软件磁盘阵列 (software RAID)；
- 在安装的过程中，可以创建逻辑卷管理员 (LVM)；
- 一般要求 swap 应该要是 1.5~2 倍的实体内存量；
- 即使没有 swap 依旧能够安装与运作 Linux 操作系统；
- CentOS 7 默认使用 xfs 作为文件系统；
- 使用 MBR 时：CentOS 7.x 的开机管理程序为 grub，安装时最好选择安装置 MBR 中；
- 没有连上 Internet 时，可尝试关闭防火墙，但 SELinux 最好选择『强制』状态；
- 设定时不要选择启动 kdump，因为那是给核心开发者查阅当机数据的；
- 可加入时间服务器来同步化时间，台湾可选择 tock.stdtime.gov.tw 这一部；
- 尽量使用一般用户来操作 Linux，有必要再转身份成为 root 即可。

## 3.5 本章习题

## 3.6 参考资料与延伸阅读

## 3.7 针对本文的建议

<http://phorum.vbird.org/viewtopic.php?p=135157>
