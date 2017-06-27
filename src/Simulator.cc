#include "Simulator.h"

namespace HeatFlow {
	Simulator::Simulator() {
		this->elapsed_time_ = 0;
	}
	Simulator::Simulator(const HeatFlowProject& project_config) {
		this->project_config_ = project_config;
		this->previous_temps_ = new MatrixFile<temperature_t>(this->project_config_.get_initial_temps());
		this->project_config_.copy_materials_matrix(this->materials_);
		//this->materials_ = new MatrixFile<Material *>(this->project_config_.get_materials_matrix());
		this->elapsed_time_ = 0;
	}
	Simulator::~Simulator() {
		delete this->previous_temps_;
		delete this->next_temps_;
	}
	Simulator& Simulator::operator=(const Simulator& s) {
		this->project_config_ = s.get_project_config();
		this->previous_temps_ = new MatrixFile<temperature_t>(this->project_config_.get_initial_temps());
		this->project_config_.copy_materials_matrix(this->materials_);
		this->elapsed_time_ = 0;
	}
}
