function version1() {
  const station = {
    name: 'ZB1',
    readings: [
      { temp: 47, time: '2016-11-10 09:10' },
      { temp: 53, time: '2016-11-10 09:20' },
      { temp: 58, time: '2016-11-10 09:30' },
      { temp: 53, time: '2016-11-10 09:40' },
      { temp: 51, time: '2016-11-10 09:50' },
    ]
  };

  function readingsOutsideRange(station, min, max) {
    return station.readings
      .filter(r => r.temp < min || r.temp > max);
  }

  const operatingPlan = {
    temperatureFloor: 50,
    temperatureCeiling: 55,
  };

  const alerts = readingsOutsideRange(
    station,
    operatingPlan.temperatureFloor,
    operatingPlan.temperatureCeiling
  );
}

function version2() {
  class NumberRange {
    constructor(min, max) {
      this._data = { min, max };
    }

    get min() { return this._data.min; }
    get max() { return this._data.max; }
  }

  const station = {
    name: 'ZB1',
    readings: [
      { temp: 47, time: '2016-11-10 09:10' },
      { temp: 53, time: '2016-11-10 09:20' },
      { temp: 58, time: '2016-11-10 09:30' },
      { temp: 53, time: '2016-11-10 09:40' },
      { temp: 51, time: '2016-11-10 09:50' },
    ]
  };

  function readingsOutsideRange(station, min, max, range) {
    return station.readings
      .filter(r => r.temp < min || r.temp > max);
  }

  const operatingPlan = {
    temperatureFloor: 50,
    temperatureCeiling: 55,
  };

  const range = new NumberRange(
    operatingPlan.temperatureFloor,
    operatingPlan.temperatureCeiling
  );

  const alerts = readingsOutsideRange(
    station,
    operatingPlan.temperatureFloor,
    operatingPlan.temperatureCeiling,
    range
  );
}

function version3() {
  class NumberRange {
    constructor(min, max) {
      this._data = { min, max };
    }

    get min() { return this._data.min; }
    get max() { return this._data.max; }
  }

  const station = {
    name: 'ZB1',
    readings: [
      { temp: 47, time: '2016-11-10 09:10' },
      { temp: 53, time: '2016-11-10 09:20' },
      { temp: 58, time: '2016-11-10 09:30' },
      { temp: 53, time: '2016-11-10 09:40' },
      { temp: 51, time: '2016-11-10 09:50' },
    ]
  };

  function readingsOutsideRange(station, range) {
    return station.readings
      .filter(r => r.temp < range.min || r.temp > range.max);
  }

  const operatingPlan = {
    temperatureFloor: 50,
    temperatureCeiling: 55,
  };

  const range = new NumberRange(
    operatingPlan.temperatureFloor,
    operatingPlan.temperatureCeiling
  );

  const alerts = readingsOutsideRange(station, range);
}

function version4() {
  class NumberRange {
    constructor(min, max) {
      this._data = { min, max };
    }

    get min() { return this._data.min; }
    get max() { return this._data.max; }

    contains(arg) { return (arg >= this.min && arg <= this.max); }
  }

  const station = {
    name: 'ZB1',
    readings: [
      { temp: 47, time: '2016-11-10 09:10' },
      { temp: 53, time: '2016-11-10 09:20' },
      { temp: 58, time: '2016-11-10 09:30' },
      { temp: 53, time: '2016-11-10 09:40' },
      { temp: 51, time: '2016-11-10 09:50' },
    ]
  };

  function readingsOutsideRange(station, range) {
    return station.readings
      .filter(r => range.contains(r.temp));
  }

  const operatingPlan = {
    temperatureFloor: 50,
    temperatureCeiling: 55,
  };

  const range = new NumberRange(
    operatingPlan.temperatureFloor,
    operatingPlan.temperatureCeiling
  );

  const alerts = readingsOutsideRange(station, range);
}
