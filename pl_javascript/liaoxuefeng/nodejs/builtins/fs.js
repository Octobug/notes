'use strict';

var fs = require('fs');

// async read
fs.readFile('sample.txt', 'utf-8', function (err, data) {
  if (err) {
    console.log(err);
  } else {
    // console.log(data.toString('utf-8'));
    console.log('async read: ' + data);
  }
});

fs.readFile('sample.jpg', function (err, data) {
  if (err) {
    console.log(err);
  } else {
    console.log(data)
    console.log(data.length + 'bytes')
  }
})

// sync read
try {
  var data = fs.readFileSync('sample.txt', 'utf-8')
  console.log("sync read: " + data)
} catch (err) {
  console.log(err)
}

// sync write
var data = 'Hello, Node.js';
fs.writeFile('output.txt', data, function (err) {
  if (err) {
    console.log(err);
  } else {
    console.log('ok.');
  }
})

// stat
fs.stat('sample.txt', function (err, stat) {
  if (err) {
    console.log(err);
  } else {
    console.log('isFile: ' + stat.isFile());
    console.log('isDirectory: ' + stat.isDirectory());
    if (stat.isFile()) {
      console.log('size: ' + stat.size);
      console.log('birth time: ' + stat.birthtime);
      console.log('modified time: ' + stat.mtime)
    }
  }
})
