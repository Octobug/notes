# Chapter 2 Installing Docker

- [Chapter 2 Installing Docker](#chapter-2-installing-docker)
  - [Installing on Ubuntu and Debian](#installing-on-ubuntu-and-debian)
    - [Checking for prerequisites](#checking-for-prerequisites)
      - [Kernel](#kernel)
    - [Installing Docker](#installing-docker)

💡 Tips: Docker for Mac and Docker for Windows are a collection of components.
It includes a tiny **virtual machine** shipped with a **wrapper script** to
manage it. The virtual machine runs the daemonn and provides a local Docker
daemon on OS X and Microsoft Windows. The Docker client binary, `docker`, is
installed natively on these platforms and connected to the Docker daemon running
in the virtual machine.

💡 Tips: Using `Puppet` and `Chef` to install Docker are recommended rather than
using a manual process.

## Installing on Ubuntu and Debian

### Checking for prerequisites

#### Kernel

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

### Installing Docker

>>>>> progress
