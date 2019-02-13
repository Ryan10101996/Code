#include <iostream>
#include <fstream>
#include <string>
using namespace std;

class stack
{
public:
    int currentsize=10;
    int timesdoubled=0;
    int items;
    string *words = new string[currentsize];
    doublesize()
    {
        string tempwords[currentsize];
        for(int i=0;i<currentsize;i++)
            tempwords[i]=words[i];
        currentsize=currentsize*2;
        words= new string[currentsize];
        for(int i=0;i<currentsize/2;i++)
            words[i]=tempwords[i];
        timesdoubled++;
    }
    getwords()
    {
        fstream file;
        file.open("hw3input.txt");
        int counter=0;
        while(!file.eof())
        {
            string currentword;
            int currentwordsize;

            file>>currentword;
            if(reject(currentword))
            {
                if(counter==currentsize)
                    doublesize();
                words[counter]=removepunctuation(currentword);
                counter++;
                items=counter;
            }
        }
    }
    outputwords()
    {
        for(int i=items-1;i>=0;i--)
            {
                ofstream out;
                out.open("hw3output.txt");
                out<<words[i];
                out<<" ";
            }
        cout<<endl<<timesdoubled;
    }
    bool reject(string current)
    {
        cout<<current<<endl;
        int currentwordsize;
        currentwordsize=current.length();

        for(int i=0;i<currentwordsize;i++)
            if(current[i]=='@'||current[i]=='#'||current[i]=='$'||current[i]=='%'||current[i]=='^'||current[i]=='&'||current[i]=='*'||current[i]=='<'||current[i]=='>'||current[i]=='/'
               ||current[i]=='|'||current[i]=='{'||current[i]=='}'||current[i]=='['||current[i]==']'||current[i]=='+'||current[i]=='='||current[i]=='-'||current[i]=='_'
               ||current[i]=='1'||current[i]=='2'||current[i]=='3'||current[i]=='0'||current[i]=='4'||current[i]=='5'||current[i]=='6'||current[i]=='7'||current[i]=='8'
               ||current[i]=='9')
            {
                return false;
            }
        for(int i=1;i<currentwordsize-1;i++)
            if(current[i]=='!'||current[i]=='.'||current[i]=='?'||current[i]=='!'||current[i]=='"'||current[i]=='('||current[i]==')'||current[i]==':'||current[i]==';')
            {
                return false;
            }
        if(current[0]=='!'||current[0]=='.'||current[0]=='?'||current[0]=='!'||current[0]==')'||current[0]==':'||current[0]==';'||current[currentwordsize-1]==
        '('||current[0]==',')
            return false;
        if(current=="")
            return false;
        return true;
    }

    string removepunctuation(string aword)
    {
        int currentwordsize = aword.length();
        if(aword[currentwordsize-1]=='!'||aword[currentwordsize-1]=='?'||aword[currentwordsize-1]==')'||aword[currentwordsize-1]=='"'||aword[currentwordsize-1]==';'
        ||aword[currentwordsize-1]==':'||aword[currentwordsize-1]==','||aword[currentwordsize-1]=='.')
        {
            aword.erase(currentwordsize-1,currentwordsize-1);
        }
        else
        {

        }
        if(aword[0]=='('||aword[0]=='"')
        {
            aword.erase(0,1);
        }

        return aword;

    }
};

int main()
{
    stack thing;
    thing.getwords();
    thing.outputwords();
}
