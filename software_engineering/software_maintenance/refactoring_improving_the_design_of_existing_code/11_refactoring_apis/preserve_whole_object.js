function version1() {
  const aRoom = {};
  const aPlan = new HeatingPlan();
  const alerts = [];

  const low = aRoom.daysTempRange.low;
  const high = aRoom.daysTempRange.high;
  if (!aPlan.withinRange(low, high)) {
    alerts.push('room temperature went outside range');
  }

  class HeatingPlan {
    withinRange(bottom, top) {
      return (bottom >= this._temperatureRange.low) && (top <= this._temperatureRange.high);
    }
  }
}

function version2() {
  const aRoom = {};
  const aPlan = new HeatingPlan();
  const alerts = [];

  if (!aPlan.xxNEWwithinRange(aRoom.daysTempRange)) {
    alerts.push('room temperature went outside range');
  }

  class HeatingPlan {
    withinRange(bottom, top) {
      return (bottom >= this._temperatureRange.low) && (top <= this._temperatureRange.high);
    }

    xxNEWwithinRange(aNumberRange) {
      return this.withinRange(aNumberRange.low, aNumberRange.high);
    }
  }
}

function version3() {
  const aRoom = {};
  const aPlan = new HeatingPlan();
  const alerts = [];

  if (!aPlan.xxNEWwithinRange(aRoom.daysTempRange)) {
    alerts.push('room temperature went outside range');
  }

  class HeatingPlan {
    xxNEWwithinRange(aNumberRange) {
      return (aNumberRange.low >= this._temperatureRange.low)
        && (aNumberRange.top <= this._temperatureRange.high);
    }
  }
}

function version4() {
  const aRoom = {};
  const aPlan = new HeatingPlan();
  const alerts = [];

  if (!aPlan.withinRange(aRoom.daysTempRange)) {
    alerts.push('room temperature went outside range');
  }

  class HeatingPlan {
    withinRange(aNumberRange) {
      return (aNumberRange.low >= this._temperatureRange.low)
        && (aNumberRange.top <= this._temperatureRange.high);
    }
  }
}
