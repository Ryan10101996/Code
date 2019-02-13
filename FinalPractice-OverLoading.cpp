#include <iostream>
using namespace std;

class Point
{
private:
    int x;
    int y;
public:
    Point();
    Point(int,int);
    int GetX();
    int GetY();
    void SetX(int);
    void SetY(int);
    friend ostream& operator<<(ostream&, Point);
    friend istream& operator>>(istream&, Point&);
    Point operator +(Point a);

};

Point operator-(Point, Point);

int main()
{
    Point a;
    cin>>a;
    cout<<a;
    Point b;
    cin>>b;
    cout<<b;
    Point c;
    cout<<"Adding those numbers get you: ";
    c=a+b;
    cout<<c;
    cout<<"Subtracting those numbers gets you: ";
    Point d;
    d=a-b;
    cout<<d<<endl;
    cout<<(a+b)<<endl;
}

Point::Point(){}
Point::Point(int a,int b){x=a; y=b;}
int Point::GetX(){return x;}
int Point::GetY(){return y;}
void Point::SetX(int a){x=a;}
void Point::SetY(int a){y=a;}
ostream& operator<<(ostream& abc, Point a)
{
    abc<<"("<<a.x<<","<<a.y<<")"<<endl;
    return abc;
}
istream& operator>>(istream& abc, Point& a)
{
    cout<<"Enter the X coordinate: ";
    abc>>a.x;
    cout<<"Enter the Y coordinate: ";
    abc>>a.y;
    return abc;
}

Point Point::operator+(Point a)
{
    Point temp;
    temp.SetX(x+a.GetX());
    temp.SetY(y+a.GetY());
    return temp;
}

Point operator-(Point a,Point b)
{
    Point temp;
    temp.SetX(a.GetX()-b.GetX());
    temp.SetY(a.GetY()-b.GetY());
    return temp;
}

