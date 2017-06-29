#pragma once
#define temperature_t double

class ProjectConfig
{
public:
	// Constructors
	ProjectConfig();
	ProjectConfig(const std::string& path);
	~ProjectConfig();

	// Accessors
	size_t* get_matrix_size();
	temperature_t* get_initial_temperatures();
	
	std::string get_title();
	void set_title(const std::string& new_title);
private:
	size_t matrix_size[2];
	temperature_t* initial_temperatures;
	std::string title;
};

