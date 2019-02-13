#include <iostream>
#include <ctime>
#include <cstdlib>
using namespace std;

class ArraySort
{
private:
    int size;
    int* unsorted_arr;
    int* sorted_arr;

public:
    ArraySort(){}
    void Setsize(int a)
        {
            size = a;
        }
    void SetUnsortedArray()
        {
            unsorted_arr= new int[size];
            for(int i=0;i<size;i++)
            {unsorted_arr[i]=rand()%100;}
        }
    void SortedArray()
        {
            sorted_arr= new int[size];
            for(int i=0;i<size;i++)
                {
                    sorted_arr[i]=unsorted_arr[i];
                }
        }
    void SortArray()
    {

    for(int i=0;i<size;i++)
        for(int y=0;y<size-1;y++)
            if(sorted_arr[y]<sorted_arr[y+1])
            {
                int temp=sorted_arr[y];
                sorted_arr[y]=sorted_arr[y+1];
                sorted_arr[y+1]=temp;
            }
    }
    void PrintAll()
    {
        cout<<"The unsorted array is:"<<endl;
        for(int x=0;x<size;x++)
            cout<<unsorted_arr[x]<<endl;
        cout<<"The sorted array is:"<<endl;
        for(int x=0;x<size;x++)
            cout<<sorted_arr[x]<<endl;
        cout<<"The size is:"<<endl;
        cout<<size;
    }
};

int main()
{
    srand(time(0));

    ArraySort object;

    object.Setsize(5);
    object.SetUnsortedArray();
    object.SortedArray();
    object.SortArray();
    object.PrintAll();




}
