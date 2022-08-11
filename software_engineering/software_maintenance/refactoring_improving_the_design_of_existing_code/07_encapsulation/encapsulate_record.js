function version1() {
  const organization = { name: 'Acme Gooseberries', country: 'GB' };

  let result = '';
  result += `<h1>${organization.name}</h1`;

  const newName = 'newName';
  organization.name = newName;
}

function version2() {
  const organization = { name: 'Acme Gooseberries', country: 'GB' };
  function getRawDataOfOrganization() { return organization; }

  let result = '';
  result += `<h1>${getRawDataOfOrganization().name}</h1`;

  const newName = 'newName';
  getRawDataOfOrganization().name = newName;
}

function version3() {
  class Organization {
    constructor(data) {
      this._data = data;
    }

    get name() { return this._data.name; }
    set name(aString) { this._data.name = aString; }
  }

  const organization = new Organization({
    name: 'Acme Gooseberries', country: 'GB'
  });

  function getOrganization() { return organization; }

  let result = '';
  result += `<h1>${getOrganization().name}</h1`;

  const newName = 'newName';
  getOrganization().name = newName;
}

function version4() {
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
    name: 'Acme Gooseberries', country: 'GB'
  });

  function getOrganization() { return organization; }

  let result = '';
  result += `<h1>${getOrganization().name}</h1`;

  const newName = 'newName';
  getOrganization().name = newName;
}
