#include "HeatFlowProject.h"

namespace HeatFlow {

HeatFlowProject::HeatFlowProject()
{
	this->title_ = "New Sim Project";
	this->notes_ = "";
	this->initial_temps_matrix_path_= "Temps.floatfield";
	this->materials_matrix_path_ = "Materials.intfield";

	this->field_gap_distance_ = 0.00001; // the distance between nodes in the X direction
	this->time_step_ = 1;  // number of milliseconds between calculation iterations
}

HeatFlowProject::~HeatFlowProject()
{
}

int HeatFlowProject::load_from_file(const std::string& path) {
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError load_success = doc.LoadFile(path.c_str());
	if (load_success != tinyxml2::XMLError::XML_SUCCESS) {
		return 0;
	}
	this->title_ = doc.FirstChildElement("HeatProject")->FirstChildElement("Title")->GetText();
	this->notes_ = doc.FirstChildElement("HeatProject")->FirstChildElement("Notes")->GetText();


	// TODO: load temperatures and materials files
	return 1;
}

} // namespace HeatFlow

