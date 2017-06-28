require 'minitest/autorun'

require_relative "../lib/simulator.rb"

class SimulatorProject < Minitest::Test
    def setup
        @project = Project.from_file(File.join(__dir__, "data/sample4_project.json"))
        @simulator = Simulator.new(project_config: @project)
    end

    def test_simulation_init
        @simulator.simulation_init

        # Validate that the surface area was computed
        assert_equal(0.000000000001, @simulator.surface_area)

        # Validate that the initial temperatures matrix has been copied in
        0.upto(9) do |i|
            0.upto(14) do |j|
                assert_kind_of(Float, @simulator.temperatures_next[i][j], "temperatures_next[#{i}][#{j}] did not load")
            end
        end
        
        # Validate that the materials matrix has been generated
        assert_kind_of(Material, @simulator.materials[0][0])
        0.upto(9) do |i|
            0.upto(14) do |j|
                assert_kind_of(Material, @simulator.materials[i][j], "Material[#{i}][#{j}] did not load")
            end
        end
        

        # Validate that the elapsed time has been set (or reset) to zero
        refute_nil(@simulator.elapsed_time, "Elapsed time has not been initialized")
        assert_equal(0, @simulator.elapsed_time)
    end

    def test_simulation_step
        @simulator.simulation_init
        @simulator.simulate_step

        assert_equal(1, @simulator.elapsed_time)

        assert_equal(10, @simulator.temperatures_next.length)
        0.upto(9) do |i| 
            assert_kind_of(Array, @simulator.temperatures_next[i], "temperatures_next[#{i}] not an Array")
            assert_equal(15, @simulator.temperatures_next[i].length, "temperatures_next[#{i}] incorrect length")
            0.upto(14) do |j|
                assert_kind_of(Float, @simulator.temperatures_next[i][j], "temperatures_next[#{i}][#{j}] did not load")
            end
        end
        
        assert_equal(123.5, @simulator.temperatures_next[0][0])
        assert_equal(0.1,   @simulator.temperatures_next[1][1])

        # Execute a second step
        @simulator.simulate_step
        assert_equal(2, @simulator.elapsed_time)
        assert_equal(123.6, @simulator.temperatures_next[0][0])
        assert_equal(0.2,   @simulator.temperatures_next[1][1])
    end
end
