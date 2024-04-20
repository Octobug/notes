const _ = {}; // _ is lodash

function version1() {
  const customerData = {
    '1920': {
      name: 'martin',
      id: '1920',
      usages: {
        '2016': {
          '1': 50,
          '2': 55,
        },
        '2015': {
          '1': 70,
          '2': 63
        }
      }
    }
  };

  const customerID = 1920;
  const year = 2016;
  const month = 1;
  const amount = 60;
  customerData[customerID].usages[year][month] = amount;

  function compareUsage(customerID, laterYear, month) {
    const later = customerData[customerID].usages[laterYear][month];
    const earlier = customerData[customerID].usages[laterYear - 1][month];
    return { laterAmount: later, change: later - earlier };
  }
}

function version2() {
  let customerData = {
    '1920': {
      name: 'martin',
      id: '1920',
      usages: {
        '2016': {
          '1': 50,
          '2': 55,
        },
        '2015': {
          '1': 70,
          '2': 63
        }
      }
    }
  };

  function getRawDataOfCustomers() { return customerData; }
  function setRawDataOfCustomers(arg) { customerData = arg; }

  const customerID = 1920;
  const year = 2016;
  const month = 1;
  const amount = 60;
  getRawDataOfCustomers()[customerID].usages[year][month] = amount;


  function compareUsage(customerID, laterYear, month) {
    const later = getRawDataOfCustomers()[customerID].usages[laterYear][month];
    const earlier = getRawDataOfCustomers()[customerID].usages[laterYear - 1][month];
    return { laterAmount: later, change: later - earlier };
  }
}

function version3() {
  class CustomerData {
    constructor(data) {
      this._data = data;
    }
  }

  let customerData = new CustomerData({
    '1920': {
      name: 'martin',
      id: '1920',
      usages: {
        '2016': {
          '1': 50,
          '2': 55,
        },
        '2015': {
          '1': 70,
          '2': 63
        }
      }
    }
  });

  function getCustomerData() { return customerData; }
  function getRawDataOfCustomers() { return customerData._data; }
  function setRawDataOfCustomers(arg) { customerData = new CustomerData(arg); }

  const customerID = 1920;
  const year = 2016;
  const month = 1;
  const amount = 60;
  getRawDataOfCustomers()[customerID].usages[year][month] = amount;


  function compareUsage(customerID, laterYear, month) {
    const later = getRawDataOfCustomers()[customerID].usages[laterYear][month];
    const earlier = getRawDataOfCustomers()[customerID].usages[laterYear - 1][month];
    return { laterAmount: later, change: later - earlier };
  }
}

function version4() {
  class CustomerData {
    constructor(data) {
      this._data = data;
    }
  }

  let customerData = new CustomerData({
    '1920': {
      name: 'martin',
      id: '1920',
      usages: {
        '2016': {
          '1': 50,
          '2': 55,
        },
        '2015': {
          '1': 70,
          '2': 63
        }
      }
    }
  });

  function getCustomerData() { return customerData; }
  function getRawDataOfCustomers() { return customerData._data; }
  function setRawDataOfCustomers(arg) { customerData = new CustomerData(arg); }
  function setUsage(customerID, year, month, amount) {
    getRawDataOfCustomers()[customerID].usages[year][month] = amount;
  }

  const customerID = 1920;
  const year = 2016;
  const month = 1;
  const amount = 60;
  setUsage(customerID, year, month, amount);

  function compareUsage(customerID, laterYear, month) {
    const later = getRawDataOfCustomers()[customerID].usages[laterYear][month];
    const earlier = getRawDataOfCustomers()[customerID].usages[laterYear - 1][month];
    return { laterAmount: later, change: later - earlier };
  }
}

function version5() {
  class CustomerData {
    constructor(data) {
      this._data = data;
    }

    setUsage(customerID, year, month, amount) {
      this._data[customerID].usages[year][month] = amount;
    }
  }

  let customerData = new CustomerData({
    '1920': {
      name: 'martin',
      id: '1920',
      usages: {
        '2016': {
          '1': 50,
          '2': 55,
        },
        '2015': {
          '1': 70,
          '2': 63
        }
      }
    }
  });

  function getCustomerData() { return customerData; }
  function getRawDataOfCustomers() { return customerData._data; }
  function setRawDataOfCustomers(arg) { customerData = new CustomerData(arg); }
  const customerID = 1920;
  const year = 2016;
  const month = 1;
  const amount = 60;
  getCustomerData().setUsage(customerID, year, month, amount);

  function compareUsage(customerID, laterYear, month) {
    const later = getRawDataOfCustomers()[customerID].usages[laterYear][month];
    const earlier = getRawDataOfCustomers()[customerID].usages[laterYear - 1][month];
    return { laterAmount: later, change: later - earlier };
  }
}

function version6() {
  class CustomerData {
    constructor(data) {
      this._data = data;
    }

    getRawData() {
      return _.cloneDeep(this._data);
    }

    setUsage(customerID, year, month, amount) {
      this._data[customerID].usages[year][month] = amount;
    }
  }

  let customerData = new CustomerData({
    '1920': {
      name: 'martin',
      id: '1920',
      usages: {
        '2016': {
          '1': 50,
          '2': 55,
        },
        '2015': {
          '1': 70,
          '2': 63
        }
      }
    }
  });

  function getCustomerData() { return customerData; }
  function getRawDataOfCustomers() { return customerData.rawData; }
  function setRawDataOfCustomers(arg) { customerData = new CustomerData(arg); }
  const customerID = 1920;
  const year = 2016;
  const month = 1;
  const amount = 60;
  getCustomerData().setUsage(customerID, year, month, amount);

  function compareUsage(customerID, laterYear, month) {
    const later = getRawDataOfCustomers()[customerID].usages[laterYear][month];
    const earlier = getRawDataOfCustomers()[customerID].usages[laterYear - 1][month];
    return { laterAmount: later, change: later - earlier };
  }
}

function version7() {
  class CustomerData {
    constructor(data) {
      this._data = data;
    }

    getRawData() {
      return _.cloneDeep(this._data);
    }

    setUsage(customerID, year, month, amount) {
      this._data[customerID].usages[year][month] = amount;
    }

    usage(customerID, year, month) {
      return this._data[customerID].usages[year][month];
    }
  }

  let customerData = new CustomerData({
    '1920': {
      name: 'martin',
      id: '1920',
      usages: {
        '2016': {
          '1': 50,
          '2': 55,
        },
        '2015': {
          '1': 70,
          '2': 63
        }
      }
    }
  });

  function getCustomerData() { return customerData; }
  function setRawDataOfCustomers(arg) { customerData = new CustomerData(arg); }
  const customerID = 1920;
  const year = 2016;
  const month = 1;
  const amount = 60;
  getCustomerData().setUsage(customerID, year, month, amount);

  function compareUsage(customerID, laterYear, month) {
    const later = getCustomerData().usage(customerID, laterYear, month);
    const earlier = getCustomerData().usage(customerID, laterYear - 1, month);
    return { laterAmount: later, change: later - earlier };
  }
}

function version8() {
  class CustomerData {
    constructor(data) {
      this._data = data;
    }

    get rawData() {
      return _.cloneDeep(this._data);
    }

    setUsage(customerID, year, month, amount) {
      this._data[customerID].usages[year][month] = amount;
    }

    usage(customerID, year, month) {
      return this._data[customerID].usages[year][month];
    }
  }

  let customerData = new CustomerData({
    '1920': {
      name: 'martin',
      id: '1920',
      usages: {
        '2016': {
          '1': 50,
          '2': 55,
        },
        '2015': {
          '1': 70,
          '2': 63
        }
      }
    }
  });

  function getCustomerData() { return customerData; }
  function setRawDataOfCustomers(arg) { customerData = new CustomerData(arg); }
  const customerID = 1920;
  const year = 2016;
  const month = 1;
  const amount = 60;
  getCustomerData().setUsage(customerID, year, month, amount);

  function compareUsage(customerID, laterYear, month) {
    const later = getCustomerData().rawData[customerID].usages[laterYear][month];
    const earlier = getCustomerData().rawData[customerID].usages[laterYear - 1][month];
    return { laterAmount: later, change: later - earlier };
  }
}
