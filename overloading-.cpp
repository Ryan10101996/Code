#include <iostream>
using namespace std;

class Numbers
{
private:
    int x;
    int y;
public:
    int GetX();
    int GetY();
    void SetX(int a);
    void SetY(int a);
    friend ostream &operator <<(ostream&, Numbers);
    friend istream &operator >>(istream&, Numbers&);
};

Numbers operator-(Numbers a, Numbers b);

int main()
{
    Numbers a;
    Numbers b;
    Numbers c;

    a.SetX(5);
    b.SetX(10);

    c=b-a;

    cout<<c.GetX()<<endl;
    cout<<b-a<<endl;
}

ostream& operator<< (ostream& a, Numbers n)
{
    a<<n.GetX();
    return a;
}

istream& operator >>(istream& d, Numbers& n)
{
    d >> n.x;
    return d;
}




int Numbers::GetX()
{
    return x;
}

int Numbers::GetY()
{
    return y;
}

void Numbers::SetX(int a)
{
    x=a;
}

void Numbers::SetY(int a)
{
    y=a;
}

Numbers operator-(Numbers a, Numbers b)
{
    Numbers c;
    c.SetX(a.GetX()-b.GetX());
    return c;
}
















