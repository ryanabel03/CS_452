function createGraph() {
  return new Graph();
}

function addNode(graph, name) {
  graph.addNode(name);
  return graph;
}

function show(graph) {
  layouter = new Graph.Layout.Spring(graph);
  layouter.layout();

  renderer = new Graph.Renderer.Raphael('canvas', graph, 600, 400);
  renderer.draw();
}
