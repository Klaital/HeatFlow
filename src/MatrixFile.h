#ifndef HEATFLOW_MATRIXFILE_H_
#define HEATFLOW_MATRIXFILE_H_

template<class T>
class MatrixFile
{
private:
	boost::numeric::ublas::matrix<T> data;
	std::string path;

public:
	MatrixFile();
	~MatrixFile();

	inline std::string get_path() { return this->path; }
	inline void set_path(std::string &new_path) { this->path = new_path; }
	inline void set_data(boost::numeric::ublas::matrix<T> new_data) { this->new_data = data; }
};

#endif
