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
    - [What can you use Docker for?](#what-can-you-use-docker-for)

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

### What can you use Docker for?

>>>>> progress
