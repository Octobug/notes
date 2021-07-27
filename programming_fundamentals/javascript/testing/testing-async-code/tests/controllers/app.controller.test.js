/* global describe, it */
const chai = require('chai');
const expect = chai.expect;
const sinon = require('sinon');
const indexPage = require('../../controllers/app.controller');


describe('getIndexPage', function () {
  it('should return index page', function () {
    let req = {};
    // Have `res` have a send key with a function value coz we use `res.send()`
    //  in our func
    let res = {
      send: function () { }
    };

    indexPage.getIndexPage(req, res);
  });
});
