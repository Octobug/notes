# Chapter 1 Introduction

- [Chapter 1 Introduction](#chapter-1-introduction)
  - [Introducing Docker](#introducing-docker)
    - [An easy and lightweight way to model reality](#an-easy-and-lightweight-way-to-model-reality)
    - [A logical segregation of duties](#a-logical-segregation-of-duties)
    - [Fast, efficient development life cycle](#fast-efficient-development-life-cycle)
    - [Encourages service oriented architecture](#encourages-service-oriented-architecture)
  - [Docker components](#docker-components)
    - [Docker client and server](#docker-client-and-server)
    - [Docker images](#docker-images)
    - [Registries](#registries)
    - [Containers](#containers)
    - [Compose, Swarm and Kubernetes](#compose-swarm-and-kubernetes)
  - [Docker with configuration management](#docker-with-configuration-management)
  - [Docker's technical components](#dockers-technical-components)

Containers run in **user** space on top of an operating system's kernel.

Container virtualization is often called operating system-level virtualization.

Containers have also been seen as less secure than the full isolation of
hypervisor virtualization.

Conntainers could be used as process isolation environments. A container is a
chroot jail, which creates an isolated directory environment for running
processes. If attackers breach the running progress in the jail, then find
themselves trapped in this ennvironment and unable to further compromise a host.

Docker has modern Linux kernel features, such as control groups and namespaces.
This means that containers can have strong isolation, their own network and
storage stacks, as well as resource management capabilities to allow friendly
co-existence of multiple containers on a host.

Containers are considered a lean technology because they do not require an
emulation layer or a hypervisor layer to run and instead use the operating
system's normal system call interface.

## Introducing Docker

### An easy and lightweight way to model reality

Docker relies on a copy-on-write model so that making changes to your
application is also incredibly fast: **only what you want to change gets
changed**.

### A logical segregation of duties

- Developers care about their applications running inside containers.
- Operations care about managing the containers.

### Fast, efficient development life cycle

### Encourages service oriented architecture

Docker recommends that each container run a single application or process. This
promotes a distributed application model where an application or service is
represented by a series of inter-connected containers.

📢 Running a multi-process application inside a single conntainer is also
acceptable.

## Docker components

Docker Community Edition (Docker CE) consists of:

- The Docker client and server, also called the Docker Engine.
- Docker Images
- Registries
- Docker Containers

### Docker client and server

Docker is a client-server application. Docker ships with a command line client
binary `docker`, as well as a full RESTful API to interact with the daemon:
`dockerd`.

### Docker images

Images have a layered format, using Union file systems.

### Registries

Docker stores images in registries. Two types of registries:

- public
- private

### Containers

A Docker container is:

- An image format.
- A set of standard operations.
- An execution environment.

### Compose, Swarm and Kubernetes

- Docker Compose: allows you to run stacks of conntainers to represent
  application stacks.
- Docker Swarm: allows you to create clusters of containers, called swarms,
  that allow you to run scalable workloads.
- Kubernetes: Docker provides the primary underlying compute layer in the
  orchestration tool Kubernetes.

## Docker with configuration management

Compared to traditional image models, Docker is a lot more lightweight: images
are layered, and you can quickly iterate on them.

With short-lived, immutable, disposable, and service-oriented, you are rarely
concerned with long-term management of state, entropy is less of a concern
because containers rarely live long enough for it to be, and the recreation of
state may often be cheaper than the remediation of state.

With the need to manage docker itself, both Docker and configuration management
tools are likely to be deployed in the majority of organization.

## Docker's technical components

>>>>> progress
