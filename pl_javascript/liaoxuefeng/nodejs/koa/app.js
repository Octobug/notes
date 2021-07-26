const bodyParser = require('koa-bodyparser');
const Koa = require('koa');
const path = require('path');

const controller = require('./controller');
const templating = require('./templating');

const isProduction = process.env.NODE_ENV === 'production';

const app = new Koa();

// log request URL:
app.use(async(ctx, next) => {
  console.log(`Process ${ctx.request.method} ${ctx.request.url}...`);
  const start = new Date().getTime();
  await next();
  const execTime = new Date().getTime() - start;
  ctx.response.set('X-Response-Time', `${execTime}ms`);
});

if (!isProduction) {
  const staticFiles = require('./static-files');
  app.use(staticFiles('/static/', path.join(__dirname, '/static')));
}

app.use(bodyParser());

app.use(templating('views', {
  noCache: !isProduction,
  watch: !isProduction
}));

// add router middleware:
app.use(controller());

app.listen(3000);
console.log('app started at port 3000...');
