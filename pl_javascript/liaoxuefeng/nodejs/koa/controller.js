const fs = require('fs');
const path = require('path');

function addMapping(router, mapping) {
  for (const url in mapping) {
    if (url.startsWith('GET ')) {
      const path = url.substring(4);
      router.get(path, mapping[url]);
      console.log(`register URL mapping: GET ${path}`);
    } else if (url.startsWith('POST ')) {
      const path = url.substring(5);
      router.post(path, mapping[url]);
      console.log(`register URL mapping: POST ${path}`);
    } else {
      console.log(`invalid URL: ${url}`);
    }
  }
}

function addControllers(router, dir) {
  const files = fs.readdirSync(path.join(__dirname, './controllers'));
  const jsFiles = files.filter(f => {
    return f.endsWith('.js');
  });

  for (const f of jsFiles) {
    console.log(`process controller: ${f}...`);
    const mapping = require(path.join(__dirname, './controllers/', f));
    addMapping(router, mapping);
  }
}

module.exports = function(dir) {
  const controllersDir = dir || 'nodejs/koa/controllers';
  const router = require('koa-router')();
  addControllers(router, controllersDir);
  return router.routes();
};
