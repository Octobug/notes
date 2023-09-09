# Chapter 1: Building Abstractions with Functions

- [Chapter 1: Building Abstractions with Functions](#chapter-1-building-abstractions-with-functions)
  - [1.1 Getting Started](#11-getting-started)
    - [1.1.1 Programming in Python](#111-programming-in-python)
    - [1.1.2 Installing Python 3](#112-installing-python-3)
    - [1.1.3 Interactive Sessions](#113-interactive-sessions)
    - [1.1.4 First Example](#114-first-example)
    - [1.1.5 Errors](#115-errors)

## 1.1 Getting Started

### 1.1.1 Programming in Python

> A language isn't something you learn so much as something you join.
> --Arika Okrent

### 1.1.2 Installing Python 3

### 1.1.3 Interactive Sessions

### 1.1.4 First Example

Python code consists of

- **expressions**: typically describe computations.
- **statements**: typically describe actions.

Broadly, computer programs consist of instructions to either

1. Compute some value
2. Carry out some action

```py
from urllib.request import urlopen

shakespeare = urlopen('https://www.composingprograms.com/shakespeare.txt')
words = set(shakespeare.read().decode().split())
{w for w in words if len(w) == 6 and w[::-1] in words}
```

- **functions**: encapsulate logic that manipulates data.
- **objects**: An object seamlessly bundles together data and the logic that
  manipulates that data, in a way that manages the complexity of both.
- **interpreters**: evaluating compound expressions requires a precise
  procedure that interprets code in a predictable way. A program that
  implements such a procedure, evaluating compound expressions, is called an
  interpreter.

### 1.1.5 Errors

>>>>> progress
