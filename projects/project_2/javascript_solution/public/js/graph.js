layouter = null;
renderer = null;
set = [];

/*
* Get all nodes that node is pointing to 
*/
function nodesFromNode(node){
  connected = [];

  for(var i = 0; i < node.edges.length; i++) {
    edge = node.edges[i];
    if(edge.source.id == node.id) {
      connected.push(edge.target);
    }
  }

  return connected;
}

function removeEdgeFromGraph(edge) {
  for(var i = 0; i < graph.edges.length; i++) {
    currentEdge = graph.edges[i];

    if(currentEdge.source.id == edge.source.id && currentEdge.target.id == edge.target.id && removedEdges.indexOf(edge) == -1) {
      removedEdges.push(edge);
    }
  }
}

/*
* Get the edge that connects the source to the target
*/
function connectingEdge(from, to) {
  for(var i = 0; i < graph.edges.length; i++) {
    edge = graph.edges[i];
    if(edge.source.id == from.id && edge.target.id == to.id) {
      return edge;
    }
  }
  return null;
}

/*
* Returns true if a node has incoming edges, false otherwise
*/
function hasNoIncomingEdges(node) {
  if(node.edges.length == 0) {
    return true;
  }

  for(var i = 0; i < node.edges.length; i++) {
    nodeEdge = node.edges[i];
    for(var j = 0; j < removedEdges.length; j++) {
      remEdge = removedEdges[j];

      if(nodeEdge.source.id == remEdge.source.id && nodeEdge.target.id == remEdge.target.id) {
        return true;
      }
    }
  }
  return false;
}

function graphHasCycle() {
  for(var key in graph.nodes) {
    node = graph.nodes[key];

    for(var i = 0; i < node.edges.length; i++) {
      edge = node.edges[i];

      if(removedEdges.indexOf(edge) == -1) {
        return true;
      }
    }
  }
  return false;
}

function nodeExists(nodes, node) {
  for(var i = 0; i < nodes.length; i++) {
    if(nodes[i].id == node.id) {
      return true;
    }
  }
  return false;
}


/*****************************************************
* Officially completed code BENEATH
*****************************************************/


//
// Create a new graph object
//
function createGraph() {
  return new Graph();
}

//
// Add a node to a graph
//
function addNode(name) {
  graph.addNode(name, {label: name});
}


//
//Add an edge to a graph
//
function addEdge(source, target) {
  graph.addEdge(source, target, {directed: true});
}


//Show the graph
//Only create a new layouter & renderer if not already created
//
function show() {
  if(!layouter) {
    layouter = new Graph.Layout.Spring(graph);
  } else {
    layouter.layout();
  }

  if(!renderer) {
    renderer = new Graph.Renderer.Raphael('canv', graph, 400, 300);
  }

  renderer.draw();
}

//
// Remove an edge from the source and target node
//
function removeEdgeFromNodes(from, to) {
  for(var key in graph.nodes) {
    node = graph.nodes[key];

    if(node.id == from || node.id == to) {

      for(var i = 0; i < node.edges.length; i++) {
        edge = node.edges[i];

        if(edge.source.id == from && edge.target.id == to) {
          console.log("Removing edge from nodes", edge);
          node.edges.splice(i, 1);
        }
      }
    }
  }
}

//
// Remove an edge from the graph
// This must be called to avoid stray arrows on the screen
//
function removeEdgeFromGraph(from, to) {
  for(var i = 0; i < graph.edges.length; i++) {
    edge = graph.edges[i];

    console.log(edge.source.id, " TO ", edge.target.id);
    if(edge.source.id == from && edge.target.id == to) {
      edge.hide();
      graph.edges.splice(i, 1);
    }
  }
}

//
//Remove an edge
//
function removeEdge(from, to) {
  removeEdgeFromNodes(from, to);
  removeEdgeFromGraph(from, to);
}

/*
* Get all nodes that have no incoming edges 
*/
function getNodesWithNoInDegree() {
  result = [];

  for(var key in graph.nodes) {
    node = graph.nodes[key];
    incomingNode = false;

    for(var i = 0; i < node.edges.length; i++) {
      edge = node.edges[i];
      if(edge.target.id == node.id) {
        incomingNode = true;
      }
    }

    if(!incomingNode) {
      result.push(node);
    }
  }
  return result;
}

/*
* Find all the nodes that have a source of node
*/
function findAllNodesWithEdgeFrom(node) {
  neighbors = [];

  for(var i = 0; i < graph.edges.length; i++) {
    edge = graph.edges[i];

    if(edge.source.id == node) {
      neighbors.push(edge.target);
    }
  }
  return neighbors;
}

function findEdge(from, to) {
  for(var i = 0; i < graph.edges.length; i++) {
    edge = graph.edges[i];

    if(edge.source.id == from && edge.target.id == to) {
      return edge;
    }
  }
  return null;
}

function getRemovedEdgeCountFor(node, removedEdges) {
  remCount = 0;
  for(var i = 0; i < node.edges.length; i++) {
    edge = node.edges[i];

    if(removedEdges.indexOf(edge) != -1) {
      remCount++;
    }
  }
  return remCount;
}

/*
* Determine if a node has any incoming edges
*/
function hasNoInDegree(node, removedEdges) {
  removedCount = getRemovedEdgeCountFor(node, removedEdges);
  console.log(removedCount);
  if(graph.nodes[node.id].edges.length - removedCount == 0) {
    return true;
  } else {
    return false;
  }
}


function checkForCycle() {
  sorted = [];
  removedEdges = [];
  emptyNodes = getNodesWithNoInDegree();

  while(emptyNodes.length > 0) {
    var i = 0;

    firstNode = emptyNodes.pop();
    sorted.push(firstNode);
    
    neighborNodes = findAllNodesWithEdgeFrom(firstNode.id);

    for(var j = 0; j < neighborNodes.length; j++) {
      secondNode = neighborNodes[i];
      edgeToRemove = findEdge(firstNode.id, secondNode.id);

      removedEdges.push(edgeToRemove);

      if(hasNoInDegree(secondNode, removedEdges)) {
        emptyNodes.push(secondNode);
      }
    }
    i++;
  }

  if(removedEdges.length - graph.edges.length > 0) {
    console.log("Cycle!");
  } else {
    console.log("No cycle!");
  }
}
