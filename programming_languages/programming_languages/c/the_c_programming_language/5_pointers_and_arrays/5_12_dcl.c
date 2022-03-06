#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define BUFSIZE 100
#define MAXTOKEN 100

static char buf[BUFSIZE]; // buffer for ungetch
static int bufp = 0;      // next free position in buf

enum
{
    NAME,
    PARENS,
    BRACKETS
};

void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype;           // type of last token
char token[MAXTOKEN];    // last token string
char name[MAXTOKEN];     // identifier name
char datatype[MAXTOKEN]; // data type = char, int, etc.
char out[1000];          // output string

// convert declaration to words
int main()
{

    while (gettoken() != EOF)
    {
        // 1st token on line is the datatype
        strcpy(datatype, token);
        out[0] = '\0';
        dcl(); // parse rest of line
        if (tokentype != '\n')
        {
            printf("syntax error\n");
        }
        printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}

// dcl: parse a declarator
void dcl(void)
{
    int ns;

    for (ns = 0; gettoken() == '*';) // count *'s
    {
        ns++;
    }
    dirdcl();
    while (ns-- > 0)
    {
        strcat(out, " pointer to");
    }
}

// dirdcl: parse a direct declarator
void dirdcl(void)
{
    int type;

    if (tokentype == '(') // ( dcl )
    {
        dcl();
        if (tokentype != ')')
        {
            printf("error: missing )\n");
        }
    }
    else if (tokentype == NAME) // variable name
    {
        strcpy(name, token);
    }
    else
    {
        printf("error: expected name or (dcl)\n");
    }
    while ((type = gettoken()) == PARENS || type == BRACKETS)
    {
        if (type == PARENS)
        {
            strcat(out, " function returning");
        }
        else
        {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
    }
}

// return next token, a token is a name, a pair or parentheses, a pair of
// brackets perhaps including a number, or any other single character.
int gettoken(void)
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    while ((c = getch()) == ' ' || c == '\t')
        ;

    if (c == '(')
    {
        if ((c = getch()) == ')')
        {
            strcpy(token, "()");
            return tokentype = PARENS;
        }
        else
        {
            ungetch(c);
            return tokentype = '(';
        }
    }
    else if (c == '[')
    {
        for (*p++ = c; (*p++ = getch()) != ']';)
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    }
    else if (isalpha(c))
    {
        for (*p++ = c; isalnum(c = getch());)
        {
            *p++ = c;
        }
        *p = '\0';
        ungetch(c);
        return tokentype = NAME;
    }
    else
    {
        return tokentype = c;
    }
}

int getch(void) // get a (possibly pushed back) character
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) // push character back on input
{
    if (bufp >= BUFSIZE)
    {
        printf("ungetch: too many characters\n");
    }
    else
    {
        buf[bufp++] = c;
    }
}

// undcl: convert word description to declaration
void undcl()
{
    int type;
    char temp[MAXTOKEN];

    while (gettoken() != EOF)
    {
        strcpy(out, token);
        while ((type = gettoken()) != '\n')
        {
            if (type == PARENS || type == BRACKETS)
            {
                strcat(out, token);
            }
            else if (type == '*')
            {
                sprintf(temp, "(*%s)", out);
                strcpy(out, temp);
            }
            else if (type == NAME)
            {
                sprintf(temp, "%s %s", token, out);
                strcpy(out, temp);
            }
            else
            {
                printf("invalid input at %s\n", token);
            }
        }
        printf("%s\n", out);
    }
}
