#include <iostream>
using namespace std;



void outputnumbers(int a)
    {
        if(a==1)
           {
            cout<<a<<endl;
           }
        else
            {cout<<a<<endl;
            outputnumbers(--a);
            }
    }

int main()
{

    outputnumbers(5);
}
