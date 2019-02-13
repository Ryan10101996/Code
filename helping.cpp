#include <iostream>
using namespace std;

int main()
{
    int newarray[4][4]=
    {
        {1,2,3,4},
        {4,3,2,1},
        {5,6,7,8},
        {8,7,6,5}
    };

    int array[4][4]=
    {
        {1,2,3,4},
        {4,3,2,1},
        {5,6,7,8},
        {8,7,6,5}
    };

    for(int i=0;i<4;i++)
        for(int j=0;j<4;j++)
            newarray[i][j]=array[i][3-j];

    for(int i=0;i<4;i++)
    {
        cout<<endl;
        for(int j=0;j<4;j++)
            cout<<newarray[i][j]<<" ";
    }
}
