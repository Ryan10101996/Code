#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main()
{
    string line;
    int lines=0;
    string array1[100];
    int i =0;

    fstream file("input2.txt");

    if (file.is_open())
        while(getline(file,line))
        {
            cout<<line<<endl;
            lines++;
            file>>array1[i];
            i++;
        }
        file.close();

    for(int i=0;i<lines;i++)
        cout<<array1[i]<<endl;
}

