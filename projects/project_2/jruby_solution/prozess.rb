class Prozess
  attr_accessor :name
  def initialize(name)
    @name = name
    @resources = [] 
  end

  def resources
    @resources
  end

  def add_resource(resource)
    @resources << resource
  end

  def remove_resource(resource)
    @resources.remove(resource)
  end
end
