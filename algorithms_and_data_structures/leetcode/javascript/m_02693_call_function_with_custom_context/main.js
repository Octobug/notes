/**
 * @param {Object} context
 * @param {any[]} args
 * @return {any}
 */
Function.prototype.callPolyfill = function (context, ...args) {
  // return this.bind(context)(...args);
  return this.apply(context, args);
};

let fn = function add(b) {
  return this.a + b;
};
console.log(fn.callPolyfill({ 'a': 5 }, 7));

fn = function tax(price, taxRate) {
  return `The cost of the ${this.item} is ${price * taxRate}`;
};
console.log(fn.callPolyfill({ 'item': 'burger' }, 10, 1.1));
