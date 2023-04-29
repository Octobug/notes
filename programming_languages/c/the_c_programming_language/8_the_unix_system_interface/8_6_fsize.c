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

    if ((fd = open(dirname, O_RDONLY, 0)) == -1 || fstat(fd, &stbuf) == -1 || (stbuf.st_mode & S_IFMT) != S_IFDIR || (dp = (DIR *)malloc(sizeof(DIR))) == NULL)
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
