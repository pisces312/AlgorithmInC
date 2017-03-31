#ifndef COMMON_H_INCLUDED
#define COMMON_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <assert.h>
#include <memory.h>

#include <iostream>
#include <iomanip>
#include <queue>
#include <vector>
#include <list>
#include <set>
#include <stack>
#include <algorithm>

inline void swapInt(int* a,int* b) {
    int tmp=*a;
    *a=*b;
    *b=tmp;
}
//inline void swap(int* x,int i, int j)
//{	int t = x[i];
//	x[i] = x[j];
//	x[j] = t;
//}
inline void swap(int* x,const int i, const int j)
{	int t = x[i];
	x[i] = x[j];
	x[j] = t;
}
void printArray(int*a,int n) ;

//template<class T>
//void display(T a[],int n) {
//    for(int i=0; i<n; i++)
//        std::cout<<a[i]<<" ";
//    std::cout<<std::endl;
//}
//template<class T>
//void display(T* a,int n);
//void display(T a[],int n);
#endif // COMMON_H_INCLUDED
