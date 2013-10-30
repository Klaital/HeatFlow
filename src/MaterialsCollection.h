#ifndef HEATFLOW_MATERIALSCOLLECTION_H_
#define HEATFLOW_MATERIALSCOLLECTION_H_

#include <stdio.h>
#include <string>
#include <vector>

#include "tinyxml2.h"
#include "Material.h"

namespace HeatFlow {

class MaterialsCollection
{
public:
	//
	// Constructors & Destructors
	//

	// Create an empty material collection.
    MaterialsCollection();
    // Default destructor.
    ~MaterialsCollection();

    //
    // File I/O
    //
    int save(const std::string& path);
    int load(const std::string& path);

    //
    // Interacting with the actual materials list
    //

    // Return the index of the first Material with the given name.
    // A negative value indicates that the name was not found.
    int find_first(const std::string& name);
    // Return a list of indices for all Materials matching the given name.
    // An empty list indicates that the name was not found.
    vector<int> find_all(const std::string& name);
    // Fetch by value the material at a given index in the BOM.
    Material get(int index);
    // Alter the material at a given index to match the Material data given in 'm'.
    int save(int index, const Material& m);
    // Append a new Material to the BOM.
    int add(const Mateial& m);
    // Remove the Material at the given index from the BOM.
    int delete(int index);

private:
	// The Bill Of Materials for a project.
    std::vector<Material> *mats;
};

} // namespace HeatFlow

#endif // HEATFLOW_MATERIALSCOLLECTION_H_
