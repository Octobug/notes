# Chapter 4. The `/usr` Hierarchy

> <https://refspecs.linuxfoundation.org/FHS_3.0/fhs/ch04.html>

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
> directory as meaning 'User System Resources' and not 'user' as was originally
> intended.

`/usr` is the second major section of the filesystem. `/usr` is shareable,
**read-only** data. That means that `/usr` should be shareable between various
FHS-compliant hosts and must not be written to. Any information that is
host-specific or varies with time is stored elsewhere.

## 4.2. Requirements

The following directories, or symbolic links to directories, are required in
`/usr`.

| Directory | Description |
| - | - |
| bin | Most user commands |
| lib | Libraries |
| local | Local hierarchy (empty after main installation) |
| sbin | Non-vital system binaries |
| share | Architecture-independent data |

## 4.3. Specific Options

| Directory | Description |
| - | - |
| `games` | Games and educational binaries (optional) |
| `include` | Header files included by C programs |
| `libexec` | Binaries run by other programs (optional) |
| `lib<qual>` | Alternate Format Libraries (optional) |
| `src` | Source code (optional) |

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

## 4.9. /usr/local : Local hierarchy

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

| Directory | Description |
| - | - |
| `bin` | Local binaries |
| `etc` | Host-specific system configuration for local binaries |
| `games` | Local game binaries |
| `include` | Local C header files |
| `lib` | Local libraries |
| `man` | Local online manuals |
| `sbin` | Local system binaries |
| `share` | Local architecture-independent hierarchy |
| `src` | Local source code |

No other directories, except those listed below, may be in `/usr/local` after
first installing a FHS-compliant system.

### 4.9.3. Specific Options

If directories `/lib<qual>` or `/usr/lib<qual>` exist, the equivalent
directories must also exist in `/usr/local`.

`/usr/local/etc` may be a symbolic link to `/etc/local`.

```txt
Rationale

The consistency of /usr/local/etc is beneficial to installers, and is already
used in other systems. As all of /usr/local needs to be backed up to reproduce
a system, it introduces no additional maintenance overhead, but a symlink to
/etc/local is suitable if systems want all their configuration under one
hierarchy.

Note that /usr/etc is still not allowed: programs in /usr should place
configuration files in /etc.
```

If the directory `/usr/share/color` exists as specified in this document, then
the directory `/usr/local/share/color` must also exist, governed by the same
rules as `/usr/share/color`.

```txt
Rationale

This usage allows the sysadmin a place to install color profiles manually when
necessary.
```

### 4.9.4. `/usr/local/share` : Local architecture-independent hierarchy

The requirements for the contents of this directory are the same as for
`/usr/share`.

Software placed in `/` or `/usr` may be overwritten by system upgrades (though
we recommend that distributions do not overwrite data in `/etc` under these
circumstances). For this reason, local software must not be placed outside of
`/usr/local` without good reason.

## 4.11. /usr/share : Architecture-independent data

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

| Directory | Description |
| - | - |
| man | Online manuals |
| misc | Miscellaneous architecture-independent data |

### 4.11.3. Specific Options

>>> untouched
