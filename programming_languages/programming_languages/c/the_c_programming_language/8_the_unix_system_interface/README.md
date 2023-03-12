# Chapter 8: The UNIX System Interface

- [Chapter 8: The UNIX System Interface](#chapter-8-the-unix-system-interface)
  - [8.1 File Descriptors](#81-file-descriptors)
  - [8.2 Low Level I/O - Read and Write](#82-low-level-io---read-and-write)
  - [8.3 Open, Creat, Close, Unlink](#83-open-creat-close-unlink)
  - [8.4 Random Access - Lseek](#84-random-access---lseek)
  - [8.5 Example - An implementation of Fopen and Getc](#85-example---an-implementation-of-fopen-and-getc)
  - [8.6 Example - Listing Directories](#86-example---listing-directories)

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

>>>>> progress
