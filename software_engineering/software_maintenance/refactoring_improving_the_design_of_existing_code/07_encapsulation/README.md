# Chapter 7: Encapsulation

- [Chapter 7: Encapsulation](#chapter-7-encapsulation)
  - [Encapsulate Record](#encapsulate-record)
    - [Motivation](#motivation)
    - [Mechanics](#mechanics)
    - [Example](#example)
    - [Example: Encapsulating a Nested Record](#example-encapsulating-a-nested-record)
  - [Encapsulate Collection](#encapsulate-collection)

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

>>>>> progress
