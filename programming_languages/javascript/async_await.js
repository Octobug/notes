function getNum(num) {
  // eslint-disable-next-line no-unused-vars
  return new Promise((resolve, reject) => {
    setTimeout(() => {
      resolve(num + 1);
    }, 1000);
  });
}

// const func = async () => {
//   const f1 = await getNum(1)
//   const f2 = await getNum(f1)
//   console.log(f2)
//   // 输出3 
// }

// async
const func = function* () {
  const res1 = yield getNum(1);
  const res2 = yield getNum(res1);
  console.log(res2);
};
asyncFun(func);

// await
function asyncFun(func) {
  const gen = func();

  function next(data) {
    const result = gen.next(data);

    if (result.done) {
      return result.value;
    }

    result.value.then(data => {
      next(data);
    });
  }

  next();
}
