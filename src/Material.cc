
#include <string>

#include "Material.h"

namespace HeatFlow {

Material::Material() 
{
    this->name = "";
	this->conductivity = 0.591; // water
	this->density = 1.0; // water at 4-5 degrees C
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

	ss << "<material index=\"" << index << "\"><name>" << this->name << "</name></material>";

    
	xml_buffer.assign(ss.str());
    return 1;
}
int Material::load_xml(const std::string& xml)
{
    // TODO: use TinyXML2 to parse the XML
    // See to_string for description of columns
    // for now, the only column is the name

    this->name = "Name from XML";
    return 0;
}

} // namespace HeatFlow
