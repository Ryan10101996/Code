#include <tchar.h>
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{

    clock_t startTime;
    int freeBytes;
    int freePage;
    int freeVirtual;

    MEMORYSTATUS MemoryInfo;
    GlobalMemoryStatus(&MemoryInfo);

    freeBytes = MemoryInfo.dwAvailPhys;
    freePage = MemoryInfo.dwAvailPageFile;

    freeVirtual = MemoryInfo.dwAvailVirtual;

    cout << "dwAvailPhys: " << MemoryInfo.dwAvailPhys << endl;
    cout << "dwAvailPageFile: " << MemoryInfo.dwAvailPageFile << endl;
    cout << "dwAvailVirtual: " << MemoryInfo.dwAvailVirtual << endl;
    double valuesToTest[] = {0.5,0.6,0.7,0.8 ,0.9, 0.95,0.99, 1.0,1.01, 1.5, 2, 5, 10, 100};
    int numberOfNewByes;
    int *arrayOfInts; //

    for (int i=0; i<15; i++) {
        cout << endl << "Value tested: " << valuesToTest[i] << endl;

        startTime = clock();
        numberOfNewByes = (int) ( valuesToTest[i] * (freeBytes));
        arrayOfInts = new int[numberOfNewByes/sizeof(int)];

        GlobalMemoryStatus(&MemoryInfo);
        cout << "dwAvailPhys: " << MemoryInfo.dwAvailPhys << endl;
        cout << "dwAvailPageFile: " << MemoryInfo.dwAvailPageFile << endl;
    cout << "dwAvailVirtual: " << MemoryInfo.dwAvailVirtual <<endl;

        for (int x=0; x < numberOfNewByes/sizeof(int); x++){
            arrayOfInts[x]=1;
        }

        for (int x=0; x < numberOfNewByes/sizeof(int); x++){
            arrayOfInts[x]=arrayOfInts[x]+1;
        }

        delete [] arrayOfInts;
        cout << endl << "Time elapsed: " << ((double)(clock() - startTime) / (double)CLOCKS_PER_SEC ) << " seconds " << endl;
    }
    return 0;
}
