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
