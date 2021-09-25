# Dangling pointer

> <https://en.wikipedia.org/wiki/Dangling_pointer>

## Digest

### Cause of dangling pointers

#### by scope

```c
{
  char *dp = NULL;
  /* ... */
  {
    char c;
    dp = &c;
  }
  /* c falls out of scope */
  /* dp is now a dangling pointer */
}
```

#### by malloc & free

```c
#include <stdlib.h>

void func()
{
  char *dp = malloc(A_CONST);
  /* ... */
  free(dp);  /* dp now becomes a dangling pointer */
  dp = NULL; /* dp is no longer dangling */
             /* ... */
}
```

#### by stack-allocated local variable

```c
int *func(void)
{
  int num = 1234;
  /* ... */
  return &num;
}
```

### Cause of wild pointers

#### by jumping over the initialization

```c
int f(int i)
{
  char *dp;         /* dp is a wild pointer */
  static char *scp; /* scp is not a wild pointer:
                     * static variables are initialized to 0
                     * at start and retain their values from
                     * the last call afterwards.
                     * Using this feature may be considered bad
                     * style if not commented */
}
```

### Avoiding dangling pointer errors

> ⚠️ technique below will not clear other pointer variables which may contain a
> copy of the pointer.

```c
#include <assert.h>
#include <stdlib.h>

/* Alternative version for 'free()' */
void safefree(void **pp)
{
  /* in debug mode, abort if pp is NULL */
  assert(pp);
  if (pp != NULL)
  {             /* safety check */
    free(*pp);  /* deallocate chunk, note that free(NULL) is valid */
    *pp = NULL; /* reset original pointer */
  }
}

int f(int i)
{
  char *p = NULL, *p2;
  p = malloc(1000); /* get a chunk */
  p2 = p;           /* copy the pointer */
  /* use the chunk here */
  /* (void **)&p turns &p to a void pointer of pointer 
    so that safefree() could receive any address of any types */
  safefree((void **)&p); /* safety freeing; does not affect p2 variable */
  safefree((void **)&p); /* this second call won't fail */
  char c = *p2;          /* p2 is still a dangling pointer, so this is
                            undefined behavior. */
  return i + c;
}

/* guarantee the validity of an empty pointer before calling malloc() */
safefree(&p);        /* i'm not sure if chunk has been released */
p = malloc(1000);    /* allocate now */
```
