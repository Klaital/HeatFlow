#ifndef HEATFLOW_MATRIXFILE_H_
#define HEATFLOW_MATRIXFILE_H_

#include <boost/numeric/ublas/matrix.hpp>
#include <boost/algorithm/string.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include "utilities.h"

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
		inline void set_data(boost::numeric::ublas::matrix<T> &new_data) { delete this->data_; this->data_ = new boost::numeric::ublas::matrix<T>(new_data); }

		// Utility functions for interacting with the underlying data matrix
		inline void set_datum(size_t i, size_t j, T new_value) { (*this->data_)(i, j) = new_value; }
		inline T    get_datum(size_t i, size_t j) { return (*this->data_)(i,j); }

		void initialize(size_t i, size_t j) {
			this->data_->resize(i, j, false);
		}
		void initialize(size_t i, size_t j, T default_value) {
			this->data_->clear();
			this->data_->resize(i, j, false);
			for (size_t i=0; i < this->data_->size1(); i++) {
				for (size_t j = 0; j < this->data_->size2(); j++) {
					(*this->data_)(i, j) = default_value;
				}
			}
		}

		// File I/O
		int read_file_ascii(const std::string& path) {
			// Validate that the file exists
			std::ifstream file;

			// Open the given file readonly
			file.open(path, std::ios::in);
			if (!file.good()) {
				return 0;
			}

			std::string header_line;
			std::getline(file, header_line);
			boost::trim_right(header_line);
			std::vector<std::string> tokens = string_split(header_line, " ");
			if (tokens.size() < 2) {
				return -1;
			}

			// Reinitialize the matrix
			size_t size1 = std::stoi(tokens[0]);
			size_t size2 = std::stoi(tokens[1]);
			if (size1 <= 0 || size2 <= 0) {
				return -2;
			}
			this->data_->resize(size1, size2, false);

			// Read in the data rows
			std::string line;
			std::stringstream sstream;
			T cast_tmp;
			for (int i = 0; i < size1; i++) {
				if (file.eof()) {
					// We ran out of file before we should have.
					return -3;
				}
				std::getline(file, line);
				
				// Parse the line on single whitespace, then check for validity
				tokens.clear();
				tokens = string_split(line, " ");
				boost::trim_right(line);

				if (tokens.size() != size2) {
					// Incorrect number of columns in one of the rows
					return -4;
				}

				// Parse each of the tokens into a type T variable, and set it in the data matrix
				for (int j = 0; j < size2; j++) {
					sstream.clear();
					sstream.str(tokens[j]);
					sstream >> cast_tmp;
					this->data_->insert_element(i, j, cast_tmp);
				}
			} 

			file.close();
			return 1;
		}  // read_file_ascii()
	}; // class MatrixFile

} // namespace HeatFlow
#endif
