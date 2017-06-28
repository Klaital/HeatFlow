class Material
    attr_accessor :name, :density, :conductivity, :index, :specific_heat

    def initialize(specific_heat: 1.0, name: "New Material", density: 1, conductivity: 1, index: -1)
        @name = name
        @density = density
        @conductivity = conductivity
        @index = index
        @specific_heat = specific_heat
    end
    
    def to_h
        {
            "name" => @name,
            "density" => @density,
            "conductivity" => @conductivity,
            "index" => @index,
            "specific_heat" => @specific_heat
        }
    end

    def from_h(config_hash)
        @name = config_hash["name"]
        @density = config_hash["density"]
        @conductivity = config_hash["conductivity"]
        @index = config_hash["index"].to_i
        @specific_heat = config_hash['specific_heat'].to_f
    end
    
    def to_s_pretty
        return to_h.to_s_pretty
    end
end
