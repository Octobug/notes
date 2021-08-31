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

## C++ Statements

### Declaration Statements and Variables

```cpp
int carrots;
```

This statement provides two kinds of information:

1. the type of memory storage needed
2. a label to attach to that storage

A declaration indicates the type of data to be stored and the name the program
will use for the data that's stored there.

The declaration state in the program is called a *definition declaration*
statement, or *definition*.

This means that its presence causes the compiler to allocate memory space for
the variable.

In more complex situations, you can also have *reference declarations*. These
tell the computer to use a variable that has already been defined elsewhere.

In general, a declaration need not be a definition.

#### Declaration and Definition

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

#### Why must Variables Be Declared in C++?

- prevent from misspelling

In BASIC (the programming language):

```bas
CastleDark = 34
...
CastleDank = CastleDark + MoreGhosts
...
PRINT CastleDark
```

#### Declaring Convention

The C++ style for declaring variables is to declare a variable as close as to
its first use as possible.

### Using `cin`

C++ considers output to be a stream of characters flowing out of the program,
it ocnsiders input to be a stream of characters flowing into the program.

The `iostream` file defined `cin` as an object that represents this stream.

### `cin` and `cout`: A Touch of Class
