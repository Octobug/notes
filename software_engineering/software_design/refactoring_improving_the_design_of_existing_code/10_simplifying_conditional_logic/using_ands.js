function version1() {
  const anEmployee = {};
  if (anEmployee.onVacation) {
    if (anEmployee.seniority > 10) {
      return 1;
    }
  }
  return 0.5;
}

function version2() {
  const anEmployee = {};
  if ((anEmployee.onVacation)
    && (anEmployee.seniority > 10)) {
    return 1;
  }
  return 0.5;
}
