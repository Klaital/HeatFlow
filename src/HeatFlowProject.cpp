#include "HeatFlowProject.hpp"

namespace HeatFlow {

HeatFlowProject::HeatFlowProject()
{
    this->output_path = ".";
    this->title = "New HeatFlow Project";
    this->notes = "Project notes here";
    
    this->x_distance = 1.0;
    this->y_distance = 1.0;
    this->time_step  = 1000;
}

HeatFlowProject::~HeatFlowProject()
{
    delete this->output_path;
    delete this->title;
    delete this->notes;
}

} // namespace HeatFlow

