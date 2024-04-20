function version1() {
  class Account {
    get daysOverdrawn() {
      return this._daysOverdrawn;
    }

    get bankCharge() {
      let result = 4.5;
      if (this._daysOverdrawn > 0) {
        result += this.overdraftCharge;
      }
      return result;
    }

    get overdraftCharge() {
      if (this.type.isPremium) {
        const baseCharge = 10;
        if (this.daysOverdrawn <= 7) {
          return baseCharge;
        } {
          return baseCharge + (this.daysOverdrawn - 7) * 0.85;
        }
      } else {
        return this.daysOverdrawn * 1.75;
      }
    }
  }
}

function version2() {
  class Account {
    get daysOverdrawn() {
      return this._daysOverdrawn;
    }

    get bankCharge() {
      let result = 4.5;
      if (this._daysOverdrawn > 0) {
        result += this.overdraftCharge;
      }
      return result;
    }

    get overdraftCharge() {
      if (this.type.isPremium) {
        const baseCharge = 10;
        if (this.daysOverdrawn <= 7) {
          return baseCharge;
        } {
          return baseCharge + (this.daysOverdrawn - 7) * 0.85;
        }
      } else {
        return this.daysOverdrawn * 1.75;
      }
    }
  }

  class AccountType {
    overdraftCharge(daysOverdrawn) {
      if (this.isPremium) {
        const baseCharge = 10;
        if (daysOverdrawn <= 7) {
          return baseCharge;
        } {
          return baseCharge + (daysOverdrawn - 7) * 0.85;
        }
      } else {
        return daysOverdrawn * 1.75;
      }
    }
  }
}

function version3() {
  class Account {
    get daysOverdrawn() {
      return this._daysOverdrawn;
    }

    get bankCharge() {
      let result = 4.5;
      if (this._daysOverdrawn > 0) {
        result += this.overdraftCharge;
      }
      return result;
    }

    get overdraftCharge() {
      return this.type.overdraftCharge(this.daysOverdrawn);
    }
  }

  class AccountType {
    overdraftCharge(daysOverdrawn) {
      if (this.isPremium) {
        const baseCharge = 10;
        if (daysOverdrawn <= 7) {
          return baseCharge;
        } {
          return baseCharge + (daysOverdrawn - 7) * 0.85;
        }
      } else {
        return daysOverdrawn * 1.75;
      }
    }
  }
}

function version4() {
  class Account {
    get daysOverdrawn() {
      return this._daysOverdrawn;
    }

    get bankCharge() {
      let result = 4.5;
      if (this._daysOverdrawn > 0) {
        result += this.type.overdraftCharge(this.daysOverdrawn);
      }
      return result;
    }
  }

  class AccountType {
    overdraftCharge(daysOverdrawn) {
      if (this.isPremium) {
        const baseCharge = 10;
        if (daysOverdrawn <= 7) {
          return baseCharge;
        } {
          return baseCharge + (daysOverdrawn - 7) * 0.85;
        }
      } else {
        return daysOverdrawn * 1.75;
      }
    }
  }
}

function version5() {
  class Account {
    get daysOverdrawn() {
      return this._daysOverdrawn;
    }

    get bankCharge() {
      let result = 4.5;
      if (this._daysOverdrawn > 0) {
        result += this.overdraftCharge;
      }
      return result;
    }

    get overdraftCharge() {
      return this.type.overdraftCharge(this);
    }
  }

  class AccountType {
    overdraftCharge(account) {
      if (this.isPremium) {
        const baseCharge = 10;
        if (account.daysOverdrawn <= 7) {
          return baseCharge;
        } {
          return baseCharge + (account.daysOverdrawn - 7) * 0.85;
        }
      } else {
        return account.daysOverdrawn * 1.75;
      }
    }
  }
}
