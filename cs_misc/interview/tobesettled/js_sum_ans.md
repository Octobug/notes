# 答案

```js
const sum = (a, b) => {
  if (typeof a === 'undefined') {
    throw new Error('param is required');
  }
  if (typeof b === 'undefined') {
    return (c) => {
      return a + c;
    };
  }
  return a + b;
}

console.log(sum(2, 3));
console.log(sum(2)(3));
```
