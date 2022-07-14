/* global describe, it, before, beforeEach, after, afterEach */
const assert = require('assert');
const { expect } = require('chai');
const {
  Province,
  sampleProvinceData
} = require('./sample');


describe('province', function () {
  it('shortfall', function () {
    const asia = new Province(sampleProvinceData());
    assert.equal(asia.shortfall, 5);
  });

  it('shortfall', function () {
    const asia = new Province(sampleProvinceData());
    expect(asia.shortfall).equal(5);
  });
});
