#include <iostream>
using namespace std;

int main(){
    int i;
    char x;

    while(!cin.eof()){
        x = cin.get();
        if(x == '\n'){
            ++i;
        }
    }

    cout << "i: " << i << endl;
}