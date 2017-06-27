require 'logger'

LOGGER = Logger.new(File.join(__dir__, '..', 'logs', 'heatflow.log'), 'daily')
LOGGER.level = Logger::DEBUG