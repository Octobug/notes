/**
 * @return {number}
 */
var argumentsLength = function (...args) {
  return args.length;
};

console.log(argumentsLength(5));
console.log(argumentsLength(1, 2, 3));
