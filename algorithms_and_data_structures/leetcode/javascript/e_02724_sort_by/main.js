/**
 * @param {Array} arr
 * @param {Function} fn
 * @return {Array}
 */
var sortBy = function (arr, fn) {
  return arr.sort((a, b) => fn(a) - fn(b));
};

function main() {
  let arr = [5, 4, 1, 2, 3], fn = (x) => x;
  let result = sortBy(arr, fn);
  console.log(result);

  arr = [{ 'x': 1 }, { 'x': 0 }, { 'x': -1 }], fn = (d) => d.x;
  result = sortBy(arr, fn);
  console.log(result);

  arr = [[3, 4], [5, 2], [10, 1]], fn = (x) => x[1];
  result = sortBy(arr, fn);
  console.log(result);
}

main();
