const assert = require('assert');
const exp = require('../hello');

it('#async function', async() => {
  const r = await exp();
  assert.strictEqual(r, 15);
});
