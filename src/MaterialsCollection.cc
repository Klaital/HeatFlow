
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

    fputs("[General]", f);
    fprint("Name: ", f);
    fputs(this->name, f);
    fputs("[Materials]", f);
    int i = 0;
    for (std::vector<Material>::iterator it = this->mats->begin(); it != this->mats->end(); ++it) 
    {
        fprintf(f, "%i,%s\n", i, *it.to_string());
        ++i;
    }
    fclose(f);
    return 0; // error
}
int MaterialsCollection::load(const std::string& path) 
{
    // TODO: implement collection file read method
    return 0; // error
}

} // namespace HeatFlow

