function version1() {
  class Employee {
    constructor(name, type) {
      this.validateType(type);
      this._name = name;
      this._type = type;
    }
    validateType(arg) {
      if (!['engineer', 'manager', 'salesman'].includes(arg)) {
        throw new Error(`Employee cannot be of type ${arg}`);
      }
    }
    toString() { return `${this._name} (${this._type})`; }
  }
}

function version2() {
  class Employee {
    constructor(name, type) {
      this.validateType(type);
      this._name = name;
      this._type = type;
    }
    validateType(arg) {
      if (!['engineer', 'manager', 'salesman'].includes(arg)) {
        throw new Error(`Employee cannot be of type ${arg}`);
      }
    }
    get type() { return this._type; }
    toString() { return `${this._name} (${this.type})`; }
  }
}

function version3() {
  class Employee {
    constructor(name, type) {
      this.validateType(type);
      this._name = name;
      this._type = type;
    }
    validateType(arg) {
      if (!['engineer', 'manager', 'salesman'].includes(arg)) {
        throw new Error(`Employee cannot be of type ${arg}`);
      }
    }
    get type() { return this._type; }
    toString() { return `${this._name} (${this.type})`; }
  }

  class Engineer extends Employee {
    get type() { return 'engineer'; }
  }

  function createEmployee(name, type) {
    switch (type) {
      case 'engineer': return new Engineer(name, type);
    }
    return new Employee(name, type);
  }
}

function version4() {
  class Employee {
    constructor(name, type) {
      this.validateType(type);
      this._name = name;
      this._type = type;
    }
    validateType(arg) {
      if (!['engineer', 'manager', 'salesman'].includes(arg)) {
        throw new Error(`Employee cannot be of type ${arg}`);
      }
    }
    get type() { return this._type; }
    toString() { return `${this._name} (${this.type})`; }
  }

  class Engineer extends Employee {
    get type() { return 'engineer'; }
  }

  class Salesman extends Employee {
    get type() { return 'salesman'; }
  }

  class Manager extends Employee {
    get type() { return 'manager'; }
  }

  function createEmployee(name, type) {
    switch (type) {
      case 'engineer': return new Engineer(name, type);
      case 'salesman': return new Salesman(name, type);
      case 'managger': return new Manager(name, type);
    }
    return new Employee(name, type);
  }
}

function version5() {
  class Employee {
    constructor(name) {
      this._name = name;
    }
    toString() { return `${this._name} (${this.type})`; }
  }

  class Engineer extends Employee {
    get type() { return 'engineer'; }
  }

  class Salesman extends Employee {
    get type() { return 'salesman'; }
  }

  class Manager extends Employee {
    get type() { return 'manager'; }
  }

  function createEmployee(name, type) {
    switch (type) {
      case 'engineer': return new Engineer(name);
      case 'salesman': return new Salesman(name);
      case 'managger': return new Manager(name);
      default: throw new Error(`Employee cannot be of type ${type}`);
    }
  }
}
