function version1() {
  function createResource() { }

  const availableResources = [];
  const allocatedResources = [];
  
  let result;
  if (availableResources.length === 0) {
    result = createResource();
    allocatedResources.push(result);
  } else {
    result = availableResources.pop();
    allocatedResources.push(result);
  }
  return result;
}

function version2() {
  function createResource() { }

  const availableResources = [];
  const allocatedResources = [];
  
  let result;
  if (availableResources.length === 0) {
    result = createResource();
  } else {
    result = availableResources.pop();
  }
  allocatedResources.push(result);
  return result;
}
