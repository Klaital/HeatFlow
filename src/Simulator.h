#ifndef HEATFLOW_SIMULATOR_H_
#define HEATFLOW_SIMULATOR_H_

#include "configs.h"
#include "MatrixFile.h"
#include "HeatFlowProject.h"
#include "Material.h"

namespace HeatFlow {
	class Simulator {

	public:
		// Constructors
		Simulator();
		Simulator(const HeatFlowProject& project_config);
		~Simulator();

		// Accessors
		inline HeatFlowProject& get_project_config() { return this->project_config_; }
		inline time_t           get_elapsed_time()   { return this->elapsed_time_; } 

	private:
		time_t elapsed_time_;
		HeatFlowProject project_config_;
		MatrixFile<Material *>    materials_;
		MatrixFile<temperature_t> *previous_temps_;
		MatrixFile<temperature_t> *next_temps_;
	};
}

#endif
