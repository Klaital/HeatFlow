require_relative './configs.rb'

class Simulator
    attr_accessor :temperatures_next, :temperatures_prev
    attr_reader   :materials # This should be an array of actual Material objects, dereferenced from the Project's BoM indices
    attr_accessor :elapsed_time
    attr_accessor :project_config, 
                    :probes # A local copy of the probes, stored as a hash for quick access by coordinates, and will have the history array populated

    attr_reader :surface_area

    def initialize(project_config: Project.new)
        @project_config = project_config
        @elapsed_time = 0.0
        
        @surface_area = nil
        @probes = {}
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

        # Compile the Probe objects into a Hash, keyed for access by the coordinate pair
        @probes = {}
        @project_config.probes.each do |probe|
            @probes[probe.coordinate] = probe
        end
    end

    def simulate_step
        return nil if @surface_area.nil? # This means that #simulation_init has not been run yet
        return nil if @temperatures_next.nil? # This means that the project config did not have temperatures for us
        return nil if @materials.nil? # This means taht the project config did not have a valid materials config and/or BoM

        # Rotate the matricies. Use the results of the previous iteration (or initial setup) as the basis for computing the next step.
        @temperatures_prev = @temperatures_next.clone
        LOGGER.debug("Step: old temps: #{@temperatures_next}")
        LOGGER.debug("Step: old temps copy: #{@temperatures_prev}")

        # Increment the elapsed time first, as the calculations represent the new state at this new time.
        @elapsed_time += @project_config.time_step
        
        0.upto(@temperatures_next.length-1) do |i|
            0.upto(@temperatures_next[0].length-1) do |j|
                old_temperature = @temperatures_prev[i][j]

                nearby_coordinates = [
                    [ i - 1, j - 1 ], [ i - 1, j ], [ i - 1, j + 1],
                    [ i, j - 1 ], [ i, j ], [ i, j + 1],
                    [ i + 1, j - 1 ], [ i + 1, j ], [ i + 1, j + 1],
                ]

                heat_flow = 0.0 # joules in

                # Compute the heat flowing into this node from all adjacent nodes in Joules.
                nearby_coordinates.each do |coordinate|
                    # Check boundary conditions. The areas outside the matrix just don't exist.
                    next if (coordinate[0] < 0 || coordinate[1] < 0 || coordinate[0] >= @materials.length || coordinate[1] >= @materials[0].length)

                    heat = Simulator.compute_heat_flow(@surface_area, @project_config.field_map_distance,
                                                    @materials[i][j], @temperatures_prev[i][j], # The current temperature and material config for this node
                                                    @temperatures_prev[coordinate[0]][coordinate[1]], # The current temperature at the nearby node
                                                    @project_config.time_step)
                    # LOGGER.debug("Step @ [#{i}][#{j}]: computed heat @ #{coordinate.to_s_pretty}")
                    heat_flow += heat
                end
                # LOGGER.debug("Step @ [#{i}][#{j}]: total computed heat #{heat_flow} J")
                
                unit_mass = @materials[i][j].density * @surface_area * @project_config.field_map_distance
                new_temperature = old_temperature + (heat_flow / (unit_mass * @materials[i][j].specific_heat) )
                @temperatures_next[i][j] =  new_temperature.dup

                # Check for any probes at this location
                if (@probes.has_key?([i,j]))
                    @probes[[i,j]].add_reading(@elapsed_time, new_temperature.dup)
                end
            end
        end
        
        
    end

    # The heat flowing into a node via conductive heat transfer in Joules.
    def self.compute_heat_flow(surface_area, distance, material, temp_home, temp_nearby, time_step)
        LOGGER.debug(">>>Computing Heat flow. Surface Area=#{surface_area}, distance=#{distance}, material=#{material.name}, Temperature1=#{temp_home}, Temperature2=#{temp_nearby}, Time Delta=#{time_step} ms")

        watts = material.conductivity * surface_area * (temp_nearby - temp_home) / distance
        joules = watts * time_step
    end

end
