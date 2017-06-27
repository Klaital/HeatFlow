class Material
    attr_accessor :name, :density, :conductivity, :index

    def initialize(name: "New Material", density: 1, conductivity: 1, index: -1)
        @name = name
        @density = density
        @conductivity = conductivity
        @index = index
    end
    
    def to_h
        {
            "name" => @name,
            "density" => @density,
            "conductivity" => @conductivity,
            "index" => @index,
        }
    end

    def from_h(config_hash)
        @name = config_hash["name"]
        @density = config_hash["density"]
        @conductivity = config_hash["conductivity"]
        @index = config_hash["index"].to_i
    end
    
end
