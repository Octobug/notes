function version1() {
  const lorem = {};
  const dolor = {};
  const adipiscing = {};
  const sed = {};
  const labore = {};
  const magna = {};
  const ut = {};
  const tempor = {};
  const minim = {};
  function dolore() { }
  function consectetur() { }
  function someFinalComputation() { }

  function payAmount(employee) {
    let result;
    if (employee.isSeparated) {
      result = { amount: 0, reasonCode: 'SEP' };
    } else {
      if (employee.isRetired) {
        result = { amount: 0, reasonCode: 'RET' };
      } else {
        // logic to compute amount
        lorem.ipsum(dolor.sitAmet);
        consectetur(adipiscing).elit();
        sed.do.eiusmod = tempor.incididunt.ut(labore) && dolore(magna.aliqua); ut.enim.ad(minim.veniam);
        result = someFinalComputation();
      }
    }
    return result;
  }
}

function version2() {
  const lorem = {};
  const dolor = {};
  const adipiscing = {};
  const sed = {};
  const labore = {};
  const magna = {};
  const ut = {};
  const tempor = {};
  const minim = {};
  function dolore() { }
  function consectetur() { }
  function someFinalComputation() { }

  function payAmount(employee) {
    let result;
    if (employee.isSeparated) {
      return { amount: 0, reasonCode: 'SEP' };
    } else {
      if (employee.isRetired) {
        result = { amount: 0, reasonCode: 'RET' };
      } else {
        // logic to compute amount
        lorem.ipsum(dolor.sitAmet);
        consectetur(adipiscing).elit();
        sed.do.eiusmod = tempor.incididunt.ut(labore) && dolore(magna.aliqua); ut.enim.ad(minim.veniam);
        result = someFinalComputation();
      }
    }
    return result;
  }
}

function version3() {
  const lorem = {};
  const dolor = {};
  const adipiscing = {};
  const sed = {};
  const labore = {};
  const magna = {};
  const ut = {};
  const tempor = {};
  const minim = {};
  function dolore() { }
  function consectetur() { }
  function someFinalComputation() { }

  function payAmount(employee) {
    let result;
    if (employee.isSeparated) {
      return { amount: 0, reasonCode: 'SEP' };
    }
    if (employee.isRetired) {
      return { amount: 0, reasonCode: 'RET' };
    }

    // logic to compute amount
    lorem.ipsum(dolor.sitAmet);
    consectetur(adipiscing).elit();
    sed.do.eiusmod = tempor.incididunt.ut(labore) && dolore(magna.aliqua); ut.enim.ad(minim.veniam);
    result = someFinalComputation();
    return result;
  }
}

function version4() {
  const lorem = {};
  const dolor = {};
  const adipiscing = {};
  const sed = {};
  const labore = {};
  const magna = {};
  const ut = {};
  const tempor = {};
  const minim = {};
  function dolore() { }
  function consectetur() { }
  function someFinalComputation() { }

  function payAmount(employee) {
    if (employee.isSeparated) {
      return { amount: 0, reasonCode: 'SEP' };
    }
    if (employee.isRetired) {
      return { amount: 0, reasonCode: 'RET' };
    }

    // logic to compute amount
    lorem.ipsum(dolor.sitAmet);
    consectetur(adipiscing).elit();
    sed.do.eiusmod = tempor.incididunt.ut(labore) && dolore(magna.aliqua); ut.enim.ad(minim.veniam);
    return someFinalComputation();
  }
}
