require 'rgl/adjacency'
require 'rgl/dot'

class GraphWrapper

  def initialize
    @graph = RGL::DirectedAdjacencyGraph.new 
  end

  def add_vertex(name)
    @graph.add_vertex(name)
  end

  def add_edge(source, target)
    @graph.add_edge(source, target)
  end

  def write_graph_to_file
    @graph.write_to_graphic_file
  end

  def remove_vertex(name)
    @graph.remove_vertex(name)
  end

  def remove_edge(source, target)
    @graph.remove_edge(source, target)
  end
end
