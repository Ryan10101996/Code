#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MNUMARRAYS 425000
void allocateArray(int **mainArray, int numOfArrays, int sizeOfArrays) {
    int i;
    for(i = 0; i < numOfArrays; i++) {
        mainArray[i] = (int *) malloc(sizeof(int) * sizeOfArrays);
    }
}
 /* Loop through arrays and free memory every even */

void deallocateEvenArrays(int **mainArray, int numOfArrays) {
    int i;
    for(i = 0; i < numOfArrays; i++) {
        if(i % 2 == 0) {
            free(mainArray[i]);
        }
    }
}

int main() {
    clock_t first_startTime, first_endTime;
    clock_t second_startTime, second_endTime;

    int ** mainArray1;
    int ** mainArray2;

    first_startTime = clock();
    mainArray1 = (int **) malloc(sizeof(int) * 3 * MNUMARRAYS);  /* Allocate3*MNUMBERRAYS arrays */
    allocateArray(mainArray1, 3 * MNUMARRAYS, 800000);
    first_endTime = clock();

    deallocateEvenArrays(mainArray1, 3 * MNUMARRAYS);

    second_startTime = clock();
    mainArray2 = (int **) malloc(sizeof(int) * 3 * MNUMARRAYS);
    allocateArray(mainArray2, 3 * MNUMARRAYS, 900000);
    second_endTime = clock();
/* Print out the difference for both sequences & dealloc */
    printf("FIRST ALLOCATION TIME: %f seconds\n", (double)(((double)first_endTime - (double)first_startTime)/(double)CLOCKS_PER_SEC));
    printf("SECOND ALLOCATION TIME: %f seconds\n", (double)(((double)second_endTime - (double)second_startTime)/(double)CLOCKS_PER_SEC));
	getchar();
}
