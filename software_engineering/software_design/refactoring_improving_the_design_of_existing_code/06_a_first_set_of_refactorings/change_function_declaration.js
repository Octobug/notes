const assert = require('assert');


function version1() {
  function circum(radius) {
    return 2 * Math.PI * radius;
  }
}

function version2() {
  function circumference(radius) {
    return 2 * Math.PI * radius;
  }
}

function version3() {
  function circum(radius) {
    return circumference(radius);
  }

  function circumference(radius) {
    return 2 * Math.PI * radius;
  }
}

function version4() {
  function circumference(radius) {
    return 2 * Math.PI * radius;
  }
}

function version5() {
  class Book {
    addReservation(customer) {
      this._reservations.push(customer);
    }
  }
}

function version6() {
  class Book {
    addReservation(customer) {
      this.zz_addReservation(customer);
    }

    zz_addReservation(customer) {
      this._reservations.push(customer);
    }
  }
}

function version7() {
  class Book {
    addReservation(customer) {
      this.zz_addReservation(customer, false);
    }

    zz_addReservation(customer, isPriority) {
      assert(isPriority === true || isPriority === false);
      this._reservations.push(customer);
    }
  }
}

function version8() {
  class Book {
    addReservation(customer, isPriority) {
      assert(isPriority === true || isPriority === false);
      this._reservations.push(customer);
    }
  }
}

function version9() {
  function inNewEngland(aCustomer) {
    return ['MA', 'CT', 'ME', 'VT', 'NH', 'RI'].includes(aCustomer.address.state);
  }

  const someCustomers = [];
  const newEnglanders = someCustomers.filter(c => inNewEngland(c));
}

function version10() {
  function inNewEngland(aCustomer) {
    return xxNewInNewEngland(aCustomer.address.state);
  }

  function xxNewInNewEngland(stateCode) {
    return ['MA', 'CT', 'ME', 'VT', 'NH', 'RI'].includes(stateCode);
  }

  const someCustomers = [];
  const newEnglanders = someCustomers.filter(c => inNewEngland(c));
}

function version11() {
  function xxNewInNewEngland(stateCode) {
    return ['MA', 'CT', 'ME', 'VT', 'NH', 'RI'].includes(stateCode);
  }

  const someCustomers = [];
  const newEnglanders = someCustomers.filter(
    c => xxNewInNewEngland(c.address.state)
  );
}

function version12() {
  function inNewInNewEngland(stateCode) {
    return ['MA', 'CT', 'ME', 'VT', 'NH', 'RI'].includes(stateCode);
  }

  const someCustomers = [];
  const newEnglanders = someCustomers.filter(
    c => inNewInNewEngland(c.address.state)
  );
}
