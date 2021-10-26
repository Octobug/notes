# Chapter 3: Control Flow

## 3.1 Statements and Blocks

In C, the semicolon is a statement terminator, rather than a seperator as it is
in languages like Pascal.

## 3.2 If-Else

## 3.3 Else-If

e.g.

```c
/* binserach: find x in v[0] <= v[1] <= ... <= v[n-1] */
int binsearch(int x, in v[], int n)
{
    int low, high, mid;

    low = 0;
    high = n - 1;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (x < v[mid])
            high = mid - 1;
        else if (x > v[mid])
            low = mid + 1;
        else    /* found match */
            return mid;
    }
    return -1;  /* no match */
}
```

## 3.4 Switch

`cases` serve just as **lables**, so execution falls through to the next case.

```c
switch (expression) {
    case const-expr: statements
    case const-expr: statements
    default: statements
}

## 3.5 Loops -- While and For
