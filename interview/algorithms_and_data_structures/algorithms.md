# Algorithms

## Array

### 将给定数组里的 0 移到末尾，并且保持其他元素的顺序

```js
const mvZeroToEnd = (arr) => {
  let nonZeroCount = 0;
  for (let i = 0; i < arr.length; i++) {
    const num = arr[i];
    if (num !== 0) {
      if (nonZeroCount !== i) {
        arr[nonZeroCount] = num;
        arr[i] = 0;
      }
      nonZeroCount++;
    }
  }
  return arr;
};
```

## Miscellaneous

### 斐波那契数列

#### 递归

```js
const fibonacci = (n) => {
  n = parseInt(n) || 0;
  if (n === 0) {
    return 0;
  } else if (n === 1) {
    return 1;
  } else {
    return fibonacci(n - 1) + fibonacci(n - 2);
  }
};
```

#### 循环

```js
const fibonacci = (n) => {
  n = parseInt(n) || 0;
  let a = 0;
  let b = 1;
  let tmp;
  while (n--) {
    tmp = a;
    a = b;
    b = tmp + b;
  }
  return a;
};
```
