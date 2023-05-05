/**
 * @param {Function} fn
 * @return {Function}
 */
var once = function (fn) {
  let called = false;
  return function (...args) {
    if (called) {
      return undefined;
    }
    called = true;
    return fn(...args);
  };
};

let fn = (a, b, c) => (a + b + c);
let onceFn = once(fn);
let result = onceFn(1, 2, 3);
console.log(result);
result = onceFn(2, 3, 6);
console.log(result);

fn = (a, b, c) => (a * b * c);
onceFn = once(fn);
result = onceFn(5, 7, 4);
console.log(result);
result = onceFn(2, 3, 6);
console.log(result);
result = onceFn(4, 6, 8);
console.log(result);
