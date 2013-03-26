require_relative 'file_reader.rb'
require_relative 'file_parser.rb'
require_relative 'resource.rb'

class Presenter
  include FileParser 

  def initialize
    @processes = nil
    @resources = nil
    @file_reader = FileReader.new "input.txt"
  end

  def next_line
    line = @file_reader.read_next_line

    if line.include?("processes") || line.include?("resources")
      #Maybe use this to print a view initially?
    else
      determine_action(parse_line(line))
    end
  end

  def determine_action(line_hash)
    process_name = line_hash[:process_name]
    action = line_hash[:action]
    resource_name = line_hash[:resource_name]

    if !exists?(@processes, process_name)
      puts "Creating new process..."
      process = Process.new process_name
      @processes <<  process
    else
      puts "Process already existed"
      process = @processes[@process.index(process_name)]
    end

    if !exists?(@resources, resource_name)
      puts "Creating new resource..."
      resource = Resource.new resource_name 
      @resources << resource 
    else
      puts "Resource already existed"
      resource = @resources[@resources.index(resource_name)]
    end

    perform_action(process, action, resource)
  end


  def exists?(arr, name)
    arr.each do |elem|
      if elem.name == name
        return true
      end
    end
    return false
  end




  def perform_action(process, action, resource)
    case action
    when "request"
      request_resource(process, resource)
    else
      release_resource(process, resource)
    end
  end


  def request_resource(process, resource)
    puts "Performing request action"
    if !resource.process?
      resource.add_process process.name
    end
  end

  def release_resource(process, resource)
    puts "Performing release action"
  end
end
