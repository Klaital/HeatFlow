#ifndef HEATFLOW_MATRIXFILE_H_
#define HEATFLOW_MATRIXFILE_H_

#include <boost/multi_array.hpp>
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
		boost::multi_array<T, 2> *data_;

	public:
		inline MatrixFile() { this->data_ = new boost::multi_array<T,2>(); };
		inline MatrixFile(boost::multi_array_types::size_type size_i, boost::multi_array_types::size_type size_j)
		{
			boost::array< boost::multi_array_types::size_type, 2 > extents = {{ size_i, size_j }};
			this->data_ = new boost::multi_array<T,2>(extents);
		}

		// Copy Constructor
		MatrixFile(const MatrixFile<T>& old_matrix)
		{
			// Resize our internal matrix to the size of the one we're copying in
			this->initialize(old_matrix.get_size1(), old_matrix.get_size2());

			// Copy in the old matrix's data
			for (boost::multi_array_types::size_type i = 0; i < old_matrix.get_size1(); i++) {
				for (boost::multi_array_types::size_type j = 0; j < old_matrix.get_size2(); j++)
				{
					this->set_datum(i,j, old_matrix.get_datum(i,j));
				}
			}
		}

		inline ~MatrixFile() {
			delete this->data_;
		}

		// Accessors
		inline boost::multi_array<T,2>* get_data() { return this->data_; }
		inline void set_data(boost::multi_array<T,2> &new_data) { delete this->data_; this->data_ = new boost::multi_array<T,2>(new_data); }
		inline boost::multi_array_types::size_type get_size1() const { return this->data_->shape()[0]; }
		inline boost::multi_array_types::size_type get_size2() const { return this->data_->shape()[1]; }

		// Utility functions for interacting with the underlying data matrix
		inline void set_datum(boost::multi_array_types::size_type i, boost::multi_array_types::size_type j, const T& new_value) 
		{
			boost::array< boost::multi_array_types::size_type, 2 > index = {{ i, j }};
			(*this->data_)(index) = new_value;
		}
		inline T    get_datum(boost::multi_array_types::size_type i, boost::multi_array_types::size_type j) const 
		{
			boost::array< boost::multi_array_types::size_type, 2 > index = {{ i, j }};
			return (*this->data_)(index);
		}

		void initialize(boost::multi_array_types::size_type i, boost::multi_array_types::size_type j)
		{
			boost::array< boost::multi_array_types::size_type, 2 > index = {{ i, j }};
			this->data_->resize(index);
		}
		void initialize(boost::multi_array_types::size_type i, boost::multi_array_types::size_type j, T default_value)
		{
			boost::array< boost::multi_array_types::size_type, 2 > index = {{ i, j }};
			this->data_->resize(index);
			for (boost::multi_array_types::size_type i=0; i < this->data_->shape()[0]; i++)
			{
				for (boost::multi_array_types::size_type j = 0; j < this->data_->shape()[1]; j++)
				{
					boost::array< boost::multi_array_types::size_type, 2 > index = {{ i, j }};
					(*this->data_)(index) = default_value;
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
			boost::multi_array_types::size_type size1 = std::stoul(tokens[0]);
			boost::multi_array_types::size_type size2 = std::stoul(tokens[1]);
			if (size1 <= 0 || size2 <= 0) {
				return -2;
			}
			this->initialize(size1, size2);

			// Read in the data rows
			std::string line;
			std::stringstream sstream;
			T cast_tmp;
			for (boost::multi_array_types::size_type i = 0; i < size1; i++) {
				if (file.eof()) {
					// We ran out of file before we should have.
					return -3;
				}
				std::getline(file, line);
				
				// Parse the line on single whitespace, then check for validity
				tokens.clear();
				boost::trim_right(line);
				tokens = string_split(line, " ");
				
				if (tokens.size() != size2) {
					// Incorrect number of columns in one of the rows
					return -4;
				}

				// Parse each of the tokens into a type T variable, and set it in the data matrix
				for (boost::multi_array_types::size_type j = 0; j < size2; j++) {
					sstream.clear();
					sstream.str(tokens[j]);
					sstream >> cast_tmp;
					this->set_datum(i,j,cast_tmp);
				}
			} 

			file.close();
			return 1;
		}  // read_file_ascii()

		int write_file_ascii(const std::string& path) {
			std::ofstream file;
			// Open the given file for writing. Set to truncate mode to blow away any existing data
			file.open(path, std::ios::out | std::ios::trunc);
			if (!file.good()) {
				return 0;
			}

			// Write the header line with the dimensions of the matrix
			file << this->data_->shape()[0] << " " << this->data_->shape()[1] << std::endl;

			// Write each row of data to a line
			for (boost::multi_array_types::size_type i = 0; i < this->data_->shape()[0]; i++) {
				for (boost::multi_array_types::size_type j = 0; j < this->data_->shape()[1]; j++) {
					file << this->get_datum(i, j) << " ";
				}
				file << std::endl;
			}

			return 1;
		}
	}; // class MatrixFile

} // namespace HeatFlow
#endif
