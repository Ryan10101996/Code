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
    friend istream& operator>>(istream&, Point);
    ~Point();

};
