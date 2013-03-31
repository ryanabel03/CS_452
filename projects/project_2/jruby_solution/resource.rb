class Resource
  attr_accessor :name
  def initialize(name)
    @name = name
    @process = nil
  end

  def process(process)
    @process = process
  end

  def remove_process(process)
    @process = nil
  end

  def process?
    @process ? true : false
  end

  def add_to_queue process
    @queue << process
  end

  def remove_from_queue process
    @queue.remove(process)
  end

  def empty_queue?
    @queue ? false : true
  end

  def pop_queue
    return @queue.shift
  end
end
