function verison1() {
  function dateToday() {
    return new Date();
  }

  class CustomerContract {
    constructor(startDate) {
      this._startDate = startDate;
    }
  }

  class Customer {
    constructor(name, discountRate) {
      this._name = name;
      this._discountRate = discountRate;
      this._contract = new CustomerContract(dateToday());
    }

    get discountRate() { return this._discountRate; }

    becomePreferred() {
      this._discountRate += 0.03;
    }

    applyDiscount(amount) {
      return amount.subtract(amount.multiply(this._discountRate));
    }
  }
}

function verison2() {
  function dateToday() {
    return new Date();
  }

  class CustomerContract {
    constructor(startDate) {
      this._startDate = startDate;
    }
  }

  class Customer {
    constructor(name, discountRate) {
      this._name = name;
      this._setDiscountRate(discountRate);
      this._contract = new CustomerContract(dateToday());
    }

    get discountRate() { return this._discountRate; }
    _setDiscountRate(aNumber) { this._discountRate = aNumber; }

    becomePreferred() {
      this._setDiscountRate(this.discountRate + 0.03);
    }

    applyDiscount(amount) {
      return amount.subtract(amount.multiply(this.discountRate));
    }
  }
}

function verison3() {
  function dateToday() {
    return new Date();
  }

  class CustomerContract {
    constructor(startDate, discountRate) {
      this._startDate = startDate;
      this._discountRate = discountRate;
    }

    get discountRate() { return this._discountRate; }
    set discountRate(arg) { this._discountRate = arg; }
  }

  class Customer {
    constructor(name, discountRate) {
      this._name = name;
      this._setDiscountRate(discountRate);
      this._contract = new CustomerContract(dateToday());
    }

    get discountRate() { return this._discountRate; }
    _setDiscountRate(aNumber) { this._discountRate = aNumber; }

    becomePreferred() {
      this._setDiscountRate(this.discountRate + 0.03);
    }

    applyDiscount(amount) {
      return amount.subtract(amount.multiply(this.discountRate));
    }
  }
}
function verison4() {
  function dateToday() {
    return new Date();
  }

  class CustomerContract {
    constructor(startDate, discountRate) {
      this._startDate = startDate;
      this._discountRate = discountRate;
    }

    get discountRate() { return this._discountRate; }
    set discountRate(arg) { this._discountRate = arg; }
  }

  class Customer {
    constructor(name, discountRate) {
      this._name = name;
      this._contract = new CustomerContract(dateToday());
      this._setDiscountRate(discountRate);
    }

    get discountRate() { return this._contract.discountRate; }
    _setDiscountRate(aNumber) { this._contract.discountRate = aNumber; }

    becomePreferred() {
      this._setDiscountRate(this.discountRate + 0.03);
    }

    applyDiscount(amount) {
      return amount.subtract(amount.multiply(this.discountRate));
    }
  }
}
