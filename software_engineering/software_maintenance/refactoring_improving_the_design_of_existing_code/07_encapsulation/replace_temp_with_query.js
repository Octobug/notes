function version1() {
  class Order {
    constructor(quantity, item) {
      this._quantity = quantity;
      this._item = item;
    }

    get price() {
      var basePrice = this._quantity * this._item.price;
      var discountFactor = 0.98;
      if (basePrice > 1000) {
        discountFactor -= 0.03;
      }
      return basePrice * discountFactor;
    }
  }
}

function version2() {
  class Order {
    constructor(quantity, item) {
      this._quantity = quantity;
      this._item = item;
    }

    get basePrice() {
      return this._quantity * this._item.price;
    }

    get price() {
      var discountFactor = 0.98;
      if (this.basePrice > 1000) {
        discountFactor -= 0.03;
      }
      return this.basePrice * discountFactor;
    }
  }
}

function version3() {
  class Order {
    constructor(quantity, item) {
      this._quantity = quantity;
      this._item = item;
    }

    get basePrice() {
      return this._quantity * this._item.price;
    }

    get discountFactor() {
      let discountFactor = 0.98;
      if (this.basePrice > 1000) {
        discountFactor -= 0.03;
      }
      return discountFactor;
    }

    get price() {
      return this.basePrice * this.discountFactor;
    }
  }
}
