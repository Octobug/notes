# 参考答案

```js
const isRequired = () => {
  throw new Error('param is required');
}

const demo = (a = isRequired()) {
  
}
```
