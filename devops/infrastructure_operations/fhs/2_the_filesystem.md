# Chapter 2. The Filesystem

> <https://refspecs.linuxfoundation.org/FHS_3.0/fhs/ch02.html>

It is possible to define two independent distinctions among files: **shareable**
vs. **unshareable** and **variable** vs. **static**. In general, files that
differ in either of these respects should be located in different directories.
This makes it easy to store files with different usage characteristics on
different filesystems.

"Shareable" files are those that can be stored on one host and used on others.
"Unshareable" files are those that are not shareable. For example, the files in
user home directories are shareable whereas device lock files are not.

"Static" files include binaries, libraries, documentation files and other files
that do not change without system administrator intervention. "Variable" files
are files that are not static.

## Rationale

Shareable files can be stored on one host and used on several others. Typically,
however, not all files in the filesystem hierarchy are shareable and so each
system has local storage containing at least its unshareable files. It is
convenient if all the files a system requires that are stored on a foreign host
can be made available by mounting one or a few directories from the foreign host.

Static and variable files should be segregated because static files, unlike
variable files, can be stored on read-only media and do not need to be backed
up on the same schedule as variable files.

Historical UNIX-like filesystem hierarchies contained both static and variable
files under both `/usr` and `/etc`. In order to realize the advantages
mentioned above, the `/var` hierarchy was created and all variable files were
transferred from `/usr` to `/var`. Consequently `/usr` can now be mounted
read-only (if it is a separate filesystem). Variable files have been
transferred from `/etc` to `/var` over a longer period as technology has
permitted.

Here is an example of a FHS-compliant system. (Other FHS-compliant layouts are possible.)

| /        | shareable         | unshareable |
| -------- | ----------------- | ----------- |
| static   | `/usr`            | `/etc`      |
| /        | `/opt`            | `/boot`     |
| variable | `/var/mail`       | `/var/run`  |
| /        | `/var/spool/news` | `/var/lock` |
