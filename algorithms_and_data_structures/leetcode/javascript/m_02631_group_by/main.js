/**
 * @param {Function} fn
 * @return {Array}
 */
Array.prototype.groupBy = function (fn) {
  const mapper = {};
  this.forEach((item) => {
    const key = fn(item);
    mapper[key] = mapper[key] || [];
    mapper[key].push(item);
  });
  return mapper;
};

let array = [
  { 'id': '1' },
  { 'id': '1' },
  { 'id': '2' }
];
let fn = function (item) {
  return item.id;
};
console.log(array.groupBy(fn));

array = [
  [1, 2, 3],
  [1, 3, 5],
  [1, 5, 9]
];
fn = function (list) {
  return String(list[0]);
};
console.log(array.groupBy(fn));

array = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10];
fn = function (n) {
  return String(n > 5);
};
console.log(array.groupBy(fn));
