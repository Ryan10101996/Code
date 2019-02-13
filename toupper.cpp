#include <iostream>
#include <string>
#include <fstream>
#include <stdio.h>
#include <string.h>
using namespace std;

int main()
{

    string letters = "FAT'a'SSss";

    char *a=new char[letters.size()+1];
    a[letters.size()]=0;
    memcpy(a,letters.c_str(),letters.size());

    char letter = 'T';

    letter += 32;

    int stringlength=letters.length();


    string newletters="";
    char c;
    for(int i=0;i<stringlength;i++)
    {
        c=letters[i];

        if(isalpha(c))
        {
            if(i==0&&letters[i]>=90)
            {
                c=letters[i]-32;
            }

            if(i!=0&&letters[i]<=90&&isalpha(letters[i]))
            {
                c=letters[i]+32;
            }
        }

        newletters=newletters+c;
    }

    cout<<newletters;

}
