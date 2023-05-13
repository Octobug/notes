/**
 * @param {Function} fn
 * @param {number} t
 * @return {Function}
 */
var throttle = function (fn, t) {
  let nextTime;
  let savedArgs;
  let timer;

  return function (...args) {
    savedArgs = args;
    if (nextTime === undefined) {
      nextTime = Date.now() + t;
      fn(...savedArgs);
    } else {
      const now = Date.now();
      clearTimeout(timer);
      if (now < nextTime) {
        timer = setTimeout(() => {
          nextTime = Date.now() + t;
          fn(...savedArgs);
        }, nextTime - now);
      } else {
        nextTime = Date.now() + t;
        fn(...savedArgs);
      }
    }
  };
};


const throttled = throttle(console.log, 70);
setTimeout(() => throttled(1), 50);
setTimeout(() => throttled(2), 75);
setTimeout(() => throttled(8), 90);
setTimeout(() => throttled(5, 7), 140);
setTimeout(() => throttled(9, 4), 300);
