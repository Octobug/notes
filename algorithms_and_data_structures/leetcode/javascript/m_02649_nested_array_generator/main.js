/**
 * @param {Array} arr
 * @return {Generator}
 */
// var inorderTraversal = function* (arr) {
//   for (const elemDirect of arr) {
//     if (typeof elemDirect == 'number') {
//       yield elemDirect;
//     }
//     else {
//       const gen = inorderTraversal(elemDirect);
//       let value = gen.next();
//       while (!value.done) {
//         yield value.value;
//         value = gen.next();
//       }
//     }
//   }
// };

var inorderTraversal = function* (arr) {
  for (const elem of arr) {
    if (typeof elem == 'number')
      yield elem;
    else
      yield* inorderTraversal(elem);
  }
};

function main() {
  const gen = inorderTraversal([1, [2, 3]]);
  console.log(gen.next().value); // 1
  console.log(gen.next().value); // 2
  console.log(gen.next().value); // 3
}

main();
