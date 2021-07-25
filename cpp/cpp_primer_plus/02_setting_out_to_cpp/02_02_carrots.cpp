// carrots.cpp -- food processing program
// uses and displays a variable

#include <iostream>

int main()
{
    using namespace std;

    // declaration and definition
    //  ref: https://stackoverflow.com/questions/1410563/what-is-the-difference-between-a-definition-and-a-declaration
    // A declaration introduces an identifier and describes its type, be it a
    //  type, object, or function. A declaration is what the compiler needs to
    //  accept references to that identifier.
    // e.g.
    //  extern int bar;
    //  extern int g(int, int);
    //  double f(int, double); // extern can be omitted for function
    //      declarations
    //  class foo; // no extern allowed for type declarations
    //
    // A definition actually instantiates/implements this identifier. It's what
    //  the linker needs in order to link references to those entities.
    // e.g.
    //  int bar;
    //  int g(int lhs, int rhs) {return lhs*rhs;}
    //  double f(int i, double d) {return i+d;}
    //  class foo {};

    int carrots;

    carrots = 25;
    cout << "I have ";
    // cout will translate an integer into character(s) before prints it
    cout << carrots;
    cout << " carrots.";
    cout << endl;
    carrots = carrots - 1;
    cout << "Crunch, crunch. Now I have " << carrots << " carrots." << endl;
    return 0;
}
