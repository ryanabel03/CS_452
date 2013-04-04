/*
* Create a process
*/
function createProcess(pName) {
  hash = {};
  hash["name"] = pName;
  return hash;
}


/*
* Add a resource to a process
*/
function addResource(process, resource) {
  process["resource"] = resource;
  return process;
}


/*
* Remove a resource from a process
*/
function removeResource(process, resource) {
  process["resource"] = null;
}


/*
* Check if a process already exists
*/
function exists(process, processes) {
  for(var index in processes) {
    if(processes[index]["name"] == process) {
      return true;
    }
  }
  return false;
}

/*
* Find a process
*/
function findProcess(process, processes) {
  for(var index in processes) {
    if(processes[index]["name"] == process) {
      return processes[index];
    }
  }
  return null;
}
