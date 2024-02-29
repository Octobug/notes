# Revision Control System

- [Revision Control System](#revision-control-system)
  - [老派 RCS](#老派-rcs)
    - [VSS (Visual Source Safe)](#vss-visual-source-safe)
    - [CVS (Concurrent Versions System)](#cvs-concurrent-versions-system)
  - [集中式 RCS](#集中式-rcs)
    - [SVN 的优点](#svn-的优点)
    - [SVN 的缺点](#svn-的缺点)
  - [分布式 RCS](#分布式-rcs)
    - [集中式 vs. 分布式](#集中式-vs-分布式)
    - [哪些人适合分布式 RCS](#哪些人适合分布式-rcs)
    - [常见的分布式 RCS](#常见的分布式-rcs)

## 老派 RCS

### VSS (Visual Source Safe)

即微软的 Visual Source Safe。VSS 对源代码库的访问基于局域网的共享文件夹方式。
共享文件夹不光效率低下，而且容易产生安全隐患。

VSS 更严重的问题是误导了开发人员的对于源代码管理的观念，比如它对文件的锁定模式。

### CVS (Concurrent Versions System)

CVS 曾经是源代码版本管理的代名词，那时大部分的开源项目都使用 CVS 进行代码管理。

弊端：

- 不能改名文件/目录
- 不支持对目录的版本控制
- 对 Unicode/UTF8 支持不够好
- 版本提交的原子性
- ...

有人受不了 CVS 的缺点，开发了一个改良版的 CVSNT。但仍有几个致命的缺点还在，比如文件改名问题；

## 集中式 RCS

SVN (subversion) 是比较有代表性的集中式 RCS。

### SVN 的优点

SVN 相对于 CVS 的优点主要有：

1. 能够导入多种 RCS 的代码库：能通过第三方工具比如 SVN Importer，把其它 RCS 比如 CVS,
   PVCS, MKS, ClearCase, SourceSafe 的代码库迁移到 SVN。
2. 和 CVS 的使用类似：SVN 的常用命令、概念、操作习惯都比较类似于 CVS。
   开发人员从 CVS 切换到 SVN 的学习成本较小。
3. 支持文件/目录改名。
4. 和 Web 密切整合：深度整合了 Web，很多版本管理的操作都可以直接在浏览器上进行。
5. 能整合其它的开发工具：比如在 Bug 管理方面，有：Trac, Bugzilla, Mantis。

### SVN 的缺点

1. 不支持分布式。
2. 性能：操作速度和存储空间都不太理想。
3. 散落的 `.svn` 目录。

## 分布式 RCS

### 集中式 vs. 分布式

主要区别：

- 对于集中式 RCS，只有一个中央代码仓库，开发人员在自己机器上维护一个工作副本；
  本地的代码在提交之前无法被 RCS 管理，因此无法进行各种操作（比如创建分支）。
  一旦开发机器和中央代码仓库的网络连接断开就无法进行后续工作。
- 对于分布式 RCS，每一个开发人员的机器上都有一个代码仓库。随时都可以提交到本地的代码仓库中。
  分布式 RCS 可以在网络连通的时候，再进行各个代码仓库之间的数据同步。

### 哪些人适合分布式 RCS

1. 开发团队有地域性分隔
2. 远程办公

### 常见的分布式 RCS

1. Git
2. Mercurial: 它特色是基于 Python 开发，所以在跨平台方面比较有优势。
   - 缺点：相对于 Git 的缺点是性能不够好。
