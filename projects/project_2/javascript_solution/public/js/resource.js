/*
* All the functions related to resources
*/

/*
* Create a new resource
*/
function createResource(pName) {
  hash = {};
  hash["name"] = pName;
  hash["waitingProcs"] = [];

  return hash;
}


/*
* Add a process to the waiting queue
*/
function addWaitingProc(resource, process) {
  resource["waitingProcs"].push(process);

  return resource;
}


/*
* Set the owner process of the resource
*/
function setProcess(resource, process) {
  resource["process"] = process;
  return resource;
}


/*
* Remove the owner process And possibly set new process as owner
*/
function removeProcess(resource) {
  if(resource["waitingProcs"]) {
    resource["process"] = resource["waitingProcs"].reverse().pop();
  } else {
    resource["process"] = null;
  }

  return resource;
}

/*
* Check if a resource already exists
*/
function exists(resource, resources) {
  for(var index in resources) {
    if(resources[index]["name"] == resource) {
      return true;
    }
  }
  return false;
}

/*
* Find an exisiting resource
*/
function findResource(resource, resources) {
  for(var index in resources) {
    if(resources[index]["name"] == resource) {
      return resources[index];
    }
  }
  return null;
}
