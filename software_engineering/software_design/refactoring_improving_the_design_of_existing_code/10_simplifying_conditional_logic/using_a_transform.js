const _ = require('lodash');

function version1() {
  const customer = {
    name: 'Warehouse Unit 15',
    location: 'Malden MA',
    // more site details 
    customer: 'unknown',
  };

  function acquireSiteData() {
    return {
      name: 'Acme Boston',
      location: 'Malden MA', // more site details 
      customer: {
        name: 'Acme Industries',
        billingPlan: 'plan-451',
        paymentHistory: {
          weeksDelinquentInLastYear: 7
          //more 
        },
        // more
      }
    };
  }

  const registry = {};

  // client 1...
  const site = acquireSiteData();
  const aCustomer = site.customer;
  // ... lots of intervening code ...
  let customerName;
  if (aCustomer === 'unknown') {
    customerName = 'occupant';
  } else {
    customerName = aCustomer.name;
  }

  // client 2...
  const plan = (aCustomer === 'unknown')
    ? registry.billingPlans.basic
    : aCustomer.billingPlan;

  // client 3...
  const weeksDelinquent = (aCustomer === 'unknown')
    ? 0
    : aCustomer.paymentHistory.weeksDelinquentInLastYear;
}

function version2() {
  const customer = {
    name: 'Warehouse Unit 15',
    location: 'Malden MA',
    // more site details 
    customer: 'unknown',
  };

  function acquireSiteData() {
    return {
      name: 'Acme Boston',
      location: 'Malden MA', // more site details 
      customer: {
        name: 'Acme Industries',
        billingPlan: 'plan-451',
        paymentHistory: {
          weeksDelinquentInLastYear: 7
          //more 
        },
        // more
      }
    };
  }

  function enrichSite(inputSite) {
    return _.cloneDeep(inputSite);
  }

  const registry = {};

  // client 1...
  const rawSite = acquireSiteData();
  const site = enrichSite(rawSite);
  const aCustomer = site.customer;
  // ... lots of intervening code ...
  let customerName;
  if (aCustomer === 'unknown') {
    customerName = 'occupant';
  } else {
    customerName = aCustomer.name;
  }

  // client 2...
  const plan = (aCustomer === 'unknown')
    ? registry.billingPlans.basic
    : aCustomer.billingPlan;

  // client 3...
  const weeksDelinquent = (aCustomer === 'unknown')
    ? 0
    : aCustomer.paymentHistory.weeksDelinquentInLastYear;
}

function version3() {
  const customer = {
    name: 'Warehouse Unit 15',
    location: 'Malden MA',
    // more site details 
    customer: 'unknown',
  };

  function acquireSiteData() {
    return {
      name: 'Acme Boston',
      location: 'Malden MA', // more site details 
      customer: {
        name: 'Acme Industries',
        billingPlan: 'plan-451',
        paymentHistory: {
          weeksDelinquentInLastYear: 7
          //more 
        },
        // more
      }
    };
  }

  function enrichSite(inputSite) {
    return _.cloneDeep(inputSite);
  }

  function isUnknown(aCustomer) {
    return aCustomer === 'unknown';
  }

  const registry = {};

  // client 1...
  const rawSite = acquireSiteData();
  const site = enrichSite(rawSite);
  const aCustomer = site.customer;
  // ... lots of intervening code ...
  let customerName;
  if (isUnknown(aCustomer)) {
    customerName = 'occupant';
  } else {
    customerName = aCustomer.name;
  }

  // client 2...
  const plan = (isUnknown(aCustomer))
    ? registry.billingPlans.basic
    : aCustomer.billingPlan;

  // client 3...
  const weeksDelinquent = (isUnknown(aCustomer))
    ? 0
    : aCustomer.paymentHistory.weeksDelinquentInLastYear;
}

function version4() {
  const customer = {
    name: 'Warehouse Unit 15',
    location: 'Malden MA',
    // more site details 
    customer: 'unknown',
  };

  function acquireSiteData() {
    return {
      name: 'Acme Boston',
      location: 'Malden MA', // more site details 
      customer: {
        name: 'Acme Industries',
        billingPlan: 'plan-451',
        paymentHistory: {
          weeksDelinquentInLastYear: 7
          //more 
        },
        // more
      }
    };
  }

  function enrichSite(inputSite) {
    const result = _.cloneDeep(inputSite);
    const unknownCustomer = {
      isUnknown: true,
    };

    if (isUnknown(result.customer)) {
      result.customer = unknownCustomer;
    } else {
      result.customer.isUnknown = false;
    }
    return result;
  }

  function isUnknown(aCustomer) {
    if (aCustomer === 'unknwon') {
      return true;
    } else {
      return aCustomer.isUnknown;
    }
  }

  const registry = {};

  // client 1...
  const rawSite = acquireSiteData();
  const site = enrichSite(rawSite);
  const aCustomer = site.customer;
  // ... lots of intervening code ...
  let customerName;
  if (isUnknown(aCustomer)) {
    customerName = 'occupant';
  } else {
    customerName = aCustomer.name;
  }

  // client 2...
  const plan = (isUnknown(aCustomer))
    ? registry.billingPlans.basic
    : aCustomer.billingPlan;

  // client 3...
  const weeksDelinquent = (isUnknown(aCustomer))
    ? 0
    : aCustomer.paymentHistory.weeksDelinquentInLastYear;
}

function version5() {
  const customer = {
    name: 'Warehouse Unit 15',
    location: 'Malden MA',
    // more site details 
    customer: 'unknown',
  };

  function acquireSiteData() {
    return {
      name: 'Acme Boston',
      location: 'Malden MA', // more site details 
      customer: {
        name: 'Acme Industries',
        billingPlan: 'plan-451',
        paymentHistory: {
          weeksDelinquentInLastYear: 7
          //more 
        },
        // more
      }
    };
  }

  function enrichSite(inputSite) {
    const result = _.cloneDeep(inputSite);
    const unknownCustomer = {
      isUnknown: true,
      name: 'occupant',
      billingPlan: registry.billingPlans.basic,
      paymentHistory: {
        weeksDelinquentInLastYear: 0,
      }
    };

    if (isUnknown(result.customer)) {
      result.customer = unknownCustomer;
    } else {
      result.customer.isUnknown = false;
    }
    return result;

    function isUnknown(aCustomer) {
      if (aCustomer === 'unknwon') {
        return true;
      } else {
        return aCustomer.isUnknown;
      }
    }
  }

  const registry = {};

  // client 1...
  const rawSite = acquireSiteData();
  const site = enrichSite(rawSite);
  const aCustomer = site.customer;
  // ... lots of intervening code ...
  let customerName;
  customerName = aCustomer.name;

  // client 2...
  const plan = aCustomer.billingPlan;

  // client 3...
  const weeksDelinquent = aCustomer.paymentHistory.weeksDelinquentInLastYear;
}
