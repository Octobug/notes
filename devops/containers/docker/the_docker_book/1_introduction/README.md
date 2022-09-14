# Chapter 1 Introduction

- [Chapter 1 Introduction](#chapter-1-introduction)
  - [Introducing Docker](#introducing-docker)
    - [An easy and lightweight way to model reality](#an-easy-and-lightweight-way-to-model-reality)
    - [A logical segregation of duties](#a-logical-segregation-of-duties)

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

>>>>> progress
