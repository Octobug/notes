# Chapter 8 Using the Docker API

- [Chapter 8 Using the Docker API](#chapter-8-using-the-docker-api)
  - [The Docker APIs](#the-docker-apis)
  - [First steps with the Engine API](#first-steps-with-the-engine-api)
  - [Testing the Docker Engine API](#testing-the-docker-engine-api)
    - [Managing images with the API](#managing-images-with-the-api)
    - [Managing containers with the API](#managing-containers-with-the-api)
  - [Improving the TProv Application](#improving-the-tprov-application)
  - [Authenticating the Docker Engine API](#authenticating-the-docker-engine-api)
    - [Create a Certificate Authority](#create-a-certificate-authority)
    - [Create a server certificate signing request and key](#create-a-server-certificate-signing-request-and-key)
    - [Configuring the Docker daemon](#configuring-the-docker-daemon)
    - [Creating a client certificate and key](#creating-a-client-certificate-and-key)
    - [Configuring our Docker client for authentication](#configuring-our-docker-client-for-authentication)

## The Docker APIs

Three specific APIs in the Docker ecosystem:

- The [Registry API](https://docs.docker.com/registry/): privides integration
  with the Docker registry.
- The Docker Hub API: provides integration with the Docker Hub
- The [Docker Engine API](https://docs.docker.com/engine/api/): provides
  integration with the Docker daemon.

All APIs are RESTful.

## First steps with the Engine API

By default, the Docker daemon binds to a socket, `unix:///var/run/docker.sock`.
The daemon runs with `root` privileges so as to have the access needed to manage
the appropriate resources. If a group named `docker` exists on your system,
Docker will apply ownership of the socket to that group. Hence, any user that
belongs to the `docker` group can run Docker without needing `root` privileges.

⚠️ Although the `docker` group makes life easier, it is still a security
exposure. The `docker` group is `root`-equivalent and should be limited to those
users and applications that absolutely need it.

This works fine if we're querying the API from the same host running Docker, but
if we want remote access to the API, we need to bind the Docker daemon to a
network interface. This is done by passing or adjusting the `-H` flag to the
Docker daemon.

Use the Docker API locally:

```sh
curl --unix-socket /var/run/docker.sock http://docker/info 
```

Bind the Docker daemon to a network interface by editing the daemon's startup
configuration files:

- For Ubuntu or Debian
  - Older releases: `/etc/default/docker`
  - Releases with upstart: `/etc/init/docker.conf`
  - Systemd releases: `/lib/systemd/system/docker.service`
- For Red Hat, Fedora and related: `/etc/sysconfig/docker`
  - Systemd releases: `/usr/lib/systemd/system/docker.service`

Bind the Docker daemon to a network interface on a Red Hat derivative running
systemd: `/usr/lib/systemd/system/docker.service`

Change

```service
ExecStart=/usr/bin/dockerd --selinux-enabled
```

to

```service
# not safe for now, better to enable auth
ExecStart=/usr/bin/dockerd --selinux-enabled -H tcp://0.0.0.0:2375
```

```sh
# Connect to the Docker daemon from a remote host
docker -H docker.example.com:2375 info

# Docker also uses the DOCKER_HOST env var
export DOCKER_HOST="tcp://docker.example.com:2375"
```

## Testing the Docker Engine API

```sh
curl http://docker/example.com:2375/info | python -mjson.tool
```

### Managing images with the API

```sh
curl http://docker/example.com:2375/images/json | python -mjson.tool

# local
curl --unix-socket /var/run/docker.sock http://docker/images/json | python -mjson.tool

curl --unix-socket /var/run/docker.sock http://docker/images/431bd73d5c59098602a2fecd84c4bcddc90b4b15676a4a68e3cb42a0924f3e5f/json | python -mjson.tool

# search for images on the Docker Hub
curl --unix-socket /var/run/docker.sock "http://docker/images/search?term=octobug/" | python -mjson.tool
```

### Managing containers with the API

List containers:

```sh
curl -s --unix-socket /var/run/docker.sock "http://docker/containers/json" | python -mjson.tool

curl -s --unix-socket /var/run/docker.sock "http://docker/containers/json?all=1" | python -mjson.tool
```

Create a container:

```sh
curl --unix-socket /var/run/docker.sock "http://docker/containers/create" \
  -X POST -H "Content-Type: application/json" \
  -d '{"Image":"redis", "Hostname":"redis"}' \
  | python -mjson.tool
```

Start a container:

```sh
curl --unix-socket /var/run/docker.sock \
  "http://docker/containers/c6771ad93b0dec17edf600f1e3f7aac85613e806b4a8078cfcb28e65f117b6ac/start" \
  -X POST -H "Content-Type: application/json" \
  | python -mjson.tool

curl --unix-socket /var/run/docker.sock \
  "http://docker/containers/c6771ad93b0dec17edf600f1e3f7aac85613e806b4a8078cfcb28e65f117b6ac/json" \
  | python -mjson.tool
```

## Improving the TProv Application

Just use the SDKs provided by Docker.

## Authenticating the Docker Engine API

💡 By turning the authentication on, you need to configure your Docker client to
support TLS authentication.

- Using a full PKI infrastructure
- creating our own Certicifate Authority
  - ⚠️ This relies on a local CA running on your Docker host. This is not as
    secure as using a full-fledged CA.
- using an existing CA

### Create a Certificate Authority

```sh
which openssl
# /usr/bin/openssl

mkdir -p ~/dev/docker
cd ~/dev/docker
```

```sh
# Generating a private key
# 每当 CA 签发一个证书时，它会自动递增序列号并将其写入 cs.srl 文件
echo 01 | sudo tee ca.srl
sudo openssl genrsa -des3 -out ca-key.pem
# ca-key.pem is the CA key
```

```sh
# Creating a CA certificate
sudo openssl req -new -x509 -days 365 -key ca-key.pem -out ca.pem
# This creates a `ca.pem` file that is the certificate for our CA
```

### Create a server certificate signing request and key

```sh
# Creating a server key, the server is the place where the Docker daemon is in
sudo openssl genrsa -des3 -out server-key.pem
```

```sh
# Creating our server CSR: certificate signing request
sudo openssl req -new -key server-key.pem -out server.csr
```

This is the request that our CA will sign to create our server certificate.
The most important option here is ***Common Name*** or ***CN***. This should
either be the FQDN (fully qualified domain name) of the Docker server (i.e. what
is resolved to in DNS; for example, `docker.example.com`) or `*`, which will
allow us to use the server certificate on any server.

```sh
# Connect via IP address, x.x.x.x is the IP of the Docker daemon
echo "subjectAltName = IP:x.x.x.x,IP:127.0.0.1" > extfile.cnf
```

```sh
# Signing our CSR & create the server certificate
sudo openssl x509 -req -days 365 -in server.csr -CA ca.pem \
  -CAkey ca-key.pem -out server-cert.pem -extfile extfile.cnf
```

We can't enter the passphrase when the Docker daemon starts, so we need to
remove it from the server key.

```sh
# Removing the passphrase from the server key
sudo openssl rsa -in server-key.pem -out server-key.pem
```

```sh
# Securing the key and certificate on the Docker server
# actual path: /etc/docker/server-key.pem
sudo chmod 0600 ~/dev/docker/server-key.pem ~/dev/docker/server-cert.pem \
  ~/dev/docker/ca-key.pem ~/dev/docker/ca.pem
```

### Configuring the Docker daemon

```service
# Enabling Docker TLS on systemd
# RedHat: /usr/lib/systemd/system/docker.service
ExecStart=/usr/bin/docker -d -H tcp://0.0.0.0:2376 --tlsverify --tlscacert=/etc/docker/ca.pem --tlscert=/etc/docker/server-cert.pem --tlskey=/etc/docker/server-key.pem
```

📝 This `2376` is the default TLS/SSL port for Docker. You should only use
`2375` for unauthenticated connections.

💡 You can use the `--tls` flag to enable TLS, but not client-side
authentication.

```sh
sudo systemctl --system doaemon-reload
```

### Creating a client certificate and key

Now we need to create and sign a certificate and key to secure our Docker
client.

```sh
# Creating a client key
sudo openssl genrsa -des3 -out client-key.pem
```

```sh
# Creating a client CSR
sudo openssl req -new -key client-key.pem -out client.csr
```

```sh
# Adding Client Authentication attributes
echo extendedKeyUsage = clientAuth > client-extfile.cnf
```

```sh
# Signing our client CSR
sudo openssl x509 -req -days 365 -in client.csr -CA ca.pem \
  -CAkey ca-key.pem -out client-cert.pem -extfile client-extfile.cnf
```

```sh
# Stripping out the client key pass phrase
# to allow us to use it with the Docker client
sudo openssl rsa -in client-key.pem -out client-key.pem
```

```sh
tree
.
├── ca-key.pem
├── ca.pem
├── ca.srl
├── client-cert.pem
├── client-extfile.cnf
├── client-key.pem
├── client.csr
├── extfile.cnf
├── server-cert.pem
├── server-key.pem
└── server.csr
```

### Configuring our Docker client for authentication

We need to copy the `ca.pem`, `client-cert.pem`, and `client-key.pem` files to
the host on which we're intending to run the Docker client.

💡 These keys provide root-level access to the Docker daemon. You should protect
them carefully.

The `~/.docker` directory is the default location where Docker will look for
certificates and keys. Docker will specifically look for `key.pem`, `cert.pem`,
and `ca.pem`.

```sh
# Copying the key and certificate on the Docker client
mkdir -p ~/.docker/
cp ca.pem ~/.docker/ca.pem
cp client-key.pem ~/.docker/key.pem
cp client-cert.pem ~/.docker/cert.pem
chmod 0600 ~/.docker/key.pem ~/.docker/cert.pem
```

```sh
# Testing our TLS-authenticated connection
sudo docker -H=docker.example.com:2376 --tlsverify info
```

We could instead specify the host using the `DOCKER_HOST` environment variable
if we didn't want to specify the `-H` flag each time. The `--tlsverify` flag
enables our TLS connection to the Docker daemon. Docker automatically looks up
the certificate and key files. If we need to specify them, we could use the
`--tlscacert`, `--tlscert`, and `--tlskey` flags.
