#include <iostream>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
using namespace std;

int main()
{
    int a[10];
    int b[10];
    srand(time(NULL));

    for(int i=0;i<10;i++)
    {
        a[i]=rand() % 10 + 1;
        b[i]=rand() % 10 + 1;
    }

    for(int i=0;i<10;i++)
    {
        for(int j=0;j<10;j++)
        {
            if(a[i]==b[j])
                cout<<a[j]<<"=="<<a[i]<<endl;
        }
    }
}

