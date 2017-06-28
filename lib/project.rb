require 'json'
require_relative './configs.rb'
require_relative './probe.rb'
require_relative './material.rb'

class Project
    attr_accessor :initial_temperatures_path, :initial_temperatures_matrix, # Temperatures across the model at the start of the simulation
                    :materials_matrix_path, :materials_matrix, # Physical materials configuration for the model
                    :bom, # Bill of Materials: the list of all materials in use in this model
                    :time_step, # number of milliseconds to elapse between simulator calculation rounds
                    :field_map_distance, # distance in meters between any two nodes in the matrix
                    :probes # Points in the model at which we want to track the temperature over time

    attr_accessor :project_config_path

    def initialize(bom: [], time_step: 1, field_map_distance: 0.001)
        @initial_temperatures_path = initial_temperatures_path
        @materials_matrix_path = materials_matrix_path
        @bom = bom
        @time_step = time_step
        @field_map_distance = field_map_distance
        @probes = []
    end

    # Serialize to Hash
    def to_h
        {
            "initial_temperatures_path" => @initial_temperatures_path,
            "materials_matrix_path"     => @materials_matrix_path,
            "bom" => @bom.collect {|mat| mat.to_h},
            "time_step" => @time_step,
            "field_map_distance" => @field_map_distance,
            "probes" => @probes.collect {|p| p.to_h},
        }
    end

    # Deserialize from Hash
    def from_h(project_hash)
        @initial_temperatures_path = project_hash["initial_temperatures_path"]
        @materials_matrix_path     = project_hash["materials_matrix_path"]
        @time_step                 = project_hash["time_step"]
        @field_map_distance        = project_hash["field_map_distance"] 
        @bom = if (project_hash.has_key?("bom") && project_hash['bom'].kind_of?(Array)) 
            project_hash["bom"].collect {|mat| m = Material.new; m.from_h(mat); m; }
        else
            []
        end
        @probes = if (project_hash.has_key?('probes') && project_hash['probes'].kind_of?(Array)) 
            project_hash["probes"].collect {|probe_config| p = Probe.new; p.from_h(probe_config); p;}
        else
            []
        end
    end

    # Deserialize from file
    def self.from_file(path)
        return nil unless File.exists?(path)
        p = Project.new
        p.project_config_path = path
        h = JSON.parse(File.read(path))
        p.from_h(h)
        return p
    end

    # Serialize to file
    def save(path='current_project.json')
        f = File.open(path, 'w')
        s = JSON.pretty_generate(to_h)
        f.puts s
        s
    end

    # Load data files for the materials config and initial temperature profile
    def load_data
        initial_temps_path = File.join(File.dirname(@project_config_path), @initial_temperatures_path)
        materials_path     = File.join(File.dirname(@project_config_path), @materials_matrix_path)

        @initial_temperatures_matrix = Project.read_data_file(initial_temps_path).dup
        @materials_matrix = Project.read_data_file(materials_path).dup
    end

    # Fetch a new Material object for the given index value
    def get_material(index)
        @bom.each do |material|
            return material.dup if index == material.index
        end
        return nil
    end

    # Static method for loading data from a matrix file
    def self.read_data_file(path)
        LOGGER.info("Loading data from file: #{path}")
        f = File.open(path, 'r')
        
        # The header line tells us the number of rows and columns to expect
        header = f.gets.strip
        LOGGER.debug("Got header: '#{header}'")
        rows, columns, data_type = header.split(/ /)
        return false if columns.nil?
        # Use a default data type of float. Anything else will result in parsing the file as floating point data.
        parse_as_integer = (data_type.nil? || data_type.to_s.downcase == "integer")
        LOGGER.debug("Parse as integer: #{parse_as_integer}")

        # Validate the data looks sane
        rows = rows.to_i
        columns = columns.to_i
        return false unless (rows > 0 && columns > 0)

        # Read all of the data
        rows_parsed = 0
        data_array = Array.new(rows)
        while(s=f.gets)
            # Ensure that the row has the expected number of columns
            elements = s.split(/ /).collect {|e| e.strip}
            return false unless (elements.length == columns)

            # Parse the elements into a Numeric object of the correct type
            elements.collect! do |e|
                (parse_as_integer) ? e.to_i : e.to_f
            end
            
            # Save the row into the data array
            data_array[rows_parsed] = elements.dup

            # Stop parsing if we have reached the expected number of rows
            rows_parsed += 1
            break if (rows_parsed >= rows)
        end

        # Return an error unless the correct number of rows was parsed
        return false unless rows_parsed == rows

        # Otherwise return the generated matrix
        return data_array
    end
    
    
end
