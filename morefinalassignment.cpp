#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

int main()
{
    float sumrow = 0;                          //Creating variable to hold sum of rows
    float sumcolumn = 0;                       //Creating variable to hold sum of columns

    int lines = 0;                           //Creating a variable for the line counter
    string waste;                            //Unused string necessary to count lines
    string inputfile;                        //Declaring variables for the input/output files
    string outputfile;

    cout<<"Enter the name of the input file, including the .txt: "<<endl;
    getline(cin,inputfile);                                               //Allows user to set name of files
    cout<<"Enter the name of the out file, including the .txt: "<<endl;
    getline(cin,outputfile);

    ifstream file;

    file.open(inputfile.c_str());             //The job of this is to count the lines in the file which determines how big the matrix is.
    while(getline(file,waste))
        lines++;

    file.close();

    float data[lines-1][lines-1];

      if(lines==0||lines==1)
    {
        cout<<"Empty file or no matrix.";
        ofstream matrix;
        matrix.open(outputfile.c_str());    //Checks to see if file is empty and stops program if so.
        matrix<<" ";
        matrix.close();
        return 1;
    }
    cout<<lines<<endl;

    file.open(inputfile.c_str());

    for(int i=0;i<lines-1;i++)         //Stores the numbers in the dynamic array using a loop
            for(int j=0;j<lines-1;j++)
            {
                file>>data[j][i];

            }


    file.open(inputfile.c_str());            //Opening the file again to actually retrieve the data
    if(file.is_open())
    {
        cout<<"File is open."<<endl;;              //Notifying that the file is open

        string garbageline;                 //The first line in the file, according to the given format, is not needed. This skips past it.
        getline(file, garbageline);

        while(!file.eof())
        {

         for(int i=0;i<lines-1;i++)         //Stores the numbers in the dynamic array using a loop
            for(int j=0;j<lines-1;j++)
            {
                file>>data[j][i];

            }
                               //If the loop fails, likely due to there being a non-float, this will display an error.
        }

    }

    file.close();

            //All data is retrieved so closing hte file


    ofstream matrix;                         //Creating a new file to write the information to
    matrix.open(outputfile.c_str());         //Opening

    matrix.precision(2);                     //Setting a fixed amount of 2 decimal places.
    matrix.setf(ios::fixed);

    for(int j=0;j<lines-1;++j)
    {
        for(int i=0;i<lines-1;++i)          //This gets the sum of each row using a for loop.
            sumrow+=data[i][j];
        matrix<<sumrow<<" ";                //Formatting
        sumrow=0;                           //The sum must be set back to zero after each iteration to work
    }
    matrix<<endl;                           //Formatting
    for(int j=0; j<lines-1;++j)
    {
        sumcolumn=0;
        for(int i=0;i<lines-1;++i)          //This does the same as above except for the columns
            sumcolumn+=data[j][i];
        matrix<<sumcolumn<<" ";             //Formatting
    }
}
