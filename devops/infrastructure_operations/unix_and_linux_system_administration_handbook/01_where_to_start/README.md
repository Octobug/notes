# 1 Where to Start

## 1.1 Essential duties of the system administrator

Below duties need not necessarily be carried out by a single person, and at many
sites the work is distributed among a team.

### Controlling access

### Adding hardware

### Automating tasks

### Overseeing backups

### Installing and upgrading software

### Monitoring

### Troubleshooting

### Maintaining local documentation

### Vigilantly monitoring security

### Tuning performance

### Developing site policies

### Working with vendors

### Fire fighting

## 1.2 Suggested background

- Get well along with command line
- Editors: `vim`, or `nano` for starter
- Scripting: `Bash`, `Ruby`, `Python`
- Driving interactive programs: `expect`

## 1.3 Linux distributions

### Comprises

- Linux kernel
- Packages (commands)

### Two predominant lineages

- Debian
- Red Hat

### Minimalist distributions

- CoreOS
- Alpine Linux

### What needs to be considered when adopting a distribution

- Is this distribution going to be around in five years?
- Is this distribution going to stay on top of the latest security patches?
- Does this distribution have an active community and sufficient documentation?
- If I have problems, will the vendor talk to me,and how much will that cost?

Table 1.1 **Most popular general-purpose Linux distributions**

| Distribution          | Comments                                |
| --------------------- | --------------------------------------- |
| Arch                  | For those who fear not the command line |
| CentOS                | Free analog of Red Hat Enterprise       |
| CoreOS                | Containers, containers everywhere       |
| Debian                | Free as in freedom, most GNUish distro  |
| Fedora                | Test bed for Red Hat Linux              |
| Kali                  | For penetration testers                 |
| Linux Mint            | Ubuntu-based, desktop-friendly          |
| openSUSE              | Free analog of SUSE Linux Enterprise    |
| openWRT               | Linux for routers and embedded devices  |
| Oracle Linux          | Oracle-supported version of RHEL        |
| RancherOS             | 20MiB, everything in containers         |
| Red Hat Enterprise    | Reliable, slow-changing, commercial     |
| Slackware             | Grizzled, long-surviving distro         |
| SUSE Linux Enterprise | Strong in Europe, multilingual          |
| Ubuntu                | Cleaned-up version of Debian            |

## 1.4 Example systems used in this book

- Debian GNU/Linux
- Ubuntu Linux
- Red Hat Enterprise Linux
- FreeBSD

## 1.5 Notation and typographical conventions

### Manual pages conventions for command syntax

- Anything between square brackets (“[” and “]”) is optional.
- Anything followed by an ellipsis (“...”) can be repeated.
- Curly braces (“{” and “}”) mean that you should select one of the items
  separated by vertical bars (“|”).

### Shell-style globbing characters

- A star (*) matches zero or more characters.
- A question mark (?) matches one character.
- A tilde or “twiddle” (~) means the home directory of the current user.
- ~*user* means the home directory of *user*.

## 1.6 Units

### Metric prefixes

- kilo-
- mega-
- giga-

are defined as powers of 10 (Network bandwidth, Storage space).

However, computer types (RAM) used them to refer to powers of 2.

### Numeric prefixes

- kibi-
- mebi-
- gibi-

based explicitly on powers of 2.

Table 1.2 **Unit decoding examples**

| Example               | Meaning                                         |
| --------------------- | ----------------------------------------------- |
| 1kB file              | A file that contains 1,000 bytes                |
| 4KiB SSD pages        | SSD pages that contain 4,096 bytes              |
| 8KB of memory         | \                                               |
| 100MB file size limit | Nominally 10^8 bytes; in context, ambiguous     |
| 100MB disk partition  | Nominally 10^8 bytes; in context, probably      |
|                       | 99,999,744 bytes                                |
| 1GiB of RAM           | 1,073,741,824 bytes of memory                   |
| 1 Gb/s Ethernet       | A network that transmits 1,000,000,000 bits     |
|                       | per second                                      |
| 6TB hard disk         | A hard disk that stores about 6,000,000,000,000 |
|                       | bytes                                           |

## 1.7 Man pages and other on-line documentation

All systems divide the man pages into sections, but there are minor variations
in the way some sections are defined.

### Organization of the man pages

| Linux | Contents                             |
| ----- | ------------------------------------ |
| 1     | User-level commands and applications |
| 2     | System calls and kernel error codes  |
| 3     | Library calls                        |
| 4     | Device drivers and network protocols |
| 5     | Standard file formats                |
| 6     | Games and demonstrations             |
| 7     | Miscellaneous files and documents    |
| 8     | System administration commands       |
| 9     | Obscure kernal specs and interfaces  |

Some commands may appear in multiple sections. For example, `passwd` has entries
in both section 1 and section 4 or 5.

### man: read man pages

`$PAGER` specifies program that man uses.

`man 5 passwd` or `man -s 5 passwd`.

`man -k keyword` or `apropos keyword` prints a list of man pages that have
*keyword* in their one-line synopses.

To rebuild the keywords database, use `mandb` (Ubuntu, SUSE) or `makewhatis`
(Red Hat and FreeBSD).

### Storage of man pages

`manpath`: find out the current default search path. To change it, set the env
var: `$MANPATH`.

### GNU Texinfo (Deprecated)

`info | less` to evade info's builtin navigation system
`info info` to start.

## 1.8 Other authoritative documentation

### System-specific guides

### Package-specific documentation

### Books

The O’Reilly books are favorites in the technology industry.

### RFC publications

## 1.9 Other sources of information

Unless you’re looking up the details of a specific command or file format,
Google or an equivalent search engine should be the first resource you consult
for any sysadmin question.

*When stuck, search the web*.

### Keeping current

### HowTos and reference sites

### Conferences

## 1.10 Ways to find and install software

### Determining if software is already installed

- `which`: find out if a relevant binary is already in search path
- `whereis`: searches in broader range of system directories
- `locate`: consults a precompiled index of the filesystem to locate filenames.
  `locate`'s database is updated periodically by the `updatedb` command, which
  runs periodically out of `cron`.

### Adding new software

- Debian: `apt` (Advanced Package Tool)
- Red Hat: `yum`
- FreeBSD: `pkg`

### Building software from source code

Common sequence:

1. `configure`: `--help`, `--prefix=directory`
2. `make`
3. `make install`

### Installing from a web script

Better to save the script to a temporary file, then run the script in a separate
step after the download.

## 1.11 Where to host

Cloud is OK for startups.

## 1.12 Specialization and adjacent disciplines

### DevOps

It aims to improve the efficiency of building and delivering software,
especially at large sites that have many interrelated services and teams.

### Site reliability engineers

### Security operations engineers

### Network administrators

### Database administrators

### Network operations center (NOC) engineers
