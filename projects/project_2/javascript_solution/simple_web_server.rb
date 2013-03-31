require 'sinatra'
require 'haml'

set :haml, format: :html5

get '/' do
  haml :index
end

get '/input.txt' do
  send_file "input.txt"
end
