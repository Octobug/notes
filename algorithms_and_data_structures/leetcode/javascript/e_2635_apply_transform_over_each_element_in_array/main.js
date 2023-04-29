/**
 * @param {number[]} arr
 * @param {Function} fn
 * @return {number[]}
 */
var map = function (arr, fn) {
  const result = [];
  for (let i = 0; i < arr.length; i++) {
    result.push(fn(arr[i], i));
  }
  return result;
};

function main() {
  let arr = [1, 2, 3];
  let fn = function plusone(n) { return n + 1; };
  console.log(map(arr, fn));

  arr = [1, 2, 3];
  fn = function plusI(n, i) { return n + i; };
  console.log(map(arr, fn));

  arr = [10, 20, 30];
  fn = function constant() { return 42; };
  console.log(map(arr, fn));
}

main();
