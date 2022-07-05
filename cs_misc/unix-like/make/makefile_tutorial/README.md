# Makefile Tutorial

> <https://makefiletutorial.com/>

## Getting Started

### Why do Makefiles exist?

Makefiles are used to help decide which parts of a large program need to be
recompiled.

Here's an example dependency graph that you might build with Make. If any
file's dependencies changes, then the file will get recompiled:

![Dependency Graph](images/dependency_graph.png)

### What alternatives are there to Make?

Popular C/C++ alternative build systems are [SCons](https://scons.org/),
[CMake](https://cmake.org/), [Bazel](https://bazel.build/), and
[Ninja](https://ninja-build.org/). Some code editors like
[Microsoft Visual Studio](https://visualstudio.microsoft.com/) have their own
built in build tools. For Java, there's [Ant](https://ant.apache.org/),
[Maven](https://maven.apache.org/what-is-maven.html), and
[Gradle](https://gradle.org/). Other languages like Go and Rust have their own
build tools.

### The versions and types of Make

GNU Make is the standard implementation on Linux and MacOS. 

### Running the Examples

run `make`

### Makefile Syntax

A Makefile consists of a set of rules. A rule generally looks like this:

```makefile
targets: prerequisites (or dependencies)
   command
   command
   command
```

- The `targets` are file names, separated by spaces.
- The `commands` are a series of steps typically used to make the target(s).
  These need to start with a tab character, not spaces.
- The `prerequisites` are also file names, separated by spaces. These files
  need to exist before the commands for the target are run.
  
### Beginner Examples

```makefile
blah: blah.o
    cc blah.o -o blah # Runs third

blah.o: blah.c
    cc -c blah.c -o blah.o # Runs second

blah.c:
    echo "int main() { return 0; }" > blah.c # Runs first
```

The above Makefile has three separate `rules`. When you run `make blah` in the
terminal, it will build a program called `blah` in a series of steps:

- Make is given `blah` as the target, so it first searches for this target
- `blah` requires `blah.o`, so make searches for the `blah.o` target
- `blah.o` requires `blah.c`, so make searches for the `blah.c` target
- `blah.c` has no dependencies, so the `echo` command is run
- The `cc -c` command is then run, because all of the `blah.o` dependencies are
  finished
- The top `cc` command is run, because all the `blah` dependencies are finished
- That's it: `blah` is a compiled c program

```makefile
some_file:
    echo "This line will always print"
```

This makefile has a single target, called `some_file`. The default target is
the first target, so in this case `some_file` will run.

```makefile
some_file:
    echo "This line will only print once"
    touch some_file
```

This file will make `some_file` the first time, and the second time notice it's
already made, resulting in `make: 'some_file' is up to date.`

```makefile
some_file: other_file
    echo "This will run second, because it depends on other_file"
    touch some_file

other_file:
    echo "This will run first"
    touch other_file
```

Here, the target `some_file` "depends" on `other_file`. When we run `make`, the
default target `some_file` will get called. It will first look at its list of
*dependencies*, and if any of them are older, it will first run the targets for
those dependencies, and then run itself. The second time this is run, neither
target will run because both targets exist.

```makefile
some_file: other_file
    touch some_file

other_file:
    echo "nothing"
```

This will always run both targets, because `some_file` depends on `other_file`,
which is never created.

```makefile
some_file: 
    touch some_file

clean:
    rm -f some_file
```

`clean` is often used as a target that removes the output of other targets, but
it is not a special word in `make`.

### Variables

Variables can only be strings:

```makefile
files = file1 file2
some_file: $(files)
    echo "Look at this variable: " $(files)
    touch some_file

file1:
    touch file1
file2:
    touch file2

clean:
    rm -f file1 file2 some_file
```

Reference variables using `${}` or `$()`

```makefile
x = dude

all:
    echo $(x)
    echo ${x}

    # Bad practice, but works
    echo $x
```

## Targets

## Automatic Variables and Wildcards

## Fancy Rules

## Commands and execution

## Variables Pt. 2

## Conditional part of Makefiles

## Functions

## Other Features

## Makefile Cookbook
