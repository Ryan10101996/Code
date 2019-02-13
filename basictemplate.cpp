#include <iostream>
using namespace std;

template <class name>
name addstuff(name a, name b){
    return a+b;
}

template <class first, class second>
first smaller(first a, second b)
{
    return(a<b?a:b);
}

int main()
{
    int a,b,e;
    double c,d,f;

    a=5;
    b=6;
    c=5.2;
    d=6.1;

    e=addstuff(a,b);
    f=addstuff(c,d);

    cout<<e<<endl;
    cout<<f<<endl;

    int x=89;
    double y= 56.78;
    cout<<smaller(y,x)<<endl;


}
