function version1() {
  class Party { }

  class Employee extends Party {
    constructor(name, id, monthlyCost) {
      super();
      this._id = id;
      this._name = name;
      this._monthlyCost = monthlyCost;
    }
    // rest of class...
  }

  class Department extends Party {
    constructor(name, staff) {
      super();
      this._name = name;
      this._staff = staff;
    }
    // rest of class...
  }
}

function version2() {
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
    // rest of class...
  }

  class Department extends Party {
    constructor(name, staff) {
      super(name);
      this._staff = staff;
    }
    // rest of class...
  }
}

function versionA() {
  class Employee {
    constructor(name) { }

    get isPrivileged() { return this._isPrivileged; }

    assignCar() { }
  }

  class Manager extends Employee {
    constructor(name, grade) {
      super(name);
      this._grade = grade;
      if (this.isPrivileged) {
        this.assignCar(); // every subclass does this
      }
    }

    get isPrivileged() {
      return this._grade > 4;
    }
  }
}

function versionB() {
  class Employee {
    constructor(name) { }

    get isPrivileged() { return this._isPrivileged; }

    assignCar() { }
  }

  class Manager extends Employee {
    constructor(name, grade) {
      super(name);
      this._grade = grade;
      this.finishConstruction();
    }

    finishConstruction() {
      if (this.isPrivileged) {
        this.assignCar();
      }
    }

    get isPrivileged() {
      return this._grade > 4;
    }
  }
}

function versionC() {
  class Employee {
    constructor(name) { }

    get isPrivileged() { return this._isPrivileged; }

    assignCar() { }

    finishConstruction() {
      if (this.isPrivileged) {
        this.assignCar();
      }
    }
  }

  class Manager extends Employee {
    constructor(name, grade) {
      super(name);
      this._grade = grade;
      this.finishConstruction();
    }

    get isPrivileged() {
      return this._grade > 4;
    }
  }
}
