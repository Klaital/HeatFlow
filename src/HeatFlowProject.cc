#include "HeatFlowProject.h"

namespace HeatFlow {

HeatFlowProject::HeatFlowProject()
{
	title = "New Sim Project";
	notes = "";
	initial_temps_matrix_path = "Temps.matrix";
	bom_path = "BOM.json";
	materials_matrix_path = "Materials.matrix";

	this->initial_temps = new boost::numeric::ublas::matrix<temperature_t>();
	this->materials = new boost::numeric::ublas::matrix<int>();
	this->bom = new MaterialsCollection();

	// TODO: decide what units these will be defined in. Maybe we can use a string for that, plus a unit-conversion library? 
	// For now, we'll assume 'meter', I guess.
	x_distance = 0.0001; // the distance between nodes in the X direction
	y_distance = 0.0001; // the distance between nodes in the Y direction
	time_step = 1;  // number of milliseconds between calculation iterations
}

HeatFlowProject::~HeatFlowProject()
{
	delete this->bom;
}

} // namespace HeatFlow

