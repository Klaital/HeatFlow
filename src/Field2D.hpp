#ifndef HEATFLOW_FIELD2D_H_
#define HEATFLOW_FIELD2D_H_

#include <iostream>
#include <string>
#include <stdio.h>

using namespace std;
namespace HeatFlow {

template <typename T> class Field
{
private:
    T ** data; // 2-d array for the field data
    int size[2]; // the rows, columns in the field
    
public:     // Constructors & destructor
    
    // Default constructor. Creates a field with NULL data field
    Field();
    
    // Construct a field with the specified dimensions
    Field(int rows, int columns);
    
    // construct a field with the specified dimensions
    Field(int size[2]);
    
    // Destroy the field
    ~Field();
    
private:    // Internal Utility functions
    
    // Allocate memory for the data array with the dimensions stored in this object
    void init_data();

public:     // Accessors
    
    // Resize the data array to the specified dimensions
    void resize(int rows, int columns);
    void resize(int size[2]);
    
    // Retrieve the size of the Field
    inline int get_rows() { return this->size[0]; }
    inline int get_columns() { return this->size[1]; }
    
    // Retrieve a datum from the field
    T get(int x, int y);
    T get(int coord[2]);
    
    // Set a value into the field
    void set(T value, int x, int y);
    void set(T value, int coord[2]);
    
public:     // I/O Methods
    
    // Display the Field on the console
    void print();
    
    // Write the Field out to a binary file
    void fprint_binary(string filename, int overwrite);
    // Write the Field out to a binary file. Defaults to overwrite=true
    void fprint_binary(string filename);
    
    // Read the Field in from a binary file.
    int fscan_binary(string filename);
    
};
}

#endif // HEATFLOW_FIELD2D_H_

