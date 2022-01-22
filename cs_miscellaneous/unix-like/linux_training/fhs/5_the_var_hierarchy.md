# 5. The `/var` Hierarchy

> <https://refspecs.linuxfoundation.org/FHS_3.0/fhs/ch05.html>

## Table of Contents

- [5. The `/var` Hierarchy](#5-the-var-hierarchy)
  - [Table of Contents](#table-of-contents)
  - [5.1. Purpose](#51-purpose)
  - [5.2. Requirements](#52-requirements)
  - [5.3. Specific Options](#53-specific-options)
  - [5.4. `/var/account`: Process accounting logs (optional)](#54-varaccount-process-accounting-logs-optional)
    - [5.4.1. Purpose](#541-purpose)
  - [5.5. `/var/cache`: Application cache data](#55-varcache-application-cache-data)
    - [5.5.1. Purpose](#551-purpose)
      - [5.5.1. Rationale](#551-rationale)
    - [5.5.2. Specific Options](#552-specific-options)
    - [5.5.3. `/var/cache/fonts`: Locally-generated fonts (optional)](#553-varcachefonts-locally-generated-fonts-optional)
      - [5.5.3.1. Purpose](#5531-purpose)
      - [5.5.3.2. Specific Options](#5532-specific-options)
    - [5.5.4. `/var/cache/man`: Locally-formatted manual pages (optional)](#554-varcacheman-locally-formatted-manual-pages-optional)
      - [5.5.4.1. Purpose](#5541-purpose)
        - [5.5.4.1. Rationale](#5541-rationale)
  - [5.6. `/var/crash`: System crash dumps (optional)](#56-varcrash-system-crash-dumps-optional)
    - [5.6.1. Purpose](#561-purpose)
  - [5.7. `/var/games`: Variable game data (optional)](#57-vargames-variable-game-data-optional)
    - [5.7.1. Purpose](#571-purpose)
      - [5.7.1. Rationale](#571-rationale)
  - [5.8. `/var/lib`: Variable state information](#58-varlib-variable-state-information)
    - [5.8.1. Purpose](#581-purpose)
    - [5.8.2. Requirements](#582-requirements)
    - [5.8.3. Specific Options](#583-specific-options)
    - [5.8.4. `/var/lib/<editor>`: Editor backup files and state (optional)](#584-varlibeditor-editor-backup-files-and-state-optional)
      - [5.8.4.1. Purpose](#5841-purpose)
        - [5.8.4.1. Rationale](#5841-rationale)
    - [5.8.5. `/var/lib/color`: Color management information (optional)](#585-varlibcolor-color-management-information-optional)
      - [5.8.5.1. Purpose](#5851-purpose)
    - [5.8.6. `/var/lib/hwclock`: State directory for hwclock (optional)](#586-varlibhwclock-state-directory-for-hwclock-optional)
      - [5.8.6.1. Purpose](#5861-purpose)
        - [5.8.6.1. Rationale](#5861-rationale)
    - [5.8.7. `/var/lib/misc`: Miscellaneous variable data](#587-varlibmisc-miscellaneous-variable-data)
      - [5.8.7.1. Purpose](#5871-purpose)
  - [5.9. `/var/lock`: Lock files](#59-varlock-lock-files)
    - [5.9.1. Purpose](#591-purpose)
  - [5.10. `/var/log`: Log files and directories](#510-varlog-log-files-and-directories)
    - [5.10.1. Purpose](#5101-purpose)
    - [5.10.2. Specific Options](#5102-specific-options)
  - [5.11. `/var/mail`: User mailbox files (optional)](#511-varmail-user-mailbox-files-optional)
    - [5.11.1. Purpose](#5111-purpose)
      - [5.11.1. Rationale](#5111-rationale)
  - [5.12. `/var/opt`: Variable data for `/opt`](#512-varopt-variable-data-for-opt)
    - [5.12.1. Purpose](#5121-purpose)
      - [5.12.1. Rationale](#5121-rationale)
  - [5.13. `/var/run`: Run-time variable data](#513-varrun-run-time-variable-data)
    - [5.13.1. Purpose](#5131-purpose)
    - [5.13.2. Requirements](#5132-requirements)
  - [5.14. `/var/spool`: Application spool data](#514-varspool-application-spool-data)
    - [5.14.1. Purpose](#5141-purpose)
    - [5.14.2. Specific Options](#5142-specific-options)
    - [5.14.3. `/var/spool/lpd`: Line-printer daemon print queues (optional)](#5143-varspoollpd-line-printer-daemon-print-queues-optional)
      - [5.14.3.1. Purpose](#51431-purpose)
      - [5.14.3.2. Specific Options](#51432-specific-options)
    - [5.14.4. `/var/spool/rwho`: Rwhod files (optional)](#5144-varspoolrwho-rwhod-files-optional)
      - [5.14.4.1. Purpose](#51441-purpose)
        - [5.14.4.1. Rationale](#51441-rationale)
  - [5.15. `/var/tmp`: Temporary files preserved between system reboots](#515-vartmp-temporary-files-preserved-between-system-reboots)
    - [5.15.1. Purpose](#5151-purpose)
  - [5.16. `/var/yp`: Network Information Service (NIS) database files (optional)](#516-varyp-network-information-service-nis-database-files-optional)
    - [5.16.1. Purpose](#5161-purpose)
      - [5.16.1. Rationale](#5161-rationale)

## 5.1. Purpose

`/var` contains variable data files. This includes spool directories and files,
administrative and logging data, and transient and temporary files.

Some portions of `/var` are not shareable between different systems. For
instance, `/var/log`, `/var/lock`, and `/var/run`. Other portions may be
shared, notably `/var/mail`, `/var/cache/man`, `/var/cache/fonts`, and
`/var/spool/news`.

`/var` is specified here in order to make it possible to mount `/usr`
read-only. Everything that once went into `/usr` that is written to during
system operation (as opposed to installation and software maintenance) must be
in `/var`.

If `/var` cannot be made a separate partition, it is often preferable to move
`/var` out of the root partition and into the `/usr` partition. (This is
sometimes done to reduce the size of the root partition or when space runs low
in the root partition.) However, `/var` must not be linked to `/usr` because
this makes separation of `/usr` and `/var` more difficult and is likely to
create a naming conflict. Instead, link `/var` to `/usr/var`.

Applications must generally not add directories to the top level of `/var`.
Such directories should only be added if they have some system-wide
implication, and in consultation with the FHS mailing list.

## 5.2. Requirements

The following directories, or symbolic links to directories, are required in
`/var`:

| Directory | Description                                      |
| --------- | ------------------------------------------------ |
| cache     | Application cache data                           |
| lib       | Variable state information                       |
| local     | Variable data for /usr/local                     |
| lock      | Lock files                                       |
| log       | Log files and directories                        |
| opt       | Variable data for /opt                           |
| run       | Data relevant to running processes               |
| spool     | Application spool data                           |
| tmp       | Temporary files preserved between system reboots |

Several directories are \`reserved' in the sense that they must not be used
arbitrarily by some new application, since they would conflict with historical
and/or local practice. They are:

    /var/backups
    /var/cron
    /var/msgs
    /var/preserve

## 5.3. Specific Options

The following directories, or symbolic links to directories, must be in
`/var`, if the corresponding subsystem is installed:

| Directory | Description                                                 |
| --------- | ----------------------------------------------------------- |
| account   | Process accounting logs (optional)                          |
| crash     | System crash dumps (optional)                               |
| games     | Variable game data (optional)                               |
| mail      | User mailbox files (optional)                               |
| yp        | Network Information Service (NIS) database files (optional) |

## 5.4. `/var/account`: Process accounting logs (optional)

### 5.4.1. Purpose

This directory holds the current active process accounting log and the
composite process usage data (as used in some UNIX-like systems by `lastcomm`
and `sa`).

## 5.5. `/var/cache`: Application cache data

### 5.5.1. Purpose

`/var/cache` is intended for cached data from applications. Such data is
locally generated as a result of time-consuming I/O or calculation. The
application must be able to regenerate or restore the data. Unlike
`/var/spool`, the cached files can be deleted without data loss. The data must
remain valid between invocations of the application and rebooting the system.

Files located under `/var/cache` may be expired in an application specific
manner, by the system administrator, or both. The application must always be
able to recover from manual deletion of these files (generally because of a
disk space shortage). No other requirements are made on the data format of the
cache directories.

#### 5.5.1. Rationale

The existence of a separate directory for cached data allows system
administrators to set different disk and backup policies from other directories
in `/var`.

### 5.5.2. Specific Options

| Directory   | Description                               |
| ----------- | ----------------------------------------- |
| fonts       | Locally-generated fonts (optional)        |
| man         | Locally-formatted manual pages (optional) |
| www         | WWW proxy or cache data (optional)        |
| `<package>` | Package specific cache data (optional)    |

### 5.5.3. `/var/cache/fonts`: Locally-generated fonts (optional)

#### 5.5.3.1. Purpose

The directory `/var/cache/fonts` should be used to store any
dynamically-created fonts. In particular, all of the fonts which are
automatically generated by `mktexpk` must be located in appropriately-named
subdirectories of `/var/cache/fonts`. [38]

#### 5.5.3.2. Specific Options

Other dynamically created fonts may also be placed in this tree, under
appropriately-named subdirectories of `/var/cache/fonts`.

### 5.5.4. `/var/cache/man`: Locally-formatted manual pages (optional)

#### 5.5.4.1. Purpose

This directory provides a standard location for sites that provide a read-only
`/usr` partition, but wish to allow caching of locally-formatted man pages.
Sites that mount `/usr` as writable (e.g., single-user installations) may
choose not to use `/var/cache/man` and may write formatted man pages into the
`cat<section>` directories in `/usr/share/man` directly. We recommend that most
sites use one of the following options instead:

- Preformat all manual pages alongside the unformatted versions.
- Allow no caching of formatted man pages, and require formatting to be done
  each time a man page is brought up.
- Allow local caching of formatted man pages in `/var/cache/man`.

The structure of `/var/cache/man` needs to reflect both the fact of multiple
man page hierarchies and the possibility of multiple language support.

Given an unformatted manual page that normally appears in
`<path>/man/<locale>/man<section>`, the directory to place formatted man pages
in is `/var/cache/man/<catpath>/<locale>/cat<section>`, where `<catpath>` is
derived from `<path>` by removing any leading `usr` and/or trailing share
pathname components. (Note that the `<locale>` component may be missing.) [39]

Man pages written to `/var/cache/man` may eventually be transferred to the
appropriate preformatted directories in the source man hierarchy or expired;
likewise formatted man pages in the source man hierarchy may be expired if they
are not accessed for a period of time.

If preformatted manual pages come with a system on read-only media (a CD-ROM,
for instance), they must be installed in the source man hierarchy (e.g.
`/usr/share/man/cat<section>`). `/var/cache/man` is reserved as a writable
cache for formatted manual pages.

##### 5.5.4.1. Rationale

Release 1.2 of this standard specified `/var/catman` for this hierarchy. The
path has been moved under `/var/cache` to better reflect the dynamic nature of
the formatted man pages. The directory name has been changed to man to allow
for enhancing the hierarchy to include post-processed formats other than "cat",
such as PostScript, HTML, or DVI.

[38] This standard does not currently incorporate the TeX Directory Structure
(a document that describes the layout TeX files and directories), but it may be
useful reading. It is located at <ftp://ctan.tug.org/tex/>

[39] For example, `/usr/share/man/man1/ls.1` is formatted into
`/var/cache/man/cat1/ls.1`, and `/usr/X11R6/man/<locale>/man3/XtClass.3x` into
`/var/cache/man/X11R6/<locale>/cat3/XtClass.3x`.

## 5.6. `/var/crash`: System crash dumps (optional)

### 5.6.1. Purpose

This directory holds system crash dumps. As of the date of this release of the
standard, system crash dumps were not supported under Linux but may be
supported by other systems which may comply with the FHS.

## 5.7. `/var/games`: Variable game data (optional)

### 5.7.1. Purpose

Any variable data relating to games in `/usr` should be placed here.
`/var/games` should hold the variable data previously found in `/usr`; static
data, such as help text, level descriptions, and so on, must remain elsewhere,
such as `/usr/share/games`.

#### 5.7.1. Rationale

`/var/games` has been given a hierarchy of its own, rather than leaving it
underneath `/var/lib` as in release 1.2 of this standard. The separation allows
local control of backup strategies, permissions, and disk usage, as well as
allowing inter-host sharing and reducing clutter in `/var/lib`. Additionally,
`/var/games` is the path traditionally used by BSD.

## 5.8. `/var/lib`: Variable state information

### 5.8.1. Purpose

This hierarchy holds state information pertaining to an application or the
system. State information is data that programs modify while they run, and that
pertains to one specific host. Users must never need to modify files in
`/var/lib` to configure a package's operation, and the specific file hierarchy
used to store the data must not be exposed to regular users. [40]

State information is generally used to preserve the condition of an application
(or a group of inter-related applications) between invocations and between
different instances of the same application. State information should generally
remain valid after a reboot, should not be logging output, and should not be
spooled data.

An application (or a group of inter-related applications) must use a
subdirectory of `/var/lib` for its data. There is one required subdirectory,
`/var/lib/misc`, which is intended for state files that don't need a
subdirectory; the other subdirectories should only be present if the
application in question is included in the distribution. [41]

`/var/lib/<name>` is the location that must be used for all distribution
packaging support. Different distributions may use different names, of course.

### 5.8.2. Requirements

The following directories, or symbolic links to directories, are required in
`/var/lib`:

| Directory | Description              |
| --------- | ------------------------ |
| misc      | Miscellaneous state data |

### 5.8.3. Specific Options

The following directories, or symbolic links to directories, must be in
`/var/lib`, if the corresponding subsystem is installed:

| Directory   | Description                                       |
| ----------- | ------------------------------------------------- |
| `<editor>`  | Editor backup files and state (optional)          |
| `<pkgtool>` | Packaging support files (optional)                |
| `<package>` | State data for packages and subsystems (optional) |
| color       | Color management information (optional)           |
| hwclock     | State directory for hwclock (optional)            |
| xdm         | X display manager variable data (optional)        |

### 5.8.4. `/var/lib/<editor>`: Editor backup files and state (optional)

#### 5.8.4.1. Purpose

These directories contain saved files generated by any unexpected termination
of an editor (e.g., `elvis`, `jove`, `nvi`).

Other editors may not require a directory for crash-recovery files, but may
require a well-defined place to store other information while the editor is
running. This information should be stored in a subdirectory under `/var/lib`
(for example, GNU Emacs would place lock files in `/var/lib/emacs/lock`).

Future editors may require additional state information beyond crash-recovery
files and lock files — this information should also be placed under
`/var/lib/<editor>`.

##### 5.8.4.1. Rationale

Previous Linux releases, as well as all commercial vendors, use `/var/preserve`
for `vi` or its clones. However, each editor uses its own format for these
crash-recovery files, so a separate directory is needed for each editor.

Editor-specific lock files are usually quite different from the device or
resource lock files that are stored in `/var/lock` and, hence, are stored under
`/var/lib`.

### 5.8.5. `/var/lib/color`: Color management information (optional)

#### 5.8.5.1. Purpose

This directory is the home for ICC color management files installed
dynamically. This directory shall be laid out using the same rules as the
`/usr/share/color` directory.

### 5.8.6. `/var/lib/hwclock`: State directory for hwclock (optional)

#### 5.8.6.1. Purpose

This directory contains the file `/var/lib/hwclock/adjtime`.

##### 5.8.6.1. Rationale

In FHS 2.1, this file was `/etc/adjtime`, but as `hwclock` updates it, that was
obviously incorrect.

### 5.8.7. `/var/lib/misc`: Miscellaneous variable data

#### 5.8.7.1. Purpose

This directory contains variable data not placed in a subdirectory in
`/var/lib`. An attempt should be made to use relatively unique names in this
directory to avoid namespace conflicts. [42]

[40] Data with exposed filesystem structure should be stored in `/srv`.

[41] An important difference between this version of this standard and previous
ones is that applications are now required to use a subdirectory of `/var/lib`.

[42] This hierarchy should contain files stored in `/var/db` in current BSD
releases. These include `locate.database` and `mountdtab`, and the kernel
symbol database(s).

## 5.9. `/var/lock`: Lock files

### 5.9.1. Purpose

Lock files should be stored within the `/var/lock` directory structure.

Lock files for devices and other resources shared by multiple applications,
such as the serial device lock files that were originally found in either
`/usr/spool/locks` or `/usr/spool/uucp`, must now be stored in `/var/lock`. The
naming convention which must be used is "LCK.." followed by the base name of
the device. For example, to lock `/dev/ttyS0` the file "LCK..ttyS0" would be
created. [43]

The format used for the contents of such lock files must be the HDB UUCP lock
file format. The HDB format is to store the process identifier (PID) as a ten
byte ASCII decimal number, with a trailing newline. For example, if process
1230 holds a lock file, it would contain the eleven characters: space, space,
space, space, space, space, one, two, three, zero, and newline.

[43] Then, anything wishing to use `/dev/ttyS0` can read the lock file and act
accordingly (all locks in `/var/lock` should be world-readable).

## 5.10. `/var/log`: Log files and directories

### 5.10.1. Purpose

This directory contains miscellaneous log files. Most logs must be written to
this directory or an appropriate subdirectory.

### 5.10.2. Specific Options

The following files, or symbolic links to files, must be in `/var/log`, if the
corresponding subsystem is installed:

| File     | Description                       |
| -------- | --------------------------------- |
| lastlog  | record of last login of each user |
| messages | system messages from syslogd      |
| wtmp     | record of all logins and logouts  |

## 5.11. `/var/mail`: User mailbox files (optional)

### 5.11.1. Purpose

The mail spool must be accessible through `/var/mail` and the mail spool files
must take the form `<username>`. [44]

User mailbox files in this location must be stored in the standard UNIX mailbox
format.

#### 5.11.1. Rationale

The logical location for this directory was changed from `/var/spool/mail` in
order to bring FHS in-line with nearly every UNIX distribution. This change is
important for inter-operability since a single `/var/mail` is often shared
between multiple hosts and multiple UNIX distribution (despite NFS locking
issues).

It is important to note that there is no requirement to physically move the
mail spool to this location. However, programs and header files must be changed
to use `/var/mail`.

[44] Note that `/var/mail` may be a symbolic link to another directory.

## 5.12. `/var/opt`: Variable data for `/opt`

### 5.12.1. Purpose

Variable data of the packages in `/opt` must be installed in
`/var/opt/<subdir>`, where `<subdir>` is the name of the subtree in `/opt`
where the static data from an add-on software package is stored, except where
superseded by another file in `/etc`. No structure is imposed on the internal
arrangement of `/var/opt/<subdir>`.

#### 5.12.1. Rationale

Refer to the rationale for `/opt`.

## 5.13. `/var/run`: Run-time variable data

### 5.13.1. Purpose

This directory was once intended for system information data describing the
system since it was booted. These functions have been moved to `/run`; this
directory exists to ensure compatibility with systems and software using an
older version of this specification.

### 5.13.2. Requirements

In general, the requirements for `/run` shall also apply to `/var/run`. It is
valid to implement `/var/run` as a symlink to `/run`.

The `utmp` file, which stores information about who is currently using the
system, is located in this directory.

Programs should not access both `/var/run` and `/run` directly, except to
access `/var/run/utmp`. [45]

[45] This is to prevent confusion about where transient files are located. In
general, a program should use either `/var/run` or `/run` to access these
files, not both.

## 5.14. `/var/spool`: Application spool data

### 5.14.1. Purpose

`/var/spool` contains data which is awaiting some kind of later processing.
Data in `/var/spool` represents work to be done in the future (by a program,
user, or administrator); often data is deleted after it has been processed. [46]

### 5.14.2. Specific Options

The following directories, or symbolic links to directories, must be in
`/var/spool`, if the corresponding subsystem is installed:

| Directory | Description                         |
| --------- | ----------------------------------- |
| lpd       | Printer spool directory (optional)  |
| mqueue    | Outgoing mail queue (optional)      |
| news      | News spool directory (optional)     |
| rwho      | Rwhod files (optional)              |
| uucp      | Spool directory for UUCP (optional) |

### 5.14.3. `/var/spool/lpd`: Line-printer daemon print queues (optional)

#### 5.14.3.1. Purpose

The lock file for `lpd`, `lpd.lock`, must be placed in `/var/spool/lpd`. It is
suggested that the lock file for each printer be placed in the spool directory
for that specific printer and named `lock`.

#### 5.14.3.2. Specific Options

| Directory | Description                              |
| --------- | ---------------------------------------- |
| printer   | Spools for a specific printer (optional) |

### 5.14.4. `/var/spool/rwho`: Rwhod files (optional)

#### 5.14.4.1. Purpose

This directory holds the `rwhod` information for other systems on the local net.

##### 5.14.4.1. Rationale

Some BSD releases use `/var/rwho` for this data; given its historical location
in `/var/spool` on other systems and its approximate fit to the definition of
\`spooled' data, this location was deemed more appropriate.

[46] UUCP lock files must be placed in `/var/lock`. See the above section on
`/var/lock`.

## 5.15. `/var/tmp`: Temporary files preserved between system reboots

### 5.15.1. Purpose

The `/var/tmp` directory is made available for programs that require temporary
files or directories that are preserved between system reboots. Therefore, data
stored in `/var/tmp` is more persistent than data in `/tmp`.

Files and directories located in `/var/tmp` must not be deleted when the system
is booted. Although data stored in `/var/tmp` is typically deleted in a
site-specific manner, it is recommended that deletions occur at a less frequent
interval than `/tmp`.

## 5.16. `/var/yp`: Network Information Service (NIS) database files (optional)

### 5.16.1. Purpose

Variable data for the Network Information Service (NIS), formerly known as the
Sun Yellow Pages (YP), must be placed in this directory.

#### 5.16.1. Rationale

`/var/yp` is the standard directory for NIS (YP) data and is almost exclusively
used in NIS documentation and systems. [47]

[47] NIS should not be confused with Sun NIS+, which uses a different
directory, `/var/nis`.
