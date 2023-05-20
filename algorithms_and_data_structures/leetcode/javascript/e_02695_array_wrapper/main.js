/**
 * @param {number[]} nums
 */
var ArrayWrapper = function (nums) {
  this.nums = nums;
};

ArrayWrapper.prototype.valueOf = function () {
  return this.nums.reduce((a, b) => a + b, 0);
};

ArrayWrapper.prototype.toString = function () {
  return `[${this.nums.join(',')}]`;
};

const obj1 = new ArrayWrapper([1, 2]);
const obj2 = new ArrayWrapper([3, 4]);
console.log(obj1 + obj2);       // 10

const obj3 = new ArrayWrapper([23, 98, 42, 7]);
console.log(String(obj3));      // "[23, 98, 42, 7]"

const obj4 = new ArrayWrapper([]);
const obj5 = new ArrayWrapper([]);
console.log(obj4 + obj5);       // 0
