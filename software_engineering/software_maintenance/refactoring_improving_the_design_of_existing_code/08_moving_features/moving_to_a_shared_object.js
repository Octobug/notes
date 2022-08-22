const assert = require('assert');


function version1() {
  class Account {
    constructor(number, type, interestRate) {
      this._number = number;
      this._type = type;
      this._interestRate = interestRate;
    }

    get interestRate() { return this._interestRate; }
  }

  class AccountType {
    constructor(nameString) {
      this._name = nameString;
    }
  }
}

function version2() {
  class Account {
    constructor(number, type, interestRate) {
      this._number = number;
      this._type = type;
      assert(interestRate === this._type.interestRate);
      this._interestRate = interestRate;
    }

    get interestRate() { return this._interestRate; }
  }

  class AccountType {
    constructor(nameString, interestRate) {
      this._name = nameString;
      this._interestRate = interestRate;
    }

    get interestRate() { return this._interestRate; }
  }
}

function version3() {
  class Account {
    constructor(number, type) {
      this._number = number;
      this._type = type;
    }

    get interestRate() { return this._type.interestRate; }
  }

  class AccountType {
    constructor(nameString, interestRate) {
      this._name = nameString;
      this._interestRate = interestRate;
    }

    get interestRate() { return this._interestRate; }
  }
}
