# 第十九章 开机流程、模块管理与 loader

> <https://linux.vbird.org/linux_basic/centos7/0510osloader.php>

- [第十九章 开机流程、模块管理与 loader](#第十九章-开机流程模块管理与-loader)
  - [19.1 Linux 的开机流程分析](#191-linux-的开机流程分析)
    - [19.1.1 开机流程一览](#1911-开机流程一览)
    - [19.1.2 BIOS, boot loader 与 kernel 载入](#1912-bios-boot-loader-与-kernel-载入)
    - [19.1.3 第一个进程 systemd 及使用 default.target 进入开机程序分析](#1913-第一个进程-systemd-及使用-defaulttarget-进入开机程序分析)
    - [19.1.4 systemd 执行 sysinit.target 初始化系统、basic.target 准备系统](#1914-systemd-执行-sysinittarget-初始化系统basictarget-准备系统)
    - [19.1.5 systemd 启动 multi-user.target 下的服务](#1915-systemd-启动-multi-usertarget-下的服务)
    - [19.1.6 systemd 启动 graphical.target 下面的服务](#1916-systemd-启动-graphicaltarget-下面的服务)
    - [19.1.7 开机过程会用到的主要配置文件](#1917-开机过程会用到的主要配置文件)
  - [19.2 内核与内核模块](#192-内核与内核模块)
    - [19.2.1 内核模块与依赖性](#1921-内核模块与依赖性)
    - [19.2.2 内核模块的查看](#1922-内核模块的查看)
    - [19.2.3 内核模块的加载与移除](#1923-内核模块的加载与移除)
    - [19.2.4 内核模块的额外参数设置: /etc/modprobe.d/*conf](#1924-内核模块的额外参数设置-etcmodprobedconf)
  - [19.3 Boot Loader: Grub2](#193-boot-loader-grub2)
    - [19.3.1 boot loader 的两个 stage](#1931-boot-loader-的两个-stage)
    - [19.3.2 grub2 的配置文件 /boot/grub2/grub.cfg 初探](#1932-grub2-的配置文件-bootgrub2grubcfg-初探)
    - [19.3.3 grub2 的配置文件维护 /etc/default/grub 与 /etc/grub.d](#1933-grub2-的配置文件维护-etcdefaultgrub-与-etcgrubd)
    - [19.3.4 initramds 的重要性与创建新 initramfs 文件](#1934-initramds-的重要性与创建新-initramfs-文件)
    - [19.3.5 测试与安装 grub2](#1935-测试与安装-grub2)
    - [19.3.6 开机钱的额外功能修改](#1936-开机钱的额外功能修改)
    - [19.3.7 关于开机画面与终端机画面的图像显示方式](#1937-关于开机画面与终端机画面的图像显示方式)
    - [19.3.8 为个别菜单加上密码](#1938-为个别菜单加上密码)
  - [19.4 开机过程的问题解决](#194-开机过程的问题解决)
    - [19.4.1 忘记 root 密码的解决之道](#1941-忘记-root-密码的解决之道)
    - [19.4.2 直接开机就以 root 执行 bash 的方法](#1942-直接开机就以-root-执行-bash-的方法)
    - [19.4.3 因文件系统错误而无法开机](#1943-因文件系统错误而无法开机)
  - [19.5 重点回顾](#195-重点回顾)
  - [19.6 本章习题](#196-本章习题)
  - [19.7 参考资料与延伸阅读](#197-参考资料与延伸阅读)

## 19.1 Linux 的开机流程分析

### 19.1.1 开机流程一览

见目录

### 19.1.2 BIOS, boot loader 与 kernel 载入

- BIOS, 开机自检与 MBR/GPT
- Boot Loader 的功能
  - 提供菜单
  - 加载内核文件
  - 转交其他 loader
- 载入内核检测硬件与 initramfs 的功能
  - 内核会解压到内存中，并利用内核测试硬件
  - initramfs: 虚拟文件系统，在内存中仿真成根目录文件系统，并提供一个可以加载内核模块的程序，
    之后再调用 systemd 进行后续开机

![内核加载流程](images/19_1_2_osloader-flow-initramfs.jpg)

### 19.1.3 第一个进程 systemd 及使用 default.target 进入开机程序分析

- 常见的操作环境 target 与兼容 runlevel 的等级

  | SystemV    | systemd                             |
  | ---------- | ----------------------------------- |
  | init 0     | systemctl poweroff                  |
  | init 1     | systemctl rescue                    |
  | init [234] | systemctl isolate multi-user.target |
  | init 5     | systemctl isolate graphical.target  |
  | init 6     | systemctl reboot                    |

- systemd 的处理流程

### 19.1.4 systemd 执行 sysinit.target 初始化系统、basic.target 准备系统

- sysinit.target 初始化系统
  - 特殊文件系统设备的挂载
  - 特殊文件系统的启用
  - 开机过程的信息传递与动画执行
  - 日志式日志文件的使用
  - 加载额外的核心模块
  - 加载额外的核心参数
  - 启动系统的随机数产生器
  - 设置终端机字体
  - 启动动态设备管理员
- basic.target 准备系统
  - 加载 alsa 声卡驱动
  - 加载 firewalld 防火墙
  - 加载 CPU 未知量功能
  - 启动与设置 SELinux 的安全上下文
  - 将目前开机过程产生的信息写入到 `/var/log/dmesg`
  - 由 `/etc/sysconfig/modules/*.modules` 及 `/etc/rc.modules` 加载管理员指定模块
  - 加载 systemd 支持的 timer 功能

### 19.1.5 systemd 启动 multi-user.target 下的服务

- 兼容 system V 的 rc-local.service

  ```sh
  # 1. 先看一下 /etc/rc.d/rc.local 的權限，然後檢查 multi-user.target 有沒有這個服務
  [root@study ~]# ll /etc/rc.d/rc.local
  -rw-r--r--. 1 root root 473 Mar  6 13:48 /etc/rc.d/rc.local
  
  [root@study ~]# systemctl status rc-local.service
  rc-local.service - /etc/rc.d/rc.local Compatibility
  Loaded: loaded (/usr/lib/systemd/system/rc-local.service; static)
  Active: inactive (dead)
  
  [root@study ~]# systemctl list-dependencies multi-user.target | grep rc-local
  # 明明就有這個服務，但是 rc.local 不具有可執行 (x) 的權限，因此這個服務不會被執行
  
  # 2. 加入可執行權限後，再看一下 rc-local 是否可被啟用！
  [root@study ~]# chmod a+x /etc/rc.d/rc.local; ll /etc/rc.d/rc.local
  -rwxr-xr-x. 1 root root 473 Mar  6 13:48 /etc/rc.d/rc.local
  
  [root@study ~]# systemctl daemon-reload
  [root@study ~]# systemctl list-dependencies multi-user.target | grep rc-local
  ├─rc-local.service   # 這個服務確實被記錄到啟動的環境下囉！
  ```

- 提供 tty 界面与登录的服务

### 19.1.6 systemd 启动 graphical.target 下面的服务

切换回文本界面: `systemctl isolate multi-user.target`

### 19.1.7 开机过程会用到的主要配置文件

- 关于模块
  - `/etc/modules-load.d/*.conf`: 单纯要内核载入模块的位置
  - `/etc/modprobe.d/*.conf`: 可以加上模块参数的位置
- `/etc/sysconfig/*`
  - `authconfig`
  - `cpupower`
  - `firewalld`, `iptables-config`, `ip6tables-config`, `ebtables-config`
  - `network-scripts/`

## 19.2 内核与内核模块

- 内核: `/boot/vmlinuz` 或 `/boot/vmlinuz-version`
- 内核解压所需 RAM Disk: `/boot/initramfs` (`/boot/initramfs-version`)
- 内核模组: `/lib/modules/version/kernel` 或 `/lib/modules/$(uname -r)/kernel`
- 内核源码: `/usr/src/linux` 或 `/usr/src/kernels/`

### 19.2.1 内核模块与依赖性

内核模组目录 `/lib/modules/$(uname -r)/kernel` 中分几个子目录：

- arch
- crypto
- drivers
- fs
- lib
- net
- sound

内核使用 `/lib/modules/$(uname -r)/modules.dep` 记录模块依赖。

使用 `depmod` 可以创建该文件。

### 19.2.2 内核模块的查看

- `lsmod` 显示内容
  - Module: 模块名称
  - Size: 模块大小
  - Used by: 模块被其他模块的使用情况
- `modingo`: 查看模块信息

### 19.2.3 内核模块的加载与移除

- `insmod`: 手动加载一个完整的内核模块，但不会分析依赖
- `rmmod`: 移除内核模块
- `modprobe`: 自动加载模块

### 19.2.4 内核模块的额外参数设置: /etc/modprobe.d/*conf

## 19.3 Boot Loader: Grub2

### 19.3.1 boot loader 的两个 stage

- Stage 1: 执行 boot loader 主程序
- Stage 2: 加载配置文件 `/boot/grub2`

### 19.3.2 grub2 的配置文件 /boot/grub2/grub.cfg 初探

### 19.3.3 grub2 的配置文件维护 /etc/default/grub 与 /etc/grub.d

### 19.3.4 initramds 的重要性与创建新 initramfs 文件

### 19.3.5 测试与安装 grub2

### 19.3.6 开机钱的额外功能修改

### 19.3.7 关于开机画面与终端机画面的图像显示方式

### 19.3.8 为个别菜单加上密码

## 19.4 开机过程的问题解决

### 19.4.1 忘记 root 密码的解决之道

- 开机时按 `e` 进入编辑模式: 在 `linux16` 行末加上 `rd.break`, 之后 `[ctrl]+x` 开机

  ```sh
  Generating "/run/initramfs/rdsosreport.txt"

  Enter emergency mode. Exit the shell to continue.
  Type "journalctl" to view system logs.
  You might want to save "/run/initramfs/rdsosreport.txt" to a USB stick or
    /boot
  after mounting them and attach it to a bug report.
  
  switch_root:/#         # 無須輸入密碼即可取得 root 權限！
  switch_root:/# mount   # 檢查一下掛載點！一定會發現 /sysroot 才是對的！
  .....(前面省略).....
  /dev/mapper/centos-root on /sysroot type xfs (ro,relatime,attr,inode64,
    noquota)
  
  switch_root:/# mount -o remount,rw /sysroot # 要先讓它掛載成可讀寫！
  switch_root:/# chroot /sysroot              # 實際切換了根目錄所在，取回原先環境
  
  sh-4.2# echo "your_root_new_pw" | passwd --stdin root
  sh-4.2# touch /.autorelabel                  # 很重要！變回 SELinux 的安全本文～
  sh-4.2# exit
  
  switch_root:/# reboot 
  ```

  - chroot 目录：切到原先系统的根目录，也就是这里的 `/sysroot`
  - `./autorelabel`: 使系统开机时自动使用默认 SELinux type 重新写入 SELinux
    安全上下文到每个文件中

### 19.4.2 直接开机就以 root 执行 bash 的方法

- 开机时按 `e` 进入编辑模式: 在 `linux16` 行末加上 `init=/bin/bash`, 之后
  `[ctrl]+x` 开机

### 19.4.3 因文件系统错误而无法开机

`mount -o remount,rw /`，修改 `/etc/fstab` 或 使用 fsck 排查错误

## 19.5 重点回顾

## 19.6 本章习题

## 19.7 参考资料与延伸阅读
