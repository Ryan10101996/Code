#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    fstream input("vowels.txt");
    fstream output("Output.txt");

    char carray[100];

    while(!input.eof())
    {
        input.getline(carray,100);
        for(int i=0;carray[i]!='\0';i++)
        {
            if(carray[i]=='a'||carray[i]=='e'||carray[i]=='i'||carray[i]=='o'||carray[i]=='u')
                carray[i]='v';
            output<<carray[i];
        }
        output<<endl;
        cout<<carray<<endl;
    }
    input.close();
    output.close();
}
