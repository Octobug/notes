# Git

> <https://git-scm.com/>

## Untrack files

```sh
# untrack
git update-index --assume-unchanged FILE

# track again
git update-index --no-assume-unchanged FILE

# list untracked files
git ls-files -v | grep ^[h]
```

## Git Config

- [Git Config](config.md)

## Useful Extensions

- [Git LFS](https://git-lfs.github.com/)

## Learning Materials

- [Git Conventions](conventions)
- [Git Reference](git_reference)
- [Pro Git](pro_git)
