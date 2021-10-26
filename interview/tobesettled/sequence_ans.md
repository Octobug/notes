# 答案

## 递归

```js
const a = (n) => {
  if (n === 0) { 
    return 1;
  }
  if (n === 1) {
    return 1;
  }
  return 2 * a(n - 1) + a(n - 2);
};
```

## 循环

```js
const b = (n) => {
  const seqs = [1, 1];
  let res;
  for (let i = 0; i <= n; i++) {
    res = seqs[i];
    if (!res) {
      const next = 2 * seqs[i - 1] + seqs[i - 2];
      seqs.push(next);
    }
    res = seqs[i];
  }
  return res;
};
```
