require 'optparse'

require_relative '../lib/project.rb'

project_file_path = 'new_project.json'
project = Project.new

OptionParser.new do |o|
    o.banner = "Create a new HeatFlow Simulation Project.\nUsage: create_project.rb [options]"

    o.on_tail('-h', '--help', 'Display this help information') do
        puts o
        exit
    end

    o.on('-o', '--output PATH', 'Path to save the project file to.') do |p|
        project_file_path = p
    end

    o.on('--materials-file PATH', 'Path to the materials matrix file.') do |p|
        project.materials_matrix_path = p
    end

    o.on('--temps-file PATH', 'Path to the matrix file describing the initial temperatures.') do |p|
        project.initial_temperatures_path = p
    end

    o.on('--time-step NUM', 'Number of milliseconds between simulation steps.') do |time_step|
        project.time_step = time_step.to_f
    end

    o.on('--distance NUM', 'Distance in meters between nodes in the data matrices.') do |distance|
        project.field_map_distance = distance.to_f
    end

end.parse!

puts project.save(project_file_path)

