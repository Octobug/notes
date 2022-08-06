function version1() {
  function baseRate(month, year) {
    return (month + year) * 0.01;
  }

  const reading = { customer: 'ivan', quantity: 10, month: 5, year: 2017 };

  function acquireReading() {
    return reading;
  }

  function client1() {
    const aReading = acquireReading();
    const baseCharge = baseRate(aReading.month, aReading.year) * aReading.quantity;
  }

  function client2() {
    const aReading = acquireReading();
    const base = (baseRate(aReading.month, aReading.year) * aReading.quantity);
    const texableCharge = Math.max(0, base - taxThreshold(aReading.year));

    function taxThreshold(year) {
      return 0.01 * year;
    }
  }

  function client3() {
    const aReading = acquireReading();
    const basicChargeAmount = calculateBaseCharge(aReading);

    function calculateBaseCharge(aReading) {
      return baseRate(aReading.month, aReading.year) * aReading.quantity;
    }
  }
}

function version2() {
  const lodash = {};
  const _ = lodash;

  function baseRate(month, year) {
    return (month + year) * 0.01;
  }

  const reading = { customer: 'ivan', quantity: 10, month: 5, year: 2017 };

  function acquireReading() {
    return reading;
  }

  function enrichReading(original) {
    const result = _.cloneDeep(original);
    return result;
  }

  function client1() {
    const aReading = acquireReading();
    const baseCharge = baseRate(aReading.month, aReading.year) * aReading.quantity;
  }

  function client2() {
    const aReading = acquireReading();
    const base = (baseRate(aReading.month, aReading.year) * aReading.quantity);
    const texableCharge = Math.max(0, base - taxThreshold(aReading.year));

    function taxThreshold(year) {
      return 0.01 * year;
    }
  }

  function client3() {
    const rawReading = acquireReading();
    const aReading = enrichReading(rawReading);
    const basicChargeAmount = calculateBaseCharge(aReading);

    function calculateBaseCharge(aReading) {
      return baseRate(aReading.month, aReading.year) * aReading.quantity;
    }
  }
}

function version3() {
  const lodash = {};
  const _ = lodash;

  function baseRate(month, year) {
    return (month + year) * 0.01;
  }

  const reading = { customer: 'ivan', quantity: 10, month: 5, year: 2017 };

  function acquireReading() {
    return reading;
  }

  function enrichReading(original) {
    function calculateBaseCharge(aReading) {
      return baseRate(aReading.month, aReading.year) * aReading.quantity;
    }

    const result = _.cloneDeep(original);
    result.baseCharge = calculateBaseCharge(result);
    return result;
  }

  function client1() {
    const rawReading = acquireReading();
    const aReading = enrichReading(rawReading);
    const baseCharge = aReading.baseCharge;
  }

  function client2() {
    const aReading = acquireReading();
    const base = (baseRate(aReading.month, aReading.year) * aReading.quantity);
    const texableCharge = Math.max(0, base - taxThreshold(aReading.year));

    function taxThreshold(year) {
      return 0.01 * year;
    }
  }

  function client3() {
    const rawReading = acquireReading();
    const aReading = enrichReading(rawReading);
    const basicChargeAmount = aReading.baseCharge;
  }
}

function version4() {
  const lodash = {};
  const _ = lodash;

  function baseRate(month, year) {
    return (month + year) * 0.01;
  }

  const reading = { customer: 'ivan', quantity: 10, month: 5, year: 2017 };

  function acquireReading() {
    return reading;
  }

  function enrichReading(original) {
    function calculateBaseCharge(aReading) {
      return baseRate(aReading.month, aReading.year) * aReading.quantity;
    }

    function taxThreshold(year) {
      return 0.01 * year;
    }

    const result = _.cloneDeep(original);
    result.baseCharge = calculateBaseCharge(result);
    result.texableCharge = Math.max(0, result.baseCharge - taxThreshold(result.year));
    return result;
  }

  function client1() {
    const rawReading = acquireReading();
    const aReading = enrichReading(rawReading);
    const baseCharge = aReading.baseCharge;
  }

  function client2() {
    const rawReading = acquireReading();
    const aReading = enrichReading(rawReading);
    const texableCharge = aReading.texableCharge;
  }

  function client3() {
    const rawReading = acquireReading();
    const aReading = enrichReading(rawReading);
    const basicChargeAmount = aReading.baseCharge;
  }
}
