/**
 * @param {Array} arr
 * @param {number} size
 * @return {Array[]}
 */
var chunk = function (arr, size) {
  const result = [];
  for (let i = 0; i < arr.length; i += size) {
    result.push(arr.slice(i, i + size));
  }
  return result;
};

let arr = [1, 2, 3, 4, 5], size = 1;
console.log(chunk(arr, size));

arr = [1, 9, 6, 3, 2], size = 3;
console.log(chunk(arr, size));

arr = [8, 5, 3, 2, 6], size = 6;
console.log(chunk(arr, size));

arr = [], size = 1;
console.log(chunk(arr, size));
