module FileParser

  def parse_header(line)
    return line.split(" ").first.to_i
  end

  def parse_line(line)
    split_line = line.split(" ")
    hash = {}

    hash[:process_name] = split_line.shift
    hash[:action] = split_line.shift
    hash[:resource_name] = split_line.shift

    return hash
  end
end
