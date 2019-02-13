#include <iostream>
#include <string>
using namespace std;

int main()
{
    string findshit = "ABCD";

    string shittofind = "Suck4itbitchhfhhh....";
    bool reject;

    int found = shittofind.find_first_not_of("abcdeghijklmopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ(),.;:?!");





    if(found!=-1)
        if(shittofind[found]!='f')
            cout<<"Rejected";

    cout<<found;
}
