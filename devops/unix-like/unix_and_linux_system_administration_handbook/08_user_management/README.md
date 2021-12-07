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

## 8.3 The Linux /etc/shadow file

The `shadow` file is not a superset of the `passwd` file, and the `passwd` file
is not generated from it. You must maintain both files or use tools such as
`useradd` that maintain both files on your behalf. Like `/etc/passwd`,
`/etc/shadow` contains one line for each user. Each line contains nine fields,
separated by colons:

1. `Login name`: same as in `/etc/passwd`. This field connects a user’s `passwd`
  and `shadow` entries.
2. `Encrypted password`: previously stored in `/etc/passwd`.
3. `Date of last password change`: filled in by the `passwd` command.
4. `Minimum number of days between password changes`: to force authentic changes
  by preventing users from immediately reverting to a familiar password after a
  required change. However, this feature can be somewhat dangerous in the
  aftermath of a security intrusion. We suggest setting this field to 0.
5. `Maximum number of days between password changes`: allows the administrator
  to enforce password aging. Under Linux, the actual enforced maximum number of
  days is the sum of this field and the seventh (grace period) field.
6. `Number of days in advance to warn users about password expiration`
7. `Days after password expiration that account is disabled`
8. `Account expiration date`: If the field is left blank, the ac- count never
  expires. You can use `usermod` to set the expiration field. It accepts dates
  in the format `yyyy-mm-dd`.
9. `A field reserved for future use which is currently always empty`

Absolute date fields in `/etc/shadow` are specified in terms of days (not
seconds) since Jan 1, 1970, which is not a standard way of reckoning time on
UNIX or Linux systems.

Use the `pwconv` utility to reconcile the contents of the `shadow` file and
those of the `passwd` file, picking up any new additions and deleting users
that are no longer listed in `passwd`.

## 8.4 FreeBSD's `/etc/master.passwd` and `/etc/login.conf` files

### The `/etc/master.passwd` file

On FreeBSD, the “real” password file is `/etc/master.passwd`, which is readable
only by root. The `/etc/passwd` file exists for backward compatibility.

In addition to containing all the fields of the `passwd` file, the
`master.passwd` file contains three bonus fields. Unfortunately, they’re
squeezed in between the default GID field and the GECOS field, so the file
formats are not directly compatible. The extra three fields are

- Login class
- Password change time
- Expiration time

### The `/etc/login.conf` file

FreeBSD’s `/etc/login.conf` file sets account-related parameters for users and
groups of users.

When a user logs in, the login class field of `/etc/master.passwd` determines
which entry in `/etc/login.conf` to apply. If the user’s `master.passwd` entry
does not specify a login class, the `default class` is used.

A `login.conf` entry can set any of the following:

- Resource limits (maximum process size, maximum file size, number of open
  files, etc.)
- Session accounting limits (when logins are allowed, and for how long)
- Default environment variables
- Default paths (PATH, MANPATH, etc.)
- Location of the “message of the day” file
- Host and TTY-based access control
- Default `umask`
- Account controls(mostly superseded by the PAM module `pam_passwdqc`)

The following example overrides several of the default values. It’s intended
for assignment to system administrators.

```conf
sysadmin:\
    :ignorenologin:\
    :requirehome@:\
    :maxproc=unlimited:\
    :openfiles=unlimited:\
    :tc=default:
```

When you modify the `/etc/login.conf` file, you must also run the following
command to compile your changes into the hashed version of the file that the
system actually refers to in daily operation: `cap_mkdb /etc/login.conf`

## 8.5 The `/etc/group` file

The `/etc/group` file contains the names of UNIX groups and a list of each
group’s members.

```group
wheel:*:0:root
sys:*:3:root,bin
operator:*:5:root
bin:*:7:root
ftp:*:14:dan
staff:*:20:dan,ben,trent
nobody:*:65534:lpd
```

Each line represents one group and contains four fields:

- Groupname
- Encrypted password or a placeholder
- GID number
- List of members, separated by commas (be careful **not to add spaces**)

As in `/etc/passwd`, fields are separated by colons. Group names should be
limited to **eight** characters for compatibility, although many systems do not
actually require this.

It’s possible to set a group password that allows arbitrary users to enter the
group with the `newgrp` command. However, this feature is rarely used. The
group password can be set with `gpasswd`, which under Linux stores the
encrypted password in the `/etc/gshadow` file.

As with usernames and UIDs, group names and GIDs should be kept consistent
among machines that share files through a network filesystem. Consistency can
be hard to maintain in a heterogeneous environment because different operating
systems use different GIDs for standard system groups.

If a user defaults to a particular group in `/etc/passwd` but does not appear
to be in that group according to `/etc/group`, `/etc/passwd` wins the argument.

There is no real limit on current Linux and FreeBSD kernels.

The UNIX tradition was originally to add new users to a group that represented
their general category such as “students” or “finance”. However, this
convention increases the likelihood that users will be able to read one
another’s files because of slipshod permission settings, even if that is not
really the intention of the files’ owner.

To avoid this problem, system utilities such as `useradd` and `adduser` now
default to putting each user in his or her own personal group (that is, a group
named after the user and which includes only that user). This convention is
much easier to maintain if personal groups’ GIDs match their corresponding
users’ UIDs.

To let users share files by way of the group mechanism, create separate groups
for that purpose. The idea behind personal groups is not to discourage the use
of groups per se —— it’s simply to establish a more restrictive `default` group
for each user so that files are not inadvertently shared. You can also limit
access to newly created files and directories by setting your user’s default
`umask` in a default startup file such as `/etc/profile` or `/etc/bashrc`.

Group membership can also serve as a marker for other contexts or privileges.
For example, rather than entering the username of each system administrator
into the `sudoers` file, you can configure sudo so that everyone in the “admin”
group automatically has `sudo` privileges.

Linux supplies the `groupadd`, `groupmod`, and `groupdel` commands to create,
modify, and delete groups.

## 8.6 Manual steps for adding users

Required:

- Edit the `passwd` and `shadow` files to define the user’s account.
- Add the user to the `/etc/group` file (not really necessary, but nice).
- Set an initial password.
- Create, `chown`, and `chmod` the user’s home directory.
- Configure roles and permissions.

For the user:

- Copy default startup files to the user’s home directory.

For you:

- Have the new user sign your policy agreement.
- Verify that the account is set up correctly.
- Document the user’s contact information and account status.

### Editing the `passwd` and `group` files

Use the `vipw` command to edit the `passwd` and `shadow` files (or on FreeBSD,
the `master.passwd` file). It locks the files so that editing sessions (or your
editing and a user’s password change) cannot collide.

After you run `vipw`, Linux reminds you to edit the `shadow` file after you
have edited the `passwd` file. Use `vipw -s` to do so.

Use the `vigr` command to edit `/etc/group`.

### Setting a password

`sudo passwd newusername`

### Creating the home directory and installing startup files

There’s nothing magical about home directories. If you neglected to include a
home directory when setting up a new user, you can create it with a simple
`mkdir`. You need to set ownerships and permissions on the new directory as
well.

Startup files traditionally begin with a `.` (dot) and end with the letters
`rc`, short for “run command,” a relic of the CTSS operating system.

#### Common startup files and their uses

- `target`
  - `Filename`
    - Typical uses

- `all shells`
  - `.login_conf`
    - Sets user-specific login defaults (FreeBSD)
- `sh`
  - `.profile`: Sets search path, terminal type, and environment
- `bash`
  - `.bashrc`
    - Sets the terminal type (if needed)
    - Sets biff and mesg switches
  - `.bash_profile`
    - Sets up environment variables
    - Sets command aliases
    - Sets the search path
    - Sets the `umask` value to control permissions
    - Sets CDPATH for filename searches
    - Sets the PS1 (prompt) and HISTCONTROL variables
- `csh/tcsh`
  - `.login`
    - Read by “login” instances of `csh`
  - `.cshrc`
    - Read by all instances of `csh`
- `vi/vim`
  - `.vimrc/.viminfo`
    - Sets `vi/vim` editor options
- `emacs`
  - `.emacs`
    - Sets `emacs` editor options and key bindings
- `git`
  - `.gitconfig`
    - Sets user, editor, color, and alias options for Git
- `GNOME`
  - `.gconf`
    - GNOME user configuration via `gconf`
  - `.gconfpath`
    - Path for additional user configuration via `gconf`
- `KDE`
  - `.kde/`
    - Directory of configuration files

Sample startup files are traditionally kept in `/etc/skel`. If you customize
your systems’ startup file examples, `/usr/local/etc/skel` is a reasonable
place to put the modified copies.

By convention, Linux also keeps fragments of startup files in the
`/etc/profile.d` directory. Although the directory name derives from `sh`
conventions, `/etc/profile.d` can actually include fragments for several
different shells. The specific shells being targeted are distinguished by
filename suffixes (`*.sh`, `*.csh`, etc.). There’s no magic `profile.d` support
built into the shells themselves; the fragments are simply executed by the
default startup script in `/etc` (e.g., `/etc/profile` in the case of `sh` or
`bash`).

### Setting home directory permissions and ownerships

```sh
sudo chown -R newuser:newgroup ~newuser
```

WRONG WAY: `sudo chown newuser:newgroup ~newuser/.*` to `chown` the dot files
because newuser would then own not only his or her own files but also the
parent directory “..” as well.

### Configuring roles and administrative privileges

Role-based access control (RBAC) allows system privileges to be tailored for
individual users. RBAC is not a traditional part of the UNIX or Linux access
control model, but if your site uses it, role configuration must be a part of
the process of adding users.

### Finishing up

To verify that a new account has been properly configured, first log out, then
log in as the new user and execute the following commands:

```sh
pwd     # To verify the home directory
ls -la  # To check owner/group of startup files
```

## 8.7 Scrpits for adding users: `useradd`, `adduser`, and `newusers`

### Commands and configuration files for user management

| System | Commands | Configuration files |
| - | - | - |
| All Linux | `useradd`, `usermod`, `userdel` | `/etc/login.defs` |
| | | `/etc/default/useradd` |
| Debian/Ubuntu | `adduser`, `deluser` | `/etc/adduser.conf` |
| | | `/etc/deluser.conf` |
| FreeBSD | `adduser`, `rmuser` | `/etc/login.conf` |

### `useradd` on Linux

Most Linux distributions include a basic `useradd` suite that draws its
configuration parameters from both `/etc/login.defs` and `/etc/default/useradd`.

The `login.defs` file addresses issues such as password aging, choice of
encryption algorithms, location of mail spool files, and the preferred ranges
of UIDs and GIDs. You maintain the `login.defs` file by hand.

Parameters stored in the `/etc/default/useradd` file include the location of
home directories and the default shell for new users. You set these defaults
through the `useradd` command itself. `useradd -D` prints the current values,
and `-D` in combination with various other flags sets the values of specific
options. For example, `sudo useradd -D -s /bin/bash` sets bash as the default
shell.

Typical defaults are to put new users in individual groups, to use SHA-512
encryption for passwords, and to populate new users’ home directories with
startup files from `/etc/skel`.

`useradd` disables the new account by default. You must assign a real password
to make the account usable.

```sh
sudo useradd \
    -c "Comment" \
    -d /home/username
    -g username # personal group
    -G othergroup
    -m # create home
    -s /bin/bash
    username
```

### adduser on Debian and Ubuntu

The Debian lineage supplies higher-level wrappers for `useradd` family commands
in the form of `adduser` and `deluser`. They are configured in
`/etc/adduser.conf`, where you can specify options such as these:

- Rules for locating home directories: by group, by username, etc.
- Permission settings for new home directories
- UID and GID ranges for system users and general users
- An option to create individual groups for each user
- Disk quotas (Boolean only, unfortunately)
- Regex-based matching of user names and group names

Other typical `useradd` parameters, such as rules for passwords, are set as
parameters to the PAM module that does regular password authentication.
`adduser` and `deluser` have twin cousins `addgroup` and `delgroup`.

### adduser on FreeBSD

FreeBSD comes with `adduser` and `rmuser` shell scripts. The scripts are built
on top of the facilities provided by the `pw` command.

### newusers on Linux: adding in bulk

Linux’s `newusers` command creates multiple accounts at one time from the
contents of a text file. `newusers` expects an input file of lines just like
the `/etc/passwd` file, except that the password field contains the initial
password in clear text.

`newusers` honors the password aging parameters set in the `/etc/login.defs`
file, but it does not copy in the default startup files as does `useradd`. The
only startup file it copies in is `.xauth`.

You’re probably better off writing your own wrapper for `useradd` in Python than
trying to get `newusers` to do what you need.

## 8.8 Safe removal of a user’s account and files

`userdel` or `rmuser` ensures the removal of all references to the login name
that were added by you or your `useradd` program. Once you’ve removed the
remnants, use the following checklist to verify that all residual user data has
been removed:

- Remove the user from any local user databases or phone lists.
- Remove the user from the mail aliases database, or add a forwarding address.
- Remove the user’s crontab file and any pending `at` jobs or print jobs.
- Kill any of the user’s processes that are still running.
- Remove the user from the `passwd`, `shadow`, `group`, and `gshadow` files.
- Remove the user’s home directory.
- Remove the user’s mail spool (if mail is stored locally).
- Clean up entries on shared calendars, room reservation systems, etc.
- Delete or transfer ownership of any mailing lists run by the deleted user.

Before you remove someone’s home directory, be sure to relocate any files that
are needed by other users. You usually can’t be sure which files those might
be, so it’s always a good idea to make an extra backup of the user’s home
directory before deleting it.

Once you have removed all traces of a user, you may want to verify that the
user’s old UID no longer owns files on the system. To find the paths of
orphaned files, you can use the `find` command with the `-nouser` argument.
Because `find` has a way of “escaping” onto network servers if you’re not
careful, it’s usually best to check filesystems individually with `-xdev`:

```sh
sudo find filesystem -xdev -nouser
```

Debian and Ubuntu’s `deluser` is a Perl script that calls the usual `userdel`;
it undoes all the things `adduser` does. It runs the script
`/usr/local/sbin/deluser.local`, if it exists, to facilitate easy localization.
The configuration file `/etc/deluser.conf` lets you set options such as these:

- Whether to remove the user’s home directory and mail spool
- Whether to back up the user’s files, and where to put the backup
- Whether to remove all files on the system owned by the user
- Whether to delete a group if it now has no members

Red Hat supports a `userdel.local` script but no pre- and post-execution
scripts to automate sequence-sensitive operations such as backing up an
about-to-be-removed user’s files.

FreeBSD’s `rmuser` script does a good job of removing instances of the user’s
files and processes, a task that other vendors’ `userdel` programs do not even attempt.

## 8.9 User login lockout
