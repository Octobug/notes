function version1() {
  function disabilityAmount(anEmployee) {
    if (anEmployee.seniority < 2) return 0;
    if (anEmployee.monthsDisabled > 12) return 0;
    if (anEmployee.isPartTime) return 0;
    // compute the disability amount
  }
}

function version2() {
  function disabilityAmount(anEmployee) {
    if ((anEmployee.seniority < 2)
      || (anEmployee.monthsDisabled > 12)) return 0;
    if (anEmployee.isPartTime) return 0;
    // compute the disability amount
  }
}

function version3() {
  function disabilityAmount(anEmployee) {
    if ((anEmployee.seniority < 2)
      || (anEmployee.monthsDisabled > 12)
      || (anEmployee.isPartTime)) return 0;
    // compute the disability amount
  }
}

function version4() {
  function disabilityAmount(anEmployee) {
    if (isNotEligibleForDisability(anEmployee)) return 0;
    // compute the disability amount
  }

  function isNotEligibleForDisability(anEmployee) {
    return ((anEmployee.seniority < 2)
      || (anEmployee.monthsDisabled > 12)
      || (anEmployee.isPartTime));
  }
}
