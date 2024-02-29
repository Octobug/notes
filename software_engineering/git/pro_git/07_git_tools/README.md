# 7. Git Tools

> <https://git-scm.com/book/en/v2/Git-Tools-Revision-Selection>

## 7.6 Git Tools - Rewriting History

> <https://git-scm.com/book/en/v2/Git-Tools-Rewriting-History>

⚠️ Note: Don’t push your work until you’re happy with it

### Changing the Last Commit

`git commit --amend`

You need to be careful with this technique because amending changes the SHA-1
of the commit. It’s like a very small rebase — don’t amend your last commit if
you’ve already pushed it.

`git commit --amend --no-edit`: just keep the existing message

### Changing Multiple Commit Messages

Git does **not** have a modify-history tool, but you can use the rebase tool to
rebase a series of commits onto the HEAD that they were originally based on
instead of moving them to another one.

`git rebase -i <identifier>`

For example, to change last three commit messages:

`git rebase -i HEAD~2^` or `git rebase -i HEAD~3`, which actually designates
four commits ago, the parent of the last commit you want to edit.

Every commit in the range `HEAD~3..HEAD` with a changed message **and all of its
descendants** will be rewritten. Do **not** include any commit you've already
pushed to a central server.

The interactive rebase gives you a script that it's going to run. It will start
at the commit you specify on the command line (`HEAD~3`) and replay the changes
introduced in each of these commits from top to bottom. It lists the oldest at
the top, rather than the newest.

### Reordering Commits

To reorder (remove) commits, just reorder (remove) the rebase script lines in
the interactive editor.

### Squashing Commits

### Splitting a Commit

For example, suppose you want to split the middle commit of your three commits.
Instead of “Update README formatting and add blame”, you want to split it into
two commits: “Update README formatting” for the first, and “Add blame” for the
second. You can do that in the rebase -i script by changing the instruction on
the commit you want to split to “edit”:

```git
pick f7f3f6d Change my name a bit
edit 310154e Update README formatting and add blame
pick a5f4a0d Add cat-file
```

Then, when the script drops you to the command line, you reset that commit,
take the changes that have been reset, and create multiple commits out of them.
When you save and exit the editor, Git rewinds to the parent of the first
commit in your list, applies the first commit (`f7f3f6d`), applies the second
(`310154e`), and drops you to the console. There, you can do a mixed reset of
that commit with git reset HEAD^, which effectively undoes that commit and
leaves the modified files unstaged. Now you can stage and commit files until
you have several commits, and run git rebase --continue when you’re done:

```sh
git reset HEAD^
git add README
git commit -m 'Update README formatting'
git add lib/simplegit.rb
git commit -m 'Add blame'
git rebase --continue
```

### Deleting a commit

If you want to get rid of a commit, you can delete it using the `rebase -i`
script. In the list of commits, put the word “drop” before the commit you want
to delete (or just delete that line from the rebase script):

```git
pick 461cb2a This commit is OK
drop 5aecc10 This commit is broken
```

Because of the way Git builds commit objects, deleting or altering a commit
will cause the rewriting of all the commits that follow it. The further back in
your repo’s history you go, the more commits will need to be recreated. This
can cause lots of merge conflicts if you have many commits later in the
sequence that depend on the one you just deleted.

If you get partway through a rebase like this and decide it’s not a good idea,
you can always stop. Type `git rebase --abort`, and your repo will be returned
to the state it was in before you started the rebase.

If you finish a rebase and decide it’s not what you want, you can use git
reflog to recover an earlier version of your branch.

### The Nuclear Option: filter-branch

There is another history-rewriting option that you can use if you need to
rewrite a larger number of commits in some scriptable way — for instance,
changing your email address globally or removing a file from every commit. The
command is `filter-branch`, and it can rewrite huge swaths of your history, so
you probably shouldn’t use it unless your project isn’t yet public and other
people haven’t based work off the commits you’re about to rewrite. However, it
can be very useful. You’ll learn a few of the common uses so you can get an
idea of some of the things it’s capable of.

⚠️ `git filter-branch` has many pitfalls, and is no longer the recommended way
to rewrite history. Instead, consider using `git-filter-repo`, which is a
Python script that does a better job for most applications where you would
normally turn to `filter-branch`. Its documentation and source code can be
found at <https://github.com/newren/git-filter-repo>.

#### Removing a File from Every Commit

To remove a file named `passwords.txt` from your entire history, you can use
the `--tree-filter` option to `filter-branch`:

```sh
git filter-branch --tree-filter 'rm -f passwords.txt' HEAD
Rewrite 6b9b3cf04e7c5686a9cb838c3f36a8cb6a0fc2bd (21/21)
Ref 'refs/heads/master' was rewritten
```

The `--tree-filter` option runs the specified command after each checkout of
the project and then recommits the results.

It’s generally a good idea to do this in a testing branch and then hard-reset
your `master` branch after you’ve determined the outcome is what you really
want. To run `filter-branch` on all your branches, you can pass `--all` to the
command.

#### Making a Subdirectory the New Root

Suppose you’ve done an import from another source control system and have
subdirectories that make no sense (`trunk`, `tags`, and so on). If you want to
make the `trunk` subdirectory be the new project root for every commit,
`filter-branch` can help you do that, too:

```sh
git filter-branch --subdirectory-filter trunk HEAD
Rewrite 856f0bf61e41a27326cdae8f09fe708d679f596f (12/12)
Ref 'refs/heads/master' was rewritten
```

Now your new project root is what was in the `trunk` subdirectory each time.
Git will also automatically remove commits that did not affect the subdirectory.

#### Changing Email Addresses Globally

You need to be careful to change only the email addresses that are yours, so
you use `--commit-filter`:

```sh
git filter-branch --commit-filter '
        if [ "$GIT_AUTHOR_EMAIL" = "schacon@localhost" ];
        then
                GIT_AUTHOR_NAME="Scott Chacon";
                GIT_AUTHOR_EMAIL="schacon@example.com";
                git commit-tree "$@";
        else
                git commit-tree "$@";
        fi' HEAD
```

This goes through and rewrites every commit to have your new address. Because
commits contain the SHA-1 values of their parents, this command changes every
commit SHA-1 in your history, not just those that have the matching email
address.
