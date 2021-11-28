# What is a Git workflow?

> <https://about.gitlab.com/topics/version-control/what-is-git-workflow/>

Empowering a software development team begins with identifying a single
branching strategy.

## Why do you need to determine a Git workflow?

Identifying a single Git workflow is a necessary step in ensuring rapid
delivery. Software development teams encompass contributors from various
backgrounds and experiences, and they’re likely to feel comfortable with a
workflow they’ve used previously. Without a single workflow, a team’s
development could be chaotic and slow down cycle time.
[Git workflows empower teams](https://about.gitlab.com/blog/2019/10/28/optimize-gitops-workflow/)
to determine roles and responsibilities, set boundaries, and identify areas of
improvement.

## The top six Git workflows to strengthen software development

### 1. Centralized Git workflow

A centralized Git workflow enables all team members to make changes directly to
the main branch, with every change logged in a running history. A centralized
workflow involves every contributor committing to the main branch without using
any other branch. This strategy works well for small teams, because team
members can communicate so that multiple developers aren’t contributing to the
same piece of code simultaneously. Centralized workflow can be seamless if team
members communicate well, but there are limitations. If multiple developers
commit to the same branch, it’s challenging to find a stable moment to release
changes. Consequently, developers must keep unstable changes local until
they’re ready for release.

#### What is the benefit of a centralized Git workflow?

After developers apply a stash and solve any merge conflicts, they can just
commit as usual without dealing with
[automatic merge commits](https://about.gitlab.com/blog/2020/03/25/git-merge-fifteen-year-git-party/),
unless someone pushed their changes at the same time. Because this strategy is
simple, it is well-suited for small teams, Git beginners, and projects that
don’t get a lot of updates.

### 2. Feature branching Git workflow

Every feature gets its own branch when developers commit to this workflow.
Rather than commit directly to the main branch, developers create a branch,
make changes, and then merge it into main.

Ideally, a branch should have a lifespan of a few hours. The longer the branch
lives, the higher the risk to find integration conflicts when merging back to
main. After all, at this scale, there are plenty of teams working on other
branches and directly streaming changes to the main branch, incrementing
entropy and chances of running into conflict with local changes.

#### What is the benefit of a feature branching Git workflow?

This Git workflow has the benefit of keeping a clean main branch that isn’t
polluted with unfinished features. Teams of any size can use this feature
branching, because it permits multiple developers to work on the same feature
simultaneously. Software that’s still in development sees the most benefit from
feature branching, but this workflow can be used for more mature applications
as well.

### 3. Trunk-based development Git workflow

Trunk-based development facilitates concurrent development on a single branch
called trunk. When developers are ready to push changes to the central
repository, they’ll pull and rebase from it to update the working copy of the
central branch. Successful trunk-based development requires a developer to
resolve merge conflicts locally. Regularly updating the local branch reduces
the impact of integration changes, because they’re spotted when they’re still
small, avoiding merge hell.

#### What is the benefit of trunk-based development Git workflow?

Trunk-based development decreases the likelihood of merge conflicts and keeps
code clean, because there are many frequent, small merges made each day. With
continuous integration, a trunk-based workflow ensures fast feedback and a
team-oriented approach to code ownership and development.

### 4. Personal branching Git workflow

Personal branching is similar to feature branching, but rather than have a
single branch per feature, it’s per developer. This approach works well if team
members work on different features and bugs. Every user can merge back to the
main branch whenever their work is done.

#### What is the benefit of personal branching Git workflow?

Personal branching has similar advantages as feature branching, and also
benefits from having fewer branches, so branch management is easier. Personal
branches can be used for bug fixes and other small changes, and they help
developers innovate if they’re interested in experimenting. Personal branching
is useful for long-running features that may not fit into a single release
cycle. This strategy can work well for small teams in which every team member
develops their own part of the application.

### 5. Forking Git workflow

A forking approach to [version control](https://about.gitlab.com/topics/version-control/)
starts with a complete copy of the repository. Forking effectively creates a
local copy of a Git repository and provides the ability to create a new
collaboration structure. In other words, every developer in the team has two
repositories: a local workspace and a remote repository.

This workflow is popular for projects that have multiple developers
contributing to it, particularly open source projects. After all, keeping track
and providing privileges to collaborate to a repository with thousands of
contributors is difficult to maintain. If a maintainer enables contributors to
try their changes on their forked copy, managing change proposals is easier and
safer.

#### What is the benefit of a forking Git workflow?

With a forking workflow, contributors can push changes to a server-side
repository, decreasing the likelihood of including low-quality code and bugs
into the source code. Only a project maintainer can integrate changes to the
source code. When large teams collaborate on software development projects,
forking enables secure, quality-driven development.

### 6. GitFlow Git workflow

With GitFlow, the main branch should always be releasable to production, and
there should never be untested or incomplete code on the main branch. When
using this Git workflow, no one commits to the main branch but rather uses a
develop branch with feature branches. When the develop branch is ready to go to
production, a contributor creates a release branch where testing and bug fixing
occur before being merged back to the develop branch. The release branch makes
the code review process easier, because there’s a dedicated place to resolve
conflicts when merging into the main branch. With this strategy, the main
branch always reflects production.
