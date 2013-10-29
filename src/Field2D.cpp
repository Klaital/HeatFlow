#include "Field2D.hpp"

//
// CONSTRUCTORS & DESTRUCTOR
//

// Default constructor. Creates a field with NULL data field
template <typename T> Field<T>::Field()
{
    this->size[0] = this->size[1] = 0;
}

// Construct a field with the specified dimensions
template <typename T> Field<T>::Field(int rows, int columns)
{
    this->size[0] = rows;
    this->size[1] = columns;
    init_data();
}

// Construct a field with the specified dimensions
template <typename T> Field<T>::Field(int size[2])
{
    this->size = new int[2];
    for(int i=0; i < 2; i++) 
        this->size[i] = size[i];
    init_data();
}

// Destroy the field
template <typename T> Field<T>::~Field()
{
    if(this->data)
    {
        // delete each row of data
        for(int i=0; i < size[0]; i++)
        {
            if(this->data[i])
            {
                delete this->data[i];
            }
        }
        
        // delete the set of row pointers
        delete this->data;
    }
}

//
// INTERNAL UTILITY METHODS
//

// Allocate memory for the data array with the dimensions stored in this object
template <typename T> void Field<T>::init_data()
{
    // ensure valid dimensions
    if(this->size[0] <= 0 || this->size[1] <= 0)
        return;
    
    // destroy the old array if it had been previously allocated
    if(this->data)
    {
        for(int x=0; x < this->size[0]; x++)
        {
            delete this->data[x];
        }
        delete this->data;
    }
    
    // allocate the array of row pointers    
    this->dimensions = new T*[this->size[0]];
    
    // allocate each row
    for(int x=0; x < this->size[0]; x++)
    {
        this->dimensions[x] = new T[this->size[1]];
    }
}

//
// ACCESSORS
//

template <typename T> void Field<T>::resize(int rows, int columns)
{
    // TODO: clear old data
    this->size[0] = rows;
    this->size[1] = columns;
    init_data();
}

// Resize the array with the given new dimensions
template <typename T> void Field<T>::resize(int size[2])
{
    // TODO: clear old data
    this->size[0] = size[0];
    this->size[1] = size[1];
    init_data();
}


// Retrieve a datum from the field
template <typename T> T Field<T>::get(int x, int y)
{
    if(this->data && x > 0 && x < this->size[0] && y > 0 && y < this->size[1])
        return this->data[x][y];
    else
        return NULL;
}

// Retrieve a datum from the field
template <typename T> T Field<T>::get(int coord[2])
{
    if(this->data && coord[0] > 0 && coord[0] < this->size[0] && coord[1] > 0 && coord[1] < this->size[1])
        return this->data[coord[0]][coord[1]];
    else
        return NULL;
}

// Set a value into the field
template <typename T> void Field<T>::set(T value, int x, int y)
{
    if(this->data && x > 0 && x < this->size[0] && y > 0 && y < this->size[1])
        this->data[x][y] = value;
}

// Set a value into the field
template <typename T> void Field<T>::set(T value, int coord[2])
{
    if(this->data && coord[0] > 0 && coord[0] < this->size[0] && coord[1] > 0 && coord[1] < this->size[1])
        this->data[coord[0]][coord[1]] = value;
}

//
// I/O Methods
//

// Display the Field on the console
template <typename T> void Field<T>::print()
{
    if(! this->data)
        return;
        
    for(int x=0; x < this->size[0]; x++)
    {
        for(int y=0; y < this->size[1]; y++)
        {
            cout << this->data[x][y];
            if(y < this->size[1] - 1)
                cout << "\t";
        }
        
        cout << endl;
    }
}

// Write the Field out to a binary file
template <typename T> void Field<T>::fprint_binary(string filename, int overwrite)
{
    // if there is no data in the array, just abort
    if(! this->data)
        return;
        


    FILE *fp;
    
    // test if the file is present by attempting to open it for reading
    fp = fopen(filename.c_str(), "r");
    
    if(overwrite)
    {
        // close and delete, then reopen the file for writing
        fclose(fp);
        remove(filename.c_str());
        fopen(filename.c_str(), "w");
    }
    else
    {
        // close and reopen for writing
        fclose(fp);
        fopen(filename.c_str(), "w");
    }
    
    
    // first write out the two dimensions of the data array
    fwrite(size, sizeof(int), 2, fp);
    
    // now write out all of the data
    for(int x=0; x < this->size[0]; x++)
    {
        fwrite(this->data[x], sizeof(T), size[1], fp);
    }
    
    // close the file
    fclose(fp);
}

// Write the Field out to a binary file. Defaults to overwrite=true
template <typename T> void Field<T>::fprint_binary(string filename)
{
    return fprint_binary(filename, true);
}

// Read the Field in from a binary file.
template <typename T> int Field<T>::fscan_binary(string filename)
{
    // delete any existing data in the field
    if(this->data)
    {
        for(int x=0; x < this->size[0]; x++)
        {
            delete this->data[x];
        }
        delete this->data;
    }
    
    // open the file
    FILE *fp;
    if(! fopen(filename.c_str(), "w"))
        return 0;
    
    // read in the two size integers
    fread(size, sizeof(int), 2, fp);
    // TODO: add error trapping here to make sure the values were successfully read (and that the values make sense)
    
    // ensure the data array is correctly sized
    init_data();
    
    // read in the data
    for(int x=0; x < this->size[0]; x++)
    {
        fread(this->data[x], sizeof(T), this->size[1], fp);
         // TODO: add error trapping here to make sure the values were successfully read 
    }
    
    // close the file
    fclose(fp);
    
    // Success!
    return 1;
}

