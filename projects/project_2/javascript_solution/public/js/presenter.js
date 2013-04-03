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
      show(graph);

      if(isCycle()) {
        alert("Detected a cycle!");
      }

    } else {
      alert("You have reached the end of the file");
    }


    $("#count-text").show();
    $("#count-text").html("Line " + count + " of " + total);

    $("#last-action-text").html("Processed line: " + line);
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

        $("#last-result-text").html(process["name"] + " Requested (but does not own) " + resource["name"]);
      } else {
        addEdge(resource["name"], process["name"]);
        resource = setProcess(resource, process);

        $("#last-result-text").html(process["name"] + " Now owns " + resource["name"]);
      }
      break;
    case "releases":
      removeEdge(resource["name"], resource["process"]["name"]);
      htmlText = resource["process"]["name"] + " Released " + resource["name"];

      resource = removeProcess(resource);

      if(resource["process"]) {
        removeEdge(resource["process"]["name"], resource["name"]);
        addEdge(resource["name"], resource["process"]["name"]);
        htmlText += " AND " + resource["process"]["name"] + " Now owns " + resource["name"];
      }

      $("#last-result-text").html(htmlText);
      break;
  }
}
