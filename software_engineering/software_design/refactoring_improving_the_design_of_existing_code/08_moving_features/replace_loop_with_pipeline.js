function version1() {
  function acquireData(input) {
    const lines = input.split('\n');
    let firstLine = true;
    const result = [];
    for (const line of lines) {
      if (firstLine) {
        firstLine = false;
        continue;
      }
      if (line.trim() === '') {
        continue;
      }
      const record = line.split(',');
      if (record[1].trim() === 'India') {
        result.push({ city: record[0].trim(), phone: record[2].trim() });
      }
    }
    return result;
  }
}

function version2() {
  function acquireData(input) {
    const lines = input.split('\n');
    let firstLine = true;
    const result = [];
    const loopItems = lines;
    for (const line of loopItems) {
      if (firstLine) {
        firstLine = false;
        continue;
      }
      if (line.trim() === '') {
        continue;
      }
      const record = line.split(',');
      if (record[1].trim() === 'India') {
        result.push({ city: record[0].trim(), phone: record[2].trim() });
      }
    }
    return result;
  }
}

function version3() {
  function acquireData(input) {
    const lines = input.split('\n');
    const result = [];
    const loopItems = lines.slice(1);
    for (const line of loopItems) {
      if (line.trim() === '') {
        continue;
      }
      const record = line.split(',');
      if (record[1].trim() === 'India') {
        result.push({ city: record[0].trim(), phone: record[2].trim() });
      }
    }
    return result;
  }
}

function version4() {
  function acquireData(input) {
    const lines = input.split('\n');
    const result = [];
    const loopItems = lines
      .slice(1)
      .filter(line => line.trim() !== '');
    for (const line of loopItems) {
      const record = line.split(',');
      if (record[1].trim() === 'India') {
        result.push({ city: record[0].trim(), phone: record[2].trim() });
      }
    }
    return result;
  }
}

function version5() {
  function acquireData(input) {
    const lines = input.split('\n');
    const result = [];
    const loopItems = lines
      .slice(1)
      .filter(line => line.trim() !== '')
      .map(line => line.split(','));
    for (const line of loopItems) {
      const record = line;
      if (record[1].trim() === 'India') {
        result.push({ city: record[0].trim(), phone: record[2].trim() });
      }
    }
    return result;
  }
}

function version6() {
  function acquireData(input) {
    const lines = input.split('\n');
    const result = [];
    const loopItems = lines
      .slice(1)
      .filter(line => line.trim() !== '')
      .map(line => line.split(','))
      .filter(record => record[1].trim() === 'India');
    for (const line of loopItems) {
      const record = line;
      result.push({ city: record[0].trim(), phone: record[2].trim() });
    }
    return result;
  }
}

function version7() {
  function acquireData(input) {
    const lines = input.split('\n');
    const result = lines
      .slice(1)
      .filter(line => line.trim() !== '')
      .map(line => line.split(','))
      .filter(record => record[1].trim() === 'India')
      .map(record => ({ city: record[0].trim(), phone: record[2].trim() }));
    return result;
  }
}

function version8() {
  function acquireData(input) {
    const lines = input.split('\n');
    return lines
      .slice(1)
      .filter(line => line.trim() !== '')
      .map(line => line.split(','))
      .filter(fields => fields[1].trim() === 'India')
      .map(fields => ({ city: fields[0].trim(), phone: fields[2].trim() }));
  }
}
