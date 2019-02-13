#include <iostream>
using namespace std;

void numberFunction(int i) {
  cout << "The number is: " << i << endl;
  i++;
  if(i<10) {
    numberFunction(i);
  }
}

void myFunction( int counter)
{
if(counter == 0)
     return;
else
       {
       cout <<counter<<endl;
       myFunction(--counter);
       return;
       }
}


int main() {

int i = 0;
numberFunction(i);
myFunction(5);
return 0;
}
