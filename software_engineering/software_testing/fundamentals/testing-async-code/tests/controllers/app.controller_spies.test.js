/* global describe, it */
const chai = require('chai');
const expect = chai.expect;
const sinon = require('sinon');
const indexPage = require('../../controllers/app.controller_spies');


const user = {
  addUser: (name) => {
    this.name = name;
  }
};

describe('AppController', () => {
  describe('getIndexPage', function () {
    it('should send hey', function () {
      let req = {};
      // Have `res` have a send key with a function value coz we use 
      //  `res.send()` in our func
      let res = {
        send: sinon.spy()
      };

      indexPage.getIndexPage(req, res);
      // `res.send` called once
      expect(res.send.calledOnce).to.be.true;
      // expect to get argument `bla` on first call
      expect(res.send.firstCall.args[0]).to.equal('Hey');
    });
  });

  describe('User', function () {
    describe('addUser', function () {
      it('should add a user', function () {
        // user.addUser()
        sinon.spy(user, 'addUser');
        user.addUser('John Doe');

        expect(user.addUser.calledOnce).to.be.true;
      });
    });
  });
});
