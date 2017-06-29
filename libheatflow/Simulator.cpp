#include "stdafx.h"
#include "Simulator.h"


Simulator::Simulator()
{
	this->matrix_size[0] = 0;
	this->matrix_size[1] = 0;
	this->temperatures_new = 0;
	this->temperatures_old = 0;
}


Simulator::~Simulator()
{
	delete[] this->temperatures_new;
	delete[] this->temperatures_old;
}

temperature_t* Simulator::get_temperatures_old() {
	return this->temperatures_old;
}

temperature_t* Simulator::get_temperatures_new() {
	return this->temperatures_new;
}

int Simulator::simulation_init() {
	// TODO: initialize the temperatures_new matrix from the project config
	if (this->matrix_size[0] == 0 || this->matrix_size[1] == 0)
		return 0;

	this->temperatures_new = new temperature_t[this->matrix_size[0] * this->matrix_size[1]];
	// TODO: initialize the Materials matrix from the project config + project BoM

	return 0;
}

int Simulator::simulate_step() {
	// TODO: iterate across all nodes in the matrix

	// TODO: compute the heat flowing into each node from all adjacent nodes, ignoring any outside the matrix

	return 0;
}