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
    - [Motivation](#motivation-4)
    - [Mechanics](#mechanics-5)
    - [Example](#example-2)
    - [Example: Using Indirect Inheritance](#example-using-indirect-inheritance)
  - [Remove Subclass](#remove-subclass)
    - [Motivation](#motivation-5)
    - [Mechanics](#mechanics-6)
    - [Example](#example-3)
  - [Extract Superclass](#extract-superclass)
    - [Motivation](#motivation-6)
    - [Mechanics](#mechanics-7)
    - [Example](#example-4)
  - [Collapse Hierarchy](#collapse-hierarchy)
    - [Motivation](#motivation-7)
    - [Mechanics](#mechanics-8)
  - [Replace Subclass with Delegate](#replace-subclass-with-delegate)
    - [Motivation](#motivation-8)
    - [Mechanics](#mechanics-9)
    - [Example](#example-5)
    - [Example: Replacing a Hierarchy](#example-replacing-a-hierarchy)
  - [Replace Superclass with Delegate](#replace-superclass-with-delegate)
    - [Motivation](#motivation-9)
    - [Mechanics](#mechanics-10)
    - [Example](#example-6)

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

```js
function createEmployee(name, type) {
  return new Employee(name, type);
}

// refactored:
function createEmployee(name, type) {
  switch (type) {
    case "engineer": return new Engineer(name);
    case "salesman": return new Salesman(name);
    case "manager": return new Manager (name);
  }
}
```

### Motivation

Subclasses allow us to use polymorphism to handle conditional logic.

### Mechanics

- Self-encapsulate the type code field.
- Pick one type code value. Create a subclass for that type code. Override the
  type code getter to return the literal type code value.
- Create selector logic to map from the type code parameter to the new subclass.
  - With direct inheritance, use `Replace Constructor with Factory Function`
    and put the selector logic in the factory. With indirect inheritance, the
    selector logic may stay in the constructor.
- Test.
- Repeat creating the subclass and adding to the selector logic for each type
  code value. Test after each change.
- Remove the type code field.
- Test.
- Use `Push Down Method` and `Replace Conditional with Polymorphism` on any
  methods that use the type code accessors. Once all are replaced, you can
  remove the type code accessors.

### Example

[replace_type_code_with_subclasses.js](replace_type_code_with_subclasses.js)

### Example: Using Indirect Inheritance

[using_indirect_inheritance.js](using_indirect_inheritance.js)

## Remove Subclass

```js
class Person {
  get genderCode() { return "X"; }
}
class Male extends Person {
  get genderCode() { return "M"; }
}
class Female extends Person {
  get genderCode() { return "F"; }
}

// refactored:
class Person {
  get genderCode() { return this._genderCode; }
}
```

### Motivation

A subclass that does too little incurs a cost in understanding that is no longer
worthwhile. When that time comes, it's best to remove the subclass, replacing it
with a field on its superclass.

### Mechanics

- Use `Replace Constructor with Factory Function` on the subclass constructor.
  - If the clients of the constructors use a data field to decide which
    subclass to create, put that decision logic into a superclass factory
    method.
- If any code tests against the subclass’s types, use `Extract Function` on the
  type test and `Move Function` to move it to the superclass. Test after each
  change.
- Create a field to represent the subclass type.
- Change the methods that refer to the subclass to use the new type field.
- Delete the subclass.
- Test.

### Example

[remove_subclass.js](remove_subclass.js)

## Extract Superclass

```js
class Department {
  get totalAnnualCost() {...}
  get name() {...}
  get headCount() {...}
}

class Employee {
  get annualCost() {...}
  get name() {...}
  get id() {...}
}

// refactored:
class Party {
  get name() {...}
  get annualCost() {...}
}

class Department extends Party {
  get annualCost() {...}
  get headCount() {...}
}

class Employee extends Party {
  get annualCost() {...}
  get id() {...}
}
```

### Motivation

Using inheritance or delegation as a way to unify duplicate behavior? Often
`Extract Superclass` is the simpler approach.

### Mechanics

- Create an empty superclass. Make the original classes its subclasses.
- Test.
- One by one, use `Pull Up Constructor Body`, `Pull Up Method`, and
  `Pull Up Field` to move common elements to the superclass.
- Examine remaining methods on the subclasses. See if there are common parts.
  If so, use `Extract Function` followed by `Pull Up Method`.
- Check clients of the original classes. Consider adjusting them to use the
  superclass interface.

### Example

[extract_superclass.js](extract_superclass.js)

## Collapse Hierarchy

```js
class Employee {...}
class Salesman extends Employee {...}

// refactored:
class Employee {...}
```

### Motivation

When a class and its parent are no longer different enough to be worth keeping
separate, it's better to merge them together.

### Mechanics

- Choose which one to remove.
- Use `Pull Up Field`, `Push Down Field`, `Pull Up Method`, and
  `Push Down Method` to move all the elements into a single class.
- Adjust any references to the victim to change them to the class that will
  stay.
- Remove the empty class.
- Test.

## Replace Subclass with Delegate

```js
class Order {
  get daysToShip() {
    return this._warehouse.daysToShip;
  }
}

class PriorityOrder extends Order {
  get daysToShip() {
    return this._priorityPlan.daysToShip;
  }
}

// refactored:
class Order {
  get daysToShip() {
    return (this._priorityDelegate)
      ? this._priorityDelegate.daysToShip
      : this._warehouse.daysToShip;
  }
}

class PriorityOrderDelegate {
  get daysToShip() {
    return this._priorityPlan.daysToShip;
  }
}
```

### Motivation

Inheritance has its downsides. Inheritance can only be used for a single axis of
variation. A further problem is that inheritance introduces a very close
relationship between classes.

Delegation handles both of these problems. Delegation could be made to many
different classes for different reasons. Delegation is a regular relationship
between objects, which is much less coupling than subclassing.

There is a popular principle:
**Favor object composition over class class inhetitance**.

Inheritance is a valuable mechanism that does the job most of the time without
problems. So we could reach for it first, and move onto delegation when it
starts to rub badly.

Not all cases of `Replace Subclass with Delegate` involve an inheritance
hierarchy for the delegate, but setting up a hierarchy for states or strategies
if often useful.

### Mechanics

- If there are many callers for the constructors, apply
  `Replace Constructor with Factory Function`.
- Create an empty class for the delegate. Its constructor should take any
  subclass-specific data as well as, usually, a back-reference to the
  superclass.
- Add a field to the superclass to hold the delegate.
- Modify the creation of the subclass so that it initializes the delegate field
  with an instance of the delegate.
  - This can be done in the factory function, or in the constructor if the
    constructor can reliably tell whether to create the correct delegate.
- Choose a subclass method to move to the delegate class.
- `Use Move Function` to move it to the delegate class. Don’t remove the
  source’s delegating code.
  - If the method needs elements that should move to the delegate, move them.
    If it needs elements that should stay in the superclass, add a field to the
    delegate that refers to the superclass.
- If the source method has callers outside the class, move the source’s
  delegating code from the subclass to the superclass, guarding it with a check
  for the presence of the delegate. If not, apply `Remove Dead Code`.
  - If there’s more than one subclass, and you start duplicating code within
    them, use `Extract Superclass`. In this case, any delegating methods on the
    source superclass no longer need a guard if the default behavior is moved
    to the delegate superclass.
- Test.
- Repeat until all the methods of the subclass are moved.
- Find all callers of the subclasses’s constructor and change them to use the
  superclass constructor.
- Test.
- Use `Remove Dead Code` on the subclass.

### Example

[replace_subclass_with_delegate_v1.js](replace_subclass_with_delegate_v1.js)

### Example: Replacing a Hierarchy

[replacing_a_hierarchy_v1.js](replacing_a_hierarchy_v1.js)

## Replace Superclass with Delegate

```js
class List {...}
class Stack extends List {...}

// refactored:
class List {...}
class Stack {
  constructor() {
    this._storage = new List();
  }
}
```

### Motivation

Subclassing can be done in a way that leads to confusion and complication.

If functions of the superclass don't make sense on the subclass, that's a sign
that we shouldn't be using inheritance to use the superclass's functionality.

Using delegation makes it clear that it is a separate thing -- one where only
some of the functions carry over.

The recommended way is to mostly use inheritance first, and apply
`Replace Superclass with Delegate` when it becomes a problem.

### Mechanics

- Create a field in the subclass that refers to the superclass object.
  Initialize this delegate reference to a new instance.
- For each element of the superclass, create a forwarding function in the
  subclass that forwards to the delegate reference. Test after forwarding each
  consistent group.
- When all superclass elements have been overridden with forwarders, remove the
  inheritance link.

### Example

[replace_superclass_with_delegate.js](replace_superclass_with_delegate.js)
