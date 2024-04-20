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
  class Reading {
    constructor(data) {
      this._customer = data.customer;
      this._quantity = data.quantity;
      this._month = data.month;
      this._year = data.year;
    }

    get customer() { return this._customer; }
    get quantity() { return this._quantity; }
    get month() { return this._month; }
    get year() { return this._year; }

    get baseCharge() {
      return baseRate(this.month, this.year) * this.quantity;
    }
  }

  function baseRate(month, year) {
    return (month + year) * 0.01;
  }

  const reading = { customer: 'ivan', quantity: 10, month: 5, year: 2017 };

  function acquireReading() {
    return reading;
  }

  function client1() {
    const rawReading = acquireReading();
    const aReading = new Reading(rawReading);
    const baseCharge = aReading.baseCharge;
  }

  function client2() {
    const rawReading = acquireReading();
    const aReading = new Reading(rawReading);
    const texableCharge = Math.max(0, aReading.baseCharge - taxThreshold(aReading.year));

    function taxThreshold(year) {
      return 0.01 * year;
    }
  }

  function client3() {
    const rawReading = acquireReading();
    const aReading = new Reading(rawReading);
    const basicChargeAmount = aReading.baseCharge;
  }
}

function version3() {
  function taxThreshold(year) {
    return 0.01 * year;
  }

  class Reading {
    constructor(data) {
      this._customer = data.customer;
      this._quantity = data.quantity;
      this._month = data.month;
      this._year = data.year;
    }

    get customer() { return this._customer; }
    get quantity() { return this._quantity; }
    get month() { return this._month; }
    get year() { return this._year; }

    get baseCharge() {
      return baseRate(this.month, this.year) * this.quantity;
    }

    get taxableCharge() {
      return Math.max(0, this.baseCharge - taxThreshold(this.year));
    }
  }

  function baseRate(month, year) {
    return (month + year) * 0.01;
  }

  const reading = { customer: 'ivan', quantity: 10, month: 5, year: 2017 };

  function acquireReading() {
    return reading;
  }

  function client1() {
    const rawReading = acquireReading();
    const aReading = new Reading(rawReading);
    const baseCharge = aReading.baseCharge;
  }

  function client2() {
    const rawReading = acquireReading();
    const aReading = new Reading(rawReading);
    const texableCharge = aReading.texableCharge;
  }

  function client3() {
    const rawReading = acquireReading();
    const aReading = new Reading(rawReading);
    const basicChargeAmount = aReading.baseCharge;
  }
}
