#ifndef HEATFLOW_MATERIAL_H_
#define HEATFLOW_MATERIAL_H_

#include <string>

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
};
} // namespace HeatFlow

#endif // HEATFLOW_MATERIAL_H_
