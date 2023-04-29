# Chapter 8: The UNIX System Interface

- [Chapter 8: The UNIX System Interface](#chapter-8-the-unix-system-interface)
  - [8.1 File Descriptors](#81-file-descriptors)
  - [8.2 Low Level I/O - Read and Write](#82-low-level-io---read-and-write)
  - [8.3 Open, Creat, Close, Unlink](#83-open-creat-close-unlink)
  - [8.4 Random Access - Lseek](#84-random-access---lseek)
  - [8.5 Example - An implementation of Fopen and Getc](#85-example---an-implementation-of-fopen-and-getc)
  - [8.6 Example - Listing Directories](#86-example---listing-directories)
  - [8.7 Example - A Storage Allocator](#87-example---a-storage-allocator)

## 8.1 File Descriptors

In the UNIX operating system, all input and output is done by reading or writing
files, because all peripheral devices, even keyboard and screen, are files in
the file system. This means that a single homogeneous interface handles all
communication between a program and peripheral devices.

You must inform the system of your intent to read and write a file. The system
checks your right to do so and if all is well, returns to the program a small
non-negative integer called a `file descriptor` (which is analogous to the file
pointer used by the standard library, or to the file handle of MS-DOS). The file
descriptor is used instead of the name to identify the file. All information
about an open file is maintained by the system.

When the shell runs a program, three files are open, with file descriptors 0, 1,
and 2, called the standard input, the standard output, and the standard error.
The user of a program can redirect I/O to and from files with `<` and `>`. The
file assignments are changed by the shell, not by the program. The program does
not know where its input comes from nor where its ouput goes.

## 8.2 Low Level I/O - Read and Write

```c
int n_read = read(int fd, char *buf, int n);
int n_written = write(int fd, char *buf, int n);
```

On reading, the number of bytes returned may be less than `n_read`. For writing,
the return value is the number of bytes written; an error has occurred if this
isn't equal to the number requested.

The most common read and written values are 1, which means one character at a
time (`unbuffered`), and a number like 1024 or 4096 that corresponds to a
physical block size on a peripheral device. Larger sizes will be more efficient
because fewer system calls will be made.

eg. copy input to output

```c
#include "syscalls.h"

int main() /* copy input to output */
{
    char buf[BUFSIZ];
    int n;

    while ((n = read(0, buf, BUFSIZ)) > 0)
    {
        write(1, buf, n);
    }
    return 0;
}
```

eg. getchar() that does unbuffered input

```c
#include "syscalls.h"

/* getchar: unbuffered single character input */
int getchar(void)
{
    char c;
    return (read(0, &c, 1) == 1) ? (unsigned char)c : EOF;
}
```

eg. getchar() that does buffered input

```c
#include "syscalls.h"

/* getchar: simple buffered version */
int getchar(void)
{
    static char buf[BUFSIZ];
    static char *bufp = buf;
    static int n = 0;

    while (n == 0) /* buffer is empty */
    {
        n = read(0, buf, sizeof buf);
        bufp = buf;
    }
    return (--n >= 0) ? (unsigned char)*bufp++ : EOF;
}
```

⚠️ If these versions of `getchar` were to be compiled with `<stdio.h>` included,
it would be necessary to `#undef` the name `getchar` in case it is implemented
as a macro.

## 8.3 Open, Creat, Close, Unlink

Other than the default standard input, output, and error, you must explicitly
open files in order to read or write them. There are two system calls for this,
`open` and `creat`.

`open` returns a file descriptor, which is just an `int`, instead of a file
pointer.

```c
#include <fcntl.h>

int fd;
int open(char *name, int flags, int perms);

fd = open(name, flags, perms);
```

The main values of flags are:

- `O_RDONLY`: open for reading only
- `O_WRONLY`: open for writing only
- `O)RDWR`: open for both reading and writing

```c
int creat(char *name, int perms);
fd = creat(name, perms);
```

In the UNIX file system, there are nine bits of permission information
associated with a file that control read, write, and execute access for the
owner of the file, for the owner's group, and for all others.

eg. simplified version of `cp`

```c
#include <fcntl.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include "syscalls.h"

#define PERMS 0666 /* RW for owner, group, others */

void error(const char *, ...);

/* cp: copy f1 to f2 */
int main(int argc, char *argv[])
{
    int f1, f2, n;
    char buf[BUFSIZ];

    if (argc != 3)
    {
        error("Usage: cp from to");
    }
    if ((f1 = open(argv[1], O_RDONLY, 0)) == -1)
    {
        error("cp: can't open %s", argv[1]);
    }
    if ((f2 = creat(argv[2], PERMS)) == -1)
    {
        error("cp: can't create %s, mode %03o", argv[2], PERMS);
    }
    while ((n = read(f1, buf, BUFSIZ)) > 0)
    {
        if (write(f2, buf, n) != n)
        {
            error("cp: write error on file %s", argv[2]);
        }
    }
    return 0;
}

/* error: print an error message and die */
void error(const char *fmt, ...)
{
    va_list args;

    va_start(args, fmt);
    fprintf(stderr, "error: ");
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n");
    va_end(args);
    exit(1);
}
```

The function `close(int fd)` breaks the connection between a file descriptor and
an open file, and frees the file descriptor for use with some other file; it
corresponds to `fclose` in the standard library except that there is no buffer
to flush.

The function `unlink(char *name)` removes the file `name` from the file system.
It corresponds to the standard library function `remove`.

## 8.4 Random Access - Lseek

A file can be read or written in any arbitrary order. The system call `lseek`
provides a way to move around in a file without reading or writing any data.

```c
long lseek(int fd, long offset, int origin);
```

`lseek` sets the current position in the file whose descriptor is `fd` to
`offset`, which is taken relative to the location specified by `origin`.
Subsequent reading or writing will begin at that position. `origin` can be
`0`, `1`, or `2` to specify that `offset` is to be measured from the beginning,
from the current position, or from the end of the file respectively.

For example, to append to a file, seek to the end before writing:

```c
lseek(fd, 0L, 2);
```

To get back to the beginning:

```c
lseek(fd, 0L, 0);
```

With `lseek`, it is possible to treat files more or less like arrays, at the
price of slower access.

eg. reads any number of bytes from any arbitrary place in a file

```c
#include "syscalls.h"

/* get: read n bytes from position pos */
int get(int fd, long pos, char *buf, int n)
{
    if (lseek(fd, pos, 0) >= 0) /* get to pos */
    {
        return read(fd, buf, n);
    }
    else
    {
        return -1;
    }
}
```

The standard library function `fseek` is similar to `lseek` except that the
first argument is a `FILE *` and the return is non-zero if an error occurred.

## 8.5 Example - An implementation of Fopen and Getc

A file pointer is a pointer to a structure that contains several pieces of
information about the file: a pointer to a buffer, so the file can be read in
large chunks; a count of the number of characters left in the buffer; a pointer
to the next character position in the buffer; the file descriptor; and flags
describing read/write mode, error status, etc.

The data structure that describes a file is contained in `<stdio.h>`, which must
be included in any source file that uses routines from the standard input/output
library.

```c
#define getc(p) (--(p)->cnt >= 0 \
                ? (unsigned char) *(p)->ptr++ : _fillbuf(p))
```

eg. `fopen`

```c
#include <fcntl.h>
#include "syscalls.h"
#define PERMS 0666
#define OPEN_MAX 20

typedef struct _iobuf
{
    int cnt;    // characters left
    char *ptr;  // next character position
    char *base; // location of buffer
    int flag;   // mode of file access
    int fd;     // file descriptor
} FILE;

extern FILE _iob[OPEN_MAX];

enum _flags
{
    _READ = 01,  // file open for reading
    _WRITE = 02, // file open for writing
    _UNBUF = 04, // file is unbuffered
    _EOF = 010,  // EOF has occurred on this file
    _ERR = 020   // error occurred on this file
};

FILE _iob[OPEN_MAX] = { // stdin, stdout, stderr
    {0, (char *)0, (char *)0, _READ, 0},
    {0, (char *)0, (char *)0, _WRITE, 1},
    {0, (char *)0, (char *)0, _WRITE | _UNBUF, 2}};

FILE *fopen(char *name, char *mode)
{
    int fd;
    FILE *fp;

    if (*mode != 'r' && *mode != 'w' && *mode != 'a')
    {
        return NULL;
    }

    for (fp = _iob; fp < _iob + OPEN_MAX; fp++)
    {
        if ((fp->flag & (_READ | _WRITE)) == 0)
        {
            break; /* found free slot */
        }
    }

    if (fp >= _iob + OPEN_MAX) // no free slots
    {
        return NULL;
    }

    if (*mode == 'w')
    {
        fd = creat(name, PERMS);
    }
    else if (*mode == 'a')
    {
        if ((fd = open(name, O_WRONLY, 0)) == -1)
        {
            fd = creat(name, PERMS);
        }
        lseek(fd, 0L, 2);
    }
    else
    {
        fd = open(name, O_RDONLY, 0);
    }
    if (fd == -1) // couldn't access name
    {
        return NULL;
    }
    fp->fd = fd;
    fp->cnt = 0;
    fp->base = NULL;
    fp->flag = (*mode == 'r') ? _READ : _WRITE;
    return fp;
}
```

```c
FILE _iob[OPEN_MAX] = { // stdin, stdout, stderr
    {0, (char *)0, (char *)0, _READ, 0},
    {0, (char *)0, (char *)0, _WRITE, 1},
    {0, (char *)0, (char *)0, _WRITE | _UNBUF, 2}};
```

The initialization of the `flag` part of the structure shows that `stdin` is to
be read, `stdout` is to be written, and `stderr` is to be written unbuffered.

## 8.6 Example - Listing Directories

UNIX file system structure: a ***directory*** is a file that contains a list of
filenames and some indication of where they are located. The ***location*** is
an index into another table called the ***inode list***. The ***inode*** for a
file is where all information about the file except its name is kept. A
directory entry generally consists of only two items, the **filename** and an
**inode number**.

eg. `fsize`: a special form of `ls` that prints the sizes of all files named in
its commandline argument list.

The outer level defines a structure called a `Dirent` and three routines
`opendir`, `readdir`, and `closedir` to provide system-independent access to
the name and inode number in a directory entry.

The `Dirent` structure contains the inode number and the name. The maximum
length of a filename component is `NAME_MAX`, which is a system-dependent value.
`opendir` returns a pointer to a structure called `DIR`, analogous to `FILE`,
which is used by `readdir` and `closedir`. This information is collected into a
file called `dirent.h`.

The system call `stat` takes a filename and returns all of the information in
the inode for that file, or `-1` if there is an error.

```c
char *name;
struct stat stbuf;
int stat(char *, struct stat *);

stat(name, &stbuf);
```

fills the structure `stbuf` with the inode information for the file name. The
structure describing the value returned by `stat` is in `<sys/stat.h>`, and
typically looks like this:

```c
struct stat // inode information returned by stat
{
    dev_t   st_dev;     // device of inode
    ino_t   st_ino;     // inode number
    short   st_mode;    // mode bits
    short   st_nlink;   // number of links to file
    short   st_uid;     // owners user id
    short   st_gid;     // owners group id
    dev_t   st_rdev;    // for special files
    off_t   st_size;    // file size in characters
    time_t  st_atime;   // time last accessed
    time_t  st_mtime;   // time last modified
    time_t  st_ctime;   // time originally created
};
```

The types like `dev_t` and `ino_t` are defined in `<sys/types.h>`.

The `st_mode` entry contains a set of flags describing the file. The flag
definitions are also included in `<sys/types.h>`. Part of them are:

```c
#define S_IFMT  0160000 // type of file
#define S_IFDIR 0040000 // directory
#define S_IFCHR 0020000 // character special
#define S_IFBLK 0060000 // block special
#define S_IFREG 0010000 // regular
```

eg. `fsize`

```c
#include <fcntl.h> // flags for read and write
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>  // structure returned by stat
#include <sys/types.h> // typedefs
#include "dirent.h"
#include "syscalls.h"

#define MAX_PATH 1024
#ifndef DIRSIZ
#define DIRSIZ 14
#endif
struct direct
{                        // directory entry
    ino_t d_ino;         // inode number
    char d_name[DIRSIZ]; // long name does not have '\0'
};

void fsize(const char *);

/* print file name */
int main(int argc, char **argv)
{
    if (argc == 1) // default: current directory (no args given)
    {
        fsize(".");
    }
    else
    {
        while (--argc > 0)
        {
            fsize(*++argv);
        }
    }
    return 0;
}

int stat(char *, struct stat *);
int fstat(int fd, struct stat *);
void dirwalk(const char *, void (*fcn)(const char *));

/* fsize: print the name of file "name" */
void fsize(const char *name)
{
    struct stat stbuf;
    {
        if (stat(name, &stbuf) == -1)
        {
            fprintf(stderr, "fsize: can't access %s\n", name);
            return;
        }
        if ((stbuf.st_mode & S_IFMT) == S_IFDIR)
        {
            dirwalk(name, fsize);
        }
        printf("%8lld %s\n", stbuf.st_size, name);
    };
}

/* dirwalk: apply fcn to all files in dir */
void dirwalk(const char *dir, void (*fcn)(const char *))
{
    char name[MAX_PATH];
    Dirent *dp;
    DIR *dfd;
    int path_len = 0;

    if ((dfd = opendir(dir)) == NULL)
    {
        fprintf(stderr, "dirwalk: can't open %s\n", dir);
        return;
    }
    while ((dp = readdir(dfd)) != NULL)
    {
        if (strcmp(dp->name, ".") == 0 || strcmp(dp->name, ".."))
        {
            continue; // skip self and parent
        }

        path_len = strlen(dir) + strlen(dp->name) + 2;
        if (path_len > sizeof(name))
        {
            fprintf(stderr, "dirwalk: name %s %s too long\n", dir, dp->name);
        }
        else
        {
            snprintf(name, path_len, "%s/%s", dir, dp->name);
            (*fcn)(name);
        }
    }
    closedir(dfd);
}

/* opendir: open a directory for readdir calls */
DIR *opendir(const char *dirname)
{
    int fd;
    struct stat stbuf;
    DIR *dp;

    if ((fd = open(dirname, O_RDONLY, 0)) == -1
        || fstat(fd, &stbuf) == -1
        || (stbuf.st_mode & S_IFMT) != S_IFDIR
        || (dp = (DIR *)malloc(sizeof(DIR))) == NULL)
    {
        return NULL;
    }
    dp->fd = fd;
    return dp;
}

/* closedir: close directory opened by opendir */
void closedir(DIR *dp)
{
    if (dp)
    {
        close(dp->fd);
        free(dp);
    }
}

/* readdir: read directory entries in sequence */
Dirent *readdir(DIR *dp)
{
    struct direct dirbuf; // local directory structure
    static Dirent d;      // return: portable structure

    while (read(dp->fd, (char *)&dirbuf, sizeof(dirbuf)) == sizeof(dirbuf))
    {
        if (dirbuf.d_ino == 0) // slot not in use
        {
            continue;
        }
        d.ino = dirbuf.d_ino;
        strncpy(d.name, dirbuf.d_name, DIRSIZ);
        d.name[DIRSIZ] = '\0'; // ensure termination
        return &d;
    }
    return NULL;
}
```

## 8.7 Example - A Storage Allocator

> These routines illustrate some of the considerations involved in writing
> machine-dependent code in a relatively machine-independent way.

Rather than allocating from a compiled-in fixed-size array, `malloc` will
request space from the operating system as needed. Since other activities in
the program may also request space without calling `malloc`, the space that
`malloc` manages may not be contiguous. Thus its free storage is kept as a list
of free blocks. Each blocks contains a size, a pointer to the next block, and
the space itself. The blocks are kept in order of increasing storage address,
and the last block (highest address) points to the first.

When a request is made, the free list is scanned until a big-enough block is
found. This algorithm is called `first fit`, by contrast with `best fit`, which
looks for the smallest block that will satisfy the request. If no big-enough
block is found, another large chunk is obtained by the operating system and
linked into the free list.

Freeing also causes a search of the free list, to find the proper place to
insert the block being freed. If the block being freed is adjacent to a free
block on either side, it is coalesced with it into a single bigger block, so
storage does not become too fragmented.

A free block contains a pointer to the next block in the chain, a record of the
size of the block, and then the free space itself; the control information at
the beginning is called the `header`. To simplify alignment, all blocks are
multiples of the header size, and the header is aligned properly. This is
achieved by a union that contains the desired header structure and an instance
of the most restrictive alignment type, which we have arbitrarily made a `long`:

```c
#include <stdio.h>

typedef long Align; // for a alignment to long boundary

union header // block header
{
    struct
    {
        union header *ptr; // next block if on free list
        unsigned size;     // size of this block
    } s;
    Align x; // force alignment of blocks
};

typedef union header Header;

static Header base;          // empty list to get started
static Header *freep = NULL; // start of free list

/* malloc: general-purpose storage allocator */
void *malloc(unsigned nbytes)
{
    Header *p, *prevp;
    Header *morecore(unsigned);
    unsigned nunits;

    nunits = (nbytes + sizeof(Header) - 1) / sizeof(Header) + 1;
    if ((prevp = freep) == NULL) // no free list yet
    {
        base.s.ptr = freep = prevp = &base;
        base.s.size = 0;
    }
    for (p = prevp->s.ptr;; prevp = p, p = p->s.ptr)
    {
        if (p->s.size >= nunits) // big enough
        {
            if (p->s.size == nunits) // exactly
            {
                prevp->s.ptr = p->s.ptr;
            }
            else // allocate tail end
            {
                p->s.size -= nunits;
                p += p->s.size;
                p->s.size = nunits;
            }
            freep = prevp;
            return (void *)(p + 1);
        }
        if (p == freep) // wrapped around free list
        {
            if ((p = morecore(nunits)) == NULL)
            {
                return NULL; // none left
            }
        }
    }
}
```

The `Align` field is never used; it just forces each header to be aligned on a
worst-case boundary.

In `malloc`, the requested size in characters is rounded up to the proper number
of header-size units; the block that will be allocated contains one more unit,
for the header itself, and this is the value recorded in the `size` field of the
header. The pointer returned by `malloc` points at the free space, not at the
header itself.

The size field is necessary because the blocks controlled by `malloc` need not
be contiguous - it is not possible to compute sizes by pointer arithmetic.

The variable `base` is used to get started. If `freep` is `NULL`, as it is at
the first call of `malloc`, then a degenerate free list is created; it contains
one block of size zero, and points to itself. The search for a free block of
adequate size begins at the point (`freep`) where the last block was found; this
strategy helps keep the list homogeneous. If a too-big block is found, the tail
end is returned to the user; in this way the header of the original needs only
to have its size adjusted.

The function `morecore` obtains storage from the operating system. Since asking
the system for memory is a comparatively expensive operation, we don't want to
do that on every call to `malloc`, so `morecore` requests at least `NALLOC`
units; this larger block will be chopped up as needed.

The UNIX system call `sbrk(n)` returns a pointer to `n` more bytes of storage.

`free` scans the free list, starting at `freep`, looking for the place to insert
the free block.
