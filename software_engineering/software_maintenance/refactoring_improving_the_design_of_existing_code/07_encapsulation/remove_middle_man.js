function version1() {
  class Department {
    get manager() { return this._manager; }
  }

  class Person {
    get manager() { return this._department.manager; }
  }

  const aPerson = new Person();
  const manager = aPerson.manager;
}

function version2() {
  class Department {
    get manager() { return this._manager; }
  }

  class Person {
    get department() { return this._department; }
  }

  const aPerson = new Person();
  const manager = aPerson.department.manager;
}
