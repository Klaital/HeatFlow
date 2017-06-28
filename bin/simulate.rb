require 'optparse'

require_relative '../lib/project.rb'
require_relative '../lib/simulator.rb'

project_file_path = ''
max_iterations = 0

OptionParser.new do |o|
    o.banner = "Run a HeatFlow Simulation\nUsage: ruby simulate.rb [options]"
    o.on_tail('-h', '--help', 'Display this help text') do
        puts o
        exit
    end

    o.on('-p', '--project PATH', 'Path to project config file.') do |p|
        project_file_path = p
    end

    o.on('-s', '--steps NUM', 'Number of simulation iterations to run') do |num|
        max_iterations = num.to_i
    end

end.parse!

project = Project.from_file(project_file_path)
puts "Starting Simulation."
puts ">Iterations: #{max_iterations}"
puts ">Got config:"
puts JSON.pretty_generate(project.to_h)


puts ">Initializing simulator"
simulator = Simulator.new(project_config: project)
simulator.simulation_init
step_runtimes = []
1.upto(max_iterations) do |iteration|
    start_time = Time.now.to_f
    puts ">>Iteration #{iteration}"
    simulator.simulate_step
    puts ">> Elapsed Time: #{simulator.elapsed_time} ms"
    runtime = Time.now.to_f - start_time
    puts ">> Step Runtime: #{runtime}"
    step_runtimes.push(runtime)
end

total_step_time = 0.0
step_runtimes.each {|t| total_step_time += t}
puts "> Total Step Runtime: #{total_step_time}"
puts "> Average Step Runtime: #{total_step_time / max_iterations}"


puts "Displaying probe results..."
project.probes.each do |probe|
    puts ">#{probe.label}"
    puts probe.to_spreadsheet
end
