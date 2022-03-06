'use strict';

const
  fs = require('fs');
const url = require('url');
const path = require('path');
const http = require('http');

// get root dir from command line args
const root = path.resolve(process.argv[2] || '.');
console.log('Static root dir: ' + root);

// create server
const server = http.createServer((request, response) => {
  // get url's path
  const pathname = url.parse(request.url).pathname;
  // get correspond local path
  const filepath = path.join(root, pathname);
  // get file states
  fs.stat(filepath, (err, stats) => {
    if (!err && stats.isFile()) {
      // ok
      console.log('200 ' + request.url);
      // redirect stream to response:
      fs.createReadStream(filepath).pipe(response);
    } else {
      // error
      console.log('404 ' + request.url);
      response.writeHead(404);
      response.end('404 Not Found');
    }
  });
});

server.listen(8080);
console.log('Server is running at http://localhost:8080/');
