#include "MatrixFile.h"
#include "gtest/gtest.h"
#include <boost/numeric/ublas/matrix.hpp>

// Tests MatrixFile

TEST(DataSetTest, Positive) {
	HeatFlow::MatrixFile<int> *test_file = new HeatFlow::MatrixFile<int>(2,2);
	boost::numeric::ublas::matrix<int> sample_data(3,3);
	test_file->set_data(sample_data);
	EXPECT_EQ(test_file->get_data()->size1(), sample_data.size1());
}
