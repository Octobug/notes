function version1() {
  class Site {
    get customer() { return this._customer; }
  }

  class Customer {
    get name() { return this._name; }
    get billingPlan() { return this._billingPlan; }
    set billingPlan(arg) { this._billingPlan = arg; }
    get paymentHistory() { return this._paymentHistory; }
  }

  const site = new Site();

  // client 1...
  const aCustomer = site.customer;
  // ... lots of intervening code ...
  let customerName;
  if (aCustomer === 'unknown') {
    customerName = 'occupant';
  } else {
    customerName = aCustomer.name;
  }

  // client 2...
  const registry = {};
  const plan = (aCustomer === 'unknown')
    ? registry.billingPlans.basic
    : aCustomer.billingPlan;

  // client 3...
  const weeksDelinquent = (aCustomer === 'unknown')
    ? 0
    : aCustomer.paymentHistory.weeksDelinquentInLastYear;
}

function version2() {
  class Site {
    get customer() { return this._customer; }
  }

  class Customer {
    get name() { return this._name; }
    get billingPlan() { return this._billingPlan; }
    set billingPlan(arg) { this._billingPlan = arg; }
    get paymentHistory() { return this._paymentHistory; }
    get isUnknown() { return false; }
  }

  function createUnknownCustomer() {
    return {
      isUnknown: true,
    };
  }

  function isUnknown(arg) {
    return (arg === 'unknown');
  }

  const site = new Site();

  // client 1...
  const aCustomer = site.customer;
  // ... lots of intervening code ...
  let customerName;
  if (isUnknown(aCustomer)) {
    customerName = 'occupant';
  } else {
    customerName = aCustomer.name;
  }

  // client 2...
  const registry = {};
  const plan = isUnknown(aCustomer)
    ? registry.billingPlans.basic
    : aCustomer.billingPlan;

  // client 3...
  const weeksDelinquent = isUnknown(aCustomer)
    ? 0
    : aCustomer.paymentHistory.weeksDelinquentInLastYear;
}

function version3() {
  class Site {
    get customer() {
      return (this._customer === 'unknown')
        ? createUnknownCustomer()
        : this._customer;
    }
  }

  class Customer {
    get name() { return this._name; }
    get billingPlan() { return this._billingPlan; }
    set billingPlan(arg) { this._billingPlan = arg; }
    get paymentHistory() { return this._paymentHistory; }
    get isUnknown() { return false; }
  }

  function createUnknownCustomer() {
    return {
      isUnknown: true,
    };
  }

  function isUnknown(arg) {
    return arg.isUnknown;
  }

  const site = new Site();

  // client 1...
  const aCustomer = site.customer;
  // ... lots of intervening code ...
  let customerName;
  if (isUnknown(aCustomer)) {
    customerName = 'occupant';
  } else {
    customerName = aCustomer.name;
  }

  // client 2...
  const registry = {};
  const plan = isUnknown(aCustomer)
    ? registry.billingPlans.basic
    : aCustomer.billingPlan;

  // client 3...
  const weeksDelinquent = isUnknown(aCustomer)
    ? 0
    : aCustomer.paymentHistory.weeksDelinquentInLastYear;
}

function version4() {
  class Site {
    get customer() {
      return (this._customer === 'unknown')
        ? createUnknownCustomer()
        : this._customer;
    }
  }

  class Customer {
    get name() { return this._name; }
    get billingPlan() { return this._billingPlan; }
    set billingPlan(arg) { this._billingPlan = arg; }
    get paymentHistory() { return this._paymentHistory; }
    get isUnknown() { return false; }
  }

  function createUnknownCustomer() {
    return {
      isUnknown: true,
      name: 'occupant',
      billingPlan: registry.billingPlans.basic,
      paymentHistory: {
        weeksDelinquentInLastYear: 0,
      }
    };
  }

  function isUnknown(arg) {
    return arg.isUnknown;
  }

  const site = new Site();

  // client 1...
  const aCustomer = site.customer;
  // ... lots of intervening code ...
  let customerName;
  customerName = aCustomer.name;

  // client 2...
  const registry = {};
  const plan = aCustomer.billingPlan;

  // client 3...
  const weeksDelinquent = aCustomer.paymentHistory.weeksDelinquentInLastYear;
}
