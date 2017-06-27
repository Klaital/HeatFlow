require 'logger'

LOGGER = Logger.new(File.join(__dir__, '..', 'logs', 'heatflow.log'), 'daily')
LOGGER.level = Logger::DEBUG

class Object
    def to_s_pretty
        if nil?
            'nil'
        else
            to_s
        end
    end
end

class Array
    def to_s_pretty
        "[" + collect {|x| x.to_s_pretty}.join(', ') + "]"
    end
end

class Hash
    def to_s_pretty
        "{" + keys.collect {|k| "#{k.to_s_pretty} => #{self[k].to_s_pretty}"}.join(',') + "}"
    end
end
