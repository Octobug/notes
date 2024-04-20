function version1() {
  const people = [];

  let youngest = people[0] ? people[0].age : Infinity;
  let totalSalary = 0;
  for (const p of people) {
    if (p.age < youngest) {
      youngest = p.age;
    }
    totalSalary += p.salary;
  }

  return `youngestAge: ${youngest}, totalSalary: ${totalSalary}`;
}

function version2() {
  const people = [];

  let youngest = people[0] ? people[0].age : Infinity;
  let totalSalary = 0;
  for (const p of people) {
    totalSalary += p.salary;
  }

  for (const p of people) {
    if (p.age < youngest) {
      youngest = p.age;
    }
  }

  return `youngestAge: ${youngest}, totalSalary: ${totalSalary}`;
}

function version3() {
  const people = [];

  let totalSalary = 0;
  for (const p of people) {
    totalSalary += p.salary;
  }

  let youngest = people[0] ? people[0].age : Infinity;
  for (const p of people) {
    if (p.age < youngest) {
      youngest = p.age;
    }
  }

  return `youngestAge: ${youngest}, totalSalary: ${totalSalary}`;
}

function version4() {
  const people = [];
  return `youngestAge: ${youngestAge()}, totalSalary: ${totalSalary()}`;

  function totalSalary() {
    let totalSalary = 0;
    for (const p of people) {
      totalSalary += p.salary;
    }
    return totalSalary;
  }

  function youngestAge() {
    let youngest = people[0] ? people[0].age : Infinity;
    for (const p of people) {
      if (p.age < youngest) {
        youngest = p.age;
      }
    }
    return youngest;
  }
}

function version5() {
  const people = [];
  return `youngestAge: ${youngestAge()}, totalSalary: ${totalSalary()}`;

  function totalSalary() {
    return people.reduce((total, p) => total + p.salary, 0);
  }

  function youngestAge() {
    return Math.min(...people.map(p => p.age));
  }
}
