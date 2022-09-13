const fs = require('fs');

const start = new Date();

function someAsyncOperation(callback) {
  // Assume this takes 95ms to complete
  fs.readFile('../README.md', callback);
}

const timeoutScheduled = Date.now();

setTimeout(() => {
  const delay = Date.now() - timeoutScheduled;

  console.log(`${delay}ms have passed since I was scheduled`);
}, 100);

// do someAsyncOperation which takes 95 ms to complete
someAsyncOperation(() => {
  const startCallback = Date.now();
  console.log(`${startCallback - start} ms have passed since started fs`);

  // do something that will take 10ms...
  while (Date.now() - startCallback < 10) {
    // do nothing
  }
});
