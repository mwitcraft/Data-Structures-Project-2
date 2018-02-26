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
    void insertRow(int position, DT*& newRow);
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
        cout << dataRows[i] << endl;
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
    DBT = new DataFrame<RowObject>(numRows, numCols);

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

    cout << DBT->getNumberRows() << endl;
    cout << numCols << endl;

    char** names = new char*[numRows];

/*
    for(int i = 0; i < numRows; ++i){
        char c;
        cin >> c;

        int year;
        char* causeName;
        char* state;
        int numberOfDeaths;
        float averageAge;

*/

        // char* name = new char[100];
        //int j = 0;

/*
        while(c != '\n'){
            name[j] = c;
            cin.get(c);
            ++j;
        }
        name[j] = '\0';
*/
/*
        char** names = new char*[numRows];

        for(int i = 0; i < numRows * numCols; ++i){
            cout << "i: " << i << endl;
            char* val = new char[100];
            int j = 0;
            
            while(c != ',' && c != '\n' && !cin.eof()){
                // cout << "C: " << c << endl;
                val[j] = c;
                cin.get(c);
                ++j;
            }
            cin >> c;
            val[j] = '\0';
            cout << "val: " << val << endl;
        }

        for(int i = 0; i < numRows; ++i){
            cout << names[i] << endl;
        }


        // names[i] = name;
    }
    */

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
        line[j] = ',';
        line[j + 1] = '\0';
        lines[i] = line;
    }

    // for(int i = 0; i < numRows; ++i){
    //     cout << "ID: " << i << " Row: " << lines[i] << endl;
    // }

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
                        cout << "Year: "<< val << endl;
                        // val = new char[100];
                        // valIndex = 0;
                        // ++column;
                        break;
                    case(1):
                        cout << "Cause: " << val << endl;
                        // val = new char[100];
                        // valIndex = 0;
                        // ++column;
                        break;
                    case(2):
                        cout << "State: " << val << endl;
                        // val = new char[100];
                        // valIndex = 0;
                        // ++column;
                        break;
                    case(3):
                        cout << "Deaths: " << val << endl;
                        // val = new char[100];
                        // valIndex = 0;
                        // ++column;
                        break;
                    case(4):
                        cout << "Age: " << val << endl;
                        // val = new char[100];
                        // valIndex = 0;
                        // ++column;
                        cout << endl;
                        break;
                }

                        val = new char[100];
                        valIndex = 0;
                        ++column;
            } else {
                // switch(column){
                //     case(0):
                //         val[rowIndex] = row[rowIndex];
                //         break;
                // }
                val[valIndex] = row[rowIndex];
                ++ valIndex;
            }

            ++rowIndex;

        }
    }







}