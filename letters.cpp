#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    char *letter = new char[5000];

    cin>>letter;

    ofstream output;
    output.open("lettersoutput.txt");

    for(int i=0;letter[i]!='\0';i++)
        {
            output<<":_"<<letter[i]<<":"<<" ";
        }

    output.close();
}
