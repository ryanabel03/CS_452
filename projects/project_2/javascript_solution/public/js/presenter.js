processes = [];
resources = [];
graph = null;

$(document).ready( function () {
  graph = createGraph();

  $("#step-button").click(function() {
    count = currentCount(); 
    total = totalCount();

    if(count == 0) {
      loadFile();
      line = nextLine();
    } else if (count <= 2) {
      line = nextLine();
      //Parse header
    } else if (count < total) {
      line = nextLine();
      hash = parseLine(line);
      executeRequest(hash);
      isThereCycle(graph);
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
    graph = addNode(graph, process);
    process = createProcess(process);
    processes.push(process);
  } else {
    process = findProcess(process, processes); 
  }

  if(!exists(resource, resources)) {
    graph = addNode(graph, resource);
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
        graph = addEdge(graph, process["name"], resource["name"]);
        resource = addWaitingProc(resource, process);
      } else {
        graph = addEdge(graph, resource["name"], process["name"]);
        resource = setProcess(resource, process);
      }
      break;
    case "releases":
      resource = removeProcess(resource);
      break;
  }
}
