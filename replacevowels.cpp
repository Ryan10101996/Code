#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    fstream file("vowels.txt");
    fstream output;
    output.open("Outputs.txt",ios::out);

    char cstring[80];


    while(!file.eof())
    {
        file.getline(cstring,80);
        for(int i=0; cstring[i] != '\0';i++)
        {
            if(cstring[i]=='a'||cstring[i]=='e'||cstring[i]=='i'||cstring[i]=='o'||cstring[i]=='u')
                cstring[i]='v';
            output<<cstring[i];
        }
        output<<endl;
        cout<<cstring<<endl;
    }

    file.close();
    output.close();
}









