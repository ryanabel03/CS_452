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
    } else if (count <= total) {
      line = nextLine();
      hash = parseLine(line);
      executeRequest(hash);
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

  if(processes.indexOf(process) == -1) {
    process = createProcess(process);
    graph = addNode(graph, process["name"]);
    processes.push(process);
  }

  if(resources.indexOf(resource) != -1) {
    resources.push(resource);
  }

  doAction(process, action, resource);
}

function doAction(process, action, resource) {
  switch(action) {
    case "request":
      if(resource["process"]) {
        resource = addWaitingProc(resource, process);
      } else {
        resource = setProcess(resource, process);
      }
      break;
    case "release":
      resource = removeProcess(resource);
      break;
  }
}
