# JavaScript

## Event Loop

### 下面代码片段的输出是什么？为什么？

```js
let bar;

function someAsyncApiCall(callback) { callback(); }

someAsyncApiCall(() => {
  console.log('bar', bar);
});

bar = 1;
```

答案：

```js
let bar;

// this has an asynchronous signature, but calls callback synchronously
function someAsyncApiCall(callback) { callback(); }

// the callback is called before `someAsyncApiCall` completes.
someAsyncApiCall(() => {
  // since someAsyncApiCall hasn't completed, bar hasn't been assigned any value
  console.log('bar', bar); // undefined
});

bar = 1;
```

## Modules

### Main


```js
if (require.main === module) {
  main();
}
```
