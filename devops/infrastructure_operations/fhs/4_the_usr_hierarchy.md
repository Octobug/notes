# Chapter 4. The `/usr` Hierarchy

> <https://refspecs.linuxfoundation.org/FHS_3.0/fhs/ch04.html>

## Table of Contents

- [Chapter 4. The `/usr` Hierarchy](#chapter-4-the-usr-hierarchy)
  - [Table of Contents](#table-of-contents)
  - [4.1. Purpose](#41-purpose)
  - [4.2. Requirements](#42-requirements)
  - [4.3. Specific Options](#43-specific-options)
  - [4.4. `/usr/bin`: Most user commands](#44-usrbin-most-user-commands)
    - [4.4.1. Purpose](#441-purpose)
    - [4.4.2. Requirements](#442-requirements)
    - [4.4.3. Specific Options](#443-specific-options)
      - [4.4.3. Rationale](#443-rationale)
  - [4.5. `/usr/include`: Directory for standard include files.](#45-usrinclude-directory-for-standard-include-files)
    - [4.5.1. Purpose](#451-purpose)
    - [4.5.2. Specific Options](#452-specific-options)
  - [4.6. `/usr/lib`: Libraries for programming and packages](#46-usrlib-libraries-for-programming-and-packages)
    - [4.6.1. Purpose](#461-purpose)
    - [4.6.2. Specific Options](#462-specific-options)
  - [4.7. `/usr/libexec`: Binaries run by other programs (optional)](#47-usrlibexec-binaries-run-by-other-programs-optional)
    - [4.7.1. Purpose](#471-purpose)
      - [4.7.1. Rationale](#471-rationale)
  - [4.8. `/usr/lib<qual>`: Alternate format libraries (optional)](#48-usrlibqual-alternate-format-libraries-optional)
    - [4.8.1. Purpose](#481-purpose)
  - [4.9. `/usr/local`: Local hierarchy](#49-usrlocal-local-hierarchy)
    - [4.9.1. Purpose](#491-purpose)
    - [4.9.2. Requirements](#492-requirements)
    - [4.9.3. Specific Options](#493-specific-options)
      - [4.9.3. Rationale 1](#493-rationale-1)
      - [4.9.3. Rationale 2](#493-rationale-2)
    - [4.9.4. `/usr/local/share`: Local architecture-independent hierarchy](#494-usrlocalshare-local-architecture-independent-hierarchy)
  - [4.10. `/usr/sbin`: Non-essential standard system binaries](#410-usrsbin-non-essential-standard-system-binaries)
    - [4.10.1. Purpose](#4101-purpose)
    - [4.10.2. Requirements](#4102-requirements)
  - [4.11. /usr/share : Architecture-independent data](#411-usrshare--architecture-independent-data)
    - [4.11.1. Purpose](#4111-purpose)
    - [4.11.2. Requirements](#4112-requirements)
    - [4.11.3. Specific Options](#4113-specific-options)

## 4.1. Purpose

> <https://tldp.org/LDP/Linux-Filesystem-Hierarchy/html/usr.html>
>
> `/usr` usually contains by far the largest share of data on a system. It
> contains all the user binaries, their documentation, libraries, header files,
> etc.... In the original Unix implementations, `/usr` was where the home
> directories of the users were placed (that is to say, `/usr/someone` was then
> the directory now known as `/home/someone`). In current Unices, `/usr` is
> where user-land programs and data are. The name hasn't changed, but it's
> meaning has narrowed and lengthened from "everything user related" to "user
> usable programs and data". As such, some people may now refer to this
> directory as meaning **User System Resources** and not 'user' as was
> originally intended.

`/usr` is the second major section of the filesystem. `/usr` is shareable,
**read-only** data. That means that `/usr` should be shareable between various
FHS-compliant hosts and must not be written to. Any information that is
host-specific or varies with time is stored elsewhere.

Large software packages must not use a direct subdirectory under the `/usr`
hierarchy.

## 4.2. Requirements

The following directories, or symbolic links to directories, are required in
`/usr`.

| Directory | Description                                     |
| --------- | ----------------------------------------------- |
| bin       | Most user commands                              |
| lib       | Libraries                                       |
| local     | Local hierarchy (empty after main installation) |
| sbin      | Non-vital system binaries                       |
| share     | Architecture-independent data                   |

## 4.3. Specific Options

| Directory   | Description                               |
| ----------- | ----------------------------------------- |
| `games`     | Games and educational binaries (optional) |
| `include`   | Header files included by C programs       |
| `libexec`   | Binaries run by other programs (optional) |
| `lib<qual>` | Alternate Format Libraries (optional)     |
| `src`       | Source code (optional)                    |

An exception is made for the X Window System because of considerable precedent
and widely-accepted practice.

The following symbolic links to directories may be present. This possibility is
based on the need to preserve compatibility with older systems until all
distribution can be assumed to use the `/var` hierarchy.

```ln
/usr/spool -> /var/spool
/usr/tmp -> /var/tmp
/usr/spool/locks -> /var/lock
```

Once a system no longer requires any one of the above symbolic links, the link
may be removed, if desired.

## 4.4. `/usr/bin`: Most user commands

### 4.4.1. Purpose

This is the primary directory of executable commands on the system.

### 4.4.2. Requirements

There must be no subdirectories in `/usr/bin`.

### 4.4.3. Specific Options

The following files, or symbolic links to files, must be in `/usr/bin`, if the
corresponding subsystem is installed:

| Command | Description                                             |
| ------- | ------------------------------------------------------- |
| perl    | The Practical Extraction and Report Language (optional) |
| python  | The Python interpreted language (optional)              |
| tclsh   | Simple shell containing Tcl interpreter (optional)      |
| wish    | Simple Tcl/Tk windowing shell (optional)                |
| expect  | Program for interactive dialog (optional)               |

#### 4.4.3. Rationale

In many executable scripts, the interpreter to be invoked to execute the script
is specified using `#!path_to_interpreter` on the first line of a script. To
make such scripts portable among different systems, it is advantageous to
standardize the interpreter locations. The shell interpreter is already fixed
in `/bin` by this specification, but interpreters for Perl, Python, Tcl and
expect may be installed in various places. The locations specified here may be
implemented as symbolic links to the physical location of the interpreters.

## 4.5. `/usr/include`: Directory for standard include files.

### 4.5.1. Purpose

This is where all of the system's general-use include files for the C
programming language should be placed.

### 4.5.2. Specific Options

The following directories, or symbolic links to directories, must be in
`/usr/include`, if the corresponding subsystem is installed:

| Directory | Description                                |
| --------- | ------------------------------------------ |
| bsd       | BSD compatibility include files (optional) |

## 4.6. `/usr/lib`: Libraries for programming and packages

### 4.6.1. Purpose

`/usr/lib` includes object files and libraries. [21] On some systems, it may
also include internal binaries that are not intended to be executed directly by
users or shell scripts. [22]

Applications may use a single subdirectory under `/usr/lib`. If an application
uses a subdirectory, all architecture-dependent data exclusively used by the
application must be placed within that subdirectory. [23]

### 4.6.2. Specific Options

For historical reasons, `/usr/lib/sendmail` must be a symbolic link which
resolves to the sendmail-compatible command provided by the system's mail
transfer agent, if the latter exists. [24] [25]

[21] Miscellaneous architecture-independent application-specific static files
and subdirectories must be placed in `/usr/share`.

[22] See below, in the `/usr/libexec` section, for a discussion of `/usr/lib`
vs. `/usr/libexec` for executable binaries.

[23] For example, the `perl5` subdirectory for Perl 5 modules and libraries.

[24] Some executable commands such as `makewhatis` and `sendmail` have also
been traditionally placed in `/usr/lib`. `makewhatis` is an internal binary and
must be placed in a binary directory; users access only `catman`. Newer
`sendmail` binaries are now placed by default in `/usr/sbin`. Additionally,
systems using a sendmail-compatible mail transfer agent must provide
`/usr/sbin/sendmail` as the `sendmail` command, either as the executable itself
or as a symlink to the appropriate executable.

[25] Host-specific data for the X Window System must not be stored in
`/usr/lib/X11`. Host-specific configuration files such as `xorg.conf` must be
stored in `/etc/X11`. This includes configuration data such as `system.twmrc`
even if it is only made a symbolic link to a more global configuration file
(probably in `/usr/lib/X11`).

## 4.7. `/usr/libexec`: Binaries run by other programs (optional)

### 4.7.1. Purpose

`/usr/libexec` includes internal binaries that are not intended to be executed
directly by users or shell scripts. Applications may use a single subdirectory
under `/usr/libexec`.

Applications which use `/usr/libexec` in this way must not also use `/usr/lib`
to store internal binaries, though they may use `/usr/lib` for the other
purposes documented here.

#### 4.7.1. Rationale

Some previous versions of this document did not support `/usr/libexec`, despite
it being standard practice in a number of environments. [26] To accomodate this
restriction, it became common practice to use `/usr/lib` instead. Either
practice is now acceptable, but each application must choose one way or the
other to organize itself.

[26] See, for example, the "GNU Coding Standards" from the Free Software
Foundation.

## 4.8. `/usr/lib<qual>`: Alternate format libraries (optional)

### 4.8.1. Purpose

`/usr/lib<qual>` performs the same role as `/usr/lib` for an alternate binary
format, except that the symbolic links `/usr/lib<qual>/sendmail` and
`/usr/lib<qual>/X11` are not required. [27]

[27] The case where `/usr/lib` and `/usr/lib<qual>` are the same (one is a
symbolic link to the other) these files and the per-application subdirectories
will exist.

## 4.9. `/usr/local`: Local hierarchy

### 4.9.1. Purpose

The `/usr/local` hierarchy is for use by the system administrator when
installing software locally. It needs to be safe from being overwritten when
the system software is updated. It may be used for programs and data that are
shareable amongst a group of hosts, but not found in `/usr`.

Locally installed software must be placed within `/usr/local` rather than `/usr`
unless it is being installed to replace or upgrade software in `/usr`.

### 4.9.2. Requirements

The following directories, or symbolic links to directories, must be in
`/usr/local`

| Directory | Description                                           |
| --------- | ----------------------------------------------------- |
| `bin`     | Local binaries                                        |
| `etc`     | Host-specific system configuration for local binaries |
| `games`   | Local game binaries                                   |
| `include` | Local C header files                                  |
| `lib`     | Local libraries                                       |
| `man`     | Local online manuals                                  |
| `sbin`    | Local system binaries                                 |
| `share`   | Local architecture-independent hierarchy              |
| `src`     | Local source code                                     |

No other directories, except those listed below, may be in `/usr/local` after
first installing a FHS-compliant system.

### 4.9.3. Specific Options

If directories `/lib<qual>` or `/usr/lib<qual>` exist, the equivalent
directories must also exist in `/usr/local`.

`/usr/local/etc` may be a symbolic link to `/etc/local`.

#### 4.9.3. Rationale 1

The consistency of `/usr/local/etc` is beneficial to installers, and is already
used in other systems. As all of `/usr/local` needs to be backed up to reproduce
a system, it introduces no additional maintenance overhead, but a symlink to
`/etc/local` is suitable if systems want all their configuration under one
hierarchy.

Note that `/usr/etc` is still not allowed: programs in `/usr` should place
configuration files in `/etc`.

If the directory `/usr/share/color` exists as specified in this document, then
the directory `/usr/local/share/color` must also exist, governed by the same
rules as `/usr/share/color`.

#### 4.9.3. Rationale 2

This usage allows the sysadmin a place to install color profiles manually when
necessary.

### 4.9.4. `/usr/local/share`: Local architecture-independent hierarchy

The requirements for the contents of this directory are the same as for
`/usr/share`.

[28] Software placed in `/` or `/usr` may be overwritten by system upgrades (though
we recommend that distributions do not overwrite data in `/etc` under these
circumstances). For this reason, local software must not be placed outside of
`/usr/local` without good reason.

## 4.10. `/usr/sbin`: Non-essential standard system binaries

### 4.10.1. Purpose

This directory contains any non-essential binaries used exclusively by the
system administrator. System administration programs that are required for
system repair, system recovery, mounting `/usr`, or other essential functions
must be placed in `/sbin` instead. [29]

### 4.10.2. Requirements

There must be no subdirectories in `/usr/sbin`.

[29] Locally installed system administration programs should be placed in
`/usr/local/sbin`.

## 4.11. /usr/share : Architecture-independent data

>>>>> <https://refspecs.linuxfoundation.org/FHS_3.0/fhs/ch04s11.html>

### 4.11.1. Purpose

The `/usr/share` hierarchy is for all read-only architecture independent data
files.

This hierarchy is intended to be shareable among all architecture platforms of
a given OS; thus, for example, a site with i386, Alpha, and PPC platforms might
maintain a single `/usr/share` directory that is centrally-mounted. Note,
however, that `/usr/share` is generally not intended to be shared by different
OSes or by different releases of the same OS.

Any program or package which contains or requires data that doesn't need to be
modified should store that data in `/usr/share` (or `/usr/local/share`, if
installed locally). It is recommended that a subdirectory be used in
`/usr/share` for this purpose. Applications using a single file may use
`/usr/share/misc`.

Game data stored in `/usr/share/games` must be purely static data. Any
modifiable files, such as score files, game play logs, and so forth, should be
placed in `/var/games`.

### 4.11.2. Requirements

The following directories, or symbolic links to directories, must be in
`/usr/share`.

| Directory | Description                                 |
| --------- | ------------------------------------------- |
| man       | Online manuals                              |
| misc      | Miscellaneous architecture-independent data |

### 4.11.3. Specific Options

>>> untouched
