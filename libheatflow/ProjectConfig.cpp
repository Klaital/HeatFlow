#include "stdafx.h"
#include "ProjectConfig.h"


ProjectConfig::ProjectConfig()
{
	this->matrix_size[0] = 0;
	this->matrix_size[1] = 0;
	this->initial_temperatures = 0;
}

ProjectConfig::ProjectConfig(const std::string& path) {
	this->matrix_size[0] = 0;
	this->matrix_size[1] = 0;
	this->initial_temperatures = 0;

	// TODO: load JSON data from the given path
}

ProjectConfig::~ProjectConfig()
{
}

std::string ProjectConfig::get_title()
{
	return this->title;
}
void ProjectConfig::set_title(const std::string& new_title)
{
	this->title = new_title;
}

size_t* ProjectConfig::get_matrix_size() {
	return this->matrix_size;
}

temperature_t* ProjectConfig::get_initial_temperatures() {
	return this->initial_temperatures;
}
