#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
struct tnode *addtree(struct tnode *, char *);
void treeprint(struct tnode *);
int getword(char *, int);

// the tree node
struct tnode
{
    char *word;          // points to the text
    int count;           // number of occurrences
    struct tnode *left;  // left child
    struct tnode *right; // right child
};

// word frequency count
int main()
{
    struct tnode *root;
    char word[MAXWORD];

    root = NULL;
    while (getword(word, MAXWORD) != EOF)
    {
        if (isalpha(word[0]))
        {
            root = addtree(root, word);
        }
    }
    treeprint(root);
    return 0;
}

// getword: get next word of character from input
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;
    if (c != EOF)
    {
        *w++ = c;
    }
    if (!isalpha(c))
    {
        // EOF or other non-alpha chars
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++)
    {
        // is not alpha or number
        if (!isalnum(*w = getch()))
        {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}
