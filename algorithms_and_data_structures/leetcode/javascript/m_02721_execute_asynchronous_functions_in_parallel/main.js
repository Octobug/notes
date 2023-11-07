/**
 * @param {Array<Function>} functions
 * @return {Promise<any>}
 */
var promiseAll = function (functions) {
  const results = functions.map(f => f());
  return new Promise((resolve, reject) => {
    let count = 0;
    results.forEach((p, index) => {
      p.then(result => {
        count++;
        results[index] = result;

        if (count === functions.length) {
          resolve(results);
        }
      }).catch(error => {
        reject(error);
      });
    });
  });
};

// /**
//  * @param {Array<Function>} functions
//  * @return {Promise<any>}
//  */
// var promiseAll = function (functions) {
//   const results = functions.map(f => f());
//   return new Promise((resolve, reject) => {
//     let count = 0;
//     results.forEach(async (p, index) => {
//       try {
//         results[index] = await p;
//         count++;

//         if (functions.length === count) {
//           resolve(results);
//         }
//       } catch (error) {
//         reject(error);
//       }
//     });
//   });
// };

async function main() {
  let functions = [
    () => new Promise(resolve => setTimeout(() => resolve(5), 200))
  ];
  await promiseAll(functions).then(console.log).catch(console.log);

  functions = [
    () => new Promise(resolve => setTimeout(() => resolve(1), 200)),
    () => new Promise((resolve, reject) => setTimeout(() => reject('Error'), 100))
  ];
  await promiseAll(functions).then(console.log).catch(console.log);

  functions = [
    () => new Promise(resolve => setTimeout(() => resolve(4), 50)),
    () => new Promise(resolve => setTimeout(() => resolve(10), 150)),
    () => new Promise(resolve => setTimeout(() => resolve(16), 100))
  ];
  await promiseAll(functions).then(console.log).catch(console.log);
}

main();
