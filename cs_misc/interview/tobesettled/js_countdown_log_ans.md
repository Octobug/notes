# 参考答案

```js
function count(arr){
  const total = arr.length;
  for (let i = 0; i < total; i++) {
    setTimeout(() => console.log(arr[total - i - 1]), 1000 * (i))
  }
}
count([1, 2, 3, 4])
```
