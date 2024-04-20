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
    get type() { return this._type; }
    set type(arg) { this._type = arg; }

    get capitalizedType() {
      return this._type.charAt(0).toUpperCase()
        + this._type.substr(1).toLowerCase();
    }
    toString() {
      return `${this._name} (${this.capitalizedType})`;
    }
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
    get typeString() { return this._type.toString(); }
    get type() { return this._type; }
    set type(arg) { this._type = arg; }

    get capitalizedType() {
      return this.typeString.charAt(0).toUpperCase()
        + this.typeString.substr(1).toLowerCase();
    }
    toString() {
      return `${this._name} (${this.capitalizedType})`;
    }
  }

  class EmployeeType {
    constructor(aString) {
      this._value = aString;
    }
    toString() { return this._value; }
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
    get typeString() { return this._type.toString(); }
    get type() { return this._type; }
    set type(arg) { this._type = Employee.createEmployeeType(arg); }

    static createEmployeeType(aString) {
      switch (aString) {
        case 'engineer': return new Engineer();
        case 'manager': return new Manager();
        case 'salesman': return new Salesman();
        default: throw new Error(`Employee cannot be of type ${aString}`);
      }
    }

    get capitalizedType() {
      return this.typeString.charAt(0).toUpperCase()
        + this.typeString.substr(1).toLowerCase();
    }
    toString() {
      return `${this._name} (${this.capitalizedType})`;
    }
  }

  class EmployeeType { }
  class Engineer extends EmployeeType {
    toString() { return 'engineer'; }
  }
  class Manager extends EmployeeType {
    toString() { return 'manager'; }
  }
  class Salesman extends EmployeeType {
    toString() { return 'salesman'; }
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
    get typeString() { return this._type.toString(); }
    get type() { return this._type; }
    set type(arg) { this._type = Employee.createEmployeeType(arg); }

    static createEmployeeType(aString) {
      switch (aString) {
        case 'engineer': return new Engineer();
        case 'manager': return new Manager();
        case 'salesman': return new Salesman();
        default: throw new Error(`Employee cannot be of type ${aString}`);
      }
    }

    toString() {
      return `${this._name} (${this.type.capitalizedType})`;
    }
  }

  class EmployeeType {
    get capitalizedType() {
      return this.toString().charAt(0).toUpperCase()
        + this.toString().substr(1).toLowerCase();
    }
  }
  class Engineer extends EmployeeType {
    toString() { return 'engineer'; }
  }
  class Manager extends EmployeeType {
    toString() { return 'manager'; }
  }
  class Salesman extends EmployeeType {
    toString() { return 'salesman'; }
  }
}
