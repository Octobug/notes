/**
 * @param {Function} fn
 * @param {number} t milliseconds
 * @return {Function}
 */
var debounce = function (fn, t) {
  var timer;
  return function (...args) {
    clearTimeout(timer);
    timer = setTimeout(() => {
      fn(...args);
    }, t);
  };
};

const log = debounce(console.log, 50);

setTimeout(() => {
  log('30'); // cancelled
}, 30);

setTimeout(() => {
  log('60'); // cancelled
}, 60);

setTimeout(() => {
  log('100'); // cancelled
}, 100);
