function version1() {
  function alertForMiscreant(people) {
    for (const p of people) {
      if (p === 'Don') {
        setOffAlarms();
        return 'Don';
      }
      if (p === 'John') {
        setOffAlarms();
        return 'John';
      }
    }
    return '';
  }

  function setOffAlarms() { }

  const people = [];
  const found = alertForMiscreant(people);
}

function version2() {
  function findMiscreant(people) {
    for (const p of people) {
      if (p === 'Don') {
        return 'Don';
      }
      if (p === 'John') {
        return 'John';
      }
    }
    return '';
  }

  function alertForMiscreant(people) {
    for (const p of people) {
      if (p === 'Don') {
        setOffAlarms();
        return 'Don';
      }
      if (p === 'John') {
        setOffAlarms();
        return 'John';
      }
    }
    return '';
  }

  function setOffAlarms() { }

  const people = [];
  const found = alertForMiscreant(people);
}

function version3() {
  function findMiscreant(people) {
    for (const p of people) {
      if (p === 'Don') {
        return 'Don';
      }
      if (p === 'John') {
        return 'John';
      }
    }
    return '';
  }

  function alertForMiscreant(people) {
    if (findMiscreant(people) !== '') {
      setOffAlarms();
    }
  }

  function setOffAlarms() { }

  const people = [];
  const found = findMiscreant(people);
  alertForMiscreant(people);
}
