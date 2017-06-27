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
    inline void set_name(const std::string& new_name) { this->name_ = new_name; }
    inline std::string get_name() { return this->name_; }
	inline void set_density(density_t density) { this->density_ = density; }
	inline density_t get_density() { return this->density_; }
	inline void set_conductivity(thermal_conductivity_t conductivity) { this->conductivity_ = conductivity; }
	inline thermal_conductivity_t get_conductivity() { return this->conductivity_; }

    // I/O helpers
    int to_xml(int index, std::string& xml_buffer);

private:
    std::string name_;
	thermal_conductivity_t conductivity_; // W / (m K)
	density_t density_; // kilograms / cubic meter
};
} // namespace HeatFlow

#endif // HEATFLOW_MATERIAL_H_
