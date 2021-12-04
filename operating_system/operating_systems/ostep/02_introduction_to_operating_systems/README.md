# 2. Introduction to Operating Systems

Virtualization: how to virtualize resources

## 2.1 Virtualizing The CPU

```c
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: cpu <string>\n");
        exit(1);
    }
    char *str = argv[1];

    while (1)
    {
        printf("%s\n", str);
        Spin(1);s
    }
    return 0;
}
```

Run many different instances of this same program at the same time:

```sh
./cpu A & ; ./cpu B & ; ./cpu C & ; ./cpu D &
```

Using `&` runs a job in the background in shell.

Turning a single CPU (or small set of them) into a seemingly infinite number of
CPUs and thus allowing many programs to seemingly run at once is what we call
virtualizing the CPU。

## 2.2 Virtualizing Memory

```c
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include "common.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "usage: mem <value>\n");
        exit(1);
    }
    int *p;
    p = malloc(sizeof(int));
    assert(p != NULL);
    printf("(%d) addr pointed to by p: %p\n", (int)getpid(), p);
    *p = atoi(argv[1]); // assign value to addr stored in p
    while (1)
    {
        Spin(1);
        *p = *p + 1;
        printf("(%d) value of p: %d\n", getpid(), *p);
    }
    return 0;
}
```
