/**
 * @param {Function[]} functions
 * @return {Function}
 */
var compose = function (functions) {
  return function (x) {
    if (functions.length === 0) {
      return x;
    }

    let result = x;
    for (let i = functions.length - 1; i >= 0; i--) {
      result = functions[i](result);
    }
    return result;
  };
};

function main() {
  let fn = compose([x => x + 1, x => x * x, x => 2 * x]);
  let x = 4;
  console.log(fn(x));

  fn = compose([x => 10 * x, x => 10 * x, x => 10 * x]);
  x = 1;
  console.log(fn(x));

  fn = compose([]);
  x = 42;
  console.log(fn(x));
}

main();
