/**
 * @param {integer} init
 * @return { increment: Function, decrement: Function, reset: Function }
 */
var createCounter = function (init) {
  let savedInit = init;
  return {
    decrement: () => {
      init--;
      return init;
    },
    increment: () => {
      init++;
      return init;
    },
    reset: () => {
      init = savedInit;
      return init;
    },
  };
};

const counter = createCounter(5);
console.log(counter.increment()); // 6
console.log(counter.reset());     // 5
console.log(counter.decrement()); // 4
