#include <iostream>
#include "converter.cpp"
using namespace std;


float ConvertCurrency(converter a);
converter operator+(converter a, converter b);

int main()
{
    converter b;
    b.ConvertDistance(50);
    b.ConvertTemp(20);
    b.SetCurrency(5000);
    ConvertCurrency(b);
    cout<<b;
    converter c;
    converter d;
    c.SetCurrency(2500);
    d=b+c;
    cout<<"The total of the currency in objects B and C is: "<<d.GetCurrency()<<endl;
    converter e;
    e=b-c;
    cout<<"The difference between the currency in objects B and C is: "<<e.GetCurrency()<<endl;
}

float ConvertCurrency(converter a)
{
    int b;
    try
    {
    cout<<"Enter 1 if converting to dollars and enter 2 if convertng to euros: ";
    cin>>b;

    if(b!=1 && b!=2)
        throw 52;
    }
    catch(int)
    {
        cout<<"You were supposed to enter a 1 or 2"<<endl;
    }

    float d=a.GetCurrency();

    if(b==1)
    {
        float c;
        c= d*1.13694;
        cout<<d<<" euros is equal to "<<c<<" dollars"<<endl;
        a.SetCurrency(c);
    }
    if(b==2)
    {
        float c;
        c=d*.879552;
        cout<<d<<" dollars is equal to "<<c<<" euros"<<endl;
        a.SetCurrency(c);
    }

}

converter operator+(converter a, converter b)
{
    converter temp;
    temp.SetCurrency(a.GetCurrency()+b.GetCurrency());
    return temp;
}
