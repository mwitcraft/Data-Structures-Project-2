#include<iostream>
using namespace std;

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
    cout << newRow << endl;
}