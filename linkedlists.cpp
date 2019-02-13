#include <iostream>
using namespace std;


struct node
  {
    int data;
    node *next;
  };

class list
  {
    private:
    node *head, *tail;
    public:
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
    node *temp;
    temp=head;
    while(temp!=NULL)
    {
      cout<<temp->data<<"\t";
      temp=temp->next;
    }
  }
   void delete_position(int pos)
  {
    node *current=new node;
    node *previous=new node;
    current=head;
    for(int i=1;i<pos;i++)
    {
      previous=current;
      current=current->next;
    }
    previous->next=current->next;
  }

  };



int main()
{   list list1;
    list1.createnode(5);
    list1.createnode(6);
    list1.createnode(7);
    list1.delete_position(3);
    list1.display();

}
