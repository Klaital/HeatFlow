require_relative './configs.rb'

class Simulator
    attr_accessor :temperatures_next, :temperatures_prev
    attr_reader   :materials # This should be an array of actual Material objects, dereferenced from the Project's BoM indices
    attr_accessor :elapsed_time
    attr_accessor :project_config
    
    attr_reader :surface_area

    def initialize(project_config: Project.new)
        @project_config = project_config
        @elapsed_time = 0.0

        @surface_area = nil
    end

    def simulation_init
        LOGGER.info("Initializing simulator")
        @project_config.load_data
        @temperatures_next = @project_config.initial_temperatures_matrix.dup
        
        # Reset the elapsed time to zero, regardless of how many steps have run
        @elapsed_time = 0.0

        # Precompute the surface area between any two adjacent nodes in the matrix,
        # assuming each is a cube described by the field map distance in the project config.
        @surface_area = @project_config.field_map_distance * @project_config.field_map_distance
        LOGGER.debug("Computed surface area: #{@surface_area}")

        # Build the Materials matrix as well
        @materials = @project_config.materials_matrix.clone
        @materials.each_index do |i|
            @materials[i].each_index do |j|
                material_index = @materials[i][j]
                # LOGGER.debug("Got material[#{i}][#{j}]=#{material_index}")
                material       = @project_config.get_material(material_index)
                # LOGGER.debug("Yielded material data: #{material.to_s_pretty}")
                @materials[i][j] = material.clone
                # LOGGER.debug("@materials[#{i}][#{j}]= #{@materials[i][j].to_s_pretty}")
            end
        end

        # LOGGER.debug("temperatures_prev: #{@temperatures_prev.to_s_pretty}")
        # LOGGER.debug("temperatures_next: #{@temperatures_next.to_s_pretty}")
        # LOGGER.debug("materials: #{@materials.to_s_pretty}")
    end

    def simulate_step
        return nil if @surface_area.nil? # This means that #simulation_init has not been run yet
        return nil if @temperatures_next.nil? # This means that the project config did not have temperatures for us
        return nil if @materials.nil? # This means taht the project config did not have a valid materials config and/or BoM

        # Rotate the matricies. Use the results of the previous iteration (or initial setup) as the basis for computing the next step.
        @temperatures_prev = @temperatures_next.clone
        LOGGER.debug("Step: old temps: #{@temperatures_next}")
        LOGGER.debug("Step: old temps copy: #{@temperatures_prev}")
        
        0.upto(@temperatures_next.length-1) do |i|
            0.upto(@temperatures_next[0].length-1) do |j|
                old_temperature = @temperatures_prev[i][j]
                new_temperature = old_temperature + 0.1 # TODO: actually compute the heat transfer
                @temperatures_next[i][j] =  new_temperature.dup
            end
        end
        
        @elapsed_time += @project_config.time_step
    end

end
