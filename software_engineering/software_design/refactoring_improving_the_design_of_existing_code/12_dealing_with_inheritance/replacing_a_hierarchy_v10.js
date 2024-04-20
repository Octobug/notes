/* eslint-disable no-unused-vars */
function createBird(data) {
  return new Bird(data);
}

class Bird {
  constructor(data) {
    this._name = data.name;
    this._plumage = data.plumage;
    this._speciesDelegate = this.selectSpeciesDelegate(data);
  }
  get name() { return this._name; }
  get plumage() {
    return this._speciesDelegate.plumage;
  }
  get airSpeedVelocity() {
    return this._speciesDelegate.airSpeedVelocity;
  }

  selectSpeciesDelegate(data) {
    switch (data.type) {
      case 'EuropeanSwallow':
        return new EuropeanSwallowDelegate(data, this);
      case 'AfricanSwallow':
        return new AfricanSwallowDelegate(data, this);
      case 'NorwegianBlueParrot':
        return new NorwegianBlueParrotDelegate(data, this);
      default: return new SpeciesDelegate(data, this);
    }
  }
}

class SpeciesDelegate {
  constructor(data, bird) {
    this._bird = bird;
  }
  get plumage() {
    return this._bird._plumage || 'average';
  }
  get airSpeedVelocity() { return null; }
}

class EuropeanSwallowDelegate extends SpeciesDelegate {
  get airSpeedVelocity() { return 35; }
}

class AfricanSwallowDelegate extends SpeciesDelegate {
  constructor(data, bird) {
    super(data, bird);
    this._numberOfCoconuts = data.numberOfCoconuts;
  }

  get airSpeedVelocity() {
    return 40 - 2 * this._numberOfCoconuts;
  }
}

class NorwegianBlueParrotDelegate extends SpeciesDelegate {
  constructor(data, bird) {
    super(data, bird);
    this._voltage = data.voltage;
    this._isNailed = data.isNailed;
  }
  get airSpeedVelocity() {
    return (this._isNailed) ? 0 : 10 + this._voltage / 10;
  }
  get plumage() {
    if (this._voltage > 100) {
      return 'scorched';
    } else {
      return this._bird._plumage || 'beautiful';
    }
  }
}
