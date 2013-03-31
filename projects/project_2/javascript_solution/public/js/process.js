function createProcess(pName) {
  hash = {};
  hash["name"] = pName;
  return hash;
}

function addResource(process, resource) {
  process["resource"] = resource;
  return process;
}

function removeResource(process, resource) {
  process["resource"] = null;
}
