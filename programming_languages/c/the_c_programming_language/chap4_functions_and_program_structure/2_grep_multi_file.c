#include <stdio.h>
#include "2_grep_multi_getline.h"
#include "2_grep_multi_strindex.h"

#define MAXLINE 1000 // maximum input line lenght

char pattern[] = "ould"; // pattern to search for

// find all lines matching pattern
int main()
{
    char line[MAXLINE];
    int found = 0;

    while (getline_c(line, MAXLINE) > 0)
    {
        if (strindex(line, pattern) >= 0)
        {
            printf("%s", line);
            found++;
        }
    }
    return found;
}
