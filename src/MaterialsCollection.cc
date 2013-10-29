
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
    // TODO: implement collection file output method
    return 0; // error
}
int MaterialsCollection::load(const std::string& path) 
{
    // TODO: implement collection file read method
    return 0; // error
}

} // namespace HeatFlow

