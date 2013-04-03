layouter = null;
renderer = null;

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
  outgoingEdgesCount = findAllNodesWithEdgeFrom(node.id).length; 

  if(graph.nodes[node.id].edges.length - (removedCount + outgoingEdgesCount) == 0) {
    return true;
  } else {
    return false;
  }
}


function isCycle() {
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

  if(graph.edges.length - removedEdges.length > 0) {
    return true;
  } else {
    return false;
  }
}
