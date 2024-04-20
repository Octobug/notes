function version1() {
  class Person {
    constructor(name) {
      this._name = name;
    }
    get name() { return this._name; }
    get genderCode() { return 'X'; }
    // snip
  }

  class Male extends Person {
    get genderCode() { return 'M'; }
  }

  class Female extends Person {
    get genderCode() { return 'F'; }
  }

  function loadFromInput(data) {
    const result = [];
    data.forEach(aRecord => {
      let p;
      switch (aRecord.gender) {
        case 'M': p = new Male(aRecord.name); break;
        case 'F': p = new Female(aRecord.name); break;
        default: p = new Person(aRecord.name);
      }
      result.push(p);
    });
    return result;
  }

  const people = [];
  const numberOfMales = people.filter(p => p instanceof Male).length;
}

function version2() {
  class Person {
    constructor(name) {
      this._name = name;
    }
    get name() { return this._name; }
    get genderCode() { return 'X'; }
    // snip
  }

  class Male extends Person {
    get genderCode() { return 'M'; }
  }

  class Female extends Person {
    get genderCode() { return 'F'; }
  }

  function createPerson(aRecord) {
    let p;
    switch (aRecord.gender) {
      case 'M': p = new Male(aRecord.name); break;
      case 'F': p = new Female(aRecord.name); break;
      default: p = new Person(aRecord.name);
    }
    return p;
  }

  function loadFromInput(data) {
    const result = [];
    data.forEach(aRecord => {
      result.push(createPerson(aRecord));
    });
    return result;
  }

  const people = [];
  const numberOfMales = people.filter(p => p instanceof Male).length;
}

function version3() {
  class Person {
    constructor(name) {
      this._name = name;
    }
    get name() { return this._name; }
    get genderCode() { return 'X'; }
    // snip
  }

  class Male extends Person {
    get genderCode() { return 'M'; }
  }

  class Female extends Person {
    get genderCode() { return 'F'; }
  }

  function createPerson(aRecord) {
    switch (aRecord.gender) {
      case 'M': return new Male(aRecord.name);
      case 'F': return new Female(aRecord.name);
      default: return new Person(aRecord.name);
    }
  }

  function loadFromInput(data) {
    return data.map(aRecord => createPerson(aRecord));
  }

  const people = [];
  const numberOfMales = people.filter(p => p instanceof Male).length;
}

function version4() {
  class Person {
    constructor(name) {
      this._name = name;
    }
    get name() { return this._name; }
    get genderCode() { return 'X'; }
    // snip
  }

  class Male extends Person {
    get genderCode() { return 'M'; }
  }

  class Female extends Person {
    get genderCode() { return 'F'; }
  }

  function createPerson(aRecord) {
    switch (aRecord.gender) {
      case 'M': return new Male(aRecord.name);
      case 'F': return new Female(aRecord.name);
      default: return new Person(aRecord.name);
    }
  }

  function loadFromInput(data) {
    return data.map(aRecord => createPerson(aRecord));
  }

  function isMale(aPerson) { return aPerson instanceof Male; }

  const people = [];
  const numberOfMales = people.filter(p => isMale(p)).length;
}

function version5() {
  class Person {
    constructor(name) {
      this._name = name;
    }
    get name() { return this._name; }
    get genderCode() { return 'X'; }
    get isMale() { return this instanceof Male; }
    // snip
  }

  class Male extends Person {
    get genderCode() { return 'M'; }
  }

  class Female extends Person {
    get genderCode() { return 'F'; }
  }

  function createPerson(aRecord) {
    switch (aRecord.gender) {
      case 'M': return new Male(aRecord.name);
      case 'F': return new Female(aRecord.name);
      default: return new Person(aRecord.name);
    }
  }

  function loadFromInput(data) {
    return data.map(aRecord => createPerson(aRecord));
  }

  const people = [];
  const numberOfMales = people.filter(p => p.isMale).length;
}

function version6() {
  class Person {
    constructor(name, genderCode) {
      this._name = name;
      this._genderCode = genderCode || 'X';
    }
    get name() { return this._name; }
    get genderCode() { return this._genderCode; }
    get isMale() { return 'M' === this._genderCode; }
    // snip
  }

  class Female extends Person {
    get genderCode() { return 'F'; }
  }

  function createPerson(aRecord) {
    switch (aRecord.gender) {
      case 'M': return new Person(aRecord.name, 'M');
      case 'F': return new Female(aRecord.name);
      default: return new Person(aRecord.name);
    }
  }

  function loadFromInput(data) {
    return data.map(aRecord => createPerson(aRecord));
  }

  const people = [];
  const numberOfMales = people.filter(p => p.isMale).length;
}

function version7() {
  class Person {
    constructor(name, genderCode) {
      this._name = name;
      this._genderCode = genderCode || 'X';
    }
    get name() { return this._name; }
    get genderCode() { return this._genderCode; }
    get isMale() { return 'M' === this._genderCode; }
    // snip
  }

  function createPerson(aRecord) {
    switch (aRecord.gender) {
      case 'M': return new Person(aRecord.name, 'M');
      case 'F': return new Person(aRecord.name, 'F');
      default: return new Person(aRecord.name);
    }
  }

  function loadFromInput(data) {
    return data.map(aRecord => createPerson(aRecord));
  }

  const people = [];
  const numberOfMales = people.filter(p => p.isMale).length;
}

function version8() {
  class Person {
    constructor(name, genderCode) {
      this._name = name;
      this._genderCode = genderCode;
    }
    get name() { return this._name; }
    get genderCode() { return this._genderCode; }
    get isMale() { return 'M' === this._genderCode; }
    // snip
  }

  function createPerson(aRecord) {
    switch (aRecord.gender) {
      case 'M': return new Person(aRecord.name, 'M');
      case 'F': return new Person(aRecord.name, 'F');
      default: return new Person(aRecord.name, 'X');
    }
  }

  function loadFromInput(data) {
    return data.map(aRecord => createPerson(aRecord));
  }

  const people = [];
  const numberOfMales = people.filter(p => p.isMale).length;
}
