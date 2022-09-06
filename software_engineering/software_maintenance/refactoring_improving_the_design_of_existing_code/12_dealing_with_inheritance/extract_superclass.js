function version1() {
  class Employee {
    constructor(name, id, monthlyCost) {
      this._id = id;
      this._name = name;
      this._monthlyCost = monthlyCost;
    }
    get monthlyCost() { return this._monthlyCost; }
    get name() { return this._name; }
    get id() { return this._id; }

    get annualCost() {
      return this.monthlyCost * 12;
    }
  }

  class Department {
    constructor(name, staff) {
      this._name = name;
      this._staff = staff;
    }
    get staff() { return this._staff.slice(); }
    get name() { return this._name; }

    get totalMonthlyCost() {
      return this.staff
        .map(e => e.monthlyCost)
        .reduce((sum, cost) => sum + cost);
    }
    get headCount() {
      return this.staff.length;
    }
    get totalAnnualCost() {
      return this.totalMonthlyCost * 12;
    }
  }
}

function version2() {
  class Party { }

  class Employee extends Party {
    constructor(name, id, monthlyCost) {
      super();
      this._id = id;
      this._name = name;
      this._monthlyCost = monthlyCost;
    }
    get monthlyCost() { return this._monthlyCost; }
    get name() { return this._name; }
    get id() { return this._id; }

    get annualCost() {
      return this.monthlyCost * 12;
    }
  }

  class Department extends Party {
    constructor(name, staff) {
      super();
      this._name = name;
      this._staff = staff;
    }
    get staff() { return this._staff.slice(); }
    get name() { return this._name; }

    get totalMonthlyCost() {
      return this.staff
        .map(e => e.monthlyCost)
        .reduce((sum, cost) => sum + cost);
    }
    get headCount() {
      return this.staff.length;
    }
    get totalAnnualCost() {
      return this.totalMonthlyCost * 12;
    }
  }
}

function version3() {
  class Party {
    constructor(name) {
      this._name = name;
    }

    get name() { return this._name; }
  }

  class Employee extends Party {
    constructor(name, id, monthlyCost) {
      super(name);
      this._id = id;
      this._monthlyCost = monthlyCost;
    }
    get monthlyCost() { return this._monthlyCost; }
    get id() { return this._id; }

    get annualCost() {
      return this.monthlyCost * 12;
    }
  }

  class Department extends Party {
    constructor(name, staff) {
      super(name);
      this._staff = staff;
    }
    get staff() { return this._staff.slice(); }

    get totalMonthlyCost() {
      return this.staff
        .map(e => e.monthlyCost)
        .reduce((sum, cost) => sum + cost);
    }
    get headCount() {
      return this.staff.length;
    }
    get totalAnnualCost() {
      return this.totalMonthlyCost * 12;
    }
  }
}

function version4() {
  class Party {
    constructor(name) {
      this._name = name;
    }

    get name() { return this._name; }
  }

  class Employee extends Party {
    constructor(name, id, monthlyCost) {
      super(name);
      this._id = id;
      this._monthlyCost = monthlyCost;
    }
    get monthlyCost() { return this._monthlyCost; }
    get id() { return this._id; }

    get annualCost() {
      return this.monthlyCost * 12;
    }
  }

  class Department extends Party {
    constructor(name, staff) {
      super(name);
      this._staff = staff;
    }
    get staff() { return this._staff.slice(); }

    get monthlyCost() {
      return this.staff
        .map(e => e.monthlyCost)
        .reduce((sum, cost) => sum + cost);
    }
    get headCount() {
      return this.staff.length;
    }
    get annualCost() {
      return this.monthlyCost * 12;
    }
  }
}

function version5() {
  class Party {
    constructor(name) {
      this._name = name;
    }

    get name() { return this._name; }

    get annualCost() {
      return this.monthlyCost * 12;
    }
  }

  class Employee extends Party {
    constructor(name, id, monthlyCost) {
      super(name);
      this._id = id;
      this._monthlyCost = monthlyCost;
    }
    get monthlyCost() { return this._monthlyCost; }
    get id() { return this._id; }
  }

  class Department extends Party {
    constructor(name, staff) {
      super(name);
      this._staff = staff;
    }
    get staff() { return this._staff.slice(); }

    get monthlyCost() {
      return this.staff
        .map(e => e.monthlyCost)
        .reduce((sum, cost) => sum + cost);
    }
    get headCount() {
      return this.staff.length;
    }
  }
}
