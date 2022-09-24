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

>>>>> progress
