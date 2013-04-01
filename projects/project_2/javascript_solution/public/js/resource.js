function createResource(pName) {
  hash = {};
  hash["name"] = pName;
  hash["waitingProcs"] = [];

  return hash;
}

function addWaitingProc(resource, process) {
  resource["waitingProcs"].push(process);

  return resource;
}

function setProcess(resource, process) {
  resource["process"] = process;
  return resource;
}

function removeProcess(resource) {
  if(resource["waitingProcs"]) {
    resource["process"] = resource["waitingProcs"].reverse().pop();
  } else {
    resource["process"] = null;
  }

  return resource;
}

function exists(resource, resources) {
  for(var index in resources) {
    if(resources[index]["name"] == resource) {
      return true;
    }
  }
  return false;
}

function findResource(resource, resources) {
  for(var index in resources) {
    if(resources[index]["name"] == resource) {
      return resources[index];
    }
  }
  return null;
}
