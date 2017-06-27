
#include <string>

#include "Material.h"

namespace HeatFlow {

Material::Material() 
{
    this->name_ = "";
	this->conductivity_ = 0.591; // water
	this->density_ = 1.0; // water at 4-5 degrees C
}
Material::~Material()
{

}

// I/O helpers
int Material::to_xml(int index, std::string& xml_buffer)
{
    // <material index="%i"><name>%s</name></material> -> 46 characters for the markup
    std::string indexStr = std::to_string(index);
	std::stringstream ss;

	ss << "<Material id=\"" << index << "\"><name>"
		<< this->name_ << "</name><density>"
		<< this->density_ << "</density><conductivity>"
		<< this->conductivity_ << "</conductivity></Material>";

    
	xml_buffer.assign(ss.str());
    return 1;
}

} // namespace HeatFlow
