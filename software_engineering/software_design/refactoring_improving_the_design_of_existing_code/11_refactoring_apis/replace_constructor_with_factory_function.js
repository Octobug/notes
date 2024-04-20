function version1() {
  class Employee {
    constructor(name, typeCode) {
      this._name = name;
      this._typeCode = typeCode;
    }
    get name() { return this._name; }
    get type() {
      return Employee.legalTypeCodes[this._typeCode];
    }
    static get legalTypeCodes() {
      return { 'E': 'Engineer', 'M': 'Manager', 'S': 'Salesman' };
    }
  }

  const document = {};
  const candidate = new Employee(document.name, document.empType);
  const leadEngineer = new Employee(document.leadEngineer, 'E');
}

function version2() {
  class Employee {
    constructor(name, typeCode) {
      this._name = name;
      this._typeCode = typeCode;
    }
    get name() { return this._name; }
    get type() {
      return Employee.legalTypeCodes[this._typeCode];
    }
    static get legalTypeCodes() {
      return { 'E': 'Engineer', 'M': 'Manager', 'S': 'Salesman' };
    }
  }

  function createEmployee(name, typeCode) {
    return new Employee(name, typeCode);
  }

  const document = {};
  const candidate = createEmployee(document.name, document.empType);
  const leadEngineer = createEmployee(document.leadEngineer, 'E');
}

function version3() {
  class Employee {
    constructor(name, typeCode) {
      this._name = name;
      this._typeCode = typeCode;
    }
    get name() { return this._name; }
    get type() {
      return Employee.legalTypeCodes[this._typeCode];
    }
    static get legalTypeCodes() {
      return { 'E': 'Engineer', 'M': 'Manager', 'S': 'Salesman' };
    }
  }

  function createEmployee(name, typeCode) {
    return new Employee(name, typeCode);
  }

  function createEngineer(name) {
    return new Employee(name, 'E');
  }

  const document = {};
  const candidate = createEmployee(document.name, document.empType);
  const leadEngineer = createEngineer(document.leadEngineer);
}
