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

## Functions

### Function Prototype

A function prototype does for functions what a variable declaration does for
variables.

The prorotype only describes the function interface.

```cpp
// function prototype
double sqrt(double);
```

The definition includes the code for the function's workings.

C and C++ divide these two features -- prototype and definition -- for library
functions. The library files contain the compiled code for the functions,
whereas the header files contain the prototypes.

You should place a function prototype ahead of where you first use the function.

The usual practice is to place prototypes just before the definition of the
`main()` function.

#### Using Library Functions

C++ library functionsa are stored in library files. When the compiler compiles a
program, it must search the library files for the functions you've used.

### Function Variations

Some languages reserve the term *function* for functions with return values and
use the terms *procedure* or *subroutine* for those without return values.

### User-Defined Functions

#### Function Form

```cpp
type functionname(argumentlist)
{
    statements
}
```

All functions are created equal.

#### Function Headers

```cpp
void simon(int n)
```

Functions that have return values should use the keyword `return` to provide
the return value and to terminate the function.

```cpp
int main() 
{
    return 0;
}
```

#### Who calls the main()

The operating system. Thus `main()`'s return value is returned to the OS.
And, the OS could use the return value as an exit code.

#### `main` is not a keyword in c++

### Placing the `using` Directive in Multifunction Programs

The current prevalent philosophy is that it's preferable to be more
discriminating and limit access to the `std` namespace to only those functions
that need access.

#### Choices of placing `using`

- above all functions
- inside specific functions
- instead of `using namespace std`, use `using std::cout;`
- omit `using`, use `std::` prefix

## Summary

### C++ statement types

- `Declaration statement`: A declaration statement announces the name and the
  type of a variable used in a function.
- `Assignment state`: An assignment statement uses the assignment operator (=)
  to assign a value to a variable.
- `Message statement`: A message statement sneds a message to an object,
  initiating some sort of action. e.g. `cout << x`
- `Function call`: A function call activates a function.
- `Function prototype`: A function prototype declares the return type for a
  function, along with the number and type of arguments the function expects.
- `Return statement`: A return statement sneds a value from a called function
  back to the calling function.

### Class

A class is a user-defined specification for a data type. It details how
information is to be represented and also the operations that can performed
with the data.

An object is an entity created according to a class prescription, just as a
simple variable is an entity created according to a data type description.

### Library functions

To use a library function, you should include the header file that provides
the prototype for the function.

## Chapter Review

### 2. What does the following preprocessor directive do?

```cpp
#include <iostream>
```

It causes the contents of the `iostream` file to be substituted for this
directive before final compilation.
