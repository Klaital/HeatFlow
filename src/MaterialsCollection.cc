
#include "MaterialsCollection.h"

namespace HeatFlow {

MaterialsCollection::MaterialsCollection()
{
    this->mats = new std::vector<Material>();
}
MaterialsCollection::~MaterialsCollection()
{
}

// File I/O
int MaterialsCollection::save(const std::string& path)
{
    FILE * f = fopen(path.c_str(), "w");
    if (f == NULL) {
        return 0;
    }

    fprintf(f, "<MaterialsCollection><name>%s</name><Materials>", this->name->c_str());
    int i = 0;
    std::string xml_buffer;
    for (std::vector<Material>::iterator it = this->mats->begin(); it != this->mats->end(); ++it) 
    {
        // TODO: check for success, log/handle error 
		it->to_xml(i, xml_buffer);
        fprintf(f, "%s", xml_buffer.c_str());
        ++i;
    }
    fprintf(f, "%s\n", "</Materials></MaterialsCollection>");
    fclose(f);
    return 0; // error
}
int MaterialsCollection::load(const std::string& path) 
{
    // TODO: implement collection file read method
    tinyxml2::XMLDocument doc;
    doc.LoadFile(path.c_str());
    const char* new_name = doc.FirstChildElement("MaterialsCollection")->FirstChildElement("name")->GetText();
    if (new_name == NULL) {
        return 0;
    }
    this->name->assign(new_name);
	tinyxml2::XMLNode *collection = doc.FirstChildElement("MaterialsCollection");
    delete this->mats;
    this->mats = new std::vector<Material>();
    if (!collection->NoChildren()) {

    }

    return 0; // error
}

} // namespace HeatFlow

