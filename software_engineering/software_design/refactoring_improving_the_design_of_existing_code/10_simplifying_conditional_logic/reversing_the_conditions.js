function version1() {
  function adjustedCapital(anInstrument) {
    let result = 0;
    if (anInstrument.capital > 0) {
      if (anInstrument.interestRate > 0 && anInstrument.duration > 0) {
        result = (anInstrument.income / anInstrument.duration) * anInstrument.adjustmentFactor;
      }
    }
    return result;
  }
}

function version2() {
  function adjustedCapital(anInstrument) {
    let result = 0;
    if (anInstrument.capital <= 0) {
      return result;
    }

    if (anInstrument.interestRate > 0 && anInstrument.duration > 0) {
      result = (anInstrument.income / anInstrument.duration) * anInstrument.adjustmentFactor;
    }
    return result;
  }
}

function version3() {
  function adjustedCapital(anInstrument) {
    let result = 0;
    if (anInstrument.capital <= 0) {
      return result;
    }

    if (!(anInstrument.interestRate > 0 && anInstrument.duration > 0)) {
      return result;
    }

    result = (anInstrument.income / anInstrument.duration) * anInstrument.adjustmentFactor;
    return result;
  }
}

function version4() {
  function adjustedCapital(anInstrument) {
    let result = 0;
    if (anInstrument.capital <= 0) {
      return result;
    }

    if (anInstrument.interestRate <= 0 || anInstrument.duration <= 0) {
      return result;
    }

    result = (anInstrument.income / anInstrument.duration) * anInstrument.adjustmentFactor;
    return result;
  }
}

function version5() {
  function adjustedCapital(anInstrument) {
    let result = 0;
    if (anInstrument.capital <= 0
      || anInstrument.interestRate <= 0
      || anInstrument.duration <= 0) {
      return result;
    }

    result = (anInstrument.income / anInstrument.duration) * anInstrument.adjustmentFactor;
    return result;
  }
}

function version6() {
  function adjustedCapital(anInstrument) {
    if (anInstrument.capital <= 0
      || anInstrument.interestRate <= 0
      || anInstrument.duration <= 0) {
      return 0;
    }

    return (anInstrument.income / anInstrument.duration) * anInstrument.adjustmentFactor;
  }
}
