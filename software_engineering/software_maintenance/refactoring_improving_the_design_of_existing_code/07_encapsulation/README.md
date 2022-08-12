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

>>>>> progress
