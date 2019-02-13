#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

int main()
{
    srand(time(0));

    int arraysize;
    arraysize=rand()%20;
    int array[arraysize];

    for(int i=0;i<arraysize;i++)
        array[i]=rand()%100;

    int n = sizeof(array) / sizeof(array[0]);

    cout<<"The unsorted array is: "<<endl;
    for(int i=0;i<n;i++)
        cout<<array[i]<<endl;

   for(int i=0;i<n;i++)
    for(int y=0;y<n-1;y++)
    {
        int num=array[y];
        int num1=array[y+1];

        if(num>num1)
        {
            array[y]=num1;
            array[y+1]=num;
        }
    }
    cout<<"The array sorted least to greatest is: "<<endl;
    for(int i=0;i<n;i++)
        cout<<array[i]<<endl;
}
