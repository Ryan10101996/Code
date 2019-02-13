#include <iostream>
using namespace std;

int main()
{

    try
{
    int word;
    cout<<"Enter a four digit number: "<<endl;
    cin>> word;


        if(word<=999)
            throw 50;
        if(word>=9999)
            throw 51;
        if(word==1234)
            throw 52;
}

    catch(int x)
    {
        if(x==50)
            cout<<"Number is less than four digits.";
        if(x==51)
            cout<<"Number is greater than four digits.";
        if(x==52)
            cout<<"I don't like that number. Enter a different one.";
    }



}
