function version1() {
  const organization = {
    name: 'Acme Gooseberries',
    country: 'GB'
  };
}

function version2() {
  class Organization {
    constructor(data) {
      this._name = data.name;
      this._country = data.country;
    }

    get name() { return this._name; }
    set name(aString) { this._name = aString; }
    get country() { return this._country; }
    set country(aCountryCode) { this._country = aCountryCode; }
  }

  const organization = new Organization({
    name: 'Acme Gooseberries',
    country: 'GB'
  });
}

function version3() {
  class Organization {
    constructor(data) {
      this._title = data.name;
      this._country = data.country;
    }

    get name() { return this._title; }
    set name(aString) { this._title = aString; }
    get country() { return this._country; }
    set country(aCountryCode) { this._country = aCountryCode; }
  }

  const organization = new Organization({
    name: 'Acme Gooseberries',
    country: 'GB'
  });
}

function version4() {
  class Organization {
    constructor(data) {
      this._title = (data.title !== undefined) ? data.title : data.name;
      this._country = data.country;
    }

    get name() { return this._title; }
    set name(aString) { this._title = aString; }
    get country() { return this._country; }
    set country(aCountryCode) { this._country = aCountryCode; }
  }

  const organization = new Organization({
    title: 'Acme Gooseberries',
    country: 'GB'
  });
}

function version5() {
  class Organization {
    constructor(data) {
      this._title = data.title;
      this._country = data.country;
    }

    get name() { return this._title; }
    set name(aString) { this._title = aString; }
    get country() { return this._country; }
    set country(aCountryCode) { this._country = aCountryCode; }
  }

  const organization = new Organization({
    title: 'Acme Gooseberries',
    country: 'GB'
  });
}

function version6() {
  class Organization {
    constructor(data) {
      this._title = data.title;
      this._country = data.country;
    }

    get title() { return this._title; }
    set title(aString) { this._title = aString; }
    get country() { return this._country; }
    set country(aCountryCode) { this._country = aCountryCode; }
  }

  const organization = new Organization({
    title: 'Acme Gooseberries',
    country: 'GB'
  });
}
