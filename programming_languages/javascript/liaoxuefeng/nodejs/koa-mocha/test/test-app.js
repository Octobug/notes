const request = require('supertest');
const app = require('../app');

describe('#test koa app', () => {
  const server = app.listen(9900);

  describe('#test server', () => {
    it('#test GET /', async () => {
      const res = await request(server)
        .get('/')
        .expect('Content-Type', /text\/html/)
        .expect(200, '<h1>Hello, world!</h1>');
    });

    it('#test GET /path?name=Bob', async () => {
      const res = await request(server)
        .get('/path?name=Bob')
        .expect('Content-Type', /text\/html/)
        .expect(200, '<h1>Hello, Bob!</h1>');
    });
  });

  server.close();
});
