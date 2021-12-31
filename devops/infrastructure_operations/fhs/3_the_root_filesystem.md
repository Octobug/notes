# Chapter 3. The Root Filesystem

> <https://refspecs.linuxfoundation.org/FHS_3.0/fhs/ch03.html>

## 3.1. Purpose

The contents of the root filesystem must be adequate to boot, restore, recover,
and/or repair the system.

- To boot a system, enough software and data must be present on the root
  partition to mount other filesystems. This includes utilities, configuration,
  boot loader information, and other essential start-up data. `/usr`, `/opt`,
  and `/var` are designed such that they may be located on other partitions or
  filesystems.
- To enable recovery and/or repair of a system, those utilities needed by an
  experienced maintainer to diagnose and reconstruct a damaged system must be
  present on the root filesystem.
- To restore a system, those utilities needed to restore from system backups
  must be present on the root filesystem.

### Rationale (minimum requirements)

The minimum requirements for the root filesystem should be as small as
reasonably possible, but no smaller. While many users may not want the extra
complexity of a partitioned system, the option to keep the root small should be
preserved for several reasons:

- It is occasionally mounted from very small media.
- The root filesystem contains many system-specific configuration files.
  Possible examples include a kernel that is specific to the system, a specific
  hostname, etc. This means that the root filesystem isn't always shareable
  between networked systems. Keeping it small on servers in networked systems
  minimizes the amount of lost space for areas of unshareable files. It also
  allows workstations with smaller local hard drives.
- While you may have the root filesystem on a large partition, and may be able
  to fill it to your heart's content, there will be people with smaller
  partitions. If you have more files installed, you may find incompatibilities
  with other systems using root filesystems on smaller partitions. If you are a
  developer then you may be turning your assumption into a problem for a large
  number of users.
- Disk errors that corrupt data on the root filesystem are a greater problem
  than errors on any other partition. A small root filesystem is less prone to
  corruption as the result of a system crash.

These considerations must be balanced against the need for a minimally useful
operating environment, for the sake of the boot process as well as in failure
recovery situations.

Applications must never create or require special files or subdirectories in
the root directory. Other locations in the FHS hierarchy provide more than
enough flexibility for any package.

```txt
Rationale

There are several reasons why creating a new subdirectory of the root
filesystem is prohibited:

- It demands space on a root partition which the system administrator may want
  kept small and simple for either performance or security reasons.
- It evades whatever discipline the system administrator may have set up for
  distributing standard file hierarchies across mountable volumes.

Distributions should not create new directories in the root hierarchy without
extremely careful consideration of the consequences including for application
portability.
```

## 3.2. Requirements

The following directories, or symbolic links to directories, are required in
`/`.

| Directory | Description |
| - | - |
| `bin` | Essential command binaries |
| `boot` | Static files of the boot loader |
| `dev` | Device files |
| `etc` | Host-specific system configuration |
| `lib` | Essential shared libraries and kernel modules |
| `media` | Mount point for removable media |
| `mnt` | Mount point for mounting a filesystem temporarily |
| `opt` | Add-on application software packages |
| `run` | Data relevant to running processes |
| `sbin` | Essential system binaries |
| `srv` | Data for services provided by this system |
| `tmp` | Temporary files |
| `usr` | Secondary hierarchy |
| `var` | Variable data |

Each directory listed above is specified in detail in separate subsections
below. `/usr` and `/var` each has a complete section in this document due to
the complexity of those directories.

## 3.3. Specific Options

The following directories, or symbolic links to directories, must be in `/`, if
the corresponding subsystem is installed:

| Directory | Description |
| `home` | User home directories (optional) |
| `lib<qual>` | Alternate format essential shared libraries (optional) |
| `root` | Home directory for the root user (optional) |

Each directory listed above is specified in detail in separate subsections
below.

## 3.17. `/srv` : Data for services provided by this system

### 3.17.1. Purpose

`/srv` contains site-specific data which is served by this system.

```txt
Rationale

This main purpose of specifying this is so that users may find the location of
the data files for a particular service, and so that services which require a
single tree for readonly data, writable data and scripts (such as cgi scripts)
can be reasonably placed. Data that is only of interest to a specific user
should go in that users' home directory. If the directory and file structure of
the data is not exposed to consumers, it should go in /var/lib.

The methodology used to name subdirectories of /srv is unspecified as there is
currently no consensus on how this should be done. One method for structuring
data under /srv is by protocol, eg. ftp, rsync, www, and cvs. On large systems
it can be useful to structure /srv by administrative context, such as
/srv/physics/www, /srv/compsci/cvs, etc. This setup will differ from host to
host. Therefore, no program should rely on a specific subdirectory structure of
/srv existing or data necessarily being stored in /srv. However /srv should
always exist on FHS compliant systems and should be used as the default
location for such data.

Distributions must take care not to remove locally placed files in these
directories without administrator permission.
```
