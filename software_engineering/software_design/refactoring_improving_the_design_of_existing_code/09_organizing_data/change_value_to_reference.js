function version1() {
  class Order {
    constructor(data) {
      this._number = data.number;
      this._customer = new Customer(data.customer);
      // load other data
    }

    get customer() { return this._customer; }
  }

  class Customer {
    constructor(id) {
      this._id = id;
    }

    get id() { return this._id; }
  }
}

function version2() {
  class Order {
    constructor(data) {
      this._number = data.number;
      this._customer = new Customer(data.customer);
      // load other data
    }

    get customer() { return this._customer; }
  }

  class Customer {
    constructor(id) {
      this._id = id;
    }

    get id() { return this._id; }
  }

  // reference_repository.js
  let _repositoryData;
  const repository = {
    initialize: function initialize() {
      _repositoryData = {};
      _repositoryData.customers = new Map();
    },
    registerCustomer: function (id) {
      if (!_repositoryData.customers.has(id)) {
        _repositoryData.customers.set(id, new Customer(id));
      }
      return repository.findCustomer(id);
    },
    findCustomer(id) {
      return _repositoryData.customers.get(id);
    }
  };
}

function version3() {
  class Order {
    constructor(data) {
      this._number = data.number;
      this._customer = repository.registerCustomer(data.customer);
      // load other data
    }

    get customer() { return this._customer; }
  }

  class Customer {
    constructor(id) {
      this._id = id;
    }

    get id() { return this._id; }
  }

  // reference_repository.js
  let _repositoryData;
  const repository = {
    initialize: function initialize() {
      _repositoryData = {};
      _repositoryData.customers = new Map();
    },
    registerCustomer: function (id) {
      if (!_repositoryData.customers.has(id)) {
        _repositoryData.customers.set(id, new Customer(id));
      }
      return repository.findCustomer(id);
    },
    findCustomer(id) {
      return _repositoryData.customers.get(id);
    }
  };
}
