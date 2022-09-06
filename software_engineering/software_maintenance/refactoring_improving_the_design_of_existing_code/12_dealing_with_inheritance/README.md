# Chapter 12: Dealing with Inheritance

- [Chapter 12: Dealing with Inheritance](#chapter-12-dealing-with-inheritance)
  - [Pull Up Method](#pull-up-method)
    - [Motivation](#motivation)
    - [Mechanics](#mechanics)
    - [Example](#example)
  - [Pull Up Field](#pull-up-field)
    - [Mechanics](#mechanics-1)
  - [Pull Up Constructor Body](#pull-up-constructor-body)
    - [Motivation](#motivation-1)
    - [Mechanics](#mechanics-2)
    - [Example](#example-1)
  - [Push Down Method](#push-down-method)
    - [Motivation](#motivation-2)
    - [Mechanics](#mechanics-3)
  - [Push Down Field](#push-down-field)
    - [Motivation](#motivation-3)
    - [Mechanics](#mechanics-4)
  - [Replace Type Code with Subclasses](#replace-type-code-with-subclasses)

## Pull Up Method

```js
class Employee {...}

class Salesman extends Employee {
    get name() {...}
}

class Engineer extends Employee {
    get name() {...}
}

// refactored:
class Employee {
    get name() {...}
}

class Salesman extends Employee {...}
class Engineer extends Employee {...}
```

### Motivation

Whenever there is duplication, there is risk that an alteration to one copy will
not be made to the other.

### Mechanics

- Inspect methods to ensure they are identical.
- Check that all method calls and field references inside the method body refer
  to features that can be called from the superclass.
- If the methods have different signatures, use `Change Function Declaration`
  to get them to the one you want to use on the superclass.
- Create a new method in the superclass. Copy the body of one of the methods
  over to it.
- Run static checks.
- Delete one subclass method.
- Test.
- Keep deleting subclass methods until they are all gone.

### Example

[pull_up_method.js](pull_up_method.js)

## Pull Up Field

```js
class Employee {...} // Java

class Salesman extends Employee {
  private String name;
}

class Engineer extends Employee {
  private String name;
}

// refactored:
class Employee {
  protected String name;
}

class Salesman extends Employee {...}
class Engineer extends Employee {...}
```

### Mechanics

- Inspect all users of the candidate field to ensure they are used in the same
  way.
- If the fields have different names, use `Rename Field` to give them the same
  name.
- Create a new field in the superclass.
- Delete the subclass fields.
- Test.

## Pull Up Constructor Body

```js
class Party {...}

class Employee extends Party {
  constructor(name, id, monthlyCost) {
    super();
    this._id = id;
    this._name = name;
    this._monthlyCost = monthlyCost;
  }
}

// refactored:
class Party {
  constructor(name) {
    this._name = name;
  }
}

class Employee extends Party {
  constructor(name, id, monthlyCost) {
    super(name);
    this._id = id;
    this._monthlyCost = monthlyCost;
  }
}
```

### Motivation

If there are subclass methods with common behavior, they should be moved into
the superclass.

### Mechanics

- Define a superclass constructor, if one doesn’t already exist. Ensure it’s
  called by subclass constructors.
- Use `Slide Statements` to move any common statements to just after the super
  call.
- Remove the common code from each subclass and put it in the superclass. Add
  to the super call any constructor parameters referenced in the common code.
- Test.
- If there is any common code that cannot move to the start of the constructor,
  use `Extract Function` followed by `Pull Up Method`.

### Example

[pull_up_constructor_body.js](pull_up_constructor_body.js)

## Push Down Method

```js
class Employee {
  get quota {...}
}

class Engineer extends Employee {...}
class Salesman extends Employee {...}

// refactored:
class Employee {...}
class Engineer extends Employee {...}
class Salesman extends Employee {
  get quota {...}
}
```

### Motivation

If a method is only relevant to one subclass or a small proportion of
subclasses, removing it from the superclass and putting it only on the
subclasses makes that clearer. This refactoring could only be done if the
callers knows it's working with a particular subclass -- otherwise, we should
use `Replace Conditional with Polymorphism` with some placebo behavior on the
superclass.

### Mechanics

- Copy the method into every subclass that needs it.
- Remove the method from the superclass.
- Test.
- Remove the method from each subclasses that don’t need it.
- Test.

## Push Down Field

```java
class Employee {
  private String quota;
}
class Engineer extends Employee {...}
class Salesman extends Employee {...}

// refactored:
class Employee {...}
class Engineer extends Employee {...}

class Salesman extends Employee {
  protected String quota;
}
```

### Motivation

If a field is only used by one subclass or a small proportion of subclasses, it
should be moved to those subclasses.

### Mechanics

- Declare field in all subclasses that need it.
- Remove the field from the superclass.
- Test.
- Remove the field from all subclasses that don’t need it.
- Test.

## Replace Type Code with Subclasses
