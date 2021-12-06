# User Management

## 8.1 Account Mechanics

A user is really nothing more than a number. Specifically, an unsigned 32-bit
integer known as the user ID or UID.

Traditionlly, `getpwuid()`, `getpwnam()`, and other library calls obtained users
infomation from `/etc/passwd` or network infomation databases (e.g., LDAP) or
other sources.

## 8.2 The `/etc/passwd` File

The system consults `/etc/passwd` at login time to determine a user’s UID and
home directory, among other things. Each line in the file represents one user
and contains seven fields separated by colons:

- Login name
- Encrypted password placeholder, `*`(FreeBSD), `x`(Linux)
- UID (user ID) number
- Default GID (group ID) number
- Optional“GECOS”information:fullname,office,extension,homephone
- Home directory
- Login shell

e.g.: `root:x:0:0:The System,,x6096,:/:/bin/sh`

If user accounts are shared through a directory service such as LDAP, you might
see special entries in the `passwd` file that begin with + or -. These entries
tell the system how to integrate the directory service’s data with the contents
of the `passwd` file. This integration can also be set up in the
`/etc/nsswitch.conf` file.

### Login name

It must be unique, most unix-like systems limit login name to 32 characters.

Good convention:

- all lowercase
- same person same name among all hosts

### Encrypted password

Historically, `DES` -> `MD5` -> salted `SHA-512`

Changing the password algorithm does not update existing passwords, so users
must manually update their passwords before the new algorithm can take effect.
To invalidate a user’s password and force an update, use

```sh
chage -d 0 username
```

### UID (user ID) number

`root` has UID `0`.

To allow plenty of room for nonhuman users you might want to add in the future,
we recommend that you assign UIDs to real users starting at 1000 or higher.

By default, Linux starts UIDs at 1000 and go up from there. FreeBSD starts the
first user at UID 1001 and then adds one for each additional user.

Do **not** recycle UIDs, even when users leave your organization and you delete
their accounts. This precaution prevents confusion if files are later restored
from backups, where users may be identified by UID rather than by login name.

UIDs should be kept unique across your entire organization. That is, a
particular UID should refer to the same login name and the same person on every
machine that person is authorized to use. Failure to maintain distinct UIDs can
result in security problems with systems such as NFS and can also result in
confusion when a user moves from one workgroup to another.

The best solution is to have a central database or directory server that
contains a record for each user and enforces uniqueness.

A simpler scheme is to assign each group within an organization its own range
of UIDs and to let each group manage its own range. This solution keeps the UID
spaces separate but does not address the parallel issue of unique login names.

### Default GID (group ID) number

A group ID number is a 32-bit integer. GID 0 is reserved for the group called
root, system, or wheel.

In ancient times, when computing power was expensive, groups were used for
accounting purposes so that the right department could be charged for your
seconds of CPU time, minutes of login time, and kilobytes of disk used. Today,
groups are used primarily to share access to files.

The `/etc/group` file defines the groups, with the GID field in `/etc/passwd`
providing a default (or “effective”) GID at login time. The default GID is not
treated specially when access is determined; it is relevant only to the
creation of new files and directories. New files are normally owned by your
effective group; to share files with others in a project group, you must
manually change the files’ group owner.

To facilitate collaboration, you can set the `setgid` bit (02000) on a
directory or mount filesystems with the `grpid` option. Both of these measures
make newly created files default to the group of their parent directory. Or
use `chmod g+s`.

### GECOS field

The GECOS field is sometimes used to record personal information about each
user. The field is a relic from a much earlier time when some early UNIX
systems used General Electric Comprehensive Operating Systems for various
services. Conventionally, comma-separated GECOS entries are placed in the
following order:

- Full name (often the only field used)
- Office number and building
- Office telephone extension
- Home phone number

The `chfn` command lets users change their own GECOS information. On most
systems, `chfn` understands only the passwd file, so if you use LDAP or some
other directory service for login information, `chfn` may not work at all.

### Home directory

A user’s home directory is his or her default directory at login time. Home
directories are where login shells look for account-specific customizations
such as shell aliases and environment variables, as well as SSH keys, server
fingerprints, and other program state.

Be aware that if home directories are mounted over a network filesystem, they
may be unavailable in the event of server or network problems. If the home
directory is missing at login time, the system might print a message such as
“no home directory” and put the user in `/`. Alternatively, it might disallow
the login entirely, depending on the system configuration.

### Login shell

The login shell is normally a command interpreter, but it can be any program. A
Bourne-shell compatible `sh` is the default for FreeBSD, and `bash` (the GNU
“Bourne again” shell) is the default for Linux.

Some systems permit users to change their shell with the `chsh` command, but as
with `chfn`, this command might not work if you are using LDAP or some other
directory service to manage login information. If you use the /etc/passwd file,
a sysadmin can always change a user’s shell by editing the `passwd` file with
`vipw`.
