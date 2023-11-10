# Object-Oriented Programming

- [Object-Oriented Programming](#object-oriented-programming)
  - [Object](#object)
    - [Object properties](#object-properties)
    - [Object type](#object-type)
    - [Object ID](#object-id)
  - [Encapsulation](#encapsulation)
    - [广义封装](#广义封装)
    - [狭义封装](#狭义封装)
  - [Inheritance](#inheritance)
    - [继承的动态性](#继承的动态性)
  - [Polymorphism](#polymorphism)

## Object

在 Python 中，一切皆对象（包括整数, `None` 等值，连类本身也是对象）。

In computer science, **reflective programming** or **reflection** is the
ability of a process to examine, introspect, and modify its own structure and
behavior.

### Object properties

- `dir()`: 反射对象，了解对象包含哪些属性
- `hasattr()`
- `setattr()`
- `getattr()`
- `delattr()`

### Object type

- `type()`

### Object ID

- `id()`

## Encapsulation

### 广义封装

数据成员和函数成员打包到一起。

### 狭义封装

增加了信息隐藏 (Information Hiding)，或者说增加了访问控制。

## Inheritance

Python 没有区分“实现继承”和“接口继承”。

### 继承的动态性

作为一种动态语言，Python 可以在运行时修改类的继承关系。

## Polymorphism

和其他 OO 语言差不多。
