# 第一章 Linux 是什么与如何学习

> <http://cn.linux.vbird.org/linux_basic/0110whatislinux.php>
>
> <http://cn.linux.vbird.org/linux_basic/0120howtolinux.php>

## 目录

- [第一章 Linux 是什么与如何学习](#第一章-linux-是什么与如何学习)
  - [目录](#目录)
  - [1.1 Linux 是什么](#11-linux-是什么)
    - [1.1.1 Linux 是什么？操作系统/应用程序？](#111-linux-是什么操作系统应用程序)
      - [操作系统分层（右内到外）](#操作系统分层右内到外)
    - [1.1.2 Linux 之前，Unix 的历史](#112-linux-之前unix-的历史)
    - [1.1.3 关于 GNU 计划、自由软件与开放源代码](#113-关于-gnu-计划自由软件与开放源代码)
  - [1.2 Torvalds 的 Linux 发展](#12-torvalds-的-linux-发展)
    - [1.2.1 与 Minix 之间](#121-与-minix-之间)
    - [1.2.2 对 386 硬件的多任务测试](#122-对-386-硬件的多任务测试)
    - [1.2.3 初次释出 Linux 0.02](#123-初次释出-linux-002)
    - [1.2.4 Linux 的发展：虚拟团队的产生](#124-linux-的发展虚拟团队的产生)
    - [1.2.5 Linux 的核心版本](#125-linux-的核心版本)
    - [1.2.6 Linux distributions](#126-linux-distributions)
    - [1.x Linux 的特色](#1x-linux-的特色)
    - [1.x.1 Linux 的特色](#1x1-linux-的特色)
    - [1.x.2 Linux 的优缺点](#1x2-linux-的优缺点)
    - [1.x.3 关于授权](#1x3-关于授权)
  - [1.3 Linux 当前应用的角色](#13-linux-当前应用的角色)
    - [1.3.1 企业环境的利用](#131-企业环境的利用)
    - [1.3.2 个人环境的使用](#132-个人环境的使用)
    - [1.3.3 云端运用](#133-云端运用)
  - [1.x 鸟哥的 Linux 苦难经验全都录](#1x-鸟哥的-linux-苦难经验全都录)
    - [1.x.1 鸟哥的 Linux 学习之路](#1x1-鸟哥的-linux-学习之路)
    - [1.x.2 学习心态的分别](#1x2-学习心态的分别)
  - [1.4 Linux 该如何学习](#14-linux-该如何学习)
    - [1.4.0 X window 的学习](#140-x-window-的学习)
    - [1.4.1 从头学习 Linux 基础](#141-从头学习-linux-基础)
    - [1.4.2 选择一本易读的工具书](#142-选择一本易读的工具书)
    - [1.4.3 实践再实践](#143-实践再实践)
    - [1.4.4 发生问题怎么处理啊？建议流程是这样...](#144-发生问题怎么处理啊建议流程是这样)
  - [1.4.5 鸟哥的建议(重点在 solution 的学习)](#145-鸟哥的建议重点在-solution-的学习)
  - [1.5 重点回顾](#15-重点回顾)
  - [1.6 本章习题](#16-本章习题)
  - [1.7 参考数据与延伸阅读](#17-参考数据与延伸阅读)

## 1.1 Linux 是什么

### 1.1.1 Linux 是什么？操作系统/应用程序？

#### 操作系统分层（右内到外）

1. 硬件
2. 内核
3. 系统调用
4. 应用程序

其中 2.内核 + 3.系统调用 即是操作系统。

### 1.1.2 Linux 之前，Unix 的历史

- 1969 年以前：一个伟大的梦想--Bell,MIT 与 GE 的『Multics』系统

  早期计算机只支持批处理，且只能使用卡片阅读机、打印机交互。

  1960 年代初期麻省理工学院 (MIT) 发展了『兼容分时系统 (Compatible Time-Sharing
  System, CTSS)』，它可以让大型主机透过提供数个终端机 (terminal) 以联机进入主机，
  利用主机的资源进行运算工作。

  1965 年前后， 由贝尔实验室 (Bell)、麻省理工学院 (MIT)及通用电气公司 (GE) 共同发起了
  Multics (注：Multics 有复杂、多数的意思存在。) 的计划， Multics
  计划的目的是想要让大型主机可以达成提供 300 个以上的终端机联机使用的目标。

- 1969 年：Ken Thompson 的小型 file server system

  Ken Thompson 以汇编语言 (Assembler) 写出了运行于 DEC (Digital Equipment
  Corporation) PDP-7 的核心程序，同时包括一些核心工具程序，以及一个小小的文件系统。
  那个系统就是 Unix 的原型。Thompson 将 Multics 庞大的复杂系统简化了不少，
  于是同实验室的朋友都戏称这个系统为：Unics。(当时尚未有 Unix 的名称)

  Thompson 的这个文件系统有两个重要的概念，分别是：

  - 所有的程序或系统设备都是文件；
  - 所有程序只有一个目的，且要有效地完成目标。

- 1973年：Unix 正式诞生，Ritchie 等人以 C 语言写出第一个正式 Unix 核心

  当时现成的高阶程序语言 B 语言所编译出来的内核性能不是很好。后来 Dennis Ritchie 将
  B 语言改写成 C 语言，再以 C 语言改写编译 Unics 的核心， 最后发行 Unix 的正式版本！

- 1977 年：重要的 Unix 分支--BSD 的诞生
- 1979 年：重要的 System V 架构与版权声明
  
  AT&T 推出 System V 第七版 Unix，支持 x86 架构的个人计算机系统。但回收了 Unix 源码版权。

- 1984 年之一：x86 架构的 Minix 操作系统诞生
  
  由于 Unix 版权问题，Andrew Tanenbaum 开发 Minix (Mini Unix)。

- 1984 年之二：GNU 计划与 FSF 基金会的成立

  Richard Mathew Stallman 在 1984 年发起 GNU 计划。
  
  - 一个分享的环境：RMS 发现自己一个人开发自由软件速度太慢，所以想成立一个开放的团体共同努力。
  - 使用 Unix 开发阶段：Lisp 操作系统是专利软件，所以 RMS 转而使用架构开放的 Unix。
  - GNU (GNU's Not Unix) 计划的推进：建立一个自由、开放的 Unix 操作系统 (Free Unix)。
    从重写 Unix 工具软件到重写 C 语言编译器 gcc，到成立自由软件基金会 (FSF, Free
    Software Foundation)。

- GNU 的通用公共许可证：为了避免 GNU 所开发的自由软件被其他人所利用而成为专利软件，
  所以他与律师草拟了有名的通用公共许可证 (General Public License, GPL)，并且称呼它为
  copyleft (相对于专利软件的 copyright)。GNU 所开发的几个重要软件，如：

  - Emacs
  - GNU C (GCC)
  - GNU C Library (glibc)
  - Bash shell

- 1988 年：图形接口 XFree86 计划，所谓 XFree86 其实是 X Window System + Free + x86
  的整合名称。
  
- 1991 年：芬兰大学生 Linus Torvalds 的一则简讯

### 1.1.3 关于 GNU 计划、自由软件与开放源代码

- 自由软件的活动：将软件与其源码一并开放
- 自由软件的版权 GNU GPL：版权制度是促进社会进步的手段，版权本身不是自然权力。
- 自由 (Free) 的真谛：自由软件的重点并不是指『免费』，而是指具有『自由度, freedom』的软件，
  RMS 进一步说明了自由度的意义：使用者可以自由地执行、复制、再发行、学习、修改与强化自由软件。
- 自由软件与商业行为：提供售后服务

## 1.2 Torvalds 的 Linux 发展

### 1.2.1 与 Minix 之间

### 1.2.2 对 386 硬件的多任务测试

1. 程序 A 输出 A
2. 程序 B 输出 B
3. 程序 C 切换程序 A 与程序 B

### 1.2.3 初次释出 Linux 0.02

Hello everybody out there using minix-  
I'm doing a (free) operation system (just a hobby,  
won't be big and professional like gnu) for 386(486) AT clones.  

I've currently ported bash (1.08) and gcc (1.40),  
and things seem to work. This implies that i'll get  
something practical within a few months, and I'd like to know  
what features most people want. Any suggestions are welcome,  
but I won't promise I'll implement them :-)

遵守 POSIX 规范。

### 1.2.4 Linux 的发展：虚拟团队的产生

- 单一个人维护阶段
- 广大志愿者加入阶段
- 核心功能细部分工发展阶段

### 1.2.5 Linux 的核心版本

Linux的核心版本编号有点类似如下的样子：

```sh
2.6.18-92.el5 
主版本.次版本.释出版本-修改版本
```

- 主、次版本为奇数：发展中版本(development)

  如 2.5.xx，这种核心版本主要用在测试与发展新功能，所以通常这种版本仅有核心开发工程师会使用。
  如果有新增的核心程序代码，会加到这种版本当中，等到众多工程师测试没问题后，
  才加入下一版的稳定核心中；

- 主、次版本为偶数：稳定版本(stable)

  如 2.6.xx，等到核心功能发展成熟后会加到这类的版本中，主要用在一般家庭计算机以及企业版本中。
  重点在于提供使用者一个相对稳定的 Linux 作业环境平台。

### 1.2.6 Linux distributions

- 可完全安装的 Linux 发布套件：内核 + 应用软件 + 工具 + 文档
- 各大 Linux Distributions 的主要异同：支持标准！
  - Linux Standard Base (LSB): <https://wiki.linuxfoundation.org/lsb/start>
  - Filesystem Hierarchy Standard (FHS): <https://refspecs.linuxfoundation.org/FHS_3.0/fhs/index.html>
- 选择适合你的 Linux distribution

### 1.x Linux 的特色

### 1.x.1 Linux 的特色

- 自由与开放的使用与学习环境
- 配置要求低
- 核心功能强大而稳定
- 独立作业

### 1.x.2 Linux 的优缺点

- 优点
  - 稳定的系统
  - 免费或少许费用
  - 安全性、漏洞的快速修补
  - 多任务、多使用者
  - 使用者与群组的规划
  - 相对比较不耗资源的系统
  - 适合需要小核心程序的嵌入式系统
  - 整合度佳且多样的图形用户接口 (GUI)
- 缺点
  - 没有特定的支持厂商
  - 游戏的支持度不足
  - 专业软件的支持度不足
  - 教育训练作的还不够好

### 1.x.3 关于授权

- Open Source (开放源码)
- Close Source
  - Freeware
  - Shareware

## 1.3 Linux 当前应用的角色

### 1.3.1 企业环境的利用

- 网络服务器
- 关键任务的应用 (金融数据库、大型企业网管环境)
- 学术机构的高性能运算任务

### 1.3.2 个人环境的使用

- 桌面计算机
- 手持系统 (PDA、手机)
- 嵌入式系统

### 1.3.3 云端运用

所谓“虚拟化”指的是：在一部实体主机上仿真出多个逻辑上完全独立的硬件，
基于这些虚拟硬件之上安装一部逻辑上完全独立的操作系统。

- 云程序
- 端设备

## 1.x 鸟哥的 Linux 苦难经验全都录

### 1.x.1 鸟哥的 Linux 学习之路

- 接触 Linux 的原因

  大约在 1999 年，鸟哥因为学业上的需要，『被迫』学习 Unix 系统。那个时候 Sun Unix
  不是一般人玩得起的，所以需要替代方案。这个替代方案就是 Linux。

- 错误的学习方针阶段

  舍弃命令行模式，直接使用了 X-Window；主机开了多少 ports/services 并不清楚...

- 恶梦的开始.....

  由于使用了 X-Window，机器性能被 GUI 消耗了不少，导致服务卡顿；使用纯命令行之后性能变好；
  不久后服务器被入侵。

- 一个贵人的出现

  上网搜寻找到 [Study Area (酷学园)](http://www.study-area.org)，并学习站长网中人
  (netman) 提供的内容。

- 撰写文件的有趣经验

  为了让自己在实验室的努力不被学弟妹所搞烂，所以开始撰写 FAQ 文件。越写越发现自己懂得少，
  於是乎就越写越多，数据也越查阅多，才有了『鸟哥的 Linux 私房菜』网站。

- 鸟哥的忠言，希望不会逆耳

  鸟哥提出这本经验谈的书籍最主要的目的：『让想要学习 Linux
  的玩家可以快速且以较为正确的心态来进入 Linux 的世界！』

### 1.x.2 学习心态的分别

- 架不架站有所谓：Linux 强项是网络服务方面，而 Windows 赢在使用者界面友好。
- 只是图形介面，可以吗：No，图形化软件为了方便使用者，常常自己加入一些设定，
  但是这些设定往往是因地制宜的，所以反而常常会导致架设的网站无法正常工作。
- 学习 Linux 还是学习 Distributions：直接学习一些 Linux 的基本技巧，
  具备找出不同版本之间的差异性的能力。

## 1.4 Linux 该如何学习

### 1.4.0 X window 的学习

目前的 Linux distribution 绝大部分预设就是以 Desktop 的角度来安装所需要的软件，也就是说，
只要将 Linux 安装好，接下来就能够进入 Linux 桌面了，根本就不需要什么学习。

鸟哥建议的 distributions 有：

- Ubuntu
- OpenSuSE
- Fedora
- Mandriva

### 1.4.1 从头学习 Linux 基础

1. 计算机概论与硬件相关知识
2. 先从 Linux 的安装与指令学起
3. Linux 操作系统的基础技能
4. 务必学会 vi 编辑器
5. Shell 与 Shell Script 的学习
6. 一定要会软件管理
7. 网络基础

### 1.4.2 选择一本易读的工具书

### 1.4.3 实践再实践

### 1.4.4 发生问题怎么处理啊？建议流程是这样...

1. 在自己的主机/网路数据库上查询 How-To 或 FAQ

    - Linux 自身的文档 `/usr/share/doc`
    - The Linux Documentation Project：<http://www.tldp.org/>

2. 注意命令行输出，自行解决疑难杂症：

    一般而言，Linux 在下达指令的过程当中，或者是 log file 里就可以自己查得错误资讯了，
    举个例子：

    ```sh
    [root@linux ~]# ls -l /vbird
    ls: /vbird: No such file or directory
    ```

    如果是网路服务的问题，请到 `/var/log/` 查阅 log file。

3. 搜寻过后，注意网路礼节，讨论区大胆的发言吧

4. Netman 大大给的建议：

    - **不要动不动就直接关机或 reset**。在 Windows 里面，程式有问题时，
      如果可能的话先将所有其它程式保存并结束，然后尝试按救命三键 (Ctrl+Alt+Delete)，
      将有问题的程式『结束工作』，看看能不能恢复系统。
    - **有系统地设计文件目录**。不要随便到处保存文件以至以后不知道放哪里了，
      或找到文件也不知道为何物。
    - **养成做记录的习惯**。把错误信息和引发状况以及解决方法记录清楚，同时最后归类及定期整理。
    - 在网路上看到任何好文章，可以为自己留一份copy，同时定好题目，归类存档。
    - 作为一个使用者，人要迁就机器；做为一个开发者，要机器迁就人。
    - 学写 script 的确没设定 server 那么好玩，不过以我自己的感觉是：关键是会得『偷』，
      偷了会得改，改了会得变，变则通矣。
    - 在 Windows 里面，设定不好设备，您可以骂它；在 Linux 里面，如果设定好设备了，
      您得要感激它！

## 1.4.5 鸟哥的建议(重点在 solution 的学习)

学习的原动力：

- 成就感
- 兴趣

方法：

- 建立兴趣
- 成就感
- 协助回答问题
- 参与讨论

## 1.5 重点回顾

- 计算机主要以二进制作为单位，而目前常用的磁盘容量单位为 bytes，其单位换算为
  `1Byte = 8bits`，其他的以 1024 为其倍数，如 `1GByte=1024MBytes`等等。
- 操作系统 (Operation System) 主要在管理与驱动硬件，因此必须要能够管理内存、管理装置、
  负责行程管理以及系统呼叫等等。因此，只要能够让硬件准备妥当 (Ready) 的情况，
  就是一个阳春的操作系统了。
- 最阳春的操作系统仅在驱动与管理硬件，而要使用硬件时，就得需要透过应用软件或者是壳程序 (shell)
  的功能，来呼叫操作系统操纵硬件工作。因此，目前称为操作系统的，除了上述功能外，
  通常已经包含了日常工作所需要的应用软件在内了。
- Unix 的前身是由贝尔实验室 (Bell lab.) 的 Ken Thompson 利用汇编语言写成的，后来在
  1971-1973 年间由 Dennis Ritchie 以 C 程序语言进行改写，才称为 Unix。
- 1977 年由 Bill Joy 释出 BSD (Berkeley Software Distribution)，这些称为 Unix-like
  的操作系统。
- 1984 年由 Andrew Tanenbaum 制作出 Minix 操作系统，该系统可以提供原始码以及软件；
- 1984 年由 Richard Stallman 提倡 GNU 计划，倡导自由软件 (Free software)，
  强调其软件可以『自由的取得、复制、修改与再发行』，并规范出 GPL 授权模式，任何 GPL
  (General Public License) 软件均不可单纯仅贩卖其软件，也不可修改软件授权。
- 1991 年由芬兰人 Linus Torvalds 开发出 Linux 操作系统。简而言之，Linux
  成功的地方主要在于：Minix (Unix), GNU, Internet, POSIX 及虚拟团队的产生。
- Linux 本身就是个最阳春的操作系统，其开发网站设立在 <http://www.kernel.org>，
  我们亦称 Linux 操作系统最底层的数据为『核心 (Kernel)』。
- 目前 Linux 核心的发展分为两种版本，分别是稳定版本的偶数版，如 2.6.X，
  适合于商业与家用环境使用； 一种是发展中版本的奇数版如 2.5.X 版，适合开发特殊功能的环境。
- Linux distributions 的组成含有：『Linux Kernel + Free Software + Documentations
  (Tools) + 可完全安装的程序』所制成的一套完整的系统。
- Linux在企业应用方面，著重於『网路服务器』、『关键任务的应用 (金融数据库、大型企业网管环境)』
  及『高效能运算』等任务；
- Linux 在个人环境的使用上，著重於：桌面计算机、手持系统 (PDA、手机)、嵌入式设备
  (如家电用品等)；
- Linux distributions 有针对桌面计算机所开发的，例如 Ubuntu, OpenSuSE 及 Fedora 等等，
  为学习 X Window 的好工具；
- 有心朝 Linux 学习者，应该多接触文字介面 (shell) 的环境，包括正规表示法、
  管线命令与资料流重导向，最好都要学习！最好连 shell script 都要有能力自行撰写；
- 『实作』是学习 Linux 的最佳方案，空读书，遇到问题也不见得能够自己处理的！
- 学习 Linux 时，建立兴趣、建立成就感是很重要的，另外，协助回答问题、
  参与社群活动也是增加热情的方式！
- Linux 文件计画的网站在：<http://www.tldp.org>

## 1.6 本章习题

1. `uname`

## 1.7 参考数据与延伸阅读
