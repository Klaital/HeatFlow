require 'minitest/autorun'

require_relative "../lib/project.rb"
require_relative "../lib/material.rb"
require_relative "../lib/probe.rb"

class TestProject < Minitest::Test
    def setup
        @project1 = Project.new
        @project1.initial_temperatures_path = "./data/sample1_ascii.floatfield"
        @project1.materials_matrix_path = "./data/sample1_ascii.intfield"
        @project1.bom = [
            Material.new(:name => "Aluminum", :density => 2712, :conductivity => 205,  :index => 1),
            Material.new(:name => 'Glass',    :density => 2400, :conductivity => 1.05, :index => 2)
        ]
        @project1.time_step = 1
        @project1.field_map_distance = 0.000001
        @project1.probes = [
            Probe.new(label: 'Probe1', coordinate: [ 0, 0 ]),
            Probe.new(label: 'Probe2', coordinate: [ 3, 1 ])
        ]
    end

    def test_project_init
        assert_equal(1, @project1.time_step)

        project2 = Project.new(:time_step => 2)
        assert_equal(2, project2.time_step)
        assert_equal(0.001, project2.field_map_distance)
    end

    def test_project_serialization
        assert_equal(2, @project1.bom.length)
        assert_equal({
            "initial_temperatures_path" => "./data/sample1_ascii.floatfield",
            "materials_matrix_path"     => "./data/sample1_ascii.intfield",
            "time_step" => 1,
            "field_map_distance" => 0.000001,
            "bom" => [
                {
                    "name" => "Aluminum", "density" => 2712, "conductivity" => 205,  "index" => 1, "specific_heat": 1.0
                },
                {
                    "name" => 'Glass',    "density" => 2400, "conductivity" => 1.05, "index" => 2, "specific_heat": 1.0
                }
            ],
            "probes" => [
                {"label" => 'Probe1', "coordinate" => { "size1" => 0, "size2" => 0 }, "value_history" => [] },
                {"label" => 'Probe2', "coordinate" => { "size1" => 3, "size2" => 1 }, "value_history" => [] }
            ]
        }, @project1.to_h)

        project2 = Project.new
        project2.from_h({
            "initial_temperatures_path" => "./data/sample1_ascii.floatfield",
            "materials_matrix_path"     => "./data/sample1_ascii.intfield",
            "time_step" => 1,
            "field_map_distance" => 0.000001,
            "bom" => [
                {
                    "name" => "Aluminum", "density" => 2712, "conductivity" => 205,   "index" => 1
                },
                {
                    "name" => 'Glass',    "density" => 2400, "conductivity" => 1.05, "index" => 2
                }
            ],
            "probes" => [
                {"label" => 'Probe1', "coordinate" => { "size1" => 0, "size2" => 0 }, "value_history" => [] },
                {"label" => 'Probe2', "coordinate" => { "size1" => 3, "size2" => 1 }, "value_history" => [] }
            ]
        })

        assert_equal("./data/sample1_ascii.floatfield", project2.initial_temperatures_path)
        assert_equal(2, project2.bom.length)
        assert_kind_of(Material, project2.bom[0], "BoM objects were not deserialized")
        assert_kind_of(Array, project2.probes)
        assert_equal(2, project2.probes.length)
        assert_kind_of(Probe, project2.probes[0])

    end

    def test_project_file_io
        path = "./data/sample4_project.json"
        p = Project.from_file(File.join(__dir__, path))
        assert_equal("./sample3_initial_temps.floatfield", p.initial_temperatures_path)
        assert_equal("./sample3_materials.intfield", p.materials_matrix_path)
        assert_equal(3, p.bom.length)
        assert_kind_of(Material, p.bom[0], "BoM objects were not deserialized")
    end

    def test_project_data_load
        path = "./data/sample4_project.json"
        p = Project.from_file(File.join(__dir__, path))
        assert_equal("./sample3_initial_temps.floatfield", p.initial_temperatures_path)
        assert_equal("./sample3_materials.intfield", p.materials_matrix_path)
        assert_equal(3, p.bom.length)
        assert_kind_of(Material, p.bom[0], "BoM objects were not deserialized")

        # Load the data files
        p.load_data

        assert_kind_of(Array, p.materials_matrix)
        assert_kind_of(Array, p.initial_temperatures_matrix)

        # Check whether the correct number of rows was returned
        assert_equal(10, p.materials_matrix.length)
        assert_equal(10, p.initial_temperatures_matrix.length)

        # Check whether the correct number of columns was returned
        assert_equal(15, p.materials_matrix[0].length)
        assert_equal(15, p.initial_temperatures_matrix[0].length)

        # Validate some of the data points
        assert_kind_of(Integer, p.materials_matrix[0][0])
        assert_kind_of(Float, p.initial_temperatures_matrix[0][0])

        assert_equal(0, p.materials_matrix[0][0])
        assert_equal(1, p.materials_matrix[2][2])
        assert_equal(2, p.materials_matrix[4][5])

        assert_equal(123.4, p.initial_temperatures_matrix[0][0])
        assert_equal(0.0, p.initial_temperatures_matrix[0][1])
        assert_equal(0.0, p.initial_temperatures_matrix[1][0])
        assert_equal(345.6, p.initial_temperatures_matrix[7][3])
    end
end
