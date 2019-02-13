#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
using namespace std;

int factorial(int a)
{
    int i;
    int total;
    total = 1;
    while(a!=0){
        total*=a;
        a-=1;}
    cout<<total<<endl;
}


int main()
{   int i;
    srand(time(0));
    for(i=0; i<10;i++)
        if((1+ (rand()%100)<50))
            cout<<"You lose"<<endl;
        else
            cout<<"You Win!"<<endl;
factorial(5);
factorial(6);
factorial(8);
factorial(4);
}


