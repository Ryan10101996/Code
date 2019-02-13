#include <fstream>
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <list>
using namespace std;

//Confirmed working

struct information
{
    string major = "";
    int starting=0;
    int median=0;
};

struct node
{
    information info;
    node *next;
};

class linkedListType
  {
    private:
    node *head, *tail;  //Create my head and tail to sort through nodes
    public:
    linkedListType()
    {
      head=NULL;
      tail=NULL; //Annnd est them to null

    }
    void insertend(information info)
    {
        node *temp=new node;
        temp->info=info;
        temp->next=head;
        head=temp;
    }
    void display(string degree)
    {
        bool found=false;
        node *temp;
        temp=head;
        string massivestring="";
        while(temp!=NULL)
        {
            if(degree==temp->info.major)
            {
                /*cout<<endl;
                cout<<"The average early career pay for a "<<degree<<" major is $"<<
                temp->info.starting<<endl;
                cout<<"The corresponding mid career pay is $"<<temp->info.median<<endl;
                cout<<endl;*/

                massivestring="\nThe average early career pay for a " + degree + " major is $" + to_string(temp->info.starting)+
                "\nThe corresponding mid career pay is $" + to_string(temp->info.median) + "\n\n";
                cout<<massivestring;
                found=true;
            }
            temp=temp->next;
        }

        if(!found)
        {
            cout<<"Not found in table."<<endl;
        }
    }
  };

information createstruct(string fileline)
{
    string major="";
    string starting="";
    string median="";

    int linesize = fileline.length();
    int tab1 = fileline.find_first_of("\t");
    int tab2 = fileline.find_last_of("\t");

    for(int i=0;i<tab1;i++)
    {
        major=major+fileline[i];
    }

    cout<<major<<endl;

    for(int i=tab1+1;i<tab2;i++)
    {
        starting=starting+fileline[i];
    }

    cout<<starting<<endl;;

    for(int i=tab2+1;i<linesize;i++)
    {
        median=median+fileline[i];
    }

    cout<<median<<endl;

    information tempstruct;
    tempstruct.major=major;
    tempstruct.starting=stoi(starting);
    tempstruct.median=stoi(median);

    return tempstruct;
}

int main()
{
    fstream file;
    file.open("Salaries.txt");
    string fileline;
    linkedListType linkedlist;

    while(!file.eof())
    {
        getline(file,fileline);
        linkedlist.insertend(createstruct(fileline));
    }

    file.close();
    string major ="";
    do
    {
        cout<<"Enter a college major: ";
        getline(cin,major);
        linkedlist.display(major);
    }while(major!="");


}
