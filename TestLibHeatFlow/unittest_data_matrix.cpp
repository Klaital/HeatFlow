#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestLibHeatFlow
{
	TEST_CLASS(UnitTestDataMatrix)
	{
	public:

		TEST_METHOD(TestDataMatrixAccessors)
		{
			DataMatrix<int> * matrix;
			matrix = new DataMatrix<int>();

			Assert::IsNull(matrix->get_data());
			
			size_t dimensions[2] = { 4, 4 };
			boost::multi_array<int, 2> new_data;
			for (size_t i = 0; i < new_data.shape()[0]; i++) {
				for (size_t j = 0; j < new_data.shape()[1]; j++) {
					new_data[i][j] = i + j;
				}
			}
			
			matrix->set_data(new_data);
			Assert::IsNotNull(matrix->get_data());
			Assert::AreEqual((size_t)4, matrix->get_data()->shape()[0]);
			Assert::AreEqual((size_t)4, matrix->get_data()->shape()[1]);

			boost::array< boost::multi_array<int, 2>::index, 2 > idx = { {0,0} };
			
			boost::multi_array<int, 2> *data = matrix->get_data();
			Assert::IsNotNull(data);
			Assert::AreEqual((size_t)4, data->shape()[0]);
			Assert::AreEqual((size_t)4, data->shape()[1]);
			Assert::AreEqual(0, (*data)[0][0] );
			/*
			Assert::AreEqual(0, (*matrix->get_data())(idx));
			idx = { {3,1} };
			Assert::AreEqual(3, (*matrix->get_data())(idx));
			*/
		}

		TEST_METHOD(TestDataMatrixSerialization)
		{
			/*
			DataMatrix<int> * matrix;
			matrix = new DataMatrix<int>();

			Assert::AreEqual((size_t)0, matrix->get_data()->shape()[0]);
			Assert::AreEqual((size_t)0, matrix->get_data()->shape()[1]);

			size_t dimensions[2] = { 3, 4 };
			boost::multi_array<int, 2> new_data;
			for (size_t i = 0; i < new_data.shape()[0]; i++) {
				for (size_t j = 0; j < new_data.shape()[1]; j++) {
					new_data[i][j] = i + j;
				}
			}
			matrix->set_data(new_data);
			Assert::IsNotNull(matrix->get_data());
			Assert::AreEqual((size_t)3, matrix->get_data()->shape()[0]);
			Assert::AreEqual((size_t)4, matrix->get_data()->shape()[1]);

			std::string matrix_path("test_serialization.intfield");
			int save_results = matrix->save(matrix_path);
			Assert::AreEqual(1, save_results);
			*/
		}

	};
}
