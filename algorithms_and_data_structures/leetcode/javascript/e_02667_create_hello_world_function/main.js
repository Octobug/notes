/**
 * @return {Function}
 */
var createHelloWorld = function () {
  // eslint-disable-next-line no-unused-vars
  return function (...args) {
    return 'Hello World';
  };
};


const f = createHelloWorld();
f(); // "Hello World"
f({}, null, 42);
