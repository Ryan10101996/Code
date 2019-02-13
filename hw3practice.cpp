#include <fstream>
#include <iostream>
#include <string>
#include <pthread.h>
#include <signal.h>
#include <unistd.h>



using namespace std;

int maxcars;
struct information
{
    int arrival;
    int crossingtime;
    int carnumber;
    string direction;
};

struct node
{
    information info;
    node *next;
};
string direction;
void* tunnel(void* arg)
{
    while(1)
    {
        cout<<"The tunnel is now open for Whittier-bound traffic."<<endl;
        direction="WB";
        sleep(5);
        cout<<"The tunnel is now closed to ALL traffic."<<endl;
        direction="CLOSED";
        sleep(5);
        cout<<"The tunnel is now open to Bear Valley-bound traffic."<<endl;
        direction="BB";
        sleep(5);
        cout<<"The tunnel is now closed to ALL traffic."<<endl;
        direction="CLOSED";
        sleep(5);
    }
}
int numbercars=0;
class linkedlist
  {
    private:
    node *head, *tail;
    public:
    string degree="";
    linkedlist()
    {
      head=NULL;
      tail=NULL;

    }
    void insertend(information info)
    {
        node *temp=new node;
        temp->info=info;
        temp->next=head;
        head=temp;
    }
    void display()
    {
        node *temp;
        temp=head;
        while(temp!=NULL)
        {
            cout<<temp->info.arrival<<" ";
            cout<<temp->info.direction<<" ";
            cout<<temp->info.crossingtime<<" "<<endl;
            temp=temp->next;
        }
    }
    information returnstruct(int number)
    {
        information tempstruct;
        node *temp;
        temp=head;

        while(temp!=NULL)
        {
            if(temp->info.carnumber==number)
            {
                tempstruct.arrival=temp->info.arrival;
                tempstruct.carnumber=temp->info.carnumber;
                tempstruct.crossingtime=temp->info.crossingtime;
                tempstruct.direction=temp->info.direction;
                return tempstruct;
            }
            temp=temp->next;
        }
    }
    information what(int i)
    {
        return returnstruct(i);
    }
};

int numberwb=0;
int numberbb=0;
int delay=0;
linkedlist cars;
int arrivaltime=0;
void getinfo()
{
    fstream file;
    string filename;
    string fileline;
    cout<<"Enter the name of the file: ";
    cin>>filename;
    file.open(filename);

    getline(file,fileline);
    maxcars= stoi(fileline);
    while(!file.eof())
    {
        int arrival;
        int crossingtime;
        string direction;

        file>>arrival;
        arrivaltime+=arrival;
        file>>direction;
        file>>crossingtime;

        if(direction=="WB")
            numberwb++;
        else if(direction=="BB")
            numberbb++;

        information tempstruct;
        tempstruct.arrival=arrivaltime+.5;
        tempstruct.crossingtime=crossingtime;
        tempstruct.direction=direction;
        numbercars++;
        tempstruct.carnumber=numbercars;

        cars.insertend(tempstruct);
    }
}
static pthread_mutex_t lock;
static int currentlycrossing=0;
void* carthread(void* arg)
{
    struct information *temp = (struct information*)arg;
    sleep(temp->arrival);
    pthread_mutex_lock(&lock);
    cout<<"Car # "<<temp->carnumber<<" going to ";
    if(temp->direction=="WB")
        cout<<"Whittier arrives at the tunnel."<<endl;
    else if(temp->direction=="BB")
        cout<<"Bear Valley arrives at the tunnel."<<endl;
    pthread_mutex_unlock(&lock);
    bool full=false;
    bool delay=false;
    while(!full)
    {
        if(direction==temp->direction)
        {
            pthread_mutex_lock(&lock);
            if(currentlycrossing<maxcars)
            {
                cout<<"Car # "<<temp->carnumber<<" going to ";
                if(temp->direction=="WB")
                    cout<<"Whittier enters the tunnel."<<endl;
                else if(temp->direction=="BB")
                    cout<<"Bear Valley enters the tunnel."<<endl;
                currentlycrossing++;
                pthread_mutex_unlock(&lock);
                sleep(temp->crossingtime);
                full=true;
            }
            else if(currentlycrossing>=maxcars)
            {
                delay=true;
                delay++;
                pthread_mutex_unlock(&lock);
            }
            else
            {
                pthread_mutex_unlock(&lock);
            }
        }
    }
    pthread_mutex_lock(&lock);
    cout<<"Car # "<<temp->carnumber<<" going to ";
    if(temp->direction=="WB")
        cout<<"Whittier exits the tunnel."<<endl;
    else if(temp->direction=="BB")
        cout<<"Bear Valley exits the tunnel."<<endl;
    currentlycrossing--;
    pthread_mutex_unlock(&lock);
	pthread_exit(NULL);

}

int main()
{
    getinfo();
    cars.display();
    pthread_t id[numbercars];
	pthread_t tunnels;
	pthread_create(&tunnels,NULL,tunnel,NULL);
	pthread_mutex_init(&lock,NULL);
	information carss[numbercars];
	for(int i=0;i<numbercars;i++)
    {
        carss[i]=cars.returnstruct(i+1);
    }
	for(int i=0;i<numbercars;i++)
	{
		pthread_create(&id[i],NULL,carthread,&carss[i]);
	}
	for(int i=0;i<numbercars;i++)
	{
		pthread_join(id[i],NULL);
	}
	cout<<numberbb<<" car(s) going to Bear Valley arrived at the tunnel."<<endl;
	cout<<numberwb<< " car(s) going to Whittier arrived at the tunnel."<<endl;
	cout<<delay <<" car(s) were delayed."<<endl;
}
