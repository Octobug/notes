# 第二十四章 核心编译

> <https://linux.vbird.org/linux_basic/centos7/0540kernel.php>

## 目录

- [第二十四章 核心编译](#第二十四章-核心编译)
  - [目录](#目录)
  - [24.1 编译前的任务：认识内核与取得内核源代码](#241-编译前的任务认识内核与取得内核源代码)
    - [24.1.1 什么是内核（Kernel）](#2411-什么是内核kernel)
    - [24.1.2 更新内核的目的](#2412-更新内核的目的)
    - [24.1.3 内核的版本](#2413-内核的版本)
    - [24.1.4 内核源代码的获取方式](#2414-内核源代码的获取方式)
    - [24.1.5 内核源代码的解压缩/安装/观察](#2415-内核源代码的解压缩安装观察)
  - [24.2 内核编译的前处理与内核功能选择](#242-内核编译的前处理与内核功能选择)
    - [24.2.1 硬件环境检视与核心功能要求](#2421-硬件环境检视与核心功能要求)
    - [24.2.2 保持干净源代码：make mrproper](#2422-保持干净源代码make-mrproper)
    - [24.2.3 开始挑选内核功能：make XXconfig](#2423-开始挑选内核功能make-xxconfig)
    - [24.2.4 内核功能详细选择](#2424-内核功能详细选择)
  - [24.3 内核的编译与安装](#243-内核的编译与安装)
    - [24.3.1 编译内核与内核模块](#2431-编译内核与内核模块)
    - [24.3.2 实际安装模块](#2432-实际安装模块)
    - [24.3.3 开始安装新内核与多重内核菜单（grub）](#2433-开始安装新内核与多重内核菜单grub)
  - [24.4 额外（单一）内核模块编译](#244-额外单一内核模块编译)
    - [24.4.1 编译前注意事项](#2441-编译前注意事项)
    - [24.4.2 单一模块编译](#2442-单一模块编译)
    - [24.4.3 内核模块管理](#2443-内核模块管理)
    - [24.5 以最新内核版本编译 CentOS 7.x 的内核](#245-以最新内核版本编译-centos-7x-的内核)
  - [24.6 重点回顾](#246-重点回顾)
  - [24.7 本章习题](#247-本章习题)
  - [24.8 参考资料与延伸阅读](#248-参考资料与延伸阅读)

## 24.1 编译前的任务：认识内核与取得内核源代码

### 24.1.1 什么是内核（Kernel）

- Kernel: 管理硬件的软件，包含驱动硬件的检测程序与驱动模块
  - 内核文件通常为 `/boot/vmlinuz-xxx`
- 内核模块（Kernel module）的用途：动态载入模块，而不需要变动内核
  - 内核模块通常在 `/lib/modules/$(uname -r)/kernel/` 中
- 自制内核 - 内核编译
- 关于驱动程序 - 是厂商的责任还是内核的责任？
  - 是硬件尝试的责任

### 24.1.2 更新内核的目的

- Linux 内核特色，与默认内核对终端用户的角色
- 内核编译的可能目的
  - 新功能需求
  - 原本的内核太过臃肿
  - 与硬件搭配的稳定性
  - 其他需求，如嵌入式系统

### 24.1.3 内核的版本

很多软件会依赖某些版本内核的功能，升级内核会导致这部分软件用不了。因此最好只在某个 LTS
版本内升级。

### 24.1.4 内核源代码的获取方式

- distribution 提供的内核源代码文件
  - CentOS: <http://vault.centos.org/>
- 获取最新的稳定版内核源代码
  - 内核官网: <https://www.kernel.org/>
- 保留原本设置：利用 patch 升级内核源代码
  - patch 必须要连续

### 24.1.5 内核源代码的解压缩/安装/观察

- 内核源代码的解压与放置目录: `/usr/src/kernels`
- 内核源代码下的次目录
  - arch: 硬件架构
  - block: 与块设备相关的设置数据
  - crypto: 支持的加密技术
  - documentation: 说明文档
  - drivers: 硬件驱动
  - firmware: 旧式硬件的固件
  - fs: 支持的文件系统
  - include: 可以让其他程序调用的 header 文件
  - init: 内核初始化的定义功能，包括挂载与 init 进程的调用等
  - ipc: 定义 Linux 系统内进程间通信
  - kernel: 定义内核的进程、内核状态、线程、进程调度、进程信号等
  - lib: 函数库
  - mm: 与内存有关的数据
  - net: 与网络有关的数据
  - security: 包括 selinux 等在内的安全设置
  - sound: 与音效相关的模块
  - virt: 与虚拟化相关的信息，如 KVM (Kernel base Virtual Machine)

## 24.2 内核编译的前处理与内核功能选择

### 24.2.1 硬件环境检视与核心功能要求

### 24.2.2 保持干净源代码：make mrproper

```sh
# 第一次执行编译前要清理编译过程的目标文件及内核配置文件：
cd /usr/src/kernels/linux-3.10.89/
make mrproper
# 之后要清理只需
make clean
```

### 24.2.3 开始挑选内核功能：make XXconfig

`/boot/config-4.15.0-167-generic` 文件正是内核功能列表文件。

- make menuconfig
- make oldconfig: 根据 `./config` 文件，只列出新版本内核的新功能提供选择
- make xconfig: qt 图形化界面
- make gconfig: gtk 图形化界面
- make config: 最旧式的方式

功能挑选：

- 一定要的功能，直接编译进内核
- 可能会用到的功能，尽量编译成模块
- 不了解的保持默认值，或编译成模块

### 24.2.4 内核功能详细选择

- General setup: 与 Linux 最相关的程序互动、内核版本说明
- loadable module + block layer: 要支持动态内核模块必须启用 loadable module
- CPU 类型与功能选择
- 电源管理功能
- 总线（bus）选项
- 编译后可执行文件的格式
- 内核的网络功能
- 各项设备的驱动程序
- 文件系统的支持
- 内核hacking、信息安全、密码应用
- 虚拟化与函数库

## 24.3 内核的编译与安装

### 24.3.1 编译内核与内核模块

基本操作：

```sh
[root@study linux-3.10.89]# make vmlinux  <==未經壓縮的核心
[root@study linux-3.10.89]# make modules  <==僅核心模組
[root@study linux-3.10.89]# make bzImage  <==經壓縮過的核心(預設)
[root@study linux-3.10.89]# make all      <==進行上述的三個動作
```

常用操作：

```sh
[root@study linux-3.10.89]# make -j 4 clean    <==先清除暫存檔
[root@study linux-3.10.89]# make -j 4 bzImage  <==先編譯核心
[root@study linux-3.10.89]# make -j 4 modules  <==再編譯模組
[root@study linux-3.10.89]# make -j 4 clean bzImage modules  <==連續動作！
```

### 24.3.2 实际安装模块

重复编译时模块目录会产生冲突：

- 将旧模块目录更名，再安装新的内核模块到目标目录
- 在 make menuconfig 时，把 general setup 内的 local version 改成新的名称

```sh
Setup is 16752 bytes (padded to 16896 bytes).
System is 4404 kB
CRC 30310acf
Kernel: arch/x86/boot/bzImage is ready  (#1)

[root@study linux-3.10.89]# ll arch/x86/boot/bzImage
-rw-r--r--. 1 root root 4526464 Oct 20 09:09 arch/x86/boot/bzImage
```

### 24.3.3 开始安装新内核与多重内核菜单（grub）

- 内核文件：`/usr/src/kernels/linux-3.10.89/arch/x86/boot/bzImage`
- 移动内核到 `/boot` 且保留旧内核文件: 确保仍然可以开机；内核文件名通常以 vmlinuz 开头
- 创建相对应的 Initial Ram Disk（initrd）
- 编辑开机菜单（grub）: grub2-mkconfig -o /boot/grub2/grub.cfg
- 重新以新内核开机、测试、修改

## 24.4 额外（单一）内核模块编译

### 24.4.1 编译前注意事项

- `/lib/modules/$(uname -r)/build`
- `/lib/modules/$(uname -r)/source`
- `/lib/modules/$(uname -r)/modules.dep`
- `modprobe` 用于载入模块
- `kernel-devel`

### 24.4.2 单一模块编译

- 硬件开发商提供的额外模块
- 利用旧有的内核源代码进行编译

### 24.4.3 内核模块管理

需要了解内核、内核模块、驱动程序模块、内核源代码、头文件、函数库等等。

- modprobe
- `/etc/modprobe.conf`

### 24.5 以最新内核版本编译 CentOS 7.x 的内核

1. 先从 ELRepo 下载不含源代码的 SRPM 文件，并安装该文件
2. 从 www.kernel.org 下载满足 ELRepo 网站所需要的内核版本
3. 修改内核功能
4. 通过 SRPM 的 rpmbuild 重新编译打包内核 

```sh
1. 先下載 ELRepo 上面的 SRPM 檔案！同時安裝它：
[root@study ~]# wget http://elrepo.org/linux/kernel/el7/SRPMS/kernel-ml-4.2.3-1.el7.elrepo.nosrc.rpm
[root@study ~]# rpm -ivh kernel-ml-4.2.3-1.el7.elrepo.nosrc.rpm

2. 根據上述的檔案，下載正確的核心原始碼：
[root@study ~]# cd rpmbuild/SOURCES
[root@study SOURCES]# wget https://cdn.kernel.org/pub/linux/kernel/v4.x/linux-4.2.3.tar.xz
[root@study SOURCES]# ll -tr
.....(前面省略).....
-rw-r--r--. 1 root root 85523884 Oct  3 19:58 linux-4.2.3.tar.xz  # 核心原始碼
-rw-rw-r--. 1 root root      294 Oct  3 22:04 cpupower.service
-rw-rw-r--. 1 root root      150 Oct  3 22:04 cpupower.config
-rw-rw-r--. 1 root root   162752 Oct  3 22:04 config-4.2.3-x86_64 # 主要的核心功能

3. 修改核心功能設定：
[root@study SOURCES]# vim config-4.2.3-x86_64
# 大約在 5623 行找到底下這一行，並在底下新增一行設定值！
# CONFIG_VFIO_PCI_VGA is not set
CONFIG_VFIO_PCI_VGA=y

[root@study SOURCES]# cd ../SPECS
[root@study SPECS]# vim kernel-ml-4.2.spec
# 大概在 145 左右找到底下這一行：
Source0: ftp://ftp.kernel.org/pub/linux/kernel/v4.x/linux-%{LKAver}.tar.xz
# 將它改成如下的模樣：
Source0: linux-%{LKAver}.tar.xz

4. 開始編譯並打包：
[root@study SPECS]# rpmbuild -bb kernel-ml-4.2.spec
# 接下來會有很長的一段時間在進行編譯行為，鳥哥的機器曾經跑過兩個小時左右才編譯完！
# 所以，請耐心等候啊！
Wrote: /root/rpmbuild/RPMS/x86_64/kernel-ml-4.2.3-1.el7.centos.x86_64.rpm
Wrote: /root/rpmbuild/RPMS/x86_64/kernel-ml-devel-4.2.3-1.el7.centos.x86_64.rpm
Wrote: /root/rpmbuild/RPMS/x86_64/kernel-ml-headers-4.2.3-1.el7.centos.x86_64.rpm
Wrote: /root/rpmbuild/RPMS/x86_64/perf-4.2.3-1.el7.centos.x86_64.rpm
Wrote: /root/rpmbuild/RPMS/x86_64/python-perf-4.2.3-1.el7.centos.x86_64.rpm
Wrote: /root/rpmbuild/RPMS/x86_64/kernel-ml-tools-4.2.3-1.el7.centos.x86_64.rpm
Wrote: /root/rpmbuild/RPMS/x86_64/kernel-ml-tools-libs-4.2.3-1.el7.centos.x86_64.rpm
Wrote: /root/rpmbuild/RPMS/x86_64/kernel-ml-tools-libs-devel-4.2.3-1.el7.centos.x86_64.rpm
```

之后再

```sh
[root@study ~]# yum install /root/rpmbuild/RPMS/x86_64/kernel-ml-4.2.3-1.el7.centos.x86_64.rpm
[root@study ~]# reboot

[root@study ~]# uname -a
Linux study.centos.vbird 4.2.3-1.el7.centos.x86_64 #1 SMP Wed Oct 21 02:31:18 
    # CST 2015 x86_64
x86_64 x86_64 GNU/Linux
```

## 24.6 重点回顾

- 其實核心就是系統上面的一個檔案而已，這個檔案包含了驅動主機各項硬體的偵測程式與驅動模組；
- 上述的核心模組放置於：`/lib/modules/$(uname -r)/kernel/`
- 『驅動程式開發』的工作上面來說，應該是屬於硬體發展廠商的問題
- 一般的使用者，由於系統已經將核心編譯的相當的適合一般使用者使用了，因此一般入門的使用者，
  基本上，不太需要編譯核心
- 編譯核心的一般目的：新功能的需求、原本的核心太過臃腫、與硬體搭配的穩定性、其他需求
  (如嵌入式系統)
- 編譯核心前，最好先瞭解到您主機的硬體，以及主機的用途，才能選擇好核心功能；
- 編譯前若想要保持核心原始碼的乾淨，可使用 make mrproper 來清除暫存檔與設定檔；
- 挑選核心功能與模組可用 make 配合：menuconfig, oldconfig, xconfig, gconfig 等等
- 核心功能挑選完畢後，一般常見的編譯過程為：make bzImage, make modules
- 模組編譯成功後的安裝方式為： make modules_install
- 核心的安裝過程中，需要移動 bzImage 檔案、建立 initramfs 檔案、重建 grub.cfg 等動作；
- 我們可以自行由硬體開發商之官網下載驅動程式來自行編譯核心模組！

## 24.7 本章习题

簡單說明核心編譯的步驟為何？

1. 先下載核心原始碼，可以從 <http://www.kernel.org> 或者是 distributions 的 SRPM
   來著手；
2. 以下以 Tarball 來處理，解開原始碼到 `/usr/src/kernels` 目錄下；
3. 先進行舊資料刪除的動作：『make mrproper』；
4. 開始挑選核心功能，可以利用『make menuconfig』、『make oldconfig』、『make gconfig』
   等等；
5. 清除過去的中間暫存檔資料：『make clean』
6. 開始核心檔案與核心模組的編譯：『make bzImage』、『make modules』
7. 開始核心模組的安裝：『make modules_install』
8. 開始核心檔案的安裝，可以使用的方式有：『make install』或者是透過手動的方式複製核心檔案到
   `/boot/` 當中；
9. 建立 initramfs 檔案；
10. 使用 grub2-mkconfig 修改 `/boot/grub2/grub.cfg` 檔案；

如果你利用新編譯的核心來操作系統，發現系統並不穩定，你想要移除這個自行編譯的核心該如何處理？

1. 重新開機，並使用舊的穩定的核心開機！
2. 此時才可以將新版核心模組刪除： `rm -rf /lib/modules/3.10.89vbird`
3. 刪除掉 `/boot` 裡面的新核心：
   `rm /boot/vmlinuz-3.10.89vbird /boot/initramfs-3.10.89vbird.img ...`
4. 重建 `grub.cfg`: `grub2-mkconfig -o /boot/grub2/grub.cfg`

## 24.8 参考资料与延伸阅读
