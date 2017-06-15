#ifndef HEATFLOW_MATRIXFILE_H_
#define HEATFLOW_MATRIXFILE_H_

#include <boost/numeric/ublas/matrix.hpp>
namespace HeatFlow {
	template<class T>
	class MatrixFile
	{
	private:
		boost::numeric::ublas::matrix<T> *data_;

	public:
		inline MatrixFile() { this->data_ = new boost::numeric::ublas::matrix<T>(2, 2); };
		inline MatrixFile(size_t size_i, size_t size_j) { this->data_ = new boost::numeric::ublas::matrix<T>(size_i, size_j); }
		inline ~MatrixFile() {
			delete this->data_;
		}

		// Accessors
		inline boost::numeric::ublas::matrix<T>* get_data() { return this->data_; }
		inline void set_data(boost::numeric::ublas::matrix<T> &new_data) { this->data_->swap(new_data); }

		// Utility functions for interacting with the underlying data matrix
		inline void set_datum(size_t i, size_t j, T new_value) { (*this->data_).insert_element(i, j, new_value); }
		inline T    get_datum(size_t i, size_t j) { return (*this->data_)[i][j]; }
	}; // class MatrixFile

} // namespace HeatFlow
#endif
