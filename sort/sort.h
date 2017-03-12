#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED
#include "../common.h"

//Test
int testSortMain();

/* Simplest insertion sort */
void insertSort1(int* x,int n);
/* Write swap function inline */
void insertSort2(int* x,int n);
/* Move assignments to and from t out of loop */
void insertSort3(int* x,int n);
//改进：使用二分搜索找到插入的位置
void insertSortWithBisearch(int* x,int n);



void quickSortLomuto(int* x,int n);
void quickSortLomuto2(int* x,int n);
void quickSortForDup(int* a,int n);
void quickSortSedgewick(int* x,int n);
void quickSortTwoWayPartition(int* x,int n);
void quickSortTwoWayPartition2(int* x,int n);
void _fastcall quickSortFinal(int* x,int n);
int partition(int*x,int l,int u);
void quickSortNonRecursive(int*x,int n);
void quickSortNonRecursive2(int*x,int n);

void selectSort(int* x,int n);

void heapSort1(int* x,int n);
void heapSort2(int* x,int n);
void heapSort3(int* x,int n);
void heapSort4(int* x,int n);


void siftdownMinHeap(int *h,int i,int n);
void siftupMinHeap(int*h,int i);
void siftdownMaxHeap(int *h,int i,int n);
void siftupMaxHeap(int*h,int i);
void heapSortByMinHeap(int*h,int n);
void heapSortByMaxHeap(int*h,int n);
int deletemax(int*h,int n);


void shellSort(int* x,int n);



void bubbleSort1(int* x,int n);
void bubbleSortWithFlag(int* x,int n);

void mergeSort(int *x,int n);
//void mergeSort2(int *x,int n);


void bitSortNoDuplicatePositiveInteger(int *x,int n,int max);
//m:max digit
//d:radix
void radixSortForPositiveInteger(int* x,int n,int m,int d);

/*
内部排序比较

Statistics
*/
class radixNode;
void radixSort(radixNode* a[],int size);
void heapSortShowingDetail(int * table, int n);
void quickSortShowingDetail(int * table, int n);
void bubbleSortShowingDetail(int * table, int n);
void selectSortShowingDetail(int * table, int n);
void insertSortShowingDetail(int *table, int n);
void shellSortShowingDetail(int* t, int n);
#endif // SORT_H_INCLUDED
