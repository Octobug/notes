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
const plan = (isUnknown(aCustomer))
  ? registry.billingPlans.basic
  : aCustomer.billingPlan;

// client 3...
const newPlan = {};
if (!isUnknown(aCustomer)) {
  aCustomer.billingPlan = newPlan;
}

// client 4...
const weeksDelinquent = (isUnknown(aCustomer))
  ? 0
  : aCustomer.paymentHistory.weeksDelinquentInLastYear;
