#include <iostream>
#include <fstream>
#include <cstdlib>
using namespace std;

struct student
{
    int grades;
    string name;
};
int main()
{
    fstream file("studentinfo.txt",ios::in);

    student *arr = new student[100];
    int i=0;

    while(!file.eof())
    {
        file>>arr[i].name;
        arr[i].grades=rand()%100;

        cout<<arr[i].name<<endl;
        cout<<arr[i].grades<<endl;
        i++;

    }
}
