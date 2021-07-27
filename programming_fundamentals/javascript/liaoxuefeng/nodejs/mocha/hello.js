module.exports = (...rest) => {
  let sum = 0;
  for (const n of rest) {
    sum += n;
  }
  return sum;
};
