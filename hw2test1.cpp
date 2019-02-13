#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdexcept>
#include "ArgumentManager.h"
using namespace std;

struct student_info
{
    string info1; //id
    string info2; //first name
    string info3; // last name
    string info4; //major
    string info5; // gpa
    string info6; // hours
};

template<class Type>
struct node
{
    Type info;
    node *next;
};
template<class Type>
class list
  {
    private:
    node<Type> *head, *tail;
    public:
    list()
    {
      head=NULL;
      tail=NULL;

    }
     string outputname;
     void createnode(Type information);


     void display()
     {
        node<Type> *temp;
        temp=head;
        while(temp!=NULL)
        {
            cout<<temp->info.info1<<"\t";
            cout<<temp->info.info2<<"\t";
            cout<<temp->info.info3<<"\t";
            cout<<temp->info.info4<<"\t";
            cout<<temp->info.info5<<"\t";
            cout<<temp->info.info6<<endl;
            temp=temp->next;
        }
    }
    void PRINT_ROSTER()
    {
        node<Type> *temp;
        temp=head;
        while(temp!=NULL)
        {
            output(temp->info.info2 + " " + temp->info.info3 + ", " + temp->info.info1,0);
            temp=temp->next;
        }
        output("",0);
    }
    void PRINT_BY_MAJOR(string fileline)
    {
        node<Type> *temp;
        temp=head;
        while(temp!=NULL)
        {
            if(fileline==temp->info.info4)
            {
                output(temp->info.info2 + " " + temp->info.info3 + ", " + temp->info.info1,0);
            }
            temp=temp->next;
        }
        output("",0);
    }
    void PRINT_BY_GPA(string fileline)
    {
        node<Type> *temp;
        temp=head;
        while(temp!=NULL)
        {
            if(temp->info.info5>=fileline)
            {
                output(temp->info.info2 + " " + temp->info.info3 + ", " + temp->info.info1,0);
            }
            temp=temp->next;
        }
        output("",0);
    }
    void PRINT_STUDENT(string fileline,string fileline1)
    {
        node<Type> *temp;
        temp=head;
        while(temp!=NULL)
        {
            if(fileline==temp->info.info2 && fileline1==temp->info.info3)
            {
                output(temp->info.info2 + " " + temp->info.info3 + ", " + temp->info.info1,0);
                output("Major: " + temp->info.info4,0);
                output(temp->info.info5,2);
                output("Credits Enrolled: " + temp->info.info6,0);

            }
            temp=temp->next;
        }
        output("",0);
    }
    void DELETE_STUDENT(string fileline,string fileline1)
    {
        int y=0;
        node<Type> *temp;
        temp=head;
        while(temp!=NULL)
        {
            if(fileline!=temp->info.info2 && fileline1!=temp->info.info3)
                y++;
            else
                break;
            temp=temp->next;

        }

        if(y==0)
        {
            node<Type> *temp = new node<Type>;
            temp=head;
            head=head->next;
            delete temp;
        }
        else
        {
            node<Type> *current = new node<Type>;
            node<Type> *previous=new node<Type>;
            current = head;
            for(int i=0;i<y;i++)
            {
                previous=current;
                current=current->next;
            }
            previous->next=current->next;
        }
    }
    void DELETE_ID(string fileline)
    {
        int y=0;
        int a = stoi(fileline);
        node<Type> *temp;
        temp=head;
        cout<<"Detle ID"<<endl;
        while(temp!=NULL)
        {
            if(a!=stoi(temp->info.info1))
            {
                y++;
                cout<<"counter"<<endl;
                if(temp->next==NULL)
                {
                    y=-1;
                    break;
                }
            }
            else
            {
                cout<<"Else"<<endl;
                break;
            }
            temp=temp->next;

        }
        if(y==0)
        {
            node<Type> *temp = new node<Type>;
            temp=head;
            head=head->next;
            delete temp;
        }
        else if(y==-1)
        {
            cout<<"Doesn't exist"<<endl;
        }
        else
        {
            node<Type> *current = new node<Type>;
            node<Type> *previous=new node<Type>;
            current = head;
            for(int i=0;i<y;i++)
            {
                previous=current;
                current=current->next;
            }
            previous->next=current->next;
        }
    }
    bool duplicates(Type information)
    {
            node<Type> *temp;
            temp=head;
            while(temp!=NULL)
            {
                if(temp->info.info2 == information.info2 && temp->info.info3 == information.info3 || temp->info.info1 == information.info1)
                {
                    return false;
                }
                temp=temp->next;
            }
            return true;
    }
    void UPDATE_GPA(string firstname, string lastname, string gpa)
    {
        float y=0;
        node<Type> *temp;
        temp=head;
        y= stof(gpa);

        if(y>4 || y<0)
            cout<<"GPA not within bounds.";
        else
        {
        while(temp!=NULL)
        {
            if(firstname==temp->info.info2 && lastname==temp->info.info3)
            {
                temp->info.info5 = gpa;
                break;
            }
            temp=temp->next;
        }
        }
    }
    void UPDATE_MAJOR(string firstname, string lastname, string major)
    {
        node<Type> *temp;
        temp=head;
        while(temp!=NULL)
        {
            if(firstname==temp->info.info2 && lastname==temp->info.info3)
            {
                temp->info.info4=major;
            }
            temp=temp->next;
        }
    }
    void ADD_CLASS(string firstname, string lastname, string credits)
    {
        node<Type> *temp;
        temp=head;
        int totalcredits = stoi(credits);
        while(temp!=NULL)
        {
            if(firstname==temp->info.info2 && lastname==temp->info.info3)
            {
                totalcredits = totalcredits + stoi(temp->info.info6);
                if(totalcredits>15)
                    break;
                else
                {
                    temp->info.info6=to_string(totalcredits);
                }
            }
            temp=temp->next;
        }
    }
    void REMOVE_CLASS(string firstname, string lastname, string credits)
    {
        node<Type> *temp;
        temp=head;
        int totalcredits = stoi(credits);
        while(temp!=NULL)
        {
            if(firstname==temp->info.info2 && lastname==temp->info.info3)
            {
                totalcredits = stoi(temp->info.info6) - totalcredits;
                if(totalcredits<=0)
                    break;
                else
                {
                    temp->info.info6=to_string(totalcredits);
                }
            }

            temp=temp->next;
        }
    }
    void GPA()
    {
        float totalgpa;
        int divideby=0;
        node<Type> *temp;
        temp=head;
        float finalgpa=0;
        while(temp!=NULL)
        {
            totalgpa= totalgpa + stof(temp->info.info5);
            divideby++;
            temp=temp->next;
        }

        if(divideby==0)
            cout<<"No students.";
        else
            finalgpa = totalgpa/divideby;
            output(to_string(finalgpa),1);

    }
    void output(string info, int isGPA)
    {
        if(isGPA==1)
        {
            ofstream out;
            out.open(outputname,ios::app);
            double floatgpa= stod(info);
            out<<"GPA Mean: "<<fixed<<setprecision(2)<<floatgpa;
            out<<endl;
            out.close();
        }
        if(isGPA==0)
        {
            ofstream out;
            out.open(outputname,ios::app);
            out<<info;
            out<<endl;
            out.close();
        }
        if(isGPA==2)
        {
            ofstream out;
            out.open(outputname,ios::app);
            float floatgpa = stof(info);
            out<<"GPA: "<<fixed<<setprecision(2)<<floatgpa<<endl;
            out.close();
        }
    }
  };

  bool isint(string info)
  {
      //want to check that each character is an integer

      try
      {
          int a = stoi(info);
      }
      catch(invalid_argument& e)
      {
        return false;
      }
      return true;
  }
  /*
  bool isint(string info)
  {
      for( int i = 0; i < info.length(); i++)
      {

          if(!(info.substr(i)=="0" ... .... =="9"))
            return false;

      }
      return true;

  }
    if(!(chararray[i]>= 0 && chararray[i]<=9))
*/
int main(int argc, char* argv[])
{
    fstream file;
    string fileline;
    string fileline1;
    string fileline2;

    int studentID;
    float gpa;
    int credits;
    int x;

    if (argc < 2)
    {
        cout << "Usage: densemult \"A=<file>;C=<file>\"" <<endl;
        return -1;
    }

    ArgumentManager am(argc, argv);
    string inputfile = am.get("A");
    string outputfile = am.get("C");
    cout << "File name for matrix A: " << inputfile << endl
    << "File name for matrix C: " << outputfile << endl;

    file.open(inputfile);
    list<student_info> linkedlist;

    linkedlist.outputname = outputfile;

    while(!file.eof())
    {
        getline(file,fileline);


        if(fileline=="INSERT")
        {
            x=0;
            student_info information;
            while(getline(file,fileline))
            {
                if(fileline!="")
                    {
                        if(x==0)
                        {
                            int length = fileline.length();
                            cout<<length<<endl;
                            if(length!=5)
                                break;
                            else
                            {
                                information.info1=fileline;
                            }
                        }
                        if(x==1)
                            information.info2=fileline;
                        if(x==2)
                            information.info3=fileline;
                        if(x==3)
                            information.info4=fileline;
                        if(x==4)
                        {
                            gpa = stof(fileline);
                            if(gpa>4 || gpa<0)
                                break;
                            information.info5=fileline;
                        }
                        if(x==5)
                        {
                            credits = stoi(fileline);
                            if(credits>15 || credits<=0)
                                break;
                            information.info6=fileline;
                        }

                        x++;
                        if(x==6)
                        {
                            if(linkedlist.duplicates(information))
                                linkedlist.createnode(information);
                        }
                    }
                else
                    break;
                if(x==6)
                    break;
            }
        }

        if(fileline=="PRINT_ROSTER")
        {
            linkedlist.PRINT_ROSTER();
            cout<<endl;
        }
        if(fileline=="PRINT_BY_MAJOR")
        {
            getline(file,fileline);
            linkedlist.PRINT_BY_MAJOR(fileline);
            cout<<endl;
        }
        if(fileline=="PRINT_BY_GPA")
        {
            getline(file,fileline);
            linkedlist.PRINT_BY_GPA(fileline);
            cout<<endl;
        }
        if(fileline=="PRINT_STUDENT")
        {
            getline(file,fileline);
            getline(file,fileline1);
            linkedlist.PRINT_STUDENT(fileline,fileline1);
            cout<<endl;
        }
        if(fileline=="DELETE_STUDENT")
        {
            getline(file,fileline);
            getline(file,fileline1);
            linkedlist.DELETE_STUDENT(fileline,fileline1);
        }
        if(fileline=="DELETE_ID")
        {
            getline(file,fileline);
            linkedlist.DELETE_ID(fileline);
        }
        if(fileline=="UPDATE_GPA")
        {
            getline(file,fileline);
            getline(file,fileline1);
            getline(file,fileline2);
            linkedlist.UPDATE_GPA(fileline,fileline1,fileline2);
        }
        if(fileline=="UPDATE_MAJOR")
        {
            getline(file,fileline);
            getline(file,fileline1);
            getline(file,fileline2);
            linkedlist.UPDATE_MAJOR(fileline,fileline1,fileline2);
        }
        if(fileline=="ADD_CLASS")
        {
            getline(file,fileline);
            getline(file,fileline1);
            getline(file,fileline2);
            if(fileline=="" || fileline1=="" ||fileline2=="")
            {

            }
            else if(!isint(fileline2))
            {

            }
            else
                linkedlist.ADD_CLASS(fileline,fileline1,fileline2);
        }
         if(fileline=="REMOVE_CLASS")
        {
            getline(file,fileline);
            getline(file,fileline1);
            getline(file,fileline2);
            linkedlist.REMOVE_CLASS(fileline,fileline1,fileline2);
        }
        if(fileline=="GPA")
        {
            linkedlist.GPA();
            cout<<endl;
        }
    }
}

template<class Type>
void list<Type>::createnode(Type information)
{
      node<Type> *temp=new node<Type>;
      temp->info=information;
      temp->next=NULL;
      if(head==NULL)
      {
        head=temp;
        tail=temp;
        temp=NULL;
      }
      else
      {
        tail->next=temp;
        tail=temp;
      }
}
