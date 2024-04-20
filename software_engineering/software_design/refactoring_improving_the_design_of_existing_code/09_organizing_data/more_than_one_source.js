const assert = require('assert');


function version1() {
  class ProductionPlan {
    constructor(production) {
      this._production = production;
      this._adjustments = [];
    }

    get production() { return this._production; }

    applyAdjustment(anAdjustment) {
      this._adjustments.push(anAdjustment);
      this._production += anAdjustment.amount;
    }
  }
}

function version2() {
  class ProductionPlan {
    constructor(production) {
      this._initialProduction = production;
      this._productionAccumulator = 0;
      this._adjustments = [];
    }

    get production() {
      return this._initialProduction + this._productionAccumulator;
    }

    applyAdjustment(anAdjustment) {
      this._adjustments.push(anAdjustment);
      this._production += anAdjustment.amount;
    }
  }
}

function version3() {
  class ProductionPlan {
    constructor(production) {
      this._initialProduction = production;
      this._productionAccumulator = 0;
      this._adjustments = [];
    }

    get production() {
      assert(
        this._productionAccumulator === this.calculatedProductionAccumulator
      );
      return this._initialProduction + this._productionAccumulator;
    }

    get calculatedProductionAccumulator() {
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
    constructor(production) {
      this._initialProduction = production;
      this._adjustments = [];
    }

    get production() {
      return this._initialProduction + this.calculatedProductionAccumulator;
    }

    get calculatedProductionAccumulator() {
      return this._adjustments.reduce((sum, a) => sum + a.amount, 0);
    }

    applyAdjustment(anAdjustment) {
      this._adjustments.push(anAdjustment);
    }
  }
}
