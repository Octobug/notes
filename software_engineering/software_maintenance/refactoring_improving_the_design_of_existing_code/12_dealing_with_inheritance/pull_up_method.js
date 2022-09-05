function version1() {
  class Party { }

  class Employee extends Party {
    get annualCost() {
      return this.monthlyCost * 12;
    }
  }
  class Department extends Party {
    get totalAnnualCost() {
      return this.monthlyCost * 12;
    }
  }
}

function version2() {
  class Party { }

  class Employee extends Party {
    get annualCost() {
      return this.monthlyCost * 12;
    }
  }
  class Department extends Party {
    get annualCost() {
      return this.monthlyCost * 12;
    }
  }
}

function version3() {
  class SubclassResponsibilityError { }

  class Party {
    get annualCost() {
      return this.monthlyCost * 12;
    }

    get monthlyCost() {
      throw new SubclassResponsibilityError();
    }
  }

  class Employee extends Party {
  }
  class Department extends Party {
  }
}
