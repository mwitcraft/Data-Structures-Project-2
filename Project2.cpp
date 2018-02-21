#include <iostream>
using namespace std;

//Data from leading causes of death in the USA
class RowObject {
protected:
    int ID;
    int year;
    char* causeName;
    char* state;
    int numberOfDeaths;
    float averageAge;

public:
    RowObject();
    RowObject(int rid, int y, const char* cn, const char* s, int n, float age);
    //Write ostream operator
    friend ostream& operator << (ostream& os, const RowObject* ro);
    //Write overloaded = operator for 10 extra points
    //Write destructor
};

template <class DT>
class DataFrame{
protected:
    //Array of pointers to DT object
    DT** dataRows;
    char** colNames;
    int noRows, noCols;
public:
    DataFrame();
    DataFrame(int numberOfRows, int numberOfColumns);
    void display();
    void display(int n);//Display first n records
    void setColName(int col, const char* name);
    DT& operator[](int i); //get the ith row
    char** getColNames();
    int getNumberRows();
    DataFrame<DT>* getRows(int* rows, int rLen);
    void addRow(DT& newRow);//Add new row at end
    void removeRow(int i);//Remove the ith row
    void insertRow(int position, DT& newRow);
    ~DataFrame();
    //Write the ostream operator
    //write the = operator for 10 extra points
};

//Default constructor
RowObject::RowObject(){}

RowObject::RowObject(int rid, int y, const char* cn, const char* s, int n, float age){
    ID = rid;
    year = y;
    causeName = (char*)cn;
    state = (char*)s;
    numberOfDeaths = n;
    averageAge = age;
}

ostream& operator<<(ostream& os, const RowObject* ro){
    os << ro->year << ',' << ro->causeName << ',' << ro->state << ',' << ro->numberOfDeaths << ',' << ro->averageAge;
    return os;
}

int main(){
    RowObject* newRow;
    newRow = new RowObject(6, 2018, "Cancer", "Oklahoma", 200, 58.2);
    cout << newRow;
}