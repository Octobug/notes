# 3 Access Control and Rootly Powers

Privileged network ports: those under 1024

## 3.1 Standard UNIX Access Control

There were some general rules that shaped the system's design:

- Access control decisions depend of which user is attempting to perform an
  operation, or in some cases, on that user's memberhship in a UNIX group.
- Object (e.g., files and processes) have owners. Owners have broad control over
  their objects.
- You own new objects that you create.
- The special user account called "root" can act as the owner of any object.
- Only root can perform certain sensitive administrative operations.

The kernel and the filesystem are intertwined.

### Filesystem access control

In the standard model, every file has both an owner and a group, sometimes
referred to as the “group owner.” The owner can set the permissions of the
file. In particular, the owner can set them so restrictively that no one else
can access it.

> In fact,the permissions can be set so restrictively that even the owner of a
> file cannot access it.

Both the kernel and the filesystem track owners and groups as numbers rather
than as text names. In the most basic case, user identification numbers (UIDs
for short) are mapped to usernames in the `/etc/passwd` file, and group
identification numbers (GIDs) are mapped to group names in `/etc/group`.

### Process ownership

Processes actually have multiple identities associated with them: a real,
effective, and saved UID; a real, effective, and saved GID; and under Linux,
a "filesystem UID that is used only to determine file access permissions.

The real numbers are used for accounting and the effective numbers are used for
the determination of access permissions. The real and effective numbers are
normally the same.

### The root account

The defining characteristic of the root account is its UID of 0. Nothing
prevents you from changing the username on this account or from creating
additional accounts whose UIDs are 0.

An example of superuser powers is the ability of a process owned by root to
change its UID and GID.

The `login` process that prompts you for your password when you log in to the
system initially runs as root. If the username and password are legitimate, the
login program changes its UID and GID to your UID and GID and starts up your
user environment.

Once a root process has changed its owner- ships to become a normal user
process, it can’t recover its former privileged state.

### `setuid` and `setgid` execution

When the kernel runs an executable file that has its “setuid” or “setgid”
permission bits set, it changes the effective UID or GID of the resulting
process to the UID or GID of the file containing the program image rather than
the UID and GID of the user that ran the command. The user’s privileges are
thus promoted for the execution of that specific command only.

For example, users must be able to change their passwords. But since passwords
are stored in the protected `/etc/shadow` file, users need a setuid `passwd`
command to mediate their access. The `passwd` command checks to see who’s
running it and customizes its behavior accordingly: users can only change their
own passwords, but root can change any password.

## 3.2 Management of the `root` Account

### Root account login

- `root` logins leave no record of what operations were performed as root.
- you cannot know what the an intruder has done to your system.
- cannot figure out who was doing the work

### `su`:substitute user identity

- `su - {username}`: `-` option makes `su` spawn the shell in login mode. It
  then ask for the target user password instead of your own password. But login
  mode normally changes the number or identity of the files that the shell reads
  when it starts up. e.g. `bash` reads
  - `~/.bash_profile` in login mode
  - `/.bashrc` in nologin mode
- `su` doesn't record the commands executed as root, but it does create a log
  entry that states who became root and when
- root can `su` to any account without entering a password

⚠️ Get in the habit of typing the full pathname to su (e.g., `/bin/su` or
`/usr/bin/su`) rather than relying on the shell to find the command for you.
This precaution gives you some protection against arbitrary programs called `su`
that might have been sneaked into your search path with the intention of
harvesting passwords.

`su` is best reserved for emergencies.

### `sudo`: limited `su`

> <https://www.sudo.ws/man/1.8.13/sudoers.man.html>

`sudo` takes as its argument a command line to be executed as root (or as
another restricted user). It will ask the user's own password.

`sudo` keeps a log of the command lines that were executed. `syslog` can forward
the logs to a secure central host.

A log entry for randy’s executing `sudo /bin/cat /etc/sudoers` might look like
this:

```log
Dec 7 10:57:19 tigger sudo: randy: TTY=ttyp0 ; PWD=/tigger/users/randy;
  USER=root ; COMMAND=/bin/cat /etc/sudoers
```

#### Example configuration

```conf
# Define aliases for machines in CS & Physics departments
Host_Alias CS = tigger, anchor, piper, moet, sigi
Host_Alias PHYSICS = eprince, ppronce, icarus

# Define collections of commands
Cmnd_Alias DUMP = /sbin/dump, /sbin/restore
Cmnd_Alias WATCHDOG = /usr/local/bin/watchdog
Cmnd_Alias SHELLS = /bin/sh, /bin/dash, /bin/bash

# Permissions
# user1, user2 | hosts = | (target user:target group) | NOPASSWD:commands
mark, ed  PHYSICS = ALL
herb      CS = /usr/sbin/tcpdump : PHYSICS = (operator) DUMP
lynda     ALL = (ALL) ALL, !SHELLS
%wheel    ALL, !PHYSICS = NOPASSWD : WATCHDOG
```

Each permission specification line includes information about

- The users to whom the line applies
- The hosts on which the line should be heeded
- The commands that the specified users can run
- The users as whom the commands can be executed

`mark, ed  PHYSICS = ALL`
allows 'mark, ed' to run 'ALL' command on 'PHYSICS' hosts as root

`herb      CS = /usr/sbin/tcpdump : PHYSICS = (operator) DUMP`
allows 'herb' to run 'tcpdump' on 'CS' hosts as root, and run 'DUMP' commnads
on 'PHYSICS' as (operator)

`lynda     ALL = (ALL) ALL, !SHELLS`
allows lynda to run 'ALL' commands as (ALL) users on ALL hosts, except that she
cannot run by 'SHELLS', but she can `cp -p /bin/sh /tmp/sh` first :)

⚠️ Generally speaking, any attempt to allow "all commands except ..." is doomed to
failure. However, it might still be worthwihle to set up the `sudoers` file this
way as a reminder that root shells are strongly discouraged.

`%wheel    ALL, !PHYSICS = NOPASSWD : WATCHDOG`
allows users in group wheel to run the local `watchdog` command as root on ALL
hosts except `PHYSICS` hosts. And no password is required.

⚠️ Commands in the `sudoers` file are specified with full pathnames to prevent
people from executing their own programs and scripts as root.

⚠️ Always use the `visudo` command, which checks to be sure no one else is
editing the file, invokes an editor (specified by `$EDITOR`) on it, and then
verifies the syntax of the detailed edited file before installing it.

#### `sudo` pros and cons

The use of `sudo` has the following advantages:

- Accountability is much improved because of command logging.
- Users can do specific chores without having unlimited root privileges
- The real root password can be known to only one or two people
- Using `sudo` is faster than using `su` or logging in as root
- Privileges can be revoked without the need to change the root password.
- A canonical list of all users with root privileges is maintained.
- The chance of a root shell being left unattended is lessened.
- A single file can control access for an entire network.

Disadvantages:

- Any breach in the security of a root sudoer's personal account can be
  equivalent to breaching the root.
- `sudo`'s command logging can easily be subverted by tricks such as shell
  escapes from within an allowed program, or by `sudo sh` and `sudo su`

#### `sudo` vs. advanced access control

`sudo` advantages:

- You decide exactly how privileges will be subdivided.
- Simple to set up, maintain, and understand.
- `sudo` suits all Linux systems.
- You can share a single configuration file throughout your site.
- You get consistent, high-quality logging for free.

#### Typical setup

```sudoers
User_Alias ADMINS = alice, bob, charles
ADMINS ALL = (ALL) ALL
```

Config above is OK though it is simple.

#### Environment management

e.g. If `$EDITOR` points to a hacker's malicious program, it's likely that
you'll end up running that program as root.

To minimize this risk, `sudo`'s default behavior is to pass only a minimal,
sanitized environment to the commands that it runs. `sudoers` file's `env_keep`
list can add your own whitelist:

```sudoers
Defaults env_keep += "SSH_AUTH_SOCK"
Defaults env_keep += "DISPLAY XAUTHORIZATION XAUTHORITY"
```

#### `sudo` without passwords

Needs to be done with much cautions.

#### Precedence

```sudoers
User_Alias    ADMINS = alice, bob, charles
User_Alias    MYSQL_ADMINS = alice, bob

%wheel        ALL = (ALL) ALL
MYSQL_ADMINS  ALL = (mysql) NOPASSWD: ALL
ADMINS        ALL = (ALL) NOPASSWD: /usr/sbin/logrotate
```

If user alice is in the wheel group, she is potentially covered by each of the
last three lines. How do you know which one will determine `sudo`'s behavior?

The rule is that sudo always obeys the last matching line, with matching being
determined by the entire 4-tuple of user, host, target user, and command. Each
of those elements must match the configuration line, or the line is simply
ignored.

#### `sudo` without a control terminal

e.g. from `cron`, an odd situation that `sudo` can check for and reject if the
`requiretty` option is turned on in the sudoers file.

This book recommends to disable `requiretty` in the `sudoers` file
`Defaults !requiretty`.

#### Site-wide `sudo` configuration

Giving `sudo` permissions to users by groups defers the enumeration of
privileged users to each local machine. You can't look at this line and
determine who's covered by it without an excursion to the machine in question.

Since it is better to keep all relevant information in one place, it’s best to
avoid this type of grouping option when sharing a `sudoers` file on a network.
Of course, if your group memberships are tightly coordinated site-wide, it’s
fine to use groups.

Distribution of the `sudoers` file is best achieved through a broader system of
configuration management.

`visudo -c -f`

- `-c`: check
- `-f`: specify file

By default, `sudo` uses the output of the `hostname` command as the text to be
matched.

### Disabling the root account

1. set root's encryped password to `*` or arbitrary string
2. `passwd -l` locks an account by prepending a `!` to the encrypted password

Above two operations make `root` cannot be used anymore, but `sudo` will still
work normally.

Ubuntu ships with the root account locked, you can unlock it with
`sudo passwd -u root`.

### System accounts other than root

There are several other pseudo-users are defined by most systems. You can
identify these sham accounts by their low UIDs. Most often, UIDs under 10 are
system accounts, and UIDs between 10 and 100 are pseudo-users associated with
specific pieces of software.

It’s customary to replace the encrypted password field of these special users
in the `shadow` or `master.passwd` file with a star so that their accounts
cannot be logged in to. Their shells should be set to `/bin/false` or
`/bin/nologin` as well.

Files and processes that are part of the operating system but that need not be
owned by root are sometimes assigned to the users `bin` or `daemon`.

The main advantage of defining pseudo-accounts and pseudo-groups is that they
can be used more safely than the root account to provide access to defined
groups of resources. For example, databases often implement elaborate access
control systems of their own. From the perspective of the kernel, they run as a
pseudo-user such as “mysql” that owns all database-related resources.

The Network File System (NFS) uses an account called “nobody” to represent root
users on other systems. For remote roots to be stripped of their rootly powers,
the remote UID 0 has to be mapped to something other than the local UID 0. The
nobody account acts as a generic alter ego for these remote roots. In NFSv4,
the `nobody` account can be applied to remote users that correspond to no valid
local account as well.

Since the nobody account is supposed to represent a generic and relatively
powerless user, it shouldn’t own any files. If nobody does own files, remote
roots can take control of them.

## 3.3 Extensions to the Standard Access Control Model

### Drawbacks of the standard model

- The root account represents a potential single point of failure.
- The only way to subdivide the privileges of the root account is to write
  `setuid` programs. Unfortunately, it’s difficult to write secure software.
  Every setuid program is a potential target.
- The standard model has little to say about security on a network. No computer
  to which an unprivileged user has physical access can be trusted to
  accurately represent the ownerships of the processes it’s running.
- In the standard model, group definition is a privileged operation. For
  example, there’s no way for a generic user to express the intent that only
  alice and bob should have access to a particular file.
- Because many access control rules are embedded in the code of individual
  commands and daemons, you cannot redefine the system’s behavior without
  modifying the source code and recompiling.
- The standard model also has little or no support for auditing or logging. You
  can see which UNIX groups a user belongs to, but you can’t necessarily
  determine what those group memberships permit a user to do.

### PAM: Pluggable Authentication Modules

PAM is an authentication technology, not an access control technology.

### Kerberos: network cryptographic authentication

Kerberos deals with authentication rather than access control. PAM is an
authentication framework, Kerberos is a specific authentication method.

### Filesysem access control lists

ACLs: access control lists.

### Linux capabilities

Capability specifications can also be assigned to executable programs. It's
essentially a lower-risk form of `setuid` execution.

### Linux namespaces

Linux can segregate processes into hierarchical partitions (“namespaces”) from
which they see only a subset of the system’s files, network ports, and
processes. Among other effects, this scheme acts as a form of preemptive access
control.

This clever trick is one of the foundations of software containerization and
its best-known implementation, Docker.

## 3.4 Modern Access Control

### Separate ecosystems

Access control is inherently a kernel-level concern. With the exception of
filesystem access control lists, there is essentially no standardization among
systems with regard to alternative access control mechanisms. As a result,
every kernel has its own array of available implementations, and none of them
are cross-platform.

Because Linux distributions share a common kernel lineage, all Linux
distributions are theoretically compatible with all the various Linux security
offerings.

### Mandatory access control

The standard UNIX model is considered a form of “discretionary access control”
because it allows the owners of access-controlled entities to set the
permissions on them. Discretionary access control provides no particular
guarantee of security for user-level data. The **downside** of letting users set
permissions is that users can set permissions. And even with the best
intentions and training, users can make mistakes.

Mandatory access control (aka MAC) systems let administrators write access
control policies that override or supplement the discretionary permissions of
the traditional model.

### Role-based access control

Another feature commonly name-checked by access control systems is role-based
access control (aka RBAC), a theoretical model formalized in 1992 by David
Ferraiolo and Rick Kuhn.

The basic idea is to add a layer of indirection to access control calculations.
Instead of permissions being assigned directly to users, they are assigned to
intermediate constructs known as "roles", and roles in turn are assigned to
users.

Roles are similar in concept to UNIX groups, but they’re more general because
they can be used outside the context of the filesystem. Roles can also have a
hierarchical relationship to one another. For example, you might define a
"senior administrator" role that has all the permissions of an "administrator"
plus the additional permissions X, Y, and Z.

RBAC of Unix variants:

- Solaris
- HP-UX
- AIX

### SELinux: security-enhanced Linux

The primary focus of SELinux is to enable "mandatory access control", aka MAC.
Under MAC, users cannot delegate their access or set access control parameters
on the objects they own.

This book regards that SELinux is capable of delivering more harm than benefit.
That harm can manifest not only as wasted time and aggravation for system
administrators, but also, ironically, as security lapses. Complex models are
hard to reason about, and SELinux isn’t really a level playing field; hackers
that focus on it understand the system far more thoroughly than the average
sysadmin.

Fortunately, many general policies are available on-line, and most
SELinux-enabled distributions come with reasonable defaults. A full-blown
policy editor that aims to ease policy application can be found at
<http://seedit.sourceforge.net>.

`/etc/selinux/config` is the top-level control for SELinux. The interesting
lines are

```conf
SELINUX=enforcing
SELINUXTYPE=targeted
```

The first line has three possible values: `enforcing`, `permissive`, or
`disabled`. The `enforcing` setting ensures that the loaded policy is applied
and prohibits violations. `permissive` allows violations to occur but logs them
through syslog, which is valuable for debugging and policy development.
`disabled` turns off SELinux entirely.

`SELINUXTYPE` refers to the name of the policy database to be applied. This is
essentially the name of a subdirectory within `/etc/selinux`. Only one policy
can be active at a time, and the available policy sets vary by system.

### AppArmor

It’s supported by Debian and Ubuntu, but has also been adopted as a standard by
SUSE distributions.

AppArmor implements a form of MAC and is intended as a supplement to the
traditional UNIX access control system. Its main goal is service securement;
that is, limiting the damage that individual programs can do if they should be
compromised or run amok.

By default, AppArmor denies all requests, so the profile must explicitly name
everything the process is allowed to do.

AppArmor profiles are stored in `/etc/apparmor.d`, and they’re relatively
readable even without detailed knowledge of the system.
