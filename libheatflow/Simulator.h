#pragma once


class Simulator
{
public:
	// Constructors
	Simulator();
	~Simulator();

	// Accessors
	temperature_t* get_temperatures_old();
	temperature_t* get_temperatures_new();

	// Simulation methods
	int simulation_init();
	int simulate_step();

	

private:
	size_t matrix_size[2];
	temperature_t* temperatures_old;
	temperature_t* temperatures_new;
};

