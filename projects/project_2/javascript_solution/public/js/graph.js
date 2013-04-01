layouter = null;
renderer = null;
set = [];
removedEdges = [];

function createGraph() {
  return new Graph();
}

function addNode(name) {
  graph.addNode(name, {label: name});
}

function addEdge(source, target) {
  graph.addEdge(source, target, {directed: true});
}

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


/*
* Get all nodes that have no incoming edges 
*/
function getEmptyNodes() {
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

    if(currentEdge.source.id == edge.source.id && currentEdge.target.id == edge.target.id) {
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

function isThereCycle() {
  emptyNodes = [];
  emptyNodes = getEmptyNodes(); 
  sorted = [];

  for(var i = 0; i < emptyNodes.length; i++) {
    node = emptyNodes[i];

    sorted.push(node);

    nodes = nodesFromNode(node);

    for(var j = 0; j < nodes.length; j++) {
      newNode = nodes[j];
      edge = connectingEdge(node, newNode);
      removeEdgeFromGraph(edge);

      if(hasNoIncomingEdges(newNode)) {
        console.log("No more incoming edges");
      }
    }
  }
}

function detectCycle(node) {
  set.push(node);

  for(var i = 0; i < graph.edges.length; i++) {
    visited = false;
    edge = graph.edges[i];

    if(edge.source.id == node) {
      for(var j = 0; j < set.length; j++) {
        if(set[j] == edge.source.id) {
          visited = true;
        }
      }

      if(visited) {
        console.log("Found cycle!");
        return true;
      }
    }
  }
  console.log("No cycle");
  return false;
}
