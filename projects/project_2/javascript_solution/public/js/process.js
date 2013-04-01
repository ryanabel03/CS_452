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

function exists(process, processes) {
  for(var index in processes) {
    if(processes[index]["name"] == process) {
      return true;
    }
  }
  return false;
}

function findProcess(process, processes) {
  for(var index in processes) {
    if(processes[index]["name"] == process) {
      return processes[index];
    }
  }
  return null;
}
