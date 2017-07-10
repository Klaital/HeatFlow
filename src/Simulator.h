#ifndef HEATFLOW_SIMULATOR_H_
#define HEATFLOW_SIMULATOR_H_

#include "configs.h"
#include "MatrixFile.h"
#include "HeatFlowProject.h"
#include "Material.h"
#include <boost/multi_array.hpp>

namespace HeatFlow {
	class Simulator {

	public:
		// Constructors
		Simulator();
		Simulator(const HeatFlowProject& project_config);
		
		// Operator Overloads
		Simulator& operator=(const Simulator &s);

		//
		// Utility Methods
		//

		// Make local copies of the project config's materials model, and 
		// initialize the internal temperature arrays with the size and 
		// initial values from the config.
		void initialize_arrays();

		// Accessors
		inline HeatFlowProject  get_project_config() const { return this->project_config_; }
		inline void             set_project_config(const HeatFlowProject& new_config) { this->project_config_ = new_config; }
		inline time_delta_t     get_elapsed_time()   const { return this->elapsed_time_; } 

	private:
		// Total time spent in simulation, in seconds. Generally, equal to the 
		// number of times "simulate" has been called * the time step value in
		// the project config
		time_delta_t elapsed_time_; 

		// Local copy of the project configuration settings. Most of the data will 
		// be copied into this object for operation, but the save paths will be 
		// left in this data structure.
		HeatFlowProject project_config_;

		// A local copy of the materials matrix from the project config. 
		// This has useable pointers in the node positions, rather then indices 
		// into the Bill of Materials (which is how the save files are written).
		MatrixFile<const Material *> materials_;

		// The temperature arrays. These hold the starting config for a simulation 
		// step, and the newly-computed temperatures after the last simulation step, 
		// respectively.
		boost::multi_array<temperature_t, 2> previous_temps_;
		boost::multi_array<temperature_t, 2> next_temps_;
	};
}

#endif
