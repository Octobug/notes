# 第八章 文件的压缩与打包

> <https://linux.vbird.org/linux_basic/centos7/0240tarcompress.php>

## 目录

- [第八章 文件的压缩与打包](#第八章-文件的压缩与打包)
  - [目录](#目录)
  - [8.1 压缩文件的用途与技术](#81-压缩文件的用途与技术)
  - [8.2 Linux 系统常见的压缩指令](#82-linux-系统常见的压缩指令)
    - [8.2.1 gzip, zcat/zmore/zless/zgrep](#821-gzip-zcatzmorezlesszgrep)
    - [8.2.2 bzip2, bzcat/bzmore/bzless/bzgrep](#822-bzip2-bzcatbzmorebzlessbzgrep)
    - [8.2.3 xz, xzcat/xzmore/xzless/xzgrep](#823-xz-xzcatxzmorexzlessxzgrep)
    - [对比](#对比)
  - [8.3 打包指令: tar](#83-打包指令-tar)
    - [8.3.1 tar](#831-tar)
      - [tarfile 与 tarball?](#tarfile-与-tarball)
      - [专题](#专题)
  - [8.4 XFS 文件系统的备份与还原](#84-xfs-文件系统的备份与还原)
    - [8.4.1 XFS 文件系统备份 xfsdump](#841-xfs-文件系统备份-xfsdump)
    - [8.4.2 XFS 文件系统换源 xfsrestore](#842-xfs-文件系统换源-xfsrestore)
  - [8.5 光盘写入工具](#85-光盘写入工具)
    - [8.5.1 mkisofs: 创建镜像文件](#851-mkisofs-创建镜像文件)
    - [8.5.2 cdrecord: 光盘烧录工具](#852-cdrecord-光盘烧录工具)
  - [8.6 其他常见的压缩与备份工具](#86-其他常见的压缩与备份工具)
    - [8.6.1 dd](#861-dd)
    - [8.6.2 cpio](#862-cpio)
  - [8.7 重点回顾](#87-重点回顾)
  - [8.8 本章习题](#88-本章习题)
  - [8.9 参考资料与延伸阅读](#89-参考资料与延伸阅读)

## 8.1 压缩文件的用途与技术

- 节省磁盘空间
- 减少流量传输

## 8.2 Linux 系统常见的压缩指令

常见扩展名（助记作用

- `.Z`: compress
- `.zip`: zip
- `.gz`: gzip
- `.bz2`: bzip2
- `.xz`: xz
- `.tar`: tar
- `.tar.gz`: tar + gzip
- `.tar.bz2`: tar + bzip2
- `.tar.xz`: tar + xz

### 8.2.1 gzip, zcat/zmore/zless/zgrep

- `-c`: 将压缩的数据输出到标准输出
- `-d`: 解压缩
- `-k`: 保留原文件，相当于 `-c >`
- `-t`: 检验文件是否有错误
- `-v`: 显示压缩过程信息
- `-数字`: 压缩等级

### 8.2.2 bzip2, bzcat/bzmore/bzless/bzgrep

用法和 gzip 基本一致。

### 8.2.3 xz, xzcat/xzmore/xzless/xzgrep

用法和 gzip 基本一致。

- `-l`: 显示压缩文件信息

### 对比

`find /etc -maxdepth 1 -type f -exec du -sh {} \; | sort -h`

`find /bin -maxdepth 1 -type f -exec du -sh {} \; | sort -h`

`time gzip/bzip2/xz...`

## 8.3 打包指令: tar

### 8.3.1 tar

- `-c`: 创建打包文件
- `-t`: 查看打包 tar 文件包含的文件名
- `-x`: 解包文件
- `-z`: 使用 gzip 压缩/解压 .tar.gz
- `-j`: 使用 bzip2 压缩/解压 .tar.bz2
- `-J`: 使用 xz 压缩/解压 .tar.xz
- `-v`: 显示处理过程
- `-f filename`: `f` 后必须紧跟被处理的文件名
- `-C directory`: 指定解压目录
- `-p`: 保留数据原本的权限与属性
- `-P`: 保留绝对路径，谨慎使用，因为解压时会按绝对路径放置
- `--exclude=FILE`: 排除某些文件
- `--newer TIMESTRING`: 只包含 mtime 与 ctime 比 TIMESTRING 更新的文件
- `--newer-mtime TIMESTRING`: 只包含 mtime 比 TIMESTRING 更新的文件

常用组合:

- 压缩: `tar -zcvf tarball.tar.gz directory`
- 查询: `tar -ztvf tarball.tar.gz`, `z` 可省略
- 解压: `tar -zxvf tarball.tar.gz -C directory`
- 只解压部分: `tar -zxvf tarball.tar.gz -C directory file_in_tarfile`

#### tarfile 与 tarball?

- tarfile: 只打包不压缩，即后缀为 .tar
- tarball: 打包加压缩

#### 专题

- 打包到特殊设备中: `tar -cvf /dev/st0 /home /root /etc`
- 结合管道与数据重定向: `tar -cvf - /etc | tar -xvf -`, 两个 `-` 分别作为
  `stdout` 与 `stdin`
- 解压缩后的 SELinux 问题三种解决方案:
  - 修改 `/etc/selinux/config`, 将 SELinux 改成 permissive 模式
  - 第一次复原后，先使用 `restorecon -Rv /etc` 修复 SELinux 的类型
  - 创建 `/.autorelabel` 文件，开机后系统会自动修复 SELinux 类型

## 8.4 XFS 文件系统的备份与还原

### 8.4.1 XFS 文件系统备份 xfsdump

- xfsdump 支持差异备份，即只备份和上一次备份有差异的文件
- 备份文件位于 `/var/lib/xfsdump/inventory`
- xfsdump 只支持备份整个文件系统而非某个目录
- `xfsdump -I`: 列出当前备份信息

### 8.4.2 XFS 文件系统换源 xfsrestore

- `xfsrestore -I`: 列出当前备份信息
- 恢复差异备份: 必须按照 level 0 -> 1 -> 2 的顺序
- `-i`: 交互模式决定是否还原

## 8.5 光盘写入工具

- 使用 `mkisofs` 将数据制作成镜像文件
- 使用 `cdrecord` 将镜像文件烧录到光盘中

### 8.5.1 mkisofs: 创建镜像文件

### 8.5.2 cdrecord: 光盘烧录工具

更新的还有 `wodim` 命令。

## 8.6 其他常见的压缩与备份工具

### 8.6.1 dd

- `dd if="input_file" of="output_file" bs="block_size" count="number"`
- `dd if=/dev/sr0 of=/tmp/system.iso`: 复制光驱内容
- `dd if=/tmp/system.iso of=/dev/sda`: 写入到 U 盘中
- dd 默认按扇区读写，因此可以不理会文件系统格式原样复制

### 8.6.2 cpio

- 备份: `cpio -ovcb > [file|device]`
  - `-o`: 将数据 copy 输出到文件或装置上
  - `-B`: 让默认的 Blocks 可以添加至 5120 bytes ，默认是 512 bytes
- 还原: `cpio -ivcdu < [file|device]`
  - `-i`: 将数据自文件或装置 copy 出来系统当中
  - `-d`: 自动创建目录
  - `-u`: 自动的将较新的文件覆盖较旧的文件
  - `-t`: 需配合 -i 选项，可用在"察看"以 cpio 创建的文件或装置的内容
- 查看: `cpio -ivct < [file|device]`
- 可共享的选项与参数
  - `-v`: 让储存的过程中文件名称可以在萤幕上显示
  - `-c`: 一种较新的 portable format 方式储存

## 8.7 重点回顾

## 8.8 本章习题

## 8.9 参考资料与延伸阅读
