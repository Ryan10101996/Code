#include <iostream>
using namespace std;

struct node
  {
    int data;
    node *next;
  };


class list{
public:
    node *head;
    node *tail;
    list()
    {
        head=NULL;
        tail=NULL;
    }
void createnode(int value)
    {
      node *temp=new node;
      temp->data=value;
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
     void display()
  {
    node *temp=new node;
    temp=head;
    while(temp!=NULL)
    {
      cout<<temp->data<<"\t";
      temp=temp->next;
    }
  }

  void kill(int value)
  {
      node *current = head;
      node *trailcurrent= new node;
      bool found = false;

      while(current->data!=value && !found)
      {

          if(current->data!=value)
          {
              cout<<"yo dog";
            trailcurrent=current;
            current=current->next;
          }

          else
          {
            cout<<"HI";
            found=true;
          }
      }
      cout<<found;
      cout<<"Hi?";
      if(2==2)
      {
          cout<<"hello";
          trailcurrent->next=current->next;
      }

  }
};


int main()
{
    list thing;

    thing.createnode(5);
    thing.createnode(10);
    thing.createnode(12);
    thing.display();
    thing.kill(10);
    thing.display();
}
