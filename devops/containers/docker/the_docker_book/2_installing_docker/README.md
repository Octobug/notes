# Chapter 2 Installing Docker

- [Chapter 2 Installing Docker](#chapter-2-installing-docker)
  - [Installing on Ubuntu and Debian](#installing-on-ubuntu-and-debian)
    - [Checking for prerequisites (Ubuntu)](#checking-for-prerequisites-ubuntu)
      - [Kernel (Ubuntu)](#kernel-ubuntu)
    - [Installing Docker (Ubuntu)](#installing-docker-ubuntu)
    - [Docker and UFW](#docker-and-ufw)
  - [Installing on Red Hat and family](#installing-on-red-hat-and-family)
    - [Installing Docker (Red Hat)](#installing-docker-red-hat)
      - [Installing on Red Hat Enterprise Linux 6 and CentOS 6](#installing-on-red-hat-enterprise-linux-6-and-centos-6)
      - [Installing on Red Hat Enterprise Linux 7](#installing-on-red-hat-enterprise-linux-7)
      - [Installing on Fedora](#installing-on-fedora)
    - [Starting the Docker daemon on the Red Hat family](#starting-the-docker-daemon-on-the-red-hat-family)
  - [Docker for Mac](#docker-for-mac)
  - [Docker for Windows installtion](#docker-for-windows-installtion)
  - [Using Docker on OSX and Windows with this book](#using-docker-on-osx-and-windows-with-this-book)
  - [Docker installation script](#docker-installation-script)
  - [The Docker daemon](#the-docker-daemon)
    - [Configuring the Docker daemon](#configuring-the-docker-daemon)
    - [Checking that the Docker daemon is running](#checking-that-the-docker-daemon-is-running)

💡 Tips: Docker for Mac and Docker for Windows are a collection of components.
It includes a tiny **virtual machine** shipped with a **wrapper script** to
manage it. The virtual machine runs the daemonn and provides a local Docker
daemon on OS X and Microsoft Windows. The Docker client binary, `docker`, is
installed natively on these platforms and connected to the Docker daemon running
in the virtual machine.

💡 Tips: Using `Puppet` and `Chef` to install Docker are recommended rather than
using a manual process.

## Installing on Ubuntu and Debian

### Checking for prerequisites (Ubuntu)

#### Kernel (Ubuntu)

```sh
uname -a
```

- `aufs`
  - `linux-image-extra`, `linux-image-extra-virtual`

    ```sh
    sudo apt-get install linux-image-extra-$(uname -r) linux-image-extra-virtual
    ```

For earlier Ubuntu, we need to upgrade Ubuntu to the later kernel:

```sh
sudo apt-get update
sudo apt-get install linux-headers-3.16.0-34-generic \
  linux-image-3.16.0-34-generic linux-headers-3.16.0-34
sudo update-grub
sudo reboot
```

### Installing Docker (Ubuntu)

```sh
# Adding prerequisite Ubuntu packages
sudo apt-get install \
  apt-transport-https \
  ca-certificates \
  curl \
  software-properties-common

# Adding the Docker GPG key
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -

# Adding the Docker APT repository
sudo add-apt-repository \
  "deb [arch=amd64] https://download.docker.com/linux/ubuntu \
  $(lsb_release -cs) \
  stable"

# Updating APT source
sudo apt-get update

# Installing the Docker packages on Ubuntus
sudo apt-get install docker-ce

# Checking Docker is installed on Ubuntu
sudo docker info
```

### Docker and UFW

Docker uses a network bridge to manage the networking on your containers. By
default, UFW drops all forwarded packets. You'll need to enable forwarding in
UFW for Docker to function correctly. We can do this by editing the
`/etc/default/ufw` file.

Old UFW forwarding policy:

```ini
DEFAULT_FORWARD_POLICY="DROP"
```

New UFW forwarding policy:

```ini
DEFAULT_FORWARD_POLICY="ACCEPT"
```

Reload the UFW firewall:

```sh
sudo ufw reload
```

## Installing on Red Hat and family

### Installing Docker (Red Hat)

#### Installing on Red Hat Enterprise Linux 6 and CentOS 6

```sh
# Installing EPEL on Red Hat Enterprise Linux 6 and CentOS 6
sudo rpm -Uvh \
  http://download.fedoraproject.prg/pub/epel/6/i386/epel-release-6-8.noarch.rpm

# Installing the Docker package on Red Hat Enterprise Linux 6 and CentOS 6
sudo yum -y install docker-io
```

#### Installing on Red Hat Enterprise Linux 7

```sh
# You'll need to be a Red Hat customer
sudo subscription-manager repos --enable=rhel-7-server-extras-rpms
sudo yum install -y docker
```

#### Installing on Fedora

```sh
# Installing the Docker package on Fedora 19
sudo yum -y install docker-io

# Installing the Docker package on Fedora 20
sudo yum -y install docker

# Installing the Docker package on Fedora 21
sudo yum -y install docker-io

# Installing the Docker package on Fedora 22
sudo dnf install docker
```

### Starting the Docker daemon on the Red Hat family

```sh
# Starting the Docker daemon on Red Hat Enterprise Linux 6
sudo service docker start

# Ensuring the Docker daemon starts at boot on Red Hat Enterprise Linux 6
sudo service docker enable

# Starting the Docker daemon on Red Hat Enterprise Linux 7
sudo systemctl start docker

# Ensuring the Docker daemon starts at boot on Red Hat Enterprise Linux 7
sudo systemctl enable docker
```

## Docker for Mac

Docker for Mac ships with a variety of components:

- Hyperkit.
- The Docker client and server.
- Docker Compose.
- Docker Machine - Which helps you create Docker hosts.
- Kitematic - is a GUI that helps you run Docker locally and interact with the
  Docker Hub.

## Docker for Windows installtion

Docker for Windows ships with a variety of components:

- The Docker client and server.
- Docker Compose.
- Docker Machine - Which helps you create Docker hosts.
- Kitematic - is a GUI that helps you run Docker locally and interact with the
  Docker Hub.

Docker for Windows requires Microsoft Hyper-V.

## Using Docker on OSX and Windows with this book

📢 On Windows: You can't mount a local directory on host into the Docker host
running in the Docker virtual machine because they don't share a file system.

## Docker installation script

```sh
curl https://get.docker.com/ | sudo sh
```

## The Docker daemon

Docker runs as a `root`-privileged daemon process to allow it to handle
operations that can't be executed by normal users. The `docker` binary runs as a
client of this daemon and also requires `root` privileges to run.

By default, the daemon listens on a Unix socket at `/var/run/docker.sock` for
incoming Docker requests. If a group named `docker` exists on our system, Docker
will apply ownership of the socket to that group. Hence, any use that belongs to
the `docker` group can run Docker without needing to use the `sudo` command.

⚠️ Remember that although the `docker` group makes life easier, it is still a
security exposure. The `docker` group is `root`-equivalent and should be limited
to those users and applications who absolutely need it.

### Configuring the Docker daemon

```sh
# server daemon
sudo dockerd -H tcp://0.0.0.0:2375
# client
docker -H :2375
# use env var
export DOCKER_HOST="tcp://0.0.0.0:2375"

# or use Unix socket
sudo dockerd -H unix:///home/docker.sock
# multiple bindings
sudo dockerd -H tcp://0.0.0.0:2375 -H unix:///home/docker.sock
```

⚠️ By default, Docker client-server communication is not authenticated. If you
bind Docker to an exposed network interface, anyone can connect to the daemon.

📢 If you're running Docker behind a proxy or corporate firewall you can also
use the `HTTPS_PROXY`, `HTTP_PROXY`, `NO_PROXY` options to control how the
daemon connects.

To make these changes permanent:

- On SystemV-enabled Ubuntu and Debian releases: editing the
  `/etc/default/docker` file and changing the `DOCKER_OPTS` variable.
- On Systemd-enabled distributions: add on override file at
  `/etc/systemd/system/docker.service.d/override.conf`:

  ```ini
  [Service]
  ExecStart=
  ExecStart=/usr/bin/dockerd -H ...
  ```

### Checking that the Docker daemon is running

```sh
# On Ubuntu
sudo status docker
sudo stop docker
sudo start docker

# On systemd-enabled linux
sudo service docker stop
sudo service docker start
```
