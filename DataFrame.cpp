#include <iostream>
using namespace std;

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
    void addRow(DT*& newRow);//Add new row at end
    void removeRow(int i);//Remove the ith row
    void insertRow(int position, DT& newRow);
    ~DataFrame();
    //Write the ostream operator
    //write the = operator for 10 extra points
};

template <class DT>
DataFrame<DT>::DataFrame(){}

template <class DT>
DataFrame<DT>::DataFrame(int numRows, int numCols){
    noRows = numRows;
    noCols = numCols;

    colNames = new char*[noCols];

    dataRows = new DT*[noRows]; 
}

template <class DT>
void DataFrame<DT>::display(){
    for(int i = 0; i < noRows; ++i){
        cout << dataRows[i];
    }
    cout << "DONE" << endl;
}

template <class DT>
void DataFrame<DT>::display(int n){

}

template <class DT>
void DataFrame<DT>::setColName(int col, const char* name){
    colNames[col] = (char*)name;
}

template <class DT>
DT& DataFrame<DT>::operator[](int i){
    return dataRows[i];
}

template <class DT>
char** DataFrame<DT>::getColNames(){
    return colNames;
}

template <class DT>
int DataFrame<DT>::getNumberRows(){
    return noRows;
}

template <class DT>
DataFrame<DT>* DataFrame<DT>::getRows(int* rows, int rLen){
    DataFrame<DT>* df;
    int row;
    for(int i = 0; i < rLen; ++i){
        row = rows[i];
        df.addRow(dataRows[row]);
    }
    return df;
}

template <class DT>
void DataFrame<DT>::addRow(DT*& newRow){
    //cout << newRow << endl;
    DT** newRows;
    newRows = new DT*[noRows + 1];
    for(int i = 0; i < noRows; ++i){
        newRows[i] = dataRows[i];
    }

    newRows[noRows] = newRow;
    ++noRows;
    dataRows = newRows;
}

template <class DT>
void DataFrame<DT>::removeRow(int i){
    DT** newRows;
    newRows = new DT*[noRows - 1];
    for(int j = 0; j < noRows; ++j){
        if(j != i){
            newRows[j] = dataRows[j];
        }
    }

    dataRows = newRows;
}

template <class DT>
void DataFrame<DT>::insertRow(int position, DT& newRow){
    DT** newRows;
    newRows = new DT*[noRows + 1];
    for(int i = 0; i < noRows + 1; ++i){
        if(i < position){
            newRows[i] = dataRows[i];
        }

        if(i == position){
            newRows[i] = newRow;
        }

        if(i > position){
            newRows[i] = dataRows[i - 1];
        }
    }

    dataRows = newRows;
}

template <class DT>
DataFrame<DT>::~DataFrame(){

}







//******************************************************************************************//

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
    friend ostream& operator<< (ostream& os, const RowObject* ro);
    //Write overloaded = operator for 10 extra points
    //Write destructor
};

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

/*

int main(){
    RowObject* newRow;
    newRow = new RowObject(6, 2018, "Cancer", "Oklahoma", 200, 58.2);
    cout << newRow << endl;
}
*/



//******************************************************************************************//


int main(){
    RowObject* newRow;
    newRow = new RowObject(6, 2018, "Cancer", "Oklahoma", 200, 58.2);


    DataFrame<RowObject>* df;
    df = new DataFrame<RowObject>(0, 2);

    df->addRow(newRow);
    df->display();

}