#include <iostream>
#include <time.h>

using namespace std;

void time_Function2(int n_value) {
	/* function that does the matrix multiplication */
	int ** matrixA = new int *[n_value];
	int ** matrixB = new int *[n_value];
	int ** matrixC = new int *[n_value];
	for (int i = 0; i < n_value; i++) {
		matrixA[i] = new int[n_value];
		matrixB[i] = new int[n_value];
		matrixC[i] = new int[n_value];
	}
	for (int k = 0; k < n_value; k++) {
		for (int l = 0; l < n_value; l++) {
			matrixA[k][l] = 1;
			matrixB[k][l] = 1;
		}
	}
	/* for debug purposes
	for (int x = 0; x < n_value; x++) {
	cout << "Matrix A has " << matrixA[x][x] << endl;
	cout << "Matrix B has " << matrixB[x][x] << endl;
	}
	*/
	clock_t timeBeg;
	timeBeg = clock();
	for (int i = 0; i < n_value; i++) {
		for (int j = 0; j < n_value; j++) {
			matrixC[j][i] = matrixA[j][i] + matrixB[j][i];
		}
	}
	cout << "Time elapsed for Matrix multiplication: " << ((((double)clock() - timeBeg) * 1000) / CLOCKS_PER_SEC) << " milliseconds." << endl;
	delete matrixA;
	delete matrixB;
	delete matrixC;
}

void time_Function(int n_value) {
	/* function that does the matrix multiplication */
	int ** matrixA = new int *[n_value];
	int ** matrixB = new int *[n_value];
	int ** matrixC = new int *[n_value];
	for (int i = 0; i < n_value; i++) {
		matrixA[i] = new int[n_value];
		matrixB[i] = new int[n_value];
		matrixC[i] = new int[n_value];
	}
	for (int k = 0; k < n_value; k++) {
		for (int l = 0; l < n_value; l++) {
			matrixA[k][l] = 1;
			matrixB[k][l] = 1;
		}
	}
	/* for debug purposes
	for (int x = 0; x < n_value; x++) {
	cout << "Matrix A has " << matrixA[x][x] << endl;
	cout << "Matrix B has " << matrixB[x][x] << endl;
	}
	*/
	clock_t timeBeg;
	timeBeg = clock();
	for (int i = 0; i < n_value; i++) {
		for (int j = 0; j < n_value; j++) {
			matrixC[i][j] = matrixA[i][j] + matrixB[i][j];
		}
	}
	cout << "Time elapsed for Matrix multiplication: " << ((((double)clock() - timeBeg) * 1000) / CLOCKS_PER_SEC) << " milliseconds." << endl;
	delete matrixA;
	delete matrixB;
	delete matrixC;
}

int main() {
	int n_values[10] = { 128,256,512,1024,2048,4096,8192,16384,32768,65536 };
	/*
	for (int i = 0; i < 10; i++) {
	time_Function(n_values[i]);
	}
	*/
	for (int j = 0; j < 10; j++) {
		time_Function2(n_values[j]);
	}
	system("pause");
	return 0;
}
