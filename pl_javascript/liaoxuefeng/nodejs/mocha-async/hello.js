const fs = require('mz/fs');

// a simple async function:
module.exports = async() => {
  const expression = await fs.readFile('nodejs/mocha-async/data.txt', 'utf-8');
  const fn = new Function('return ' + expression);
  const r = fn();
  console.log(`Calculate: ${expression} = ${r}`);
  return r;
};
