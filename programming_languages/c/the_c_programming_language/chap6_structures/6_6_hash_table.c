
// table entry:
struct nlist
{
    struct nlist *next; // next entry in chain
    char *name;         //  defined name
    char *defn;         // replacement text
};

#define HASHSIZE 101

// pointer table
static struct nlist *hashtab[HASHSIZE];

// hash: form hash value for string s
unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
    {
        hashval = *s + 31 * hashval;
    }
    return hashval % HASHSIZE;
}
