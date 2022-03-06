'use strict';

var fs = require('fs');

// read stream
var rs = fs.createReadStream('sample.txt', 'utf-8');

rs.on('data', function (chunk) {
  console.log('DATA: ');
  console.log(chunk);
});

rs.on('end', function () {
  console.log('END');
});

rs.on('error', function (err) {
  console.log('ERROR: ' + err)
});

// write stream
var ws1 = fs.createWriteStream('output1.txt', 'utf-8');
ws1.write('使用Stream写入文本数据...\n');
ws1.write('END.');
ws1.end();

var ws2 = fs.createWriteStream('output2.txt');
ws2.write(Buffer.from('使用Stream写入二进制数据...\n', 'utf-8'));
ws2.write(Buffer.from('END.', 'utf-8'));
ws2.end();

// pipe
var rs = fs.createReadStream('sample.txt');
var ws = fs.createWriteStream('copied.txt')

rs.pipe(ws)