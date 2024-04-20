function version1() {
  const thermostat = {};

  class HeatingPlan {
    get targetTemperature() {
      if (thermostat.selectedTemperature > this._max) {
        return this._max;
      } else if (thermostat.selectedTemperature < this._min) {
        return this._min;
      } else {
        return thermostat.selectedTemperature;
      }
    }
  }

  const thePlan = new HeatingPlan();
  if (thePlan.targetTemperature > thermostat.currentTemperature) {
    setToHeat();
  } else if (thePlan.targetTemperature < thermostat.currentTemperature) {
    setToCool();
  } else {
    setOff();
  }

  function setToHeat() { }
  function setToCool() { }
  function setOff() { }
}

function version2() {
  const thermostat = {};

  class HeatingPlan {
    get targetTemperature() {
      const selectedTemperature = thermostat.selectedTemperature;
      if (selectedTemperature > this._max) {
        return this._max;
      } else if (selectedTemperature < this._min) {
        return this._min;
      } else {
        return selectedTemperature;
      }
    }
  }

  const thePlan = new HeatingPlan();
  if (thePlan.targetTemperature > thermostat.currentTemperature) {
    setToHeat();
  } else if (thePlan.targetTemperature < thermostat.currentTemperature) {
    setToCool();
  } else {
    setOff();
  }

  function setToHeat() { }
  function setToCool() { }
  function setOff() { }
}

function version3() {
  const thermostat = {};

  class HeatingPlan {
    get targetTemperature() {
      const selectedTemperature = thermostat.selectedTemperature;
      return this.xxNEWtargetTemperature(selectedTemperature);
    }

    xxNEWtargetTemperature(selectedTemperature) {
      if (selectedTemperature > this._max) {
        return this._max;
      } else if (selectedTemperature < this._min) {
        return this._min;
      } else {
        return selectedTemperature;
      }
    }
  }

  const thePlan = new HeatingPlan();
  if (thePlan.targetTemperature > thermostat.currentTemperature) {
    setToHeat();
  } else if (thePlan.targetTemperature < thermostat.currentTemperature) {
    setToCool();
  } else {
    setOff();
  }

  function setToHeat() { }
  function setToCool() { }
  function setOff() { }
}

function version4() {
  const thermostat = {};

  class HeatingPlan {
    get targetTemperature() {
      return this.xxNEWtargetTemperature(thermostat.selectedTemperature);
    }

    xxNEWtargetTemperature(selectedTemperature) {
      if (selectedTemperature > this._max) {
        return this._max;
      } else if (selectedTemperature < this._min) {
        return this._min;
      } else {
        return selectedTemperature;
      }
    }
  }

  const thePlan = new HeatingPlan();
  if (thePlan.xxNEWtargetTemperature(thermostat.selectedTemperature)
    > thermostat.currentTemperature) {
    setToHeat();
  } else if (thePlan.xxNEWtargetTemperature(thermostat.selectedTemperature)
    < thermostat.currentTemperature) {
    setToCool();
  } else {
    setOff();
  }

  function setToHeat() { }
  function setToCool() { }
  function setOff() { }
}

function version5() {
  const thermostat = {};

  class HeatingPlan {
    targetTemperature(selectedTemperature) {
      if (selectedTemperature > this._max) {
        return this._max;
      } else if (selectedTemperature < this._min) {
        return this._min;
      } else {
        return selectedTemperature;
      }
    }
  }

  const thePlan = new HeatingPlan();
  if (thePlan.targetTemperature(thermostat.selectedTemperature)
    > thermostat.currentTemperature) {
    setToHeat();
  } else if (thePlan.targetTemperature(thermostat.selectedTemperature)
    < thermostat.currentTemperature) {
    setToCool();
  } else {
    setOff();
  }

  function setToHeat() { }
  function setToCool() { }
  function setOff() { }
}
