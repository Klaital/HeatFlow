#pragma once
template <class T>
class DataMatrix
{
private:
	boost::multi_array<T, 2> *data_;

public:
	DataMatrix() { 
		this->data_ = 0;
	}
	~DataMatrix() { delete this->data_; }

	// Accessors
	//boost::multi_array::size_type get_size1() { return this->data_->shape()[0]; }
	//boost::multi_array::size_type get_size2() { return this->data_->shape()[1]; }
//	boost::multi_array<T, 2>::size_type* get_matrix_size() { return this->data_->shape(); }
	boost::multi_array<T, 2>* get_data() { return this->data_; }
	
	void set_data(const boost::multi_array<T,2>& new_data) {
		// Resize the data array
		delete this->data_;
		this->data_ = new boost::multi_array<T, 2>(new_data.shape());
		
		// Copy in the new data
		for (boost::multi_array<T,2>::size_type i = 0; i < this->data_->shape()[0]; i++) {
			for (boost::multi_array<T, 2>::size_type j = 0; j < this->data_->shape()[1]; j++) {
				boost::array< boost::multi_array<T, 2>::index, 2 > idx = { { i,j } };
				(*this->data_)(idx) = new_data(idx);
			}
		}
	}

	// Serialization
	int save(const std::string& path) {
		std::ofstream file;
		// Open the given file for writing. Set to truncate mode to blow away any existing data
		file.open(path, std::ios::out | std::ios::trunc);
		if (!file.good()) {
			return 0;
		}

		// Write the header line with the dimensions of the matrix
		file << this->data_->shape()[0] << " " << this->data_->shape()[1] << std::endl;

		// Write each row of data to a line
		for (boost::multi_array<T,2>::size_type i = 0; i < this->data_->shape()[0]; i++) {
			for (boost::multi_array<T,2>::size_type j = 0; j < this->data_->shape()[1]; j++) {
				boost::array< boost::multi_array<T, 2>::index, 2 > idx = { { i,j } };
				file << (*this->data_)(idx) << " ";
			}
			
			file << std::endl;
		}

		return 1;
	}
};

