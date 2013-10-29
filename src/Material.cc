
#include <string>

#include "Material.h"

namespace HeatFlow {

Material::Material() 
{
    this->name = "";
}
Material::~Material()
{

}

// I/O helpers
std::string Material::to_string()
{
    // CSV Columns:
    // NAME

    return this->name;
}
int Material::load_string(const std::string& s)
{
    // See to_string for description of columns
    // for now, the only column is the name
    this->name = s;
}

} // namespace HeatFlow
