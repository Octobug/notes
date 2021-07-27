const fs = require('fs');
const path = require('path');

const db = require('./db');

const files = fs.readdirSync(path.join(__dirname, '/models'));

const jsFiles = files.filter(f => {
  return f.endsWith('.js');
}, files);

module.exports = {};

for (const f of jsFiles) {
  console.log(`import model from file ${f}...`);
  const name = f.substring(0, f.length - 3);
  module.exports[name] = require(path.join(__dirname, '/models/', f));
}

module.exports.sync = () => {
  db.sync();
};
