/*
* This group of function is responsible for delegating tasks to other files and altering the view
*/

// Globals
processes = [];
resources = [];

// Do all things when the document is loaded
$(document).ready( function () {
     graph = createGraph();

  //Click the step button
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

/*
* Add or find processes and resources for the current line
*/
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

/*
* Determine the correct action to take and execute it
*/
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
