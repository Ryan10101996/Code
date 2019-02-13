#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/* Objective: Exhaust the memory to understand fragmentation and explain the timings.
 *
 */
int main(int argc, char** argv) {
    clock_t begin1, stop1, begin2, stop2;
    double tdif = 0, tdif2 = 0;
    for (int k = 0; k < 1000; k++) {
        double dif, dif2;
        const int m = 65000; //Change this
        begin1 = clock();
        printf("Step One\n"); //DO NOT CHANGE
        int *container[3 * m];
        for (int i = 0; i < (3 * m); i++) {
            int *tmpAry = (int *) malloc(800000 * sizeof (int));
            container[i] = tmpAry;
        }
        stop1 = clock();
        printf("Step Two\n"); //DO NOT CHANGE
        for (int i = 0; i < (3 * m); i += 2) {
            free(container[i]);
        }
        begin2 = clock();
        printf("Step Three\n\n"); //DO NOT CHANGE
        int *container2[m];
        for (int i = 0; i < m; i++) {
            int *tmpAry = (int *) malloc(900000 * sizeof (int));
            container2[i] = tmpAry;
        }
        stop2 = clock();
        dif = (stop1 - begin1) / 1000.00;
        dif2 = (stop2 - begin2) / 1000.00;
        tdif += dif;
        tdif /= 2;
        tdif2 += dif2;
        tdif2 /= 2;
    }
    printf("First array allocation: %.5f\n", tdif);
    printf("Second array allocation: %.5f\n", tdif2);
    system("pause");
};
