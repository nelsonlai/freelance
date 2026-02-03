#include <iostream>
#include <string>
#include <typeinfo>
using namespace std;
int main() {
    
    int x = 47385;
    cout<<sizeof(x)<<endl;
    cout << "Type of x : " << typeid(x).name() << endl;
    cout<<"Size of int "<<sizeof(int)<<endl;

    const char* greeting = "Hello, world!";;
    cout << "Size of *greeting "<< sizeof(*greeting)<<endl;
    cout << "Size of greeting "<< sizeof(greeting)<<endl;
    cout << "Type of greeting : " << typeid(greeting).name() << endl;
    cout << "Size of char "<<sizeof(char)<<endl;
    return 0;
}