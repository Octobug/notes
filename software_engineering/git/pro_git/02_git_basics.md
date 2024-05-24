# 2. Git Basics

- [2. Git Basics](#2-git-basics)
  - [2.5 Git Basics - Working with Remotes](#25-git-basics---working-with-remotes)
    - [Working with Remotes](#working-with-remotes)
      - [Showing Your Remotes](#showing-your-remotes)
      - [Adding Remote Repositories](#adding-remote-repositories)
      - [Fetching and Pulling from Your Remotes](#fetching-and-pulling-from-your-remotes)
      - [Pushing to Your Remotes](#pushing-to-your-remotes)
      - [Inspecting a Remote](#inspecting-a-remote)
      - [Renaming and Removing Remotes](#renaming-and-removing-remotes)

## 2.5 Git Basics - Working with Remotes

> <https://git-scm.com/book/en/v2/Git-Basics-Working-with-Remotes>

### Working with Remotes

⚠️ Note **Remote repositories can be on your local machine.**

You can work with a “remote” repository that is, in fact, on the same host you
are. Working with such a remote repository would still involve all the standard
pushing, pulling and fetching operations as with any other remote.

#### Showing Your Remotes

- `git remove -v`

#### Adding Remote Repositories

- `git remote add <shortname> <url>`
- `git fetch <remote>`: the fetched `shortname/master` branch is now
  accessible locally as `shortname/master` - you can merge it into one of your
  branches, or you can check out a local branch at that point if you want to
  inspect it.

#### Fetching and Pulling from Your Remotes

- `git fetch <remote>`

The git fetch command only downloads the data to your local repository -
it doesn’t automatically merge it with any of your work or modify what you’re
currently working on. You have to merge it manually into your work.

#### Pushing to Your Remotes

- `git push origin master`

#### Inspecting a Remote

If you want to see more information about a particular remote, you can use the
`git remote show <remote>` command.

```sh
$ git remote show origin
* remote origin
  Fetch URL: https://github.com/schacon/ticgit
  Push  URL: https://github.com/schacon/ticgit
  HEAD branch: master
  Remote branches:
    master                               tracked
    dev-branch                           tracked
  Local branch configured for 'git pull':
    master merges with remote master
  Local ref configured for 'git push':
    master pushes to master (up to date)
```

It lists the URL for the remote repository as well as the tracking branch
information. The command helpfully tells you that if you’re on the `master`
branch and you run `git pull`, it will automatically merge the remote’s `master`
branch into the local one after it has been fetched.

When you’re using Git more heavily, however, you may see much more information
from git remote show:

```sh
$ git remote show origin
* remote origin
  URL: https://github.com/my-org/complex-project
  Fetch URL: https://github.com/my-org/complex-project
  Push  URL: https://github.com/my-org/complex-project
  HEAD branch: master
  Remote branches:
    master                           tracked
    dev-branch                       tracked
    markdown-strip                   tracked
    issue-43                         new (next fetch will store in remotes/origin)
    issue-45                         new (next fetch will store in remotes/origin)
    refs/remotes/origin/issue-11     stale (use 'git remote prune' to remove)
  Local branches configured for 'git pull':
    dev-branch merges with remote dev-branch
    master     merges with remote master
  Local refs configured for 'git push':
    dev-branch                     pushes to dev-branch                     (up to date)
    markdown-strip                 pushes to markdown-strip                 (up to date)
    master                         pushes to master                         (up to date)
```

It shows you which remote branches on the server you don’t yet have, which
remote branches you have that have been removed from the server, and multiple
local branches that are able to merge automatically with their remote-tracking
branch when you run git pull.

#### Renaming and Removing Remotes

You can run `git remote rename` to change a remote’s shortname.

```sh
$ git remote rename pb paul
$ git remote
origin
paul
```

If you want to remove a remote, you can either use `git remote remove` or
`git remote rm`:

```sh
$ git remote remove paul
$ git remote
origin
```
