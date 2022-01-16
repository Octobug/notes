# 7. Appendix

> <https://refspecs.linuxfoundation.org/FHS_3.0/fhs/ch07.html>

## Table of Contents

- [7. Appendix](#7-appendix)
  - [Table of Contents](#table-of-contents)
  - [7.1. The FHS mailing list](#71-the-fhs-mailing-list)
  - [7.2. Background of the FHS](#72-background-of-the-fhs)
  - [7.3. General Guidelines](#73-general-guidelines)
  - [7.4. Scope](#74-scope)
  - [7.5. Acknowledgments](#75-acknowledgments)
  - [7.6. Contributors](#76-contributors)

## 7.1. The FHS mailing list

The FHS mailing list is located at <fhs-discuss@lists.linuxfoundation.org>
(subscription required as a spam limitation measure). Mailing list subscription
information, archives, etc. are at <https://lists.linux-foundation.org/mailman/listinfo/fhs-discuss>

## 7.2. Background of the FHS

The process of developing a standard filesystem hierarchy began in August 1993
with an effort to restructure the file and directory structure of Linux. The
FSSTND, a filesystem hierarchy standard specific to the Linux operating system,
was released on February 14, 1994. Subsequent revisions were released on
October 9, 1994 and March 28, 1995.

In early 1995, the goal of developing a more comprehensive version of FSSTND to
address not only Linux, but other UNIX-like systems was adopted with the help
of members of the BSD development community. As a result, a concerted effort
was made to focus on issues that were general to UNIX-like systems. In
recognition of this widening of scope, the name of the standard was changed to
Filesystem Hierarchy Standard or FHS for short.

Volunteers who have contributed extensively to this standard are listed at the
end of this document. This standard represents a consensus view of those and
other contributors.

Thanks to Network Operations at the University of California at San Diego, and
later to SourceForge, who allowed us to use their excellent mailing list
servers during earlier phases of development.

## 7.3. General Guidelines

Here are some of the guidelines that have been used in the development of this
standard:

- Solve technical problems while limiting transitional difficulties.
- Make the specification reasonably stable.
- Gain the approval of distributors, developers, and other decision-makers in
  relevant development groups and encourage their participation.
- Provide a standard that is attractive to the implementors of different
  UNIX-like systems.

## 7.4. Scope

This document specifies a standard filesystem hierarchy for FHS filesystems by
specifying the location of files and directories, and the contents of some
system files.

This standard has been designed to be used by system integrators, package
developers, and system administrators in the construction and maintenance of
FHS compliant filesystems. It is primarily intended to be a reference and is
not a tutorial on how to manage a conforming filesystem hierarchy.

The FHS grew out of earlier work on FSSTND, a filesystem organization standard
for the Linux operating system. It builds on FSSTND to address interoperability
issues not just in the Linux community but in a wider arena including
**4.4BSD-based** operating systems. It incorporates lessons learned in the BSD
world and elsewhere about multi-architecture support and the demands of
heterogeneous networking.

Although this standard is more comprehensive than previous attempts at
filesystem hierarchy standardization, periodic updates may become necessary as
requirements change in relation to emerging technology. It is also possible
that better solutions to the problems addressed here will be discovered so that
our solutions will no longer be the best possible solutions. Supplementary
drafts may be released in addition to periodic updates to this document.
However, a specific goal is backwards compatibility from one release of this
document to the next.

Comments related to this standard are welcome. Any comments or suggestions for
changes may be directed to the FHS mailing list, or filed as bugs, or both.
Typographical or grammatical comments should be filed as bugs. The bugtracker
is at <http://bugs.linuxfoundation.org> - use the category FHS.

Before sending mail to the mailing list it is requested that you first glance
at the mailing list archives to avoid excessive re-discussion of old topics.

Questions about how to interpret items in this document may occasionally arise.
If you have need for a clarification, please contact the FHS mailing list.
Since this standard represents a consensus of many participants, it is
important to make certain that any interpretation also represents their
collective opinion. For this reason it may not be possible to provide an
immediate response unless the inquiry has been the subject of previous
discussion.

## 7.5. Acknowledgments

The developers of the FHS wish to thank the developers, system administrators,
and users whose input was essential to this standard. We wish to thank each of
the contributors who helped to write, compile, and compose this standard.

The FHS Group also wishes to thank those Linux developers who supported the
FSSTND, the predecessor to this standard. If they hadn't demonstrated that the
FSSTND was beneficial, the FHS could never have evolved.

## 7.6. Contributors

> <https://refspecs.linuxfoundation.org/FHS_3.0/fhs/ch07s06.html>
