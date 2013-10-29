#include "HeatFlowProject.h"

namespace HeatFlow {

HeatFlowProject::HeatFlowProject()
{
    this->output_path = ".";
    this->title = "New HeatFlow Project";
    this->notes = "Project notes here";
    
    this->x_distance = 1.0;
    this->y_distance = 1.0;
    this->time_step  = 1000;

    this->initial_temps = NULL;
    this->materials = NULL;
    this->bom = NULL;
}

HeatFlowProject::~HeatFlowProject()
{
}

} // namespace HeatFlow

