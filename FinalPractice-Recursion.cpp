#include <iostream>
using namespace std;

int power(int,int);
int factorial(int);
void printing(int);

int main(){
    cout<<power(2,3)<<endl;
    cout<<factorial(5)<<endl;
    printing(3);
}

int power(int a, int b){
    if (b == 1){
        return a;
    }
    else{
        return a*(power(a,--b));
    }
}

int factorial(int a){
    if (a == 1){
        return a;
    }
    else{
        return a*(factorial(a-1));
    }
}

void printing(int a){
    if (a == 1){
        cout << "The number is: "<<a<<endl;
    }else{
        cout<< "The number is: "<<a<<endl;
        printing(a-1);
    }

}





