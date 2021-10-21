# Introduction

> <https://docker-curriculum.com/#introduction>

## What is Docker?

> An open-source project that automates the deployment of software applications
> inside containers by providing an additional layer of abstraction and
> automation of OS-level virtualization on Linux.
>
> Wikipedia

The key benefit of Docker is that it allows users to package an application
with all of its dependencies into a standardized unit for software development.

Unlike virtual machines, containers do not have high overhead and hence enable
more efficient usage of the underlying system and resources.

## What are containers?

VMs run applications inside a guest Operating System, which runs on virtual
hardware powered by the server’s host OS.

VMs are great at providing full process isolation for applications: there are
very few ways a problem in the host operating system can affect the software
running in the guest operating system, and vice-versa. But this isolation comes
at great cost — the computational overhead spent virtualizing hardware for a
guest OS to use is substantial.

Containers take a different approach: by leveraging the low-level mechanics of
the host operating system, containers provide most of the isolation of virtual
machines at a fraction of the computing power.

## Why use containers?

Containers offer a logical packaging mechanism in which applications can be
abstracted from the environment in which they actually run. This decoupling
allows container-based applications to be deployed easily and consistently.
This gives developers the ability to create predictable environments that are
isolated from the rest of the applications and can be run anywhere.

From an operations standpoint, apart from portability containers also give more
granular control over resources giving your infrastructure improved efficiency
which can result in better utilization of your compute resources.
