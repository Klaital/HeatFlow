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

	tinyxml2::XMLElement *root = doc.FirstChildElement("HeatProject");

	this->title_ = root->FirstChildElement("Title")->GetText();
	this->notes_ = root->FirstChildElement("Notes")->GetText();

	this->time_step_          = std::strtod(root->FirstChildElement("TimeStep")->GetText(), NULL);
	this->field_gap_distance_ = std::strtod(root->FirstChildElement("FieldGapDistance")->GetText(), NULL);

	this->initial_temps_matrix_path_ = root->FirstChildElement("InitialTemperaturesField")->FirstChildElement("path")->GetText();
	this->materials_matrix_path_     = root->FirstChildElement("MaterialsField")->FirstChildElement("path")->GetText();
	// TODO: load temperatures and materials files
	return 1;
}

} // namespace HeatFlow

