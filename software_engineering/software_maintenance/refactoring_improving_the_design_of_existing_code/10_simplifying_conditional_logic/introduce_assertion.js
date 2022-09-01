const assert = require('assert');

function version1() {
  class Customer {
    applyDiscount(aNumber) {
      return (this.discountRate)
        ? aNumber - (this.discountRate * aNumber)
        : aNumber;
    }
  }
}

function version2() {
  class Customer {
    applyDiscount(aNumber) {
      if (!this.discountRate) {
        return aNumber;
      } else {
        assert(this.discountRate >= 0);
        return aNumber - (this.discountRate * aNumber);
      }
    }
  }
}

function version3() {
  class Customer {
    applyDiscount(aNumber) {
      if (!this.discountRate) {
        return aNumber;
      } else {
        return aNumber - (this.discountRate * aNumber);
      }
    }

    set discountRate(aNumber) {
      assert(null === aNumber || aNumber >= 0);
      this._discountRate = aNumber;
    }
  }
}
