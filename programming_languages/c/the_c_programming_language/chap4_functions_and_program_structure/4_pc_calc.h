// defines
#define NUMBER '0' // signal that a number was found
// stack
void push(double);
double pop(void);
// getop
int getop(char[]);
// getch
int getch(void);
void ungetch(int); // when meets the first non-digit, it has to be given back
