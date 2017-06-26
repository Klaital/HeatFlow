#include "HeatFlowProject.h"

namespace HeatFlow {

	HeatFlowProject::HeatFlowProject()
	{
		this->title_ = "New Sim Project";
		this->notes_ = "";
		this->initial_temps_matrix_path_ = "Temps.floatfield";
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

		// Load the single-value elements
		this->title_ = root->FirstChildElement("Title")->GetText();
		this->notes_ = root->FirstChildElement("Notes")->GetText();

		this->time_step_ = std::strtod(root->FirstChildElement("TimeStep")->GetText(), NULL);
		this->field_gap_distance_ = std::strtod(root->FirstChildElement("FieldGapDistance")->GetText(), NULL);

		// Get the absolute paths to the data files. 
		// In the project file, they are specified relative to the config file's directory.
		boost::filesystem::path config_path(path);
		boost::filesystem::path initial_temps_path(root->FirstChildElement("InitialTemperaturesField")->FirstChildElement("path")->GetText());
		this->initial_temps_matrix_path_ = (config_path.parent_path() / initial_temps_path).native();
		boost::filesystem::path materials_matrix_path(root->FirstChildElement("MaterialsField")->FirstChildElement("path")->GetText());
		this->materials_matrix_path_ = (config_path.parent_path() / materials_matrix_path).native();

		// Load the Bill of Materials
		tinyxml2::XMLElement *bom = root->FirstChildElement("Materials");
		tinyxml2::XMLElement *material = bom->FirstChildElement();
		Material tmp_material;
		int new_id = 0;
		while (material != NULL) {
			tmp_material.set_name(material->FirstChildElement("name")->GetText());
			tmp_material.set_density(std::strtod(material->FirstChildElement("density")->GetText(), NULL));
			tmp_material.set_conductivity(std::strtod(material->FirstChildElement("conductivity")->GetText(), NULL));
			new_id = material->IntAttribute("id");
			this->bom_[new_id] = tmp_material;

			material = material->NextSiblingElement();
		}

		// load initial temperatures
		if (boost::filesystem::exists(this->initial_temps_matrix_path_)) {
			if (!this->initial_temperatures_.read_file_ascii(this->initial_temps_matrix_path_)) return -2;
		}
		else {
			return -1;
		}

		// load materials configuration
		if (boost::filesystem::exists(this->materials_matrix_path_)) {
			if (!this->materials_.read_file_ascii(this->materials_matrix_path_)) return -4;
		}
		else {
			return -3;
		}
		
		// Check whether the temperature and materials matrices are the same size.
		if (this->initial_temperatures_.get_data()->size1() != this->materials_.get_data()->size1() 
			|| this->initial_temperatures_.get_data()->size2() != this->materials_.get_data()->size2()) 
		{
			return -5;
		}
		
		// If we got here, life must be good
		return 1;
	}

	int HeatFlowProject::add_material(const Material& new_material) {
		// Find the largest currently-used index
		int max_index = 0;
		for (std::map<int, Material>::iterator it = this->bom_.begin(); it != this->bom_.end(); ++it) {
			if (it->first > max_index) {
				max_index = it->first;
			}
		}

		// Increment that index to create a new, unused one
		int new_index = max_index + 1;

		// Assign the new material to the BoM at the computed index
		this->bom_[new_index] = new_material;

		// Then return it
		return new_index;
	}
	int HeatFlowProject::delete_material(const std::string& name) {
		// Find the index in the BoM of a Material named 'name'
		for (std::map<int, Material>::iterator it = this->bom_.begin(); it != this->bom_.end(); ++it) {
			if (name == it->second.get_name()) {
				this->bom_.erase(it);
				return 1;
			}
		}

		// If we get here, no materials matched the given name
		return 0;
	}
	int HeatFlowProject::delete_material(int index) {
		std::map<int, Material>::iterator it = this->bom_.find(index);
		if (it == this->bom_.end()) {
			return 0;
		}
		
		this->bom_.erase(index);
		return 1;
	}

	void HeatFlowProject::copy_materials_matrix(MatrixFile<Material *> &materials_matrix) {
		// initialize the resulting matrix with the correct dimensions
		materials_matrix.initialize(this->materials_.get_size1(), this->materials_.get_size2());
		//MatrixFile<Material *> materials_matrix(this->materials_.get_size1(), this->materials_.get_size2());

		// Convert the BOM index at each matrix node into a pointer to the actual Material object in the BOM
		for (size_t i = 0; i < this->materials_.get_size1(); i++) {
			for (size_t j = 0; j < this->materials_.get_size2(); j++) {
				materials_matrix.set_datum(i, j, &this->bom_[this->materials_.get_datum(i, j)]);
			}
		}

	}
} // namespace HeatFlow

