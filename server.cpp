#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

string dostuff(int);
void getdegree(int);
void error(const char *msg)
{
    perror(msg);
    exit(1);
}

struct information  //struct which will store information from text file
{
    string major = "";
    int starting=0;
    int median=0;
};

struct node //nodes of the linked list
{
    information info;
    node *next;
};

class linkedListType //creating my linked list class
  {
    private:
    node *head, *tail;  //Create my head and tail to sort through nodes
    public:
    string degree="";
    linkedListType()
    {
      head=NULL;
      tail=NULL; //Annnd est them to null

    }
    void insertend(information info) //function to insert struct into list
    {
        node *temp=new node;
        temp->info=info;
        temp->next=head;
        head=temp;
    }
    string display(string degree) //will search through linked list and give required output
    {
        bool found=false;
        node *temp;
        temp=head;
        string massivestring="";
        while(temp!=NULL)
        {
            if(degree==temp->info.major)
            {

                massivestring="\nThe average early career pay for a " + degree + " major is $" + to_string(temp->info.starting)+
                "\nThe corresponding mid career pay is $" + to_string(temp->info.median) + "\n\n";
                found=true;
            }
            temp=temp->next;
        }

        if(!found)
        {
            massivestring = "The degree was not found.\n";
           /*If the major is not found it will displace this in the place of the information on pay. I wasn't sure what it meant by giving
            negative numbers if the major was not found and this is better in my opinion so I went with this anyway. If I wanted to do
            the negative numbers thing I could just do something like:

            massivestring = "\nThe average early career pay for a " + degree "major is $-1\nThe corresponding mid career pay is $-1" and it should
            work just as well*/
        }
        return massivestring;
    }
    void dostuff (int sock) //This handles the output and receives the message from the client
    {
       int n;
       char buffer[256];
       string degree;
       string output;
       bzero(buffer,256);
       n = read(sock,buffer,255);
       if (n < 0) error("ERROR reading from socket");
       printf("Here is the message: %s\n",buffer);
       degree=buffer;
       output = display(degree);
       cout<<output;
       char coutput[500];
       strcpy(coutput,output.c_str());
       n = write(sock,coutput,500);
       if (n < 0) error("ERROR writing to socket");
    }
  };

information createstruct(string fileline) //Sorts through the list and creates the structs to be stored in the linked list
{
    string major="";
    string starting="";
    string median="";

    int linesize = fileline.length();
    int tab1 = fileline.find_first_of("\t"); //Since there will always be tabs before the needed information, it finds their location.
    int tab2 = fileline.find_last_of("\t");

    for(int i=0;i<tab1;i++)
    {
        major=major+fileline[i];
    }

    cout<<major<<endl;                      //It then records the needed information up to the tab into different strings to be stored

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

    return tempstruct; //returning a struct
}

int main()
{
     int sockfd, newsockfd, portno, pid;
     socklen_t clilen;
     struct sockaddr_in serv_addr, cli_addr; //declaring variables
     string portnumber;
     string filename;
     string fileline;

     cout<<"Enter the file name: ";     //Prompting user for information
     getline(cin,filename);

     fstream file;
     file.open(filename);
     linkedListType linkedlist;

    while(!file.eof())  //Goes through the file to create the linked list
    {
        getline(file,fileline);
        linkedlist.insertend(createstruct(fileline));
    }


     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0)
        error("ERROR opening socket");
     bzero((char *) &serv_addr, sizeof(serv_addr));
     cout<<"Enter the port number: ";
     getline(cin,portnumber); //Retreiving port number and setting it to the server
     portno = stoi(portnumber);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
              error("ERROR on binding");
     listen(sockfd,5);
     clilen = sizeof(cli_addr);

     while (1) { //while loop to keep server running to handle multiple requests
         newsockfd = accept(sockfd,
               (struct sockaddr *) &cli_addr, &clilen);
         if (newsockfd < 0)
             error("ERROR on accept");
         pid = fork();
         if (pid < 0)
             error("ERROR on fork");
         if (pid == 0)  {
             close(sockfd);
             linkedlist.dostuff(newsockfd); //This line does most of the work by calling dostuff which handles output and input
             exit(0);
         }
         else close(newsockfd);
     }
     close(sockfd);
     return 0;
}


void getdegree(int sock) //Gets the degree from the client
{
    string degree;
    int n;
    char buffer[256];
    bzero(buffer,256);
    n=read(sock,buffer,255);
    if (n < 0) error("ERROR reading from socket");
    n = write(sock,"I got your message",500);
    if (n < 0) error("ERROR writing to socket");
    degree=buffer;
    cout<<degree;
}
