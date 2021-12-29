#!/bin/sh

# Install EPEL repo.
yum install -y epel-release

# Import Remi GPG key.
wget https://rpms.remirepo.net/RPM-GPG-KEY-remi \
  -O /etc/pki/rpm-gpg/RPM-GPG-KEY-remi
rpm --import /etc/pki/rpm-gpg/RPM-GPG-KEY-remi

# Install Remi repo.
rpm -Uvh --quiet \
  https://rpms.remirepo.net/enterprise/remi-release-7.rpm

# Install Node.js (npm plus all its dependencies)
yum --enablerepo=epel -y install npm
