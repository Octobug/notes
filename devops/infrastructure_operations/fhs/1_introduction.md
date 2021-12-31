# Chapter 1. Introduction

> <https://refspecs.linuxfoundation.org/FHS_3.0/fhs/ch01.html>

## 1.1. Purpose

This standard enables:

- Software to predict the location of installed files and directories, and
- Users to predict the location of installed files and directories.

We do this by:

- Specifying guiding principles for each area of the filesystem,
- Specifying the minimum files and directories required,
- Enumerating exceptions to the principles, and
- Enumerating specific cases where there has been historical conflict.

The FHS document has a limited scope:

- Local placement of local files is a local issue, so FHS does not attempt to
  usurp system administrators.
- FHS addresses issues where file placements need to be coordinated between
  multiple parties such as local sites, distributions, applications,
  documentation, etc.

## 1.2. Conventions

Components of filenames that vary are represented by a description of the
contents enclosed in "<" and ">" characters, `<thus>`. Electronic mail
addresses are also enclosed in "<" and ">" but are shown in the usual typeface.

Optional components of filenames are enclosed in "[" and "]" characters and may
be combined with the "<" and ">" convention. For example, if a filename is
allowed to occur either with or without an extension, it might be represented
by `<filename>[.<extension>]`.

Variable substrings of directory names and filenames are indicated by "*".

The sections of the text marked as Rationale are explanatory and are
non-normative.
