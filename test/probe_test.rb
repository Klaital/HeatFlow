require 'minitest/autorun'

require_relative "../lib/probe.rb"

class SimulatorProject < Minitest::Test
    def setup
        
    end

    def test_probe_add_record
        probe = Probe.new(label: "Test Probe", coordinate: [0,1])

        assert_equal(2, probe.coordinate.length)
        assert_equal(0, probe.coordinate[0])
        assert_equal(1, probe.coordinate[1])

        assert_equal(0, probe.value_history.length)
        probe.add_reading(1, 15)
        assert_equal(1, probe.value_history.length)
        assert_equal(15, probe.value_history[-1][1])
        probe.add_reading(2, 17)
        assert_equal(2, probe.value_history.length)
        assert_equal(17, probe.value_history[-1][1])
    end
end
