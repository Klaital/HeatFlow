require 'minitest/autorun'

require_relative "../lib/material.rb"

class TestMaterial < Minitest::Test
    def setup
        @material1 = Material.new
        @material1.name = "Mat1"
        @material1.density = 1.003
        @material1.conductivity = 203.557
        @material1.index = 0
    end

    def test_material_init
        assert_equal("Mat1", @material1.name)
        assert_equal(1.003, @material1.density)
        assert_equal(203.557, @material1.conductivity)

        mat2 = Material.new(:index => 14, :name => "Aluminum", :density => 2712, :conductivity => 205)
        assert_equal("Aluminum", mat2.name)
        assert_equal(2712, mat2.density)
        assert_equal(205, mat2.conductivity)
        assert_equal(14, mat2.index)
    end

    def test_hash_io
        assert_equal("Mat1", @material1.to_h["name"])
        assert_equal(1.003, @material1.to_h["density"])
        assert_equal(203.557, @material1.to_h["conductivity"])

        mat2 = Material.new(:name => "Aluminum", :density => 2712, :conductivity => 205)
        mat2.from_h({
            "name" => 'Glass',
            "conductivity" => 1.05,
            "density" => 2400,
            "index" => 2
        })

        assert_equal("Glass", mat2.name)
        assert_equal(2400, mat2.density)
        assert_equal(1.05, mat2.conductivity)
        assert_equal(2, mat2.index)
    end
    
end

