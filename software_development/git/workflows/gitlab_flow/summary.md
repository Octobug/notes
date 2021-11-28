# GitLab Flow Summary

> Full: [GitLab Flow](README.md)

## Working with Git

1. Working on local copy
2. `git add` to staging
3. `git commit` to local repository
4. `git push` to remote repository

## Git flow and its problems

1. developers must use the `develop` branch instead of `main`, `main` is
    reserved for code that is released to production. But `main` branch is
    commonly considered a default branch.
2. hotfix and release branches make Git flow complex.

## GitHub flow as a simpler alternative

Leaves questions unanswered regarding deployments, environments, releases, and
integrations with issues.

## Production branch with GitLab flow

You can deploy a new version by merging development into the production branch.
This flow prevents the overhead of releasing, tagging, and merging that happens
with Git flow.

## Environment branches with GitLab flow

This workflow, where commits only flow downstream, ensures that everything is
tested in all environments.

If you need to cherry-pick a commit with a hotfix, it is common to develop it
on a feature branch and merge it into `production` with a merge request. If
`production` passes automatic testing, you then merge the feature branch into
the other branches.

## Release branches with GitLab flow

You should work with release branches only if you need to release software to
the outside world.

Create stable branches using `main` as a starting point, and branch as late as
possible.

If possible, first merge these bug fixes into `main`, and then cherry-pick them
into the release branch. If you start by merging into the release branch, you
might forget to cherry-pick them into `main`, and then you’d encounter the same
bug in subsequent releases.

Every time you include a bug fix in a release branch, increase the patch
version by setting a new tag.

## Merge/pull requests with GitLab flow

When you are ready for your feature branch to be merged, assign the merge
request to the person who knows most about the codebase you are changing.

In GitLab, it is common to protect the long-lived branches, such as the `main`
branch.

## Issue tracking with GitLab flow

Any significant change to the code should start with an issue that describes
the goal.

The issue title should describe the desired state of the system. For example,
the issue title “As an administrator, I want to remove users without receiving
an error” is better than “Administrators can’t remove users.”

When you are ready to code, create a branch for the issue from the `main`
branch. This branch is the place for any work related to this change.

The reviewer can merge the changes when they think the code is ready for
inclusion in the `main` branch.

At any time, there is at most one branch for every issue. It is possible that
one feature branch solves more than one issue.

## Squashing commits with rebase

You should avoid rebasing commits you have pushed to a remote server if you
have other active contributors in the same branch. Because rebasing creates new
commits for all your changes, it can cause confusion because the same change
would have multiple identifiers.

You should never rebase commits authored by other people unless you’ve agreed
otherwise. Not only does this rewrite history, but it also loses authorship
information.

If a merge involves many commits, it may seem more difficult to undo. You might
consider solving this by squashing all the changes into one commit just before
merging by using the GitLab Squash-and-Merge feature.

Fortunately, you can undo a merge with all its commits. The way to do this is
by reverting the merge commit. Preserving this ability to revert a merge is a
good reason to always use the “no fast-forward” (--no-ff) strategy when you
merge manually.

## Reducing merge commits in feature branches

Having lots of merge commits can make your repository history messy. Therefore,
you should try to avoid merge commits in feature branches.

Often, people avoid merge commits by just using rebase to reorder their commits
after the commits on the `main` branch. Using rebase prevents a merge commit
when merging main into your feature branch, and it creates a neat linear
history.

A good way to prevent creating many merge commits is to **not** frequently merge
`main` into the feature branch.

If you need to use some code that was introduced in `main` after you created
the feature branch, you can often solve this by just cherry-picking a commit.

If your feature branch has a merge conflict, creating a merge commit is a
standard way of solving this.

The last reason for creating merge commits is to keep long-running feature
branches up-to-date with the latest state of the project. The solution here is
to keep your feature branches short-lived.

In conclusion, you should try to prevent merge commits, but not eliminate them.
Your codebase should be clean, but your history should represent what actually
happened.

## Commit often and push frequently

Another way to make your development work easier is to commit often. Every time
you have a working set of tests and code, you should make a commit.

Smaller commits make it clear how a feature was developed.

## How to write a good commit message

An example of a good commit message is: “Combine templates to reduce duplicate
code in the user views.” The words “change,” “improve,” “fix,” and “refactor”
don’t add much information to a commit message.

## Testing before merging

When using GitLab flow, developers create their branches from this `main`
branch, so it is essential that it never breaks. Therefore, each merge request
must be tested before it is accepted.

There is one drawback to testing merge requests: the CI server only tests the
feature branch itself, not the merged result.

## Working with feature branches

When creating a feature branch, always branch from an up-to-date `main`.

If you know before you start that your work depends on another branch, you can
also branch from there.

If you need to merge in another branch after starting, explain the reason in
the merge commit.

If you have not pushed your commits to a shared location yet, you can also
incorporate changes by rebasing on `main` or another feature branch.

Do not merge from upstream again if your code can work and merge cleanly
without doing so. Merging only when needed prevents creating merge commits in
your feature branch that later end up littering the main history.
