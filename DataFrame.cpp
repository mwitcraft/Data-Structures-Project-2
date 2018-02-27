#include <iostream>
using namespace std;


//********************************************************************//

template <class DT>
class DataFrame{
protected:
    //Array of pointers to DT object
    DT** dataRows;
    char** colNames;
    int noRows, noCols;
public:
    DataFrame();
    DataFrame(int numberOfColumns);
    DataFrame(int numberOfRows, int numberOfColumns);
    void display();
    void display(int n);//Display first n records
    void setColName(int col, const char* name);
    DT* operator[](int i); //get the ith row
    int getNumberColumns();    
    char** getColNames();
    int getNumberRows();
    DataFrame<DT>* getRows(int* rows, int rLen);
    void addRow(DT& newRow);//Add new row at end
    void removeRow(int i);//Remove the ith row
    void insertRow(int position, DT*& newRow);
    ~DataFrame();
    //Write the ostream operator
    template<class T>
    friend ostream& operator<< (ostream& os, DataFrame<T>* df);
    //write the = operator for 10 extra points
};

template <class DT>
DataFrame<DT>::DataFrame(){}

template <class DT>
DataFrame<DT>::DataFrame(int numCols){
    noRows = 0;
    noCols = numCols;

    colNames = new char*[noCols];

    dataRows = new DT*[noRows];
}

template <class DT>
DataFrame<DT>::DataFrame(int numRows, int numCols){
    noRows = numRows;
    noCols = numCols;

    colNames = new char*[noCols];

    dataRows = new DT*[noRows]; 
}

template <class DT>
void DataFrame<DT>::display(){
    for(int i = 0; i < noCols; ++i){
        if(i != noCols - 1){
            cout << colNames[i] << ',';
        } else {
            cout << colNames[i] << '\n';
        }
    }

    for(int i = 0; i < noRows; ++i){
        cout << dataRows[i];
    }
    cout << endl;
}

template <class DT>
void DataFrame<DT>::display(int n){

}

template <class DT>
void DataFrame<DT>::setColName(int col, const char* name){
    colNames[col] = (char*)name;
}

template <class DT>
DT* DataFrame<DT>::operator[](int i){
    return dataRows[i];
}

template<class DT>
int DataFrame<DT>::getNumberColumns(){
    return noCols;
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
    DataFrame<DT>* df = new DataFrame<DT>(noCols);
    for(int i = 0; i < noCols; ++i){
        df->setColName(i, colNames[i]);
    }
    int row;
    for(int i = 0; i < rLen; ++i){
        row = rows[i];
        DT realRow = DT(*dataRows[row]);
        df->addRow(realRow);
    }
    return df;
}

template <class DT>
void DataFrame<DT>::addRow(DT& newRow){
    DT** newRows;
    newRows = new DT*[noRows + 1];
    for(int i = 0; i < noRows; ++i){
        newRows[i] = dataRows[i];
    }

    DT* addr = &newRow;

    newRows[noRows] = addr;
    ++noRows;
    dataRows = newRows;
}

template <class DT>
void DataFrame<DT>::removeRow(int position){
    cout << "position: " << position << endl;
    DT** newRows;
    newRows = new DT*[noRows - 1];
    for(int i = 0; i < noRows; ++i){
        if(i < position){
            newRows[i] = dataRows[i];
        }

        if(i == position){
            cout << "Deleting: " << dataRows[i] << endl;
        }

        if(i > position){
            newRows[i - 1] = dataRows[i];
        }
    }

    --noRows;
    dataRows = newRows;
}

template <class DT>
void DataFrame<DT>::insertRow(int position, DT*& newRow){
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

    ++noRows;
    dataRows = newRows;
}

template <class DT>
DataFrame<DT>::~DataFrame(){

}

template <class T>
ostream& operator<< (ostream& os, DataFrame<T>* df){
    for(int i = 0; i < df->noCols; ++i){
        if(i != df->noCols - 1){
            os << df->colNames[i] << ',';
        } else {
            os << df->colNames[i] << '\n';
        }
    }

    for(int i = 0; i < df->noRows; ++i){
        os << df->dataRows[i];
    }
    os << endl;

    return os;
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
    ~RowObject();
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

ostream& operator<< (ostream& os, const RowObject* ro){
    os << ro->ID << ',' << ro->year << ',' << ro->causeName << ',' << ro->state << ',' << ro->numberOfDeaths << ',' << ro->averageAge << '\n';
    return os;
}

RowObject::~RowObject(){

}

/*

int main(){
    RowObject* newRow;
    newRow = new RowObject(6, 2018, "Cancer", "Oklahoma", 200, 58.2);
    cout << newRow << endl;
}
*/



//******************************************************************************************//


/*
int main(){
    RowObject* newRow;
    newRow = new RowObject(1, 1, "1", "1", 1, 1);
    RowObject* row2;
    row2 = new RowObject(2, 2, "2", "2", 2, 2);
    RowObject* row3;
    row3 = new RowObject(3, 3, "3", "3", 3, 3);
    RowObject* row4;
    row4 = new RowObject(4, 4, "4", "4", 4, 4);
    RowObject* row5;
    row5 = new RowObject(5, 5, "5", "5", 5, 5);

    DataFrame<RowObject>* df;
    df = new DataFrame<RowObject>(0, 2);

    df->addRow(newRow);
    df->addRow(row2);
    df->addRow(row3);
    df->addRow(row4);
    df->addRow(row5);    
    df->display();

    cout << "------------------------" << endl;
    cout << endl;

    RowObject* insertedRow;
    insertedRow = new RowObject(99, 99, "99", "99", 99, 99);


    df->insertRow(5, insertedRow);
    cout << endl;
    df->display();

}
*/

int main(){

//******************************************************************//
//Here column names are set    
    int numRows;
    int numCols = 5;

    DataFrame<RowObject>* DBT;

    int selectR[10];

    for(int i = 0; i < 10; ++i){
        selectR[i] = i + 2;
    }

    cin >> numRows;
    DBT = new DataFrame<RowObject>(numCols);

    for(int i = 0; i < numCols; ++i){
        char* name = new char[100];
        char c;
        cin >> c;
        int j = 0;
        while(c != ',' && c != '\n'){
            name[j] = c;
            cin.get(c);
            ++j;
        }
        name[j] = '\0';
        DBT->setColName(i, name);
    }

//*************************************************************************/
//Row objects are created

    char** lines = new char*[numRows];
    for(int i = 0; i < numRows; ++i){
        char c;
        cin >> c;

        int j = 0;
        char* line = new char[1000];
        while(c != '\n'){
            line[j] = c;
            cin.get(c);
            ++j;
        }
        line[j] = '\0';
        lines[i] = line;
    }

    for(int i = 0; i < numRows; ++i){
        int ID;
        int year;
        char* causeName;
        char* state;
        int numberOfDeaths;
        float averageAge;

        char* row = lines[i];

        int rowIndex = 0;
        int column = 0;
        char* val = new char[100];
        int valIndex = 0;
        while(row[rowIndex] != '\0'){
            if(row[rowIndex] == ','){
                switch(column){
                    case(0):
                        year = atoi(val);
                        break;
                    case(1):
                        causeName = val;
                        break;
                    case(2):
                        state = val;
                        break;
                    case(3):
                        numberOfDeaths = atoi(val);
                        break;
                }
                   val = new char[100];
                    valIndex = 0;
                    ++column;
            } else {
                val[valIndex] = row[rowIndex];
                ++ valIndex;
            }

            ++rowIndex;

        }

        if(column == 4){
            averageAge = atof(val);
        }

        RowObject* newRow = new RowObject(i + 1, year, causeName, state, numberOfDeaths, averageAge);

        // cout << newRow << endl;

        DBT->insertRow(i, newRow);
    }

    // DBT->display();

//*************************************************************************/

    (*DBT).setColName(4, "Number Deaths");
    (*DBT).setColName(2, "Cause Name");
    cout << DBT;
    

    DataFrame<RowObject>* tempRows = (*DBT).getRows(selectR, 10);
    (*tempRows).display();

// Testing addRow, constructor for RowObject and getNumberRows method
RowObject* newRow;
newRow = new RowObject((*DBT).getNumberRows(),2018,"Cancer","Oklahoma",200, 58.2);
(*DBT).addRow(*newRow);
// Testing destructor for RowObject
delete newRow;
newRow = new RowObject((*DBT).getNumberRows(),2018,"Opiod","Texas",2000, 32.4);
(*DBT).addRow(*newRow);
delete newRow;
cout << (*DBT)[(*DBT).getNumberRows()-2];
cout << (*DBT)[(*DBT).getNumberRows()-1];
}