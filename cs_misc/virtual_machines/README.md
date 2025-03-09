# Virtual Machines

## VirtualBox

### Network

`File` -> `Host Network Manager`

#### Host <-> Guest

- Adapter 1: `NAT`
- Adapter 2: `Host-only`

or

- Adapter 1: `Bridged`

#### Ubuntu 24

- `/etc/netplan/50-cloud-init.yaml`
- `sudo netplan apply`

```yaml
network:
  version: 2
  ethernets:
    enp0s8:
      dhcp4: true
    enp0s9:
      dhcp4: true
```
