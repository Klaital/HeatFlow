#include "logger.h"
#include <iostream>
#include <boost/logging/format/named_write_fwd.hpp>

int main()
{
    HeatFlow::Logger logger;
    logger.log("Hello, world!", __FILE__, __LINE__);
}
