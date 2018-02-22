#include <iostream>
using namespace std;

int main(){
    char** colNames;
    int noCols;

    //Second line: strings separated by a comma (c of them); representing column names
    //Third line and more: Each column values is separated by a COMMA and the last one by end of line
    //Read the input; store the row number for each row read in ID

    int size;
    cin >> size;

    noCols = 5;
    
    for(int i = 0; i < noCols; ++i){
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

        cout << name << endl;
    }
}