# Handle (computing)

> <https://en.wikipedia.org/wiki/Handle_(computing)>

## Relevants

- [Network Socket](network_socket.md)
- [Tombstone](tombstone.md)

## Digest

> In computer programming, a handle is an abstract reference to a resource that
> is used when application software references blocks of memory or objects that
> are managed by another system like a database or an operating system.
>
> A resource handle can be an opaque identifier, in which case it is often an
> integer number (often an array index in an array or "table" that is used to
> manage that type of resource), or it can be a pointer that allows access to
> further information.

### Common resource handles

- file descriptors
- network sockets
- database connections
- process identifiers (PIDs)
- job IDs

### Comparison to pointers

- a pointer contains the address of the item to which it refers, a handle is an
  abstraction of a reference which is managed externally
- handle's opacity allows the referent to be relocated in memory by the system
  without invalidating the handle, which is impossible with pointers

### Security

e.g.

if a program wishes to read the system password file (`/etc/passwd`) in
`read/write` mode (O_RDWR), it could try to open the file via the following
call:

> This call asks the operating system to open the specified file with the
> specified access rights.

```c
int fd = open("/etc/passwd", O_RDWR);
```

> file descriptor in Linux is unforgeable because its numerical value alone is
> meaningless, and only in the process context may refer to anything
