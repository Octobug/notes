# Chapter 9 Getting help and extending Docker

- [Chapter 9 Getting help and extending Docker](#chapter-9-getting-help-and-extending-docker)
  - [Getting help](#getting-help)
    - [The Docker forums](#the-docker-forums)
    - [Docker on IRC](#docker-on-irc)
    - [Docker on GitHub](#docker-on-github)
  - [Reporting issues for Docker](#reporting-issues-for-docker)
  - [Setting up a build environment](#setting-up-a-build-environment)
    - [Install Docker](#install-docker)
    - [Install source and build tools](#install-source-and-build-tools)
    - [Check out the source](#check-out-the-source)
    - [Contributing to the documentation](#contributing-to-the-documentation)
    - [Build the environment](#build-the-environment)
    - [Running the tests](#running-the-tests)
    - [Use Docker inside our development environment](#use-docker-inside-our-development-environment)
    - [Submitting a pull request](#submitting-a-pull-request)
    - [Merge approval and maintainers](#merge-approval-and-maintainers)
  - [Summary](#summary)

## Getting help

### The Docker forums

> <https://forums.docker.com/>

### Docker on IRC

[Freenode IRC network](https://freenode.net/)

- `#docker`
- `#docker-dev`

### Docker on GitHub

- <https://github.com/moby/moby>
- <https://github.com/distribution/distribution>
- <https://github.com/opencontainers/runc>
- <https://github.com/moby/swarmkit>
- <https://github.com/docker/compose>

## Reporting issues for Docker

## Setting up a build environment

### Install Docker

### Install source and build tools

### Check out the source

### Contributing to the documentation

- <https://github.com/docker/docs>

### Build the environment

```sh
# building the docker environment
make build

# building the docker binary
make binary
```

### Running the tests

```sh
make test
```

This command will create a development image. A container will be launched from
this image, and the test will run inside it.

💡 You can use the `$TESTFLAGS` environment variable to pass in arguments to the
test run.

### Use Docker inside our development environment

```sh
# launching an interactive session
make shell
```

### Submitting a pull request

### Merge approval and maintainers

- `LGTM` (Looks Good To Me)

## Summary
