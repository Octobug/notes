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
  - [4.11. `/usr/share`: Architecture-independent data](#411-usrshare-architecture-independent-data)
    - [4.11.1. Purpose](#4111-purpose)
    - [4.11.2. Requirements](#4112-requirements)
    - [4.11.3. Specific Options](#4113-specific-options)
    - [4.11.4. `/usr/share/color`: Color management information (optional)](#4114-usrsharecolor-color-management-information-optional)
      - [4.11.4.1. Purpose](#41141-purpose)
      - [4.11.4.2. Specific Options](#41142-specific-options)
    - [4.11.5. `/usr/share/dict`: Word lists (optional)](#4115-usrsharedict-word-lists-optional)
      - [4.11.5.1. Purpose](#41151-purpose)
        - [4.11.5.1. Rationale](#41151-rationale)
      - [4.11.5.2. Specific Options](#41152-specific-options)
    - [4.11.6. `/usr/share/man`: Manual pages](#4116-usrshareman-manual-pages)
      - [4.11.6.1. Purpose](#41161-purpose)
      - [4.11.6.2. Specific Options](#41162-specific-options)
    - [4.11.7. `/usr/share/misc`: Miscellaneous architecture-independent data](#4117-usrsharemisc-miscellaneous-architecture-independent-data)
      - [4.11.7.1. Specific Options](#41171-specific-options)
    - [4.11.8. `/usr/share/ppd`: Printer definitions (optional)](#4118-usrshareppd-printer-definitions-optional)
      - [4.11.8.1. Purpose](#41181-purpose)
    - [4.11.9. `/usr/share/sgml`: SGML data (optional)](#4119-usrsharesgml-sgml-data-optional)
      - [4.11.9.1. Purpose](#41191-purpose)
      - [4.11.9.2. Specific Options](#41192-specific-options)
    - [4.11.10. `/usr/share/xml`: XML data (optional)](#41110-usrsharexml-xml-data-optional)
      - [4.11.10.1. Purpose](#411101-purpose)
      - [4.11.10.2. Specific Options](#411102-specific-options)
  - [4.12. `/usr/src`: Source code (optional)](#412-usrsrc-source-code-optional)
    - [4.12.1. Purpose](#4121-purpose)

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

## 4.11. `/usr/share`: Architecture-independent data

### 4.11.1. Purpose

The `/usr/share` hierarchy is for all read-only architecture independent data
files. [30]

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
`/usr/share`

| Directory | Description                                 |
| --------- | ------------------------------------------- |
| man       | Online manuals                              |
| misc      | Miscellaneous architecture-independent data |

### 4.11.3. Specific Options

The following directories, or symbolic links to directories, must be in
`/usr/share`, if the corresponding subsystem is installed:

| Directory | Description                                             |
| --------- | ------------------------------------------------------- |
| color     | Color management information (optional)                 |
| dict      | Word lists (optional)                                   |
| doc       | Miscellaneous documentation (optional)                  |
| games     | Static data files for `/usr/games` (optional)           |
| info      | Primary directory for GNU Info system (optional)        |
| locale    | Locale information (optional)                           |
| nls       | Message catalogs for Native language support (optional) |
| ppd       | Printer definitions (optional)                          |
| sgml      | SGML data (optional)                                    |
| terminfo  | Directories for terminfo database (optional)            |
| tmac      | troff macros not distributed with groff (optional)      |
| xml       | XML data (optional)                                     |
| zoneinfo  | Timezone information and configuration (optional)       |

It is recommended that application-specific, architecture-independent
directories be placed here. Such directories include `groff`, `perl`,
`ghostscript`, `texmf`, and `kbd` (Linux) or `syscons` (BSD). They may,
however, be placed in `/usr/lib` for backwards compatibility, at the
distributor's discretion. Similarly, a `/usr/lib/games` hierarchy may be used
in addition to the `/usr/share/games` hierarchy if the distributor wishes to
place some game data there.

### 4.11.4. `/usr/share/color`: Color management information (optional)

#### 4.11.4.1. Purpose

This directory is the home for ICC color management files installed by the
system.

#### 4.11.4.2. Specific Options

The following directories must be in `/usr/share/color`, if the corresponding
subsystem is installed:

| Directory | Description                   |
| --------- | ----------------------------- |
| icc       | ICC color profiles (optional) |

The top-level directory `/usr/share/color` must not contain any files; all
files should be in subdirectories of `/usr/share/color`.

### 4.11.5. `/usr/share/dict`: Word lists (optional)

#### 4.11.5.1. Purpose

This directory is the home for word lists on the system; Traditionally this
directory contains only the English `words` file, which is used by `look(1)` and
various spelling programs. `words` may use either American or British spelling.

##### 4.11.5.1. Rationale

The reason that only word lists are located here is that they are the only
files common to all spell checkers.

#### 4.11.5.2. Specific Options

The following files, or symbolic links to files, must be in `/usr/share/dict`,
if the corresponding subsystem is installed:

| File  | Description                      |
| ----- | -------------------------------- |
| words | List of English words (optional) |

Sites that require both American and British spelling may link words to
`­/usr/share/dict/american-english` or `/usr/share/dict/british-english`.

Word lists for other languages may be added using the English name for that
language, e.g., `/usr/share/dict/french`, `/usr/share/dict/danish`, etc. These
should, if possible, use a character set based on Unicode, with the UTF-8
character set being the preferred option.

Other word lists must be included here, if present.

### 4.11.6. `/usr/share/man`: Manual pages

#### 4.11.6.1. Purpose

This section details the organization for manual pages throughout the system,
including `/usr/share/man`. Also refer to the section on `/var/cache/man`.

The primary `<mandir>` of the system is `/usr/share/man`. `/usr/share/man`
contains manual information for commands and data under the `/` and `/usr`
filesystems. [31]

Manual pages are stored in `<mandir>/<locale>/man<section>/<arch>`. An
explanation of `<mandir>`, `<locale>`, `<section>`, and `<arch>` is given below.

A description of each section follows:

- `man1`: User programs Manual pages that describe publicly accessible commands
  are contained in this chapter. Most program documentation that a user will
  need to use is located here.
- `man2`: System calls This section describes all of the system calls (requests
  for the kernel to perform operations).
- `man3`: Library functions and subroutines Section 3 describes program library
  routines that are not direct calls to kernel services. This and chapter 2 are
  only really of interest to programmers.
- `man4`: Special files Section 4 describes the special files, related driver
  functions, and networking support available in the system. Typically, this
  includes the device files found in `/dev` and the kernel interface to
  networking protocol support.
- `man5`: File formats The formats for many data files are documented in the
  section 5. This includes various include files, program output files, and
  system files.
- `man6`: Games This chapter documents games, demos, and generally trivial
  programs. Different people have various notions about how essential this is.
- `man7`: Miscellaneous Manual pages that are difficult to classify are
  designated as being section 7. The troff and other text processing macro
  packages are found here.
- `man8`: System administration Programs used by system administrators for
  system operation and maintenance are documented here. Some of these programs
  are also occasionally useful for normal users.

#### 4.11.6.2. Specific Options

The following directories, or symbolic links to directories, must be in
`/usr/share/<mandir>/<locale>`, unless they are empty: [32]

| Directory | Description                      |
| --------- | -------------------------------- |
| man1      | User programs (optional)         |
| man2      | System calls (optional)          |
| man3      | Library calls (optional)         |
| man4      | Special files (optional)         |
| man5      | File formats (optional)          |
| man6      | Games (optional)                 |
| man7      | Miscellaneous (optional)         |
| man8      | System administration (optional) |

The component `<section>` describes the manual section.

Provisions must be made in the structure of `/usr/share/man` to support manual
pages which are written in different (or multiple) languages. These provisions
must take into account the storage and reference of these manual pages.
Relevant factors include language (including geographical-based differences),
and character code set.

This naming of language subdirectories of `/usr/share/man` is based on Appendix
E of the POSIX 1003.1 standard which describes the locale identification
string — the most well-accepted method to describe a cultural environment. The
`<locale>` string is:

```locale
<language>[_<territory>][.<character-set>][,<version>]
```

The `<language>` field must be taken from ISO 639 (a code for the
representation of names of languages). It must be two characters wide and
specified with lowercase letters only.

The `<territory>` field must be the two-letter code of ISO 3166 (a
specification of representations of countries), if possible. (Most people are
familiar with the two-letter codes used for the country codes in email
addresses.) It must be two characters wide and specified with uppercase letters
only. [33]

The `<character-set>` field must represent the standard describing the
character set. If the `<character-set>` field is just a numeric specification,
the number represents the number of the international standard describing the
character set. It is recommended that this be a numeric representation if
possible (ISO standards, especially), not include additional punctuation
symbols, and that any letters be in lowercase.

A parameter specifying a `<version>` of the profile may be placed after the
`<character-set>` field, delimited by a comma. This may be used to discriminate
between different cultural needs; for instance, dictionary order versus a more
systems-oriented collating order. This standard recommends not using the
`<version>` field, unless it is necessary.

Systems which use a unique language and code set for all manual pages may omit
the `<locale>` substring and store all manual pages in `<mandir>`. For example,
systems which only have English manual pages coded with ASCII, may store manual
pages (the `man<section>` directories) directly in `/usr/share/man`. (That is
the traditional circumstance and arrangement, in fact.)

Countries for which there is a well-accepted standard character code set may
omit the `<character-set>` field, but it is strongly recommended that it be
included, especially for countries with several competing standards.

Various examples:

| Language | Territory      | Character Set   | Directory                  |
| -------- | -------------- | --------------- | -------------------------- |
| English  | —              | ASCII           | /usr/share/man/en          |
| English  | United Kingdom | Unicode UTF-8   | /usr/share/man/en_GB.10646 |
| English  | United States  | ASCII           | /usr/share/man/en_US       |
| French   | Canada         | ISO 8859-1      | /usr/share/man/fr_CA.88591 |
| French   | France         | ISO 8859-1      | /usr/share/man/fr_FR.88591 |
| German   | Germany        | ISO 646         | /usr/share/man/de_DE.646   |
| German   | Germany        | ISO 6937        | /usr/share/man/de_DE.6937  |
| German   | Germany        | ISO 8859-1      | /usr/share/man/de_DE.88591 |
| German   | Switzerland    | ISO 646         | /usr/share/man/de_CH.646   |
| Japanese | Japan          | JIS             | /usr/share/man/ja_JP.jis   |
| Japanese | Japan          | SJIS            | /usr/share/man/ja_JP.sjis  |
| Japanese | Japan          | UJIS (or EUC-J) | /usr/share/man/ja_JP.ujis  |
| Japanese | Japan          | Unicode UTF-16  | /usr/share/man/ja_JP.10646 |

Similarly, provision must be made for manual pages which are
architecture-dependent, such as documentation on device-drivers or low-level
system administration commands. These must be placed under an `<arch>`
directory in the appropriate `man<section>` directory; for example, a man page
for the i386 `ctrlaltdel(8)` command might be placed in
`/usr/share/man/<locale>/man8/i386/ctrlaltdel.8`.

Manual pages for commands and data under `/usr/local` are stored in
`/usr/local/man` or `/usr/local/share/man`. All manual page hierarchies in the
system must have the same structure as `/usr/share/man`, as this structure is
expected by commands which consume manual page content. [34]

The cat page sections (`cat<section>`) containing formatted manual page entries
are also found within subdirectories of `<mandir>/<locale>`, but are not
required nor may they be distributed in lieu of nroff source manual pages.

The numbered sections "1" through "8" are traditionally defined. In general,
the file name for manual pages located within a particular section end with
`.<section>`.

In addition, some large sets of application-specific manual pages have an
additional suffix appended to the manual page filename. For example, the MH
mail handling system manual pages must have `mh` appended to all MH manuals.
All X Window System manual pages must have an `x` appended to the filename.

The practice of placing various language manual pages in appropriate
subdirectories of `/usr/share/man` also applies to the other manual page
hierarchies, such as `/usr/local/man`. (This portion of the standard also
applies later in the section on the optional `/var/cache/man` structure.)

### 4.11.7. `/usr/share/misc`: Miscellaneous architecture-independent data

This directory contains miscellaneous architecture-independent files which
don't require a separate subdirectory under `/usr/share`.

#### 4.11.7.1. Specific Options

The following files, or symbolic links to files, must be in `/usr/share/misc`,
if the corresponding subsystem is installed:

| File       | Description                             |
| ---------- | --------------------------------------- |
| ascii      | ASCII character set table (optional)    |
| termcap    | Terminal capability database (optional) |
| termcap.db | Terminal capability database (optional) |

Other (application-specific) files may appear here, but a distributor may place
them in `/usr/lib` at their discretion. [35] [36]

### 4.11.8. `/usr/share/ppd`: Printer definitions (optional)

#### 4.11.8.1. Purpose

`/usr/share/ppd` contains PostScript Printer Definition (PPD) files, which are
used as descriptions of printer drivers by many print systems. PPD files may be
placed in this directory, or in a subdirectory.

### 4.11.9. `/usr/share/sgml`: SGML data (optional)

#### 4.11.9.1. Purpose

`/usr/share/sgml` contains architecture-independent files used by SGML
applications, such as ordinary catalogs (not the centralized ones, see
`/etc/sgml`), DTDs, entities, or style sheets.

#### 4.11.9.2. Specific Options

The following directories, or symbolic links to directories, must be in
`/usr/share/sgml`, if the corresponding subsystem is installed:

| Directory | Description            |
| --------- | ---------------------- |
| docbook   | docbook DTD (optional) |
| tei       | tei DTD (optional)     |
| html      | html DTD (optional)    |
| mathml    | mathml DTD (optional)  |

Other files that are not specific to a given DTD may reside in their own
subdirectory.

### 4.11.10. `/usr/share/xml`: XML data (optional)

#### 4.11.10.1. Purpose

`/usr/share/xml` contains architecture-independent files used by XML
applications, such as ordinary catalogs (not the centralized ones, see
`/etc/sgml`), DTDs, entities, or style sheets.

#### 4.11.10.2. Specific Options

The following directories, or symbolic links to directories, must be in
`/usr/share/xml`, if the corresponding subsystem is installed:

| Directory | Description                |
| --------- | -------------------------- |
| docbook   | docbook XML DTD (optional) |
| xhtml     | XHTML DTD (optional)       |
| mathml    | MathML DTD (optional)      |

[30] Much of this data originally lived in `/usr` (man, doc) or `/usr/lib`
(dict, terminfo, zoneinfo).

[31] Obviously, there are no manual pages in `/` because they are not required
at boot time nor are they required in emergencies. Really.

[32] For example, if `/usr/share/man` has no manual pages in section 4
(Devices), then `/usr/share/man/man4` may be omitted.

[33] A major exception to this rule is the United Kingdom, which is \`GB' in
the ISO 3166, but \`UK' for most email addresses.

[34] `/usr/local/man` is deprecated and may be dropped in a future version of
this specification.

[35] Some such files include: `airport`, `birthtoken`, `eqnchar`, `getopt`,
`gprof.callg`, `gprof.flat`, `inter.phone`, `ipfw.samp.filters`,
`ipfw.samp.scripts`, `keycap.pcvt`, `mail.help`, `mail.tildehelp`,
`man.template`, `map3270`, `mdoc.template`, `more.help`, `na.phone`,
`nslookup.help`, `operator`, `scsi_modes`, `sendmail.hf`, `style`, `units.lib`,
`vgrindefs`, `vgrindefs.db`, `zipcodes`.

[36] Historically, the magic file was placed in `/usr/share/misc`, but modern
variants of the file command use several files and place them in
`/usr/share/file`. For compatibility, distribution may create a symlink at
`/usr/share/misc/magic`, pointing to `/usr/share/file/magic`.

## 4.12. `/usr/src`: Source code (optional)

### 4.12.1. Purpose

Source code may be placed in this subdirectory, only for reference purposes.
[37]

[37] Generally, source should not be built within this hierarchy.
