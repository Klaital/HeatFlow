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
		unsigned int new_id = 0;
		unsigned int max_id = 0;

		// Loop once to find the max index, so that we can pre-allocate the array
		while (material != NULL)
		{
			new_id = material->IntAttribute("id");
			if (new_id >= max_id)
				max_id = new_id;
			
			material = material->NextSiblingElement();
		}
		this->bom_.resize(max_id+1);

		// Loop a second time to place each Material in it's correct index
		material = bom->FirstChildElement(); // start over
		while (material != NULL) {
			// Extract the materials data
			tmp_material.set_name(material->FirstChildElement("name")->GetText());
			tmp_material.set_density(std::strtod(material->FirstChildElement("density")->GetText(), NULL));
			tmp_material.set_conductivity(std::strtod(material->FirstChildElement("conductivity")->GetText(), NULL));
			// Set the material in the correct index in the BoM
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
		if (this->initial_temperatures_.get_size1() != this->materials_.get_size1() 
			|| this->initial_temperatures_.get_size2() != this->materials_.get_size2()) 
		{
			return -5;
		}

		// If we got here, life must be good
		return 1;
	}

	unsigned int HeatFlowProject::add_material(const Material& new_material) {
		// Find the largest currently-used index
		unsigned int found_index = 0;
		for (std::vector<Material>::iterator it = this->bom_.begin(); it != this->bom_.end(); ++it)
		{
			if ("Unused BoM Material" == it->get_name())
			{
				(*it) = new_material;
				return found_index;
			}
			found_index++;
		}

		// If we reach here, then there were no holes in the BoM, 
		// so push the new material onto the end of the list.
		this->bom_.push_back(new_material);

		// Then return the new entry's index
		return this->bom_.size() - 1;
	}

	int HeatFlowProject::delete_material(const std::string& name) {
		// Find the index in the BoM of a Material named 'name'
		for (std::vector<Material>::iterator it = this->bom_.begin(); it != this->bom_.end(); ++it) {
			if (name == it->get_name()) {
				it->set_name("Unused BoM Material");  // TODO: implement real BoM deletion. Until then, this name indicates a "deleted" item.
				//this->bom_.erase(it);
				return 1;
			}
		}

		// If we get here, no materials matched the given name
		return 0;
	}
	int HeatFlowProject::delete_material(unsigned int index) {
		if (index >= this->bom_.size())
		{
			return 0;
		}
		
		this->bom_[index].set_name("Unused BoM Material"); // TODO: implement real BoM deletion. Until then, this name indicates a "deleted" item.
		//this->bom_.erase(this->bom_.begin() + index);
		return 1;
	}

	void HeatFlowProject::copy_materials_matrix(MatrixFile<const Material *> &materials_matrix) const
	{
		/*
		// Copy the internal BoM to the return BoM
		for(unsigned int i=0; i < this->bom_.size(); i++)
		{
			bill_of_materials[i] = this->bom_[i];
		}
		*/
		// initialize the resulting matrix with the correct dimensions
		materials_matrix.initialize(this->materials_.get_size1(), this->materials_.get_size2());

		// Convert the BOM index at each matrix node into a pointer to the actual Material object in the BOM
		for (boost::multi_array_types::size_type i = 0; i < this->materials_.get_size1(); i++)
		{
			for (boost::multi_array_types::size_type j = 0; j < this->materials_.get_size2(); j++)
			{
				unsigned int index = this->materials_.get_datum(i,j);
				materials_matrix.set_datum(i, j, &(this->bom_[index]));
			}
		}

	}
} // namespace HeatFlow

