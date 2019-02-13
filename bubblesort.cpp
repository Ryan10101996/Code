#include <iostream>
using namespace std;


int main()
{

    string names[6]={"Matherne","Smith","Matthew","Harrison","Smite","Adam"};

    int arraysize = sizeof(names)/sizeof(names[0]);

    for(int i=0;i<arraysize;i++)
        {
        for(int y=0;y<arraysize-1;y++)
        {
            string num= names[y];
            string num1=names[y+1];
            if(names[y]>names[y+1])
            {
                names[y]=num1;
                names[y+1]=num;
            }
        }
        }

    for(int i=0;i<arraysize;i++)
    {
        cout<<names[i]<<endl;
    }



}
