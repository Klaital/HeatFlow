require_relative './configs.rb'

class Probe
    attr_accessor :label, :coordinate, :value_history

    def initialize(label: 'Temperature Probe', coordinate: [0,0])
        @label = label
        @coordinate = coordinate
        @value_history = []
    end

    def add_reading(elapsed_time, value)
        @value_history.push([ elapsed_time, value ])
    end

    def to_spreadsheet(set_header: true, delim: ',')
        s = ""
        s += "Elapsed Time (ms),Temperature (C)" if set_header
        @value_history.each do |history_record|
            s += "#{history_record[0]},#{history_record[1]}\n"
        end

        return s
    end

    # Serialization to a Hash
    def to_h
        {
            "label" => @label.to_s,
            "coordinate" => { "size1" => @coordinate[0], "size2" => @coordinate[1] },
            "value_history" => @value_history,
        }
    end

    # Deserialize from Hash
    def from_h(probe_config)
        @label = probe_config['label']
        @coordinate = [ probe_config['coordinate']['size1'], probe_config['coordinate']['size1'] ]
        @value_history = probe_config['value_history']
    end
end

