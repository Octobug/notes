# Chapter 3. The Root Filesystem

> <https://refspecs.linuxfoundation.org/FHS_3.0/fhs/ch03.html>

## Table of Contents

- [Chapter 3. The Root Filesystem](#chapter-3-the-root-filesystem)
  - [Table of Contents](#table-of-contents)
  - [3.1. Purpose](#31-purpose)
    - [3.1. Rationale](#31-rationale)
  - [3.2. Requirements](#32-requirements)
  - [3.3. Specific Options](#33-specific-options)
  - [3.4. `/bin`: Essential user command binaries (for use by all users)](#34-bin-essential-user-command-binaries-for-use-by-all-users)
    - [3.4.1. Purpose](#341-purpose)
    - [3.4.2. Requirements](#342-requirements)
      - [3.4.2. Rationale](#342-rationale)
    - [3.4.3. Specific Options](#343-specific-options)
      - [3.4.3. Rationale](#343-rationale)
  - [3.5. `/boot`: Static files of the boot loader](#35-boot-static-files-of-the-boot-loader)
    - [3.5.1. Purpose](#351-purpose)
    - [3.5.2. Specific Options](#352-specific-options)
  - [3.6. `/dev`: Device files](#36-dev-device-files)
    - [3.6.1. Purpose](#361-purpose)
    - [3.6.2. Specific Options](#362-specific-options)
  - [3.7. `/etc`: Host-specific system configuration](#37-etc-host-specific-system-configuration)
    - [3.7.1. Purpose](#371-purpose)
    - [3.7.2. Requirements](#372-requirements)
    - [3.7.3. Specific Options](#373-specific-options)
    - [3.7.4. `/etc/opt`: Configuration files for `/opt`](#374-etcopt-configuration-files-for-opt)
      - [3.7.4.1. Purpose](#3741-purpose)
      - [3.7.4.2. Requirements](#3742-requirements)
        - [3.7.4.2. Rationale](#3742-rationale)
    - [3.7.5. `/etc/X11`: Configuration for the X Window System (optional)](#375-etcx11-configuration-for-the-x-window-system-optional)
      - [3.7.5.1. Purpose](#3751-purpose)
      - [3.7.5.2. Specific Options](#3752-specific-options)
    - [3.7.6. `/etc/sgml`: Configuration files for SGML (optional)](#376-etcsgml-configuration-files-for-sgml-optional)
      - [3.7.6.1. Purpose](#3761-purpose)
    - [3.7.7. `/etc/xml`: Configuration files for XML (optional)](#377-etcxml-configuration-files-for-xml-optional)
      - [3.7.7.1. Purpose](#3771-purpose)
  - [3.8. `/home`: User home directories (optional)](#38-home-user-home-directories-optional)
    - [3.8.1. Purpose](#381-purpose)
    - [3.8.2. Requirements](#382-requirements)
    - [3.8.3. Home Directory Specifications and Conventions](#383-home-directory-specifications-and-conventions)
  - [3.9. `/lib`: Essential shared libraries and kernel modules](#39-lib-essential-shared-libraries-and-kernel-modules)
    - [3.9.1. Purpose](#391-purpose)
    - [3.9.2. Requirements](#392-requirements)
    - [3.9.3. Specific Options](#393-specific-options)
  - [3.10. `/lib<qual>`: Alternate format essential shared libraries (optional)](#310-libqual-alternate-format-essential-shared-libraries-optional)
    - [3.10.1. Purpose](#3101-purpose)
    - [3.10.2. Requirements](#3102-requirements)
  - [3.11. `/media`: Mount point for removable media](#311-media-mount-point-for-removable-media)
    - [3.11.1. Purpose](#3111-purpose)
      - [3.11.1. Rationale](#3111-rationale)
    - [3.11.2. Specific Options](#3112-specific-options)
  - [3.12. `/mnt`: Mount point for a temporarily mounted filesystem](#312-mnt-mount-point-for-a-temporarily-mounted-filesystem)
    - [3.12.1. Purpose](#3121-purpose)
  - [3.13. `/opt`: Add-on application software packages](#313-opt-add-on-application-software-packages)
    - [3.13.1. Purpose](#3131-purpose)
    - [3.13.2. Requirements](#3132-requirements)
      - [3.13.2. Rationale](#3132-rationale)
  - [3.14. `/root`: Home directory for the root user (optional)](#314-root-home-directory-for-the-root-user-optional)
    - [3.14.1. Purpose](#3141-purpose)
  - [3.15. `/run`: Run-time variable data](#315-run-run-time-variable-data)
    - [3.15.1. Purpose](#3151-purpose)
    - [3.15.2. Requirements](#3152-requirements)
  - [3.16. `/sbin`: System binaries](#316-sbin-system-binaries)
    - [3.16.1. Purpose](#3161-purpose)
    - [3.16.2. Requirements](#3162-requirements)
    - [3.16.3. Specific Options](#3163-specific-options)
  - [3.17. `/srv`: Data for services provided by this system](#317-srv-data-for-services-provided-by-this-system)
    - [3.17.1. Purpose](#3171-purpose)
      - [3.17.1. Rationale](#3171-rationale)
  - [3.18. `/tmp`: Temporary files](#318-tmp-temporary-files)
    - [3.18.1. Purpose](#3181-purpose)
      - [3.18.1. Rationale](#3181-rationale)

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

### 3.1. Rationale

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

| Directory | Description                                       |
| --------- | ------------------------------------------------- |
| `bin`     | Essential command binaries                        |
| `boot`    | Static files of the boot loader                   |
| `dev`     | Device files                                      |
| `etc`     | Host-specific system configuration                |
| `lib`     | Essential shared libraries and kernel modules     |
| `media`   | Mount point for removable media                   |
| `mnt`     | Mount point for mounting a filesystem temporarily |
| `opt`     | Add-on application software packages              |
| `run`     | Data relevant to running processes                |
| `sbin`    | Essential system binaries                         |
| `srv`     | Data for services provided by this system         |
| `tmp`     | Temporary files                                   |
| `usr`     | Secondary hierarchy                               |
| `var`     | Variable data                                     |

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

## 3.4. `/bin`: Essential user command binaries (for use by all users)

### 3.4.1. Purpose

`/bin` contains commands that may be used by both the system administrator and
by users, but which are required when no other filesystems are mounted (e.g. in
single user mode). It may also contain commands which are used indirectly by
scripts. [1]

### 3.4.2. Requirements

There must be no subdirectories in `/bin`.

The following commands, or symbolic links to commands, are required in `/bin`:

| Command  | Description                                           |
| -------- | ----------------------------------------------------- |
| cat      | Utility to concatenate files to standard output       |
| chgrp    | Utility to change file group ownership                |
| chmod    | Utility to change file access permissions             |
| chown    | Utility to change file owner and group                |
| cp       | Utility to copy files and directories                 |
| date     | Utility to print or set the system data and time      |
| dd       | Utility to convert and copy a file                    |
| df       | Utility to report filesystem disk space usage         |
| dmesg    | Utility to print or control the kernel message buffer |
| echo     | Utility to display a line of text                     |
| false    | Utility to do nothing, unsuccessfully                 |
| hostname | Utility to show or set the system's host name         |
| kill     | Utility to send signals to processes                  |
| ln       | Utility to make links between files                   |
| login    | Utility to begin a session on the system              |
| ls       | Utility to list directory contents                    |
| mkdir    | Utility to make directories                           |
| mknod    | Utility to make block or character special files      |
| more     | Utility to page through text                          |
| mount    | Utility to mount a filesystem                         |
| mv       | Utility to move/rename files                          |
| ps       | Utility to report process status                      |
| pwd      | Utility to print name of current working directory    |
| rm       | Utility to remove files or directories                |
| rmdir    | Utility to remove empty directories                   |
| sed      | The `sed' stream editor                               |
| sh       | POSIX compatible command shell                        |
| stty     | Utility to change and print terminal line settings    |
| su       | Utility to change user ID                             |
| sync     | Utility to flush filesystem buffers                   |
| true     | Utility to do nothing, successfully                   |
| umount   | Utility to unmount file systems                       |
| uname    | Utility to print system information                   |

If `/bin/sh` is not the POSIX compatible shell command itself, it must be a
hard or symbolic link to the real shell command.

The `[` and `test` commands must be placed together in either `/bin` or
`/usr/bin`.

#### 3.4.2. Rationale

Various shells behave differently when called as `sh`, so as to preserve POSIX
compatibility while allowing changes or extensions to POSIX when desired.

The requirement for the `[` and `test` commands to be included as binaries
(even if implemented internally by the shell) is shared with the POSIX.1-2008
standard.

### 3.4.3. Specific Options

The following programs, or symbolic links to programs, must be in `/bin` if the
corresponding subsystem is installed:

| Command  | Description                                           |
| -------- | ----------------------------------------------------- |
| csh      | The C shell (optional)                                |
| ed       | The `ed' editor (optional)                            |
| tar      | The tar archiving utility (optional)                  |
| cpio     | The cpio archiving utility (optional)                 |
| gzip     | The GNU compression utility (optional)                |
| gunzip   | The GNU uncompression utility (optional)              |
| zcat     | The GNU uncompression utility (optional)              |
| netstat  | The network statistics utility (optional)             |
| ping     | The ICMP network test utility (optional)              |
| /bin/csh | may be a symbolic link to /bin/tcsh or /usr/bin/tcsh. |

#### 3.4.3. Rationale

The `tar`, `gzip` and `cpio` commands have been added to make restoration of a
system possible (provided that / is intact).

Conversely, if no restoration from the root partition is ever expected, then
these binaries might be omitted (e.g., a ROM chip root, mounting `/usr` through
NFS). If restoration of a system is planned through the network, then `ftp` or
`tftp` (along with everything necessary to get an ftp connection) must be
available on the root partition.

[1] Command binaries that are not essential enough to place into `/bin` must be
placed in `/usr/bin`, instead. Items that are required only by non-root users
(the X Window System, chsh, etc.) are generally not essential enough to be
placed into the root partition.

## 3.5. `/boot`: Static files of the boot loader

### 3.5.1. Purpose

This directory contains everything required for the boot process except
configuration files not needed at boot time and the map installer. Thus `/boot`
stores data that is used before the kernel begins executing user-mode programs.
This may include saved master boot sectors and sector map files.

Programs necessary to arrange for the boot loader to be able to boot a file
must be placed in `/sbin`. Configuration files for boot loaders that are not
required at boot time must be placed in `/etc`.

### 3.5.2. Specific Options

The operating system kernel must be located in either `/` or `/boot`.

Certain architectures may have other requirements for `/boot` related to
limitations or expectations specific to that architecture. These requirements
are not enumerated here; distributions are allowed to add requirements as
needed to enable system startup on these architectures.

## 3.6. `/dev`: Device files

### 3.6.1. Purpose

The `/dev` directory is the location of special or device files.

### 3.6.2. Specific Options

If it is possible that devices in `/dev` will need to be manually created,
`/dev` must contain a command named `MAKEDEV`, which can create devices as
needed. It may also contain a `MAKEDEV.local` for any local devices.

If required, `MAKEDEV` must have provisions for creating any device that may be
found on the system, not just those that a particular distribution installs.

## 3.7. `/etc`: Host-specific system configuration

### 3.7.1. Purpose

The `/etc` hierarchy contains configuration files. A "configuration file" is a
local file used to control the operation of a program; it must be static and
cannot be an executable binary. [2]

It is recommended that files be stored in subdirectories of `/etc` rather than
directly in `/etc`.

### 3.7.2. Requirements

No binaries may be located under `/etc`.

The following directories, or symbolic links to directories are required in
`/etc`:

| Directory | Description            |
| --------- | ---------------------- |
| opt       | Configuration for /opt |

### 3.7.3. Specific Options

The following directories, or symbolic links to directories must be in `/etc`,
if the corresponding subsystem is installed:

| Directory | Description                                      |
| --------- | ------------------------------------------------ |
| X11       | Configuration for the X Window system (optional) |
| sgml      | Configuration for SGML (optional)                |
| xml       | Configuration for XML (optional)                 |

The following files, or symbolic links to files, must be in `/etc` if the
corresponding subsystem is installed: [3]

| File        | Description                                                   |
| ----------- | ------------------------------------------------------------- |
| csh.login   | Systemwide initialization file for C shell logins (optional)  |
| exports     | NFS filesystem access control list (optional)                 |
| fstab       | Static information about filesystems (optional)               |
| ftpusers    | FTP daemon user access control list (optional)                |
| gateways    | File which lists gateways for routed (optional)               |
| gettydefs   | Speed and terminal settings used by getty (optional)          |
| group       | User group file (optional)                                    |
| host.conf   | Resolver configuration file (optional)                        |
| hosts       | Static information about host names (optional)                |
| hosts.allow | Host access file for TCP wrappers (optional)                  |
| hosts.deny  | Host access file for TCP wrappers (optional)                  |
| hosts.equiv | List of trusted hosts for rlogin, rsh, rcp (optional)         |
| hosts.lpd   | List of trusted hosts for lpd (optional)                      |
| inetd.conf  | Configuration file for inetd (optional)                       |
| inittab     | Configuration file for init (optional)                        |
| issue       | Pre-login message and identification file (optional)          |
| ld.so.conf  | List of extra directories to search for shared libraries      |
|             | (optional)                                                    |
| motd        | Post-login message of the day file (optional)                 |
| mtab        | Dynamic information about filesystems (optional)              |
| mtools.conf | Configuration file for mtools (optional)                      |
| networks    | Static information about network names (optional)             |
| passwd      | The password file (optional)                                  |
| printcap    | The lpd printer capability database (optional)                |
| profile     | Systemwide initialization file for sh shell logins (optional) |
| protocols   | IP protocol listing (optional)                                |
| resolv.conf | Resolver configuration file (optional)                        |
| rpc         | RPC protocol listing (optional)                               |
| securetty   | TTY access control for root login (optional)                  |
| services    | Port names for network services (optional)                    |
| shells      | Pathnames of valid login shells (optional)                    |
| syslog.conf | Configuration file for syslogd (optional)                     |

`mtab` does not fit the static nature of `/etc`: it is excepted for historical
reasons. [4]

### 3.7.4. `/etc/opt`: Configuration files for `/opt`

#### 3.7.4.1. Purpose

Host-specific configuration files for add-on application software packages must
be installed within the directory `/etc/opt/<subdir>`, where `<subdir>` is the
name of the subtree in `/opt` where the static data from that package is stored.

#### 3.7.4.2. Requirements

No structure is imposed on the internal arrangement of `/etc/opt/<subdir>`.

If a configuration file must reside in a different location in order for the
package or system to function properly, it may be placed in a location other
than `/etc/opt/<subdir>`.

##### 3.7.4.2. Rationale

Refer to the rationale for `/opt`.

### 3.7.5. `/etc/X11`: Configuration for the X Window System (optional)

#### 3.7.5.1. Purpose

`/etc/X11` is the location for all X11 host-specific configuration. This
directory is necessary to allow local control if `/usr` is mounted read only.

#### 3.7.5.2. Specific Options

The following files, or symbolic links to files, must be in `/etc/X11` if the
corresponding subsystem is installed:

| File      | Description                                                      |
| --------- | ---------------------------------------------------------------- |
| xorg.conf | The configuration file for X.org versions 7 and later (optional) |
| Xmodmap   | Global X11 keyboard modification file (optional)                 |

Subdirectories of `/etc/X11` may include those for `xdm` and for any other
programs (some window managers, for example) that need them. [5]

### 3.7.6. `/etc/sgml`: Configuration files for SGML (optional)

#### 3.7.6.1. Purpose

Generic configuration files defining high-level parameters of the SGML systems
are installed here. Files with names `*.conf` indicate generic configuration
files. File with names `*.cat` are the DTD-specific centralized catalogs,
containing references to all other catalogs needed to use the given DTD. The
super catalog file `catalog` references all the centralized catalogs.

### 3.7.7. `/etc/xml`: Configuration files for XML (optional)

#### 3.7.7.1. Purpose

Generic configuration files defining high-level parameters of the XML systems
are installed here. Files with names `*.conf` indicate generic configuration
files. The super catalog file `catalog` references all the centralized catalogs.

[2] To be clear, `/etc` may contain executable scripts, such as the command
scripts commonly called by init to start and shut down the system and start
daemon processes. "Executable binary" in this context refers to direct machine
code or pseudocode not in a human-readable format, such as native ELF executables.

[3] Systems that use the shadow password suite will have additional
configuration files in `/etc` (`/etc/shadow` and others) and programs in
`/usr/sbin` (useradd, usermod, and others).

[4] On some Linux systems, this may be a symbolic link to `/proc/mounts`, in
which case this exception is not required.

[5] `/etc/X11/xdm` holds the configuration files for `xdm`. These are most of
the files previously found in `/usr/lib/X11/xdm`. Some local variable data for
`xdm` is stored in `/var/lib/xdm`.

## 3.8. `/home`: User home directories (optional)

### 3.8.1. Purpose

`/home` is a fairly standard concept, but it is clearly a site-specific
filesystem. [6] The setup will differ from host to host. Therefore, no program
should assume any specific location for a home directory, rather it should
query for it. [7]

### 3.8.2. Requirements

User specific configuration files for applications are stored in the user's
home directory in a file that starts with the '.' character (a "dot file"). If
an application needs to create more than one dot file then they should be
placed in a subdirectory with a name starting with a '.' character, (a "dot
directory"). In this case the configuration files should not start with the '.'
character. [8]

### 3.8.3. Home Directory Specifications and Conventions

A number of efforts have been made in the past to standardize the layout of
home directories, including the XDG Base Directories specification [9] and the
GLib conventions on user directory contents. [10] Additional efforts in this
direction are possible in the future. To accomodate software which makes use of
these specifications and conventions, distributions may create directory
hierarchies which follow the specifications and conventions. Those directory
hierarchies may be located underneath home directories.

[6] Different people prefer to place user accounts in a variety of places. This
section describes only a suggested placement for user home directories;
nevertheless we recommend that all FHS-compliant distributions use this as the
default location for user home directories. Non-login accounts created for
administrative purposes often have their home directories elsewhere.

On smaller systems, each user's home directory is typically implemented as a
subdirectory directly under `/home`, for example `/home/smith`,
`/home/torvalds`, `/home/operator`, etc. On large systems (especially when the
`/home` directories are shared amongst many hosts using NFS) it is useful to
subdivide user home directories. Subdivision may be accomplished by using
subdirectories such as `/home/staff`, `/home/guests`, `/home/students`, etc.

[7] To find a user's home directory, use a library function such as `getpwent`,
`getpwent_r` of `fgetpwent` rather than relying on `/etc/passwd` because user
information may be stored remotely using systems such as NIS.

[8] It is recommended that, apart from autosave and lock files, programs should
refrain from creating non dot files or directories in a home directory without
user consent.

[9] Found at <http://standards.freedesktop.org/basedir-spec/basedir-spec-latest.html>
and <http://www.freedesktop.org/wiki/Software/xdg-user-dirs>.

[10] A description of GLib's conventions can be found in the documentation for
GUserDirectory, at <http://developer.gnome.org/glib/unstable/glib-Miscellaneous-Utility-Functions.html#GUserDirectory>.

## 3.9. `/lib`: Essential shared libraries and kernel modules

### 3.9.1. Purpose

The `/lib` directory contains those shared library images needed to boot the
system and run the commands in the root filesystem, ie. by binaries in `/bin`
and `/sbin`. [11]

### 3.9.2. Requirements

At least one of each of the following filename patterns are required (they may
be files, or symbolic links):

| File      | Description                                 |
| --------- | ------------------------------------------- |
| libc.so.* | The dynamically-linked C library (optional) |
| ld*       | The execution time linker/loader (optional) |

If a C preprocessor is installed, `/lib/cpp` must be a reference to it, for
historical reasons. [12]

### 3.9.3. Specific Options

The following directories, or symbolic links to directories, must be in `/lib`,
if the corresponding subsystem is installed:

| Directory | Description                        |
| --------- | ---------------------------------- |
| modules   | Loadable kernel modules (optional) |

[11] Shared libraries that are only necessary for binaries in `/usr` (such as
any X Window binaries) must not be in `/lib`. Only the shared libraries
required to run binaries in `/bin` and `/sbin` may be here. In particular, the
library `libm.so.*` may also be placed in `/usr/lib` if it is not required by
anything in `/bin` or `/sbin`.

[12] The usual placement of this binary is `/usr/bin/cpp`.

## 3.10. `/lib<qual>`: Alternate format essential shared libraries (optional)

### 3.10.1. Purpose

There may be one or more variants of the `/lib` directory on systems which
support more than one binary format requiring separate libraries. [13]

### 3.10.2. Requirements

If one or more of these directories exist, the requirements for their contents
are the same as the normal `/lib` directory, except that `/lib<qual>/cpp` is
not required. [14]

[13] This is commonly used for 64-bit or 32-bit support on systems which
support multiple binary formats, but require libraries of the same name. In
this case, `/lib32` and `/lib64` might be the library directories, and `/lib` a
symlink to one of them.

[14] `/lib<qual>/cpp` is still permitted: this allows the case where `/lib` and
`/lib<qual>` are the same (one is a symbolic link to the other).

## 3.11. `/media`: Mount point for removable media

### 3.11.1. Purpose

This directory contains subdirectories which are used as mount points for
removable media such as floppy disks, cdroms and zip disks.

#### 3.11.1. Rationale

Historically there have been a number of other different places used to mount
removable media such as `/cdrom`, `/mnt` or `/mnt/cdrom`. Placing the mount
points for all removable media directly in the root directory would potentially
result in a large number of extra directories in `/`. Although the use of
subdirectories in `/mnt` as a mount point has recently been common, it
conflicts with a much older tradition of using `/mnt` directly as a temporary
mount point.

### 3.11.2. Specific Options

The following directories, or symbolic links to directories, must be in
`/media`, if the corresponding subsystem is installed:

| Directory  | Description             |
| ---------- | ----------------------- |
| floppy     | Floppy drive (optional) |
| cdrom      | CD-ROM drive (optional) |
| cdrecorder | CD writer (optional)    |
| zip        | Zip drive (optional)    |

On systems where more than one device exists for mounting a certain type of
media, mount directories can be created by appending a digit to the name of
those available above starting with '0', but the unqualified name must also
exist. [15]

[15] A compliant distribution with two CDROM drives might have `/media/cdrom0`
and `/media/cdrom1` with `/media/cdrom` a symlink to either of these.

## 3.12. `/mnt`: Mount point for a temporarily mounted filesystem

### 3.12.1. Purpose

This directory is provided so that the system administrator may temporarily
mount a filesystem as needed. The content of this directory is a local issue
and should not affect the manner in which any program is run.

This directory must not be used by installation programs: a suitable temporary
directory not in use by the system must be used instead.

## 3.13. `/opt`: Add-on application software packages

### 3.13.1. Purpose

`/opt` is reserved for the installation of add-on application software packages.

A package to be installed in `/opt` must locate its static files in a separate
`/opt/<package>` or `/opt/<provider>` directory tree, where `<package>` is a
name that describes the software package and `<provider>` is the provider's
LANANA registered name.

### 3.13.2. Requirements

| Directory    | Description                     |
| ------------ | ------------------------------- |
| `<package>`  | Static package objects          |
| `<provider>` | LANANA registered provider name |

The directories `/opt/bin`, `/opt/doc`, `/opt/include`, `/opt/info`, `/opt/lib`,
and `/opt/man` are reserved for local system administrator use. Packages may
provide "front-end" files intended to be placed in (by linking or copying)
these reserved directories by the local system administrator, but must function
normally in the absence of these reserved directories.

Programs to be invoked by users must be located in the directory
`/opt/<package>/bin` or under the `/opt/<provider>` hierarchy. If the package
includes UNIX manual pages, they must be located in `/opt/<package>/share/man`
or under the `/opt/<provider>` hierarchy, and the same substructure as
`/usr/share/man` must be used.

Package files that are variable (change in normal operation) must be installed
in `/var/opt`. See the section on `/var/opt` for more information.

Host-specific configuration files must be installed in `/etc/opt`. See the
section on `/etc` for more information.

No other package files may exist outside the `/opt`, `/var/opt`, and `/etc/opt`
hierarchies except for those package files that must reside in specific
locations within the filesystem tree in order to function properly. For
example, device lock files must be placed in `/var/lock` and devices must be
located in `/dev`.

Distributions may install and otherwise manage software in `/opt` under an
appropriately registered subdirectory.

#### 3.13.2. Rationale

The use of `/opt` for add-on software is a well-established practice in the
UNIX community. The System V Application Binary Interface [AT&T 1990], based on
the System V Interface Definition (Third Edition), provides for an `/opt`
structure very similar to the one defined here.

The Intel Binary Compatibility Standard v. 2 (iBCS2) also provides a similar
structure for `/opt`.

Generally, all data required to support a package on a system must be present
within `/opt/<package>`, including files intended to be copied into
`/etc/opt/<package>` and `/var/opt/<package>` as well as reserved directories
in `/opt`.

The minor restrictions on distributions using `/opt` are necessary because
conflicts are possible between distribution-installed and locally-installed
software, especially in the case of fixed pathnames found in some binary
software.

The structure of the directories below `/opt/<provider>` is left up to the
packager of the software, though it is recommended that packages are installed
in `/opt/<provider>/<package>` and follow a similar structure to the guidelines
for `/opt/<package>`. A valid reason for diverging from this structure is for
support packages which may have files installed in `/opt/<provider>/lib` or
`/opt/<provider>/bin`.

## 3.14. `/root`: Home directory for the root user (optional)

### 3.14.1. Purpose

The root account's home directory may be determined by developer or local
preference, but this is the recommended default location. [16]

[16] If the home directory of the root account is not stored on the root
partition it will be necessary to make certain it will default to `/` if it
cannot be located.

We recommend against using the root account for tasks that can be performed as
an unprivileged user, and that it be used solely for system administration. For
this reason, we recommend that subdirectories for mail and other applications
not appear in the root account's home directory, and that mail for
administration roles such as root, postmaster, and webmaster be forwarded to an
appropriate user.

## 3.15. `/run`: Run-time variable data

### 3.15.1. Purpose

This directory contains system information data describing the system since it
was booted. Files under this directory must be cleared (removed or truncated as
appropriate) at the beginning of the boot process.

The purposes of this directory were once served by `/var/run`. In general,
programs may continue to use `/var/run` to fulfill the requirements set out for
`/run` for the purposes of backwards compatibility. Programs which have
migrated to use `/run` should cease their usage of `/var/run`, except as noted
in the section on `/var/run`.

Programs may have a subdirectory of `/run`; this is encouraged for programs
that use more than one run-time file. Users may also have a subdirectory of
`/run`, although care must be taken to appropriately limit access rights to
prevent unauthorized use of `/run` itself and other subdirectories. [17]

### 3.15.2. Requirements

Process identifier (PID) files, which were originally placed in `/etc`, must be
placed in `/run`. The naming convention for PID files is `<program-name>.pid`.
For example, the `crond` PID file is named `/run/crond.pid`.

The internal format of PID files remains unchanged. The file must consist of
the process identifier in ASCII-encoded decimal, followed by a newline
character. For example, if `crond` was process number 25, `/run/crond.pid`
would contain three characters: two, five, and newline.

Programs that read PID files should be somewhat flexible in what they accept;
i.e., they should ignore extra whitespace, leading zeroes, absence of the
trailing newline, or additional lines in the PID file. Programs that create PID
files should use the simple specification located in the above paragraph.

System programs that maintain transient UNIX-domain sockets must place them in
this directory or an appropriate subdirectory as outlined above.

[17] `/run` should not be writable for unprivileged users; it is a major
security problem if any user can write in this directory. User-specific
subdirectories should be writable only by each directory's owner.

## 3.16. `/sbin`: System binaries

### 3.16.1. Purpose

Utilities used for system administration (and other root-only commands) are
stored in `/sbin`, `/usr/sbin`, and `/usr/local/sbin`. `/sbin` contains
binaries essential for booting, restoring, recovering, and/or repairing the
system in addition to the binaries in `/bin`. [18] Programs executed after
`/usr` is known to be mounted (when there are no problems) are generally placed
into `/usr/sbin`. Locally-installed system administration programs should be
placed into `/usr/local/sbin`. [19]

### 3.16.2. Requirements

There must be no subdirectories in `/sbin`.

The following commands, or symbolic links to commands, are required in `/sbin`:

| Command  | Description                       |
| -------- | --------------------------------- |
| shutdown | Command to bring the system down. |

### 3.16.3. Specific Options

The following files, or symbolic links to files, must be in `/sbin` if the
corresponding subsystem is installed:

| Command  | Description                                                    |
| -------- | -------------------------------------------------------------- |
| fastboot | Reboot the system without checking the disks (optional)        |
| fasthalt | Stop the system without checking the disks (optional)          |
| fdisk    | Partition table manipulator (optional)                         |
| fsck     | File system check and repair utility (optional)                |
| fsck.*   | File system check and repair utility for a specific filesystem |
|          | (optional)                                                     |
| getty    | The getty program (optional)                                   |
| halt     | Command to stop the system (optional)                          |
| ifconfig | Configure a network interface (optional)                       |
| init     | Initial process (optional)                                     |
| mkfs     | Command to build a filesystem (optional)                       |
| mkfs.*   | Command to build a specific filesystem (optional)              |
| mkswap   | Command to set up a swap area (optional)                       |
| reboot   | Command to reboot the system (optional)                        |
| route    | IP routing table utility (optional)                            |
| swapon   | Enable paging and swapping (optional)                          |
| swapoff  | Disable paging and swapping (optional)                         |
| update   | Daemon to periodically flush filesystem buffers (optional)     |

[18] Originally, `/sbin` binaries were kept in `/etc`.

[19] Deciding what things go into "sbin" directories is simple: if a normal
(not a system administrator) user will ever run it directly, then it must be
placed in one of the "bin" directories. Ordinary users should not have to place
any of the sbin directories in their path.

For example, files such as `chfn` which users only occasionally use must still
be placed in `/usr/bin`. `ping`, although it is absolutely necessary for root
(network recovery and diagnosis) is often used by users and must live in `/bin`
for that reason.

We recommend that users have read and execute permission for everything in
`/sbin` except, perhaps, certain `setuid` and `setgid` programs. The division
between `/bin` and `/sbin` was not created for security reasons or to prevent
users from seeing the operating system, but to provide a good partition between
binaries that everyone uses and ones that are primarily used for administration
tasks. There is no inherent security advantage in making `/sbin` off-limits for
users.

## 3.17. `/srv`: Data for services provided by this system

### 3.17.1. Purpose

`/srv` contains site-specific data which is served by this system.

#### 3.17.1. Rationale

This main purpose of specifying this is so that users may find the location of
the data files for a particular service, and so that services which require a
single tree for readonly data, writable data and scripts (such as cgi scripts)
can be reasonably placed. Data that is only of interest to a specific user
should go in that users' home directory. If the directory and file structure of
the data is not exposed to consumers, it should go in `/var/lib`.

The methodology used to name subdirectories of `/srv` is unspecified as there is
currently no consensus on how this should be done. One method for structuring
data under `/srv` is by protocol, eg. `ftp`, `rsync`, `www`, and `cvs`. On
large systems it can be useful to structure `/srv` by administrative context,
such as `/srv/physics/www`, `/srv/compsci/cvs`, etc. This setup will differ
from host to host. Therefore, no program should rely on a specific subdirectory
structure of `/srv` existing or data necessarily being stored in `/srv`.
However `/srv` should always exist on FHS compliant systems and should be used
as the default location for such data.

Distributions must take care not to remove locally placed files in these
directories without administrator permission.

## 3.18. `/tmp`: Temporary files

### 3.18.1. Purpose

The `/tmp` directory must be made available for programs that require temporary
files.

Programs must not assume that any files or directories in `/tmp` are preserved
between invocations of the program.

#### 3.18.1. Rationale

IEEE standard POSIX.1-2008 lists requirements similar to the above section.

Although data stored in `/tmp` may be deleted in a site-specific manner, it is
recommended that files and directories located in `/tmp` be deleted whenever
the system is booted.

FHS added this recommendation on the basis of historical precedent and common
practice, but did not make it a requirement because system administration is
not within the scope of this standard.
