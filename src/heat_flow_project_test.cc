#include "HeatFlowProject.h"
#include "MatrixFile.h"
#include "Material.h"

#include "gtest/gtest.h"
#include <boost/numeric/ublas/matrix.hpp>
#include <string>

// Tests HeatFlowProject

TEST(ProjectBasic, Accessors) {
	HeatFlow::HeatFlowProject *project;
	project = new HeatFlow::HeatFlowProject();

	std::string title("test title");
	project->set_title(title);
	EXPECT_EQ("test title", project->get_title());

	std::string project_config_path = "./project.config";
	project->set_project_config_filename(project_config_path);
	EXPECT_EQ("./project.config", project->get_project_config_filename());

	std::string notes = "this project is ephemeral - used only in this one test case.";
	project->set_notes(notes);
	EXPECT_EQ("this project is ephemeral - used only in this one test case.", project->get_notes());

	project->set_field_gap_distance(15.5);
	EXPECT_EQ(15.5, project->get_field_gap_distance());

	project->set_time_step(1.15);
	EXPECT_EQ(1.15, project->get_time_step());

	std::string initial_temps_path = "./temps.matrix";
	project->set_initial_temps_path(initial_temps_path);
	EXPECT_EQ("./temps.matrix", project->get_initial_temps_path());

	std::string materials_path = "./materials.matrix";
	project->set_materials_path(materials_path);
	EXPECT_EQ("./materials.matrix", project->get_materials_path());

	// TODO: add/remove data matrices

	HeatFlow::Material m1,m2;
	m1.set_name("Test material 1");
	m2.set_name("Test material 2");
	project->add_material(m1);
	EXPECT_EQ(1, project->get_bom().size());
	project->add_material(m2);
	EXPECT_EQ(2, project->get_bom().size());
	EXPECT_EQ("Test material 1", project->get_bom()[0].get_name());
	EXPECT_EQ("Test material 2", project->get_bom()[1].get_name());
	
	int delete_success = project->delete_material("Test material 1");
	EXPECT_EQ(1, delete_success);
	EXPECT_EQ(2, project->get_bom().size()); // TODO: implement real BoM deletion
	EXPECT_EQ("Unused BoM Material", project->get_bom()[0].get_name());
	EXPECT_EQ("Test material 2", project->get_bom()[1].get_name());
	
	delete_success = project->delete_material(1);
	EXPECT_EQ(2, project->get_bom().size()); // TODO: implement real BoM deletion
	EXPECT_EQ("Unused BoM Material", project->get_bom()[0].get_name());
	EXPECT_EQ("Unused BoM Material", project->get_bom()[1].get_name());
}

TEST(ProjectLoadTest, HandwrittenSample) {

	HeatFlow::HeatFlowProject project;

	// Load from a file, and validate whether the object reports success
	int file_read_success = project.load_from_file("../test/data/sample1.heatproject");
	EXPECT_EQ(1, file_read_success);
/*
	// Validate each of the member fields individually
	EXPECT_EQ("Sample Sim 1", project.get_title());
	EXPECT_EQ("Here, we are simulating a simple model for the sake of unit testing the code base", project.get_notes());

	EXPECT_EQ(1.0, project.get_time_step());
	EXPECT_EQ(0.00001, project.get_field_gap_distance());

	EXPECT_EQ("./sample3_initial_temps.floatfield", project.get_initial_temps_path());
	EXPECT_EQ("./sample3_materials.intfield", project.get_materials_path());

	EXPECT_EQ(3, project.get_bom().size());
	std::vector<HeatFlow::Material> bom = project.get_bom();
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

	// TODO: Validate the data files as well.
*/
}
/*
TEST(ProjectAccessorsTest, SingleMaterialQuery) {
	HeatFlow::HeatFlowProject project;

	// Load from a file, and validate whether the object reports success
	int file_read_success = project.load_from_file("../test/data/sample1.heatproject");
	EXPECT_EQ(1, file_read_success);

	HeatFlow::MatrixFile<const HeatFlow::Material *> materials;
	project.copy_materials_matrix(materials);
	//HeatFlow::Material *m = materials.get_datum(0, 0);
	EXPECT_EQ("Air", materials.get_datum(0, 0)->get_name());
	EXPECT_EQ(1.225, materials.get_datum(0, 0)->get_density());
	EXPECT_EQ(0.024, materials.get_datum(0, 0)->get_conductivity());

	//m = materials.get_datum(2, 2);
	EXPECT_EQ("Aluminum", materials.get_datum(2, 2)->get_name());
	EXPECT_EQ(2712, materials.get_datum(2, 2)->get_density());
	EXPECT_EQ(205, materials.get_datum(2, 2)->get_conductivity());
}
*/