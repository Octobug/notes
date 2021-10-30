// qsort: sort v[left]...v[fight] into increasing order
#include <stdio.h>

void swap(int v[], int i, int j)
{
    int temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

void qsort(int v[], int left, int right)
{
    int i, last;

    // do nothing if array contains fewer than two elements
    if (left >= right)
    {
        return;
    }
    // move partition elem to v[left];
    swap(v, left, (left + right) / 2);
    last = left;
    for (i = left + 1; i <= right; i++)
    {
        if (v[i] < v[left])
        {
            swap(v, ++last, i);
            for (int i = 0; i < 5; i++)
            {
                printf("%d ", v[i]);
            }
            printf("\n");
        }
    }
    // restore partition elem
    swap(v, left, last);
    qsort(v, left, last - 1);
    qsort(v, last + 1, right);
}

int main()
{
    int nums[] = {2, 1, 4, 5, 3};
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", nums[i]);
    }
    printf("\n");
    qsort(nums, 0, 4);
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", nums[i]);
    }
}
