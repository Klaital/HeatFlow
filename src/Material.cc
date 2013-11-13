
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
int Material::to_xml(int index, std::string& xml_buffer)
{
    // <material index="%i"><name>%s</name></material> -> 46 characters for the markup
    std::string indexStr = std::to_string(index);

    size_t buffer_length = indexStr.length() + 47 + this->name.length()
    char *buff = malloc(buffer_length);
    res = snprintf(buff, buffer_length, "<material index=\"%i\"><name>%s</name></material>", index, this->name.c_str());
    if (res <= 0) {
        return res;
    }

    xml_buffer.assign(buff);
    free(buff);
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
