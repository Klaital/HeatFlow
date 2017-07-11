#include <iostream>
#include <sstream>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace HeatFlow {
class Logger {
public:
    Logger(std::ostream& out = std::cout) : m_Out(out) {}
    ~Logger() {
        m_Stream << "\n";
        m_Out << m_Stream.rdbuf();
        m_Out.flush();
    }
    template <class T>
    Logger& operator<<(const T& thing) { m_Stream << thing; return *this; }

    void log(const std::string& msg, const std::string& file, int line) {
        time_t now;
        time(&now);
        char buf[sizeof "2011-10-08T07:07:09Z"];
        strftime(buf, sizeof buf, "%FT%TZ", gmtime(&now));
        //boost::posix_time::ptime t = boost::posix_time::microsec_clock::universal_time();
        m_Stream << "[" << buf << "] " << file << ", line #" << line << ": " << msg << "\n";
    }
private:
    std::stringstream m_Stream;
    std::ostream& m_Out;
    //static LogFilter...
};
}

