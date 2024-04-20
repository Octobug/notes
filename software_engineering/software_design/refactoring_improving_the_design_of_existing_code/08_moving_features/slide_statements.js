function version1() {
  function retrievePricingPlan() { }
  function retrieveOrder() { }
  function chargeOrder() { }

  const pricingPlan = retrievePricingPlan();
  const order = retrieveOrder();
  const baseCharge = pricingPlan.base;
  let charge;
  const chargePerUnit = pricingPlan.unit;
  const units = order.units;
  let discount;
  charge = baseCharge + units * chargePerUnit;
  let discountableUnits = Math.max(units - pricingPlan.discountThreshold, 0);
  discount = discountableUnits * pricingPlan.discountFactor;
  if (order.isRepeat) {
    discount += 20;
  }
  charge = charge - discount;
  chargeOrder(charge);
}

function version2() {
  function retrievePricingPlan() { }
  function retrieveOrder() { }
  function chargeOrder() { }

  const pricingPlan = retrievePricingPlan();
  const order = retrieveOrder();
  const baseCharge = pricingPlan.base;
  let charge;
  const chargePerUnit = pricingPlan.unit;
  const units = order.units;
  charge = baseCharge + units * chargePerUnit;
  let discountableUnits = Math.max(units - pricingPlan.discountThreshold, 0);
  let discount = discountableUnits * pricingPlan.discountFactor;
  if (order.isRepeat) {
    discount += 20;
  }
  charge = charge - discount;
  chargeOrder(charge);
}

function version3() {
  function retrievePricingPlan() { }
  function retrieveOrder() { }
  function chargeOrder() { }

  const pricingPlan = retrievePricingPlan();
  const baseCharge = pricingPlan.base;
  let charge;
  const chargePerUnit = pricingPlan.unit;
  const order = retrieveOrder();
  const units = order.units;
  charge = baseCharge + units * chargePerUnit;
  let discountableUnits = Math.max(units - pricingPlan.discountThreshold, 0);
  let discount = discountableUnits * pricingPlan.discountFactor;
  if (order.isRepeat) {
    discount += 20;
  }
  charge = charge - discount;
  chargeOrder(charge);
}

function version4() {
  function retrievePricingPlan() { }
  function retrieveOrder() { }
  function chargeOrder() { }

  const pricingPlan = retrievePricingPlan();
  const baseCharge = pricingPlan.base;
  let charge;
  const chargePerUnit = pricingPlan.unit;
  const order = retrieveOrder();
  const units = order.units;
  let discountableUnits = Math.max(units - pricingPlan.discountThreshold, 0);
  let discount = discountableUnits * pricingPlan.discountFactor;
  if (order.isRepeat) {
    discount += 20;
  }
  charge = baseCharge + units * chargePerUnit;
  charge = charge - discount;
  chargeOrder(charge);
}

function version5() {
  function retrievePricingPlan() { }
  function retrieveOrder() { }
  function chargeOrder() { }

  const order = retrieveOrder();
  const units = order.units;
  const pricingPlan = retrievePricingPlan();
  let discountableUnits = Math.max(units - pricingPlan.discountThreshold, 0);
  let discount = discountableUnits * pricingPlan.discountFactor;
  if (order.isRepeat) {
    discount += 20;
  }
  const baseCharge = pricingPlan.base;
  const chargePerUnit = pricingPlan.unit;
  let charge = baseCharge + units * chargePerUnit;
  charge = charge - discount;
  chargeOrder(charge);
}
