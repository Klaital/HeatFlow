#ifndef HEATFLOW_MATERIAL_H_
#define HEATFLOW_MATERIAL_H_

#include <string>
#include <sstream>
#include "configs.h"

namespace HeatFlow {
class Material 
{
public:
    Material();
    ~Material();

    // Accessors 
    inline void set_name(const std::string& new_name) { this->name = new_name; }
    inline std::string get_name() { return this->name; }
    
    // I/O helpers
    int to_xml(int index, std::string& xml_buffer);
    int load_xml(const std::string& s);

private:
    std::string name;
	thermal_conductivity_t conductivity; // W / (m^2 K / m)
	density_t density; // grams / cm^3
};
} // namespace HeatFlow

#endif // HEATFLOW_MATERIAL_H_
