# 12 Special file types

## 12.2 ln: Make links between files

```bash
ln [option]… [-T] target linkname
```

### How to find hard/symbolic links?

```bash
# hard link
find . -samefile /path/to/file

# symbolic link
find . -type l -ls
```

### References

- [12.2 ln: Make links between files](https://www.gnu.org/software/coreutils/manual/html_node/ln-invocation.html#ln-invocation)
- [How to find all hard links to a given file?](https://unix.stackexchange.com/a/201922/389858)
- [How to list all symbolic links in a directory](https://askubuntu.com/a/522059/1120167)
- [Why do hard links seem to take the same space as the originals?](https://unix.stackexchange.com/a/88426/389858)
