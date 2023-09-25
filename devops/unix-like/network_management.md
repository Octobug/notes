# Network Management

- [Network Management](#network-management)
  - [网络设置（手动设置与 DHCP）](#网络设置手动设置与-dhcp)
  - [CA 证书管理](#ca-证书管理)

## 网络设置（手动设置与 DHCP）

- 手动设置固定 IP
  - 重要参数
    - IP
    - netmask (子网掩码)
    - gateway (网关)
    - DNS 主机 IP
  - 常见网卡名称: `ifconfig -a`
    - eno1: 主板内置网卡
    - ens1: 主板内置的 PCI-E 接口网卡
    - enp2s0: PCI-E 接口的独立网卡，可能有多个接口，s0, s1 ...
    - eth0: 默认网卡
  - 设置命令：`nmcli`
- DHCP
- 修改主机名称：hostnamectl

## CA 证书管理

- Debian
  - `dpkg-reconfigure ca-certificates`
  - `/etc/ca-certificates.conf`
    - `update-ca-certificates`
