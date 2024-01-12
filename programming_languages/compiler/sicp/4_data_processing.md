# Chapter 4: Data Processing

- [Chapter 4: Data Processing](#chapter-4-data-processing)
  - [4.1 Introduction](#41-introduction)
  - [4.2 Implicit Sequences](#42-implicit-sequences)
    - [4.2 Iterators](#42-iterators)
    - [4.2.2 Iterables](#422-iterables)
  - [Lab 6: Mutability, Iterators](#lab-6-mutability-iterators)

## 4.1 Introduction

> <https://www.composingprograms.com/pages/41-introduction.html>

To process large data sets efficiently, programs are organized into pipelines of
manipulations on sequential streams of data.

Sequential data sets of unbounded length also appear in other computational
domains. For instance:

- the sequence of telephone calls sent through a cell tower
- the sequence of mouse movements made by a computer user
- the sequence of acceleration measurements from sensors on an aircraft

## 4.2 Implicit Sequences

> <https://www.composingprograms.com/pages/42-implicit-sequences.html>

We can construct an object that provides access to all of the elements of some
sequential dataset without computing the value of each element in advance.
Instead, they can be computed on demand.

```py
>>> r = range(10000, 1000000000)
>>> r[45006230]
45016230
```

Computing values on demand, rather than retrieving them from an existing
representation, is an example of ***lazy computation***. In computer science,
lazy computation describes any program that delays the computation of a value
until that value is needed.

### 4.2 Iterators

An ***iterator*** is an object that provides sequential access to values, one by
one. The iterator abstraction has two components:

- a mechanism for retrieving the next element in the sequence being processed
- a mechanism for signaling that the end of the sequence has been reached and no
  further elements remain.

For any container, such as a `list` or `range`, an iterator can be obtained by
calling the built-in `iter` function. The contents of the iterator can be
accessed by calling the built-in `next` function.

```py
>>> primes = [2, 3, 5, 7]
>>> type(primes)
<class 'list'>
>>> iterator = iter(primes)
>>> type(iterator)
<class 'list_iterator'>
>>> next(iterator)
2
>>> next(iterator)
3
>>> next(iterator)
5
>>> next(iterator)
7
>>> next(iterator)
Traceback (most recent call last):
  File "<stdin>", line 1, in <module>
StopIteration

>>> try:
        next(iterator)
    except StopIteration:
        print('No more values')
No more values
```

An iterator maintains local state to represent its position in a sequence. Each
time `next` is called, that position advances. Two separate iterators can track
two different positions in the same sequence. However, two names for the same
iterator will share a position, because they share the same value.

```py
>>> r = range(3, 13)
>>> s = iter(r)  # 1st iterator over r
>>> next(s)
3
>>> next(s)
4
>>> t = iter(r)  # 2nd iterator over r
>>> next(t)
3
>>> next(t)
4
>>> u = t        # Alternate name for the 2nd iterator
>>> next(u)
5
>>> next(u)
6
>>> next(s)
5
>>> next(t)
7
```

Calling `iter` on an iterator will return that iterator, not a copy. This
behavior is included in Python so that a programmer can call `iter` on a value
to get an iterator without having to worry about whether it is an iterator or a
container.

```py
>>> v = iter(t)  # Another alterante name for the 2nd iterator
>>> next(v)
8
>>> next(u)
9
>>> next(t)
10
```

The usefulness of iterators is derived from the fact that the underlying series
of data for an iterator may not be represented explicitly in memory. An
iterator provides a mechanism for considering each of a series of values in
turn, but all of those elements do not need to be stored simultaneously.
Instead, when the next element is requested from an iterator, that element may
be computed on demand instead of being retrieved from an existing memory source.

Iterators allow for lazy generation of a much broader class of underlying
sequential datasets, because they do not need to provide access to arbitrary
elements of the underlying series. Instead, **iterators are only required to
compute the next element of the series, in order**, each time another element
is requested. While not as flexible as accessing arbitrary elements of a
sequence (called random access), sequential access to sequential data is often
sufficient for data processing applications.

### 4.2.2 Iterables

>>>>> progress

## Lab 6: Mutability, Iterators

- [ ] [Lab 6: Mutability, Iterators](https://inst.eecs.berkeley.edu/~cs61a/sp23/lab/lab06/)

>>>>> progress
