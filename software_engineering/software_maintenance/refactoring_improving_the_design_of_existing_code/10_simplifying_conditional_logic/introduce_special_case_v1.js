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
const newPlan = {};
if (aCustomer !== 'unknown') {
  aCustomer.billingPlan = newPlan;
}

// client 4...
const weeksDelinquent = (aCustomer === 'unknown')
  ? 0
  : aCustomer.paymentHistory.weeksDelinquentInLastYear;
