function blah () {
  sigRoot = document.getElementById('sigma-example')
  sigInst = sigma.init(sigRoot)
  nodeCount = 0
  window.debugSigInst = sigInst

  sigInst.drawingProperties({
    defaultLabelColor: '#fff',
    defaultLabelSize: 14,
    defaultLabelBGColor: '#fff',
    defaultLabelHoverColor: '#000',
    labelThreshold: 6,
    defaultEdgeType: 'curve'
  }).graphProperties({
    minNodeSize: 5,
    maxNodeSize: 5,
    minEdgeSize: 1,
    maxEdgeSize: 1
  }).mouseProperties({
    maxRatio: 4
  });

  sigInst.addNode('hello',{
    label: 'Hello',
    color: '#ff0000'
  });

  sigInst.addNode('world',{
    label: 'World !',
    color: '#00ff00'
  });

  sigInst.addEdge('hello_world','hello','world');

  sigInst.draw();
}
