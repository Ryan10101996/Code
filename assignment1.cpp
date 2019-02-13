#include <iostream>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

main()
{
  srand(time(0));
  int arraysize;
  arraysize=rand()%10;
  int numbers[arraysize][arraysize];
  int sumrow=0;
  int sumcolumn=0;
  int fileinfo[5][5];

  for(int j=0;j<arraysize;j++)
    for(int i=0;i<arraysize;i++)
        numbers[i][j]=rand()%20;

  for(int j=0;j<arraysize;j++){
        cout<<endl;
    for(int i=0;i<arraysize;i++)
        cout<<numbers[i][j]<<" ";
  }
 ifstream file;
 file.open("numberfile.txt");
 if(file.is_open())
 {
     cout<<"File is open.";

     string garbageline;
     getline(file, garbageline);

     while(!file.eof())
     {
         for(int i=0;i<5;i++)
            for(int j=0;j<5;j++)
                file>>fileinfo[j][i];
     }
 }
cout<<endl;

for(int i=0;i<5;i++)
    for(int j=0;j<5;j++)
        cout<<fileinfo[j][i];


cout<<endl<<endl;

ofstream matrix;
matrix.open("matrix.txt");

for(int j=0;j<arraysize;++j)
{
    for(int i=0;i<arraysize;++i)
        sumrow+=numbers[i][j];
    matrix<<sumrow<<" ";
    sumrow=0;
}
matrix<<endl;
for(int j=0; j<arraysize;++j)
{
    sumcolumn=0;
    for(int i=0;i<arraysize;++i)
        sumcolumn+=numbers[j][i];
    matrix<<sumcolumn<<" ";
}




}

