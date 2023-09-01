/**
 * @param {Promise} promise1
 * @param {Promise} promise2
 * @return {Promise}
 */
var addTwoPromises = async function (promise1, promise2) {
  return await promise1 + await promise2;
};

/**
 * @param {Promise} promise1
 * @param {Promise} promise2
 * @return {Promise}
 */
addTwoPromises = async function (promise1, promise2) {
  const results = await Promise.allSettled([promise1, promise2]);
  return results.reduce((sum, item) => sum + item.value, 0);
};


async function main() {
  let promise1 = new Promise(resolve => setTimeout(() => resolve(2), 20));
  let promise2 = new Promise(resolve => setTimeout(() => resolve(5), 60));

  await addTwoPromises(promise1, promise2).then(console.log); // 7

  promise1 = new Promise(resolve => setTimeout(() => resolve(10), 50));
  promise2 = new Promise(resolve => setTimeout(() => resolve(-12), 30));

  await addTwoPromises(promise1, promise2).then(console.log); // -2
}

main();
