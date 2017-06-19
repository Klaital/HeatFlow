#ifndef HEATFLOW_HEATFLOWPROJECT_H_
#define HEATFLOW_HEATFLOWPROJECT_H_
#include <string>

#include <boost/numeric/ublas/vector.hpp>
#include <boost/numeric/ublas/matrix.hpp>

#include "configs.h"
#include "tinyxml2.h"
#include "MatrixFile.h"
#include "Material.h"

namespace HeatFlow {

class HeatFlowProject
{
private:    // Member variables
    // The basename of the config file; it will be located as a file in the output directory root: $project_directory/$project_config_filename
    std::string  project_config_filename_; 
    std::string  title_;
    std::string  notes_;
    std::string  initial_temps_matrix_path_;
    std::string  materials_matrix_path_;
	MatrixFile<temperature_t> initial_temperatures_;
	MatrixFile<int> materials_;

	std::vector<Material> bom_;

    distance_t      field_gap_distance_; // the distance between nodes in the X direction in meters
    time_delta_t    time_step_;  // number of milliseconds between calculation iterations
    
public:     // Accessors
    inline std::string get_project_config_filename() { return this->project_config_filename_; }
    inline void set_project_config_filename(std::string& new_filename) { this->project_config_filename_ = new_filename; }
    inline std::string get_title()      { return this->title_; }
    inline void set_title(const std::string& new_title) { this->title_ = new_title; }
    inline std::string get_notes()      { return this->notes_; }
    inline void set_notes(const std::string& new_notes) { this->notes_ = new_notes; }
    
    inline double get_field_gap_distance() { return this->field_gap_distance_; }
    inline void set_x_distance(distance_t new_gap_distance) { this->field_gap_distance_= new_gap_distance; }
    
    inline time_delta_t get_time_step() { return this->time_step_; }
    inline void set_time_step(time_delta_t time_step) { this->time_step_ = time_step; }

	inline std::string get_initial_temps_path() { return this->initial_temps_matrix_path_; }
	inline void        set_initial_temps_path(const std::string& initial_temps_path) { this->initial_temps_matrix_path_ = initial_temps_path; }
	inline std::string get_materials_path() { return this->materials_matrix_path_; }
	inline void        set_materials_path(const std::string& materials_path) { this->materials_matrix_path_ = materials_path; }

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
    int load_from_file(const std::string& path);
};

} // namespace HeatFlow

#endif // HEATFLOW_HEATFLOWPROJECT_H_

