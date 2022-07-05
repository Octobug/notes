# 5 The Filesystem

Unix-like OSs represent almost everything within the filesystem. In most cases,
the filesystem is used as a rendezvous point to connect clients with the
drivers they are seeking.

The basic purpose of a filesystem is to represent and organize the system’s
storage resources. However, programmers have been eager to avoid reinventing
the wheel when it comes to managing other types of objects. It has often proved
convenient to map these objects into the filesystem namespace. This unification
has some advantages (consistent programming interface, easy access from the
shell) and some disadvantages (filesystem implementations suggestive of
Frankenstein’s monster), but like it or not, this is the UNIX (and hence, the
Linux) way.

The filesystem can be thought of as comprising four main components:

- A namespace – a way to name things and organize them in a hierarchy
- An API – a set of system calls for navigating and manipulating objects
- Security models – schemes for protecting, hiding, and sharing things
- An implementation – software to tie the logical model to the hardware

Modern kernels define an abstract interface that accommodates many different
back-end filesystems. Some portions of the file tree are handled by traditional
disk-based implementations. Others are fielded by separate drivers within the
kernel.

Unfortunately, the architectural boundaries are not clearly drawn, and quite a
few special cases exist.

Another complicating factor is that the kernel supports more than one type of
disk-based filesystem. The predominant standards are the ext4, XFS, and UFS
filesystems, along with Oracle’s ZFS and Btrfs.

## 5.3 Organization of the File Tree

`man hier`

UNIX systems have never been well organized.

In many cases, files are divided by function and not by how likely they are to
change, making it difficult to upgrade the operating system.

Unfortunately, the file tree has many hidden dependencies, so such efforts
usually end up creating problems. When offered a choice of locations, always
accept the default unless you have a specific and compelling reason to do
otherwise.

The root filesystem includes at least the root directory and a minimal set of
files and subdirectories. The file that contains the OS kernel usually lives
under `/boot`, but its exact name and location can vary.

Also part of the root filesystem are `/etc` for critical system and
configuration files, `/sbin` and `/bin` for important utilities, and sometimes
`/tmp` for temporary files. The `/dev` directory was traditionally part of the
root filesystem, but these days it’s a virtual filesystem that’s mounted
separately.

Some systems keep shared library files and a few other oddments, such as the C
preprocessor, in the `/lib` or `/lib64` directory. Others have moved these
items into `/usr/lib`, sometimes leaving `/lib` as a symbolic link.

The directories `/usr` and `/var` are also of great importance. `/usr` is where
most standard-but-not-system-critical programs are kept, along with various
other booty such as on-line manuals and most libraries. `/var` houses spool
directories, log files, accounting information, and various other items that
grow or change rapidly and that vary on each host. Both `/usr` and `/var` must
be available to enable the system to come up all the way to multiuser mode.

The secular trend is toward having one big root filesystem. Large hard disks
and increasingly sophisticated filesystem implementations have reduced the
value of partitioning.

In cases where partitioning is used, it’s most frequently an attempt to prevent
one part of the file tree from consuming all available space and bringing the
entire system to a halt. Accordingly, `/var`, `/tmp`, and user home directories
are some of the most common candidates for having their own partitions.
Dedicated filesystems can also store bulky items such as source code libraries
and databases.

### Standard directories and their contents

| Pathname | Contents |
| - | - |
| `/bin` | Core operating system commands |
| `/boot` | Boot loader, kernel, and files needed by the kernel |
| `/compat` | On FreeBSD, files and libraries for Linux binary compatibility |
| `/dev` | Device entries for disks, printers, pseudo-terminals, etc. |
| `/etc` | Critical startup and configuration files |
| `/home` | Default home directories for users |
| `/lib` | Libraries, shared libraries, and commands used by `/bin`, `/sbin` |
| `/media` | Mount points for filesystems on removable media |
| `/mnt` | Temporary mount points, mounts for removable media |
| `/opt` | Optional software packages (rarely used, for compatibility) |
| `/proc` | Information about all running processes |
| `/root` | Home directory of the superuser (sometimes just /) |
| `/run` | Rendezvous points for running programs (PIDs, sockets, etc.) |
| `/sbin` | Core operating system commands |
| | Originally for statically linked bin, nowadays all binaries are |
| | dynamically linked and there is no real difference to `/sbin`. |
| `/srv` | Files held for distribution through web or other servers |
| `/sys` | A plethora of different kernel interfaces (Linux) |
| `/tmp` | Temporary files that may disappear between reboots |
| `/usr` | Hierarchy of secondary files and commands |
| - `/usr/bin` | Most commands and executable files |
| - `/usr/include` | Header files for compiling C programs |
| - `/usr/lib` | Libraries; also, support files for standard programs |
| - `/usr/local` | Local software or configuration data; mirrors `/usr` |
| - `/usr/sbin` | Less essential commands for administration and repair |
| - `/usr/share` | Items that might be common to multiple systems |
| - `/usr/share/man` | On-line manual pages |
| - `/usr/src` | Source code for nonlocal software (not widely used) |
| - `/usr/tmp` | More temporary space (preserved between reboots) |
| `/var` | System-specific data and a few configuration files |
| - `/var/adm` | Varies: logs, setup records, strange administrative bits |
| - `/var/log` | System log files |
| - `/var/run` | Same function as `/run`; now often a symlink |
| - `/var/spool` | Spooling (storage) directories for printers, mail, etc. |
| - `/var/tmp` | More temporary space (preserved between reboots) |
