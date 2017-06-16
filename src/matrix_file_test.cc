#include "MatrixFile.h"
#include "gtest/gtest.h"
#include <boost/numeric/ublas/matrix.hpp>

// Tests MatrixFile

TEST(DataSetTest, WholeNewMatrix) {
	HeatFlow::MatrixFile<int> *test_file = new HeatFlow::MatrixFile<int>(2,2);
	boost::numeric::ublas::matrix<int> sample_data(3,3);
	test_file->set_data(sample_data);
	EXPECT_EQ(sample_data.size1(), test_file->get_data()->size1());
	EXPECT_EQ(sample_data.size2(), test_file->get_data()->size2());
}

TEST(DataSetTest, SingleValue) {
	// Initialize the data matrix
	HeatFlow::MatrixFile<int> *test_file = new HeatFlow::MatrixFile<int>(2, 2);
	boost::numeric::ublas::matrix<int> sample_data(3, 3);
	test_file->set_data(sample_data);

	// Set a single new value
	test_file->set_datum(0, 0, 15);

	EXPECT_EQ(3, test_file->get_data()->size1());
	EXPECT_EQ(3, test_file->get_data()->size2());
	EXPECT_EQ(15, test_file->get_datum(0, 0));
}

TEST(FileIOTest, ReadIntAsciiSuccess) {
	HeatFlow::MatrixFile<int> *test_file = new HeatFlow::MatrixFile<int>();
	std::string path("../test/data/sample1_ascii.intfield");
	int file_read_success = test_file->read_file_ascii(path);

	// Check whether the data matrix resized correctly
	EXPECT_EQ(10, test_file->get_data()->size1());
	EXPECT_EQ(15, test_file->get_data()->size2());

	// Check if the file read method reported success
	EXPECT_EQ(1, file_read_success);
	// Test whether the resulting data matrix has the correct dimensions and values
	EXPECT_EQ(0, test_file->get_datum(0, 1));
	EXPECT_EQ(1234, test_file->get_datum(0, 0));
	EXPECT_EQ(3456, test_file->get_datum(7, 3));
}


TEST(FileIOTest, ReadDoubleAsciiSuccess) {
	HeatFlow::MatrixFile<double> *test_file = new HeatFlow::MatrixFile<double>();
	std::string path("../test/data/sample1_ascii.floatfield");
	int file_read_success = test_file->read_file_ascii(path);

	// Check whether the data matrix resized correctly
	EXPECT_EQ(10, test_file->get_data()->size1());
	EXPECT_EQ(15, test_file->get_data()->size2());

	// Check if the file read method reported success
	EXPECT_EQ(1, file_read_success);
	// Test whether the resulting data matrix has the correct dimensions and values
	EXPECT_EQ(0.0, test_file->get_datum(0, 1));
	EXPECT_EQ(123.4, test_file->get_datum(0, 0));
	EXPECT_EQ(345.6, test_file->get_datum(7, 3));
}


TEST(FileIOTest, ReadAsciiFileNotFound) {
	HeatFlow::MatrixFile<int> *test_file = new HeatFlow::MatrixFile<int>();
	std::string path("../test/data/sample1_ascii.intfield__");
	int file_read_success = test_file->read_file_ascii(path);

	EXPECT_EQ(0, file_read_success);
}

TEST(FileIOTest, ReadAsciiFileInvalidHeader) {
	HeatFlow::MatrixFile<int> *test_file = new HeatFlow::MatrixFile<int>();
	std::string path("../test/data/sample1_ascii_invalid_header.intfield");
	int file_read_success = test_file->read_file_ascii(path);

	EXPECT_EQ(-1, file_read_success);
}

TEST(FileWriteTest, WriteAsciiSuccess) {
	HeatFlow::MatrixFile<int> *test_file = new HeatFlow::MatrixFile<int>();

	// Initialize the matrix and validate the new structure
	test_file->initialize(10, 15, 3);
	EXPECT_EQ(10, test_file->get_data()->size1());
	EXPECT_EQ(15, test_file->get_data()->size2());
	EXPECT_EQ(3, test_file->get_datum(1, 1));

	// Alter one of the elements and revalidate
	test_file->set_datum(2, 2, 95);
	EXPECT_EQ(10, test_file->get_data()->size1());
	EXPECT_EQ(15, test_file->get_data()->size2());
	EXPECT_EQ(95, test_file->get_datum(2, 2));

}
