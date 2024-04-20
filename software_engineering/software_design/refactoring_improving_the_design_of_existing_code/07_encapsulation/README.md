# Chapter 7: Encapsulation

- [Chapter 7: Encapsulation](#chapter-7-encapsulation)
  - [Encapsulate Record](#encapsulate-record)
    - [Motivation](#motivation)
    - [Mechanics](#mechanics)
    - [Example](#example)
    - [Example: Encapsulating a Nested Record](#example-encapsulating-a-nested-record)
  - [Encapsulate Collection](#encapsulate-collection)
    - [Motivation](#motivation-1)
    - [Mechanics](#mechanics-1)
    - [Example](#example-1)
  - [Replace Primitive with Object](#replace-primitive-with-object)
    - [Motivation](#motivation-2)
    - [Mechanics](#mechanics-2)
    - [Example](#example-2)
  - [Replace Temp with Query](#replace-temp-with-query)
    - [Motivation](#motivation-3)
    - [Mechanics](#mechanics-3)
    - [Example](#example-3)
  - [Extract Class](#extract-class)
    - [Motivation](#motivation-4)
    - [Mechanics](#mechanics-4)
    - [Example](#example-4)
  - [Inline Class](#inline-class)
    - [Motivation](#motivation-5)
    - [Mechanics](#mechanics-5)
    - [Example](#example-5)
  - [Hide Delegate](#hide-delegate)
    - [Motivation](#motivation-6)
    - [Mechanics](#mechanics-6)
    - [Example](#example-6)
  - [Remove Middle Man](#remove-middle-man)
    - [Motivation](#motivation-7)
    - [Mechanics](#mechanics-7)
    - [Example](#example-7)
  - [Substitute Algorithm](#substitute-algorithm)
    - [Motivation](#motivation-8)
    - [Mechanics](#mechanics-8)

The most important criteria to be used in decomposing modules is to identiify
secrets that modules should hide from the rest of the system. Data structures
are the most common secrets.

## Encapsulate Record

```js
const organization = { name: 'Acme Gooseberries', country: 'GB' };

// refactored:
class Organization {
    constructor(data) {
        this._name = data.name;
        this._country = data.country;
    }
    get name() { return this._name; }
    set name(arg) { this._name = arg; }
    get country() { return this._country; }
    set country(arg) { this._country = arg; }
}
```

### Motivation

The user of the object doesn't need to know or care which is stored and which is
calculated. This encapsulation also helps with renaming. It's common to pass
nested structures of lists and hashmaps which are often serialized into formats
like JSON or XML. Such structures can be encapsulated too, which helps if their
formats change later on or if we're concerned about updates to the data that are
hard to keep track of.

### Mechanics

- Use `Encapsulate Variable` on the variable holding the record.
- Replace the content of the variable with a simple calss that wraps the record.
  Define an accessor inside this class that returns the raw record. Modify the
  functions that encapsulate the variable to use this accessor.
- Test.
- Provide new functions that return the object rather than the raw record.
- For each user of the record, replace its use of a function that returns the
  record with a function that returns the object. Use an accessor on the object
  to get at the field data, creating that accessor if needed. Test after each
  change.
- Remove the class's raw data accessor and the easily searchable functions that
  returned the raw record.
- Test.
- If the fields of the record are themselves structures, consider using
  `Encapsulate Record` and `Encapsulate Collection` recursively.

### Example

[encapsulate_record.js #version1, #version2, #version3, #version4](encapsulate_record.js)

### Example: Encapsulating a Nested Record

[encapsulating_a_nested_record.js #version1, #version2, #version3, #version4, #version5, #version6, #version7, #version8](encapsulating_a_nested_record.js)

## Encapsulate Collection

```js
class Person {
  get courses() { return this._courses; }
  set courses(aList) { this._courses = aList; }
}

class Person {
  get courses() { return this._courses.slice(); }
  addCourse(aCourse) { ... }
  removeCourse(aCourse) { ... }
}
```

### Motivation

Encapsulating any mutable data in program makes it easier to see when and how
data structures are modified, which then makes it easier to change those data
structures when it needs to.

To avoid collection being altered, we can provide collection modifier methods on
the class itself. And allows some form of read-only access to a collection. The
most common approach is to provide a getting method for the collection, but make
it return a copy of the underlying collection.

The difference between using a proxy and a copy is that a modification of the
source data will be visible in the proxy but not in a copy.

### Mechanics

- Apply `Encapsulate Variable` if the reference to the collection isn't already
  encapsulated.
- Add functions to add and remove elements from the collection.
- Run static checks.
- Find all reference to the collection. If anyone calls modifiers on the
  collection, change them to use the new add/remove functions. Test after each
  change.
- Modify the getter for the collection to return a protected view on it, using
  a read-only proxy or a copy.
- Test.

### Example

[encapsulate_collection.js #version1, #version2](encapsulate_collection.js)

## Replace Primitive with Object

```js
orders.filter(o => 'high' === o.priority
  || 'rush' === o.priority);

// refactored:
orders.filter(o => o.priority.higherThan(new Priority('normal')));
```

### Motivation

It is a good way to create a new class for some bits of data when you want to
do something other than simple printing.

### Mechanics

- Apply `Encapsulate Variable` if it isn't already.
- Create a simple value class for the data value. It should take the existing
  value in its constructor and provide a getter for that value.
- Run sttic checks.
- Change the setter to create a new instance of the value class and store that
  in the field, changing the type of the field if present.
- Change the getter to return the result of invoking the getter of the new
  class.
- Test.
- Consider using `Rename Function` on the original accessors to better reflect
  what they do.
- Consider clarifying the role of the new object as a value or reference object
  by applying `Change Reference to Value` or `Change Value to Reference`.

### Example

[replace_primitive_with_object.js](replace_primitive_with_object.js)

## Replace Temp with Query

```js
const basePrice = this._quantity * this._itemPrice;
if (basePrice > 1000){
  return basePrice * 0.95;
} else {
  return basePrice * 0.98;
}

// refactored:
get basePrice() { this._quantity * this._itemPrice; }

if (this.basePrice > 1000) {
  return this.basePrice * 0.95;
} else {
  return this.basePrice * 0.98;
}
```

### Motivation

Using a temp allows us to refer the value while explaining its meaning and
avoiding repeating the code that calculates it. But while using a variable is
handy, it can often by worthwhile to go a step further and use a function
instead.

Turning variables into their own functions makes it easier to extract parts of
the function. Using functions instead of variables also allows us to avoid
duplicating the calculation logic in similar functions.

### Mechanics

- Check that the variable is determined entirely before it's used, and the code
  that calculates it does not yield a different value whenever it is used.
- If the variable isn't read-only, and can be made read-only, do so.
- Test.
- Extract the assignment of the variable into a function. Ensure the extracted
  function is free of side effects. If not, use `Separate Query from Modifier`.
- Test.
- Use `Inline Variable` to remove the temp.

### Example

[replace_temp_with_query.js](replace_temp_with_query.js)

## Extract Class

```js
class Person {
  get officeAreaCode() { return this._officeAreaCode; }
  get officeNumber() { return this._officeNumber; }
}

// refactored:
class TelephoneNumber {
  get areaCode() { return this._areaCode; }
  get number() { return this._number; }
}

class Person {
  get officeAreaCode() { return this._telephoneNumber.areaCode; }
  get officeNumber() { return this._telephoneNumber.number; }
}
```

### Motivation

A class with many methods and quite a lot of data is too big to understand
easily. A good sign of splitting a class is when a subset of the data and a
subset of the methods seem to go together. Other good signs are subsets of data
that usually change together or are particularly dependent on each other.

### Mechanics

- Decide how to split the responsibilities of the class.
- Create a new child class to express the split-off responsibilities.
- Create an instance of the child class when constructing the parent and add a
  link from parent to child.
- Use `Move Field` on each field you wish to move. Test after each move.
- Use `Move Function` to move methods to the new child. Start with lower-level
  methods (those being called rather than calling). Test after each move.
- Review the interfaces of both classes, remove undeeded methods, change names
  to better fit the new circumstances.
- Decide whether to expose the new child. If so, consider applying
  `Change Reference to Value` to the child class.

### Example

[extract_class.js](extract_class.js)

## Inline Class

```js
class TelephoneNumber {
  get areaCode() { return this._areaCode; }
  get number() { return this._number; }
}

class Person {
  get officeAreaCode() { return this._telephoneNumber.areaCode; }
  get officeNumber() { return this._telephoneNumber.number; }
}

// refactored:
class Person {
  get officeAreaCode() { return this._officeAreaCode; }
  get officeNumber() { return this._officeNumber; }
}
```

### Motivation

Use `Inline Class` if a class is no longer pulling its weight and shouldn't be
around any more. Often, this is the result of refactoring that moves other
responsibilities out of the calss so there is little left.

Another reason to use `Inline Class` is if there are two classes that we want to
refactor into a pair of classes with a different allocation of features, we may
find it easier to first use `Inline Class` to combine them into a single class,
then `Extract Class` to make the new separation.

### Mechanics

- In the target class, create functions for all the public functions of the
  source class. These functions should just delegate to the source class.
- Change all references to source class methods so they use the target class's
  delegators instead. Test after each change.
- Move all the functions and data from the source class into the target, testing
  after each move, until the source class is empty.
- Delete the source class and hold a short, simple funeral service.

### Example

[inline_class.js](inline_class.js)

## Hide Delegate

```js
const manager = aPerson.department.manager;

// refactored:
const manager = aPerson.manager;

class Person {
  get manager() { return this.department.manager; }
}
```

### Motivation

If a delegate changes its interface, changes propagate to all the clients of its
server that use the delegate. But if we remove this dependency by placing a
simple delegating method on the server that hides the delegate. Then any changes
we make to the delegate propagate only to the server and not to the clients.

### Mechanics

- For each method on the delegate, create a simple delegating method on the
  server.
- Adjust the client to call the server. Test after each change.
- If no client needs to access the delegate anymore, remove the server's
  accessor for the delegate.
- Test.

### Example

[hide_delegate.js](hide_delegate.js)

## Remove Middle Man

```js
const manager = aPerson.manager;

class Person {
  get manager() { return this.department.manager; }
}

// refactored:
const manager = aPerson.department.manager;
```

### Motivation

Every time the client wants to use a new feature of the delegate, we have to add
a simple delegating method to the server. This might indicate that the server
class is just a middle man, and perhaps it's time for the client to call the
delegate directly.

### Mechanics

- Create a getter for the delegate.
- For each client use of a delegating method, replace the call to the delegating
  method by chaining through the accessor. Test after each replacement.

### Example

[remove_middle_man.js](remove_middle_man.js)

## Substitute Algorithm

```js
function foundPerson(people) {
  for (let i = 0; i < people.length; i++) {
    if (people[i] === 'Don') {
      return 'Don';
    }
    if (people[i] === 'John') {
      return 'John';
    }
    if (people[i] === 'Kent') {
      return 'Kent';
    }
  }
  return '';
}

// refactored:
function foundPerson(people) {
  const candidates = ['Don', 'John', 'Kent'];
  return people.find(p => candidates.includes(p)) || '';
}
```

### Motivation

When we want to change the algorithm to work slightly differently, it's easier
to start by replacing it with something that would make the change more
straightforward to make. Only by making it simple can we make the substitution
tractable.

### Mechanics

- Arrange the code to be replaced so that it fills a complete function.
- Prepare tests using this functions only, to capture its behavior.
- Prepare your alternative algorithm.
- Run static checks.
- Run tests to compare the output of the old algorithm to the new one. If they
  are the same, you're done. Otherwise, use the old algorithm for comparison in
  testing and debugging.
