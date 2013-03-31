class FileReader

  def initialize(file)
    @file = File.open(file, "r")
    @lines = @file.readlines
    @count = 0
    @size = @lines.size
  end

  def read_next_line
    line = @lines.shift
    @count += 1
    return line
  end

  def is_empty?
    @count == @lines.size - 1 ? true : false
  end

  def size
    @size
  end

  def count
    @count
  end
end
