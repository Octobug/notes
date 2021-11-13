#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define BUFSIZE 100

static char buf[BUFSIZE]; // buffer for ungetch
static int bufp = 0;      // next free position in buf

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

struct tnode *talloc(void);
char *strdup(char *);

// addtree: add a node with w, at or below p
struct tnode *addtree(struct tnode *p, char *w)
{
    int cond;

    // a new word has arrived
    if (p == NULL)
    {
        // make a new node
        p = talloc();
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    }
    else if ((cond = strcmp(w, p->word)) == 0)
    {
        // repeated word
        p->count++;
    }
    else if (cond < 0)
    {
        // less than into left subtree
        p->left = addtree(p->left, w);
    }
    else
    {
        // greater than into right subtree
        p->right = addtree(p->right, w);
    }
    return p;
}

// treeprint: in-order print of tree p
void treeprint(struct tnode *p)
{
    if (p != NULL)
    {
        treeprint(p->left);
        printf("%4d %s\n", p->count, p->word);
        treeprint(p->right);
    }
}

#include <stdlib.h>

// talloc: make a tnode
struct tnode *talloc(void)
{
    return (struct tnode *)malloc(sizeof(struct tnode));
}

// make a duplicate of s
char *strdup(char *s)
{
    char *p;

    // +1 for '\0'
    p = (char *)malloc(strlen(s) + 1);
    if (p != NULL)
    {
        strcpy(p, s);
    }
    return p;
}
