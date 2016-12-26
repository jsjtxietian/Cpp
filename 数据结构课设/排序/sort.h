#include<iostream>
#include<vector>
#include<ctime>
#include<functional>

using namespace std;

void exitProgram(vector<int> data);

void bubbleSort(vector<int> data);
void selectSort(vector<int> data);
void insertSort(vector<int> data);
void shellSort(vector<int> data);

void quickSort(vector<int> data);
int quickSortMethod(vector<int>& data, int , int );

void mergeSort(vector<int> data);
int mergeSortRecursive(vector<int>& data, int *reg, int start, int end);

int maxbit(vector<int> data, int );
void radixSort(vector<int> data);

int maxHeapify(vector<int>& data, int start, int end);
void heapSort(vector<int> data);



