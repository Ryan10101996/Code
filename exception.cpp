#include <iostream>
using namespace std;

int main()
{
    try
    {
        int num1;
        cout <<"Enter a number: ";
        cin>>num1;
        int num2;
        cout<<"Enter a number to divide by: ";
        cin>>num2;

        if(num2==0)
            throw 99;

        cout<<num1<<" divided by "<<num2<<" is "<<num1/num2<<endl;

    }
    catch(int x)
    {
        cout<<"ERROR: CANNOT DIVIDE BY ZERO"<<endl;
    }

}
