function version1() {
  let charge;
  const aDate = {};
  const plan = {};
  const quantity = 10;

  if (!aDate.isBefore(plan.summerStart) && !aDate.isAfter(plan.summerEnd)) {
    charge = quantity * plan.summerRate;
  } else {
    charge = quantity * plan.regularRate + plan.regularServiceCharge;
  }
}

function version2() {
  let charge;
  const aDate = {};
  const plan = {};
  const quantity = 10;

  if (summer()) {
    charge = quantity * plan.summerRate;
  } else {
    charge = quantity * plan.regularRate + plan.regularServiceCharge;
  }

  function summer() {
    return !aDate.isBefore(plan.summerStart) && !aDate.isAfter(plan.summerEnd);
  }
}

function version3() {
  let charge;
  const aDate = {};
  const plan = {};
  const quantity = 10;

  if (summer()) {
    charge = summerCharge();
  } else {
    charge = regularCharge();
  }

  function summer() {
    return !aDate.isBefore(plan.summerStart) && !aDate.isAfter(plan.summerEnd);
  }

  function summerCharge() {
    return quantity * plan.summerRate;
  }

  function regularCharge() {
    return quantity * plan.regularRate + plan.regularServiceCharge;
  }
}

function version4() {
  let charge;
  const aDate = {};
  const plan = {};
  const quantity = 10;

  charge = summer() ? summerCharge() : regularCharge();

  function summer() {
    return !aDate.isBefore(plan.summerStart) && !aDate.isAfter(plan.summerEnd);
  }

  function summerCharge() {
    return quantity * plan.summerRate;
  }

  function regularCharge() {
    return quantity * plan.regularRate + plan.regularServiceCharge;
  }
}
