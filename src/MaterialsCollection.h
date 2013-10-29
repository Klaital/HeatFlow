#ifndef HEATFLOW_MATERIALSCOLLECTION_H_
#define HEATFLOW_MATERIALSCOLLECTION_H_

#include <string>

namespace HeatFlow {

class MaterialsCollection
{
public:
    MaterialsCollection();
    ~MaterialsCollection();

    // File I/O
    int save(const std::string& path);
    int load(const std::string& path);

private:
    vector<Material> *mats;
};

}

#endif //HEATFLOW_MATERIALSCOLLECTION_H_
