const chai = require("chai");
const expect = chai.expect;
// import our getIndexPage function
const indexPage = require("../../controllers/app.controller");


describe("getIndexPage", function () {
  it("should return index page", function () {
    let req = {}
    // Have `res` have a send key with a function value coz we use `res.send()`
    //  in our func
    let res = {
      send: function () { }
    }

    indexPage.getIndexPage(req, res)
  });
});
