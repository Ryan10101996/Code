#include <iostream>
#include <string>
using namespace std;

int main()
{
    float a;
    string n="";
    string temp;

    cout<<"Enter a number: ";
    cin>>a;
    while(a>=1)
    {
        cout<<"Number must be a decimal. Try again: ";
        cin>>a;
    }

    for(int i=0;i<23;i++)
    {
        if(a>=1)
        {
            a=(a-1)*2;
            cout<<a<<endl;
            temp=to_string(a);
            n=n+temp[0];

        }
        else
        {
            a=a*2;
            cout<<a<<endl;
            temp=to_string(a);
            n=n+temp[0];
        }
    }

    cout<<endl<<n;
}
