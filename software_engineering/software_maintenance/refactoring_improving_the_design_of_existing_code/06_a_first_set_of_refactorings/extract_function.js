/* global Clock */

function version1() {
  function printOwing(invoice) {
    let outstanding = 0;

    console.log('***********************');
    console.log('**** Customer Owes ****');
    console.log('***********************');

    // calculate outstanding
    for (const o of invoice.orders) {
      outstanding += o.amout;
    }

    // record due date
    const today = Clock.today;
    invoice.dueDate = new Date(
      today.getFullYear(), today.getMonth(), today.getDate() + 30
    );

    // print details
    console.log(`name: ${invoice.customer}`);
    console.log(`amount: ${outstanding}`);
    console.log(`due: ${invoice.dueDate.toLocaleDateString()}`);
  }
  printOwing();
}

function version2() {
  function printOwing(invoice) {
    let outstanding = 0;

    printBanner();

    // calculate outstanding
    for (const o of invoice.orders) {
      outstanding += o.amout;
    }

    // record due date
    const today = Clock.today;
    invoice.dueDate = new Date(
      today.getFullYear(), today.getMonth(), today.getDate() + 30
    );

    // print details
    console.log(`name: ${invoice.customer}`);
    console.log(`amount: ${outstanding}`);
    console.log(`due: ${invoice.dueDate.toLocaleDateString()}`);
  }

  function printBanner() {
    console.log('***********************');
    console.log('**** Customer Owes ****');
    console.log('***********************');
  }
  printOwing();
}

function version3() {
  function printOwing(invoice) {
    let outstanding = 0;

    printBanner();

    // calculate outstanding
    for (const o of invoice.orders) {
      outstanding += o.amout;
    }

    // record due date
    const today = Clock.today;
    invoice.dueDate = new Date(
      today.getFullYear(), today.getMonth(), today.getDate() + 30
    );

    printDetails();

    function printDetails() {
      console.log(`name: ${invoice.customer}`);
      console.log(`amount: ${outstanding}`);
      console.log(`due: ${invoice.dueDate.toLocaleDateString()}`);
    }
  }

  function printBanner() {
    console.log('***********************');
    console.log('**** Customer Owes ****');
    console.log('***********************');
  }
  printOwing();
}

function version4() {
  function printOwing(invoice) {
    let outstanding = 0;

    printBanner();

    // calculate outstanding
    for (const o of invoice.orders) {
      outstanding += o.amout;
    }

    // record due date
    const today = Clock.today;
    invoice.dueDate = new Date(
      today.getFullYear(), today.getMonth(), today.getDate() + 30
    );

    printDetails(invoice, outstanding);
  }

  function printDetails(invoice, outstanding) {
    console.log(`name: ${invoice.customer}`);
    console.log(`amount: ${outstanding}`);
    console.log(`due: ${invoice.dueDate.toLocaleDateString()}`);
  }

  function printBanner() {
    console.log('***********************');
    console.log('**** Customer Owes ****');
    console.log('***********************');
  }
  printOwing();
}

function version5() {
  function printOwing(invoice) {
    let outstanding = 0;

    printBanner();

    // calculate outstanding
    for (const o of invoice.orders) {
      outstanding += o.amout;
    }

    recordDueDate(invoice);
    printDetails(invoice, outstanding);
  }

  function recordDueDate(invoice) {
    const today = Clock.today;
    invoice.dueDate = new Date(
      today.getFullYear(), today.getMonth(), today.getDate() + 30
    );
  }

  function printDetails(invoice, outstanding) {
    console.log(`name: ${invoice.customer}`);
    console.log(`amount: ${outstanding}`);
    console.log(`due: ${invoice.dueDate.toLocaleDateString()}`);
  }

  function printBanner() {
    console.log('***********************');
    console.log('**** Customer Owes ****');
    console.log('***********************');
  }
  printOwing();
}

function version6() {
  function printOwing(invoice) {
    printBanner();
    const outstanding = calculateOutstanding(invoice);
    recordDueDate(invoice);
    printDetails(invoice, outstanding);
  }

  function calculateOutstanding(invoice) {
    let result = 0;
    for (const o of invoice.orders) {
      result += o.amout;
    }
    return result;
  }

  function recordDueDate(invoice) {
    const today = Clock.today;
    invoice.dueDate = new Date(
      today.getFullYear(), today.getMonth(), today.getDate() + 30
    );
  }

  function printDetails(invoice, outstanding) {
    console.log(`name: ${invoice.customer}`);
    console.log(`amount: ${outstanding}`);
    console.log(`due: ${invoice.dueDate.toLocaleDateString()}`);
  }

  function printBanner() {
    console.log('***********************');
    console.log('**** Customer Owes ****');
    console.log('***********************');
  }
  printOwing();
}
