#include <stdio.h>
#include "3_atof.h"
#include "2_grep_multi_getline.h"

#define MAXLINE 100

// rudimentary calculator
int main()
{
    double sum;
    char line[MAXLINE];

    sum = 0;
    while (getline_c(line, MAXLINE) > 0)
    {
        // %g 自动处理数字
        printf("\t%g\n", sum += atof(line));
    }
    return 0;
}
