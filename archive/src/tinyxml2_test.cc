#include "tinyxml2.h"
#include "gtest/gtest.h"
#include <string>

TEST(XmlTraining, FileRead) {
	std::string path = "../test/data/sample1.heatproject";
	tinyxml2::XMLDocument doc;
	tinyxml2::XMLError file_read_status = doc.LoadFile(path.c_str());
	EXPECT_EQ(tinyxml2::XMLError::XML_SUCCESS, file_read_status);

	std::string title;
	title = doc.FirstChildElement("HeatProject")->FirstChildElement("Title")->GetText();
	EXPECT_EQ("Sample Sim 1", title);
}
