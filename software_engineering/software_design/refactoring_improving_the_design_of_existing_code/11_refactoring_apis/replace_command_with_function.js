function version1() {
  class ChargeCalculator {
    constructor(customer, usage, provider) {
      this._customer = customer;
      this._usage = usage;
      this._provider = provider;
    }
    get baseCharge() {
      return this._customer.baseRate * this._usage;
    }
    get charge() {
      return this.baseCharge + this._provider.connectionCharge;
    }
  }

  const customer = {};
  const usage = {};
  const provider = {};
  const monthCharge = new ChargeCalculator(customer, usage, provider).charge;
}

function version2() {
  class ChargeCalculator {
    constructor(customer, usage, provider) {
      this._customer = customer;
      this._usage = usage;
      this._provider = provider;
    }
    get baseCharge() {
      return this._customer.baseRate * this._usage;
    }
    get charge() {
      const baseCharge = this.baseCharge;
      return baseCharge + this._provider.connectionCharge;
    }
  }

  function charge(customer, usage, provider) {
    return new ChargeCalculator(customer, usage, provider).charge;
  }

  const customer = {};
  const usage = {};
  const provider = {};
  const monthCharge = charge(customer, usage, provider);
}

function version3() {
  class ChargeCalculator {
    charge(customer, usage, provider) {
      const baseCharge = customer.baseRate * usage;
      return baseCharge + provider.connectionCharge;
    }
  }

  function charge(customer, usage, provider) {
    return new ChargeCalculator().charge(customer, usage, provider);
  }

  const customer = {};
  const usage = {};
  const provider = {};
  const monthCharge = charge(customer, usage, provider);
}

function version4() {
  function charge(customer, usage, provider) {
    const baseCharge = customer.baseRate * usage;
    return baseCharge + provider.connectionCharge;
  }

  const customer = {};
  const usage = {};
  const provider = {};
  const monthCharge = charge(customer, usage, provider);
}
