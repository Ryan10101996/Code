#include <iostream>
using namespace std;

int divide(int a, int b);

int main()
{
    divide(5,0);
    catch(50)
    {
        cout<<"You suck"<<endl;
    }
}

int divide(int a, int b)
{
    try
    {
        if(b==0)
            throw 50;
        else
            int c=a/b;
    }

    catch(int x)
    {
        cout<<"Divide by zero"<<endl;
    }
}
