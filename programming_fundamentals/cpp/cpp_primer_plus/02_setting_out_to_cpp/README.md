# Setting Out To C++

## Namespace Convention

modern practice regards this(`using namespace std;`) as a bit lazy and
potentially a problem in large projects. The preferred approaches are to use
`std::qualifier` or to use something called a using declaration to make just
particular names available:

```cpp
    using std::cout;
    using std::endl;
    using std::cin;
```

## Declaration and Definition

> <https://stackoverflow.com/questions/1410563/what-is-the-difference-between-a-definition-and-a-declaration>

A declaration introduces an identifier and describes its type, be it a type,
object, or function. A declaration is what the compiler needs to accept
references to that identifier.

**e.g.**

```cpp
extern int bar;
extern int g(int, int);
// extern can be omitted for function declarations
double f(int, double);
// no extern allowed for type declarations
class foo;
```

A definition actually instantiates/implements this identifier. It's what the
linker needs in order to link references to those entities.

**e.g.**

```cpp
int bar;
int g(int lhs, int rhs) {return lhs*rhs;}
double f(int i, double d) {return i+d;}
class foo {};
```
