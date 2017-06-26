#include "Simulator.h"
#include "HeatFlowProject.h"
#include "MatrixFile.h"
#include "Material.h"

#include "gtest/gtest.h"

// Tests Simulator.h

TEST(SimulatorSetup, Accessors) {
	HeatFlow::HeatFlowProject project;
	// Load from a file, and validate whether the object reports success
	int file_read_success = project.load_from_file("../test/data/sample1.heatproject");
	EXPECT_EQ(1, file_read_success);

	HeatFlow::Simulator simulator(project);
	EXPECT_EQ(0, simulator.get_elapsed_time());
}