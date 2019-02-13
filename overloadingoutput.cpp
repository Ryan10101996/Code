#include <iostream>
#include <cstdlib>
using namespace std;

class door
{
private:
    int screws;
public:
    GetScrews();
    SetScrews(int x);
    friend ostream& operator<<(ostream&, door);
};

int main()
{
    door a;
    door b;
    door c;

    a.SetScrews(5);
    b.SetScrews(1);
    c.SetScrews(4);


}

door::GetScrews()
{
    return screws;
}

door::SetScrews(int x)
{
    screws =x;
}

ostream& operator<<(ostream& abc, door a[])
{
    int n = sizeof(a)/sizeof(a[0]);

    for(int i=0;i<n;i++)
    {
        abc<<a[i];
        return abc;
    }

}
