/**
 * @param {Function} fn
 * @param {number} t
 * @return {Function}
 */
var timeLimit = function (fn, t) {
  return async function (...args) {
    return new Promise((resolve, reject) => {
      setTimeout(() => reject('Time Limit Exceeded'), t);
      fn(...args).then(resolve).catch(reject);
    });
  };
};


let fn = async (n) => {
  await new Promise(res => setTimeout(res, 100));
  return n * n;
};
let limited = timeLimit(fn, 50);
limited(5).catch(console.log);

fn = async (n) => {
  await new Promise(res => setTimeout(res, 100));
  return n * n;
};
limited = timeLimit(fn, 150);
limited(5).catch(console.log);

fn = async (a, b) => {
  await new Promise(res => setTimeout(res, 120));
  return a + b;
};
limited = timeLimit(fn, 150);
limited(5, 10).catch(console.log);

fn = async () => {
  throw 'Error';
};
limited = timeLimit(fn, 1000);
limited().catch(console.log);
