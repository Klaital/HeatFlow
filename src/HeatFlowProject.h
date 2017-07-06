#ifndef HEATFLOW_HEATFLOWPROJECT_H_
#define HEATFLOW_HEATFLOWPROJECT_H_
#include <string>
#include <vector>

#include <boost/filesystem.hpp>
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
    MatrixFile<unsigned int> materials_;

    std::vector<Material> bom_;

    distance_t      field_gap_distance_; // the distance between nodes in the X direction in meters
    time_delta_t    time_step_;  // number of milliseconds between calculation iterations

public:     // Accessors
    inline std::string get_project_config_filename() const { return this->project_config_filename_; }
    inline void set_project_config_filename(std::string& new_filename) { this->project_config_filename_ = new_filename; }
    inline std::string get_title() const { return this->title_; }
    inline void set_title(const std::string& new_title) { this->title_ = new_title; }
    inline std::string get_notes() const { return this->notes_; }
    inline void set_notes(const std::string& new_notes) { this->notes_ = new_notes; }
    
    inline double get_field_gap_distance() const { return this->field_gap_distance_; }
    inline void set_field_gap_distance(distance_t new_gap_distance) { this->field_gap_distance_= new_gap_distance; }
    
    inline time_delta_t get_time_step() const { return this->time_step_; }
    inline void set_time_step(time_delta_t time_step) { this->time_step_ = time_step; }

    inline std::string get_initial_temps_path() const { return this->initial_temps_matrix_path_; }
    inline void        set_initial_temps_path(const std::string& initial_temps_path) { this->initial_temps_matrix_path_ = initial_temps_path; }
    inline std::string get_materials_path() const { return this->materials_matrix_path_; }
    inline void        set_materials_path(const std::string& materials_path) { this->materials_matrix_path_ = materials_path; }

    inline MatrixFile<temperature_t> get_initial_temps() const { return this->initial_temperatures_; }
    inline MatrixFile<unsigned int>           get_materials() const { return this->materials_; }

    inline std::vector<Material> get_bom() const { return this->bom_; }
    inline void set_bom(const std::vector<Material>& new_bom) { this->bom_ = new_bom; }
    inline void set_material(unsigned int index, const Material& material) { this->bom_[index] = material; }
    inline Material get_material(unsigned int index) const { return this->bom_[index]; }

public:     // Data Manipulation
    // Copy the new material into the BoM, and return the index to the newly created entry
    unsigned int add_material(const Material& new_material);
    // Delete materials matching the given values. The return value indicates success/failure.
    int delete_material(const std::string& name);
    int delete_material(unsigned int index);

    // Populate the given materials_matrix with pointers to the BoM, rather
    // than mere indexes, to make iterating faster during simulation.
    void copy_materials_matrix(MatrixFile<const Material *> &materials_matrix) const;

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

