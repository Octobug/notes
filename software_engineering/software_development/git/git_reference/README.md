# Reference

> <http://git-scm.com/docs>

## Guides

### gitignore

> <http://git-scm.com/docs/gitignore>

#### Precedence (from highest to lowest)

Within one level of precedence, the last matching pattern decides the outcome.

- Patterns read from the command line for those commands that support them.
- Patterns read from a `.gitignore` file in the same directory as the path, or
  in any parent directory (up to the top-level of the working tree), with
  patterns in the higher level files being overridden by those in lower level
  files down to the directory containing the file. These patterns match
  relative to the location of the `.gitignore` file. A project normally
  includes such `.gitignore` files in its repository, containing patterns for
  files generated as part of the project build.
- Patterns read from `$GIT_DIR/info/exclude`.
- Patterns read from the file specified by the configuration variable
  `core.excludesFile`.

#### Examples

- The pattern `hello.*` matches any file or folder whose name begins with
  `hello.`. If one wants to restrict this only to the directory and not in its
  subdirectories, one can prepend the pattern with a slash, i.e. `/hello.*`;
  the pattern now matches `hello.txt`, `hello.c` but not `a/hello.java`.
- The pattern `doc/frotz` and `/doc/frotz` have the same effect in any
  `.gitignore` file. In other words, a leading slash is not relevant if there
  is already a middle slash in the pattern.
