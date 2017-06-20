#include "HeatFlowProject.h"
#include "gtest/gtest.h"
#include <boost/numeric/ublas/matrix.hpp>

// Tests HeatFlowProject

TEST(ProjectBasic, Accessors) {
	HeatFlow::HeatFlowProject *project;
	project = new HeatFlow::HeatFlowProject();

	project->set_title("test title");
	EXPECT_EQ("test title", project->get_title());
}

TEST(ProjectLoadTest, HandwrittenSample) {

	HeatFlow::HeatFlowProject project;

	// Load from a file, and validate whether the object reports success
	int file_read_success = project.load_from_file("../test/data/sample1.heatproject");
	EXPECT_EQ(1, file_read_success);

	// Validate each of the member fields individually
	EXPECT_EQ("Sample Sim 1", project.get_title());
	EXPECT_EQ("Here, we are simulating a simple model for the sake of unit testing the code base", project.get_notes());

	EXPECT_EQ(1.0, project.get_time_step());
	EXPECT_EQ(0.00001, project.get_field_gap_distance());
	
	EXPECT_EQ("./sample3_initial_temps.floatfield", project.get_initial_temps_path());
	EXPECT_EQ("./sample3_materials.intfield", project.get_materials_path());
	
	EXPECT_EQ(3, project.get_bom().size());
	std::map<int, HeatFlow::Material> bom = project.get_bom();
	HeatFlow::Material mat1;
	HeatFlow::Material mat2;
	HeatFlow::Material mat3;
	
	mat1 = bom[0];
	EXPECT_EQ("Air", mat1.get_name());
	EXPECT_EQ(1.225, mat1.get_density());
	EXPECT_EQ(0.024, mat1.get_conductivity());

	mat2 = bom[1];
	EXPECT_EQ("Aluminum", mat2.get_name());
	EXPECT_EQ(2712.0, mat2.get_density());
	EXPECT_EQ(205.0, mat2.get_conductivity());

	mat3 = bom[2];
	EXPECT_EQ("Glass", mat3.get_name());
	EXPECT_EQ(2400.0, mat3.get_density());
	EXPECT_EQ(1.05, mat3.get_conductivity());

	// TODO: write the temps and materials data files, and validate their values here
}