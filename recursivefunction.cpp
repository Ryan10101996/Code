#include <iostream>
using namespace std;

float raisetopower(float base, int power)
{
    int answer=base;
    if(power==0)
    {
        return 1;
    }
    else
    {
        for(int i=1;i<power;i++)
        {
            answer*=base;
        }
        return answer;
    }
}

float recursivepower(float base, int power)
{
    if(power==0)
        return 1;
    else
    {
        return (base*recursivepower(base, power-1));
    }
}


int main()
{
    float a = raisetopower(2,5);
    cout<<a<<endl;
    float b= recursivepower(2,0);
    cout<<b<<endl;
}
