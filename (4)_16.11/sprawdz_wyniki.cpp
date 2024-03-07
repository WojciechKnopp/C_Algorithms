#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;


int main(){
    ifstream p1("wynik_count.txt");
    ifstream p2("wynik_quick.txt");
    if(!p1.good()){
        cout<<"błąd pliku p1"<<endl;
        return 0;
    }
    if(!p2.good()){
        cout<<"błąd pliku p2"<<endl;
        return 0;
    }
    string s1, s2;
    int i=0;
    while(!p1.eof()){
        p1 >> s1;
        p2 >> s2;
        if(s1.compare(s2)!=0)
            cout<<"NIE ok w linii " << i/2 <<" "<<s1<<" "<<s2<< endl;
        i++;
    }
    p1.close();
    p2.close();
    return 0;
}
