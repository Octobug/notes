function version1() {
  function distanceTravelled(scenario, time) {
    let result;
    let acc = scenario.primaryForce / scenario.mass;
    let primaryTime = Math.min(time, scenario.delay);
    result = 0.5 * acc * primaryTime * primaryTime;
    let secondaryTime = time - scenario.delay;
    if (secondaryTime > 0) {
      let primaryVelocity = acc * scenario.delay;
      acc = (scenario.primaryForce + scenario.secondaryForce) / scenario.mass;
      result += primaryVelocity * secondaryTime + 0.5 * acc * secondaryTime * secondaryTime;
    }
    return result;
  }
}

function version2() {
  function distanceTravelled(scenario, time) {
    let result;
    const primaryAcceleration = scenario.primaryForce / scenario.mass;
    let primaryTime = Math.min(time, scenario.delay);
    result = 0.5 * primaryAcceleration * primaryTime * primaryTime;
    let secondaryTime = time - scenario.delay;
    if (secondaryTime > 0) {
      let primaryVelocity = primaryAcceleration * scenario.delay;
      let acc = (scenario.primaryForce + scenario.secondaryForce) / scenario.mass;
      result += primaryVelocity * secondaryTime + 0.5 * acc * secondaryTime * secondaryTime;
    }
    return result;
  }
}

function version3() {
  function distanceTravelled(scenario, time) {
    let result;
    const primaryAcceleration = scenario.primaryForce / scenario.mass;
    let primaryTime = Math.min(time, scenario.delay);
    result = 0.5 * primaryAcceleration * primaryTime * primaryTime;
    let secondaryTime = time - scenario.delay;
    if (secondaryTime > 0) {
      let primaryVelocity = primaryAcceleration * scenario.delay;
      const secondaryAcceleration = (
        scenario.primaryForce + scenario.secondaryForce
      ) / scenario.mass;
      result += primaryVelocity * secondaryTime
        + 0.5 * secondaryAcceleration * secondaryTime * secondaryTime;
    }
    return result;
  }
}
