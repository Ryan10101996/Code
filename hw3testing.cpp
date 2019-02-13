#include <iostream>
#include <fstream>          //Including some basic libraries
#include <string>
#include "ArgumentManager.h"
using namespace std;        //In order to not write out std:;

class stack                 //Declaring my stack
{
public:
    int currentsize=10;     //Setting 10 for inital size of stack
    int timesdoubled=0;     //Variable to keep track of the times the stack is doubled
    int stacktop =0;        //Variable to keep track of top of stack
    string *words = new string[currentsize];    //Creating stack as dynamic array
    string input;       //variables to store file names
    string output;
    void doublesize()
    {
        string tempwords[currentsize];      //In order to double the stack a temp array must first be created to store all the values
        for(int i=0;i<currentsize;i++)      //The for loop stores these values in the temp array
            tempwords[i]=words[i];
        currentsize=currentsize*2;          //Doubles the size and creates new array
        delete[] words;                     //deletes old array
        words= new string[currentsize];     //Creates new one of desired size
        for(int i=0;i<currentsize/2;i++)    //Puts variables from temp back into main array
            words[i]=tempwords[i];
        timesdoubled++;
    }
    void getwords()
    {
        fstream file;
        file.open(input);       //create fstream object and open file
        int counter=0;
        while(!file.eof())          //This function simply reads through the file
        {
            string currentword;     //Usd to store current word
            int currentwordsize;    //keeps track of size of the word

            file>>currentword;      //reads from file
            if(reject(currentword))
            {
                if(stacktop==currentsize)   //Checks if words need to be rejected, if not checks if array needs to be doubled, if not
                    doublesize();           //calls push to insert word
                push(currentword);
            }
        }
    }
    void outputwords()
    {
        ofstream out;
        out.open(output);   //creates file object and opens
        while(stacktop-1>=0)
            {
                out<<words[stacktop-1];    //Outputs to the file, using pop to travel through the stack and stopping at index 0
                out<<" ";
                pop();
            }
        out<<endl<<timesdoubled; //outputs times doubled
        out.close();         //closes file
    }
    bool reject(string current)
    {
        cout<<current<<endl;
        int currentwordsize;                //Checks to see if word needs to be rejected by searching through the string for illegal characters
        currentwordsize=current.length();

        int found = current.find_first_not_of("abcdefghijklmopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ(),.;:?!");

        if(found!=-1)
            if(current[found]!='"')
                return false;
        for(int i=1;i<currentwordsize-1;i++)
            if(current[i]=='!'||current[i]=='.'||current[i]=='?'||current[i]=='!'||current[i]=='"'||current[i]=='('||current[i]==')'||current[i]==':'||current[i]==';'||current[i]==',')
            {
                return false;       //Searches for puncuation in the middle of the word and returns false if it finds it
            }
        if(current[0]=='!'||current[0]=='.'||current[0]=='?'||current[0]=='!'||current[0]==')'||current[0]==':'||current[0]==';'||current[currentwordsize-1]==
        '('||current[0]==',')   //Searches for the wrong type of punctuation at the start
            return false;
        if(current=="")
            return false;   //deletes blank spaces
        return true;        //If none of the above conditions are met it is safe to insert
    }

    string removepunctuation(string aword)
    {
        int currentwordsize = aword.length();   //Removes punctuation by searching through the word in the same way as above
        if(aword[currentwordsize-1]=='!'||aword[currentwordsize-1]=='?'||aword[currentwordsize-1]==')'||aword[currentwordsize-1]=='"'||aword[currentwordsize-1]==';'
        ||aword[currentwordsize-1]==':'||aword[currentwordsize-1]==','||aword[currentwordsize-1]=='.')
        {
            aword.erase(currentwordsize-1,currentwordsize-1);   //If it comes across puncuation it uses the erase command to delete it
        }
        else
        {

        }
        if(aword[0]=='('||aword[0]=='"')
        {
            aword.erase(0,1);
        }

        return aword;   //returns the word without punctuation
    }
    void push(string word)
    {
        words[stacktop]=removepunctuation(word);    //Adds the word to array and increments the stacktop variable
        stacktop++;
    }
    void pop()
    {
        if(stacktop>0) //Removes from the stack unless it is at index 0
            stacktop--;
    }
};

int main(int argc, char* argv[])
{
    stack thing;        //creates my stack

    if (argc < 2)
    {
        cout << "Usage: densemult \"A=<file>;C=<file>\"" <<endl;        //For reading the file names
        return -1;
    }

    ArgumentManager am(argc, argv);
    thing.input = am.get("A");
    thing.output = am.get("C");


    thing.getwords();   //stores the words
    thing.outputwords(); //outputs them
}
