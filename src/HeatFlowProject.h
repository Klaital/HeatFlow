#ifndef HEATFLOW_HEATFLOWPROJECT_H_
#define HEATFLOW_HEATFLOWPROJECT_H_

#include "Field2D.hpp"

namespace HeatFlow {

class HeatFlowProject
{
private:    // Member variables
    string  output_path;
    string  title;
    string  notes;
    // TODO: decide what units these will be defined in. Maybe we can use a string for that, plus a unit-conversion library? 
    // For now, we'll assume 'meter', I guess.
    double  x_distance; // the distance between nodes in the X direction
    double  y_distance; // the distance between nodes in the Y direction
    int    time_step;  // number of milliseconds between calculation iterations
    
public:     // Accessors
    inline string get_output_path() { return this->output_path; }
    inline void set_output_path(string new_path) { delete this->output_path; this->output_path = new string(new_path); }
    inline string get_title()      { return this->title; }
    inline void set_title(string new_title) { delete this->title; this->title = new string(new_title); }
    inline string get_notes()      { return this->notes; }
    inline void set_notes(string new_notes) { delete this->notes; this->notes = new string(new_notes); }
    
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

