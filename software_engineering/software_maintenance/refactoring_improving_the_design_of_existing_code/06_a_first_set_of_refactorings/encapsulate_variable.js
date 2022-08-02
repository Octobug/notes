const assert = require('assert');

function version1() {
  let defaultOwner = { firstName: 'Martin', lastName: 'Fowler' };

  const spaceship = {};
  spaceship.owner = defaultOwner;

  defaultOwner = { firstName: 'Rebecca', lastName: 'Parsons' };
}

function version2() {
  let defaultOwner = { firstName: 'Martin', lastName: 'Fowler' };

  const spaceship = {};
  spaceship.owner = getDefaultOwner();

  setDefaultOwner({ firstName: 'Rebecca', lastName: 'Parsons' });

  function getDefaultOwner() { return defaultOwner; }
  function setDefaultOwner(arg) { defaultOwner = arg; }
}

function version3() {
  // default_owner.js
  let defaultOwner = { firstName: 'Martin', lastName: 'Fowler' };
  // export
  function getDefaultOwner() { return defaultOwner; }
  // export
  function setDefaultOwner(arg) { defaultOwner = arg; }
  // main.js
  const spaceship = {};
  spaceship.owner = getDefaultOwner();
  setDefaultOwner({ firstName: 'Rebecca', lastName: 'Parsons' });
}

function version4() {
  // default_owner.js
  let defaultOwnerData = { firstName: 'Martin', lastName: 'Fowler' };
  // export
  function defaultOwner() { return defaultOwnerData; }
  // export
  function setDefaultOwner(arg) { defaultOwnerData = arg; }

  // main.js
  const spaceship = {};
  spaceship.owner = defaultOwner();
  setDefaultOwner({ firstName: 'Rebecca', lastName: 'Parsons' });
}

function version5() {
  // default_owner.js
  let defaultOwnerData = { firstName: 'Martin', lastName: 'Fowler' };
  // export
  function defaultOwner() { return defaultOwnerData; }
  // export
  function setDefaultOwner(arg) { defaultOwnerData = arg; }

  // main.js
  const owner1 = defaultOwner();
  assert.equal('Fowler', owner1.lastName, 'when set');
  const owner2 = defaultOwner();
  owner2.lastName = 'Parsons';
  assert.equal('Parsons', owner1.lastName, 'after change owner2'); // is this ok?
}

function version6() {
  // default_owner.js
  let defaultOwnerData = { firstName: 'Martin', lastName: 'Fowler' };
  // export
  function defaultOwner() { return Object.assign({}, defaultOwnerData); }
  // export
  function setDefaultOwner(arg) { defaultOwnerData = arg; }

  // main.js
  const owner1 = defaultOwner();
  assert.equal('Fowler', owner1.lastName, 'when set');
  const owner2 = defaultOwner();
  owner2.lastName = 'Parsons';
  assert.equal('Parsons', owner1.lastName, 'after change owner2'); // is this ok?
}

function version7() {
  // default_owner.js
  let defaultOwnerData = { firstName: 'Martin', lastName: 'Fowler' };
  // export
  function defaultOwner() { return new Person(defaultOwnerData); }
  // export
  function setDefaultOwner(arg) { defaultOwnerData = arg; }

  class Person {
    constructor(data) {
      this._lastName = data.lastName;
      this._firstName = data.firstName;
    }
    get lastName() { return this._lastName; }
    get firstName() { return this._firstName; }
  }

  // main.js
  const owner1 = defaultOwner();
  assert.equal('Fowler', owner1.lastName, 'when set');
  const owner2 = defaultOwner();
  owner2.lastName = 'Parsons';
  assert.equal('Parsons', owner1.lastName, 'after change owner2'); // is this ok?
}
