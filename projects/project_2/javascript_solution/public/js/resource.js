function createResource(pName) {
  hash = {};
  hash["name"] = pName;

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
