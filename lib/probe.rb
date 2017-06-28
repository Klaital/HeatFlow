require_relative './configs.rb'

class Probe
    attr_accessor :label, :coordinate, :value_history

    def initialize(label: 'Temperature Probe', coordinate: [0,0])
        @label = label
        @coordinate = coordinate
        @value_history = []
    end

    def add_reading(elapsed_time, value)
        @value_history.unshift([ elapsed_time, value ])
    end

    def to_spreadsheet(set_header: true, delim: ',')
        s = ""
        s += "Elapsed Time (ms),Temperature (C)" if set_header
        @value_history.each do |history_record|
            s += "#{history_record[0]},#{history_record[1]}\n"
        end

        return s
    end
end

