#include "Simulator.h"
#include "HeatFlowProject.h"
#include "MatrixFile.h"
#include "Material.h"

#include "gtest/gtest.h"

// Tests Simulator.h

TEST(SimulatorSetup, Initialization) {
    HeatFlow::Simulator simulator;
    EXPECT_EQ(0.0, simulator.get_elapsed_time());

    HeatFlow::HeatFlowProject project;
    // Load from a file, and validate whether the object reports success
    int file_read_success = project.load_from_file("../test/data/sample1.heatproject");
    EXPECT_EQ(1, file_read_success);

    simulator.set_project_config(project);
    EXPECT_EQ("Sample Sim 1", simulator.get_project_config().get_title());

    simulator.initialize_arrays();
    boost::multi_array<temperature_t, 2> *next_temps = simulator.get_next_temps();
    boost::multi_array<temperature_t, 2> *previous_temps = simulator.get_previous_temps();

    // After the initialization, the next_temps array should be initialized with proper data. 
    // Meanwhile, the previous_temps array is allocated, but not initialized. 
    // Its values are undefined here, and thus not tested. (see SimulationBasic test case for that)
    EXPECT_EQ(10, next_temps->shape()[0]);
    EXPECT_EQ(15, next_temps->shape()[1]);
    boost::array< boost::multi_array_types::size_type, 2 > index1 = {{ 0, 0 }};
    EXPECT_EQ(123.4, (*next_temps)(index1));
    boost::array< boost::multi_array_types::size_type, 2 > index2 = {{ 0, 1 }};
    EXPECT_EQ(0.0, (*next_temps)(index2));
}

// TEST(Simulator, SimulationBasic)
// {
//     HeatFlow::Simulator simulator;
//     EXPECT_EQ(0.0, simulator.get_elapsed_time());

//     HeatFlow::HeatFlowProject project;
//     // Load from a file, and validate whether the object reports success
//     int file_read_success = project.load_from_file("../test/data/sample1.heatproject");
//     EXPECT_EQ(1, file_read_success);

//     simulator.set_project_config(project);
//     EXPECT_EQ("Sample Sim 1", simulator.get_project_config().get_title());

//     // TODO: initialize the data arrays, then run a few iterations of simulations
//     simulator.initialize_arrays();
//     simulator.simulate();

// }