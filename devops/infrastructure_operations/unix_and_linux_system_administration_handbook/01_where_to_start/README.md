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

> untouched

## 1.7 Man pages and other on-line documentation

All systems divide the man pages into sections, but there are minor variations
in the way some sections are defined.

### Organization of the man pages

| Linux | Contents |
| - | - |
| 1 | User-level commands and applications |
| 2 | System calls and kernel error codes |
| 3 | Library calls |
| 4 | Device drivers and network protocols |
| 5 | Standard file formats |
| 6 | Games and demonstrations |
| 7 | Miscellaneous files and documents |
| 8 | System administration commands |
| 9 | Obscure kernal specs and interfaces |

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
