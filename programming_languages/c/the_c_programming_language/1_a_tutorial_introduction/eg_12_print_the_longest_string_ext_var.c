#include <stdio.h>
#define MAXLINE 1000 /* maximum input line size */

int max;               /* maximum length seen so far */
char line[MAXLINE];    /* current input line */
char longest[MAXLINE]; /* longest line saved here */

// ! external variables abuse is not recommended !

int getline(void);
void copy(void);

/* print longest input line */
int main()
{
    int len;               /* current line length; specialized version */
    extern int max;        // can be omitted
    extern char longest[]; // can be omitted

    max = 0;
    while ((len = getline()) > 0)
    {
        if (len > max)
        {
            max = len;
            copy();
        }
    }
    if (max > 0) /* there was a line */
    {
        printf("%s", longest);
    }
    return 0;
}

/* getline: specialized version */
int getline(void)
{
    int c, i;
    extern char line[]; // can be omitted

    for (i = 0; i < MAXLINE - 1 && (c = getchar()) != EOF && c != '\n'; ++i)
    {
        line[i] = c;
    }
    if (c == '\n')
    {
        line[i] = c;
        ++i;
    }
    line[i] = '\0';
    return i;
}

/* copy: specialized version */
void copy(void)
{
    int i;
    extern char line[], longest[]; // can be omitted

    i = 0;
    while ((longest[i] = line[i]) != '\0')
    {
        ++i;
    }
}
