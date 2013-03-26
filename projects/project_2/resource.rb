class Resource
  def initialize(name)
    @name = name
    @process = nil
  end

  def name
    @name
  end

  def name(name)
    @name = name
  end

  def add_process(process)
    @process = process
  end

  def remove_process(process)
    @process = nil
  end

  def process?
    @process ? true : false
  end
end
