# Class

## Error

> <https://stackoverflow.com/a/32749533/7267801>

```js
class ExtendableError extends Error {
  constructor(message) {
    super(message);
    this.name = this.constructor.name;
    if (typeof Error.captureStackTrace === 'function') {
      // for compatibility
      Error.captureStackTrace(this, this.constructor);
    } else { 
      this.stack = (new Error(message)).stack; 
    }
  }
}
// now I can extend

class MyError extends ExtendableError {}

var myerror = new MyError("ll");
console.log(myerror.message);
console.log(myerror instanceof Error);
console.log(myerror.name);
console.log(myerror.stack);
```
