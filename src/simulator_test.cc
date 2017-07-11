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

    // Validate the shape of all of the relevant arrays:
    // 1) Project Config / initial temps
    // 2) Project Config / Materials layout
    // 3) Project Config / Bill of Materials (all values in the materials layout should be valid indices in the Bill of Materials)
    
    // Part 1: Validate the shape of the initial temps matrix
    HeatFlow::MatrixFile<temperature_t> initial_temps_matrix = project.get_initial_temps();
    EXPECT_EQ(10, initial_temps_matrix.get_size1());
    EXPECT_EQ(15, initial_temps_matrix.get_size2());

    // Part 2: Validate the shape of the materials layout matrix
    HeatFlow::MatrixFile<unsigned int> materials_layout_matrix = project.get_materials();
    EXPECT_EQ(10, materials_layout_matrix.get_size1());
    EXPECT_EQ(15, materials_layout_matrix.get_size2());

    // Find the largest included material index
    unsigned int max_material_index = 0;
    unsigned int tmp = 0;
    for (boost::multi_array_types::size_type i=0; i < materials_layout_matrix.get_size1(); i++)
    {
        for (boost::multi_array_types::size_type j = 0; j < materials_layout_matrix.get_size2(); j++)
        {
            tmp = materials_layout_matrix.get_datum(i,j);
            if (tmp > max_material_index)
                max_material_index = tmp;
        }
    }

    // Part 3: Validate that the materials indices all fall in bounds of the BoM
    EXPECT_GE(project.get_bom().size(), max_material_index);

    // Initialize the data arrays, then validate their shape and contents
    simulator.initialize_arrays();

    // Validate that the simulator's internal data arrays are properly allocated
    boost::multi_array<temperature_t, 2>* previous_temps = simulator.get_previous_temps();
    boost::multi_array<temperature_t, 2>* next_temps = simulator.get_next_temps();

    EXPECT_EQ(10, previous_temps->shape()[0]);
    EXPECT_EQ(15, previous_temps->shape()[1]);
    EXPECT_EQ(10, next_temps->shape()[0]);
    EXPECT_EQ(15, next_temps->shape()[1]);

    // After the initialization, the next_temps array should be initialized with proper data. 
    // Meanwhile, the previous_temps array is allocated, but not initialized. 
    // Its values are undefined here, and thus not tested. (see SimulationBasic test case for that)
    boost::array< boost::multi_array_types::size_type, 2 > index1 = {{ 0, 0 }};
    EXPECT_EQ(123.4, (*next_temps)(index1));
    boost::array< boost::multi_array_types::size_type, 2 > index2 = {{ 0, 1 }};
    EXPECT_EQ(0.0, (*next_temps)(index2));
}

TEST(Simulator, SimulationBasic)
{
    HeatFlow::Simulator simulator;
    EXPECT_EQ(0.0, simulator.get_elapsed_time());

    HeatFlow::HeatFlowProject project;
    // Load from a file, and validate whether the object reports success
    int file_read_success = project.load_from_file("../test/data/sample1.heatproject");
    EXPECT_EQ(1, file_read_success);

    simulator.set_project_config(project);
    EXPECT_EQ("Sample Sim 1", simulator.get_project_config().get_title());

    // initialize the data arrays, then run a few iterations of simulations
    boost::array< boost::multi_array_types::size_type, 2 > index1 = {{ 0, 0 }};
    boost::array< boost::multi_array_types::size_type, 2 > index2 = {{ 0, 1 }};
    boost::multi_array<temperature_t, 2>* next_temps = simulator.get_next_temps();
    simulator.initialize_arrays();
    EXPECT_EQ(123.4, (*next_temps)(index1));
    EXPECT_EQ(0.0, (*next_temps)(index2));
    simulator.simulate();

    next_temps = simulator.get_next_temps();
    EXPECT_EQ(123.5, (*next_temps)(index1));
    EXPECT_EQ(0.1, (*next_temps)(index2));
}