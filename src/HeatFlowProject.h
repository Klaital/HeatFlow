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
    std::string  output_path;
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
    int    time_step;  // number of milliseconds between calculation iterations
    
public:     // Accessors
    inline std::string get_output_path() { return this->output_path; }
    inline void set_output_path(std::string new_path) { this->output_path = new_path; }
    inline std::string get_title()      { return this->title; }
    inline void set_title(std::string new_title) { this->title = new_title; }
    inline std::string get_notes()      { return this->notes; }
    inline void set_notes(std::string new_notes) { this->notes = new_notes; }
    
    inline double get_x_distance() { return this->x_distance; }
    inline double get_y_distance() { return this->y_distance; }
    inline void set_x_distance(double distance) { this->x_distance = distance; }
    inline void set_y_distance(double distance) { this->y_distance = distance; }
    
    inline int get_time_step() { return this->time_step; }
    inline void set_time_step(int time_step) { this->time_step = time_step; }

public:     // Constructors & Destructors
    
    // Construct an empty project
    HeatFlowProject();    
    
    // Destroy the project
    ~HeatFlowProject();
};

} // namespace HeatFlow

#endif // HEATFLOW_HEATFLOWPROJECT_H_

