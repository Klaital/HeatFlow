// ThermalSimulator.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int argc, char ** argv)
{
	if (argc == 1) {
		std::cout << "Usage: " << argv[0] << " PROJECT_FILE" << std::endl;
		exit(0);
	}

	std::string project_config_path(argv[1]);
	std::cout << "Thermal Simulation initializing..." << std::endl;
	std::cout << "Loading project config at " << project_config_path.c_str() << std::endl;


    return 0;
}

