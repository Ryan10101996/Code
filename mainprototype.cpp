#include <iostream>
#include <string>
#include <time.h>
using namespace std;


////////////////////////////////////////////////////////////////////////////
//start array sort class

template<class T>
class arraysort{
    private:
        int size;
        T *unsorted_arr;
        T *sorted_arr;
    public:
        
        arraysort();
        void fillarray();
        void fillarrayc();
    	void setsize(int);
	    void sortarr();
	    void rsortarr();
	    int getsize();
	    T getunsorted_arr();
	    T getsorted_arr();
	    void printall();
	    
};

//end array sort class
/////////////////////////////////////////////////////////////////////////////
//begin main

int main(int argc,char*argv[]){
    srand(time(0));

	double num = stoi(argv[1]);


	arraysort<int> thing;
	arraysort<char> thing2;
	thing.setsize(num);
	thing.fillarray();
	thing.sortarr();
	thing.printall();

	thing2.setsize(num);
	thing2.fillarrayc();
	thing2.sortarr();
	thing2.printall();



    return 0;
}

//end main
///////////////////////////////////////////////////////////////////////////////
//main functions


//end main functions
//////////////////////////////////////////////////////////////////////////////
//overloading functions




//end overloading functions
///////////////////////////////////////////////////////////////////////////////
//array functions start

template <class T>
arraysort<T>::arraysort(){
	size =0;
}

template <class T>
void arraysort<T>::setsize(int a){

	size = a;
	unsorted_arr=new T[size];
    sorted_arr=new T[size];
}

template <class T>
void arraysort<T>::fillarray(){
	for(int i = 0; i < size; i++){
		unsorted_arr[i] =1+rand()%100+1;
	}
}

template<class T>
void arraysort<T>::fillarrayc(){
	for(int i = 0; i < size; i++){
		unsorted_arr[i] +=(char)(65+rand()%25+1);
	}
}

template <class T>
void arraysort<T>::sortarr(){
	
	for (int i=0;i<size;i++){

	sorted_arr[i]=unsorted_arr[i];	

	}

	for(int i =size-1; i>0;i--){
		for(int j=0;j<i;j++){
			if(sorted_arr[j]>sorted_arr[j+1]){
				int temp = sorted_arr[j+1];
				sorted_arr[j+1]=sorted_arr[j];
				sorted_arr[j]=temp;
			}
		}
	
	}

}

template<class T>
int arraysort<T>::getsize(){return size;}

template<class T>
T arraysort<T>::getunsorted_arr(){return *unsorted_arr;}

template<class T>
T arraysort<T>::getsorted_arr(){return *sorted_arr;}

template<class T>
void arraysort<T>::printall(){

	cout << "The size of the array is: "<<size <<endl;
	cout << "The unsorted array is: [";
		for (int i = 0; i<size; i++){
		
			cout <<unsorted_arr[i] <<" ";

		}	
		cout << "]"<<endl;

	cout << "The sorted array is: [";
                for (int i = 0; i<size; i++){

                        cout <<sorted_arr[i] <<" ";

                }
                cout << "]"<<endl;

}

//end arraysort functions
