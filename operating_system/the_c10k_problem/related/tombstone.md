# Tombstone (programming)

> <https://en.wikipedia.org/wiki/Tombstone_(programming)>

## Relevants

- [Dangling pointer](dangling_pointer.md)
- [Handle](handle.md)

## Digest

> A tombstone is a structure that acts as an intermediary between a pointer and
> the heap-dynamic data in memory.
>
> The pointer – sometimes called the handle – points only at tombstones and
> never to the memory that holds the actual value.
>
> When the data is deallocated, the tombstone is set to a null (or, more
> generally, to a value that is illegal for a pointer in the given runtime
> environment), indicating that the variable no longer exists.
>
> This prevents the use of invalid pointers, which would otherwise access the
> memory area that once belonged to the now deallocated variable, although it
> may already contain other data, in turn leading to corruption of in-memory
> data.

### More general

> In more generalized terms, a tombstone can be understood as a marker for
> "this data is no longer here". For example, in filesystems it may be
> efficient when deleting files to mark them as "dead" instead of immediately
> reclaiming all their data blocks

### Downsides

> The downsides of using tombstones include a computational overhead and
> additional memory consumption: extra processing is necessary to follow the
> path from the pointer to data through the tombstone, and extra memory is
> necessary to retain tombstones for every pointer throughout the program. One
> other problem is that all the code that needs to work with the pointers in
> question needs to be implemented to use the tombstone mechanism.

### Status Quo

> No popular programming language currently uses tombstones. However, built–in
> support by the programming language or the compiler is not necessary to use
> them.
