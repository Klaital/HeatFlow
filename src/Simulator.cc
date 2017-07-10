#include "Simulator.h"

namespace HeatFlow {
	Simulator::Simulator() {
		this->elapsed_time_ = 0.0;
	}
	Simulator::Simulator(const HeatFlowProject& project_config) {
		this->project_config_ = project_config;
		//this->previous_temps_ = new MatrixFile<temperature_t>(this->project_config_.get_initial_temps());
		//this->project_config_.copy_materials_matrix(this->materials_);
		//this->materials_ = new MatrixFile<Material *>(this->project_config_.get_materials_matrix());
		this->elapsed_time_ = 0.0;
	}
	
	Simulator& Simulator::operator=(const Simulator& s)
    {
        if(this == &s)
          return *this;
    
		this->project_config_ = s.get_project_config();
		this->elapsed_time_ = 0.0;
		this->initialize_arrays();
		return *this;
	}

	void Simulator::initialize_arrays()
	{
		// Start by copying in a local copy of the materials for the model
		this->project_config_.copy_materials_matrix(this->materials_);

		// Use the dimensions of the materials matrix to resize the temperature matrices
		boost::array< boost::multi_array_types::size_type, 2 > extents = {{ this->materials_.get_size1(), this->materials_.get_size1() }};
		this->next_temps_.resize(extents);
		this->previous_temps_.resize(extents);

		// Use the data in the project config's initial temperature setup to initialize the "new temperatures" array.
		// (only the new temperatures need to be initialized, because the first step of any simulation run will be to 
		// copy those values into the "old temperatures" array)
		MatrixFile<temperature_t> initial_temps = this->project_config_.get_initial_temps();
		for (boost::multi_array_types::size_type i=0; i < this->materials_.get_size1(); i++)
		{
			for (boost::multi_array_types::size_type j=0; j < this->materials_.get_size2(); j++)
			{
				boost::array< boost::multi_array_types::size_type, 2 > index = {{ i, j }};
				this->next_temps_(index) = (*(initial_temps.get_data()))(index);
			}
		}
	}
	
	void Simulator::simulate()
	{
		// Copy the last iteration's results to the "old state" array
		for (boost::multi_array_types::size_type i=0; i < this->materials_.get_size1(); i++)
		{
			for (boost::multi_array_types::size_type j=0; j < this->materials_.get_size2(); j++)
			{
				boost::array< boost::multi_array_types::size_type, 2 > index = {{ i, j }};
				this->previous_temps_(index) = this->next_temps_(index);
			}
		}

		// TODO: implement real calculations for the simulation step
		for (boost::multi_array_types::size_type i=0; i < this->materials_.get_size1(); i++)
		{
			for (boost::multi_array_types::size_type j=0; j < this->materials_.get_size2(); j++)
			{
				boost::array< boost::multi_array_types::size_type, 2 > index = {{ i, j }};
				this->next_temps_(index) = this->previous_temps_(index) + 0.1; // TODO: implement real calculations
			}
		}
	}
}
