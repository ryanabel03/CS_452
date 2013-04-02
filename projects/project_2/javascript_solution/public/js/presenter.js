processes = [];
resources = [];

$(document).ready( function () {
     graph = createGraph();

  $("#step-button").click(function() {
    count = currentCount(); 
    total = totalCount();

    if(count == 0) {
      loadFile();
      line = nextLine();
    } else if (count <= 1) {
      line = nextLine();
      //Parse header
    } else if (count < total) {
      line = nextLine();
      hash = parseLine(line);
      executeRequest(hash);
      // isThereCycle(graph);
      show(graph);
    } else {
      alert("You have reached the end of the file");
    }

    $("#count-text").show();
    $("#count-text").html("Line " + count + " of " + total);
  });

});

function executeRequest(hash) {
  process = hash["process"];
  action = hash["action"];
  resource = hash["resource"];

  if(!exists(process, processes)) {
    addNode(process);
    process = createProcess(process);
    processes.push(process);
  } else {
    process = findProcess(process, processes); 
  }

  if(!exists(resource, resources)) {
    addNode(resource);
    resource = createResource(resource);
    resources.push(resource);
  } else {
    resource = findResource(resource, resources);
  }

  doAction(process, action, resource);
}

function doAction(process, action, resource) {
  switch(action) {
    case "requests":
      if(resource["process"]) {
         addEdge(process["name"], resource["name"]);
        resource = addWaitingProc(resource, process);
      } else {
         addEdge(resource["name"], process["name"]);
        resource = setProcess(resource, process);
      }
      break;
    case "releases":
      removeEdge(resource["name"], resource["process"]["name"]);
      resource = removeProcess(resource);
      if(resource["process"]) {
        removeEdge(resource["process"]["name"], resource["name"]);
        addEdge(resource["name"], resource["process"]["name"]);
      }
      break;
  }
}
