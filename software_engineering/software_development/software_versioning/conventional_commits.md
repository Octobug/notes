# Conventional Commits

> <https://www.conventionalcommits.org/en/v1.0.0/>

A specification for adding human and machine readable meaning to commit messages

## Conventional Commits 1.0.0

### Summary

The Conventional Commits specification is a lightweight convention on top of
commit messages. It provides an easy set of rules for creating an explicit
commit history; which makes it easier to write automated tools on top of. This
convention dovetails with [SemVer](http://semver.org/), by describing the
features, fixes, and breaking changes made in commit messages.

The commit message should be structured as follows:

```git
<type>[optional scope]: <description>

[optional body]

[optional footer(s)]
```

The commit contains the following structural elements, to communicate intent to
the consumers of your library:

---

1. **fix**: a commit of the *type* `fix` patches a bug in your codebase (this correlates with PATCH in Semantic Versioning).
