function version1() {
  function discount(inputValue, quantity) {
    if (inputValue > 50) {
      inputValue = inputValue - 2;
    }
    if (quantity > 100) {
      inputValue = inputValue - 1;
    }
    return inputValue;
  }
}

function version2() {
  function discount(originalInputValue, quantity) {
    let inputValue = originalInputValue;
    if (inputValue > 50) {
      inputValue = inputValue - 2;
    }
    if (quantity > 100) {
      inputValue = inputValue - 1;
    }
    return inputValue;
  }
}

function version3() {
  function discount(inputValue, quantity) {
    let result = inputValue;
    if (inputValue > 50) {
      result = result - 2;
    }
    if (quantity > 100) {
      result = result - 1;
    }
    return result;
  }
}
