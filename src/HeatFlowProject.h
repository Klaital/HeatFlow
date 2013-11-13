#ifndef HEATFLOW_HEATFLOWPROJECT_H_
#define HEATFLOW_HEATFLOWPROJECT_H_
#include <string>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

#include "configs.h"
#include "MaterialsCollection.h"

namespace HeatFlow {

class HeatFlowProject
{
private:    // Member variables
    // The directory where this project's data lives, both input and output.
    std::string  project_directory;
    // The basename of the config file; it will be located as a file in the output directory root: $project_directory/$project_config_filename
    std::string  project_config_filename; 
    std::string  title;
    std::string  notes;
    std::string  initial_temps_matrix_path;
    std::string  bom_path;
    std::string  materials_matrix_path;

    boost::numeric::ublas::matrix<temperature_t, temperature_t> *initial_temps;
    boost::numeric::ublas::matrix<int, int> *materials;
    MaterialsCollection *bom;

    // TODO: decide what units these will be defined in. Maybe we can use a string for that, plus a unit-conversion library? 
    // For now, we'll assume 'meter', I guess.
    double  x_distance; // the distance between nodes in the X direction
    double  y_distance; // the distance between nodes in the Y direction
    time_delta_t    time_step;  // number of milliseconds between calculation iterations
    
public:     // Accessors
    inline std::string get_project_directory() { return this->project_directory; }
    inline void set_project_directory(std::string new_dir) { this->project_directory = new_dir; }
    inline std::string get_project_config_filename() { return this->project_config_filename; }
    inline void set_project_config_filename(std::string& new_filename) { this->project_config_filename = new_filename; }
    inline std::string get_title()      { return this->title; }
    inline void set_title(std::string new_title) { this->title = new_title; }
    inline std::string get_notes()      { return this->notes; }
    inline void set_notes(std::string new_notes) { this->notes = new_notes; }
    
    inline double get_x_distance() { return this->x_distance; }
    inline double get_y_distance() { return this->y_distance; }
    inline void set_x_distance(double distance) { this->x_distance = distance; }
    inline void set_y_distance(double distance) { this->y_distance = distance; }
    
    inline time_delta_t get_time_step() { return this->time_step; }
    inline void set_time_step(time_delta_t time_step) { this->time_step = time_step; }

public:     // Constructors & Destructors
    
    // Construct an empty project
    HeatFlowProject();    
    
    // Destroy the project
    ~HeatFlowProject();

    //
    // Utility methods
    //

    // Serialize the Project data into an XML document
    std::string to_xml();
    // Deserialize from an XML document
    int load_xml(const std::string& xml);

    // Save to file. The path is defined by the project_directory and project_config_filename variables.
    int save();
    int load(const std::string& path);
};

} // namespace HeatFlow

#endif // HEATFLOW_HEATFLOWPROJECT_H_

