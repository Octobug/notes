# Appendix B - Standard Library

The ANSI standard library is not part of the C language proper, but an
environment that supports standard C will provide the `function declarations`
and `type` and `macro definitions` of this library.

The `functions`, `types` and `macros` of the standard library are declared in
standard `headers`:

- <assert.h>
- <float.h>
- <math.h>
- <stdarg.h>
- <stdlib.h>
- <ctype.h>
- <limits.h>
- <setjmp.h>
- <stddef.h>
- <string.h>
- <errno.h>
- <locale.h>
- <signal.h>
- <stdio.h>
- <time.h>

Headers may be included in any order and any number of times. A header must be
included outside of any external declaration or definition and before any use
of anything it declares. A header need **not** be a source file.

External identifiers that begin with an underscore are reserved for use by the
library, as are all other identifiers that begin with an underscore and an
uppercase letter or another underscore.

## B.1 Input and Output: `<stdio.h>`

The input and output `functions`, `types`, and `macros` defined in `<stdio.h>`
represent nearly one third of the library.

A `stream` is a source or destination of data that may be associated with a
disk or other peripheral. The library supports text streams and binary streams,
although on some systems, notably UNIX, these are identical.

- A text stream is a sequence of lines; each line has zero or more characters
  and is terminated by `'\n'`. An environment may need to convert a text stream
  to or from some other representation (such as mapping '\n' to carriage return
  and linefeed).
- A binary stream is a sequence of unprocessed bytes that record internal data,
  with the property that if it is written, then read back on the same system,
  it will compare equal.

A stream is connected to a file or device by opening it; the connection is
broken by `closing` the stream. Opening a file returns a pointer to an object
of type `FILE`, which records whatever information is necessary to control the
stream. We will use `file pointer` and `stream` interchangeably when there is
no ambiguity.

When a program begins execution, the three streams `stdin`, `stdout`, and
`stderr` are already open.
