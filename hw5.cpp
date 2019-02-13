#include <iostream>
#include <fstream>
#include <unistd.h>
#include <float.h>
#include <cassert>
#include <streambuf>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <sys/stat.h>
#include "ArgumentManager.h"
#include <stdexcept>

using namespace std;

int vcount = 0;              //global variables
bool tfpat = false;
int ostart = 0;
bool isadded1 = false;
int variable3 = 0;
int int2 = 0;
void swap(int *xp, int *yp)
{
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}


void bubbleSort(int arr[], int n)
{
   int i, j;                        //sorting function
   for (i = 0; i < n-1; i++)
       for (j = 0; j < n-i-1; j++)
           if (arr[j] > arr[j+1])
              swap(&arr[j], &arr[j+1]);
}
int loop (int start, int end, int **&adjacencyarray10, int **&pathwayarray10, int *&adjmatcounter)
{
    bool boolvalue2 = false;
    int int1;
    int pathc = 1;
    boolvalue2 = false;     //declare values

    for (int i = start; i < start + 1; i++)
    {
        for (int i = 0; i < vcount; i++)            //begin for loops
        {

            if (adjacencyarray10[start][i] == 0)
                boolvalue2 = true;              //if matrix = 0, set true
            else
            {
                boolvalue2 = false; //other wise false n break
                break;
            }
        }

        if (boolvalue2 == true && start == variable3 && !isadded1)
        {
            isadded1 = true;
            pathwayarray10[ostart-1][0] = start;
            adjmatcounter[ostart-1] += 1;       //incrmen counter

            if (int2 == 3) //break condition
            {
                break;
            }
        }

       for (int j = end; j < vcount; j++)
       {

        if (adjacencyarray10[i][j] == 1)
        {
            for (int a = ostart-1; a < ostart; a++) //
            {
                for (int b = 0; b < adjmatcounter[ostart-1]; b++) //for loops for patbways
                  {
                    pathc = b;
                    if (j == pathwayarray10[a][b])
                    {
                        tfpat = true;       //setting my bool values
                    }
                    else
                    {
                        tfpat = false;
                    }
                    if (tfpat)
                    {
                        break;
                    }
                  }
                if (tfpat)
                {
                    break;
                }
            }

            if (tfpat)
            {
                continue;
            }
            if (!tfpat)
            {

                if (start == variable3 && !isadded1) //set same as i
                {

                    isadded1 = true;
                    pathwayarray10[ostart-1][0] = start;
                    adjmatcounter[ostart-1] += 1;
                }

                pathwayarray10[ostart -1][adjmatcounter[ostart-1]] = j;
                adjmatcounter[ostart-1] += 1;
                loop(j, 0, adjacencyarray10, pathwayarray10, adjmatcounter);
                int1 = i;
            }
        }
       }
    }
}

class msTreeType
{                   //creating my spanning tree
public:
    void minimumSpanning(int sVertex);

     msTreeType(int size = 0);

     int temppathc = 1;         //variables

    ~msTreeType();
    int z = 0;

    int tracker = 0;

    void retrieveData();
    int array10[3];
int array102[3];

    string input;
    string output;      //declaring more variables, including the files
    int counter3 = 0;
    int chosearray10[500];
    bool boolvalue1 = false;


protected:

    int source;     //protefcted variables
    double **weights;
    int *edges;
    double *edgeweight;
    int gSize;
};


void msTreeType::minimumSpanning(int sVertex)
{

    int startVertex, endVertex;
    double minWeight;
    int k = 0;          //declaring variables
    int j = 0;


    source = sVertex;

    bool *mstv;
    mstv = new bool[gSize];

    for (int j = 0; j < gSize; j++)
    {
        mstv[j] = false;        //for loop looking at weights
        edges[j] = source;
        edgeweight[j] = weights[source][j];
    }

    mstv[source] = true;
    edgeweight[source] = 0;

    for (int i = 0; i < gSize - 1; i++)
    {
        minWeight = 9999;

        for (j = 0; j < gSize; j++)
            {
                if(mstv[j])
                {
                    for (k = 0; k < gSize; k++)     //storing some info
                    {
                        if (!mstv[k] &&     weights[j][k]  < minWeight)
                        {
                            if (weights[j][k] == -999 || weights[j][k] == 0)
                                 continue;
                            endVertex = k;
                            startVertex = j;
                            minWeight = weights[j][k];
                        }
                    }
                }
            }

        mstv[endVertex] = true;
        edges[endVertex] = startVertex;     //storing edges
        edgeweight[endVertex] = minWeight;
    }



}

msTreeType::msTreeType(int size)
                                //setting some weights
{
    weights = new double*[size];
    for (int i = 0; i < size; i++)
        weights[i] = new double[size];
    edges = new int[size];
    edgeweight = new double[size];
    gSize = size;
}

msTreeType::~msTreeType() //to destruct tree
{
    for (int i = 0; i < gSize; i++)
        delete [] weights;
    delete [] edges;
    delete edgeweight;
}

void msTreeType::retrieveData()
{
    fstream f; //input stream
    ofstream g; //output stream
    f.open(input, ios::in);
    g.open(output, ios::out);
    string line; //line to store input
    int word[500][500]; //to store
    string wordss;
    int tempnum;
    stringstream ss;
    int elemc = 0;
    int horizontalCount[500];
    for (int i = 0; i < 500; i++)
        horizontalCount[i] = 0;
    int horCounter = 0;

    getline(f, line);
        while(line != "" && !f.eof())
        {

             //to split the input into potential words
            while(line != "" && !f.eof())
            {ss << line;
            for (int i = 0; ss >> wordss; i++)
            {

                tempnum = atoi(wordss.c_str());
                word[vcount][i] = tempnum;
                horizontalCount[horCounter] += 1;
            }

            ss.clear();
            vcount++;       //add to counters and getlines
            getline(f, line);
            horCounter++;

            }

        }
        int **adjmatrix;
        adjmatrix = new int*[vcount];
        for (int i = 0; i < vcount; i++)
            adjmatrix[i] = new int[vcount];

        for (int pu  = 0; pu < vcount; pu++)
            for (int mu = 0; mu < vcount; mu++)
                adjmatrix[pu][mu] = 0;
        for (int i = 0; i < vcount; i++)
          {
          for (int j = 0; j < horizontalCount[i]; j++)
        {
            adjmatrix[word[i][j]][i] = 1;
            adjmatrix[i][word[i][j]] = 1;
        }
          }
        int secondvcount = 0; //reset counter
        int horizcounter = 0;

        getline(f, line);
        while(line != "" && !f.eof())
        {

            ss.clear();
            ss << line;
            for (int i = 0; ss >> wordss; i++)
             {
                tempnum = atoi(wordss.c_str());
                word[secondvcount][i] = tempnum;
                horizcounter++; //fixed matrix
             }
            secondvcount++;
            if (horizcounter != vcount)
            {
                exit(0);
            }
            getline(f, line);
            ss.clear();
            horizcounter = 0;
        }

        if (secondvcount != vcount)
            exit(0);
        for (int pu  = 0; pu < vcount; pu++)
            for (int mu = 0; mu < vcount; mu++)     //handling weights
                weights[pu][mu] = word[pu][mu];

                getline(f, line);
        if (line == "")
            exit(0);
        int clustnum = atoi(line.c_str());
        if (clustnum < 1)
            exit(0);
        else if (clustnum > vcount)
            exit(0);




int r = 0;
int vortex = 0;
       for (int i = 0; i < vcount; i++)
       {
        for (r = 0; r < vcount; i++)
            if (adjmatrix[i][r] == 1)
            {
                vortex = i;
                break;
            }
            if (adjmatrix[i][r] == 1)
                break;
       }

minimumSpanning(vortex);

tracker = true;
int highestWeight = 0;
    int weightloc[vcount][2];
    int weightlocnum = 0;
int **pathwayList;
pathwayList = new int*[clustnum];
for (int i = 0; i < clustnum; i++)
            pathwayList[i] = new int[vcount];

int *adjmatcounter;
adjmatcounter = new int[clustnum];
for (int i = 0; i < clustnum; i++)
    adjmatcounter[i] = 0;


 while (temppathc != clustnum)
   {


    for (int i = 0; i < vcount; i++)
        for (int j = 0; j < vcount; j++)// check if weights need to be removed
            if (weights[i][j] >= highestWeight)
            {
                highestWeight = weights[i][j];
            }
    for (int i = 0; i < vcount; i++)
        for (int j = 0; j < vcount; j++)// check if weights need to be removed
            if (weights[i][j] == highestWeight)
            {
                highestWeight = weights[i][j];
                weightloc[weightlocnum][0] = i;
                weightloc[weightlocnum][1] = j;
                weightlocnum++;
            }
    bool proceed = false;



   for (int q = 0; q < weightlocnum; q++)
    for (int i = 0; edges[i]; i++)
        {
            if (weightloc[q][0] != i)
                if(weightloc[q][0] != edges[i])
                    if (weightloc[q][1] != i)
                        if(weightloc[q][1] != edges[i])
                            {
                                proceed = true;
                                break;
                            }
                        else
                            proceed = false;
        }

    if (proceed = true)
    {
        for (int i = 0; i < weightlocnum; i++)
        {
        adjmatrix[weightloc[i][0]][weightloc[i][1]] = 0;
        adjmatrix[weightloc[i][1]][weightloc[i][0]] = 0;//check weights
        weights[weightloc[i][0]][weightloc[i][1]] = -999;
        weights[weightloc[i][1]][weightloc[i][0]] = -999;//removes weights
        }


    }

weightlocnum = 0;
highestWeight = 0;

            elemc = 0;
            variable3 = 0;
            counter3 = 0;
            ostart = 0;
            if (z == 0)
                tracker = vcount;
for (int j = 0; j <= temppathc; j++)
            adjmatcounter[j] = 0;
   for (int i = 0; elemc != vcount; i++)
    {
        isadded1 = false;
        tfpat = false;
        ostart++;
        loop(variable3, 0, adjmatrix, pathwayList, adjmatcounter);

        for (int packingHeat = i; packingHeat < ostart ; packingHeat++)
        {


       elemc += adjmatcounter[i];
        }
         for (int j = 0; j < vcount; j++)
     {


      for (int itch = 0; itch < ostart; itch++)
        {
     for (int ithurts = 0; ithurts < adjmatcounter[itch]; ithurts++)
    {
        if (pathwayList[itch][ithurts] != j)
            boolvalue1 = false;
        else
        {
            boolvalue1 = true;
            break;
        }
    }
    if (boolvalue1 == true)
        break;}
    if (boolvalue1 == true)
        continue;
    if (boolvalue1 == false && j != 0)
    {
        chosearray10[counter3] = j;
        counter3++;
    }
}

variable3 = chosearray10[0];
for (int i = 0; i < counter3; i++)
 {
        if (variable3 < chosearray10[i])
            continue;
        else
            variable3 = chosearray10[i];

}


if (elemc != vcount && elemc != tracker && i == temppathc - 1)
       temppathc++;


isadded1 = false;
for (int i = 0; i < vcount; i++)
    chosearray10[i] = 9999;
}
tracker = elemc;

    int2++;

if (clustnum != temppathc)
{

    delete [] pathwayList;
    int ** pathwayList;
    pathwayList = new int*[clustnum];
    for (int i = 0; i < clustnum; i++)
                pathwayList[i] = new int[vcount];
}
}
    z++;



for (int q = 0; q < clustnum; q++)
{
    int *matco;
    matco = new int[adjmatcounter[q]];

for (int j = 0; j < adjmatcounter[q]; j++)
{
    matco[j] = pathwayList[q][j];
}
    bubbleSort(matco, adjmatcounter[q]);
for (int j = 0; j < adjmatcounter[q]; j++)
{
    pathwayList[q][j] = matco[j];

}
delete matco;

}


for (int i = 0; i < clustnum; i++)
    array10[i] = pathwayList[i][0];
bubbleSort(array10, clustnum);

for (int i = 0; i < clustnum; i++)
    for (int j = 0; j < clustnum; j++)
if (pathwayList[j][0] == array10[i])
array102[i] = j;


for (int i = 0; i < clustnum; i++)
{
for (int j = 0; j < adjmatcounter[array102[i]]; j++)
    g << pathwayList[array102[i]][j] << " ";
g << endl;
}
}
int main(int argc, char* argv[])
{

string iferror;

try{
    msTreeType thing = msTreeType(10);

     if (argc < 2)
    {
        cout << "Usage: densemult \"A=<file>;C=<file>\"" <<endl;        //For reading the file names
        return -1;
    }

    ArgumentManager am(argc, argv);

    thing.input = am.get("A");
    thing.output = am.get("C"); //setting right names
    string iferror= am.get("C");



    thing.retrieveData();
}

catch(invalid_argument& e)
{
    ofstream blankfile;
    blankfile.open(iferror);
    blankfile.close();
}
}







