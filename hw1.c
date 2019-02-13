
#include <iostream>
#include <time.h>
#include <cstdlib>
using namespace std;


double fRand(double, double);
int main(int argc, char* argv[]){

        if(argc!=3){
        cout<<"Enter 3 arguments"<<endl;
        exit(1);
}


        double theMax = 0.0;
        double theMin = 0.0;

        int totalRows = atoi(argv[1]);
        int totalCols = atoi(argv[2]);

        double **matrixM; //initialize array of pointer to arrays
        double **matrixN;
        double **sumMatrix;

        matrixM = new double * [totalRows];
        matrixN = new double * [totalRows];
        sumMatrix = new double * [totalRows];

        if((totalRows <= 0) ||(totalCols<=0)){
        cout<< "You must enter positive integers"<<endl;
        exit(1);
        }

        for (int currentRow = 0; currentRow < totalRows; currentRow++){
                matrixM[currentRow] = new double [totalCols];
        }

        for (int currentRow = 0; currentRow < totalRows; currentRow++){
                for (int currentCol = 0; currentCol < totalCols; currentCol++){
                        matrixM[currentRow][currentCol] = fRand(1.0,100.0);

                        cout<<"["<<matrixM[currentRow][currentCol]<<"] ";
                }
                cout<<endl;
        }
        cout <<"+"<<endl;
         for (int currentRow = 0; currentRow<totalRows; currentRow++){
                matrixN[currentRow] = new double [totalCols];
        }

        for (int currentRow = 0; currentRow < totalRows; currentRow++){
                for (int currentCol = 0; currentCol < totalCols; currentCol++){
                        matrixN[currentRow][currentCol] = fRand(1.0,100.0);

                        cout<<"["<<matrixM[currentRow][currentCol]<<"] ";
                }
                cout<<endl;
        }
        cout <<"="<<endl;

        for (int currentRow = 0; currentRow<totalRows; currentRow++){
        sumMatrix[currentRow] = new double [totalCols];
        }

        for (int currentRow = 0; currentRow < totalRows; currentRow++){
                for (int currentCol = 0; currentCol < totalCols; currentCol++){
                        sumMatrix[currentRow][currentCol] = matrixM[currentRow][currentCol]+matrixN[currentRow][currentCol];
                        if (theMax <= sumMatrix[currentRow][currentCol]){
                                theMax = sumMatrix[currentRow][currentCol];
                        }
                        if (theMin >= sumMatrix[currentRow][currentCol] || theMin == 0){
                                theMin = sumMatrix[currentRow][currentCol];
                        }

                        cout<<"["<<sumMatrix[currentRow][currentCol]<<"] ";
                }
                cout<<endl;
         }
        cout<<"\n\n\n\n"<<"The max of all this is: "<<theMax<<endl;
        cout<<"\n"<<"The min of all this is: "<<theMin<<endl;

        for (int k =0; k < totalRows; k++){
                delete [] matrixM[k];
                delete[] matrixN[k];
                delete sumMatrix[k];
        }
        delete [] matrixM;
        delete [] matrixN;
        delete [] sumMatrix;
}

double fRand(double fMin, double fMax)
{
 double f = (double)rand() / RAND_MAX;
        return fMin + f * (fMax - fMin);
}





