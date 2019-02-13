#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <stdexcept>
#include "ArgumentManager.h"
using namespace std;

struct student_info //struct to store student info
{
    string info1; //id
    string info2; //first name
    string info3; // last name
    string info4; //major
    string info5; // gpa
    string info6; // hours
};

template<class Type> //template because...No reason. I guess to make things harder.
struct node
{
    Type info; // Create my node
    node *next;
};
template<class Type> //TEMPLATE
class linkedListType
  {
    private:
    node<Type> *head, *tail;  //Create my head and tail to sort through nodes
    public:
    linkedListType()
    {
      head=NULL;
      tail=NULL; //Annnd est them to null

    }
     string outputname; // Can't actually remember why this is here but I'm not deleting anything
     void createnode(Type information);
     int listlength =0;
      //Declare function to create node. Don't ask why everything is set up within list except this.


    void PRINT_ROSTER()
    {
        node<Type> *temp; // Function to print roster
        temp=head;
        while(temp!=NULL) // Stops when it reaches end of list
        {
            output(temp->info.info2 + " " + temp->info.info3 + ", " + temp->info.info1,0); //Prints stuff...
            temp=temp->next; //Moves on to next node
        }
        output("",0); //Newline
    }
    void PRINT_BY_MAJOR(string fileline) //Prints by major
    {
        node<Type> *temp;
        temp=head;
        while(temp!=NULL)
        {
            if(fileline==temp->info.info4)
                output(temp->info.info2 + " " + temp->info.info3 + ", " + temp->info.info1,0);
            temp=temp->next;

        }

        output("",0);
    }
    void PRINT_BY_GPA(string fileline)
    {
        node<Type> *temp; //Once again, same as above. Only difference is it prints things out which are equal to or greater than given gpa
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
        temp=head;          //sorts through node
        while(temp!=NULL)
        {
            if(fileline==temp->info.info2 && fileline1==temp->info.info3)
            {
                output(temp->info.info2 + " " + temp->info.info3 + ", " + temp->info.info1,0);
                output("Major: " + temp->info.info4,0);
                output(temp->info.info5,2);                         //formatted output
                output("Credits Enrolled: " + temp->info.info6,0);

            }
            temp=temp->next; //goes to next node, just like on the others
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
            if(fileline!=temp->info.info2 && fileline1!=temp->info.info3)  //find position of student
            {
                y++;
                 if(temp->next==NULL)       //if the student isn't found it breaks out
                {
                    y=-1;
                    break;
                }
            }
            else
                break;
            temp=temp->next;

        }

        if(y==0)
        {
            node<Type> *temp = new node<Type>; //if position of student is first in list it uses this
            temp=head;
            head=head->next;
            delete temp;
            listlength--;
        }
        else if(y==-1)
        {
            cout<<"Doesnt exist";       //if it's -1 which means it doesn't exist it outputs this
        }
        else
        {
            node<Type> *current = new node<Type>;
            node<Type> *previous=new node<Type>; //anywhere else in the list it uses this
            current = head;
            for(int i=0;i<y;i++)
            {
                previous=current;
                current=current->next;
            }
            previous->next=current->next;
            listlength--;
        }
    }
    void DELETE_ID(string fileline)
    {
        int y=0;
        int a = stoi(fileline);     //pretty much same thing going on here as above
        node<Type> *temp;
        temp=head;                      //only difference is it ompares ID instead of first and last name
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
            listlength--;

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
            listlength--;
        }
    }
    bool duplicates(Type information)
    {
            node<Type> *temp;
            temp=head;          //this function searches for duplicates
            while(temp!=NULL)   //it compares the info it's given to what's already in the list
            {                   //and returns true if such an entry a;ready exists
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
        y= stof(gpa);       //Stuff I guess. Stof..>Yeah. GPA needs to be a float here or you can't compare it to numbers.

        if(y>4 || y<0)
            cout<<"GPA not within bounds.";     //Checks to see if it's between 0 and 4.
        else
        {
        while(temp!=NULL)
        {
            if(firstname==temp->info.info2 && lastname==temp->info.info3)
            {
                temp->info.info5 = gpa;     //This...Umm. Oh. Yeah. If the GPA is appropiate it then sets it
                break; //and breaks out
            }
            temp=temp->next;
        }
        }
    }
    void UPDATE_MAJOR(string firstname, string lastname, string major)
    {
        node<Type> *temp;
        temp=head;              //updates the major!
        while(temp!=NULL)
        {
            if(firstname==temp->info.info2 && lastname==temp->info.info3)
            {
                temp->info.info4=major;     //searches through, when it finds a match it sets it
            }
            temp=temp->next;
        }
    }
    void ADD_CLASS(string firstname, string lastname, string credits)
    {
        node<Type> *temp;
        temp=head;
        int totalcredits = stoi(credits);       //adds a class. this is making the credits into an int and storing it
        while(temp!=NULL)
        {
            if(firstname==temp->info.info2 && lastname==temp->info.info3)   //checking for matching first and last name
            {
                totalcredits = totalcredits + stoi(temp->info.info6);
                if(totalcredits>15)
                    break;              //This adds up the credits and checks if it's out of bonds. If it does it breaks out.
                else
                {
                    temp->info.info6=to_string(totalcredits);       //Otherwise all is fine and dandy and it sets it.
                }
            }
            temp=temp->next;
        }
    }
    void REMOVE_CLASS(string firstname, string lastname, string credits)
    {
        node<Type> *temp;
        temp=head;
        int totalcredits = stoi(credits);       //Same thing as above, really. Except subtraction.
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
        temp=head;          //Prints out average gpa. This is just like declaring stuff...Some if it may not be used. I edit stuff as I go.
        float finalgpa=0;
        while(temp!=NULL)
        {
            totalgpa= totalgpa + stof(temp->info.info5);
            divideby++;
            temp=temp->next;            //This adds up all the GPAs into one variable and keeps track fo how many were added
        }

        if(divideby==0)
            cout<<"No students.";   //Cannot divide by 0
        else
            finalgpa = totalgpa/divideby;   //Gets the average
            output(to_string(finalgpa),1); //Has to be string to work

    }
    void output(string info, int isGPA) //This is where all my output is done
    {
        if(isGPA==1)
        {
            ofstream out;   //So this is a bit weird but oh well. Since GPA has to be precision 2 but nothing else has to be...I did this.
            out.open(outputname,ios::app);
            double floatgpa= stod(info);
            out<<"GPA Mean: "<<fixed<<setprecision(2)<<floatgpa;
            out<<endl;
            out.close(); //I have three different cases for this output function. If it's 1, it will pretty much just print GPA mean correct.
        }
        if(isGPA==0)
        {
            ofstream out;
            out.open(outputname,ios::app);
            out<<info;          //0 is what most will use and just print normally
            out<<endl;
            out.close();
        }
        if(isGPA==2)
        {
            ofstream out;
            out.open(outputname,ios::app);
            float floatgpa = stof(info);
            out<<"GPA: "<<fixed<<setprecision(2)<<floatgpa<<endl; //This is just for a single line within print student...Nothing use uses 2.
            out.close();
        }
    }
      void insertmiddle(Type information)
    {
        node<Type> *pre=new node<Type>;
        node<Type> *cur=new node<Type>;
        node<Type> *temp=new node<Type>;
        cur=head;
        int pos=findposition(information.info3);
        cout<<pos;

        for(int i=0;i<pos;i++)
        {
            pre=cur;
            cur=cur->next;

        }

        temp->info=information;
        pre->next=temp;
        temp->next=cur;
    }
    int findposition(string lastname)
    {
        int counter=0;
        node<Type> *temp;
        temp=head;

        while(temp!=NULL)
        {
            string otherlastname=temp->info.info3;

            if(lastname>otherlastname)
                counter++;
            else
                break;
            temp=temp->next;
        }
        return counter;
    }
    void insertend(Type information)
    {
        node<Type> *temp=new node<Type>;
        temp->info=information;
        temp->next=head;
        head=temp;
    }
    void insertsomewhere(Type information,int listlengthglobal)
    {
        int pos = findposition(information.info3);

        if(pos==0)
            insertend(information);
        else if(pos==listlengthglobal)
            createnode(information);
        else
            insertmiddle(information);
    }

  };

  bool isint(string info)
  {
      //want to check that each character is an integer

      try
      {
          float a = stof(info); //if thsi fails
      }
      catch(invalid_argument& e)        //it goes here
      {
        return false;       //and returns false to say it aint int
      }
      return true;
  }
  /*
  bool isint(string info)
  {
      for( int i = 0; i < info.length(); i++)
      {

          if(!(info.substr(i)=="0" ... .... =="9")) //coulda done this but oh well
            return false;

      }
      return true;

  }
    if(!(chararray[i]>= 0 && chararray[i]<=9))
*/
int main()
{
    fstream file;
    string fileline;            //declaring variable
    string fileline1;
    string fileline2;
    int listlengthglobal =0;


    int studentID;
    float gpa;
    int credits;
    int x;

   /* if (argc < 2)
    {
        cout << "Usage: densemult \"A=<file>;C=<file>\"" <<endl;
        return -1;
    }

    ArgumentManager am(argc, argv);
    string inputfile = am.get("A");
    string outputfile = am.get("C");
    cout << "File name for matrix A: " << inputfile << endl
    << "File name for matrix C: " << outputfile << endl;
    */


    file.open("hw2input.txt");
    linkedListType<student_info> linkedlist;

    linkedlist.outputname = "hw2output.txt";    //file input


    while(!file.eof())
    {
        getline(file,fileline);


        if(fileline=="INSERT")
        {
            x=0;
            student_info information;           //This massive bit of code sorts through the file
            while(getline(file,fileline))
            {
                if(fileline!="")
                    {
                        if(x==0)
                        {
                            int length = fileline.length();
                            cout<<length<<endl;
                            if(length!=5)
                                break;          //For id. If length of ID isn't 5 ints, it breaks out.
                            else
                            {
                                information.info1=fileline; //stores
                            }
                        }
                        if(x==1)
                            information.info2=fileline;
                        if(x==2)
                            information.info3=fileline; //stors more info
                        if(x==3)
                            information.info4=fileline;
                        if(x==4)
                        {
                            gpa = stof(fileline);
                            if(gpa>4 || gpa<0)
                                break;                  //makes sure gpa is within bounds then stores. If not breaks/
                            information.info5=fileline;
                        }
                        if(x==5)
                        {
                            credits = stoi(fileline);
                            if(credits>15 || credits<=0)        //checks to see if credits are within bounds. Ifn ot break
                                break;
                            information.info6=fileline;
                        }

                        x++;
                        if(x==6)
                        {
                            if(linkedlist.duplicates(information))
                            {
                                listlengthglobal++;

                                if(listlengthglobal==1)
                                    linkedlist.createnode(information);
                                else
                                    linkedlist.insertsomewhere(information,listlengthglobal);


                            }
                        }
                    }
                else
                    break;
                if(x==6)        //break out to start again
                    break;
            }
        }

        if(fileline=="PRINT_ROSTER")
        {
            linkedlist.PRINT_ROSTER();  //calls function
        }
        if(fileline=="PRINT_BY_MAJOR")
        {
            getline(file,fileline);
            if(fileline=="")
            {

            }
            else        //checks to see if there is any input and if there is it does it
            {
            linkedlist.PRINT_BY_MAJOR(fileline);
            }
        }
        if(fileline=="PRINT_BY_GPA")
        {
            getline(file,fileline);
            if(fileline=="")
            {

            }                           //same as above
            else if(!isint(fileline))
            {

            }
            else
            {
            linkedlist.PRINT_BY_GPA(fileline);
            }
        }
        if(fileline=="PRINT_STUDENT")
        {
            getline(file,fileline);
            if(fileline!="")
            {
                getline(file,fileline1);        //nested if statements so it can break out if any info is missing
                if(fileline1!="")
                {
                    linkedlist.PRINT_STUDENT(fileline,fileline1);
                }
            }
        }
        if(fileline=="DELETE_STUDENT")
        {
            getline(file,fileline);
            if(fileline!="")
            {
                getline(file,fileline1);        //same thing as above
                if(fileline1!="")
                {
                    linkedlist.DELETE_STUDENT(fileline,fileline1);
                }
            }
        }
        if(fileline=="DELETE_ID")
        {
            getline(file,fileline);
            if(fileline=="")
            {

            }
            else if(!isint(fileline))       //only difference here is it calls in on my isint function to make sure the imput is proper, if its' there
            {

            }
            else
            {
            linkedlist.DELETE_ID(fileline); //if it is it does the thing
            }
        }
        if(fileline=="UPDATE_GPA")
        {
          getline(file,fileline);
            if(fileline!="")
            {
                getline(file,fileline1);
                if(fileline1!="")
                {
                    getline(file,fileline2);
                    if(fileline2!="")
                    {
                        if(!isint(fileline2))       //same as above with more lines
                        {

                        }
                        else
                        {
                            linkedlist.UPDATE_GPA(fileline,fileline1,fileline2);
                        }
                    }
                }
            }
        }

        if(fileline=="UPDATE_MAJOR")
        {
            getline(file,fileline);
            if(fileline!="")
            {
                getline(file,fileline1);
                if(fileline1!="")               //same
                {
                    getline(file,fileline2);
                    if(fileline2!="")
                    {
                        linkedlist.UPDATE_MAJOR(fileline,fileline1,fileline2);
                    }

                }

            }
        }
        if(fileline=="ADD_CLASS")
        {
            getline(file,fileline);
            if(fileline!="")
            {
                getline(file,fileline1);
                if(fileline1!="")
                {
                    getline(file,fileline2);        //....
                    if(fileline2!="")
                    {
                        if(!isint(fileline2))
                        {

                        }
                        else
                        {
                            linkedlist.ADD_CLASS(fileline,fileline1,fileline2);
                        }
                    }
                }
            }
        }
         if(fileline=="REMOVE_CLASS")
        {
            getline(file,fileline);
            if(fileline!="")
            {
                getline(file,fileline1);
                if(fileline1!="")
                {
                    getline(file,fileline2);
                    if(fileline2!="")
                    {
                        if(!isint(fileline2))
                        {

                        }
                        else
                        {
                            linkedlist.REMOVE_CLASS(fileline,fileline1,fileline2);
                        }
                    }
                }
            }

        }
        if(fileline=="GPA")
        {
            linkedlist.GPA();
            cout<<endl;
        }
    }
}

template<class Type>
void linkedListType<Type>::createnode(Type information)       //This creates my createnode function. He doesn't behave well with the rest of the functions
{                                                   //So he has been exiled to the bottom of the code.
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
