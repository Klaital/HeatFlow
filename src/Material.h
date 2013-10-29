#ifndef HEATFLOW_MATERIAL_H_
#define HEATFLOW_MATERIAL_H_

#include <string>

namespace HeatFlow {
class Material 
{
public:
    Material();
    ~Material();

    // I/O helpers
    std::string to_string();
//  std::string to_xml();
    int load_string(const std::string& s);
//  int load_xml(const std::string& s);
};
} // namespace HeatFlow

#endif // HEATFLOW_MATERIAL_H_
