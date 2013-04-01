layouter = null;
renderer = null;
set = [];

function createGraph() {
  return new Graph();
}

function addNode(graph, name) {
  graph.addNode(name, {label: name});
  return graph;
}

function addEdge(graph, source, target) {
  graph.addEdge(source, target, {directed: true});
  return graph;
}

function show(graph) {
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

function adjacentEdges(graph, node) {
  result = [];
  for(var i = 0; i < graph.edges.length; i++) {
    edge = graph.edges[i];

    if(edge.source.id == node) {
      result.push(edge);
    }
  }
  console.log(result);
  return result;
}

function isThereCycle(graph) {
  for(var key in graph.nodes) {
    blah = adjacentEdges(graph, key);
  }
  return blah;
}

function detectCycle(graph, node) {
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
