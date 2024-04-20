class Site {
  get customer() {
    return (this._customer === 'unknown')
      ? new UnknownCustomer()
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

class UnknownCustomer {
  get isUnknown() { return true; }
  get name() { return 'occupant'; }
  get billingPlan() { return registry.billingPlan.basic; }
  set billingPlan(arg) { }

  get paymentHistory() { return new NullPaymentHistory(); }
}

class NullPaymentHistory {
  get weeksDelinquentInLastYear() { return 0; }
}

function isUnknown(arg) {
  if (!((arg instanceof Customer) || (arg === 'unknown'))) {
    throw new Error(`investigate bad value: <${arg}>`);
  }
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
const newPlan = {};
aCustomer.billingPlan = newPlan;

// client 4...
const weeksDelinquent = aCustomer.paymentHistory.weeksDelinquentInLastYear;

// client 5...
const name = !isUnknown(aCustomer) ? aCustomer.name : 'unknown occupant';
