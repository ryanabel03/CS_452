require_relative 'file_reader.rb'
require_relative 'file_parser.rb'
require_relative 'resource.rb'
require_relative 'prozess.rb'
require_relative 'graph_wrapper.rb'

class Presenter
  include FileParser 

  def initialize
    @processes = {}
    @resources = {} 
    @file_reader = FileReader.new "input.txt"
    @graph_wrapper = GraphWrapper.new
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
      process = Prozess.new process_name
      @graph_wrapper.add_vertex(process_name)
      @processes[process_name.to_sym] = process
    else
      process = @processes[process_name.to_sym]
    end

    if !exists?(@resources, resource_name)
      puts "Creating new resource..."
      resource = Resource.new resource_name 
      @graph_wrapper.add_vertex(resource_name)
      @resources[resource_name.to_sym] = resource
    else
      puts "Resource already existed"
      resource = @resources[resource_name.to_sym]
    end

    perform_action(process, action, resource)
  end


  def exists?(hash, key)
    hash[key] ? true : false
  end

  def perform_action(process, action, resource)
    case action
    when "requests"
      request_resource(process, resource)
    else
      release_resource(process, resource)
    end
    @graph_wrapper.write_graph_to_file
  end


  def request_resource(process, resource)
    puts "Performing request action"
    if !resource.process?
      resource.process process.name
      @graph_wrapper.add_edge(process.name, resource.name)
    else
      resource.add_to_queue process.name
    end
  end

  def release_resource(process, resource)
    if resource.process?
      resource.remove_process process.name
      @graph_wrapper.remove_edge(process.name, resource.name)
      if !resource.empty_queue?
        new_process = resource.pop_queue
        resource.process(new_process)
        @graph_wrapper.add_edge(new_process)
      end
    end
    puts "Performing release action"
  end
end
