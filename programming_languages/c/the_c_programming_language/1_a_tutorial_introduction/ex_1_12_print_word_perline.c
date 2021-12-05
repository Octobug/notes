#include <stdio.h>

int main()
{
    int c;
    int prev_c = 0;

    while ((c = getchar()) != EOF)
    {
        if (c == '\n' || c == ' ' || c == '\t')
        {
            c = '\n';
        }

        if (prev_c != c)
        {
            putchar(c);
        }
        prev_c = c;
    }
    return 0;
}
