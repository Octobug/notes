function version1() {
  class Department {
    get chargeCode() { return this._chargeCode; }
    set chargeCode(arg) { this._chargeCode = arg; }

    get manager() { return this._manager; }
    set manager(arg) { this._manager = arg; }
  }

  class Person {
    constructor(name) {
      this._name = name;
    }

    get name() { return this._name; }

    get department() { return this._department; }
    set department(arg) { this._department = arg; }
  }

  const aPerson = new Person('John');
  const manager = aPerson.department.manager;
}

function version2() {
  class Department {
    get chargeCode() { return this._chargeCode; }
    set chargeCode(arg) { this._chargeCode = arg; }

    get manager() { return this._manager; }
    set manager(arg) { this._manager = arg; }
  }

  class Person {
    constructor(name) {
      this._name = name;
    }

    get name() { return this._name; }

    get department() { return this._department; }
    set department(arg) { this._department = arg; }

    get manager() { return this._department.manager; }
  }

  const aPerson = new Person('John');
  const manager = aPerson.manager;
}
