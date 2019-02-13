ga#include <iostream>
using namespace std;

int main(){
    int a=2;
    int b=0;
    double result;

    try{
        if(b==0){
            throw "hey";
        }
        result = a/b;       //  If b = 0, and a/b; it will throw an error.
                            // That's why its in the Try block
    }catch(int x){
        cout << "ERROR"<<x<<endl;
        result =0;
    }catch(...){
        cout << "General Error"<<endl;
        result =0;
    }

    cout <<"The Result is: "<< result<<endl;
}
