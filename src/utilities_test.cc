#include "gtest/gtest.h"
#include <boost/numeric/ublas/matrix.hpp>
#include <boost/algorithm/string.hpp>

#include "utilities.h"

#include <iostream>
#include <fstream>


TEST(StringSplitTest, Positive) {
	std::string str("Hello, world!");
	std::vector<std::string> tokens = string_split(str, " ");

	EXPECT_EQ(2, tokens.size());
	EXPECT_EQ("Hello,", tokens[0]);

	tokens = string_split(str, ", ");
	EXPECT_EQ(2, tokens.size());
	EXPECT_EQ("Hello", tokens[0]);

	str = "10 15";
	tokens = string_split(str, " ");
	EXPECT_EQ(2, tokens.size());
	EXPECT_EQ("10", tokens[0]);
}

TEST(FileIOTest, WritePositive) {
	std::string path("sample2_ascii.intfield");
	
	std::ofstream file;
	file.open(path.c_str(), std::ofstream::out | std::ofstream::trunc);
	EXPECT_TRUE(file.good());

	file << "10 16" << std::endl;
	EXPECT_TRUE(file.good());
	file.flush();
	file.close();
}

TEST(FileReadTest, Negative) {
	std::string path("../test/data/sample1_ascii.intfield__");
	std::ifstream file;
	
	file.open(path, std::ios::in);
	EXPECT_FALSE(file.good()); 
	EXPECT_FALSE(file.is_open());
	file.close();
}

TEST(FileReadTest, IntegerReadPositive) {
	std::string path("/mnt/c/Users/kenka/Documents/GitHub/HeatFlow/test/data/sample1_ascii.intfield");
	std::ifstream file;
	
	file.open(path, std::ifstream::in);
	EXPECT_TRUE(file.is_open());
	EXPECT_FALSE(file.bad());
	
	std::string line;
	std::getline(file, line);
	boost::trim_right(line);
	EXPECT_FALSE(file.fail());
	EXPECT_EQ("10 15", line);

	// Try reading values from the file
	std::vector<std::string> tokens;
	tokens = string_split(line, " ");
	EXPECT_EQ(2, tokens.size());

	file.close();
}