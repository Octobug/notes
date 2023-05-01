/**
 * @param {Function} fn
 * @return {Function}
 */
var curry = function (fn) {
  return function curried(...args) {
    const flatArgs = args.flat();
    if (fn.length === 0) {
      return fn();
    } else if (flatArgs.length === fn.length) {
      return fn(...flatArgs);
    } else {
      return function (...argsLeft) {
        return curried(...args, ...argsLeft);
      };
    }
  };
};

/**
* function sum(a, b) { return a + b; }
* const csum = curry(sum);
* csum(1)(2) // 3
*/

function main() {
  let fn = function sum(a, b, c) { return a + b + c; };
  let curriedSum = curry(fn);
  console.log(curriedSum(1)(2)(3));

  fn = function sum(a, b, c) { return a + b + c; };
  curriedSum = curry(fn);
  console.log(curriedSum(1, 2)(3));

  fn = function sum(a, b, c) { return a + b + c; };
  curriedSum = curry(fn);
  console.log(curriedSum()()(1, 2, 3));

  fn = function life() { return 42; };
  let curriedLife = curry(fn);
  console.log(curriedLife());
}

main();
