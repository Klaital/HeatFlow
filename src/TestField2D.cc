#include <iostream>
#include "Field2D.hpp"

typedef HeatFlow::Field<int> IntField;
using namespace std;


int main( )
{
    cout << "Creating int field with default constructor" << endl;
    IntField *iField = new IntField();
    
    int rows = iField->get_rows();
    int columns = iField->get_columns();
    cout << "Printing out the " << rows << "x" << columns << " Field..." << endl;
    iField->print(); 
}


