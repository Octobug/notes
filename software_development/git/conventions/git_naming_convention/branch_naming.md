# Git Naming Convention > Branch Naming

> <https://github.com/naming-convention/naming-convention-guides/blob/master/git/branch-naming.md>

Must:

- Include a short descriptive summary in imperative present tense
- Use Hyphens for separating words

May:

- Include the work type: feature, refactor, bugfix, hotfix, etc.
- Include corresponding ticket/story id (e.g. from Jira, GitHub issue, etc.)

Suggested Format:  
*{work type e.g.}/{2-3 word summary}/{story or ticket id}_*

Example:

```sh
git checkout -b feature/oauth-migration/ATL-244
```
