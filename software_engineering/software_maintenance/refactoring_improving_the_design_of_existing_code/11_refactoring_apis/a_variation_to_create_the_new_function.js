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
      return (bottom >= this._temperatureRange.low)
        && (top <= this._temperatureRange.high);
    }
  }
}

function version2() {
  const aRoom = {};
  const aPlan = new HeatingPlan();
  const alerts = [];

  const low = aRoom.daysTempRange.low;
  const high = aRoom.daysTempRange.high;
  const isWithinRange = aPlan.withinRange(low, high);
  if (!isWithinRange) {
    alerts.push('room temperature went outside range');
  }

  class HeatingPlan {
    withinRange(bottom, top) {
      return (bottom >= this._temperatureRange.low)
        && (top <= this._temperatureRange.high);
    }
  }
}

function version3() {
  const aRoom = {};
  const aPlan = new HeatingPlan();
  const alerts = [];

  const tempRange = aRoom.daysTempRange;
  const low = tempRange.low;
  const high = tempRange.high;
  const isWithinRange = aPlan.withinRange(low, high);
  if (!isWithinRange) {
    alerts.push('room temperature went outside range');
  }

  class HeatingPlan {
    withinRange(bottom, top) {
      return (bottom >= this._temperatureRange.low)
        && (top <= this._temperatureRange.high);
    }
  }
}

function version4() {
  const aRoom = {};
  const aPlan = new HeatingPlan();
  const alerts = [];

  const tempRange = aRoom.daysTempRange;
  const isWithinRange = xxNEWwithinRange(aPlan, tempRange);
  if (!isWithinRange) {
    alerts.push('room temperature went outside range');
  }

  class HeatingPlan {
    withinRange(bottom, top) {
      return (bottom >= this._temperatureRange.low)
        && (top <= this._temperatureRange.high);
    }
  }

  function xxNEWwithinRange(aPlan, tempRange) {
    const low = tempRange.low;
    const high = tempRange.high;
    const isWithinRange = aPlan.withinRange(low, high);
    return isWithinRange;
  }
}

function version5() {
  const aRoom = {};
  const aPlan = new HeatingPlan();
  const alerts = [];

  const tempRange = aRoom.daysTempRange;
  const isWithinRange = aPlan.xxNEWwithinRange(tempRange);
  if (!isWithinRange) {
    alerts.push('room temperature went outside range');
  }

  class HeatingPlan {
    withinRange(bottom, top) {
      return (bottom >= this._temperatureRange.low)
        && (top <= this._temperatureRange.high);
    }

    xxNEWwithinRange(tempRange) {
      const low = tempRange.low;
      const high = tempRange.high;
      const isWithinRange = this.withinRange(low, high);
      return isWithinRange;
    }
  }
}

function version6() {
  const aRoom = {};
  const aPlan = new HeatingPlan();
  const alerts = [];

  const tempRange = aRoom.daysTempRange;
  const isWithinRange = aPlan.xxNEWwithinRange(tempRange);
  if (!isWithinRange) {
    alerts.push('room temperature went outside range');
  }

  class HeatingPlan {
    xxNEWwithinRange(tempRange) {
      return (tempRange.low >= this._temperatureRange.low)
        && (tempRange.high <= this._temperatureRange.high);
    }
  }
}

function version7() {
  const aRoom = {};
  const aPlan = new HeatingPlan();
  const alerts = [];

  const tempRange = aRoom.daysTempRange;
  const isWithinRange = aPlan.withinRange(tempRange);
  if (!isWithinRange) {
    alerts.push('room temperature went outside range');
  }

  class HeatingPlan {
    withinRange(tempRange) {
      return (tempRange.low >= this._temperatureRange.low)
        && (tempRange.high <= this._temperatureRange.high);
    }
  }
}
