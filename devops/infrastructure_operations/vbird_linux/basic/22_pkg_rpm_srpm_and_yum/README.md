# 第二十二章 软件安装：RPM, SRPM 与 YUM 功能

> <https://linux.vbird.org/linux_basic/centos7/0520rpm_and_srpm.php>

## 目录

- [第二十二章 软件安装：RPM, SRPM 与 YUM 功能](#第二十二章-软件安装rpm-srpm-与-yum-功能)
  - [目录](#目录)
  - [22.1 软件管理器简介](#221-软件管理器简介)
    - [22.1.1 Linux 界的两大主流: RPM 与 DPKG](#2211-linux-界的两大主流-rpm-与-dpkg)
    - [22.1.2 什么是 RPM 与 SRPM](#2212-什么是-rpm-与-srpm)
    - [22.1.3 什么是 i386, i586, i686, noarch, x86_64](#2213-什么是-i386-i586-i686-noarch-x86_64)
    - [22.1.4 RPM 的优点](#2214-rpm-的优点)
    - [22.1.5 RPM 依赖的克服方式：yum 在线升级](#2215-rpm-依赖的克服方式yum-在线升级)
  - [22.2 RPM 软件管理程序: rpm](#222-rpm-软件管理程序-rpm)
    - [22.22.1 RPM 默认安装路径](#22221-rpm-默认安装路径)
    - [22.2.2 RPM 安装 (install)](#2222-rpm-安装-install)
    - [22.2.3 RPM 升级与更新（upgrade/freshen）](#2223-rpm-升级与更新upgradefreshen)
    - [22.2.4 RPM 查询 (query)](#2224-rpm-查询-query)
    - [22.2.5 RPM 验证与数字签名 (verify/signature)](#2225-rpm-验证与数字签名-verifysignature)
    - [22.2.6 RPM 卸载与重建数据库 (erase/rebuilddb)](#2226-rpm-卸载与重建数据库-eraserebuilddb)
  - [22.3 YUM 在线升级机制](#223-yum-在线升级机制)
    - [22.3.1 利用 yum 进行查询、安装、升级与移除功能](#2231-利用-yum-进行查询安装升级与移除功能)
    - [22.3.2 yum 的配置文件](#2232-yum-的配置文件)
    - [22.3.3 yum 的软件群组功能](#2233-yum-的软件群组功能)
    - [22.3.4 EPEL/ELRepo 外挂软件以及自定义配置文件](#2234-epelelrepo-外挂软件以及自定义配置文件)
    - [22.3.5 全系统自动升级](#2235-全系统自动升级)
    - [22.3.6 管理的抉择: RPM 还是 Tarball](#2236-管理的抉择-rpm-还是-tarball)
    - [22.3.7 基础服务管理: 以 Apache 为例](#2237-基础服务管理-以-apache-为例)
  - [22.4 SRPM 的使用: rpmbuild (Optional)](#224-srpm-的使用-rpmbuild-optional)
    - [22.4.1 利用默认值安装 SRPM 文件 (--rebuild/--recompile)](#2241-利用默认值安装-srpm-文件---rebuild--recompile)
    - [22.4.2 SRPM 使用的路径与需要的软件](#2242-srpm-使用的路径与需要的软件)
    - [22.4.3 配置文件的主要内容 (*.spec)](#2243-配置文件的主要内容-spec)
    - [22.4.4 SRPM 的编译命令 (-ba/-bb)](#2244-srpm-的编译命令--ba-bb)
    - [22.4.5 一个打包自己软件的范例](#2245-一个打包自己软件的范例)
  - [22.5 重点回顾](#225-重点回顾)
  - [22.6 本章习题](#226-本章习题)
  - [22.7 参考资料与延伸阅读](#227-参考资料与延伸阅读)

## 22.1 软件管理器简介

### 22.1.1 Linux 界的两大主流: RPM 与 DPKG

目前 Linux 软件安装方式最常见的有两种，分别是：

- DPKG: 由 Debian Linux 社区开发
- RPM: 由 Red Hat 开发

| distribution   | 管理机制 | 命令          | 线上升级命令 |
| -------------- | -------- | ------------- | ------------ |
| Red Hat/Fedora | RPM      | rpm, rpmbuild | yum          |
| Debian/Ubuntu  | DPKG     | dpkg          | apt          |

### 22.1.2 什么是 RPM 与 SRPM

RPM (RedHat Package Manager) 优点：

1. 软件都预先编译打包，所以传输与安装都很方便
2. 软件的信息都记录在 Linux 主机的数据库中，可以方便查询、升级与卸载

缺点：

1. 软件文件安装的环境必须与打包时的环境需求一致
2. 需要满足软件的依赖
3. 卸载时需要特别小心，最底层的软件不可先移除，否则可能造成整个系统的问题

SRPM (Source RPM), 及包含源代码的 RPM 文件，SRPM 提供的软件没有预先编译，
它提供的是源代码。与 tarball 相比，它的优点是提供了源代码之外的信息（与 RPM 一样）。
使用步骤：

- 以 RPM 管理的方式编译，SRPM 文件变成 RPM 文件
- 安装 RPM 文件

| 格式 | 文件名    | 直接安装与否 | 内含软件类型   | 可否修改参数 |
| ---- | --------- | ------------ | -------------- | ------------ |
| RPM  | *.rpm     | 可           | 已编译         | 不可         |
| SRPM | *.src.rpm | 不可         | 未编译的源代码 | 可           |

### 22.1.3 什么是 i386, i586, i686, noarch, x86_64

每个 RPM 包的格式为

```txt
rp-pppoe - 3.11   - 5            .el7.x86_64  .rpm
软件名称    版本信息   release次数   硬件平台       扩展名
```

硬件平台：

- i386: 几乎所有的 x86 平台，i 指的是 Intel 兼容的 CPU，386 是 CPU 的等级。
- i586: 586 等级的 CPU，包括 Pentium 第一代 MMX CPU， AMD 的 K5, K6 系列 CPU。
- i686: 在 Pentium II 以后的 Intel 系列 CPU ，及 K7 以后的 CPU。
  由于市面上几乎只有 P-II 以后的，因此很多 distributions 都直接发布该等级 RPM 文件
- x86_64: 针对 64 位 CPU 进行最优化的编译设定，包括 Intel 的 Core 2 以上等級 CPU，
  以及 AMD 的 Athlon64 以后等级的 CPU。
- noarch: 就是沒有任何硬件限制。一般来说这类 RPM 文件里没有 binary 程序，通常是 shell
  script。

### 22.1.4 RPM 的优点

- RPM 内含已编译的程序与配置文件等数据，使用户免除编译的困扰；
- RPM 安装前会先检查系统磁盘空间、系统版本等，避免错误安装；
- RPM 文件本身提供软件版本信息、依赖信息、用途说明、所含文件等信息；
- RPM 管理使用数据库记录 RPM 文件的相关信息，便于升级、移除、查询与验证。

### 22.1.5 RPM 依赖的克服方式：yum 在线升级

1. 发布的软件放在 yum 服务器内
2. 分析软件的依赖信息并记录，形成依赖清单列表
3. 依赖清单与软件位置等信息数据成为 repository
4. 用户安装时根据 repository 提供的信息获取依赖于软件文件

## 22.2 RPM 软件管理程序: rpm

### 22.22.1 RPM 默认安装路径

| 目录           | 意义                        |
| -------------- | --------------------------- |
| /etc           | 配置文件，例如 /etc/crontab |
| /usr/bin       | 可执行文件                  |
| /usr/lib       | 动态函数库                  |
| /usr/share/doc | 使用手册                    |
| /usr/share/man | man page                    |

### 22.2.2 RPM 安装 (install)

需要 root 权限。

`rpm -ivh RPM_FILE`

### 22.2.3 RPM 升级与更新（upgrade/freshen）

`rpm -Uvh`: 安装或更新
`rpm -Fvh`: 只更新

### 22.2.4 RPM 查询 (query)

基于 `/var/lib/rpm` 下的数据库文件。

`rpm -q[ap]`

### 22.2.5 RPM 验证与数字签名 (verify/signature)

`rpm -V PKG_NAME`

例子：

```sh
[root@study ~]# rpm -V logrotate
..5....T.  c /etc/logrotate.conf
```

- 变更类型
  - S: file Size differs
  - M: Mode differs
  - 5: MD5 sum differs
  - D: Device major/minor number mis-match
  - L: readLink(2) path mis-match
  - U: User ownership differs
  - G: Group ownership differs
  - T: mTime differs
  - P: caPabilities differ
- 文件类型
  - c: config file
  - d: documentation
  - g: ghost file, 无主文件
  - l: license file
  - r: README
- 数字签名（digital signature），当你要安装一个 RPM 文件时
  1. 必须安装厂商发布的 GPG 公钥文件
  2. 安装官方 RPM 软件时，rpm 命令会去读取 RPM 文件的签名信息，与本机的签名信息对比
  3. 签名相同才安装，找不到签名信息则警告并停止安装

### 22.2.6 RPM 卸载与重建数据库 (erase/rebuilddb)

卸载必须从最上层往下进行。

- `rpm -e RPM_NAME`
- `rpm --rebuilddb`

## 22.3 YUM 在线升级机制

### 22.3.1 利用 yum 进行查询、安装、升级与移除功能

- 查询: `yum [list|info|search|provides|whatprovides]`
- 安装/升级: `yum [install|update]`
- 移除: `yum [remove]`

### 22.3.2 yum 的配置文件

```sh
[root@study ~]# vim /etc/yum.repos.d/CentOS-Base.repo
[base]
name=CentOS-$releasever - Base
mirrorlist=http://mirrorlist.centos.org/?release=$releasever&arch=$basearch&repo=os&infra=$infra
#baseurl=http://mirror.centos.org/centos/$releasever/os/$basearch/
gpgcheck=1
gpgkey=file:///etc/pki/rpm-gpg/RPM-GPG-KEY-CentOS-7
```

- `[base]`: 软件 repo 名称
- name: repo 名称
- mirrorlist=: 列出这个 repo 可以使用的镜像站
- baseurl=: repo 实际网址，mirrorlist 是由 yum 自行去获取镜像站，baseurl
  则指定固定的 repo
- enable=1: 启用
- gpgcheck=1: 进行 GPG 签名验证
- gpgkey=: GPG 公钥

修改软件库产生的问题与解决之道：修改默认软件 repo 如果没有修改名称，会造成本机清单与新的 yum
服务不同步，此时需要 `yum clean`

### 22.3.3 yum 的软件群组功能

- `yum [grouplist|groupinfo|groupinstall|groupremove]`

### 22.3.4 EPEL/ELRepo 外挂软件以及自定义配置文件

EPEL: Extra Packages for Enterprise Linux
ELRepo: 提供的软件大多数与内核、内核模块和虚拟化相关软件又换

### 22.3.5 全系统自动升级

`yum -y update`

### 22.3.6 管理的抉择: RPM 还是 Tarball

1. 优先选择官方的 RPM
2. 选择官方发布到 RPM 或提供的软件库地址
3. 利用 Tarball 安装特殊软件
4. 用 Tarball 测试新版软件

### 22.3.7 基础服务管理: 以 Apache 为例

1. 安装: yum install
2. 启动: systemctl start
3. 开机启动: systemctl enable
4. 防火墙: firewall-cmd --add-service="NAME";
   firewall-cmd --permanent --add-service="NAME"
5. 测试

## 22.4 SRPM 的使用: rpmbuild (Optional)

### 22.4.1 利用默认值安装 SRPM 文件 (--rebuild/--recompile)

- `rpmbuild --rebuild` 产生 rpm 文件，再用 `rpm -i` 安装
- `rpmbuild --recompile` 会编译、打包并安装

### 22.4.2 SRPM 使用的路径与需要的软件

假设用 root 用户操作 SRPM，则

- `/root/rpmbuild/SPECS`: 配置文件、规格等
- `/root/rpmbuild/SOURCES`: 源代码以及 config 配置文件
- `/root/rpmbuild/BUILD`: 编译过程的暂存目录
- `/root/rpmbuild/RPMS`: 编译、打包结果的存储目录
- `/root/rpmbuild/SRPMS`: 与 RPMS 相似，这里放置的就是 SRPM 封装的文件

### 22.4.3 配置文件的主要内容 (*.spec)

SRPM 的编译过程有 `./configure`, `make`, `make check`, `make install` 等，
这些步骤写在 SPECS 目录中的 `*.spec` 文件。

1. 文件以 Summary 开始，包含基本的说明内容
2. 之后每个段落以 % 开头，如 %prep, %install 等

SRPM 配置段落：

- 系统整体信息
  - 必要信息
    - Summary
    - Name
    - Version
    - Release
    - License
    - Group
    - URL
    - SourceN
    - PatchN
    - BuildRoot
  - 额外信息
    - Requires
    - BuildRequires
- %description: 简要说明，`rpm -qi`
- %prep
  1. 进行软件补丁相关工作
  2. 确认软件所需目录是否存在
  3. 预先创建所需目录等
  4. 如果安装将会覆盖文件，则进行备份
- %build: configure, make 等执行编译步骤
- %install: make install
- %files: 文件列表
- %changelog

### 22.4.4 SRPM 的编译命令 (-ba/-bb)

- `rpmbuild -ba *.spec`: 编译并同时产生 RPM 与 SRPM 文件
- `rpmbuild -bb *.spec`: 仅编译产生 RPM 文件

### 22.4.5 一个打包自己软件的范例

- 制作源代码文件 tarball
- 创建 *.spec 配置文件
- 编译成 RPM 与 SRPM
- 安装、测试、查询

## 22.5 重点回顾

- 為了避免使用者自行編譯的困擾，開發商自行在特定的硬體與作業系統平台上面預先編譯好軟體，
  並將軟體以特殊格式封包成檔案，提供終端用戶直接安裝到固定的作業系統上，
  並提供簡單的查詢/安裝/移除等流程。常見的軟體管理員有 RPM 與 DPKG 兩大主流。
- RPM 的全名是 RedHat Package Manager，原本是由 Red Hat 公司所發展的，流傳甚廣；
- RPM 類型的軟體中，所含有的軟體是經過編譯後的 binary program，
  所以可以直接安裝在使用者端的系統上， 不過，也由於如此，所以 RPM
  對於安裝者的環境要求相當嚴格；
- RPM 除了將軟體安裝至使用者的系統上之外，還會將該軟體的版本、名稱、檔案與目錄配置、
  系統需求等等均記錄於資料庫 (/var/lib/rpm) 當中，方便未來的查詢與升級、移除；
- RPM 可針對不同的硬體等級來加以編譯，製作出來的檔案可於副檔名 (i386, i586, i686,
  x86_64, noarch) 來分辨；
- RPM 最大的問題為軟體之間的相依性問題；
- SRPM 為 Source RPM ，內含的檔案為 Source code 而非為 binary file ，所以安裝 SRPM
  時還需要經過 compile ，不過，SRPM 最大的優點就是可以讓使用者自行修改設定參數
  (makefile/configure 的參數) ，以符合使用者自己的 Linux 環境；
- RPM 軟體的屬性相依問題，已經可以藉由 yum 或者是 APT 等方式加以克服。 CentOS 使用的就是
  yum 機制。
- yum 伺服器提供多個不同的軟體庫放置個別的軟體，以提供用戶端分別管理軟體類別。

## 22.6 本章习题

## 22.7 参考资料与延伸阅读
