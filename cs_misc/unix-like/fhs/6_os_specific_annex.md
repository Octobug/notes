# 6. Operating System Specific Annex

> <https://refspecs.linuxfoundation.org/FHS_3.0/fhs/ch06.html>

This section is for additional requirements and recommendations that only apply
to a specific operating system. The material in this section should never
conflict with the base standard.

## Table of Contents

- [6. Operating System Specific Annex](#6-operating-system-specific-annex)
  - [Table of Contents](#table-of-contents)
  - [6.1. Linux](#61-linux)
    - [6.1.1. `/`: Root directory](#611--root-directory)
    - [6.1.2. `/bin`: Essential user command binaries (for use by all users)](#612-bin-essential-user-command-binaries-for-use-by-all-users)
    - [6.1.3. `/dev`: Devices and special files](#613-dev-devices-and-special-files)
      - [6.1.3. Rationale](#613-rationale)
    - [6.1.4. `/etc`: Host-specific system configuration](#614-etc-host-specific-system-configuration)
    - [6.1.5. `/proc`: Kernel and process information virtual filesystem](#615-proc-kernel-and-process-information-virtual-filesystem)
    - [6.1.6. `/sbin`: Essential system binaries](#616-sbin-essential-system-binaries)
    - [6.1.7. `/sys`: Kernel and system information virtual filesystem](#617-sys-kernel-and-system-information-virtual-filesystem)
    - [6.1.8. `/usr/include`: Header files included by C programs](#618-usrinclude-header-files-included-by-c-programs)
    - [6.1.9. `/usr/src`: Source code](#619-usrsrc-source-code)
      - [6.1.9. Note](#619-note)
      - [6.1.9. Rationale](#619-rationale)
    - [6.1.10. `/var/spool/cron`: `cron` and `at` jobs](#6110-varspoolcron-cron-and-at-jobs)

## 6.1. Linux

This is the annex for the Linux operating system.

### 6.1.1. `/`: Root directory

On Linux systems, if the kernel is located in `/`, we recommend using the names
`vmlinux` or `vmlinuz`, which have been used in recent Linux kernel source
packages.

### 6.1.2. `/bin`: Essential user command binaries (for use by all users)

Linux systems which require them place these additional files into `/bin`:

- `setserial`

### 6.1.3. `/dev`: Devices and special files

The following devices must exist under `/dev`.

`/dev/null`

All data written to this device is discarded. A read from this device will
return an EOF condition.

`/dev/zero`

This device is a source of zeroed out data. All data written to this device is
discarded. A read from this device will return as many bytes containing the
value zero as was requested.

`/dev/tty`

This device is a synonym for the controlling terminal of a process. Once this
device is opened, all reads and writes will behave as if the actual controlling
terminal device had been opened.

#### 6.1.3. Rationale

Previous versions of the FHS had stricter requirements for `/dev`. Other
devices may also exist in `/dev`. Device names may exist as symbolic links to
other device nodes located in `/dev` or subdirectories of `/dev`. There is no
requirement concerning major/minor number values.

### 6.1.4. `/etc`: Host-specific system configuration

Linux systems which require them place these additional files into `/etc`.

- `lilo.conf`

### 6.1.5. `/proc`: Kernel and process information virtual filesystem

The `proc` filesystem is the de-facto standard Linux method for handling
process and system information, rather than `/dev/kmem` and other similar
methods. We strongly encourage this for the storage and retrieval of process
information as well as other kernel and memory information.

### 6.1.6. `/sbin`: Essential system binaries

Linux systems place commands relating to filesystem maintenance and boot loader
management into `/sbin`.

Optional files for `/sbin`:

- Static binaries:
  - `ldconfig`
  - `sln`
  - `ssync`

  Static `ln` (`sln`) and static `sync` (`ssync`) are useful when things go
  wrong. The primary use of `sln` (to repair incorrect symlinks in `/lib` after
  a poorly orchestrated upgrade) is no longer a major concern now that the
  `ldconfig` program (usually located in `/usr/sbin`) exists and can act as a
  guiding hand in upgrading the dynamic libraries. Static `sync` is useful in
  some emergency situations. Note that these need not be statically linked
  versions of the standard `ln` and `sync`, but may be.

  The `ldconfig` binary is optional for `/sbin` since a site may choose to run
  `ldconfig` at boot time, rather than only when upgrading the shared
  libraries. (It's not clear whether or not it is advantageous to run
  `ldconfig` on each boot.) Even so, some people like `ldconfig` around for the
  following (all too common) situation:
  1. I've just removed `/lib/<file>`.
  2. I can't find out the name of the library because `ls` is dynamically
    linked, I'm using a shell that doesn't have `ls` built-in, and I don't know
    about using "echo *" as a replacement.
  3. I have a static `sln`, but I don't know what to call the link.

- Miscellaneous:
  - `ctrlaltdel`
  - `kbdrate`

  So as to cope with the fact that some keyboards come up with such a high
  repeat rate as to be unusable, `kbdrate` may be installed in `/sbin` on some
  systems.

  Since the default action in the kernel for the Ctrl-Alt-Del key combination
  is an instant hard reboot, it is generally advisable to disable the behavior
  before mounting the root filesystem in read-write mode. Some `init` suites
  are able to disable Ctrl-Alt-Del, but others may require the `ctrlaltdel`
  program, which may be installed in `/sbin` on those systems.

### 6.1.7. `/sys`: Kernel and system information virtual filesystem

The `sys` filesystem is the location where information about devices, drivers,
and some kernel features is exposed. Its underlying structure is determined by
the particular Linux kernel being used at the moment, and is otherwise
unspecified.

### 6.1.8. `/usr/include`: Header files included by C programs

These symbolic links are required if a C or C++ compiler is installed and only
for systems not based on `glibc`.

    /usr/include/asm -> /usr/src/linux/include/asm-<arch>
    /usr/include/linux -> /usr/src/linux/include/linux

### 6.1.9. `/usr/src`: Source code

For systems based on `glibc`, there are no specific guidelines for this
directory. For systems based on Linux `libc` revisions prior to `glibc`, the
following guidelines and rationale apply:

The only source code that should be placed in a specific location is the Linux
kernel source code. It is located in `/usr/src/linux`.

If a C or C++ compiler is installed, but the complete Linux kernel source code
is not installed, then the include files from the kernel source code must be
located in these directories:

    /usr/src/linux/include/asm-<arch>
    /usr/src/linux/include/linux

`<arch>` is the name of the system architecture.

#### 6.1.9. Note

`/usr/src/linux` may be a symbolic link to a kernel source code tree.

#### 6.1.9. Rationale

It is important that the kernel include files be located in `/usr/src/linux`
and not in `/usr/include` so there are no problems when system administrators
upgrade their kernel version for the first time.

### 6.1.10. `/var/spool/cron`: `cron` and `at` jobs

This directory contains the variable data for the `cron` and `at` programs.
