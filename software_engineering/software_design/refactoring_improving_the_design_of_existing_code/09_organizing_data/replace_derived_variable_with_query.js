const assert = require('assert');


function version1() {
  class ProductionPlan {
    get production() { return this._production; }
    applyAdjustment(anAdjustment) {
      this._adjustments.push(anAdjustment);
      this._production += anAdjustment.amount;
    }
  }
}

function version2() {
  class ProductionPlan {
    get production() {
      assert(this._production === this.calculatedProduction);
      return this._production;
    }

    get calculatedProduction() {
      return this._adjustments.reduce((sum, a) => sum + a.amount, 0);
    }

    applyAdjustment(anAdjustment) {
      this._adjustments.push(anAdjustment);
      this._production += anAdjustment.amount;
    }
  }
}

function version3() {
  class ProductionPlan {
    get production() {
      return this.calculatedProduction;
    }

    get calculatedProduction() {
      return this._adjustments.reduce((sum, a) => sum + a.amount, 0);
    }

    applyAdjustment(anAdjustment) {
      this._adjustments.push(anAdjustment);
      this._production += anAdjustment.amount;
    }
  }
}

function version4() {
  class ProductionPlan {
    get production() {
      return this._adjustments.reduce((sum, a) => sum + a.amount, 0);
    }

    applyAdjustment(anAdjustment) {
      this._adjustments.push(anAdjustment);
    }
  }
}
