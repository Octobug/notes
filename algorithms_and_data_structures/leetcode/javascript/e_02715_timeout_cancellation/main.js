/**
 * @param {Function} fn
 * @param {Array} args
 * @param {number} t
 * @return {Function}
 */
var cancellable = function (fn, args, t) {
  const now = Date.now();
  let timer = setTimeout(() => {
    fn(...args);
  }, t);

  return function () {
    if (Date.now() - now < t) {
      clearTimeout(timer);
    }
  };
};

function main() {
  const result = [];
  let fn = (x) => x * 5;
  let args = [2], t = 20, cancelT = 50;
  let start = performance.now();

  const log = (...argsArr) => {
    const diff = Math.floor(performance.now() - start);
    result.push({ 'time': diff, 'returned': fn(...argsArr) });
  };

  let cancel1 = cancellable(log, args, t);
  let maxT = Math.max(t, cancelT);
  setTimeout(() => {
    cancel1();
  }, cancelT);
  setTimeout(() => {
    console.log(result); // [{"time":20,"returned":10}]
  }, maxT + 15);
}

main();
