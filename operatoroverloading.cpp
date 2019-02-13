#include <iostream>
using namespace std;

class MidPoint
{
private:
    float x;
    float y;
public:
    MidPoint();
    void SetX(float a);
    void SetY(float b);
    float GetX();
    float GetY();
    MidPoint operator+(MidPoint a)
    {
        MidPoint b;
        int c= GetX() + a.GetX();
        cout<<"X1 is: "<<GetX()<<endl;;
        cout<<"X2 is: "<<a.GetX()<<endl;
        cout<<c;
        b.SetX(GetX() + a.GetX());
        cout<<b.GetX();
        return b;
    }








};

int main()
{
    MidPoint d;
    MidPoint b;
    MidPoint c;

    d.SetX(10);
    b.SetY();
    c.SetX(0);
    cout<<c.GetX();

    c = d+b;

    cout<<c.GetX()<<endl;
}

MidPoint::MidPoint(){}

void MidPoint::SetX(float a)
{
    x=a;
}

void MidPoint::SetY(float b)
{
    y=b;
}

float MidPoint::GetX()
{
    return x;
}

float MidPoint::GetY()
{
    return y;
}

