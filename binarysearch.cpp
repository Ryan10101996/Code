#include <iostream>
#include <math.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <time.h>
using namespace std;
int binarySearch(int arr[], int l, int r, int x) {
	if (r >= l)
	{
		int mid = l + (r - l) / 2;
		if (arr[mid] == x)
			return mid;
		if (arr[mid] > x)
			return binarySearch(arr, l, mid - 1, x);
		return binarySearch(arr, mid + 1, r, x);
	}
	return -1;
}

int main() {
	// 2 places you need to change size
	int arraySize = 2097152;
	static int ar[2097152];
	//

	for (int i = 0; i < arraySize; i++) {
		ar[i] = i;
	}

	//128     =
	//512     = 650
	//2048    = 860
	//8192    = 1062
	//32768   = 1172
	//131072  = 1362
	//524288  = 1622
	//2097152 = 1772
	clock_t t;
	t = clock();
	int target = arraySize+1;
	for (double i = 0; i < 10000000; i++) {
		binarySearch(ar, 0, arraySize - 1, arraySize+1);
	}
	t = clock() - t;
	cout << t;

	delete[] ar;

	return 0;
}
