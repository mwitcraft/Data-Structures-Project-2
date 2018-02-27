#include <iostream>
using namespace std;

//DataFrame object
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
    void addRow(DT*& newRow);//Add new row at end
    void removeRow(int i);//Remove the ith row
    void insertRow(int position, DT*& newRow);
    ~DataFrame();
    //Write the ostream operator
    template<class T>
    friend ostream& operator<< (ostream& os, DataFrame<T>* df); //Operator is 'friend' so is has access to the protected variables
    //write the = operator for 10 extra points
};

//Default constructor
template <class DT>
DataFrame<DT>::DataFrame(){}

//Added this constructor with only noCols being set
//because the number of rows is incremented or decremented from
//add or insert row
template <class DT>
DataFrame<DT>::DataFrame(int numCols){
    noRows = 0;
    noCols = numCols;

    //Initializes the array of arrays
    colNames = new char*[noCols];

    dataRows = new DT*[noRows];
}

//Constructor that sets both the noRows and noCols
template <class DT>
DataFrame<DT>::DataFrame(int numRows, int numCols){
    noRows = numRows;
    noCols = numCols;

    colNames = new char*[noCols];

    dataRows = new DT*[noRows]; 
}

//Display function
template <class DT>
void DataFrame<DT>::display(){
    //Prints out the column names at the top,
    //seperating with a ',' then a new line at last column name
    for(int i = 0; i < noCols; ++i){
        if(i != noCols - 1){
            cout << colNames[i] << ',';
        } else {
            cout << colNames[i] << '\n';
        }
    }

    //Prints out the rows one by one
    for(int i = 0; i < noRows; ++i){
        cout << dataRows[i];
    }
    cout << endl;
}

//Same thing as display method above but only prints out the first n rows
template <class DT>
void DataFrame<DT>::display(int n){
    for(int i = 0; i < noCols; ++i){
        if(i != noCols -1){
            cout << colNames[i] << ',';
        } else {
            cout << colNames[i] << '\n';
        }
    }
    for(int i = 0; i < n; ++i){
        cout << dataRows[i];
    }
    cout << endl;
}

//Sets name of column at col to name
template <class DT>
void DataFrame<DT>::setColName(int col, const char* name){
    colNames[col] = (char*)name;
}

//Returns the RowObject at dataRows[i]
template <class DT>
DT* DataFrame<DT>::operator[](int i){
    return dataRows[i];
}

//Returns number of columns
template<class DT>
int DataFrame<DT>::getNumberColumns(){
    return noCols;
}

//Returns colNames
template <class DT>
char** DataFrame<DT>::getColNames(){
    return colNames;
}

//Returns the number of rows
template <class DT>
int DataFrame<DT>::getNumberRows(){
    return noRows;
}

//Returns a new DataFrame pointer that contains only the rows specified
template <class DT>
DataFrame<DT>* DataFrame<DT>::getRows(int* rows, int rLen){
    //Number of columns and column names remain the same
    DataFrame<DT>* df = new DataFrame<DT>(noCols);
    for(int i = 0; i < noCols; ++i){
        df->setColName(i, colNames[i]);
    }

    //Adds rows specified in rows to new DataFrame pointer
    int row;
    for(int i = 0; i < rLen; ++i){
        row = rows[i];
        df->addRow(dataRows[row]);
    }
    return df;
}

//Adds a row to the end of the DataFrame 
template <class DT>
void DataFrame<DT>::addRow(DT*& newRow){
    DT** newRows;
    //Updated DataFrame will contain one more row
    newRows = new DT*[noRows + 1];
    //Previous rows stay the same
    for(int i = 0; i < noRows; ++i){
        newRows[i] = dataRows[i];
    }
    //New row is added at end
    newRows[noRows] = newRow;
    //noRows is increments because a new RowObject was added
    ++noRows;
    dataRows = newRows;
}

//Removes a row from the DataFrame at a certain row
template <class DT>
void DataFrame<DT>::removeRow(int position){
    DT** newRows;
    //Updated DataFrame will contain one less row
    newRows = new DT*[noRows - 1];
    for(int i = 0; i < noRows; ++i){
        //Before removed row everything is at the same index 
        if(i < position){
            newRows[i] = dataRows[i];
        }
        //After remove row, other rows are at index - 1 in the updated DataFrame
        if(i > position){
            newRows[i - 1] = dataRows[i];
        }
        //At i == position, the row is not added
    }

    //noRows decrements because a row was removed
    --noRows;
    dataRows = newRows;
}

//Inserts newRow at position
template <class DT>
void DataFrame<DT>::insertRow(int position, DT*& newRow){
    DT** newRows;
    //Adding a row so updated DataFrame will contain one more row
    newRows = new DT*[noRows + 1];
    for(int i = 0; i < noRows + 1; ++i){
        //Before inserting row everything remains at the same index
        if(i < position){
            newRows[i] = dataRows[i];
        }
        //Row is inserted at position
        if(i == position){
            newRows[i] = newRow;
        }
        //After insertion, rows from old DataFrame are placed at original index + 1
        //in the updated DataFrame to accomodate new row
        if(i > position){
            newRows[i] = dataRows[i - 1];
        }
    }

    //noRows increments because a new row is added
    ++noRows;
    dataRows = newRows;
}

//Destructor
template <class DT>
DataFrame<DT>::~DataFrame(){
    //Deletes pointers to arrays
    delete[] dataRows;
    delete[] colNames;
}

//Ostream operator for <<
//same as display method
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

//RowObject object
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
    friend ostream& operator<< (ostream& os, const RowObject* ro); //Operator is 'friend' so it has access to the protected variables
    //Write overloaded = operator for 10 extra points
    //Write destructor
    ~RowObject();
};

//Default constructor
RowObject::RowObject(){}

//Constructor
RowObject::RowObject(int rid, int y, const char* cn, const char* s, int n, float age){
    ID = rid;
    year = y;
    causeName = (char*)cn;
    state = (char*)s;
    numberOfDeaths = n;
    averageAge = age;
}

//Operator << that prints out the RowObject in the correct format.
ostream& operator<< (ostream& os, const RowObject* ro){
    os << ro->ID << ',' << ro->year << ',' << ro->causeName << ',' << ro->state << ',' << ro->numberOfDeaths << ',' << ro->averageAge << '\n';
    return os;
}

//Destructor
RowObject::~RowObject(){
    //No pointers to arrays to delete
}

int main(){

    int numRows;
    //numCols is hard coded because the number of columns remains the same
    int numCols = 5;

    DataFrame<RowObject>* DBT;

    int selectR[10];

    for(int i = 0; i < 10; ++i){
        selectR[i] = i + 2;
    }

    //Number of rows is read in from the file
    cin >> numRows;
    //Constructs DataFrame with numCols
    DBT = new DataFrame<RowObject>(numCols);

    //Reads in column names from file
    for(int i = 0; i < numCols; ++i){
        //Column name lengths are unknows so set to large number just to be safe
        char* name = new char[100];
        char c;
        cin >> c;
        int j = 0;
        //Reads each character that is not a ',' or a '\n' and stores it in name
        while(c != ',' && c != '\n'){
            name[j] = c;
            cin.get(c);
            ++j;
        }
        //Terminates name when a ',' or '\n' is read
        name[j] = '\0';
        //Sets DataFrame column name using name
        DBT->setColName(i, name);
    }

    //Row objects are created
    char** lines = new char*[numRows];
    //Reads each line and stores it in lines
    for(int i = 0; i < numRows; ++i){
        char c;
        cin >> c;

        int j = 0;
        //Line length is unknown so sets to large number to be safe
        char* line = new char[1000];
        //Reads each character until '\n' and stores it in line
        while(c != '\n'){
            line[j] = c;
            cin.get(c);
            ++j;
        }
        //Terminates line when a '\n' is read
        line[j] = '\0';
        //Adds line to lines
        lines[i] = line;
    }

    //Create RowObjects from lines and add them to the DataFrame
    for(int i = 0; i < numRows; ++i){
        int ID;
        int year;
        char* causeName;
        char* state;
        int numberOfDeaths;
        float averageAge;

        //Selects first entry in lines (the first row)
        char* row = lines[i];

        int rowIndex = 0;
        int column = 0;
        char* val = new char[100];
        int valIndex = 0;
        //Loops while row is not at the end
        while(row[rowIndex] != '\0'){
            //When ',' is read, sets certain RowObject variable base on value of column
            if(row[rowIndex] == ','){
                switch(column){
                    case(0):
                        //Converts char* to int
                        year = atoi(val);
                        break;
                    case(1):
                        causeName = val;
                        break;
                    case(2):
                        state = val;
                        break;
                    case(3):
                        //Converts char* to int
                        numberOfDeaths = atoi(val);
                        break;
                }
                   val = new char[100];
                    valIndex = 0;
                    ++column;
            } else {
                //',' is not read and character read gets added to val
                val[valIndex] = row[rowIndex];
                ++ valIndex;
            }

            ++rowIndex;

        }

        //Sets RowObject value based on column
        if(column == 4){
            //Converts char* to float
            averageAge = atof(val);
        }

        //Constructs RowObject using values obtained
        RowObject* newRow = new RowObject(i + 1, year, causeName, state, numberOfDeaths, averageAge);

        //Inserts row into DataFrame
        DBT->insertRow(i, newRow);
    }

    //Test cases run
    (*DBT).setColName(4, "Number Deaths");
    (*DBT).setColName(2, "Cause Name");
    cout << DBT;
    

    DataFrame<RowObject>* tempRows = (*DBT).getRows(selectR, 10);
    (*tempRows).display();

    cout << (*DBT)[4];
    cout << (*DBT)[5];
    cout << (*DBT)[10];

    RowObject* newRow;
    newRow = new RowObject((*DBT).getNumberRows(),2018,"Cancer","Oklahoma",200, 58.2);
    DBT->addRow(newRow);

    newRow = new RowObject((*DBT).getNumberRows(),2018,"Opiod","Texas",2000, 32.4);
    DBT->addRow(newRow);

    cout << (*DBT)[(*DBT).getNumberRows()-2];
    cout << (*DBT)[(*DBT).getNumberRows()-1];

    newRow = new RowObject((*DBT).getNumberRows(),2016,"Cancer","Texas",500, 72.1);
    (*DBT).insertRow(1, newRow);

    newRow = new RowObject((*DBT).getNumberRows(),2016,"Stroke","Oklahoma",400, 68.1);
    (*DBT).insertRow(4, newRow);

    (*DBT).display(10);

    (*DBT).removeRow(1);
    (*DBT).removeRow(3);

    (*DBT).display(10);
}