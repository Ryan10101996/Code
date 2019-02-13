#include <iostream>
#include <string>
using namespace std;

class Enemy
{
    public:
        virtual void attack(){}
        Enemy()
        {
            cout<<"Enemy constructor"<<endl;
        }
        ~Enemy()
        {
            cout<<"Enemy destructor"<<endl;
        }
};
class Ninja : public Enemy
{
    public:
        Ninja()
        {
            cout<<"ninja constructor"<<endl;
        }
        void attack()
        {
            cout << "ninja attack" <<endl;
        }
        ~Ninja()
        {
            cout<<"Ninja destructor"<<endl;
        }

};
class Monster : public Enemy
{
    public:
        void attack()
        {
            cout << "Monster attack" <<endl;
        }
        Monster()
        {
            cout<<"Monster constructor"<<endl;
        }
        ~Monster()
        {
            cout<<"Monster destructor"<<endl;
        }
};

class AnotherEnemy : public Monster
{
public:
    AnotherEnemy()
    {
        cout<<"AnotherEnemy constructor"<<endl;
    }
    ~AnotherEnemy()
    {
        cout<<"AnotherEnemy deconstructor"<<endl;
    }
};

int main ()
{

    Monster m;
    Ninja n;
    AnotherEnemy am;

    Enemy *enemy1 = &n;
    Enemy *enemy2 = &m;

    enemy2 -> attack();
    enemy1 -> attack();

}
