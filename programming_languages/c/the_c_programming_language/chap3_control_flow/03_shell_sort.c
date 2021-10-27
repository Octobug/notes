#include <stdio.h>

// shellsort: sort v[0]...v[n-1] into increasing order
void shellsort(int v[], int n)
{
    int gap, i, j, temp;

    // shrink the gap
    for (gap = n / 2; gap > 0; gap /= 2)
    {
        // steps along the elements
        for (i = gap; i < n; i++)
        {
            // compare same gap elems
            for (j = i - gap; j >= 0 && v[j] > v[j + gap]; j -= gap)
            {
                temp = v[j];
                v[j] = v[j + gap];
                v[j + gap] = temp;
            }
        }
    }
}

int main()
{
    int arr[10] = {3, 1, 2, 0, 4, 5, 6, 7, 8, 9};
    shellsort(arr, 10);
    printf("digits =");
    for (int i = 0; i < 10; i++)
        printf(" %d", arr[i]);
    return 0;
}
